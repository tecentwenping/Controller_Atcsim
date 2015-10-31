/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: witemshareprivate.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含了几个全局函数，这些函数主要作用是辅助图元完成相应的功能
  【其  它】:   
******************************************************************************/
#ifndef _WITEM_SHARE_PRIVATE_H_
#define _WITEM_SHARE_PRIVATE_H_

#include "../wdllimport.h"
#include "wworldline.h"
#include "wworldrect.h"

typedef const WWorldPointF& WPF;

/**
\brief      attachLine
\Access    public 
\param  const WWorldLineF & line
\param  double attachDistance
\param  const WWorldPointF & pos
\param  WWorldPointF * attachedPos
\retval     bool MAPAPI
\remark     判断一个点(pos)是否能够吸附一条直线(line)
				判断是否吸附的标准是点(pos)到直线(line)的距离是否小于一个给定的域值(attachDistance)，
				如果是吸附的，则函数返回true，并由函数参数attachedPos返回直线上的吸附点
*/
bool MAPAPI attachLine(const WWorldLineF& line, double attachDistance, const WWorldPointF& pos, WWorldPointF* attachedPos);

//以下几个重载的函数用于获取n(2, 3, 4, 5, 6)个点形成的折线的边界矩形区域
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5, WPF p6);

#endif