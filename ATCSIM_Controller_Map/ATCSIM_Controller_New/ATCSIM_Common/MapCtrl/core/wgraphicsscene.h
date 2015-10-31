/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsscene.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsScene��
  ����  ����:   
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

//�˺����ڽ������е��¼��ַ��������е��¼�������
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
 \brief                 ���������ڹ���ͼ���ͼԪ�������¼������
\details   
 \author    ����
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
	\remark     �ڳ������Ƴ���ǰѡ�е�ͼԪ
	*/
	void removeSelectedItems(bool updating = false, bool opStack = false);

	/**
	\brief      render
	\Access    public 
	\param  WPainter * painter
	\param  const WWorldRectF & rect
	\param  WGraphicsView * view
	\retval     void
	\remark     ͼ���ػ�
	*/
	void render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view);


	/**
	\brief      itemAt
	\Access    public 
	\param  const WWorldPointF & point
	\retval     WGraphicsItem*
	\remark     ���س����е�ǰ���ͼԪ������ж��ֻ�������ȱ��������Ǹ������û���򷵻�0��
	*/
	WGraphicsItem* itemAt(const WWorldPointF& point) const;

	/**
	\brief      items
	\Access    public 
	\param  const WWorldPointF & point
	\retval     std::vector<WGraphicsItem*>
	\remark     ���س����е�ǰ�������ͼԪ
	*/
	std::vector<WGraphicsItem*> items(const WWorldPointF& point) const;

	/**
	\brief      items
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     std::vector<WGraphicsItem*>
	\remark     ���س����ľ��������е�����ͼԪ
	*/
	std::vector<WGraphicsItem*> items(const WWorldRectF& rect) const;

	/**
	\brief      updateSelectedItem
	\Access    public 
	\param  const WWorldPointF & point
	\retval     void
	\remark     �������еĵ�ǰ�������ͼԪ����Ϊѡ��
	*/
	void updateSelectedItem(const WWorldPointF& point);

	/**
	\brief      updateSelectedItem
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     �������еĵ�ǰ�����е�����ͼԪ����Ϊѡ��
	*/
	void updateSelectedItem(const WWorldRectF& rect);
	
	/**
	\brief      getSelectedItems
	\Access    public 
	\retval     std::set<WGraphicsItem*>
	\remark     ��ȡ�����е�ǰѡ�е�����ͼԪ
	*/
	std::set<WGraphicsItem*> getSelectedItems() const;

	/**
	\brief      getFirstSelectedItem
	\Access    public 
	\retval     WGraphicsItem*
	\remark     ��ȡ�����е�ǰѡ�еĵ�һ��ͼԪ
	*/
	WGraphicsItem* getFirstSelectedItem() const;

	/**
	\brief      hasSelectedItem
	\Access    public 
	\retval     bool
	\remark     ���س������Ƿ���ѡ�е�ͼԪ
	*/
	bool hasSelectedItem() const;

	/**
	\brief      setSelectedItem
	\Access    public 
	\param  WGraphicsItem * item
	\retval     bool �����Ƿ�ɹ�
	\remark     ��ͼԪ���ӵ�������ѡ�ж�����ȥ
	*/
	bool setSelectedItem(WGraphicsItem* item);

	/**
	\brief      unsetSelectedItem
	\Access    public 
	\param  WGraphicsItem * item
	\retval     bool �����Ƿ�ɹ�
	\remark    ��ͼԪ�ӳ�����ѡ�ж�����ɾ�� 
	*/
	bool unsetSelectedItem(WGraphicsItem* item);

	//�����ǳ�������꣬�����¼���Ӧ
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);
	virtual void keyPressEvent(WKeyEvent* event);
	virtual void keyReleaseEvent(WKeyEvent* event);

	//�����ǽ������е���Ϣ���ݸ������¼�������
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
	\remark     ͼԪ�����ı�
	*/
	void itemChange(const WGraphicsChange& change);

	/**
	\brief      addEventListener
	\Access    public 
	\param  WEventListener * eventListener
	\retval     bool ���ز����Ƿ�ɹ�
	\remark     Ϊ��������¼�������
	*/
	bool addEventListener(WEventListener* eventListener);

	/**
	\brief      removeEventListener
	\Access    public 
	\param  WEventListener * eventListener
	\retval     bool ���ز����Ƿ�ɹ�
	\remark     �����������ߴӳ�����ɾ��
	*/
	bool removeEventListener(WEventListener* eventListener);

	/**
	\brief      addView
	\Access    public 
	\param  WGraphicsView * view
	\retval     bool �����Ƿ�ɹ�
	\remark     Ϊ��������һ����ͼ
	*/
	bool addView(WGraphicsView* view); //����һ���Ӵ�

	/**
	\brief      removeView
	\Access    public 
	\param  WGraphicsView * view
	\retval     bool �����Ƿ�ɹ�
	\remark     ��һ����ͼ�ӳ�����ɾ��
	*/
	bool removeView(WGraphicsView* view); //ɾ��һ���Ӵ�

	/**
	\brief      views
	\Access    public 
	\retval     std::list<WGraphicsView*>
	\remark     ���س��������е���ͼ
	*/
	std::list<WGraphicsView*> views() const; //�����Ӵ�

	/**
	\brief      update
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     ������ͼ
	*/
	void update(const WWorldRectF& rect = WWorldRectF());

	/**
	\brief      operationStack
	\Access    public 
	\retval     WOperationStack*
	\remark     ���س����еĲ�����ջ
	*/
	WOperationStack* operationStack(); //������ջ

	/**
	\brief      attachPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\retval     bool
	\remark     �ж�ĳһ��pos�Ƿ��ڳ����������������е�ͼԪ
					 ����ܣ���������true�������������attachPos���������ĵ�
	*/
	bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      attachPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\param  int iLayer
	\retval     bool
	\remark     �ж�ĳһ��pos�Ƿ��ڳ�����ָ��ͼ��������ͼԪ
					 ����ܣ���������true�������������attachPos���������ĵ�
					 ͬʱ�����ҵ���ͼԪ
	*/
	bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos, int iLayer, WGraphicsItem** curItem = NULL) const;

	/**
	\brief      attachedPoint
	\Access    public 
	\param  const WWorldPointF & pos
	\retval     WWorldPointF
	\remark     ������ĺ�����������
					 ���pos������������ͼԪ�ϵĵ㣬���������������ĵ㣬���򷵻ش���ĵ�pos
	*/
	WWorldPointF attachedPoint(const WWorldPointF& pos) const;

	//�Ҽ��˵�
	/**
	\brief      requestContextMenu
	\Access    public 
	\param  Ws::ContextMenuFlags flags
	\retval     void
	\remark     �����Ҽ��˵�
	*/
	void requestContextMenu(Ws::ContextMenuFlags flags);

	/**
	\brief      onContextMenu
	\Access    public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     ��Ӧ�Ҽ��˵�
	*/
	void onContextMenu(Ws::ContextMenuFlag flag);

	void setClipboard(WGraphicsItem* item); //��ָ��ͼԪ���ڼ��а���
	void setClipboard(const std::vector<WGraphicsItem*>& items); //��ָ��ͼԪ���ڼ��а���
	void clearClipboard(); //��ռ��а�
	std::vector<WGraphicsItem*> clipboard() const; //���а��е�ͼԪ
	bool isClipboardEmpty() const; //���а��Ƿ�Ϊ��

	/**
	\brief      mousePos
	\Access    public 
	\retval     WWorldPointF
	\remark     ��������ڳ�����λ��
	*/
	WWorldPointF mousePos() const;

	/**
	\brief      dragStartPos
	\Access    public 
	\retval     WWorldPointF
	\remark     �����϶��¼������
	*/
	WWorldPointF dragStartPos() const;

	void copyToClipboard(); //����ǰѡ����ŵ����а�
	void paste(); //�����а��е�ͼԪճ��

	WGraphicsLayer* layer(int id) const; //��ȡĳ��ͼ��
	WGraphicsLayer* currentLayer() const; //��ȡ��ǰͼ�㣬λ����߲�
	WGraphicsLayer* defaultLayer() const; //��ȡĬ��ͼ�㣬λ�ڴθ߲�
	bool hasLayer(WGraphicsLayer* layer) const; //�Ƿ���ָ��ͼ��
	std::vector<WGraphicsLayer*> layers() const; //����ͼ��
	WGraphicsLayer* addLayer(int id); //����һ��ͼ��
	bool removeLayer(WGraphicsLayer* layer, bool updating = false); //ɾ��һ��ͼ��
	void removeAllLayers(bool updating = false); //ɾ������ͼ��
	bool setCurrentLayer(WGraphicsLayer* layer); //���õ�ǰͼ��

	/**
	\brief      attachEnabled
	\Access    public 
	\retval     bool
	\remark     ���س������Ƿ�����������
	*/
	bool attachEnabled() const;

	/**
	\brief      setAttachEnabled
	\Access    public 
	\param  bool enable
	\retval     void
	\remark     ���ó����Ƿ�����������
	*/
	void setAttachEnabled(bool enable); //���ñ༭���Ƿ�����������

	void clearGarbage(); //��ջ���վ

private:
	bool _attach_enabled; //�������Ƿ�����������
	std::set<WGraphicsItem*> _selected_items; //�����е�ǰѡ�е�ͼԪ
	std::set<WGraphicsItem*> _clipboard; //������ͼԪ���а壬����֧��ͼԪ��copy paste cut����
	std::set<WEventListener*> _elisteners; //�������¼�������
	std::list<WGraphicsView*> _views; //�����е�������ͼ
	WWorldPointF _mouse_pos; //��ǰ����ڳ����е�λ��
	WWorldPointF _drag_start_pos; //����ڳ����е��϶����
	WOperationStack _opStack; //�����еĲ�����ջ������֧�ֳ����е�redo undo����
	WGraphicsLayer* _curr_layer; //�����еĵ�ǰͼ�㣬��������ڳ����ж�̬��ͼ���õ�
	std::set<WGraphicsLayer*, WLayerCmp> _layers; //���������е�ͼ��
	std::set<WGraphicsLayer*> _layers_garbage; //��������վ�����ڱ��汻ɾ����ͼ�㣩
};

#endif