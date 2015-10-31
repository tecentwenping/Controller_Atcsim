#ifndef _WLONGLAT_GLYPH_H_
#define _WLONGLAT_GLYPH_H_

#include "wgraphicsitem.h"

const int g_max_longlat_num = 5;
//经纬度
class WLongLatItemData : public WItemData
{
public:
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WWorldPointF m_point;//点的场景坐标
	std::string m_strText;//经纬度信息
	int m_index;//索引号
	WRectF m_rect;//经纬度的显示范围
};

class WLongLatGlyph : public WGraphicsItem
{
	RTTI_DECL(WLongLatGlyph)

public:
	typedef WLongLatItemData data_type;
	WMatrix m_mapToViewMatrix;

public:
	explicit WLongLatGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif