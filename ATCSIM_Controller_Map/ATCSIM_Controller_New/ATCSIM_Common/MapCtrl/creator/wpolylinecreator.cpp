#include "../wdllexport.h"
#include "wpolylinecreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicslineitem.h"
#include "../core/wgraphicspolylineitem.h"

inline static QString tip_string(int step)
{
	return QString().sprintf("1. press left button to select polyline's %dth point\n"
		"2. double click left button  to select polyline's\n    %dth point and finish editing polyline\n"
		"3. press right button to cancel", step+1, step+1);
}

WPolylineCreator::WPolylineCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0), _helperItem(0)
{
}

void WPolylineCreator::clear()
{
	_step = 0;
	_item = 0;
	_helperItem = 0;
	_polyline.clear();
}

void WPolylineCreator::start()
{
	clear();
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip(tip_string(_step));
}

void WPolylineCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();
	if (_step > 0)
	{
		scene()->attachPoint(pos, &pos);
		WWorldLineF line(*_polyline.rbegin(), pos);
		if (!_helperItem)
		{
			_helperItem = scene()->currentLayer()->addLine(line, WPen(Ws::DashLine, WColor(0, 0, 255), 1.0), true);
			_helperItem->showArraw(false);
		}
		else
		{
			_helperItem->setLine(line, true);
		}
	}
	emit geometry((_item ? cell_format(*_item) : QString()) + cell_format(pos));
}

void WPolylineCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
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
		scene()->attachPoint(pos, &pos);
		_polyline.push_back(pos);
		if (_step == 0)
		{
			_item = scene()->currentLayer()->addPolyline(_polyline, WCreatorSettings::instance().pen(), true);
		}
		else
		{
			_item->setPolyline(_polyline, true);
		}
		emit tip(tip_string(++_step));
		emit geometry(cell_format(*_item));
	}
}

void WPolylineCreator::mouseDoubleClickEvent(WGraphicsSceneMouseEvent*)
{
	scene()->currentLayer()->removeItem(_helperItem, true);
	
	if (_polyline.size() < 2)
	{
		scene()->currentLayer()->removeItem(_item, true);
		emit finished(0);
	}
	else
	{
		emit finished(_item);
	}

	clear();
}