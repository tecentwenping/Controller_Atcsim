#include "../wdllexport.h"
#include "wevent.h"
#include "wcursor.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wworldpolygon.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "witemshareprivate.h"
#include "wgraphicspolylineitem.h"

static const int SF_NONE = 0x0;
static const int SF_VERTEX = 0x1;
static const int SF_CONTENT = 0x2;

inline static int low_word(int i)
{
	return i & 0xffff;
}

inline static int high_word(int i)
{
	return (i >> 16) & 0xffff;
}

inline static int make_int(int highword, int lowword)
{
	return ((highword & 0xffff) << 16) | (lowword & 0xffff);
}

static Ws::CursorShape getCursorShape(int flag)
{
	switch(low_word(flag))
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_VERTEX : return Ws::PointingHandCursor;
	case SF_CONTENT : return Ws::SizeAllCursor;
	default: return Ws::ArrowCursor;
	}
}

static bool near_line(const WWorldPointF& p1, const WWorldPointF& p2, const WWorldPointF& point)
{
	return distance(point, p1) + distance(point, p2) - distance(p1, p2) <= 1.0;
}

static WWorldPolylineF draggedPolyline(const WWorldPolylineF& p, const WWorldPointF& from, const WWorldPointF& to, int select_flag)
{
	WWorldPolylineF polyline = p;
	int flag = low_word(select_flag);
	WWorldPointF offset = to - from;

	if (flag == SF_CONTENT) //drag move the whole polyline
	{
		polyline.translate(offset);
	}
	else if (flag == SF_VERTEX) //drag move vertex
	{
		polyline[high_word(select_flag)] += offset;
	}

	return polyline;
}

RTTI_IMPL(WGraphicsPolylineItem)

char* WPolylineItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << pen << polyline).value();
}

const char* WPolylineItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> pen >> polyline).value();
}

size_t WPolylineItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << pen << polyline).value();
}

WGraphicsPolylineItem::WGraphicsPolylineItem(const WWorldPolylineF& p, const WPen& pn) :
	WGraphicsItem(new data_type(Type, p, pn)), _select_flag(SF_NONE)
{
}

WGraphicsPolylineItem::WGraphicsPolylineItem(WPolylineItemData* d) : 
	WGraphicsItem(d ? d : new data_type), _select_flag(SF_NONE)
{
}

WWorldPolylineF WGraphicsPolylineItem::polyline() const
{
	return data()->polyline;
}

const std::vector<WWorldPointF>& WGraphicsPolylineItem::points() const
{
	return data()->polyline;
}

WPen WGraphicsPolylineItem::pen() const
{
	return data()->pen;
}

void WGraphicsPolylineItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (pen == data()->pen)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPolylineItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WGraphicsPolylineItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsPolylineItem::setPolyline(const WWorldPolylineF& p, bool update, bool opStack)
{
	if (p == data()->polyline)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPolylineItem::setPolyline, this, p, true, false),
			WCmdFactory::create(&WGraphicsPolylineItem::setPolyline, this, data()->polyline, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->polyline = p;
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->polyline = p;
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsPolylineItem::setPoints(const std::vector<WWorldPointF>& pts, bool update, bool opStack)
{
	setPolyline(WWorldPolylineF(pts), update, opStack);
}

bool WGraphicsPolylineItem::setPoint(unsigned index, const WWorldPointF& pos, bool update, bool opStack)
{
	WWorldPolylineF& p = data()->polyline;
	if (index >= p.size() || p[index] == pos)
	{
		return false;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPolylineItem::setPoint, this, index, pos, true, false),
			WCmdFactory::create(&WGraphicsPolylineItem::setPoint, this, index, p[index], true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		p[index] = pos;
		scene()->update(r | boundingRect());
	}
	else
	{
		p[index] = pos;
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
	return true;
}

void WGraphicsPolylineItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setPen(data()->pen);
	painter->drawPolyline(data()->polyline);

	if (isSelected())
	{
		painter->setPen(CP_PEN);
		painter->setBrush(CP_BRUSH);
		const std::vector<WWorldPointF>& v = data()->polyline;
		unsigned size = v.size();
		
		for (unsigned i=0; i<size; ++i)
		{
			painter->drawEllipse(WWorldRectF(v[i].x()-CP_RADIUS, v[i].y()-CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS));
		}

		if (_dragging)
		{
			WPen dragPen = data()->pen;
			dragPen.setColor(dragPen.color().lighter(2.0));
			painter->setPen(dragPen);
			painter->drawPolyline(draggedPolyline(data()->polyline, scene()->dragStartPos(), scene()->attachedPoint(scene()->mousePos()), _select_flag));
		}
	}
}

bool WGraphicsPolylineItem::contains(const WWorldPointF& point) const
{
	const std::vector<WWorldPointF>& v = data()->polyline;

	unsigned size = v.size();
	if (size < 2)
	{
		return false;
	}

	for (unsigned i=0; i<size-1; ++i)
	{
		if (near_line(v[i], v[i+1], point) || distance(v[i], point) < CP_RADIUS)
		{
			return true;
		}
	}

	return distance(v[size-1], point) < CP_RADIUS;
}

WWorldRectF WGraphicsPolylineItem::boundingRect() const
{
	return expanded(data()->polyline.boundingRect());
}

void WGraphicsPolylineItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();

	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;
			
			WWorldPolylineF polylineFrom = draggedPolyline(data()->polyline, scene()->dragStartPos(), event->lastScenePos(), _select_flag);
			WWorldPolylineF polylineTo = draggedPolyline(data()->polyline, scene()->dragStartPos(), event->scenePos(), _select_flag);
			scene()->update(expanded(polylineFrom.boundingRect() | polylineTo.boundingRect() | data()->polyline.boundingRect()));
		}
		else //update select flag (status transfer) 
		{
			int old_flag = _select_flag;
			if (!contains(pos)) //other status ---> none selected
			{
				_select_flag = SF_NONE;
			}
			else
			{
				const std::vector<WWorldPointF>& v = data()->polyline;
				unsigned i = 0;
				unsigned size = v.size();

				for (; i<size; ++i)
				{
					if (distance(pos, v[i]) < CP_RADIUS)
					{
						_select_flag = make_int(i, SF_VERTEX);
						break;
					}
				}

				if (i == size) //no vertex is selected, that is, content is selected
				{
					_select_flag = SF_CONTENT;
				}
			}

			if (_select_flag != old_flag) //select status changed
			{
				scene()->update(boundingRect());
				event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
			}
		}
	}
}

void WGraphicsPolylineItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::LeftButton)
	{
		bool contain = contains(event->scenePos());
		if (isSelectable() && !isSelected() && contain) //status transfer, not selected ---> selected
		{
			_select_flag = SF_CONTENT;
			setSelected();
			scene()->update(boundingRect());
			event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

			scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
		}
		else if (isSelected() && !contain) //status transfer, selected ---> not selected
		{
			_select_flag = SF_NONE;
			setSelected(false);
			scene()->update(boundingRect());
			event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

			scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
		}
	}
	else if (event->button() == Ws::RightButton)
	{
		Ws::ContextMenuFlags flags = 0;
		int flag = low_word(_select_flag);
		if (flag == SF_VERTEX)
		{
			if (data()->polyline.size() > 2)
			{
				flags |= Ws::DeleteVertex;
			}
			if (high_word(_select_flag) != 0)
			{
				flags |= Ws::AddVertex;
			}
		}
		else if (flag == SF_CONTENT)
		{
			flags |= Ws::Copy;
		}

		if (flags)
		{
			requestContextMenu(flags);
		}
	}
}

void WGraphicsPolylineItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		setPolyline(draggedPolyline(data()->polyline, scene()->dragStartPos(), scene()->attachedPoint(event->scenePos()), _select_flag));
		scene()->update();
	}
}

WGraphicsPolylineItem::data_type* WGraphicsPolylineItem::data()
{
	return W_D();
}

const WGraphicsPolylineItem::data_type* WGraphicsPolylineItem::data() const
{
	return W_CD();
}

WGraphicsPolylineItem* WGraphicsPolylineItem::copy() const
{
	return new WGraphicsPolylineItem(new data_type(*data()));
}

int WGraphicsPolylineItem::type() const
{
	return Type;
}

bool WGraphicsPolylineItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	const std::vector<WWorldPointF>& v = data()->polyline;
	if (v.empty())
	{
	   return false;
	}
	
	int size = v.size() - 1;

	for (int i=0; i<size; ++i)
	{
		if (::attachLine(WWorldLineF(v[i], v[i+1]), ATTACH_DISTANCE, pos, attachedPos))
		{
			return true;
		}
	}
	return false;
}

void WGraphicsPolylineItem::onContextMenu(Ws::ContextMenuFlag flag)
{
	if (flag == Ws::AddVertex)
	{
		int id = high_word(_select_flag);
		WWorldPolylineF p = data()->polyline;
		p.insert(p.begin()+id, (p[id-1] + p[id])/2);
		setPolyline(p, true, true);
	}
	else if (flag == Ws::DeleteVertex)
	{
		int id = high_word(_select_flag);
		WWorldPolylineF p = data()->polyline;
		p.erase(p.begin() + id);
		setPolyline(p, true, true);
	}
	else if (flag == Ws::Copy)
	{
		scene()->setClipboard(this);
	}
}

void WGraphicsPolylineItem::translate(const WWorldPointF& offset)
{
	setPolyline(data()->polyline.translated(offset));
}