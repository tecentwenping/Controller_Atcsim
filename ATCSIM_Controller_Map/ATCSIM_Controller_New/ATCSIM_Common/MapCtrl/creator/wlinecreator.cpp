#include "../wdllexport.h"
#include "wlinecreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wworldrect.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicslineitem.h"

WLineCreator::WLineCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0)
{
}

void WLineCreator::clear()
{
	_step = 0;
	_item = 0;
}

void WLineCreator::start()
{
	clear();
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select line's start point or press right button to cancel");
}

void WLineCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	if (_step == 0)
	{
		emit geometry(cell_format(event->scenePos()));
	}
	else if (_step == 1)
	{
		WWorldLineF line = _item->line();
		WWorldPointF pos = event->scenePos();
		scene()->attachPoint(pos, &pos);
		line.setP2(pos);
		_item->setLine(line, true);
		emit geometry(cell_format(*_item));
	}
}

void WLineCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		if (_item)
		{
			scene()->currentLayer()->removeItem(_item, true);
		}
		emit finished(0);
		clear();
	}
	else if (event->button() == Ws::LeftButton)
	{
		if (_step == 0)
		{
			WWorldPointF pos = event->scenePos();
			scene()->attachPoint(pos, &pos);
			WWorldLineF line(pos, pos+WWorldPointF(5, -5));
			_item = scene()->currentLayer()->addLine(line, WCreatorSettings::instance().pen(), true);
			emit geometry(cell_format(*_item));
			emit tip("press left button to select line's end point or press right button to cancel");
			++_step;	
		}
		else if (_step == 1)
		{
			emit finished(_item);
			clear();
		}
	}
}