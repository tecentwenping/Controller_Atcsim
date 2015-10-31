#include "../wdllexport.h"
#include "wgraphicschange.h"

WGraphicsChange::WGraphicsChange(Type typ, WGraphicsItem* item) : _type(typ), _item(item)
{
}

WGraphicsChange::Type WGraphicsChange::type() const
{
	return _type;
}

WGraphicsItem* WGraphicsChange::item() const
{
	return _item;
}

void WGraphicsChange::setType(Type typ)
{
	_type = typ;
}

void WGraphicsChange::setItem(WGraphicsItem* item)
{
	_item = item;
}