/******************************************************************************
版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
【文件名】: wrandompointglyph.h
【作  者】: 杨与光
【版  本】:1.0
【完成日期】:2013/10/9
【描  述】:  此文件主要用于随机作图点的绘制
【其  它】:   
******************************************************************************/

#ifndef _WRANDOMPOINTGLYPH_H
#define _WRANDOMPOINTGLYPH_H

#include "wpen.h"
#include "wgraphicsitem.h"
#include "wbrush.h"
#include "EnumVarible.h"
#define TYPE_RANDOM_POINT_ITEM 11


class WRandomPointItemData : public WItemData
{
public:
	WRandomPointItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	ENUM_RANDOMPOINT_TYPE m_eRandomPointType;
	WPointF m_pos;
	WPen m_pen;
	WBrush m_brush;
};

class WRandomPointGlyph : public WGraphicsItem
{
	RTTI_DECL(WRandomPointGlyph)

public:
	typedef WRandomPointItemData data_type;

	enum { Type = TYPE_RANDOM_POINT_ITEM };
	virtual int type() const;

public:
	explicit WRandomPointGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;
};
#endif