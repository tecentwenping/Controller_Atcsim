#include "../wdllexport.h"
#include "wcolor.h"

WColor::WColor() : _r(0), _g(0), _b(0), _a(0xff)
{
}

WColor::WColor(WRgb color) :
			_a(static_cast<unsigned char>(color >> 24)),
			_r(static_cast<unsigned char>(color >> 16)),
			_g(static_cast<unsigned char>(color >> 8)),
			_b(static_cast<unsigned char>(color >> 0))
{
}

WColor::WColor(int r, int g, int b, int a) : 
			_a(static_cast<unsigned char>(a)),
			_r(static_cast<unsigned char>(r)),
			_g(static_cast<unsigned char>(g)),
			_b(static_cast<unsigned char>(b))
{
}

int WColor::red() const
{
	return _r;
}

int WColor::green() const
{
	return _g;
}

int WColor::blue() const
{
	return _b;
}

int WColor::alpha() const
{
	return _a;
}

WRgb WColor::rgb() const
{
	return 0xffu << 24
		| static_cast<unsigned int>(_r) << 16
		| static_cast<unsigned int>(_g) << 8
		| static_cast<unsigned int>(_b) << 0;
}

WRgb WColor::rgba() const
{
	return static_cast<unsigned int>(_a) << 24
		| static_cast<unsigned int>(_r) << 16
		| static_cast<unsigned int>(_g) << 8
		| static_cast<unsigned int>(_b) << 0;
}

WRgb WColor::colorref() const
{
	return static_cast<unsigned int>(_b) << 16
		| static_cast<unsigned int>(_g) << 8
		| static_cast<unsigned int>(_r) << 0;
}

void WColor::setRed(int r)
{
	_r = static_cast<unsigned char>(r);
}

void WColor::setGreen(int g)
{
	_g = static_cast<unsigned char>(g);
}

void WColor::setBlue(int b)
{
	_b = static_cast<unsigned char>(b);
}

void WColor::setAlpha(int a)
{
	_a = static_cast<unsigned char>(a);
}

void WColor::setRgb(WRgb color)
{
	_a = static_cast<unsigned char>(0xff);
	_r = static_cast<unsigned char>(color >> 16);
	_g = static_cast<unsigned char>(color >> 8);
	_b = static_cast<unsigned char>(color >> 0);
}

void WColor::setRgba(WRgb color)
{
	_a = static_cast<unsigned char>(color >> 24);
	_r = static_cast<unsigned char>(color >> 16);
	_g = static_cast<unsigned char>(color >> 8);
	_b = static_cast<unsigned char>(color >> 0);
}

void WColor::setRgb(int r, int g, int b, int a)
{
	_a = static_cast<unsigned char>(a);
	_r = static_cast<unsigned char>(r);
	_g = static_cast<unsigned char>(g);
	_b = static_cast<unsigned char>(b);
}

WColor WColor::opposite() const
{
	return WColor(~rgba());
}

bool WColor::equal(const WColor& other) const
{
	return _r == other._r
		&& _g == other._g
		&& _b == other._b
		&& _a == other._a;
}

WColor WColor::darker(double factor) const
{
	return WColor(_r, _g, _b, static_cast<unsigned char>(_a * factor));
}

WColor WColor::lighter(double factor) const
{
	return WColor(_r, _g, _b, static_cast<unsigned char>(_a / factor));
}