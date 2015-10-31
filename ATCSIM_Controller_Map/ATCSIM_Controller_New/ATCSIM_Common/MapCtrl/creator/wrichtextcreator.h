#ifndef _WRICH_TEXT_CREATOR_H_
#define _WRICH_TEXT_CREATOR_H_

#include "../wdllimport.h"
#include "wdefaultcreator.h"

class MAPAPI WRichTextCreator : public WDefaultCreator
{
public:
	explicit WRichTextCreator(WGraphicsScene* scene);

	virtual void start();
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
};

#endif