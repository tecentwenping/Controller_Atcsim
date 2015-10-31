#include "../wdllexport.h"
#include "wpointcreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicspointitem.h"

WPointCreator::WPointCreator(WGraphicsScene* scene) : WDefaultCreator(scene)
{
}

void WPointCreator::start()
{
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select fix point or press right button to cancel");
}

void WPointCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	emit geometry(cell_format(event->scenePos()));
}

void WPointCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		emit finished(0);
	}
	else if (event->button() == Ws::LeftButton)
	{
		WWorldPointF pos = event->scenePos();
		scene()->attachPoint(pos, &pos);
		emit finished(scene()->currentLayer()->addPoint(pos, WCreatorSettings::instance().pen(), true));
	}
}