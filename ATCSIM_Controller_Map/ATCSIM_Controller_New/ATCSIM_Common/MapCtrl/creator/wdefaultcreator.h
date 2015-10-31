/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wdefaultcreator.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要包含WDefaultCreator类
  【其  它】:   
******************************************************************************/
#ifndef _WDEFAULT_CREATOR_H_
#define _WDEFAULT_CREATOR_H_

#include "../wdllimport.h"
#include "wabstractcreator.h"

class WGraphicsScene;

/** 
 \brief                 此在WAbstractCreator接口的基础上提供了一个默认的实现（什么事件也不干）
\details   WAbstractCreator只是定义了一个标准接口，它定义了太多的纯虚函数，不适合直接继承使用
			 所以提供了此类，以避免其子类定义很多没用的实现
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WDefaultCreator : public WAbstractCreator
{
public:
	explicit WDefaultCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);
	virtual void keyPressEvent(WKeyEvent* event);
	virtual void keyReleaseEvent(WKeyEvent* event);
	
	WGraphicsScene* scene() const;

private:
	WGraphicsScene* _scene;
};

#endif