#ifndef _WRECT_CREATOR_H_
#define _WRECT_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class WGraphicsRectItem;

class MAPAPI WRectCreator : public WDefaultCreator
{
public:
	explicit WRectCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WGraphicsRectItem* _item;
};

#endif