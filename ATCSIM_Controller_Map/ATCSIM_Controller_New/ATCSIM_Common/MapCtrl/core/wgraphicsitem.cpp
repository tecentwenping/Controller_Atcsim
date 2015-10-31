#include "../wdllexport.h"
#include "wpen.h"
#include "wevent.h"
#include "wbrush.h"
#include "wserialize.h"
#include "wgraphicsitem.h"
#include "wgraphicsscene.h"

//支持动态创建的实现宏
RTTI_IMPL(WGraphicsItem)

MAPAPI const double WGraphicsItem::CP_ROTATE_HEADER = 25.0;
MAPAPI const double WGraphicsItem::CP_RADIUS = 6.0;
MAPAPI const WPen WGraphicsItem::CP_PEN = WPen(Ws::SolidLine, WColor(130, 136, 143), 1.0);
MAPAPI const WPen WGraphicsItem::CP_SEL_PEN = WPen(Ws::SolidLine, WColor(0, 0, 255), 1.0);
MAPAPI const WBrush WGraphicsItem::CP_BRUSH = WBrush(WColor(206, 247, 250));
MAPAPI const WPen WGraphicsItem::HOVER_PEN = WPen(Ws::SolidLine, WColor(58, 97, 141), 2.0);
MAPAPI const WBrush WGraphicsItem::ROTATE_BRUSH = WBrush(WColor(141, 234, 63));
MAPAPI const double WGraphicsItem::ATTACH_DISTANCE = 10.0;
MAPAPI const double WGraphicsItem::ATTACH_DISTANCE_SQUARE = WGraphicsItem::ATTACH_DISTANCE * WGraphicsItem::ATTACH_DISTANCE;
MAPAPI const WPen WGraphicsItem::DRAG_PEN = WPen(Ws::DashLine);

char* WItemData::serialize(char* buf) const
{
	return (WSerializer(buf) << type << layer).value();
}

const char* WItemData::unserialize(const char* buf)
{
	return (WUnserializer(buf) >> type >> layer).value();
}

size_t WItemData::serialize_size() const
{
	return (WSizeHelper() << type << layer).value();
}

WGraphicsItem::WGraphicsItem(data_type* d) : _data(d ? d : new data_type),
	_enabled(true), _visible(true), _selectable(true), _selected(false), _movable(true), _layer(0)
{
}

WGraphicsItem::~WGraphicsItem()
{
	_data->destroy();
}

void WGraphicsItem::destroy()
{
	delete this;
}

void WGraphicsItem::contextMenuEvent(WContextMenuEvent*)
{

}

void WGraphicsItem::dragEnterEvent(WGraphicsSceneDragDropEvent*)
{

}

void WGraphicsItem::dragLeaveEvent(WGraphicsSceneDragDropEvent*)
{

}

void WGraphicsItem::dragMoveEvent(WGraphicsSceneDragDropEvent*)
{

}

void WGraphicsItem::dropEvent(WGraphicsSceneDragDropEvent*)
{

}

void WGraphicsItem::focusInEvent(WFocusEvent*)
{

}

void WGraphicsItem::focusOutEvent(WFocusEvent*)
{

}

void WGraphicsItem::hoverEnterEvent(WGraphicsSceneHoverEvent*)
{

}

void WGraphicsItem::hoverLeaveEvent(WGraphicsSceneHoverEvent*)
{

}

void WGraphicsItem::hoverMoveEvent(WGraphicsSceneHoverEvent*)
{

}

void WGraphicsItem::inputMethodEvent(WInputMethodEvent*)
{

}

void WGraphicsItem::keyPressEvent(WKeyEvent*)
{

}

void WGraphicsItem::keyReleaseEvent(WKeyEvent*)
{

}

void WGraphicsItem::mouseMoveEvent(WGraphicsSceneMouseEvent*)
{

}

void WGraphicsItem::mousePressEvent(WGraphicsSceneMouseEvent*)
{

}

void WGraphicsItem::mouseReleaseEvent(WGraphicsSceneMouseEvent*)
{

}

void WGraphicsItem::mouseDoubleClickEvent(WGraphicsSceneMouseEvent*)
{

}

void WGraphicsItem::wheelEvent(WGraphicsSceneWheelEvent*)
{

}

int WGraphicsItem::type() const
{
	return Type;
}

bool WGraphicsItem::isEnabled() const
{
	return _enabled;
}

bool WGraphicsItem::isVisible() const
{
	return _visible;
}

bool WGraphicsItem::isSelectable() const
{
	return _selectable;
}

bool WGraphicsItem::isSelected() const
{
	return _selected;
}

bool WGraphicsItem::isMovable() const
{
	return _movable;
}

bool WGraphicsItem::isTransformable() const
{
	return _transformable;
}

bool WGraphicsItem::isScalable() const
{
	return _scalable;
}

void WGraphicsItem::setEnabled(bool enabled)
{
	_enabled = enabled;
}

void WGraphicsItem::setVisible(bool visible, bool updating)
{
	_visible = visible;
	if (updating)
	{
		scene()->update(boundingRect());
	}
}

void WGraphicsItem::setSelectable(bool selectable)
{
	_selectable = selectable;
}

void WGraphicsItem::setSelected(bool selected)
{
	_selected = selected;
	if (selected)
	{
		scene()->setSelectedItem(this);
	}
	else
	{
		scene()->unsetSelectedItem(this);
	}
}

void WGraphicsItem::setMovable(bool movable)
{
	_movable = movable;
}

void WGraphicsItem::setTransformable(bool transformable)
{
	_transformable = transformable;
}

void WGraphicsItem::setScalable(bool scalable)
{
	_scalable = scalable;
}

WGraphicsLayer* WGraphicsItem::layer() const
{
	return _layer;
}

void WGraphicsItem::setLayer(WGraphicsLayer* layer)
{
	_layer = layer;
	_data->layer = _layer->layer();
}

WGraphicsScene* WGraphicsItem::scene() const
{
	return _layer ? _layer->scene() : 0;
}

WGraphicsItem::data_type* WGraphicsItem::data()
{
	return W_D();
}

const WGraphicsItem::data_type* WGraphicsItem::data() const
{
	return W_CD();
}

WItemData* WGraphicsItem::baseData()
{
	return _data;
}

const WItemData* WGraphicsItem::baseData() const
{
	return _data;
}

bool WGraphicsItem::attachPoint(const WWorldPointF&, WWorldPointF*) const
{
	return false;
}

void WGraphicsItem::requestContextMenu(Ws::ContextMenuFlags flags)
{
	scene()->requestContextMenu(flags);
}

void WGraphicsItem::onContextMenu(Ws::ContextMenuFlag)
{
}

void WGraphicsItem::translate(const WWorldPointF& offset, bool updating)
{
	if (updating)
	{
		WWorldRectF r = boundingRect();
		translate(offset);
		scene()->update(r | boundingRect());
	}
	else
	{
		translate(offset);
	}
}

WWorldRectF& WGraphicsItem::expand(WWorldRectF& r)
{
	r.adjust(-2*CP_RADIUS, -2*CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS);
	return r;
}

WWorldRectF WGraphicsItem::expanded(const WWorldRectF& r)
{
	return r.adjusted(-2*CP_RADIUS, -2*CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS);
}

bool WGraphicsItem::contains(const WWorldPointF&) const
{
	return false;
}

WGraphicsItem* WGraphicsItem::copy() const
{
	return 0;
}

void WGraphicsItem::translate(const WWorldPointF&)
{
}