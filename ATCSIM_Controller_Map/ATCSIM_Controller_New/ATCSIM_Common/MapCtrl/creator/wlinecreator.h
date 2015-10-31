#ifndef _WLINE_CREATOR_H_
#define _WLINE_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class WGraphicsLineItem;

class MAPAPI WLineCreator : public WDefaultCreator
{
public:
	explicit WLineCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WGraphicsLineItem* _item;
};

#endif