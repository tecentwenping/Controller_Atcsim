#include "../wdllexport.h"
#include "wrichtextcreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicsrichtextitem.h"

WRichTextCreator::WRichTextCreator(WGraphicsScene* scene) : WDefaultCreator(scene)
{
}

void WRichTextCreator::start()
{
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select rich text's start point or press right button to cancel");
}

void WRichTextCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	emit geometry(cell_format(event->scenePos()));
}

void WRichTextCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		emit finished(0);
	}
	else if (event->button() == Ws::LeftButton)
	{
		emit finished(scene()->currentLayer()->addRichText(event->scenePos(), "<b><i>type rich text here ...</b></i>", true));
	}
}