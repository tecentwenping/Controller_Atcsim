#include "../wdllexport.h"
#include "wpen.h"

WPen::WPen() : _ps(Ws::SolidLine), _color(WColor(0, 0, 0)), _width(0.0)
{
}

WPen::WPen(Ws::PenStyle ps) : _ps(ps), _color(WColor(0, 0, 0)), _width(0)
{
}

WPen::WPen(const WColor& color) : _ps(Ws::SolidLine), _color(color), _width(0)
{
}

WPen::WPen(double width) : _ps(Ws::SolidLine), _color(WColor(0, 0, 0)), _width(width)
{
}

WPen::WPen(Ws::PenStyle ps, const WColor& color, double width) : _ps(ps), _color(color), _width(width)
{
}

Ws::PenStyle WPen::style() const
{
	return _ps;
}

WColor WPen::color() const
{
	return _color;
}

double WPen::width() const
{
	return _width;
}

void WPen::setStyle(Ws::PenStyle ps)
{
	_ps = ps;
}

void WPen::setColor(const WColor& color)
{
	_color = color;
}

void WPen::setWidth(double width)
{
	_width = width;
}

bool WPen::equal(const WPen& other) const
{
	return _ps == other._ps
		&& _color == other._color
		&& numeric_equal(_width, other._width);
}