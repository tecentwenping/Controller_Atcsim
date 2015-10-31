#include <climits>
#include <algorithm>
#include <boost/foreach.hpp>
#include "../wdllexport.h"
#include "wevent.h"
#include "wpainter.h"
#include "wcmdfactory.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"

WGraphicsScene::WGraphicsScene() : _attach_enabled(false)
{
	_layers.insert(new WGraphicsLayer(this, std::numeric_limits<int>::min()));
	_curr_layer = defaultLayer();
}

WGraphicsScene::~WGraphicsScene()
{
	operationStack()->clear(); //清空操作堆栈

	BOOST_FOREACH(WGraphicsLayer* layer, _layers) //删除所有的图层
	{
		delete layer;
	}

	BOOST_FOREACH(WGraphicsLayer* layer, _layers_garbage) //删除图层回收站中的所有图层
	{
		delete layer;
	}
}
//图层重绘
void WGraphicsScene::render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view)
{
	//图层代理的管理功能,得到图层代理
	const WGraphicsLayerProxyManager& layerProxyManager = view->layerProxyManager();

 	BOOST_REVERSE_FOREACH(WGraphicsLayer* layer, _layers)
	{
		if (layerProxyManager.hasProxy(layer)) //图层有代理(说明：代理并不绘制图层，代理只重新定义图层属性）
		{
			WGraphicsLayerProxy layerProxy = layerProxyManager.proxy(layer); //获取图层代理
			bool bAccept = layerProxy.proxy(layer, painter, rect, view);
			if (!bAccept && layer->visible())
			{
				layer->render(painter, rect, view);
			}
		}
		else if (layer->visible()) //图层是否可视
		{
			layer->render(painter, rect, view);
		}
	}
}

WGraphicsItem* WGraphicsScene::itemAt(const WWorldPointF& point) const
{
	//BOOST_FOREACH带来了一种简单而有效的遍历数组的方式
	BOOST_FOREACH(WGraphicsLayer* layer, _layers)
	{
		std::vector<WGraphicsItem*> items = layer->items();
		BOOST_FOREACH(WGraphicsItem* item, items)
		{
			if (item->contains(point))
			{
				return item;
			}
		}
	}

	return 0;
}

std::vector<WGraphicsItem*> WGraphicsScene::items(const WWorldPointF& point) const
{
	std::vector<WGraphicsItem*> v;
	BOOST_FOREACH(WGraphicsLayer* layer, _layers)
	{
		std::vector<WGraphicsItem*> items = layer->items();
		BOOST_FOREACH(WGraphicsItem* item, items)
		{
			if (item->contains(point))
			{
				v.push_back(item);
			}
		}
	}

	return v;
}

std::vector<WGraphicsItem*> WGraphicsScene::items(const WWorldRectF& rect) const
{
	std::vector<WGraphicsItem*> v;
	BOOST_FOREACH(WGraphicsLayer* layer, _layers)
	{
		std::vector<WGraphicsItem*> items = layer->items();
		BOOST_FOREACH(WGraphicsItem* item, items)
		{
			if(rect.contains(item->boundingRect()))
			{
				v.push_back(item);
			}
		}
	}

	return v;
}
//将场景中的当前点的所有图元设置为选中
void WGraphicsScene::updateSelectedItem(const WWorldPointF& point)
{
	//场景中当前选中的图元,容器为set
	_selected_items.clear();
	WGraphicsItem* item = itemAt(point);
	if (item)
	{
		_selected_items.insert(item);
	}
}

void WGraphicsScene::updateSelectedItem(const WWorldRectF& rect)
{
	_selected_items.clear();
	std::vector<WGraphicsItem*> v = items(rect);
	_selected_items.insert(v.begin(), v.end());
}

std::set<WGraphicsItem*> WGraphicsScene::getSelectedItems() const
{
	return _selected_items;
}

WGraphicsItem* WGraphicsScene::getFirstSelectedItem() const
{
	return _selected_items.empty() ? 0 : *_selected_items.begin();
}


bool WGraphicsScene::hasSelectedItem() const
{
	return !_selected_items.empty();
}

bool WGraphicsScene::setSelectedItem(WGraphicsItem* item)
{
	return _selected_items.insert(item).second;
}

bool WGraphicsScene::unsetSelectedItem(WGraphicsItem* item)
{
	return _selected_items.erase(item) > 0;
}

void WGraphicsScene::keyPressEvent(WKeyEvent* event)
{
	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->keyPressEvent(event);
		keyPressEvent(item, event);
	}
}

void WGraphicsScene::keyReleaseEvent(WKeyEvent* event)
{
	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->keyReleaseEvent(event);
		keyReleaseEvent(item, event);//只有当前选中的图元才能响应事件
	}
}

void WGraphicsScene::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	_mouse_pos = event->scenePos();

	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->mouseMoveEvent(event); //只有当前选中的图元才能响应事件
	}
}

void WGraphicsScene::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() & Ws::LeftButton) //左键按下
	{
		_drag_start_pos = event->scenePos();
	}

	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->mousePressEvent(event);//只有当前选中的图元才能响应事件
	}
	
	if (s.empty() || _selected_items.size() < s.size()) //当前没有选中的图元，或选中的图元数量变少
																		 //就把事件传递给当前没有选中的图元
	{
		bool found = false;
		BOOST_FOREACH(WGraphicsLayer* layer, _layers)
		{
			if (layer->visible() && layer->editable()) //图层可视并且可编辑
			{
				std::vector<WGraphicsItem*> v = layer->items();
				BOOST_FOREACH(WGraphicsItem* item, v)
				{
					if (item->isVisible() && item->isSelectable()) //图元支持选中
					{
						item->mousePressEvent(event);
						if (item->isSelected()) //如果有一个图元被选中，就终止事件继续传递
						{
							found = true;
							break;
						}
					}
				}

				if (found)
				{
					break;
				}
			}
		}
	}
}

void WGraphicsScene::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->mouseReleaseEvent(event);//只有当前选中的图元才能响应事件
		mouseReleaseEvent(item, event);
	}
}

void WGraphicsScene::mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event)
{
	//item的操作可能导致_selected_items容器的改变，导致迭代器失效，这里拷贝一份容器来循环
	std::set<WGraphicsItem*> s(_selected_items);
	BOOST_FOREACH(WGraphicsItem* item, s)
	{
		item->mouseDoubleClickEvent(event);//只有当前选中的图元才能响应事件
		mouseDoubleClickEvent(item, event);
	}
}

bool WGraphicsScene::addEventListener(WEventListener* eventListener)
{
	//_elisteners，场景中事件监听者
	return _elisteners.insert(eventListener).second;
}

bool WGraphicsScene::removeEventListener(WEventListener* eventListener)
{
	return _elisteners.erase(eventListener) > 0;
}

void WGraphicsScene::itemChange(const WGraphicsChange& change)
{
	std::set<WEventListener*>::iterator it = _elisteners.begin();
	for (; it != _elisteners.end(); ++it)
	{
		(*it)->itemChange(change);
	}
}

bool WGraphicsScene::addView(WGraphicsView* view)
{
	std::list<WGraphicsView*>::const_iterator cit = std::find(_views.begin(), _views.end(), view);
	if (view && cit == _views.end())
	{
		_views.push_back(view);
		return true;
	}
	return false;
}

bool WGraphicsScene::removeView(WGraphicsView* view)
{
	std::list<WGraphicsView*>::const_iterator cit = std::find(_views.begin(), _views.end(), view);
	if (cit != _views.end())
	{
		_views.erase(cit);
		return true;
	}
	return false;
}

std::list<WGraphicsView*> WGraphicsScene::views() const
{
	return _views;
}
//更新视图
void WGraphicsScene::update(const WWorldRectF& rect)
{
	std::list<WGraphicsView*>::const_iterator cit = _views.begin();
	for (; cit != _views.end(); ++cit)
	{
		(*cit)->updateScene(rect);
	}
}

WOperationStack* WGraphicsScene::operationStack()
{
	return &_opStack;
}

bool WGraphicsScene::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	if (_attach_enabled)
	{
		BOOST_FOREACH(WGraphicsLayer* layer, _layers)
		{
			if (layer->visible())
			{
				std::vector<WGraphicsItem*> items = layer->items();
				BOOST_FOREACH(WGraphicsItem* item, items)
				{
					if (item->isVisible() && item->attachPoint(pos, attachedPos))
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool WGraphicsScene::attachPoint( const WWorldPointF& pos, WWorldPointF* attachedPos, int iLayer, WGraphicsItem** curItem ) const
{
	if (_attach_enabled)
	{
		WGraphicsLayer* l = layer(iLayer);
		if (l)
		{
			std::vector<WGraphicsItem*> items = l->items();
			BOOST_FOREACH(WGraphicsItem* item, items)
			{
				if (item->isVisible() && item->attachPoint(pos, attachedPos))
				{
					if (curItem)
					{
						*curItem = item;
					}
					
					return true;
				}
			}
		}
	}

	return false;
}

WWorldPointF WGraphicsScene::attachedPoint(const WWorldPointF& pos) const
{
	WWorldPointF p;
	return attachPoint(pos, &p) ? p : pos;
}

void WGraphicsScene::removeSelectedItems(bool updating, bool /*opStack*/)
{
	BOOST_FOREACH(WGraphicsItem* item, _selected_items)
	{
		item->layer()->removeItem(item, updating, true);
	}
}

void WGraphicsScene::requestContextMenu(Ws::ContextMenuFlags flags)
{
	std::list<WGraphicsView*>::const_iterator cit = _views.begin();
	for (; cit != _views.end(); ++cit)
	{
		(*cit)->requestContextMenu(flags);
	}
}

void WGraphicsScene::onContextMenu(Ws::ContextMenuFlag flag)
{
	if (flag == Ws::NormalSize)
	{
	}
	else if (flag == Ws::ZoomIn)
	{
	}
	else if (flag == Ws::ZoomOut)
	{
	}
	else if (flag == Ws::Paste)
	{
		paste();
	}
	else
	{
		WGraphicsItem* item = getFirstSelectedItem();
		if (item)
		{
			item->onContextMenu(flag);
		}
	}
}

void WGraphicsScene::setClipboard(WGraphicsItem* item)
{
	clearClipboard();
	_clipboard.insert(item);
}

void WGraphicsScene::setClipboard(const std::vector<WGraphicsItem*>& items)
{
	clearClipboard();
	_clipboard.insert(items.begin(), items.end());
}

void WGraphicsScene::clearClipboard()
{
	_clipboard.clear();
}

std::vector<WGraphicsItem*> WGraphicsScene::clipboard() const
{
	return std::vector<WGraphicsItem*>(_clipboard.begin(), _clipboard.end());
}

bool WGraphicsScene::isClipboardEmpty() const
{
	return _clipboard.empty();
}

WWorldPointF WGraphicsScene::mousePos() const
{
	return _mouse_pos;
}

WWorldPointF WGraphicsScene::dragStartPos() const
{
	return _drag_start_pos;
}

void WGraphicsScene::copyToClipboard()
{
	setClipboard(std::vector<WGraphicsItem*>(_selected_items.begin(), _selected_items.end()));
}

void WGraphicsScene::paste()
{
	static const double DELTA_MAX = 200.0;
	static const double RATE = DELTA_MAX / RAND_MAX;

	WWorldPointF offset(rand() * RATE, rand() * RATE);

	BOOST_FOREACH(WGraphicsItem* item, _clipboard)
	{
		WGraphicsItem* c = item->copy();
		item->layer()->addItem(c);
		c->translate(offset, true);
	}
}

WGraphicsLayer* WGraphicsScene::layer(int id) const
{
	WGraphicsLayer l(const_cast<WGraphicsScene*>(this), id);
	std::set<WGraphicsLayer*, WLayerCmp>::const_iterator i = _layers.find(&l);
	return (i != _layers.end()) ? *i : 0;
}

bool WGraphicsScene::hasLayer(WGraphicsLayer* layer) const
{
	return _layers.find(layer) != _layers.end();
}

std::vector<WGraphicsLayer*> WGraphicsScene::layers() const
{
	return std::vector<WGraphicsLayer*>(_layers.begin(), _layers.end());
}

WGraphicsLayer* WGraphicsScene::addLayer(int id)
{
	WGraphicsLayer* l = layer(id);
	if (!l)
	{
		l = new WGraphicsLayer(this, id);
		_layers.insert(l);
	}
	return l;
}

bool WGraphicsScene::removeLayer(WGraphicsLayer* layer, bool updating)
{
	bool found =  (_layers.erase(layer) > 0);
	if (found)
	{
		_layers_garbage.insert(layer);
		if (updating)
		{
			update();
		}
	}

	if (layer == _curr_layer)
	{
		_curr_layer = defaultLayer();
	}

	return found;
}

void WGraphicsScene::removeAllLayers(bool updating)
{
	WGraphicsLayer* l = defaultLayer();
	_curr_layer = l;

	BOOST_FOREACH(WGraphicsLayer* layer, _layers)
	{
		layer->removeAllItems();
		_layers_garbage.insert(layer);
	}
	_layers_garbage.erase(l);
	_layers.clear();
	_layers.insert(l);

	if (updating)
	{
		update();
	}
}

WGraphicsLayer* WGraphicsScene::defaultLayer() const
{
	return *_layers.begin();
}

bool WGraphicsScene::attachEnabled() const
{
	return _attach_enabled;
}

void WGraphicsScene::setAttachEnabled(bool enable)
{
	_attach_enabled = enable;
}

WGraphicsLayer* WGraphicsScene::currentLayer() const
{
	return _curr_layer;
}

bool WGraphicsScene::setCurrentLayer(WGraphicsLayer* layer)
{
	if (layer)
	{
		if (hasLayer(layer))
		{
			_curr_layer = layer;
		}
		else
		{
			return false;
		}
	}
	else
	{
		_curr_layer = defaultLayer();
	}

	return true;
}

void WGraphicsScene::clearGarbage()
{
	_clipboard.clear();
	operationStack()->clear();

	BOOST_FOREACH(WGraphicsLayer* layer, _layers_garbage)
	{
		delete layer;
	}
	_layers_garbage.clear();

	BOOST_FOREACH(WGraphicsLayer* layer, _layers)
	{
		layer->clearGarbage();
	}
}