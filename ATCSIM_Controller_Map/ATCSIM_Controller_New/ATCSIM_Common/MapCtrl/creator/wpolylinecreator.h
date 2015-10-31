#ifndef _WPOLYLINE_CREATOR_H_
#define _WPOLYLINE_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"
#include "../core/wworldpolyline.h"

class WGraphicsPolylineItem;
class WGraphicsLineItem;

class MAPAPI WPolylineCreator : public WDefaultCreator
{
public:
	explicit WPolylineCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WWorldPolylineF _polyline;
	WGraphicsPolylineItem* _item;
	WGraphicsLineItem* _helperItem;
};

#endif