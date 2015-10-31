#include <algorithm>
#include <functional>
#include "../wdllexport.h"
#include "wevent.h"
#include "wbrush.h"
#include "wcursor.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "witemshareprivate.h"
#include "wgraphicspolygonitem.h"

//select flag--->SF
static const int SF_NONE = 0x0; //没有被选中
static const int SF_VERTEX = 0x1; //多边形顶点被选中
static const int SF_MID = 0x2; //多边形的边的中点被选中
static const int SF_CONTENT = 0x4; //多边形内部区域被选中

/**
\brief      low_word
\Access    public static 
\param  int i
\retval     int
\remark     获取一个整数的高16位
*/
inline static int low_word(int i)
{
	return i & 0xffff;
}

/**
\brief      high_word
\Access    public static 
\param  int i
\retval     int
\remark     获取一个整数的低16位
*/
inline static int high_word(int i)
{
	return (i >> 16) & 0xffff;
}

/**
\brief      make_int
\Access    public static 
\param  int highword
\param  int lowword
\retval     int
\remark     以高16位和低16位构造一个整数
*/
inline static int make_int(int highword, int lowword)
{
	return ((highword & 0xffff) << 16) | (lowword & 0xffff);
}

/**
\brief      getCursorShape
\Access    public static 
\param  int flag
\retval     Ws::CursorShape
\remark     根据多边形的选中状态获取光标的形状
*/
static Ws::CursorShape getCursorShape(int flag)
{
	switch(low_word(flag))
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_VERTEX : return Ws::PointingHandCursor;
	case SF_MID : return Ws::PointingHandCursor;
	case SF_CONTENT : return Ws::SizeAllCursor;
	default: return Ws::ArrowCursor;
	}
}

/**
\brief      draggedPolygon
\Access    public static 
\param  const WWorldPolygonF & p
\param  const WWorldPointF & from
\param  const WWorldPointF & to
\param  int select_flag
\retval     WWorldPolygonF
\remark    这是一个辅助函数，仅供内部使用
				返回一个多边形(p)以一定方式(select_flag)从一个点(from)拖动到另一个点(to)后的结果 
*/
static WWorldPolygonF draggedPolygon(const WWorldPolygonF& p, const WWorldPointF& from, const WWorldPointF& to, int select_flag)
{
	WWorldPolygonF polygon = p;
	int flag = low_word(select_flag);
	int id = high_word(select_flag);
	WWorldPointF offset = to - from;

	if (flag == SF_CONTENT) //drag move the whole polygon
	{
		polygon.translate(offset);
	}
	else if (flag == SF_VERTEX) //drag move vertex
	{
		polygon[id] += offset;
		if (id == 0) //synchronize the polygon's first element and last element
		{
			*polygon.rbegin() += offset;
		}
	}
	else if (flag == SF_MID) //drag move the middle of two vertexes
	{
		polygon[id] += offset;
		if (id == 0) //synchronize the polygon's first element and last element
		{
			*polygon.rbegin() += offset;
		}

		polygon[id+1] += offset;
		if (static_cast<unsigned>(id + 1) == polygon.size() - 1)  //synchronize the polygon's first element and last element
		{
			polygon[0] += offset;
		}
	}

	return polygon;
}

RTTI_IMPL(WGraphicsPolygonItem)

char* WPolygonItemData::serialize(char* buf) const
{
	return (WSerializer(WAbstractShapeItemData::serialize(buf)) << polygon).value();
}

const char* WPolygonItemData::unserialize(const char* buf)
{
	return (WUnserializer(WAbstractShapeItemData::unserialize(buf)) >> polygon).value();
}

size_t WPolygonItemData::serialize_size() const
{
	return (WSizeHelper(WAbstractShapeItemData::serialize_size()) << polygon).value();
}

WGraphicsPolygonItem::WGraphicsPolygonItem(const WWorldPolygonF& p, const WBrush& b, const WPen& pn) :
	WAbstractGraphicsShapeItem(new data_type(Type, p, b, pn)), _select_flag(SF_NONE)
{
	updateCp();
}

WGraphicsPolygonItem::WGraphicsPolygonItem(data_type* d) : 
	WAbstractGraphicsShapeItem(d ? d : new data_type), _select_flag(SF_NONE)
{
}

WWorldPolygonF WGraphicsPolygonItem::polygon() const
{
	return data()->polygon;
}

const std::vector<WWorldPointF>& WGraphicsPolygonItem::points() const
{
	return data()->polygon;
}

void WGraphicsPolygonItem::setPolygon(const WWorldPolygonF& polygon, bool update, bool opStack)
{
	if (polygon == data()->polygon)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPolygonItem::setPolygon, this, polygon, true, false),
			WCmdFactory::create(&WGraphicsPolygonItem::setPolygon, this, data()->polygon, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->polygon = polygon;
		updateCp();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->polygon = polygon;
		updateCp();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsPolygonItem::setPoints(const std::vector<WWorldPointF>& pts, bool update, bool opStack)
{
	setPolygon(WWorldPolygonF(pts), update, opStack);
}

bool WGraphicsPolygonItem::setPoint(unsigned int index, const WWorldPointF& pos, bool update, bool opStack)
{
	WWorldPolygonF& p = data()->polygon;
	if (index >= p.size() || p[index] == pos)
	{
		return false;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsPolygonItem::setPoint, this, index, pos, true, false),
			WCmdFactory::create(&WGraphicsPolygonItem::setPoint, this, index, p[index], true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		p[index] = pos;
		if (index == 0)
		{
			p.back() = pos;
		}
		else if (index == p.size() - 1)
		{
			*p.begin() = pos;
		}
		updateCp();
		scene()->update(r | boundingRect());
	}
	else
	{
		p[index] = pos;
		if (index == 0)
		{
			p.back() = pos;
		}
		else if (index == p.size() - 1)
		{
			*p.begin() = pos;
		}
		updateCp();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
	return true;
}

void WGraphicsPolygonItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setPen(data()->pen);
	painter->setBrush(data()->brush);
	painter->drawPolygon(data()->polygon); //绘制多边形

	if (isSelected()) //多边形被选中
	{
		painter->setPen(CP_PEN);
		painter->setBrush(CP_BRUSH);
		//绘制控制点
		for (unsigned i=0; i<_cp.size(); ++i)
		{
			painter->drawEllipse(WWorldRectF(_cp[i].x() - CP_RADIUS, _cp[i].y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
			painter->drawEllipse(WWorldRectF(data()->polygon[i].x() - CP_RADIUS, data()->polygon[i].y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
		}

		if (_dragging) //多边形被拖动，绘制拖动后的多边形
		{
			WPen dragPen = data()->pen;
			WBrush dragBrush = data()->brush;
			dragPen.setColor(dragPen.color().lighter(2.0));
			dragBrush.setColor(dragBrush.color().lighter(2.0));
			painter->setPen(dragPen);
			painter->setBrush(dragBrush);
			painter->drawPolygon(draggedPolygon(data()->polygon, scene()->dragStartPos(), scene()->attachedPoint(scene()->mousePos()), _select_flag));
		}
	}
}

bool WGraphicsPolygonItem::contains(const WWorldPointF& point) const
{
	unsigned sz = _cp.size();
	for (unsigned i=0; i<sz; ++i)
	{
		if (distance(point, _cp[i]) < CP_RADIUS || distance(point, data()->polygon[i]) < CP_RADIUS)
		{
			return true;
		}
	}

	return data()->polygon.containsPoint(point);
}

WWorldRectF WGraphicsPolygonItem::boundingRect() const
{
	return expanded(data()->polygon.boundingRect());
}

void WGraphicsPolygonItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();
	
	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;

			WWorldPolygonF polygonFrom = draggedPolygon(data()->polygon, scene()->dragStartPos(), event->lastScenePos(), _select_flag);
			WWorldPolygonF polygonTo = draggedPolygon(data()->polygon, scene()->dragStartPos(), event->scenePos(), _select_flag);
			scene()->update(expanded(polygonFrom.boundingRect() | polygonTo.boundingRect() | data()->polygon.boundingRect()));
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
				unsigned i = 0;
				unsigned size = _cp.size();
				for (; i<size; ++i)
				{
					//detect wheter control point is selected
					if (distance(pos, data()->polygon[i]) < CP_RADIUS)
					{
						_select_flag = make_int(i, SF_VERTEX);
						break;
					}
					else if (distance(pos, _cp[i]) < CP_RADIUS) 
					{
						_select_flag = make_int(i, SF_MID);
						break;
					}
				}

				if (i == size) //no control point is selected, that is, content is selected
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

int WGraphicsPolygonItem::type() const
{
	return TYPE_POLYGON_ITEM;
}

void WGraphicsPolygonItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::LeftButton)
	{
		bool contain = contains(event->scenePos());
		if (isSelectable() && !isSelected() && contain) //not selected ---> selected
		{
			_select_flag = SF_CONTENT;
			setSelected();
			scene()->update(boundingRect());
			event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

			scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
		}
		else if (isSelected() && !contain) //selected ---> not selected
		{
			_select_flag = SF_NONE;
			setSelected(false);
			scene()->update(boundingRect());
			event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

			scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
		}
	}
	else if (event->button() == Ws::RightButton) //请求右键菜单
	{
		int flag = low_word(_select_flag);
		Ws::ContextMenuFlags flags = 0;
		if (flag == SF_VERTEX && data()->polygon.size() > 4)
		{
			flags |= Ws::DeleteVertex;
		}
		else if (flag == SF_MID)
		{
			flags |= Ws::AddVertex;
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

void WGraphicsPolygonItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		setPolygon(draggedPolygon(data()->polygon, scene()->dragStartPos(), scene()->attachedPoint(event->scenePos()), _select_flag), false, true);
		scene()->update();
	}
}

void WGraphicsPolygonItem::updateCp()
{
	unsigned size = data()->polygon.size() - 1;

	if (_cp.size() != size)
	{
		_cp.resize(size);
	}

	for (unsigned i=0; i<size; ++i) //update control points
	{
		_cp[i] = (data()->polygon[i] + data()->polygon[i+1]) / 2;
	}
}

WGraphicsPolygonItem::data_type* WGraphicsPolygonItem::data()
{
	return W_D();
}

const WGraphicsPolygonItem::data_type* WGraphicsPolygonItem::data() const
{
	return W_CD();
}

WGraphicsPolygonItem* WGraphicsPolygonItem::copy() const
{
	return new WGraphicsPolygonItem(new data_type(*data()));
}

bool WGraphicsPolygonItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	const std::vector<WWorldPointF>& v = data()->polygon;
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

void WGraphicsPolygonItem::onContextMenu(Ws::ContextMenuFlag flag)
{
	if (flag == Ws::AddVertex)
	{
		int id = high_word(_select_flag);
		WWorldPolygonF p = data()->polygon;
		p.insert(p.begin()+id+1, _cp[id]);
		setPolygon(p, true, true);
	}
	else if (flag == Ws::DeleteVertex)
	{
		int id = high_word(_select_flag);
		WWorldPolygonF p = data()->polygon;
		p.erase(p.begin() + id);
		if (id == 0)
		{
			p.back() = p.front();
		}
		setPolygon(p, true, true);
	}
	else if (flag == Ws::Copy)
	{
		scene()->setClipboard(this);
	}
}

void WGraphicsPolygonItem::translate(const WWorldPointF& offset)
{
	setPolygon(data()->polygon.translated(offset));
}