#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include "../wdllexport.h"
#include "wevent.h"
#include "wcursor.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wgraphicsview.h"
#include "wworldpolygon.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "wgraphicspointitem.h"

//SF -> selected flag
static const int SF_NONE = 0x0; //没有被选中
static const int SF_CONTENT = 0x1; //点被选中

/**
\brief      getCursorShape
\Access    public static 
\param  int flag
\retval     Ws::CursorShape
\remark      根据图元的选中状态获取光标的形状
*/
static Ws::CursorShape getCursorShape(int flag)
{
	switch(flag)
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_CONTENT : return Ws::PointingHandCursor;
	default: return Ws::ArrowCursor;
	}
}

RTTI_IMPL(WGraphicsPointItem)

char* WPointItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << pos << pen).value();
}

const char* WPointItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> pos >> pen).value();
}

size_t WPointItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << pos << pen).value();
}

WGraphicsPointItem::WGraphicsPointItem(const WWorldPointF& p, const WPen& pn) : 
	WGraphicsItem(new data_type(Type, p, pn)), _select_flag(SF_NONE)
{
	updateCp();
}

WGraphicsPointItem::WGraphicsPointItem(WPointItemData* d) :
WGraphicsItem(d ? d : new data_type), _select_flag(SF_NONE)
{
	updateCp();
}

WWorldPointF WGraphicsPointItem::pos() const
{
	return data()->pos;
}

WPen WGraphicsPointItem::pen() const
{
	return data()->pen;
}

void WGraphicsPointItem::setPos(const WWorldPointF& pos, bool update, bool opStack)
{
	if (pos == data()->pos)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPointItem::setPos, this, pos, true, false),
			WCmdFactory::create(&WGraphicsPointItem::setPos, this, data()->pos, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->pos = pos;
		updateCp();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->pos = pos;
		updateCp();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsPointItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (pen == data()->pen)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPointItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WGraphicsPointItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

/**
\brief      paint
\Access    virtual public 
\param  WPainter * painter
\retval     void
\remark     目前点主要用一个三角形来表达
*/
void WGraphicsPointItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);

	painter->setPen(data()->pen);
	painter->setBrush(isSelected() ? CP_BRUSH : WBrush());
	painter->drawPolygon(_cp); //绘制对应的三角形区域

	if (isSelected() && _dragging) //点被选中，并且在拖动
	{
		WWorldPointF pos = scene()->attachedPoint(scene()->mousePos());

		painter->setPen(DRAG_PEN);
		painter->setBrush(WBrush());
		painter->drawPolygon(_cp.translated(pos - scene()->dragStartPos()));
	}
}

bool WGraphicsPointItem::contains(const WWorldPointF& point) const
{
	return _cp.containsPoint(point);
}

WWorldRectF WGraphicsPointItem::boundingRect() const
{
	return expanded(_cp.boundingRect());
}

int WGraphicsPointItem::type() const
{
	return Type;
}

void WGraphicsPointItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();

	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //selected && drag move
		{
			_dragging = true;
			
			WWorldPolygonF polygonFrom = _cp.translated(event->lastScenePos() - scene()->dragStartPos());
			WWorldPolygonF polygonTo = _cp.translated(pos - scene()->dragStartPos());
			scene()->update(expanded(polygonFrom.boundingRect() | polygonTo.boundingRect() | _cp.boundingRect()));
		}
		else //update select flag (status transfer)
		{
			int old_flag = _select_flag;
			_select_flag = (contains(pos) ? SF_CONTENT : SF_NONE);

			if (old_flag != _select_flag) //select status changed
			{
				scene()->update(boundingRect());
				event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
			}
		}
	}
}

void WGraphicsPointItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	bool contain = contains(event->scenePos());
	if (isSelectable() && !isSelected() && contain) //status transfer, not selected ---> selected
	{
		setSelected();
		_select_flag = SF_CONTENT;
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
		
		scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
	}
	else if (isSelected() && !contain) //status transfer, selected ---> not selected
	{
		setSelected(false);
		_select_flag = SF_NONE;
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

		scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
	}
}

void WGraphicsPointItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;
		setPos(scene()->attachedPoint(event->scenePos()), false, true);
		scene()->update();
	}
}

WGraphicsPointItem::data_type* WGraphicsPointItem::data()
{
	return W_D();
}

const WGraphicsPointItem::data_type* WGraphicsPointItem::data() const
{
	return W_CD();
}

WGraphicsPointItem* WGraphicsPointItem::copy() const
{
	return new WGraphicsPointItem(new data_type(*data()));
}

/**
\brief      updateCp
\Access    private 
\retval     void
\remark     更新点对应的三角形区域
*/
void WGraphicsPointItem::updateCp()
{
	static const double M_PI_6 = M_PI / 6;
	static const double RADIUS = CP_RADIUS * 2;
	static const double A = RADIUS * sin(M_PI_6);
	static const double B = RADIUS * cos(M_PI_6);

	if (_cp.size() != 4)
	{
		_cp.resize(4);
	}
	
	double x = data()->pos.x();
	double y = data()->pos.y();

	_cp[0].setXY(x, y+RADIUS);
	_cp[1].setXY(x-B, y-A);
	_cp[2].setXY(x+B, y-A);
	_cp[3] = _cp[0];
}

bool WGraphicsPointItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	const WWorldPointF& p = data()->pos;
	if (pos != p && distance(pos, p) < ATTACH_DISTANCE)
	{
		if (attachedPos)
		{
			*attachedPos = p;
		}
		return true;
	}

	return false;
}

void WGraphicsPointItem::translate(const WWorldPointF& offset)
{
	setPos(data()->pos + offset);
}