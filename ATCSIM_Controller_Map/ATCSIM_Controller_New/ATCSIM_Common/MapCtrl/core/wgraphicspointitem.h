/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicspointitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsPointItem类和其相对应的数据类WPointItemData
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_POINT_ITEM_H
#define _WGRAPHICS_POINT_ITEM_H

#include "../wdllimport.h"
#include "wpen.h"
#include "wgraphicsitem.h"
#include "wworldpolygon.h"

class WPainter;

/** 
 \brief                 WGraphicsPointItem类的核心数据类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WPointItemData : public WItemData
{
public:
	explicit WPointItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const WPen& pn = WPen()) : WItemData(typ), pos(p), pen(pn) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WPointItemData* copy() const { return new WPointItemData(*this); }

	WWorldPointF pos; //点的位置
	WPen pen; //绘制点的画笔
};

/** 
 \brief                 点图元
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsPointItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsPointItem)

public:
	typedef WPointItemData data_type;

public:
	explicit WGraphicsPointItem(const WWorldPointF& p, const WPen& pn = WPen());
	explicit WGraphicsPointItem(data_type* d = 0);

	WWorldPointF pos() const;
	WPen pen() const;

	void setPos(const WWorldPointF& pos, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsPointItem* copy() const;

	enum { Type = TYPE_POINT_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	virtual void translate(const WWorldPointF& offset);

private:
	void updateCp();

private:
	int _select_flag; //选中标识
	WWorldPolygonF _cp; //点对应的三角形的三个点
	bool _dragging; //是否在拖动
};


#endif