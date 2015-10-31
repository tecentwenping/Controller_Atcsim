#ifndef _WARC_CREATOR_H_
#define _WARC_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class WGraphicsArcItem;
class WGraphicsRectItem;

class MAPAPI WArcCreator : public WDefaultCreator
{
public:
	explicit WArcCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

private:
	void clear();

private:
	int _step;
	WGraphicsArcItem* _item;
	WGraphicsRectItem* _helperItem;
};

#endif