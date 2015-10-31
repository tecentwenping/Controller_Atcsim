#ifndef _WELLIPSE_CREATOR_H_
#define _WELLIPSE_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class WGraphicsRectItem;
class WGraphicsEllipseItem;

class MAPAPI WEllipseCreator : public WDefaultCreator
{
public:
	explicit WEllipseCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WGraphicsEllipseItem* _item;
	WGraphicsRectItem* _helperItem;
};

#endif