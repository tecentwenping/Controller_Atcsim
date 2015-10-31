#include "../wdllexport.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "wabstractgraphicsshapeitem.h"

RTTI_IMPL(WAbstractGraphicsShapeItem)

char* WAbstractShapeItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << brush << pen).value();
}

const char* WAbstractShapeItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> brush >> pen).value();
}

size_t WAbstractShapeItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << brush << pen).value();
}

WAbstractGraphicsShapeItem::WAbstractGraphicsShapeItem(const WBrush& brush, const WPen& pen) : 
	WGraphicsItem(new data_type(Type, brush, pen))
{
}

WAbstractGraphicsShapeItem::WAbstractGraphicsShapeItem(data_type* d) :
	WGraphicsItem(d ? d : new data_type)
{
}

WBrush WAbstractGraphicsShapeItem::brush() const
{
	return data()->brush;
}

WPen WAbstractGraphicsShapeItem::pen() const
{
	return data()->pen;
}

void WAbstractGraphicsShapeItem::setBrush(const WBrush& brush, bool update, bool opStack)
{
	if (data()->brush == brush)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WAbstractGraphicsShapeItem::setBrush, this, brush, true, false),
			WCmdFactory::create(&WAbstractGraphicsShapeItem::setBrush, this, data()->brush, true, false));
	}

	data()->brush = brush;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WAbstractGraphicsShapeItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (data()->pen == pen)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WAbstractGraphicsShapeItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WAbstractGraphicsShapeItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

int WAbstractGraphicsShapeItem::type() const
{
	return Type;
}

WAbstractGraphicsShapeItem::data_type* WAbstractGraphicsShapeItem::data()
{
	return W_D();
}

const WAbstractGraphicsShapeItem::data_type* WAbstractGraphicsShapeItem::data() const
{
	return W_CD();
}