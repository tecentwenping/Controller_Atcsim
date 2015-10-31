#ifndef _WPOLYGON_CREATOR_H_
#define _WPOLYGON_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"
#include "../core/wworldpolygon.h"

class WGraphicsPolygonItem;
class WGraphicsLineItem;

class MAPAPI WPolygonCreator : public WDefaultCreator
{
public:
	explicit WPolygonCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WWorldPolygonF _polygon;
	WGraphicsPolygonItem* _item;
	WGraphicsLineItem* _helperItem1;
	WGraphicsLineItem* _helperItem2;
};

#endif