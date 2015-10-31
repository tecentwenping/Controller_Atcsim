#include <boost/foreach.hpp>
#include "../wdllexport.h"
#include "wcmdfactory.h"
#include "wgraphicsview.h"
#include "wgraphicslayer.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicsarcitem.h"
#include "wgraphicslineitem.h"
#include "wgraphicsrectitem.h"
#include "wgraphicstextitem.h"
#include "wgraphicspointitem.h"
#include "wgraphicsellipseitem.h"
#include "wgraphicsrichtextitem.h"
#include "wgraphicspolylineitem.h"
#include "wgraphicspolygonitem.h"

#include "wgraphicsitemfilter.h"

WGraphicsLayer::WGraphicsLayer(WGraphicsScene* scene, int layer) : _scene(scene), _layer(layer),
	_visible(true), _editable(false)
{
}

WGraphicsLayer::~WGraphicsLayer()
{
	BOOST_FOREACH(WGraphicsItem* item, _items)
	{
		item->destroy();
	}

	BOOST_FOREACH(WGraphicsItem* item, _items_garbage)
	{
		item->destroy();
	}
}

int WGraphicsLayer::layer() const
{
	return _layer;
}

bool WGraphicsLayer::visible() const
{
	return _visible;
}

bool WGraphicsLayer::editable() const
{
	return _editable;
}

WGraphicsScene* WGraphicsLayer::scene() const
{
	return _scene;
}

void WGraphicsLayer::setLayer(int layer)
{
	_layer = layer;
}

void WGraphicsLayer::setVisible(bool visible)
{
	_visible = visible;
	_scene->update();
}

void WGraphicsLayer::setEditable(bool editable)
{
	_editable = editable;
}

/**
\brief      render
\Access    public 
\param  WPainter * painter 绘图设备上下文
\param  const WWorldRectF & rect 重绘的区域
\param  WGraphicsView * view 导致此次重绘的视图
\retval     void
\remark     
*/
void WGraphicsLayer::render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view) const
{
	/*const WGraphicsItemProxyManager& itemProxyManager = view->itemProxyManager();

	BOOST_FOREACH(WGraphicsItem* item, _items)
	{
		if (item->isVisible())
		{
			if (itemProxyManager.hasProxy(item))
			{
				WGraphicsItemProxy itemProxy = itemProxyManager.proxy(item);
				if (rect.intersects(itemProxy.boundingRect(item)))
				{
					itemProxy.paint(item, painter);
				}
			}
			else if (rect.intersects(item->boundingRect()))
			{
				item->paint(painter);
			}
		}  
	}*/

	const WGraphicsItemProxyManager& itemProxyManager = view->itemProxyManager();

	BOOST_FOREACH(WGraphicsItem* item, _items)
	{
		if (itemProxyManager.hasProxy(item)) //图层有代理(说明：代理并不绘制图层，代理只重新定义图层属性）
		{
			WGraphicsItemProxy itemproxy = itemProxyManager.proxy(item); //获取图层代理
			bool bAccept = itemproxy.proxy(item, painter, rect, view);
			if (!bAccept && item->isVisible() &&
				rect.intersects(item->boundingRect()))
			{
				item->paint(painter);
			}
		}
		else if (item->isVisible() && rect.intersects(item->boundingRect())) //图元可视
		{
			item->paint(painter);
		}
	}
}

bool WGraphicsLayer::hasItem(WGraphicsItem* item) const
{
	return _items.find(item) != _items.end();
}

std::vector<WGraphicsItem*> WGraphicsLayer::items() const
{
	return std::vector<WGraphicsItem*>(_items.begin(), _items.end());
}

WGraphicsItem* WGraphicsLayer::addItem(WGraphicsItem* item, bool updating)
{
	return addItemPrivate(item, updating);
}

WGraphicsItem* WGraphicsLayer::addItem(const WGraphicsItem& item, bool updating)
{
	return addItemPrivate(item.copy(), updating);
}

/**
\brief      removeItem
\Access    public 
\param  WGraphicsItem * item 图元指针
\param  bool updating 是否立即进行一次刷新（如果在很短时间内多次删除图元，建议将此值设为false）
\param  bool opStack 是否将删除操作进栈，以后可以撤消删除
\retval     bool
\remark     
*/
bool WGraphicsLayer::removeItem(WGraphicsItem* item, bool updating, bool opStack)
{
	if (_items.erase(item) > 0)
	{
		_items_garbage.insert(item);
		if (updating)
		{
			scene()->update(item->boundingRect());
		}
		if (opStack)
		{
			scene()->operationStack()->push(WCmdFactory::create(&WGraphicsLayer::removeItem, this, item, updating, false),
				WCmdFactory::create(&WGraphicsLayer::recoverItem, this, item, updating));
		}
		return true;
	}
	return false;
}

void WGraphicsLayer::removeAllItems(bool updating)
{
	_items_garbage.insert(_items.begin(), _items.end());
	_items.clear();
	if (updating)
	{
		scene()->update();
	}
}

WGraphicsLineItem* WGraphicsLayer::addLine(const WWorldLineF& line, const WPen& pen, bool updating)
{
	return addItemPrivate(new WGraphicsLineItem(line, pen), updating);
}

WGraphicsRectItem* WGraphicsLayer::addRect(const WWorldRectF& rect, double angle, const WPen& pen, const WBrush& brush, bool updating)
{
	return addItemPrivate(new WGraphicsRectItem(rect, brush, pen, angle), updating);
}

WGraphicsEllipseItem* WGraphicsLayer::addEllipse(const WWorldRectF& rect, const WPen& pen, const WBrush& brush, bool updating)
{
	return addItemPrivate(new WGraphicsEllipseItem(rect, brush, pen), updating);
}

WGraphicsPolygonItem* WGraphicsLayer::addPolygon(const WWorldPolygonF& polygon, const WPen& pen, const WBrush& brush, bool updating)
{
	return addItemPrivate(new WGraphicsPolygonItem(polygon, brush, pen), updating);
}

WGraphicsArcItem* WGraphicsLayer::addArc(const WWorldRectF& rect, double startAngle, double endAngle, const WPen& pen, bool updating)
{
	return addItemPrivate(new WGraphicsArcItem(rect, startAngle, endAngle, pen), updating);
}

WGraphicsTextItem* WGraphicsLayer::addText(const WWorldPointF& pos, const std::string& text, bool updating)
{
	return addItemPrivate(new WGraphicsTextItem(pos, text), updating);
}

WGraphicsRichTextItem* WGraphicsLayer::addRichText(const WWorldPointF& pos, const std::string& text, bool updating)
{
	return addItemPrivate(new WGraphicsRichTextItem(pos, text), updating);
}

WGraphicsPointItem* WGraphicsLayer::addPoint(const WWorldPointF& pos, const WPen& pen, bool updating)
{
	return addItemPrivate(new WGraphicsPointItem(pos, pen), updating);
}

WGraphicsPolylineItem* WGraphicsLayer::addPolyline(const WWorldPolylineF& polyline, const WPen& pen, bool updating)
{
	return addItemPrivate(new WGraphicsPolylineItem(polyline, pen), updating);
}

template<class Item>
Item* WGraphicsLayer::addItemPrivate(Item* item, bool updating)
{
	item->setLayer(this);
	_items.insert(item);
	if (updating)
	{
		scene()->update(item->boundingRect());
	}

	return item;
}

void WGraphicsLayer::recoverItem(WGraphicsItem* item, bool updating)
{
	if (_items_garbage.erase(item) > 0)
	{
		_items.insert(item);
		if (updating)
		{
			scene()->update(item->boundingRect());
		}
	}
}

void WGraphicsLayer::clearGarbage()
{
	BOOST_FOREACH(WGraphicsItem* item, _items_garbage)
	{
		item->destroy();
	}
	_items_garbage.clear();
}