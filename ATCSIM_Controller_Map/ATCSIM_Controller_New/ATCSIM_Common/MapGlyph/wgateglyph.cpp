#include "wgateglyph.h"
#include "core/wserialize.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"

WGateItemData::WGateItemData()
{
	m_iRadius = 5;
	m_iFactor = 8;
}

// char* WGateItemData::serialize(char* buf) const
// {
// 	return (WSerializer(WItemData::serialize(buf)) << m_ItemData << m_pen).value();
// }
// const char* WGateItemData::unserialize(const char* buf)
// {
// 	return (WUnserializer(WItemData::unserialize(buf)) >> m_ItemData >> m_pen).value();
// }
// 
// size_t WGateItemData::serialize_size() const
// {
// 	return (WSizeHelper(WItemData::serialize_size()) << m_ItemData << m_pen).value();
// }

RTTI_IMPL(WGateGlyph)

WGateGlyph::WGateGlyph(data_type* d) : WGraphicsPolylineItem(d ? d : new data_type)
{
}

// static const int FACTOR = 8;
// static const int FACTOR_2 = FACTOR / 2;

void WGateGlyph::paint(WPainter* painter)
{
	if (data()->polyline.empty())
	{
		return;
	}
	WPainterProxy proxy(painter);
	
	WMatrix mapToViewMatrix = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
	for (int i = 0;i < (int)data()->polyline.size()-1;i++)
	{
		WPointF p1 = mapToViewMatrix.map(data()->polyline[i]);
		WPointF p2 = mapToViewMatrix.map(data()->polyline[i+1]);

		data()->pen.setStyle(Ws::SolidLine);
		data()->pen.setWidth(2);
		painter->setPen(data()->pen);
		painter->drawLine(WLineF(p1, p2));
	}

// 		data()->pen.setStyle(Ws::SolidLine);
// 		painter->setPen(data()->pen);
// 		int typ = data()->m_vItemDatas[i].m_navType;
// 		WRectF r(p1.x() - data()->m_iRadius, p1.y() - data()->m_iRadius, data()->m_iRadius * 2, data()->m_iRadius * 2);
// 		if (typ == 0)
// 		{
// 			painter->drawRect(r);
// 		}
// 		else if (typ == 1)
// 		{
// 			painter->drawEllipse(r);
// 		}
// 		painter->drawText(WRectF(p1.x() - data()->m_iRadius * data()->m_iFactor / 2, 
// 			                     p1.y() - data()->m_iRadius * data()->m_iFactor / 2, 
// 			                     data()->m_iRadius * data()->m_iFactor, data()->m_iRadius * data()->m_iFactor), 
// 						  0, 
// 			              data()->m_vItemDatas[i].m_name);
// 	}
// 	data()->pen.setStyle(Ws::SolidLine);
// 	painter->setPen(data()->pen);
// 	GateItemData item = data()->m_vItemDatas.back();
// 	WPointF& pEnd = data()->polyline.back();
// 	int type = item.m_navType;
// 	WRectF r(pEnd.x() - data()->m_iRadius, pEnd.y() - data()->m_iRadius, data()->m_iRadius * 2, data()->m_iRadius * 2);
// 	if (type == 0)
// 	{
// 		painter->drawEllipse(r);
// 	}
// 	else if (type == 1)
// 	{
// 		painter->drawRect(r);
// 	}
// 	painter->drawText(WRectF(pEnd.x() - data()->m_iRadius * data()->m_iFactor / 2, 
// 		                     pEnd.y() - data()->m_iRadius * data()->m_iFactor / 2, 
// 		                     data()->m_iRadius * data()->m_iFactor, data()->m_iRadius * data()->m_iFactor), 
// 		              0, 
// 		              item.m_name);

}

WRectF WGateGlyph::boundingRect() const
{
	WRectF tmpRect = data()->polyline.boundingRect();
	//将点的半径计算在内
	WRectF rect(tmpRect.left() - data()->m_iRadius, tmpRect.bottom() - data()->m_iRadius, 
		        tmpRect.width() + 2 * data()->m_iRadius, 
				tmpRect.height() + 2 * data()->m_iRadius);
    return rect;
}

WGateGlyph::data_type* WGateGlyph::data()
{
	return W_D();
}

const WGateGlyph::data_type* WGateGlyph::data() const
{
	return W_CD();
}