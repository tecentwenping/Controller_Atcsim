/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsscene.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsScene类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_SCENE_H_
#define _WGRAPHICS_SCENE_H_

#include <set>
#include <list>
#include <map>
#include <vector>
#include "../wdllimport.h"
#include "wworldline.h"
#include "wworldrect.h"
#include "weventlistener.h"
#include "wgraphicslayer.h"
#include "woperationstack.h"

class WGraphicsView;
class WGraphicsItem;

class WPainter;

class WContextMenuEvent;
class WGraphicsSceneDragDropEvent;
class WFocusEvent;
class WGraphicsSceneHoverEvent;
class WInputMethodEvent;
class WKeyEvent;
class WGraphicsSceneMouseEvent;
class WGraphicsSceneWheelEvent;
class WItemChangeEvent;

class WAbstractSceneWriter;
class WGraphicsChange;

//此宏用于将场景中的事件分发给场景中的事件监听器
#define DISPATCH_ITEM_EVENT(memfun, Event)\
void memfun(WGraphicsItem* item, Event* event)\
{\
	std::set<WEventListener*>::iterator it = _elisteners.begin();\
	for (; it != _elisteners.end(); ++it)\
{\
	(*it)->memfun(item, event);\
}\
}\
\

/** 
 \brief                 场景，用于管理图层和图元，负责事件处理等
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsScene
{
public:
	WGraphicsScene();
	~WGraphicsScene();

	/**
	\brief      removeSelectedItems
	\Access    public 
	\param  bool updating
	\param  bool opStack
	\retval     void
	\remark     在场景中移除当前选中的图元
	*/
	void removeSelectedItems(bool updating = false, bool opStack = false);

	/**
	\brief      render
	\Access    public 
	\param  WPainter * painter
	\param  const WWorldRectF & rect
	\param  WGraphicsView * view
	\retval     void
	\remark     图层重绘
	*/
	void render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view);


	/**
	\brief      itemAt
	\Access    public 
	\param  const WWorldPointF & point
	\retval     WGraphicsItem*
	\remark     返回场景中当前点的图元（如果有多个只返回最先遍历到的那个，如果没有则返回0）
	*/
	WGraphicsItem* itemAt(const WWorldPointF& point) const;

	/**
	\brief      items
	\Access    public 
	\param  const WWorldPointF & point
	\retval     std::vector<WGraphicsItem*>
	\remark     返回场景中当前点的所有图元
	*/
	std::vector<WGraphicsItem*> items(const WWorldPointF& point) const;

	/**
	\brief      items
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     std::vector<WGraphicsItem*>
	\remark     返回场景的矩形区域中的所有图元
	*/
	std::vector<WGraphicsItem*> items(const WWorldRectF& rect) const;

	/**
	\brief      updateSelectedItem
	\Access    public 
	\param  const WWorldPointF & point
	\retval     void
	\remark     将场景中的当前点的所有图元设置为选中
	*/
	void updateSelectedItem(const WWorldPointF& point);

	/**
	\brief      updateSelectedItem
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     将场景中的当前矩形中的所有图元设置为选中
	*/
	void updateSelectedItem(const WWorldRectF& rect);
	
	/**
	\brief      getSelectedItems
	\Access    public 
	\retval     std::set<WGraphicsItem*>
	\remark     获取场景中当前选中的所有图元
	*/
	std::set<WGraphicsItem*> getSelectedItems() const;

	/**
	\brief      getFirstSelectedItem
	\Access    public 
	\retval     WGraphicsItem*
	\remark     获取场景中当前选中的第一个图元
	*/
	WGraphicsItem* getFirstSelectedItem() const;

	/**
	\brief      hasSelectedItem
	\Access    public 
	\retval     bool
	\remark     返回场景中是否有选中的图元
	*/
	bool hasSelectedItem() const;

	/**
	\brief      setSelectedItem
	\Access    public 
	\param  WGraphicsItem * item
	\retval     bool 操作是否成功
	\remark     将图元增加到场景的选中队列中去
	*/
	bool setSelectedItem(WGraphicsItem* item);

	/**
	\brief      unsetSelectedItem
	\Access    public 
	\param  WGraphicsItem * item
	\retval     bool 操作是否成功
	\remark    将图元从场景的选中队列中删除 
	*/
	bool unsetSelectedItem(WGraphicsItem* item);

	//以下是场景的鼠标，键盘事件响应
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);
	virtual void keyPressEvent(WKeyEvent* event);
	virtual void keyReleaseEvent(WKeyEvent* event);

	//以下是将场景中的消息传递给场景事件监听者
	//void contextmenuEvent(WGraphicsItem* item, WContextMenuEvent* event);
	DISPATCH_ITEM_EVENT(contextMenuEvent, WContextMenuEvent)

	//void dragEnterEvent(WGraphicesItem* item, WGraphicsSceneDragDropEvent* event);
	DISPATCH_ITEM_EVENT(dragEnterEvent, WGraphicsSceneDragDropEvent)
	DISPATCH_ITEM_EVENT(dragLeaveEvent, WGraphicsSceneDragDropEvent)
	DISPATCH_ITEM_EVENT(dragMoveEvent, WGraphicsSceneDragDropEvent)
	DISPATCH_ITEM_EVENT(dropEvent, WGraphicsSceneDragDropEvent)

	DISPATCH_ITEM_EVENT(focusInEvent, WFocusEvent)
	DISPATCH_ITEM_EVENT(focusOutEvent, WFocusEvent)

	DISPATCH_ITEM_EVENT(hoverEnterEvent, WGraphicsSceneHoverEvent)
	DISPATCH_ITEM_EVENT(hoverLeaveEvent, WGraphicsSceneHoverEvent)
	DISPATCH_ITEM_EVENT(hoverMoveEvent, WGraphicsSceneHoverEvent)

	DISPATCH_ITEM_EVENT(inputMethodEvent, WInputMethodEvent)

	DISPATCH_ITEM_EVENT(keyPressEvent, WKeyEvent)
	DISPATCH_ITEM_EVENT(keyReleaseEvent, WKeyEvent)

	DISPATCH_ITEM_EVENT(mouseMoveEvent, WGraphicsSceneMouseEvent)
	DISPATCH_ITEM_EVENT(mousePressEvent, WGraphicsSceneMouseEvent)
	DISPATCH_ITEM_EVENT(mouseReleaseEvent, WGraphicsSceneMouseEvent)
	DISPATCH_ITEM_EVENT(mouseDoubleClickEvent, WGraphicsSceneMouseEvent)

	DISPATCH_ITEM_EVENT(wheelEvent, WGraphicsSceneWheelEvent)

	/**
	\brief      itemChange
	\Access    public 
	\param  const WGraphicsChange & change
	\retval     void
	\remark     图元发生改变
	*/
	void itemChange(const WGraphicsChange& change);

	/**
	\brief      addEventListener
	\Access    public 
	\param  WEventListener * eventListener
	\retval     bool 返回操作是否成功
	\remark     为场景添加事件监听者
	*/
	bool addEventListener(WEventListener* eventListener);

	/**
	\brief      removeEventListener
	\Access    public 
	\param  WEventListener * eventListener
	\retval     bool 返回操作是否成功
	\remark     将场景监听者从场景中删除
	*/
	bool removeEventListener(WEventListener* eventListener);

	/**
	\brief      addView
	\Access    public 
	\param  WGraphicsView * view
	\retval     bool 操作是否成功
	\remark     为场景增加一个视图
	*/
	bool addView(WGraphicsView* view); //增加一个视窗

	/**
	\brief      removeView
	\Access    public 
	\param  WGraphicsView * view
	\retval     bool 操作是否成功
	\remark     将一个视图从场景中删除
	*/
	bool removeView(WGraphicsView* view); //删除一个视窗

	/**
	\brief      views
	\Access    public 
	\retval     std::list<WGraphicsView*>
	\remark     返回场景的所有的视图
	*/
	std::list<WGraphicsView*> views() const; //所有视窗

	/**
	\brief      update
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     更新视图
	*/
	void update(const WWorldRectF& rect = WWorldRectF());

	/**
	\brief      operationStack
	\Access    public 
	\retval     WOperationStack*
	\remark     返回场景中的操作堆栈
	*/
	WOperationStack* operationStack(); //操作堆栈

	/**
	\brief      attachPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\retval     bool
	\remark     判断某一点pos是否在场景中能吸附场景中的图元
					 如果能，函数返回true，并用输入参数attachPos返回吸附的点
	*/
	bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      attachPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\param  int iLayer
	\retval     bool
	\remark     判断某一点pos是否在场景中指定图层能吸附图元
					 如果能，函数返回true，并用输入参数attachPos返回吸附的点
					 同时返回找到的图元
	*/
	bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos, int iLayer, WGraphicsItem** curItem = NULL) const;

	/**
	\brief      attachedPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\retval     WWorldPointF
	\remark     和上面的函数功能类似
					 如果pos能吸附场景中图元上的点，则函数返回中吸附的点，否则返回传入的点pos
	*/
	WWorldPointF attachedPoint(const WWorldPointF& pos) const;

	//右键菜单
	/**
	\brief      requestContextMenu
	\Access    public 
	\param  Ws::ContextMenuFlags flags
	\retval     void
	\remark     请求右键菜单
	*/
	void requestContextMenu(Ws::ContextMenuFlags flags);

	/**
	\brief      onContextMenu
	\Access    public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     响应右键菜单
	*/
	void onContextMenu(Ws::ContextMenuFlag flag);

	void setClipboard(WGraphicsItem* item); //将指定图元放在剪切板上
	void setClipboard(const std::vector<WGraphicsItem*>& items); //将指定图元放在剪切板上
	void clearClipboard(); //清空剪切板
	std::vector<WGraphicsItem*> clipboard() const; //剪切板中的图元
	bool isClipboardEmpty() const; //剪切板是否为空

	/**
	\brief      mousePos
	\Access    public 
	\retval     WWorldPointF
	\remark     返回鼠标在场景中位置
	*/
	WWorldPointF mousePos() const;

	/**
	\brief      dragStartPos
	\Access    public 
	\retval     WWorldPointF
	\remark     返回拖动事件的起点
	*/
	WWorldPointF dragStartPos() const;

	void copyToClipboard(); //将当前选中项放到剪切板
	void paste(); //将剪切板中的图元粘贴

	WGraphicsLayer* layer(int id) const; //获取某个图层
	WGraphicsLayer* currentLayer() const; //获取当前图层，位于最高层
	WGraphicsLayer* defaultLayer() const; //获取默认图层，位于次高层
	bool hasLayer(WGraphicsLayer* layer) const; //是否有指定图层
	std::vector<WGraphicsLayer*> layers() const; //所有图层
	WGraphicsLayer* addLayer(int id); //增加一个图层
	bool removeLayer(WGraphicsLayer* layer, bool updating = false); //删除一个图层
	void removeAllLayers(bool updating = false); //删除所有图层
	bool setCurrentLayer(WGraphicsLayer* layer); //设置当前图层

	/**
	\brief      attachEnabled
	\Access    public 
	\retval     bool
	\remark     返回场景中是否开启吸附功能
	*/
	bool attachEnabled() const;

	/**
	\brief      setAttachEnabled
	\Access    public 
	\param  bool enable
	\retval     void
	\remark     设置场景是否开启吸附功能
	*/
	void setAttachEnabled(bool enable); //设置编辑能是否开启吸附功能

	void clearGarbage(); //清空回收站

private:
	bool _attach_enabled; //场景中是否开启吸附功能
	std::set<WGraphicsItem*> _selected_items; //场景中当前选中的图元
	std::set<WGraphicsItem*> _clipboard; //场景的图元剪切板，用于支持图元的copy paste cut操作
	std::set<WEventListener*> _elisteners; //场景中事件监听者
	std::list<WGraphicsView*> _views; //场景中的所有视图
	WWorldPointF _mouse_pos; //当前鼠标在场景中的位置
	WWorldPointF _drag_start_pos; //鼠标在场景中的拖动起点
	WOperationStack _opStack; //场景中的操作堆栈，用于支持场景中的redo undo功能
	WGraphicsLayer* _curr_layer; //场景中的当前图层，这个可能在场景中动态绘图会用到
	std::set<WGraphicsLayer*, WLayerCmp> _layers; //场景中所有的图层
	std::set<WGraphicsLayer*> _layers_garbage; //场景回收站（用于保存被删除的图层）
};

#endif