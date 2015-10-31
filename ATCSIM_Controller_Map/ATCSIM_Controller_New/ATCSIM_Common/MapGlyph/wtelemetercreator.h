#ifndef _WTELEMETER_CREATOR_H_
#define _WTELEMETER_CREATOR_H_

#include "wdefaultcreator.h"
#include "wworldpoint.h"

class WGraphicsScene;
class WTelemeterGlyph;

class WTelemeterCreator : public WDefaultCreator
{
	Q_OBJECT
public:
	explicit WTelemeterCreator(WGraphicsScene* scene);

	virtual void start();
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	void setSavePoint(const WPointF& p);
private:
	void clear();
signals:
	void stepOver(WTelemeterGlyph*, int, const WPointF&);
	void start(WGraphicsItem*);
private:
	int _step;
	WTelemeterGlyph* _item;
	WPointF _savePoint;
};

#endif