/********************************************************************
版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司	
【文件名】:  wcloudglyph.h
【作  者】:  @yyg
【版  本】:  1.0
【完成日期】:2013/06/25	
【描  述】:  

【其  它】:   
*********************************************************************/
#ifndef WCLOUDGLYPH_H
#define WCLOUDGLYPH_H

#include "core/wgraphicsitem.h"
#include "core/wgraphicspolygonitem.h"

class WCloudGlyph;

class WCloudGlyphItemData :public WPolygonItemData
{
public:
	WCloudGlyphItemData();
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WColor m_color;
};

class WCloudGlyph :public WGraphicsPolygonItem
{
	RTTI_DECL(WCloudGlyph)

public:
	typedef WCloudGlyphItemData data_type;

public:
	explicit WCloudGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;
};
#endif