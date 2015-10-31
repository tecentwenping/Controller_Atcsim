#ifndef _WAZIMUTH_CIRCLE_GLYPH_H_
#define _WAZIMUTH_CIRCLE_GLYPH_H_

#include "wgraphicsitem.h"

class WAzimuthCircleItemData : public WItemData
{
public:
	WAzimuthCircleItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WPen m_pen;
};

//·½Î»‡ü
class WAzimuthCircleGlyph : public WGraphicsItem
{
	RTTI_DECL(WAzimuthCircleGlyph)

public:
	typedef WAzimuthCircleItemData data_type;

public:
	explicit WAzimuthCircleGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif