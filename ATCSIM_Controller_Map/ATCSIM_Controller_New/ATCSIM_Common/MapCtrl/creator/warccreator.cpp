#include "../wdllexport.h"
#include "warccreator.h"
#include "wcreatorsettings.h"
#include "../core/wevent.h"
#include "../gui/cellformat.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicsarcitem.h"
#include "../core/wgraphicsrectitem.h"

WArcCreator::WArcCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0), _helperItem(0)
{
}

void WArcCreator::start()
{
	clear();
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select rectangle's top left point or press right button to cancel");
}

void WArcCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	if (_step == 0)
	{
		emit geometry(cell_format(event->scenePos()));
	}
	else if (_step == 1 && (event->buttons() & Ws::LeftButton))
	{
		WWorldRectF rect = _item->rect();
		WWorldPointF offset = event->scenePos() - rect.bottomRight();
		rect.adjust(0, offset.y(), offset.x(), 0);
		_item->setRect(rect, true);
		_helperItem->setRect(rect, true);
		emit geometry(cell_format(*_item));
	}
}

void WArcCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
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
			_item = scene()->currentLayer()->addArc(rect, 30, 150, WCreatorSettings::instance().pen(), true);
			_helperItem = scene()->currentLayer()->addRect(rect, 0.0, WPen(Ws::DashLine, WColor(0, 0, 255), 1.0), WBrush(), true);
			emit geometry(cell_format(*_item));
			emit tip("move mouse and release left button to select rectangle's bottom right point or press right button to cancel");
			++_step;	
		}
	}
}

void WArcCreator::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (_step == 1 && event->button() == Ws::LeftButton)
	{
		scene()->currentLayer()->removeItem(_helperItem, true);
		emit finished(_item);
		clear();
	}
}

void WArcCreator::clear()
{
	_step = 0;
	_item = 0;
	_helperItem = 0;
}