#include "wrunwayglyph.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"

WRunwayItemData::WRunwayItemData() : m_dProlongLength(0.0), m_bShowProlong(SHOW_PROLONG),
	m_genericScaleCount(GENERIC_SCALE_COUNT), m_detailScaleCount(DETAIL_SCALE_COUNT)
{
}

RTTI_IMPL(WRunwayGlyph)

WRunwayGlyph::WRunwayGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

WRunwayGlyph::data_type* WRunwayGlyph::data()
{
	return W_D();
}

const WRunwayGlyph::data_type* WRunwayGlyph::data() const
{
	return W_CD();
}

void WRunwayGlyph::paint(WPainter* painter)
{
	data_type& d = *data();
	WPointF c = d.m_line.center();
	double w = d.m_size.width();
	//double h = d.m_size.height();
	double h = d.m_line.length();
	d.m_dProlongLength = h / 2;

	WPainterProxy proxy(painter);
	painter->setPen(d.m_pen);
	painter->setBrush(WBrush(Ws::NoBrush));
	painter->setWorldTransform(WMatrix().translate(c).rotate(90 - d.m_angle).translate(-c), true);
	painter->drawRect(WRectF(c.x() - h / 2, c.y() - w / 2, h, w));

	if (data()->m_bShowProlong)
	{
		WPointF s(c.x() + h / 2, c.y()); //line start point
		WLineF line(s, WPointF(s.x() + data()->m_dProlongLength, s.y()));
		painter->drawLine(line);

		const size_t scaleCount = data()->m_genericScaleCount * data()->m_detailScaleCount;
		const double genericScaleLength = data()->m_dProlongLength / 20.0;
		const double detailScaleLength = data()->m_dProlongLength / 40.0;
		const double scaleDistance = data()->m_dProlongLength / scaleCount;

		for (size_t i = 1; i < scaleCount + 1; ++i)
		{
			WPointF p(s.x() + i * scaleDistance, s.y());
			WPointF p1(p);
			WPointF p2(p);
			const double& scaleLength = (i % data()->m_detailScaleCount == 0 ? 
			genericScaleLength : detailScaleLength);
			p1.ry() -= scaleLength;
			p2.ry() += scaleLength;
			painter->drawLine(WLineF(p1, p2));
		}
	}
}

WRectF WRunwayGlyph::boundingRect() const
{
	/*const WRectItemData& d = data()->m_rectData;
	const WRectF& r = d.rect;
	WWorldPointF p = r.bottomLeft();
	const double genericScaleLength = data()->m_dProlongLength / 20.0;
	const double dy = std::max(genericScaleLength - r.height() / 2.0, 0.0);

	WMatrix m = WMatrix().translate(-p) * WMatrix().rotate(d.angle) * WMatrix().translate(p);
	
	return m.mapRect(data()->m_bShowProlong ? r.adjusted(0.0, -dy, data()->m_dProlongLength, dy) : r);*/
	return WRectF(-20000, -20000, 40000, 40000);
}