#include "wrandompointglyph.h"
#include "wserialize.h"
#include "wpainter.h"
#include "wpainterproxy.h"


/**
\brief      WRandomPointItemData
\Access    public 
\retval     
\remark     
*/
WRandomPointItemData::WRandomPointItemData():m_eRandomPointType(RPT_TRIANGLE)
{
}

/**
\brief      serialize
\Access    virtual public 
\param  char * buf
\retval     char*
\remark     
*/
char* WRandomPointItemData::serialize( char* buf ) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_eRandomPointType << m_pos << m_pen << m_brush).value();
}

/**
\brief      unserialize
\Access    virtual public 
\param  const char * buf
\retval     const char*
\remark     
*/
const char* WRandomPointItemData::unserialize( const char* buf )
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_eRandomPointType >> m_pos >> m_pen >> m_brush).value();
}

/**
\brief      serialize_size
\Access    virtual public 
\retval     size_t
\remark     
*/
size_t WRandomPointItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_eRandomPointType << m_pos << m_pen << m_brush).value();
}


static const int POINTRADIUS = 5;
RTTI_IMPL(WRandomPointGlyph)
/**
\brief      WRandomPointGlyph
\Access    public 
\param  data_type * d
\retval     
\remark     
*/
WRandomPointGlyph::WRandomPointGlyph( data_type* d /*= 0*/ ) : WGraphicsItem(d ? d : new data_type)
{
}

/**
\brief      paint
\Access    virtual public 
\param  WPainter * painter
\retval     void
\remark     
*/
void WRandomPointGlyph::paint( WPainter* painter )
{
	WPainterProxy proxy(painter);
	ENUM_RANDOMPOINT_TYPE typ = data()->m_eRandomPointType;
	const WPointF& p = data()->m_pos;

	painter->setPen(data()->m_pen);
	painter->setBrush(data()->m_brush);

	WMatrix mapToViewMatrix = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
	WPointF viewPos = mapToViewMatrix.map(p);

	WRectF r(viewPos.x() - POINTRADIUS, viewPos.y() - POINTRADIUS, POINTRADIUS * 2.0, POINTRADIUS * 2.0);
	if (typ == RPT_CIRCLE)
	{
		painter->drawEllipse(r);
	}
	else if (typ == RPT_RECT)
	{
		painter->drawRect(r);
	}
	else if(typ == RPT_TRIANGLE)
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(viewPos.x(), viewPos.y() - POINTRADIUS);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - POINTRADIUS, viewPos.y() + POINTRADIUS);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + POINTRADIUS, viewPos.y() + POINTRADIUS);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
	}

}

/**
\brief      boundingRect
\Access    virtual public 
\retval     WRectF
\remark     
*/
WRectF WRandomPointGlyph::boundingRect() const
{
	const WPointF& p = data()->m_pos;
	return WRectF(p.x() - POINTRADIUS, p.y() - POINTRADIUS, POINTRADIUS * 2, POINTRADIUS * 2);
}

/**
\brief      data
\Access    public 
\retval     data_type*
\remark     
*/
WRandomPointGlyph::data_type* WRandomPointGlyph::data()
{
	return W_D();
}

/**
\brief      data
\Access    public 
\retval     const data_type*
\remark     
*/
const WRandomPointGlyph::data_type* WRandomPointGlyph::data() const
{
	return W_CD();
}

/**
\brief      type
\Access    virtual public 
\retval     int
\remark     
*/
int WRandomPointGlyph::type() const
{
	return Type;
}
