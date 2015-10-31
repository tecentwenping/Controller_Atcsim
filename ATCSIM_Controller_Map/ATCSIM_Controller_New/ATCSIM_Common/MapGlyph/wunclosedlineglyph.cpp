#include "wunclosedlineglyph.h"
#include "core/wserialize.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"
#include "wfontmetrics.h"

WUnclosedLineItemData::WUnclosedLineItemData()
{
	m_color.setRgb(0, 0, 0);
}

void WUnclosedLineItemData::SetLineStyle(Ws::PenStyle style)
{
	pen.setStyle(style);
}


char* WUnclosedLineItemData::serialize(char* buf) const
{
	return (WSerializer(WPolylineItemData::serialize(buf))).value();
}
const char* WUnclosedLineItemData::unserialize(const char* buf)
{
	return (WUnserializer(WPolylineItemData::unserialize(buf))).value();
}

size_t WUnclosedLineItemData::serialize_size() const
{
	return (WSizeHelper(WPolylineItemData::serialize_size())).value();
}

RTTI_IMPL(WUnclosedLineGlyph)

WUnclosedLineGlyph::WUnclosedLineGlyph(data_type* d)
:WGraphicsPolylineItem(d ? d : new data_type)
{
	setSelectable(false);
}

void WUnclosedLineGlyph::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	data()->pen.setColor(data()->m_color);
	painter->setPen(data()->pen);
	for (int i = 0;i < (int)data()->polyline.size()-1;i++)
	{
		WPointF& p1 = data()->polyline[i];
		WPointF& p2 = data()->polyline[i+1];
		painter->drawLine(WLineF(p1, p2));
	}
	WMatrix mapToViewMatrix = painter->worldTransform();
	painter->setWorldTransform(WMatrix());
	WFont font = painter->font();
	const WFontMetrics metrics(font);
	const double DX = metrics.averageCharWidth();
	const double HEIGHT = metrics.height();
	for (int i = 0; i < (int)data()->polyline.size()-1; ++i)
	{
		WPointF center = WLineF(data()->polyline[i], data()->polyline[i+1]).center();
		WPointF viewPos = mapToViewMatrix.map(center);
		double width = data()->m_sName.size() * DX;
		WRectF rect(viewPos.x() - width / 2, viewPos.y() + HEIGHT / 2, width, HEIGHT);
		//painter->setWorldTransform(WMatrix().translate(rect.center()).scale(1, -1).translate(-rect.center()), true);
		painter->drawText(rect,  Ws::AlignLeft, data()->m_sName);
		painter->setWorldTransform(WMatrix());
	}
}

WRectF WUnclosedLineGlyph::boundingRect() const
{
	WRectF tmpRect = data()->polyline.boundingRect();
	//当rect宽度或高度为0时不会作图，所以将两者人为+1
	WRectF rect(tmpRect.left(), tmpRect.bottom(), tmpRect.width()+1, tmpRect.height()+1);
	return rect;
}

WUnclosedLineGlyph::data_type* WUnclosedLineGlyph::data()
{
	return W_D();
}

const WUnclosedLineGlyph::data_type* WUnclosedLineGlyph::data() const
{
	return W_CD();
}