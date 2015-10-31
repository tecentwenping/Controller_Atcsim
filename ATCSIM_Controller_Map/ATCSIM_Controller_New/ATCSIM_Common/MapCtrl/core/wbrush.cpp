#include "../wdllexport.h"
#include "wbrush.h"

WBrush::WBrush() : _style(Ws::NoBrush), _color(WColor(0, 0, 0))
{
}

WBrush::WBrush(Ws::BrushStyle style) : _style(style), _color(WColor(0, 0, 0))
{
}

WBrush::WBrush(const WColor& color, Ws::BrushStyle style) : _style(style), _color(color)
{
}

Ws::BrushStyle WBrush::style() const
{
	return _style;
}

WColor WBrush::color() const
{
	return _color;
}

void WBrush::setStyle(Ws::BrushStyle style)
{
	_style = style;
}

void WBrush::setColor(const WColor& color)
{
	_color = color;
}

bool WBrush::equal(const WBrush& other) const
{
	return _style == other._style && _color == other._color;
}