#ifndef _WRUNWAY_GLYPH_H_
#define _WRUNWAY_GLYPH_H_

#include "core/wgraphicsrectitem.h"
#include "wworldline.h"

class WRunwayItemData : public WItemData
{
public:
	WRunwayItemData();

public:
	static const size_t GENERIC_SCALE_COUNT = 2;
	static const size_t DETAIL_SCALE_COUNT = 5;
	static const bool SHOW_PROLONG = true;

public:
	WPen m_pen;
	double m_dProlongLength; //延长线长度
	size_t m_genericScaleCount; //延长线大刻度个数
	size_t m_detailScaleCount; //延长线小刻度个数
	bool m_bShowProlong; //是否显示延长线
	WPointF m_pointStart; // 无用
	WLineF m_line; // 起点到终点
	WSizeF m_size; // 长、宽
	double m_angle; // 角度
};

class WRunwayGlyph : public WGraphicsItem
{
	RTTI_DECL(WRunwayGlyph)

public:
	typedef WRunwayItemData data_type;

public:
	explicit WRunwayGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;
};

#endif