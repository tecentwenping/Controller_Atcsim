#ifndef CHILDMAPVIEW_H
#define CHILDMAPVIEW_H

#include <boost/signals2.hpp>
using namespace boost;
using namespace boost::signals2;

#include "wmapwidget.h"
#include "wgraphicsscene.h"
#include "qevent.h"
#include "CMapView.h"

class ChildMapView : public CMapView
{
	Q_OBJECT

public:
	explicit ChildMapView(WGraphicsScene *scne);
	~ChildMapView();
protected:
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	
};

#endif // CHILDMAPVIEW_H
