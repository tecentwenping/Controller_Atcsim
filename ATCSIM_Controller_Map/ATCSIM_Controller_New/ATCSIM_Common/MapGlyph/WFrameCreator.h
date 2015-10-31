/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: WFrameCreator.h
  【作  者】: @hxl
  【版  本】:1.0
  【完成日期】:2013/07/05
  【描  述】:  画鼠标拖选框的创建者类

  【其  它】:   
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