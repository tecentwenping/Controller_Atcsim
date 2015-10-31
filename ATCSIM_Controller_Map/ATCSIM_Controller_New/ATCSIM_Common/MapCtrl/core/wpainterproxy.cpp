#include "../wdllexport.h"
#include "wpainter.h"
#include "wpainterproxy.h"

WPainterProxy::WPainterProxy(WPainter* painter) : _painter(painter)
{
	if (_painter)
	{
		_painter->save();
	}
}

WPainterProxy::~WPainterProxy()
{
	if (_painter)
	{
		_painter->restore();
	}
}

WPainter* WPainterProxy::painter() const
{
	return _painter;
}