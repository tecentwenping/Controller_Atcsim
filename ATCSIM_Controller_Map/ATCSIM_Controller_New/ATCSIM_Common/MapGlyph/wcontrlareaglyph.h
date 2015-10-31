#ifndef _WCONTROLAREAGLYPH_H
#define _WCONTROLAREAGLYPH_H

#include "core/wgraphicsrectitem.h"
#include "core/wgraphicspolygonitem.h"

class WControlAreaGlyph;

class WControlAreaItemData:public WPolygonItemData
{
public:
	WControlAreaItemData();
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;
public:

};


//绘制管制区域图元
class WControlAreaGlyph: public WGraphicsItem
{
	RTTI_DECL(WControlAreaGlyph)

public:
	typedef WControlAreaItemData data_type;

public:
	explicit WControlAreaGlyph(data_type *d = 0);

public:
	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

public:
	data_type* data();
	const data_type* data() const;
};


#endif