#include "../wdllexport.h"
#include "guitransform.h"

QPen transform(const WPen& pen)
{
	return QPen(QBrush(transform(pen.color())), pen.width(), static_cast<Qt::PenStyle>(pen.style()));
}

WPen transform(const QPen& pen)
{
	return WPen(static_cast<Ws::PenStyle>(pen.style()), transform(pen.color()), pen.widthF());
}

QBrush transform(const WBrush& brush)
{
	return QBrush(transform(brush.color()), static_cast<Qt::BrushStyle>(brush.style()));
}

WBrush transform(const QBrush& brush)
{
	return WBrush(transform(brush.color()), static_cast<Ws::BrushStyle>(brush.style()));
}

QFont transform(const WFont& font)
{
	QFont f(QString::fromStdString(font.family()), font.pointSize(), font.weight(), font.italic());
	f.setUnderline(font.underline());
	f.setStrikeOut(font.strikeOut());
	f.setKerning(font.kerning());
	return f;
}

WFont transform(const QFont& font)
{
	WFont f(font.family().toStdString(), font.pointSize(), font.weight(), font.italic());
	f.setUnderline(font.underline());
	f.setStrikeOut(font.strikeOut());
	f.setKerning(font.kerning());
	return f;
}

QTransform transform(const WMatrix& matrix)
{
	return QTransform(matrix.m11(), matrix.m12(), matrix.m21(), matrix.m22(), matrix.dx(), matrix.dy());
}

WMatrix transform(const QTransform& matrix)
{
	return WMatrix(matrix.m11(), matrix.m12(), matrix.m21(), matrix.m22(), matrix.dx(), matrix.dy());
}

QCursor transform(const WCursor& cursor)
{
	return QCursor(static_cast<Qt::CursorShape>(cursor.shape()));
}

WCursor transform(const QCursor& cursor)
{
	return WCursor(static_cast<Ws::CursorShape>(cursor.shape()));
}

QRectF transform(const WWorldRectF& rect)
{
	//return QRectF(rect.left(), rect.top(), rect.width(), rect.height());
	return QRectF(rect.left(), rect.bottom(), rect.width(), rect.height());
}

WWorldRectF transform(const QRectF& rect)
{
	//return WWorldRectF(rect.left(), rect.bottom(), rect.width(), rect.height());
	return WWorldRectF(rect.left(), rect.top(), rect.width(), rect.height());
}

QPointF transform(const WWorldPointF& point)
{
	return QPointF(point.x(), point.y());
}

WWorldPointF transform(const QPointF& point)
{
	return WWorldPointF(point.x(), point.y());
}

QColor transform(const WColor& color)
{
	return QColor(color.red(), color.green(), color.blue(), color.alpha());
}

WColor transform(const QColor& color)
{
	return WColor(color.red(), color.green(), color.blue(), color.alpha());
}

QLineF transform(const WWorldLineF& line)
{
	return QLineF(line.x1(), line.y1(), line.x2(), line.y2());
}

WWorldLineF transform(const QLineF& line)
{
	return WWorldLineF(line.x1(), line.y1(), line.x2(), line.y2());
}

QPixmap transform(const WPixmap& pixmap)
{
	return QPixmap(pixmap);
}

WPixmap transform(const QPixmap& pixmap)
{
	return WPixmap(pixmap);
}

QSizeF transform(const WWorldSizeF& size)
{
	return QSizeF(size.width(), size.height());
}

WWorldSizeF transform(const QSizeF& size)
{
	return WWorldSizeF(size.width(), size.height());
}

WWorldPoint transform( const QPoint& point )
{
	return WWorldPoint(point.x(), point.y());
}

QPoint transform( const WWorldPoint& point )
{
	return QPoint(point.x(), point.y());
}
