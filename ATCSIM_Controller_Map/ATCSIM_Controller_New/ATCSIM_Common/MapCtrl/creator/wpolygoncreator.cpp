#include "../wdllexport.h"
#include "wcreatorsettings.h"
#include "wpolygoncreator.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicslineitem.h"
#include "../core/wgraphicspolygonitem.h"

inline static QString tip_string(int step)
{
	return QString().sprintf("1. press left button to select polygon's %dth point\n"
		"2. double click left button  to select polygon's\n    %dth point and finish editing polygon\n"
		"3. press right button to cancel", step+1, step+1);
}

WPolygonCreator::WPolygonCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0), 
	_helperItem1(0), _helperItem2(0)
{
}

void WPolygonCreator::clear()
{
	_step = 0;
	_item = 0;
	_helperItem1 = 0;
	_helperItem2 = 0;
	_polygon.clear();
}

void WPolygonCreator::start()
{
	clear();
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip(tip_string(_step));
}

void WPolygonCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();
	if (_step > 0)
	{
		scene()->attachPoint(pos, &pos);
		WWorldLineF line1(pos, _polygon[_step-1]);
		WWorldLineF line2(pos, _polygon[0]);
		if (!_helperItem1 || !_helperItem2)
		{
			_helperItem1 = scene()->currentLayer()->addLine(line1, WPen(Ws::DashLine, WColor(0, 0, 255), 1.0), true);
			_helperItem2 = scene()->currentLayer()->addLine(line2, WPen(Ws::DashLine, WColor(0, 0, 255), 1.0), true);
			_helperItem1->showArraw(false, true);
			_helperItem2->showArraw(false, true);
		}
		else
		{
			_helperItem1->setLine(line1, true);
			_helperItem2->setLine(line2, true);
		}
	}
	emit geometry((_item ? cell_format(*_item) : QString()) + cell_format(pos));
}

void WPolygonCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		if (_item)
		{
			scene()->currentLayer()->removeItem(_item, true);
			scene()->currentLayer()->removeItem(_helperItem1, true);
			scene()->currentLayer()->removeItem(_helperItem2, true);
		}
		emit finished(0);
		clear();
	}
	else if (event->button() == Ws::LeftButton)
	{
		WWorldPointF pos = event->scenePos();
		scene()->attachPoint(pos, &pos);

		if (_step == 0)
		{
			_polygon.resize(4, pos);
			const WCreatorSettings& settings = WCreatorSettings::instance();
			_item = scene()->currentLayer()->addPolygon(_polygon, settings.pen(), settings.brush(), true);
		}
		else
		{
			if (_polygon.size() < static_cast<unsigned>(_step + 2))
			{
				_polygon.push_back(*_polygon.begin());
			}
			_polygon[_step] = pos;
			_item->setPolygon(_polygon, true);
		}
		
		emit tip(tip_string(++_step));
		emit geometry(cell_format(*_item));
	}
}

void WPolygonCreator::mouseDoubleClickEvent(WGraphicsSceneMouseEvent*)
{
	scene()->currentLayer()->removeItem(_helperItem1, true);
	scene()->currentLayer()->removeItem(_helperItem2, true);

	emit finished(_item);
	clear();
}