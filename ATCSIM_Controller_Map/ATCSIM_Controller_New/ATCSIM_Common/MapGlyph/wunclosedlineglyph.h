#ifndef _WUNCLOSEDLINEGLYPH_H
#define _WUNCLOSEDLINEGLYPH_H

#include "core/wgraphicsitem.h"
#include "core/wgraphicspolylineitem.h"

class WUnclosedLineItemData : public WPolylineItemData
{
public:
	WUnclosedLineItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	void SetLineStyle(Ws::PenStyle style);//用作模拟虚线效果

public:
	WColor m_color;
	std::string m_sName;
};

class WUnclosedLineGlyph : public WGraphicsPolylineItem
{
	RTTI_DECL(WUnclosedLineGlyph)

public:
	typedef WUnclosedLineItemData data_type;

public:
	explicit WUnclosedLineGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;
};



#endif