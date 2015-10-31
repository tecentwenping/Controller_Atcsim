/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wpainterproxy.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WPainterProxy类
  【其  它】:   
******************************************************************************/
#ifndef _WPAINTER_PROXY_H_
#define _WPAINTER_PROXY_H_

#include "../wdllimport.h"

class WPainter;

//WPainterProxy is a helper class,
//it helps WPainter users to automatically save and restore paint objects
//it saves paint objects in ctor and restore them is detor
//the following example demonstrates basic usage of WPainterProxy
/*
void paintEvent(WPainter* painter)
{
	WPainterProxy proxy(painter); //WPainterProxy ctor, save paint objects in ctor
	painter->setPen(...); //pen has changed
	{
		WPainterProxy proxy_inner(painter); //save paint objects in ctor
		painter.setWorldTransform(...); //world transform has changed
	} //WPainterProxy detor, restore paint objects, that is, world transform has restored, now only pen has changed
	painter->setBrush(...); //brush has changed
} //WPainterProxy detor, restore paint objects, that is, nothing has changed
*/

/** 
 \brief                 此类主要为WPainter的操作提供便利
\details   此类会在构造的时候自动保存WPainter的状态，然后在析构的时候自动恢复WPainter的状态，
			WPainter使用者一般都需要在使用之前保存WPainter的状态，在WPainter使用完成之后恢复WPainter的
			状态，这样操作有时会很麻烦，容易错误，比如在开始的时候保存WPainter的状态后，然后对WPainter进行
			一系列的操作，使用完WPainter之后忘记了恢复WPainter到原来的状态，这样之后，其它的对象使用同一个
			WPainter对象时会表现出显示不正常的情况，尤其是WPainter进行矩阵变换没有及时恢复，更为致命。
			为了解决这个容易被遗忘的问题，在使用WPainter之前创建一个WPainterProxy对象即可。

 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WPainterProxy
{
public:
	/**
	\brief      WPainterProxy
	\Access    public 
	\param  WPainter * painter
	\retval     
	\remark    保存WPainter的状态 
	*/
	explicit WPainterProxy(WPainter* painter);

	/**
	\brief      ~WPainterProxy
	\Access    public 
	\retval     
	\remark    恢复WPainter的状态 
	*/
	~WPainterProxy();

	/**
	\brief      painter
	\Access    public 
	\retval     WPainter*
	\remark    获取WPainter对象 
	*/
	WPainter* painter() const;

private:
	WPainter* _painter;
};

#endif