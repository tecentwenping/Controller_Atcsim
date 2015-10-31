#include "wpainter.h"
#include "wserialize.h"
#include "wlonglatglyph.h"
#include "wfontmetrics.h"
#include "core/wpainterproxy.h"

const int g_point_radius = 2;
const WColor g_color = WColor(255, 0, 0);

char* WLongLatItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_point << m_strText << m_index).value();
}

const char* WLongLatItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_point >> m_strText >> m_index).value();
}

size_t WLongLatItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_point << m_strText << m_index).value();
}

RTTI_IMPL(WLongLatGlyph)

WLongLatGlyph::WLongLatGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{

}

void WLongLatGlyph::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	data_type& d = *data();

 	m_mapToViewMatrix = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
 	WPointF viewPos = m_mapToViewMatrix.map(d.m_point);

	WFont font("Verdana", 11, 25);
	const WFontMetrics metrics(font);
	const double HEIGHT = metrics.height();
	const double WIDTH = /*170*/(data()->m_strText.size()+4) * metrics.averageCharWidth();
	d.m_rect.setRect(viewPos.x() - WIDTH / 2, viewPos.y() + HEIGHT / 2, WIDTH, HEIGHT);


	WPen pen(g_color);
	painter->setPen(pen);
	painter->setFont(font);
	painter->setBrush(WBrush(g_color));

	painter->drawEllipse(WWorldPoint(viewPos.x(), viewPos.y()), g_point_radius, g_point_radius);
	painter->drawText(d.m_rect, Ws::AlignCenter, d.m_strText);
}

WRectF WLongLatGlyph::boundingRect() const
{
 	const data_type& d = *data();

	if (d.m_rect.isEmpty())
	{
		WWorldPointF viewPoint = m_mapToViewMatrix.map(d.m_point);
		return m_mapToViewMatrix.inverted().mapRect(WRectF(viewPoint.x()-80, viewPoint.y()-g_point_radius, 29, 160));
	}
	else
	{
		return m_mapToViewMatrix.inverted().mapRect(d.m_rect);
	}
}

WLongLatGlyph::data_type* WLongLatGlyph::data()
{
	return W_D();
}

const WLongLatGlyph::data_type* WLongLatGlyph::data() const
{
	return W_CD();
}