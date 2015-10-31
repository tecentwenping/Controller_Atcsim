#include "wpainter.h"
#include "wserialize.h"
#include "wringsglyph.h"
#include "wpainterproxy.h"

#include <boost/lexical_cast.hpp>

RING_UNIT WRingsItemData::m_sUnitType = RING_METRIC;

char* WRingsItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_center << m_rings).value();
}

const char* WRingsItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_center >> m_rings).value();
}

size_t WRingsItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_center << m_rings).value();
}

const WPointF WRingsItemData::GetCenter() const
{
	return m_center;
}

void WRingsItemData::SetCenter(const WPointF& c)
{
	m_center = c;
}

bool WRingsItemData::AddRing(double radius)
{
	return m_rings.insert(radius).second;
}

void WRingsItemData::AddRings(double radiusBase, double step, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		m_rings.insert(radiusBase + i * step);
	}
}

bool WRingsItemData::RemoveRing(double radius)
{
	return m_rings.erase(radius) > 0;
}

void WRingsItemData::RemoveRings()
{
	m_rings.clear();
}

const std::vector<double> WRingsItemData::GetRings() const
{
	return std::vector<double>(m_rings.begin(), m_rings.end());
}

void WRingsItemData::SetUnitType( const int type )
{
	m_sUnitType = (RING_UNIT)type;
}

RTTI_IMPL(WRingsGlyph)

WRingsGlyph::WRingsGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

void WRingsGlyph::paint(WPainter* painter)
{
	const data_type& d = *data();
	const std::vector<double> rings = d.GetRings();
	WPointF c = d.GetCenter();
	
	const WMatrix& matrxOrg = painter->worldTransform();

	WPainterProxy proxy(painter);
	WPen pen = d.m_pen;
	painter->setPen(d.m_pen);
	painter->setBrush(WBrush(Ws::NoBrush));

	int i = 1;
	BOOST_FOREACH(double ring, rings)
	{
		if (1 == i % 2)
		{
			pen.setStyle(Ws::SolidLine);
			painter->setPen(pen);
		}
		else
		{
			pen.setStyle(Ws::DashLine);
			painter->setPen(pen);
		}

		int realRing;
		std::string strUnitName;
		//公制单位
		if (RING_METRIC == WRingsItemData::m_sUnitType)
		{
			realRing = ring;
			if (ring < 1000)
			{
				strUnitName = "m";
			}
			else
			{
				strUnitName = "km";
				ring /= 1000;
			}
		}
		//英制单位
		else if (RING_IMPERIAL == WRingsItemData::m_sUnitType)
		{
			realRing = ring/0.5403;
			if (ring < 1000)
			{
				strUnitName = "mnm";
			}
			else
			{
				strUnitName = "nm";
				ring /= 1000;
			}
		}
		

		painter->drawEllipse(WRectF(c.x() - realRing, c.y() - realRing, realRing * 2, realRing * 2));
		// 绘制距离环单位显示
		WPointF viewPosL = matrxOrg.map(WPointF(c.x() - realRing, c.y()));
		WPointF viewPosR = matrxOrg.map(WPointF(c.x() + realRing, c.y()));
		WPainterProxy proxy(painter);
		painter->setWorldTransform(WMatrix());
		painter->drawText(viewPosL, boost::lexical_cast<std::string>(ring) + strUnitName);
		painter->drawText(viewPosR, boost::lexical_cast<std::string>(ring) + strUnitName);
		++i;
	}
}

WRectF WRingsGlyph::boundingRect() const
{
	const data_type& d = *data();
	const std::vector<double> rings = d.GetRings();
	double dRingMax = (rings.empty() ? 0 : *rings.rbegin());

	WPointF c = d.GetCenter();
	return WRectF(c.x() - dRingMax, c.y() - dRingMax, dRingMax * 2, dRingMax * 2);
}

WRingsGlyph::data_type* WRingsGlyph::data()
{
	return W_D();
}

const WRingsGlyph::data_type* WRingsGlyph::data() const
{
	return W_CD();
}