#include "../wdllexport.h"
#include "wcreatorsettings.h"

void WCreatorSettings::setLayer(int layer)
{
	layer_ = layer;
}

void WCreatorSettings::setBrush(const WBrush& brush)
{
	brush_ = brush;
}

void WCreatorSettings::setPen(const WPen& pen)
{
	pen_ = pen;
}

void WCreatorSettings::setFont(const WFont& font)
{
	font_ = font;
}

void WCreatorSettings::set(int layer, const WBrush& brush, const WPen& pen, const WFont& font)
{
	setLayer(layer);
	setBrush(brush);
	setPen(pen);
	setFont(font);
	setPointType(0);
}

void WCreatorSettings::reset()
{
	set(0, WBrush(), WPen(), WFont());
}

int WCreatorSettings::layer() const
{
	return layer_;
}

WBrush WCreatorSettings::brush() const
{
	return brush_;
}

WPen WCreatorSettings::pen() const
{
	return pen_;
}

WFont WCreatorSettings::font() const
{
	return font_;
}

WCreatorSettings& WCreatorSettings::instance()
{
	static WCreatorSettings creatorSettings;
	return creatorSettings;
}

/**
\brief      setPointType
\Access    public 
\param  int pointType
\retval     void
\remark     
*/
void WCreatorSettings::setPointType( int pointType )
{
	pointType_ = pointType;
}

/**
\brief      pointType
\Access    public 
\retval     int
\remark     
*/
int WCreatorSettings::pointType() const
{
	return pointType_;
}
