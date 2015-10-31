#include "../wdllexport.h"
#include "wabstractscenereader.h"
#include "../core/wgraphicslayer.h"
#include "../core/wgraphicsscene.h"

WAbstractSceneReader::WAbstractSceneReader() : _scene(0)
{
}

WAbstractSceneReader::~WAbstractSceneReader()
{
}

void WAbstractSceneReader::itemAvailable(WGraphicsItem* item)
{
	if (_scene)
	{
		WGraphicsLayer* layer = _scene->addLayer(item->data()->layer);
		layer->addItem(item);
	}
}

void WAbstractSceneReader::read(WGraphicsScene* scene)
{
	_scene = scene;
	readImpl();
}

void WAbstractSceneReader::readBegin()
{
}

void WAbstractSceneReader::readEnd()
{
}