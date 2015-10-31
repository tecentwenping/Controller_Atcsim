/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsellipseitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/28
  【描  述】:  此文件主要包含WGraphicsEllipseItem
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_ELLIPSE_ITEM_H_
#define _WGRAPHICS_ELLIPSE_ITEM_H_

#include "../wdllimport.h"
#include "wgraphicsrectitem.h"

/** 
 \brief                 椭圆图元
\details   
 \author    陈龙
\date      2013/05/28
*/
class MAPAPI WGraphicsEllipseItem : public WGraphicsRectItem
{
	RTTI_DECL(WGraphicsEllipseItem)

public:
	explicit WGraphicsEllipseItem(const WWorldRectF& r, const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0);
	explicit WGraphicsEllipseItem(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;

	enum { Type = TYPE_ELLIPSE_ITEM };
	virtual int type() const;

	virtual WGraphicsEllipseItem* copy() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;
};

#endif