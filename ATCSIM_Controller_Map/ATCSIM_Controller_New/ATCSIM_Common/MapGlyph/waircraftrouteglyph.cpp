#include <boost/foreach.hpp>
#include "waircraftrouteglyph.h"
#include <wpainterproxy.h>
#include <wpainter.h>
#include <wmatrix.h>
#include <wglobal.h>


static unsigned line_max_chars(const std::string& text)
{
	unsigned max_chars = 0;
	unsigned curr_max_chars = 0;
	std::string::size_type pos = 0;

	while (pos != std::string::npos)
	{
		std::string::size_type p = text.find('\n', pos);
		curr_max_chars = (p == std::string::npos ? text.size() : p) - pos;
		max_chars = wMax(max_chars, curr_max_chars);
		pos = (p == std::string::npos) ? p : p + 1;
	}

	return max_chars;
}


/**
\brief      SetRadius
\Access    public 
\param  double r
\retval     void
\remark     
*/
void RouteData::SetRadius( double r )
{
	m_width = m_height = r;
}

/**
\brief      SetRadius
\Access    public 
\param  double w
\param  double h
\retval     void
\remark     
*/
void RouteData::SetRadius( double w, double h )
{
	m_width = w;
	m_height = h;
}

/**
\brief      SetCenter
\Access    public 
\param  const WPointF & p
\retval     void
\remark     
*/
void RouteData::SetCenter( const WPointF& p )
{
	m_center = p;
}

/**
\brief      SetArcDir
\Access    public 
\param  ARC_DIR arcDir
\retval     void
\remark     
*/
void RouteData::SetArcDir( ARC_DIR arcDir )
{
	m_arcDir = arcDir;
}


RTTI_IMPL(WAircraftRouteGlyph)


/**
\brief      WAircraftRouteGlyph
\Access    public 
\param  date_type * d
\retval     
\remark     
*/
WAircraftRouteGlyph::WAircraftRouteGlyph( data_type* d /*= 0*/ )
: WGraphicsItem( d ? d : new data_type())
{

}

/**
\brief      paint
\Access    virtual public 
\param  WPainter * painter
\retval     void
\remark     
*/
void WAircraftRouteGlyph::paint( WPainter* painter )
{
	// 绘制导航台

	WPainterProxy proxy(painter);
	WMatrix matrixOrg = painter->worldTransform();
	const data_type& d = *data();

	if (d.m_routeData.empty())
	{
		return;
	}
	painter->setPen(d.m_pen);

	// 画线
	for (size_t i = 1; i < d.m_routeData.size(); ++i )
	{
		if (d.m_routeData[i-1].m_drawType == DT_LINETO
			|| d.m_routeData[i].m_pos.x() == d.m_routeData[i-1].m_pos.x())
		{
			painter->drawLine(WLineF(d.m_routeData[i].m_pos, d.m_routeData[i-1].m_pos));
		}
		else
		{
			// 画弧 // TO MODIFY
			const WPointF& pStart = d.m_routeData[i-1].m_pos;
			const WPointF& pEnd = d.m_routeData[i].m_pos;
			const WPointF& c = d.m_routeData[i-1].m_center; // center
			const double& w = d.m_routeData[i-1].m_width; // 1/2 width
			const double& h = d.m_routeData[i-1].m_height; // 1/2 height
			painter->setBrush(WBrush(Ws::NoBrush));
			WRectF r(c.x() - w, c.y() - h, 2 * w, 2 * h);  // rect area
			//painter->drawRect(r);     // 调试用的区域
			ARC_DIR dir = d.m_routeData[i-1].m_arcDir;
			double startAngle = WLineF(c, pStart).angle();
			double endAngle = WLineF(c, pEnd).angle();
			double delta = endAngle - startAngle;
			dir == AD_RIGHT \
				? painter->drawArc(r, startAngle * 16, delta * 16) \
				: painter->drawArc(r, endAngle * 16, -delta * 16);    //逆时针 & 顺时针
		}
	}
	// 画点
	painter->setWorldTransform(WMatrix());
	static const int R = 10;
	static const WPointF offset(30., -10.);
	static const double FONT_HEIGHT = 14.;
	static const double FONT_WIDTH = 9.;
	BOOST_FOREACH(const RouteData& rd, d.m_routeData)
	{
		WPointF viewPos = matrixOrg.map(rd.m_pos);
		painter->drawLine(WLineF(viewPos + WPointF(0, -R), viewPos + WPointF(-R, R)));
		painter->drawLine(WLineF(viewPos + WPointF(-R, R), viewPos + WPointF(R, R)));
		painter->drawLine(WLineF(viewPos + WPointF(R, R), viewPos + WPointF(0, -R)));

		// 绘制label, 固定大小来画
		WPointF l1 = viewPos + offset;
		int length = wMax(line_max_chars(rd.m_strName), line_max_chars(rd.m_strHeight));
		painter->drawRect(WRectF(l1 - WPointF(2, FONT_HEIGHT - 2), WSizeF(length * FONT_WIDTH, 2 * FONT_HEIGHT)));
		// text
		painter->drawText(l1, rd.m_strName);
		painter->drawText(l1 + WPointF(0, FONT_HEIGHT), rd.m_strHeight);
	}
}

/**
\brief      contain
\Access    virtual public 
\param  const WWorldRectF & r
\retval     bool
\remark     
*/
bool WAircraftRouteGlyph::contain( const WWorldRectF& r ) const
{
	return true;
}

/**
\brief      boundingRect
\Access    virtual public 
\retval     WWorldRectF
\remark     
*/
WWorldRectF WAircraftRouteGlyph::boundingRect() const
{
	static const double inf = 1.0e10;
	return WRectF(-inf, -inf, inf * 2, inf * 2);
}

/**
\brief      data
\Access    public 
\retval     data_type*
\remark     
*/
WAircraftRouteGlyph::data_type* WAircraftRouteGlyph::data()
{
	return W_D();
}

/**
\brief      data
\Access    public 
\retval     const data_type*
\remark     
*/
const WAircraftRouteGlyph::data_type* WAircraftRouteGlyph::data() const
{
	return W_CD();
}





