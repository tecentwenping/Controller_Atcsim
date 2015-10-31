#include "wcloudglyph.h"
#include "core/wserialize.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"
#include "wfontmetrics.h"

/**
\brief      WCloudGlyphItemData
\Access    public 
\retval     
\remark     
*/
WCloudGlyphItemData::WCloudGlyphItemData()
{
	m_color.setRgb(0, 0, 0);
}

/**
\brief      serialize
\Access    virtual public 
\param  char * buf
\retval     char*
\remark     
*/
char* WCloudGlyphItemData::serialize( char* buf ) const
{
	return (WSerializer(WPolygonItemData::serialize(buf))).value();
}

/**
\brief      unserialize
\Access    virtual public 
\param  const char * buf
\retval     const char*
\remark     
*/
const char* WCloudGlyphItemData::unserialize( const char* buf )
{
	return (WUnserializer(WPolygonItemData::unserialize(buf))).value();
}

/**
\brief      serialize_size
\Access    virtual public 
\retval     size_t
\remark     
*/
size_t WCloudGlyphItemData::serialize_size() const
{
	return (WSizeHelper(WPolygonItemData::serialize_size())).value();
}


/**
\brief      WCloudGlyph
\Access    public 
\param  data_type * d
\retval     
\remark     
*/

RTTI_IMPL(WCloudGlyph)

WCloudGlyph::WCloudGlyph( data_type* d /*= 0*/ )
 :WGraphicsPolygonItem(d ? d : new data_type)
{
	setSelectable(false);

}

/**
\brief      paint
\Access    virtual public 
\param  WPainter * painter
\retval     void
\remark     
*/
void WCloudGlyph::paint( WPainter* painter )
{
	WPainterProxy proxy(painter);
	painter->setPen(data()->pen);
	data()->brush.setColor(data()->m_color);
	painter->setBrush(data()->brush);
	painter->drawPolygon(data()->polygon); //»æÖÆ¶à±ßÐÎ
}

/**
\brief      boundingRect
\Access    virtual public 
\retval     WRectF
\remark     
*/
WRectF WCloudGlyph::boundingRect() const
{
	return data()->polygon.boundingRect();
}

/**
\brief      data
\Access    public 
\retval     data_type*
\remark     
*/
WCloudGlyph::data_type* WCloudGlyph::data()
{
	return W_D();
}

/**
\brief      data
\Access    public 
\retval     const data_type*
\remark     
*/
const WCloudGlyph::data_type* WCloudGlyph::data() const
{
	return W_CD();
}
