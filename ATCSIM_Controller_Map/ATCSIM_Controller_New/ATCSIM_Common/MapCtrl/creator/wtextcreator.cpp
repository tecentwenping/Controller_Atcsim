#include <QInputDialog>
#include "../wdllexport.h"
#include "wtextcreator.h"
#include "wcreatorsettings.h"
#include "../gui/cellformat.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../core/wgraphicstextitem.h"

WTextCreator::WTextCreator(WGraphicsScene* scene) : WDefaultCreator(scene)
{
}

void WTextCreator::start()
{
	WGraphicsLayer* layer = scene()->addLayer(WCreatorSettings::instance().layer());
	layer->setEditable(true);
	scene()->setCurrentLayer(layer);
	emit tip("press left button to select text's start point or press right button to cancel");
}

void WTextCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	emit geometry(cell_format(event->scenePos()));
}

void WTextCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	if (event->button() == Ws::RightButton)
	{
		emit finished(0);
	}
	else if (event->button() == Ws::LeftButton)
	{
		const WCreatorSettings& settings = WCreatorSettings::instance();
		bool ok = false;
		static const QString defaultText("type text here ...");
		QString text = QInputDialog::getText(0, "Input Dialog", "Input Text : ", QLineEdit::Normal, defaultText, &ok);
		text = (ok ? text : defaultText);
		WGraphicsTextItem* item = scene()->currentLayer()->addText(event->scenePos(), text.toStdString());
		item->setFont(settings.font());
		item->setPen(settings.pen(), true);
		emit finished(item);
	}
}