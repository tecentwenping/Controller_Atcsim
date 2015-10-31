#include "../wdllexport.h"
#include "wserialize.h"
#include "wserializeimpl.h"

char* serialize_impl(char* buf, const WWorldPointF& point)
{
	return (WSerializer(buf) << point.x() << point.y()).value();
}

const char* unserialize_impl(const char* buf, WWorldPointF& point)
{
	double x = 0.0;
	double y = 0.0;
	buf = unserialize(buf, x);
	buf = unserialize(buf, y);
	point.setXY(x, y);
	return buf;
}

size_t serialize_size_impl(const WWorldPointF& point)
{
	return (WSizeHelper() << point.x() << point.y()).value();
}

char* serialize_impl(char* buf, const WWorldSizeF& size)
{
	return (WSerializer(buf) << size.width() << size.height()).value();
}

const char* unserialize_impl(const char* buf, WWorldSizeF& size)
{
	double w = 0.0;
	double h = 0.0;
	buf = unserialize(buf, w);
	buf = unserialize(buf, h);
	size.setWidth(w);
	size.setHeight(h);
	return buf;
}

size_t serialize_size_impl(const WWorldSizeF& size)
{
	return (WSizeHelper() << size.width() << size.height()).value();
}

char* serialize_impl(char* buf, const WWorldRectF& rect)
{
	return (WSerializer(buf) << rect.x() << rect.y() << rect.width() << rect.height()).value();
}

const char* unserialize_impl(const char* buf, WWorldRectF& rect)
{
	double x = 0.0;
	double y = 0.0;
	double w = 0.0;
	double h = 0.0;
	buf = unserialize(buf, x);
	buf = unserialize(buf, y);
	buf = unserialize(buf, w);
	buf = unserialize(buf, h);
	rect.setRect(x, y, w, h);
	return buf;
}

size_t serialize_size_impl(const WWorldRectF& rect)
{
	return (WSizeHelper() << rect.x() << rect.y() << rect.width() << rect.height()).value();
}

char* serialize_impl(char* buf, const WWorldLineF& line)
{
	return (WSerializer(buf) << line.p1() << line.p2()).value();
}

const char* unserialize_impl(const char* buf, WWorldLineF& line)
{
	WWorldPointF p1;
	WWorldPointF p2;
	buf = unserialize(buf, p1);
	buf = unserialize(buf, p2);
	line.setP1(p1);
	line.setP2(p2);
	return buf;
}

size_t serialize_size_impl(const WWorldLineF& line)
{
	return (WSizeHelper() << line.p1() << line.p2()).value();
}

char* serialize_impl(char* buf, const WColor& color)
{
	return (WSerializer(buf) << color.red() << color.green() << color.blue() << color.alpha()).value();
}

const char* unserialize_impl(const char* buf, WColor& color)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	buf = unserialize(buf, r);
	buf = unserialize(buf, g);
	buf = unserialize(buf, b);
	buf = unserialize(buf, a);
	color.setRgb(r, g, b, a);
	return buf;
}

size_t serialize_size_impl(const WColor& color)
{
	return (WSizeHelper() << color.red() << color.green() << color.blue() << color.alpha()).value();
}

char* serialize_impl(char* buf, const WBrush& brush)
{
	return (WSerializer(buf) << brush.color() << brush.style()).value();
}

const char* unserialize_impl(const char* buf, WBrush& brush)
{
	WColor color;
	Ws::BrushStyle style;
	buf = unserialize(buf, color);
	buf = unserialize(buf, style);
	brush.setColor(color);
	brush.setStyle(style);
	return buf;
}

size_t serialize_size_impl(const WBrush& brush)
{
	return (WSizeHelper() << brush.color() << brush.style()).value();
}

char* serialize_impl(char* buf, const WPen& pen)
{
	return (WSerializer(buf) << pen.style() << pen.color() << pen.width()).value();
}

const char* unserialize_impl(const char* buf, WPen& pen)
{
	Ws::PenStyle style;
	WColor color;
	double width;
	buf = unserialize(buf, style);
	buf = unserialize(buf, color);
	buf = unserialize(buf, width);
	pen.setStyle(style);
	pen.setColor(color);
	pen.setWidth(width);
	return buf;
}

size_t serialize_size_impl(const WPen& pen)
{
	return (WSizeHelper() << pen.style() << pen.color() << pen.width()).value();
}

char* serialize_impl(char* buf, const WFont& font)
{
	return (WSerializer(buf) << font.family() << font.pointSize() << font.weight() 
		<< font.italic() << font.underline() << font.strikeOut() << font.kerning()).value();
}

const char* unserialize_impl(const char* buf, WFont& font)
{
	std::string family;
	int pointSize = 0;
	int weight = 0;
	bool italic = false;
	bool underline = false;
	bool strikeOut = false;
	bool kerning = false;
	buf = unserialize(buf, family);
	buf = unserialize(buf, pointSize);
	buf = unserialize(buf, weight);
	buf = unserialize(buf, italic);
	buf = unserialize(buf, underline);
	buf = unserialize(buf, strikeOut);
	buf = unserialize(buf, kerning);
	font.setFamily(family);
	font.setPointSize(pointSize);
	font.setWeight(weight);
	font.setItalic(italic);
	font.setUnderline(underline);
	font.setStrikeOut(strikeOut);
	font.setKerning(kerning);
	return buf;
}

size_t serialize_size_impl(const WFont& font)
{
	return (WSizeHelper() << font.family() << font.pointSize() << font.weight() 
		<< font.italic() << font.underline() << font.strikeOut() << font.kerning()).value();
}