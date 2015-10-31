#include "wqtpainter.h"
#include "guitransform.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <QPolygonF>
#include <QStaticText>
#include <QWidget>
#include "wmapwidget.h"


WQtPainter::WQtPainter(WMapWidget* w, QPainter* dc) : _w(w), _dc(dc)
{
}

void WQtPainter::setDc(QPainter* dc)
{
	_dc = dc;
}

QPainter* WQtPainter::dc()
{
	return _dc;
}

void WQtPainter::drawLine(const WWorldLineF& line)
{
	_dc->drawLine(transform(line));
}

void WQtPainter::drawRect(const WWorldRectF& rect)
{
	_dc->drawRect(transform(rect));
}

WPen WQtPainter::pen() const
{
	return transform(_dc->pen());
}

WBrush WQtPainter::brush() const
{
	return transform(_dc->brush());
}

WFont WQtPainter::font() const
{
	return transform(_dc->font());
}

WMatrix WQtPainter::worldTransform() const
{
	return transform(_dc->worldTransform());
}

void WQtPainter::setPen(const WPen& pen)
{
	_dc->setPen(transform(pen));
}

void WQtPainter::setBrush(const WBrush& brush)
{
	_dc->setBrush(transform(brush));
}

void WQtPainter::setFont(const WFont& font)
{
	_dc->setFont(transform(font));
}

void WQtPainter::setWorldTransform(const WMatrix& matrix, bool combine)
{
	_dc->setWorldTransform(transform(matrix), combine);
}

void WQtPainter::save()
{
	_dc->save();
}

void WQtPainter::restore()
{
	_dc->restore();
}

Ws::BGMode WQtPainter::backgroundMode() const
{
	return static_cast<Ws::BGMode>(_dc->backgroundMode());
}

void	WQtPainter::setBackgroundMode(Ws::BGMode mode)
{
	_dc->setBackgroundMode(static_cast<Qt::BGMode>(mode));
}

void WQtPainter::drawPolygon(const WWorldPolygonF& polygon)
{
	unsigned sz = polygon.size();
	QPolygonF p(sz);
	for (unsigned i=0; i<sz; ++i)
	{
		p[i].rx() = polygon[i].x();
		p[i].ry() = polygon[i].y();
	}

	_dc->drawPolygon(p);
}

void WQtPainter::drawEllipse(const WWorldRectF& rect)
{
	_dc->drawEllipse(transform(rect));
}

void WQtPainter::drawEllipse(const WWorldPoint& center, double rx, double ry)
{
	drawEllipse(WWorldRectF(center.x() - rx, center.y() - ry, rx * 2, ry * 2));
}

void WQtPainter::drawArc(const WWorldRectF& rect, double startAngle, double spanAngle)
{
	//_dc->drawArc(ws2qt_rect(rect), startAngle, spanAngle);
	if (worldTransform().m22() > 0)
	{
		_dc->drawArc(transform(rect), startAngle, spanAngle);
	}
	else
	{
		_dc->drawArc(transform(rect), -startAngle, -spanAngle);
	}
}

void WQtPainter::drawChord(const WWorldRectF& rect, double startAngle, double spanAngle)
{
	_dc->drawChord(transform(rect), startAngle, spanAngle);
}

void WQtPainter::drawPie(const WWorldRectF& rect, double startAngle, double spanAngle)
{
	_dc->drawPie(transform(rect), startAngle, spanAngle);
}

void WQtPainter::drawPolyline(const WWorldPolylineF& polyline)
{
	unsigned sz = polyline.size();

	if (sz > 0)
	{
		std::vector<QPointF> v(sz);

		for (unsigned i=0; i<sz; ++i)
		{
			v[i].rx() = polyline[i].x();
			v[i].ry() = polyline[i].y();
		}

		_dc->drawPolyline(&v[0], sz);
	}
}

void WQtPainter::drawText(const WWorldPointF& pos, const std::string& text)
{
	_dc->drawText(transform(pos), QString::fromStdString(text));
}

void WQtPainter::drawText(const WWorldPointF& pos, const std::wstring& text)
{
	_dc->drawText(transform(pos), QString::fromStdWString(text));
}

//void WQtPainter::drawText(const WWorldRectF& r, int flags, const std::string& text, WWorldRectF* boundingRect)
//{
//	QRectF br;
//	_dc->drawText(transform(r), flags, QString::fromStdString(text), boundingRect ? &br : 0);
//	if (boundingRect)
//	{
//		*boundingRect = transform(br);
//	}
//}

//void WQtPainter::drawText(const WWorldRectF& r, int flags, const std::string& text, WWorldRectF* boundingRect)
//{
//	QRectF br;
//	save();
//	QPointF p = transform(r.center());
//	QTransform m = QTransform().translate(-p.x(), -p.y()) * QTransform().scale(1, -1) * QTransform().translate(p.x(), p.y());
//	_dc->setWorldTransform(m, true);
//	_dc->drawText(transform(r), flags, QString::fromStdString(text), boundingRect ? &br : 0);
//	restore();
//	if (boundingRect)
//	{
//		*boundingRect = transform(br);
//	}
//}

void WQtPainter::drawText(const WWorldRectF& r, int flags, const std::string& text, WWorldRectF* boundingRect)
{
	static QRectF br;
	
	WPointF p = r.center();

	//QTransform m = _dc->worldTransform();
	//_dc->setWorldTransform(QTransform().translate(p.x(), p.y()).scale(1, -1).translate(-p.x(), -p.y()), true);
	_dc->drawText(transform(r), flags, QString::fromStdString(text), boundingRect ? &br : 0);
	//_dc->setWorldTransform(m);

	if (boundingRect)
	{
		*boundingRect = transform(br);
	}
}

//void WQtPainter::drawText(const WWorldRectF& r, int flags, const std::wstring& text, WWorldRectF* boundingRect)
//{
//	QRectF br;
//	_dc->drawText(transform(r), flags, QString::fromStdWString(text), boundingRect ? &br : 0);
//	if (boundingRect)
//	{
//		*boundingRect = transform(br);
//	}
//}

void WQtPainter::drawText(const WWorldRectF& r, int flags, const std::wstring& text, WWorldRectF* boundingRect)
{
	static QRectF br;

	WPointF p = r.center();

	//QTransform m = _dc->worldTransform();
	//_dc->setWorldTransform(QTransform().translate(p.x(), p.y()).scale(1, -1).translate(-p.x(), -p.y()), true);
	_dc->drawText(transform(r), flags, QString::fromStdWString(text), boundingRect ? &br : 0);
	//_dc->setWorldTransform(m);

	if (boundingRect)
	{
		*boundingRect = transform(br);
	}
}

void WQtPainter::drawStaticText(const WWorldPointF& pos, const std::string& text)
{
	_dc->drawStaticText(transform(pos), QStaticText(QString::fromStdString(text)));
}

void WQtPainter::drawPixmap(const WWorldPointF& p, const WPixmap& pixmap)
{
	_dc->drawPixmap(transform(p), transform(pixmap));
}

void WQtPainter::drawPixmap(const WWorldRectF& r, const WPixmap& pixmap)
{
	_dc->drawPixmap(transform(r).toRect(), transform(pixmap));
}

WWorldSizeF WQtPainter::deviceSize()
{
	return WWorldSizeF(_dc->device()->width(), _dc->device()->height());
}

/**
\brief      device
\Access    virtual public 
\retval     WGrahicsView*
\remark     
*/
WGraphicsView* WQtPainter::device() const
{
	// device maybe image or widget
	//return dynamic_cast<WMapWidget*>(_dc->device());
	return _w;
}

/**
\brief      drawPoint
\Access    virtual public 
\param  const WWorldPointF & point
\retval     void
\remark     
*/
void WQtPainter::drawPoint( const WWorldPointF& point )
{
	_dc->drawPoint(transform(point));
}

/**
\brief      setRenderHint
\Access    virtual public 
\param  RenderHint hint
\param  bool on
\retval     void
\remark     
*/
void WQtPainter::setRenderHint( Ws::RenderHint hint, bool on /*= true*/ )
{
	_dc->setRenderHint(static_cast<QPainter::RenderHint>(hint), on);
}
