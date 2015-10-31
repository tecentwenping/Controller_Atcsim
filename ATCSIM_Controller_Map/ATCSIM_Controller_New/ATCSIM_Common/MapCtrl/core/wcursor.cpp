#include "../wdllexport.h"
#include "wcursor.h"

WCursor::WCursor(Ws::CursorShape shape) : _shape(shape)
{
}

Ws::CursorShape WCursor::shape() const
{
	return _shape;
}

void WCursor::setShape(Ws::CursorShape shape)
{
	_shape = shape;
}