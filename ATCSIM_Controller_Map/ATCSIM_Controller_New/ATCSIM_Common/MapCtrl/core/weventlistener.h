/** 
 \brief                 ���ļ���Ҫʵ���˳������¼��������� WEventListener
\details   
 \author    ����
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
 \brief                 ������Ҫʵ���˳������¼���������
\details   �������֪��Χ�ǣ��������з��������飨�¼�������̳�֮
 \author    ����
\date      2013/05/23
*/
class MAPAPI WEventListener
{
public:

	/** 
	\brief                 ���ã���ȡ�����¼���������Ŀǰû���õ���
	\details   
	\author    ����
	\date      2013/05/23
	*/
	WEventOption& eventOption();
	const WEventOption& eventOption() const;
	void setEventOption(const WEventOption& eventOption);

	/** 
	\brief                 ��Щ�¼�Ŀǰû���õ�
	\details   
	\author    ����
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
	\brief                 ������ͼԪ��Ӧ������Щ�¼���ʱ�����Զ��ص�������Щ����
	\details   
	\author    ����
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
	\remark    ����һ�������¼���ÿ��������ͼԪ�����ı�ʱ���˺������ص�
					�糡��ͼԪɾ����ͼԪѡ�У��������а����ݷ����ı�
	*/
	virtual void itemChange(const WGraphicsChange& change);

private:
	WEventOption _eventOption; //�����¼���������Ŀǰû���õ���
};

#endif