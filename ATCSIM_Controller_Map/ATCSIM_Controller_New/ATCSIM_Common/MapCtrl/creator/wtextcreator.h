#ifndef _WTEXT_CREATOR_H_
#define _WTEXT_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class MAPAPI WTextCreator : public WDefaultCreator
{
public:
	explicit WTextCreator(WGraphicsScene* scene);

	virtual void start();
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
};

#endif