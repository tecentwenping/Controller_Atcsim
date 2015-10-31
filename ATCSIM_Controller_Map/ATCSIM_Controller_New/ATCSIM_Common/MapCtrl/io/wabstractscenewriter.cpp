#include <boost/foreach.hpp>
#include "../wdllexport.h"
#include "wabstractscenewriter.h"
#include "../core/wgraphicslayer.h"
#include "../core/wgraphicsscene.h"

WAbstractSceneWriter::~WAbstractSceneWriter()
{
}

void WAbstractSceneWriter::write(const WGraphicsScene* scene)
{
	writeBegin();

	std::vector<WGraphicsLayer*> layers = scene->layers();
	BOOST_FOREACH(WGraphicsLayer* layer, layers)
	{
		std::vector<WGraphicsItem*> items = layer->items();
		BOOST_FOREACH(WGraphicsItem* item, items)
		{
			writeImpl(item);
		}
	}

	writeEnd();
}

void WAbstractSceneWriter::writeBegin()
{
}

void WAbstractSceneWriter::writeEnd()
{
}