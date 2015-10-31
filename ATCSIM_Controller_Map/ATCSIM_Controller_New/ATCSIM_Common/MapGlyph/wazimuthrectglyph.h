#ifndef _WAZIMUTH_RECT_GLYPH_H_
#define _WAZIMUTH_RECT_GLYPH_H_

#include "wgraphicsitem.h"

class WAzimuthRectItemData : public WItemData
{
public:
	WAzimuthRectItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WPen m_pen;
};

//·½Î»È¦
class WAzimuthRectGlyph : public WGraphicsItem
{
	RTTI_DECL(WAzimuthRectGlyph)

public:
	typedef WAzimuthRectItemData data_type;

public:
	explicit WAzimuthRectGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif