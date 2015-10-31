#include "wpainter.h"
#include "wpainterproxy.h"
#include "wpixmapglyph.h"

RTTI_IMPL(WPixmapGlyph)

WPixmapGlyph::WPixmapGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{

}

void WPixmapGlyph::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setBrush(WBrush(Ws::NoBrush));
	painter->setRenderHint(Ws::SmoothPixmapTransform);

	m_mapToView = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
	
	data_type& d = *data();
	d.m_pixmap = WPixmap(":/plane.png");
	WWorldPointF point = m_mapToView.map(d.m_pos) -WPointF(d.m_pixmap.width()/2, d.m_pixmap.height()/2);
	painter->drawPixmap(point, d.m_pixmap);
}


WPixmapGlyph::data_type* WPixmapGlyph::data()
{
	return W_D();
}

const WPixmapGlyph::data_type* WPixmapGlyph::data() const
{
	return W_CD();
}

/**
\brief      boundingRect
\Access    virtual public 
\retval     WWorldRectF
\remark     
*/
WWorldRectF WPixmapGlyph::boundingRect() const
{
 	const data_type& d = *data();
 	WWorldPointF viewPos = m_mapToView.map(d.m_pos);
 	return m_mapToView.inverted().mapRect(WWorldRectF(viewPos.x()-20, viewPos.y()-20, 40, 40));
}