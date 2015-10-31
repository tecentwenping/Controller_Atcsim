#include "wnavpointglyph.h"
#include "core/wserialize.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"
#include "wfontmetrics.h"

WNavPointItemData::WNavPointItemData() : m_navType(NAV_CIRCLE)
{
}

char* WNavPointItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << m_navType << m_pos << m_pen).value();
}
const char* WNavPointItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> m_navType >> m_pos >> m_pen).value();
}

size_t WNavPointItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << m_navType << m_pos << m_pen).value();
}

RTTI_IMPL(WNavPointGlyph)

WNavPointGlyph::WNavPointGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

static const int FACTOR = 8;
static const int FACTOR_2 = FACTOR / 2;

void WNavPointGlyph::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	int typ = data()->m_navType;
	const WPointF& p = data()->m_pos;
	
	painter->setPen(data()->m_pen);
	painter->setBrush(WBrush(Ws::NoBrush));

	m_mapToViewMatrix = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
    WPointF viewPos = m_mapToViewMatrix.map(p);
 
	WRectF r(viewPos.x() - RADIUS, viewPos.y() - RADIUS, RADIUS * 2, RADIUS * 2);
	if (typ == NAV_CIRCLE)
	{
		painter->drawEllipse(r);
	}
	else if (typ == NAV_RECT)
	{
		painter->drawRect(r);
	}
	else if(typ == 3)//ʵ������
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(viewPos.x(), viewPos.y() - 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - 5, viewPos.y() + 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 5, viewPos.y() + 5);
		vPoints.push_back(Tmppoint);
		painter->setBrush(WBrush(Ws::SolidPattern));
		painter->drawPolygon(WWorldPolygonF(vPoints));
	}
	else if (typ == 4)//˫Բ��
	{
		painter->drawEllipse(r);
		r.setRect(viewPos.x() - 3, viewPos.y() - 3, 6, 6);
		painter->drawEllipse(r);
	}
	else if (typ == 5)//��������
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(viewPos.x(), viewPos.y() - 4);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - 4, viewPos.y() + 4);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 4, viewPos.y() + 4);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
	}
	else if (typ == 6)//����
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		painter->setBrush(WBrush(Ws::SolidPattern));
		//��
		Tmppoint.setXY(viewPos.x() - 1, viewPos.y() + 2);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 1, viewPos.y() + 2);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x(), viewPos.y() + 8);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
		//��
		vPoints.clear();
		Tmppoint.setXY(viewPos.x() + 2, viewPos.y() - 1);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 2, viewPos.y() + 1);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 8, viewPos.y());
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
		//��
		vPoints.clear();
		Tmppoint.setXY(viewPos.x() - 1, viewPos.y() - 2);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 1, viewPos.y() - 2);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x(), viewPos.y() - 8);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
		//��
		vPoints.clear();
		Tmppoint.setXY(viewPos.x() - 2, viewPos.y() - 1);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - 2, viewPos.y() + 1);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - 8, viewPos.y());
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
	}
	else if (typ == 7)//ɽ
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		painter->setBrush(WBrush(Ws::SolidPattern));
		Tmppoint.setXY(viewPos.x(), viewPos.y() - 8);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() - 4, viewPos.y() + 4);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 4, viewPos.y() + 4);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
	}
	else if (typ == 8)//ԲȦ�м��ʮ��
	{
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(viewPos.x(), viewPos.y() + 7);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x(), viewPos.y() - 7);
		vPoints.push_back(Tmppoint);
		painter->drawLine(WWorldLineF(vPoints[0].x(), vPoints[0].y(), vPoints[1].x(), vPoints[1].y()));
		vPoints.clear();
		Tmppoint.setXY(viewPos.x() - 7, viewPos.y());
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(viewPos.x() + 7, viewPos.y());
		vPoints.push_back(Tmppoint);
		painter->drawLine(WWorldLineF(vPoints[0].x(), vPoints[0].y(), vPoints[1].x(), vPoints[1].y()));
		r.setRect(viewPos.x() - 7, viewPos.y() - 7, 14, 14);
		painter->drawEllipse(r);
	}

	WFont font = painter->font();
	const WFontMetrics metrics(font);
	const double DX = metrics.averageCharWidth();
	const double HEIGHT = metrics.height();
    const double WIDTH = data()->m_text.size() * DX;
	WRectF rect(viewPos.x() - WIDTH / 2, viewPos.y() + HEIGHT / 2, WIDTH, HEIGHT);

	//painter->setWorldTransform(WMatrix().translate(rect.center()).scale(1, -1).translate(-rect.center()), true);
	painter->drawText(rect,  Ws::AlignLeft, data()->m_text);
}

WRectF WNavPointGlyph::boundingRect() const
{
	const WPointF& p = data()->m_pos;
	return WRectF(p.x() - RADIUS * FACTOR_2, p.y() - RADIUS * FACTOR_2, RADIUS * FACTOR, RADIUS * FACTOR_2);
}

WNavPointGlyph::data_type* WNavPointGlyph::data()
{
	return W_D();
}

const WNavPointGlyph::data_type* WNavPointGlyph::data() const
{
	return W_CD();
}

/**
\brief      attachPoint
\Access    virtual public 
\param  const WWorldPointF & pos
\param  WWorldPointF * attachedPos
\retval     bool
\remark     
*/
bool WNavPointGlyph::attachPoint( const WWorldPointF& pos, WWorldPointF* attachedPos ) const
{
	const WWorldPointF& p = data()->m_pos;
	//���������ʾ������Ļ������룬 ����ǳ��������ڱ�����С������¼���������������״̬
	if (pos == p || distance(m_mapToViewMatrix.map(pos), m_mapToViewMatrix.map(p)) < ATTACH_DISTANCE)
	{
		if (attachedPos)
		{
			*attachedPos = p;
		}
		return true;
	}

	return false;
}

/**
\brief      GetId
\Access    public 
\retval     int
\remark     
*/
int WNavPointGlyph::GetId()
{
	return data()->m_id;
}