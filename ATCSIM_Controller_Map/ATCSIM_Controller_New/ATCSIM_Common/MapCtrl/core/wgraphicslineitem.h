/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicslineitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsLineItem类和其核心数据WLineItemData类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_LINE_ITEM_H
#define _WGRAPHICS_LINE_ITEM_H

#include "../wdllimport.h"
#include "wpen.h"
#include "wworldline.h"
#include "wgraphicsitem.h"

class WPainter;

/** 
 \brief                 WGraphicsLineItem类的核心数据
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WLineItemData : public WItemData
{
public:
	explicit WLineItemData(int typ = 0, const WWorldLineF& l = WWorldLineF(), const WPen& p = WPen()) : WItemData(typ), line(l), pen(p) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WLineItemData* copy() const { return new WLineItemData(*this); }

	WWorldLineF line; //直线
	WPen pen; //画笔
};

/** 
 \brief                 直线图元类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsLineItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsLineItem)

public:
	typedef WLineItemData data_type;

public:
	explicit WGraphicsLineItem(const WWorldLineF& l, const WPen& p = WPen());
	explicit WGraphicsLineItem(data_type* d = 0);

	WWorldLineF line() const;
	WPen pen() const;

	void setLine(const WWorldLineF& line, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	virtual void keyPressEvent(WKeyEvent* event);

	data_type* data();
	const data_type* data() const;

	void showArraw(bool show = true, bool update = false);
	bool isArrawShow() const;

	virtual WGraphicsLineItem* copy() const;

	enum { Type = TYPE_LINE_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	virtual void translate(const WWorldPointF& offset);

private:
	int _select_flag; //选中标识
	bool _show_arraw; //是否显示直线（矢量）的箭头
	bool _dragging; //直线是否在拖动
};

#endif