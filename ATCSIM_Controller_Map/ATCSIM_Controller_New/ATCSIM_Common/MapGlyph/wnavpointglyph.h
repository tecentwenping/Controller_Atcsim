#ifndef _WNAV_POINT_GLYPH_H_
#define _WNAV_POINT_GLYPH_H_

#include "core/wpen.h"
#include "core/wgraphicsitem.h"
#include "core/wmatrix.h"

static const int RADIUS = 5;
static const int NAV_CIRCLE = 0;
static const int NAV_TRIANGLE = 1;
static const int NAV_RECT = 2;

class WNavPointItemData : public WItemData
{
public:
	WNavPointItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	int m_id;
	int m_navType;
	std::string m_text;
	WPointF m_pos;
	WPen m_pen;
};

class WNavPointGlyph : public WGraphicsItem
{
	RTTI_DECL(WNavPointGlyph)

public:
	typedef WNavPointItemData data_type;

public:
	explicit WNavPointGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域
	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const; //吸附
	int GetId();

	data_type* data(); //图元核心数据
	const data_type* data() const;

private:
	WMatrix m_mapToViewMatrix;
};

#endif