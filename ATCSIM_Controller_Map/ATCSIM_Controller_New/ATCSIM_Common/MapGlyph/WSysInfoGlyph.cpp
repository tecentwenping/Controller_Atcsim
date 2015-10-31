#include "WSysInfoGlyph.h"
#include "wpainter.h"
#include "wpainterproxy.h"
#include "wserialize.h"

/**
\brief     WSysInfoItemData
\Access    public 
\retval    
\remark     
*/
WSysInfoItemData::WSysInfoItemData()
{

}

/**
\brief     serialize
\Access    virtual public 
\param     char * buf
\retval    char*
\remark     
*/
char* WSysInfoItemData::serialize( char* buf ) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_strLongitude << m_strLatitude).value();
}

/**
\brief     unserialize
\Access    virtual public 
\param     const char * buf
\retval    const char*
\remark     
*/
const char* WSysInfoItemData::unserialize( const char* buf )
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_strLongitude >> m_strLatitude).value();
}
/**
\brief     serialize_size
\Access    virtual public 
\retval    size_t
\remark     
*/
size_t WSysInfoItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_strLongitude << m_strLatitude).value();
}




RTTI_IMPL(WSysInfoGlyph)

/**
\brief     WSysInfoGlyph
\Access    public 
\param     data_type * d
\retval    
\remark     
*/
WSysInfoGlyph::WSysInfoGlyph( data_type* d /*= 0*/ ) : WGraphicsItem(d ? d : new data_type)
{

}
/**
\brief     paint
\Access    virtual public 
\param     WPainter * painter
\retval    void
\remark     
*/
void WSysInfoGlyph::paint( WPainter* painter )
{
	WPainterProxy proxy(painter);
	painter->setWorldTransform(WMatrix());

	WBrush brush = painter->brush();
	
	WPen p = painter->pen();
	p.setColor(WColor(255, 255, 0));
	
	WFont font = painter->font();
	font.setPointSize(20);

	painter->setFont(font);
	painter->setPen(p);

	WPointF textPos(50, 150);
	painter->drawText(textPos, data()->m_strLongitude);
	painter->drawText(WPointF(textPos.x(), textPos.y() + 50), data()->m_strLatitude);
}


/**
\brief     boundingRect
\Access    virtual public 
\retval    WRectF
\remark     
*/
WRectF WSysInfoGlyph::boundingRect() const
{
	static const double INFINITE_RADIUS = 1.0e10;
	return WRectF(-INFINITE_RADIUS, -INFINITE_RADIUS, INFINITE_RADIUS * 2, INFINITE_RADIUS * 2);
}
/**
\brief     data
\Access    public 
\retval    data_type*
\remark     
*/
WSysInfoGlyph::data_type* WSysInfoGlyph::data()
{
	return W_D();
}
/**
\brief     data
\Access    public 
\retval    const data_type*
\remark     
*/
const WSysInfoGlyph::data_type* WSysInfoGlyph::data() const
{
	return W_CD();
}





