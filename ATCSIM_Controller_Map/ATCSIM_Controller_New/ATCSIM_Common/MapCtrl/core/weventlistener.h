/** 
 \brief                 此文件主要实现了场景中事件监听功能 WEventListener
\details   
 \author    陈龙
\date      2013/05/23
*/
#ifndef _WEVENT_LISTENER_H_
#define _WEVENT_LISTENER_H_

#include "../wdllimport.h"
#include "weventoption.h"
#include "wgraphicsitem.h"

class WKeyEvent;
class WFocusEvent;
class WEventOption;
class WGraphicsItem;
class WGraphicsChange;
class WInputMethodEvent;
class WContextMenuEvent;
class WGraphicsSceneHoverEvent;
class WGraphicsSceneWheelEvent;
class WGraphicsSceneMouseEvent;
class WGraphicsSceneDragDropEvent;

/** 
 \brief                 此类主要实现了场景中事件监听功能
\details   如果你想知道围城（场景）中发生的事情（事件），请继承之
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WEventListener
{
public:

	/** 
	\brief                 设置，获取场景事件过滤器（目前没有用到）
	\details   
	\author    陈龙
	\date      2013/05/23
	*/
	WEventOption& eventOption();
	const WEventOption& eventOption() const;
	void setEventOption(const WEventOption& eventOption);

	/** 
	\brief                 这些事件目前没有用到
	\details   
	\author    陈龙
	\date      2013/05/23
	*/
	virtual void contextMenuEvent(WGraphicsItem* item, WContextMenuEvent* event);
	virtual void dragEnterEvent(WGraphicsItem* item, WGraphicsSceneDragDropEvent* event);
	virtual void dragLeaveEvent(WGraphicsItem* item, WGraphicsSceneDragDropEvent* event);
	virtual void dragMoveEvent(WGraphicsItem* item, WGraphicsSceneDragDropEvent* event);
	virtual void dropEvent(WGraphicsItem* item, WGraphicsSceneDragDropEvent* event);

	virtual void focusInEvent(WGraphicsItem* item, WFocusEvent* event);
	virtual void focusOutEvent(WGraphicsItem* item, WFocusEvent* event);
	
	virtual void hoverEnterEvent(WGraphicsItem* item, WGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(WGraphicsItem* item, WGraphicsSceneHoverEvent* event);
	virtual void hoverMoveEvent(WGraphicsItem* item, WGraphicsSceneHoverEvent* event);

	virtual void inputMethodEvent(WGraphicsItem* item, WInputMethodEvent* event);
	
	/** 
	\brief                 场景中图元响应下面这些事件的时候，用自动回调下面这些函数
	\details   
	\author    陈龙
	\date      2013/05/23
	*/
	virtual void keyPressEvent(WGraphicsItem* item, WKeyEvent* event);
	virtual void keyReleaseEvent(WGraphicsItem* item, WKeyEvent* event);

	virtual void mouseMoveEvent(WGraphicsItem* item, WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsItem* item, WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsItem* item, WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsItem* item, WGraphicsSceneMouseEvent* event);
	
	virtual void wheelEvent(WGraphicsItem* item, WGraphicsSceneWheelEvent* event);

	/**
	\brief      itemChange
	\Access    virtual public 
	\param  const WGraphicsChange & change
	\retval     void
	\remark    这是一个经典事件，每当场景，图元发生改变时，此函数被回调
					如场景图元删除，图元选中，场景剪切板数据发生改变
	*/
	virtual void itemChange(const WGraphicsChange& change);

private:
	WEventOption _eventOption; //场景事件过滤器（目前没有用到）
};

#endif