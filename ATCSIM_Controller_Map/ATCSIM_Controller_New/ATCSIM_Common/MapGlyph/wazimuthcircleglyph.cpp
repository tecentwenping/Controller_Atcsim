#include <boost/lexical_cast.hpp>
#include "wpainter.h"
#include "wserialize.h"
#include "wpainterproxy.h"
#include "wazimuthcircleglyph.h"

WAzimuthCircleItemData::WAzimuthCircleItemData() : m_pen(WColor(255, 255, 0))
{
}

char* WAzimuthCircleItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_pen).value();
}

const char* WAzimuthCircleItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_pen).value();
}

size_t WAzimuthCircleItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_pen).value();
}

RTTI_IMPL(WAzimuthCircleGlyph)

WAzimuthCircleGlyph::WAzimuthCircleGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

//椭圆在某个方向的点坐标，即从椭圆中心点向某个方向引直线与椭圆的交点
static WPointF point_on_ellipse(const WRectF& r, double radian)
{
	WPointF c = r.center();
	return WPointF(c.x() + r.width() * cos(radian) / 2, c.y() + r.height() * sin(radian) / 2);
}

//世界坐标系方向（弧度，x轴正向为0）转换化为时钟方向（角度，y轴正向为0）
static double world_to_clockwise(double radian)
{
	return normalized_angle(90 - radian * 180 / M_PI);
}

void WAzimuthCircleGlyph::paint(WPainter* painter)
{
	static const size_t LEVEL_1_COUNT = 4;
	static const size_t LEVEL_2_COUNT = 3;
	static const size_t LEVEL_3_COUNT = 5;

	static const double RADIAN = 2 * M_PI;
	static const double RADIAN_LEVEL_1 = RADIAN / LEVEL_1_COUNT;
	static const double RADIAN_LEVEL_2 = RADIAN_LEVEL_1 / LEVEL_2_COUNT;
	static const double RADIAN_LEVEL_3 = RADIAN_LEVEL_2 / LEVEL_3_COUNT;

	static const double L1 = 30.0;
	static const double L2 = 20.0;
	static const double L3 = 10.0;
	static const double L4 = 0.0;

	WSizeF size = painter->deviceSize();
	const double WIDTH = size.width();
	const double HEIGHT = size.height();
	const double DIAMETER = std::min(WIDTH, HEIGHT);
	const double X = (WIDTH - DIAMETER) / 2;
	const double Y = (HEIGHT - DIAMETER) / 2;

	const WRectF R1(X + L1, Y + L1, DIAMETER - 2 * L1, DIAMETER - 2 * L1);
	const WRectF R2(X + L2, Y + L2, DIAMETER - 2* L2, DIAMETER - 2 * L2);
	const WRectF R3(X + L3, Y + L3, DIAMETER - 2 * L3, DIAMETER - 2 * L3);
	const WRectF R4(X + L4, Y + L4, DIAMETER - 2* L4, DIAMETER - 2 * L4);

	WPainterProxy proxy(painter);
	painter->setWorldTransform(WMatrix());
	WBrush brush = painter->brush();
	brush.setStyle(Ws::NoBrush);
	painter->setBrush(brush);
	painter->setPen(data()->m_pen);
	painter->setBrush(WBrush(Ws::NoBrush));
	painter->drawEllipse(R4);

	for (size_t i = 0; i < LEVEL_1_COUNT; ++i)
	{
		double radian_1 = i * RADIAN_LEVEL_1;
		painter->drawText(point_on_ellipse(R4, radian_1), 
			boost::lexical_cast<std::string>(world_to_clockwise(radian_1)) + char(0xb0));
		painter->drawLine(WLineF(point_on_ellipse(R4, radian_1), point_on_ellipse(R1, radian_1)));
		for (size_t j = 0; j < LEVEL_2_COUNT; ++j)
		{
			double radian_2 = radian_1 + j * RADIAN_LEVEL_2;
			painter->drawLine(WLineF(point_on_ellipse(R4, radian_2), point_on_ellipse(R2, radian_2)));
			for (size_t k = 0; k < LEVEL_3_COUNT; ++k)
			{
				double radian_3 = radian_2 + k * RADIAN_LEVEL_3;
				painter->drawLine(WLineF(point_on_ellipse(R4, radian_3), point_on_ellipse(R3, radian_3)));
			}
		}
	}
}

WRectF WAzimuthCircleGlyph::boundingRect() const
{
	static const double INFINITE_RADIUS = 1.0e10;
	return WRectF(-INFINITE_RADIUS, -INFINITE_RADIUS, INFINITE_RADIUS * 2, INFINITE_RADIUS * 2);
}

WAzimuthCircleGlyph::data_type* WAzimuthCircleGlyph::data()
{
	return W_D();
}

const WAzimuthCircleGlyph::data_type* WAzimuthCircleGlyph::data() const
{
	return W_CD();
}