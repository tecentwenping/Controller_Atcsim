#include "wpainter.h"
#include "wserialize.h"
#include "wpainterproxy.h"
#include "wfrozenframeglyph.h"

WFrozenFrameItemData::WFrozenFrameItemData() : 
	m_brushBegin(WColor(255, 255, 255)), m_brushEnd(WColor(255, 0, 0))
{
}

char* WFrozenFrameItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_pen << m_brushBegin << m_brushEnd).value();
}

const char* WFrozenFrameItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_pen >> m_brushBegin >> m_brushEnd).value();
}

size_t WFrozenFrameItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_pen << m_brushBegin << m_brushEnd).value();
}

RTTI_IMPL(WFrozenFrameGlyph)

WFrozenFrameGlyph::WFrozenFrameGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

void WFrozenFrameGlyph::paint(WPainter* painter)
{
	static const size_t BLOCK_COUNT = 20;
	static const double BLOCK_WIDTH = 30.0;
	static const double X_LEFT= 0.0;

	const data_type& d = *data();
	WSizeF size = painter->deviceSize();
	const double BLOCK_HEIGHT = size.height() / BLOCK_COUNT;
	const double X_RIGHT = size.width() - X_LEFT - BLOCK_WIDTH;

	WPainterProxy proxy(painter);
	painter->setWorldTransform(WMatrix());
	painter->setPen(d.m_pen);
	for (size_t i = 0; i < BLOCK_COUNT; ++i)
	{
		double y = BLOCK_HEIGHT * i;
		painter->setBrush((i & 1) ? d.m_brushEnd : d.m_brushBegin);
		painter->drawRect(WRectF(X_LEFT, y, BLOCK_WIDTH, BLOCK_HEIGHT));
		painter->drawRect(WRectF(X_RIGHT, y, BLOCK_WIDTH, BLOCK_HEIGHT));
	}
}

WRectF WFrozenFrameGlyph::boundingRect() const
{
	static const double INFINITE_RADIUS = 1.0e10;
	return WRectF(-INFINITE_RADIUS, -INFINITE_RADIUS, INFINITE_RADIUS * 2, INFINITE_RADIUS * 2);
}

WFrozenFrameGlyph::data_type* WFrozenFrameGlyph::data()
{
	return W_D();
}

const WFrozenFrameGlyph::data_type* WFrozenFrameGlyph::data() const
{
	return W_CD();
}