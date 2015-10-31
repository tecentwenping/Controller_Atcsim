#include "../wdllexport.h"
#include "wellipsecreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicsrectitem.h"
#include "../core/wgraphicsellipseitem.h"

WEllipseCreator::WEllipseCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0), _helperItem(0)
{
}

void WEllipseCreator::start()
{
	clear();
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select rectangle's top left point or press right button to cancel");
}

void WEllipseCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	if (_step == 0)
	{
		emit geometry(cell_format(event->scenePos()));
	}
	else if (_step == 1 && (event->buttons() & Ws::LeftButton))
	{
		WWorldRectF rect = _item->rect();
		WWorldPointF offset = event->scenePos() - rect.bottomRight();
		_item->setRect(rect.adjusted(0, offset.y(), offset.x(), 0), true);
		_helperItem->setRect(rect.adjusted(0, offset.y(), offset.x(), 0), true);
		emit geometry(cell_format(*_item));
	}
}

void WEllipseCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		if (_item)
		{
			scene()->currentLayer()->removeItem(_item, true);
			scene()->currentLayer()->removeItem(_helperItem, true);
		}
		emit finished(0);
		clear();
	}
	else if (event->button() == Ws::LeftButton)
	{
		WWorldPointF pos = event->scenePos();
		if (_step == 0)
		{
			WWorldRectF rect(pos.x()-20, pos.y(), 20, 20);
			const WCreatorSettings& settings = WCreatorSettings::instance();
			_item = scene()->currentLayer()->addEllipse(rect, settings.pen(), settings.brush(), true);
			_helperItem = scene()->currentLayer()->addRect(rect, 0.0, WPen(Ws::DashDotDotLine, WColor(0, 0, 255), 1.0), WBrush(), true);
			emit geometry(cell_format(*_item));
			emit tip("move mouse and release left button to select rectangle's bottom right point or press right button to cancel");
			++_step;	
		}
	}
}

void WEllipseCreator::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (_step == 1 && event->button() == Ws::LeftButton)
	{
		scene()->currentLayer()->removeItem(_helperItem, true);
		emit finished(_item);
		clear();
	}
}

void WEllipseCreator::clear()
{
	_step = 0;
	_item = 0;
	_helperItem = 0;
}