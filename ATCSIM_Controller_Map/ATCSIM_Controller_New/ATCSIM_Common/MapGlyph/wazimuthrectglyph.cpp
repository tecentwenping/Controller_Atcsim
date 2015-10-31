#include <boost/lexical_cast.hpp>
#include "wpainter.h"
#include "wserialize.h"
#include "wpainterproxy.h"
#include "wazimuthrectglyph.h"

WAzimuthRectItemData::WAzimuthRectItemData() : m_pen(WColor(255, 255, 0))
{
}

char* WAzimuthRectItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_pen).value();
}

const char* WAzimuthRectItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_pen).value();
}

size_t WAzimuthRectItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_pen).value();
}

RTTI_IMPL(WAzimuthRectGlyph)

WAzimuthRectGlyph::WAzimuthRectGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

void WAzimuthRectGlyph::paint(WPainter* painter)
{
	static const size_t SCALE_COUNT = 20;
	static const size_t SCALE_COUNT_2 = SCALE_COUNT / 2;
	static const double SCALE_LENGTH = 30.0;

	WSizeF size = painter->deviceSize();
	const double WIDTH = size.width();
	const double HEIGHT = size.height();
	const double CELL_WIDTH = WIDTH / SCALE_COUNT;
	const double CELL_HEIGHT = HEIGHT / SCALE_COUNT;
	const WPointF C(WIDTH / 2.0, HEIGHT / 2.0);

	WPainterProxy proxy(painter);
	painter->setWorldTransform(WMatrix());
	painter->setPen(data()->m_pen);
	painter->setBrush(WBrush(Ws::NoBrush));
	painter->drawRect(WRectF(1.0, 1.0, WIDTH - 2.0, HEIGHT - 2.0));

	WPointF pts[4];
	pts[0].ry() = 0.0;
	pts[1].rx() = WIDTH;
	pts[2].ry() = HEIGHT;
	pts[3].rx() = 0.0;

	for (size_t i = 0; i < SCALE_COUNT; ++i)
	{
		pts[0].rx() = CELL_WIDTH * i;
		pts[1].ry() = CELL_HEIGHT * i;
		pts[2].rx() = pts[0].x();
		pts[3].ry() = pts[1].y();

		bool drawAngle = (i == SCALE_COUNT_2);
		size_t count = 0;
		BOOST_FOREACH(const WPointF& p, pts)
		{
			WLineF line(p, C);
			line.setLength(SCALE_LENGTH);
			painter->drawLine(line);
			if (drawAngle)
			{
				painter->drawText(line.p2(), boost::lexical_cast<std::string>(90 * (count++)) + char(0xb0));
			}
		}
	}
}

WRectF WAzimuthRectGlyph::boundingRect() const
{
	static const double INFINITE_RADIUS = 1.0e10;
	return WRectF(-INFINITE_RADIUS, -INFINITE_RADIUS, INFINITE_RADIUS * 2, INFINITE_RADIUS * 2);
}

WAzimuthRectGlyph::data_type* WAzimuthRectGlyph::data()
{
	return W_D();
}

const WAzimuthRectGlyph::data_type* WAzimuthRectGlyph::data() const
{
	return W_CD();
}