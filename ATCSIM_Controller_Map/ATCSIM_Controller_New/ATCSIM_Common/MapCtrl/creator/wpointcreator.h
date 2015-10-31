#ifndef _WPOINT_CREATOR_H_
#define _WPOINT_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class MAPAPI WPointCreator : public WDefaultCreator
{
public:
	explicit WPointCreator(WGraphicsScene* scene);

	virtual void start();
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
};

#endif