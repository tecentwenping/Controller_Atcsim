#include "../wdllexport.h"
#include "wfont.h"

static const int DEFAULT_POINT_SIZE = 14; //7

WFont::WFont(const std::string& family, int pointSize, int weight, bool italic)
: _family(family), _point_size(pointSize > 0 ? pointSize : DEFAULT_POINT_SIZE), _weight(weight > 0 ? weight : Normal), _italic(italic), 
_underline(false), _strike_out(false), _kerning(false)
{
}

std::string WFont::family() const
{
	return _family;
}

int WFont::pointSize() const
{
	return _point_size;
}

int WFont::weight() const
{
	return _weight;
}

bool WFont::italic() const
{
	return _italic;
}

bool WFont::underline() const
{
	return _underline;
}

bool WFont::strikeOut() const
{
	return _strike_out;
}

bool WFont::kerning() const
{
	return _kerning;
}

bool WFont::bold() const
{
	return _weight > Normal;
}

void WFont::setFamily(const std::string& family)
{
	_family = family;
}

void WFont::setPointSize(int pointSize)
{
	_point_size = (pointSize > 0 ? pointSize : DEFAULT_POINT_SIZE);
}

void WFont::setWeight(int weight)
{
	_weight = (weight > 0 ? weight : Normal);
}

void WFont::setItalic(bool enable)
{
	_italic = enable;
}

void WFont::setUnderline(bool enable)
{
	_underline = enable;
}

void WFont::setStrikeOut(bool enable)
{
	_strike_out = enable;
}

void WFont::setKerning(bool enable)
{
	_kerning = enable;
}

void WFont::setBold(bool enable)
{
	_weight = (enable ? Bold : Normal);
}

bool WFont::equal(const WFont& other) const
{
	return _family == other._family
		&& _point_size == other._point_size
		&& _weight == other._weight
		&& _italic == other._italic
		&& _underline == other._underline
		&& _strike_out == other._strike_out
		&& _kerning == other._kerning;
}