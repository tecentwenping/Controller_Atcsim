#ifndef _WGATE_GLYPH_H_
#define _WGATE_GLYPH_H_

#include "core/wpen.h"
#include "core/wgraphicsitem.h"
#include "wgraphicspolylineitem.h"

// static const int RADIUS = 5;
// static const int NAV_CIRCLE = 0;
// static const int NAV_TRIANGLE = 1;
// static const int NAV_RECT = 2;

struct GateItemData
{
	int m_navType;
	std::string m_name;
};

class WGateItemData : public WPolylineItemData
{
public:
	WGateItemData();

// 	virtual char* serialize(char* buf) const;
// 	virtual const char* unserialize(const char* buf);
// 	virtual size_t serialize_size() const;

public:
	std::vector<GateItemData> m_vItemDatas;
	int m_iRadius;
	int m_iFactor;
	WPen m_pen;
};

class WGateGlyph : public WGraphicsPolylineItem
{
	RTTI_DECL(WGateGlyph)

public:
	typedef WGateItemData data_type;

public:
	explicit WGateGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;
};

#endif