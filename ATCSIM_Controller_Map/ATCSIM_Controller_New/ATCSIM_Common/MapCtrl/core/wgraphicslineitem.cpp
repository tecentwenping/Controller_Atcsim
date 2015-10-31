#include <cmath>
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
#include "wgraphicschange.h"
#include "wgraphicslineitem.h"
#include "witemshareprivate.h"

//SF -> selected flag
static const int SF_NONE = 0x0; //直线没有选中
static const int SF_START = 0x1; //直线的起点被选中
static const int SF_END = 0x2; //直线的终点被选中
static const int SF_CONTENT = 0x4; //直线的中间线段部分被选中

/**
\brief      getCursorShape
\Access    public static 
\param  int flag
\retval     Ws::CursorShape
\remark     根据直线的选中状态来获取光标形状
*/
static Ws::CursorShape getCursorShape(int flag)
{
	switch(flag)
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_START : return Ws::CrossCursor;
	case SF_END : return Ws::CrossCursor;
	case SF_CONTENT : return Ws::SizeAllCursor;
	default: return Ws::ArrowCursor;
	}
}

RTTI_IMPL(WGraphicsLineItem)

char* WLineItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << line << pen).value();
}

const char* WLineItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> line >> pen).value();
}

size_t WLineItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << line << pen).value();
}

WGraphicsLineItem::WGraphicsLineItem(const WWorldLineF& l, const WPen& p) : 
	WGraphicsItem(new data_type(Type, l, p)), _select_flag(SF_NONE), _show_arraw(false)
{
}

WGraphicsLineItem::WGraphicsLineItem(data_type* d) : WGraphicsItem(d ? d : new data_type),
	_select_flag(SF_NONE), _show_arraw(false)
{
}

WWorldLineF WGraphicsLineItem::line() const
{
	return data()->line;
}

WPen WGraphicsLineItem::pen() const
{
	return data()->pen;
}

void WGraphicsLineItem::setLine(const WWorldLineF& line, bool update, bool opStack)
{
	if (line == data()->line)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsLineItem::setLine, this, line, true, false),
			WCmdFactory::create(&WGraphicsLineItem::setLine, this, data()->line, true, false));
	}

	if (update)
	{
		WWorldRectF r = ::boundingRect(data()->line.p1(), data()->line.p2(), line.p1(), line.p2());
		data()->line = line;
		scene()->update(expanded(r));
	}
	else
	{
		data()->line = line;
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsLineItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (pen == data()->pen)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsLineItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WGraphicsLineItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

int WGraphicsLineItem::type() const
{
	return Type;
}

void WGraphicsLineItem::keyPressEvent(WKeyEvent* event)
{
	if (isSelected()) //如果被选中
	{
		if ((event->modifiers() & Ws::ShiftModifier)) //旋转直线
		{
			const int UNIT = (event->modifiers() & Ws::ControlModifier) ? 1 : 45; //ctrl是否被按下？
			WWorldPointF c = data()->line.center();
			int delta = 0;
			int angle = approximate_integer(data()->line.angle());
			int rem = angle % UNIT;

			if (event->key() == Ws::Key_Up) //向上旋转直线
			{
				delta = UNIT - rem;
			}
			else if (event->key() == Ws::Key_Down) //向下旋转直线
			{
				delta = (rem == 0) ? -UNIT : -rem;
			}

			if (delta) //旋转角度不为0
			{
				WWorldLineF line = data()->line;
				WWorldRectF r(boundingRect());
				data()->line.setAngle(angle + delta);
				data()->line.translate(c - data()->line.center());
				scene()->update(r | boundingRect());

				scene()->operationStack()->push(WCmdFactory::create(&WGraphicsLineItem::setLine, this, data()->line, true, false),
					WCmdFactory::create(&WGraphicsLineItem::setLine, this, line, true, false));

				scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
			}
		}
	}
}

void WGraphicsLineItem::showArraw(bool show, bool update)
{
	_show_arraw = show;
	if (update)
	{
		scene()->update(boundingRect());
	}
}

bool WGraphicsLineItem::isArrawShow() const
{
	return _show_arraw;
}

WGraphicsLineItem::data_type* WGraphicsLineItem::data()
{
	return W_D();
}

const WGraphicsLineItem::data_type* WGraphicsLineItem::data() const
{
	return W_CD();
}

WGraphicsLineItem* WGraphicsLineItem::copy() const
{
	return new WGraphicsLineItem(new data_type(*data()));
}

bool WGraphicsLineItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	return ::attachLine(data()->line, ATTACH_DISTANCE, pos, attachedPos);
}

void WGraphicsLineItem::translate(const WWorldPointF& offset)
{
	setLine(data()->line.translated(offset));
}

void WGraphicsLineItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();

	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //selected && drag move
		{
			_dragging = true;

			WWorldRectF r;
			const WWorldLineF& line = data()->line;
			WWorldPointF lastPos = event->lastScenePos();
			
			if (_select_flag & SF_CONTENT)
			{
				WWorldLineF lineFrom = line.translated(lastPos - scene()->dragStartPos());
				WWorldLineF lineTo = line.translated(pos - scene()->dragStartPos());
				r = ::boundingRect(line.p1(), line.p2(), lineFrom.p1(), lineFrom.p2(), lineTo.p1(), lineTo.p2());
			}
			else	
			{
				r = ::boundingRect(line.p1(), line.p2(), pos, lastPos);
			}

			scene()->update(expand(r));
		}
		else //update select flag (status transfer)
		{
			int old_flag = _select_flag;
			if (!contains(pos)) //other status ---> none selected
			{
				_select_flag = SF_NONE;
			}
			else if (distance(pos, data()->line.p1()) < CP_RADIUS) //other status ---> start point selected
			{
				_select_flag = SF_START;
			}
			else if (distance(pos, data()->line.p2()) < CP_RADIUS) //other status ---> end point selected
			{
				_select_flag = SF_END;
			}
			else //other status ---> content selected
			{
				_select_flag = SF_CONTENT;
			}

			if (old_flag != _select_flag) //select status changed
			{
				scene()->update(boundingRect());
				event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
			}
		}
	}
}

void WGraphicsLineItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
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

void WGraphicsLineItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		WWorldLineF newline;
		WWorldLineF& line = data()->line;
		WWorldPointF pos = scene()->attachedPoint(event->scenePos());

		if (_select_flag & SF_START)
		{
			newline = WWorldLineF(pos, line.p2());
		}
		else if (_select_flag & SF_END)
		{
			newline = WWorldLineF(line.p1(), pos);
		}
		else if (_select_flag & SF_CONTENT)
		{
			newline = line.translated(pos - scene()->dragStartPos());
		}
		setLine(newline, false, true);
		scene()->update();
	}
}

void WGraphicsLineItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);

	painter->setPen(data()->pen);
	painter->drawLine(data()->line);

	if (_show_arraw && data()->line.length() > 10.0) //如果显示箭头，则绘制箭头
	{
		double angle = data()->line.angle() + 180.0;
		WWorldLineF line(data()->line.p2(), data()->line.p1());
		line.setLength(10.0);
		painter->setPen(WPen());
		for (int i=-1; i<2; i+=2)
		{
			line.setAngle(angle + i * 30.0);
			painter->drawLine(line);
		}
	}

	if (isSelected()) //如果直线被选中
	{
		painter->setBrush(CP_BRUSH);
		painter->setPen(WPen(Ws::SolidLine, WColor(0, 0, 255), 2.0));

		//绘制控制点，即起点和终点
		WWorldPointF p[2] = {data()->line.p1(), data()->line.p2()};
		for (unsigned i=0; i<sizeof(p)/sizeof(p[0]); ++i)
		{
			painter->drawEllipse(WWorldRectF(p[i].x()-CP_RADIUS, p[i].y()-CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS));
		}

		if (_dragging) //直线在拖动
		{
			WWorldPointF pos = scene()->attachedPoint(scene()->mousePos());
			WPen dragPen = data()->pen;
			dragPen.setColor(dragPen.color().lighter(2.0));
			painter->setPen(dragPen);
			
			if (_select_flag & SF_START)
			{
				painter->drawLine(WWorldLineF(pos, p[1]));
			}
			else if (_select_flag & SF_END)
			{
				painter->drawLine(WWorldLineF(p[0], pos));
			}
			else
			{
				painter->drawLine(data()->line.translated(pos - scene()->dragStartPos()));
			}
		}
	}
}

bool WGraphicsLineItem::contains(const WWorldPointF& point) const
{
	return distance(point, data()->line.p1()) < CP_RADIUS 
		|| distance(point, data()->line.p2()) < CP_RADIUS
		|| distance(point, data()->line.p1()) + distance(point, data()->line.p2()) - distance(data()->line.p1(), data()->line.p2()) <= 1.0;
}

WWorldRectF WGraphicsLineItem::boundingRect() const
{
	return expanded(WWorldRectF(data()->line.p1(), data()->line.p2()));
}