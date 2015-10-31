#ifndef _WPIXMAP_GLYPH_H_
#define _WPIXMAP_GLYPH_H_

#include "wgraphicsitem.h"
#include "wpixmap.h"

class WPixmapItemData : public WItemData
{
public:
	WPixmap m_pixmap;
	WPointF m_pos;
};

class WPixmapGlyph : public WGraphicsItem
{
	RTTI_DECL(WPixmapGlyph)

public:
	typedef WPixmapItemData data_type;

public:
	explicit WPixmapGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WWorldRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;

private:
	WMatrix m_mapToView;
};

#endif