#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include "wevent.h"
#include "wpainter.h"
#include "wpainterproxy.h"
#include "wfontmetrics.h"
#include "wgraphicsscene.h"
#include "wtelemeterglyph.h"
#include "witemshareprivate.h"
#include "wglyphidentity.h"

TELE_UNIT WTelemeterItemData::m_sUnitType = TELE_METRIC;

void WTelemeterItemData::SetUnitType( const int iType )
{
	m_sUnitType = (TELE_UNIT)iType;
}

RTTI_IMPL(WTelemeterGlyph)

WTelemeterGlyph::WTelemeterGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
	setSelectable(true);
	m_bToDel = false;
	{
		const data_type& d = *data();
		const WFontMetrics metrics(d.m_fontText);
		const double DX = metrics.averageCharWidth();
		const double HEIGHT = metrics.height();
		const double WIDTH = DX * MAX_CHARS;

		// screen
 		m_labelBlockData[0].block_rect = WRectF(0, 0, WIDTH, HEIGHT);
 		m_labelBlockData[1].block_rect = WRectF(0, HEIGHT, WIDTH, HEIGHT);
		m_labelBlockData[2].block_rect = WRectF(0, 2*HEIGHT, WIDTH, HEIGHT);
		
		m_label_bounding_rect = WRectF(0, 0, WIDTH, LABEL_BLOCK_COUNT * HEIGHT);
	}

}

void WTelemeterGlyph::paint(WPainter* painter)
{
	static const double RADIUS = 3.0;

	m_matrixOrg = painter->worldTransform();

	WPainterProxy proxy(painter);
	const data_type& d = *data();

	painter->setPen(d.m_penLine);
	painter->drawLine(d.m_line); // 绘制测距线

	//draw length of this line on screen matrix
	WPointF view_label_pos = m_matrixOrg.map(d.m_line.center()); // 文字显示位置
	painter->setWorldTransform(WMatrix());

	painter->setPen(d.m_penText);
	painter->setFont(d.m_fontText);

	// 计算文字显示
	m_labelBlockData[0].block_text = "B:";
	m_labelBlockData[0].block_text += boost::lexical_cast<std::string>(GetTranslateAngle());
	m_labelBlockData[0].block_text += "°";
	
	m_labelBlockData[1].block_text = "R:";
	char ch[20] ={0};
	int length = static_cast<int>(d.m_line.length());

	double dRealLegth = 0.0;
	std::string strUnitName = "m";
	if (TELE_METRIC == WTelemeterItemData::m_sUnitType)
	{
		if (length > 1000)
		{
			dRealLegth = (double)length/1000;
			strUnitName = "km";
		}
		else
		{
			dRealLegth = length;
			strUnitName = "m";
		}
	}
	else if (TELE_IMPERIAL == WTelemeterItemData::m_sUnitType)
	{
		length *= 0.5403;

		if (length > 1000)
		{
			dRealLegth = (double)length/1000;
			strUnitName = "nm";
		}
		else
		{
			dRealLegth = length;
			strUnitName = "mnm";
		}
	}
	
	sprintf_s(ch, "%.2f %s", dRealLegth, strUnitName.c_str());
	m_labelBlockData[1].block_text += std::string(ch);

	if (!d.m_strTime.empty())
	{
		m_labelBlockData[2].block_text = "T:";
		m_labelBlockData[2].block_text += d.m_strTime;
	}

	// 绘制label
	m_label_bounding_rect.setRect(view_label_pos.x(), view_label_pos.y(), 0., 0.); // reset
	for (unsigned i = 0; i < LABEL_BLOCK_COUNT; ++i)
	{
		const WRectF& targetR = m_labelBlockData[i].block_rect;
		WRectF r(m_labelBlockData[i].block_rect.bottomLeft() + view_label_pos, WSizeF(targetR.width(), targetR.height()));
		painter->drawText(r, Ws::AlignLeft, m_labelBlockData[i].block_text);

		m_label_bounding_rect |= r; // save for label bounding rect
	}
}

WWorldRectF WTelemeterGlyph::boundingRect() const
{
	const WLineF& line = data()->m_line;
	double x1 = line.x1();
	double x2 = line.x2();
	double y1 = line.y1();
	double y2 = line.y2();
	WRectF r_label = m_matrixOrg.inverted().mapRect(m_label_bounding_rect);
	WRectF outR = r_label | WRectF(WPointF(x1<x2?x1:x2, y1<y2?y1:y2), WSizeF(abs(line.dx()), abs(line.dy())));
	return outR.adjusted(-1, -1, 1, 1);
}

WTelemeterGlyph::data_type* WTelemeterGlyph::data()
{
	return W_D();
}

const WTelemeterGlyph::data_type* WTelemeterGlyph::data() const
{
	return W_CD();
}

void WTelemeterGlyph::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	WRectF r_label_scene = m_matrixOrg.inverted().mapRect(m_label_bounding_rect);

	if ((event->buttons() & Ws::MidButton)
		 && ((attachLine(data()->m_line, 3.0, event->scenePos(), 0))
		 || r_label_scene.contains(event->scenePos()))
		)
	{
		setSelected(true);
		m_bToDel = true;
	}
}

/**
\brief      mouseReleaseEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WTelemeterGlyph::mouseReleaseEvent( WGraphicsSceneMouseEvent* event )
{
	setSelected(false);

	if (m_bToDel)
	{
		scene()->addLayer(GLYPH_TELEMETER)->removeItem(this, true);
	}

}

/**
\brief      mouseMoveEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WTelemeterGlyph::mouseMoveEvent( WGraphicsSceneMouseEvent* event )
{
	setSelected(false);

	if (event->buttons() & Ws::MidButton)
	{
		m_bToDel = false;
	}
}

/**
\brief      GetTranslateAngle
\Access    public
\retval     int
\remark     
*/
int WTelemeterGlyph::GetTranslateAngle()
{
	//这里以正北方向为零度,顺时针增加
	//360-d.m_line.angle()切换坐标系从逆时针增加到顺时针，再旋转90，调整0度从正东到正北
	return (450 - static_cast<int>(data()->m_line.angle()))%360;
}