/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wcursor.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现WCursor
  【其  它】:   
******************************************************************************/
#ifndef _WCURSOR_H_
#define _WCURSOR_H_

#include "../wdllimport.h"
#include "wenums.h"

/** 
 \brief                 此类主要实现GDI中的光标
\details  目前只支持只支持最基本的光标，不支持自定义图片的光标 
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WCursor
{
public:
	explicit WCursor(Ws::CursorShape shape = Ws::ArrowCursor);

	Ws::CursorShape shape() const;
	void setShape(Ws::CursorShape shape);

private:
	Ws::CursorShape _shape;
};

#endif