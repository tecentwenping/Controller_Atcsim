/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: WFrameCreator.h
  ����  �ߡ�: @hxl
  ����  ����:1.0
  ��������ڡ�:2013/07/05
  ����  ����:  �������ѡ��Ĵ�������

  ����  ����:   
******************************************************************************/
#ifndef _WFrame_Creator_H__
#define _WFrame_Creator_H__

#include "wdefaultcreator.h"

class WGraphicsItem;
class WGraphicsRectItem;
class WGraphicsLayer;

class WFrameCreator : public WDefaultCreator
{
	Q_OBJECT
public:
	explicit WFrameCreator(WGraphicsScene* scene);
	
	virtual void start();
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

signals:
	void filterOtherViews(WGraphicsItem*);
private:
	void clear();

private:
	int _step;
	WGraphicsRectItem* _item;
	WGraphicsLayer* m_layer;
};
#endif // _WFrame_Creator_H__