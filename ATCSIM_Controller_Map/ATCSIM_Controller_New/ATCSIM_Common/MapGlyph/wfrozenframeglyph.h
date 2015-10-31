#ifndef _WFROZEN_FRAME_GLYPH_H_
#define _WFROZEN_FRAME_GLYPH_H_

#include "wgraphicsitem.h"

class WFrozenFrameItemData : public WItemData
{
public:
	WFrozenFrameItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WPen m_pen;
	WBrush m_brushBegin;
	WBrush m_brushEnd;
};

class WFrozenFrameGlyph : public WGraphicsItem
{
	RTTI_DECL(WFrozenFrameGlyph)

public:
	typedef WFrozenFrameItemData data_type;

public:
	explicit WFrozenFrameGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif