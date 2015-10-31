#include "wcontrlareaglyph.h"
#include "core/wserialize.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"

WControlAreaItemData::WControlAreaItemData()
{

}


char * WControlAreaItemData::serialize(char* buf) const
{
	return (WSerializer(WPolygonItemData::serialize(buf))).value();
}

const char* WControlAreaItemData::unserialize(const char* buf)
{
	return (WUnserializer(WPolygonItemData::unserialize(buf))).value();
}


size_t WControlAreaItemData::serialize_size() const
{
	return (WSizeHelper(WPolygonItemData::serialize_size())).value();
}


//////////////////////////////////////////////////////////////////////////
RTTI_IMPL(WControlAreaGlyph)
WControlAreaGlyph::WControlAreaGlyph(data_type *d)
:WGraphicsItem(d ? d:new data_type)
{

}

void WControlAreaGlyph::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setBrush(data()->brush);
	painter->drawPolygon(data()->polygon);
}


WRectF WControlAreaGlyph::boundingRect() const
{
	return data()->polygon.boundingRect();
}

WControlAreaGlyph::data_type* WControlAreaGlyph::data()
{
	return W_D();
}

const WControlAreaGlyph::data_type* WControlAreaGlyph::data() const
{
	return W_CD();
}