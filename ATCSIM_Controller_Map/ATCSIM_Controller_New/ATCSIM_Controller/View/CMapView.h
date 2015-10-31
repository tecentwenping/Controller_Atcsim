#ifndef _MapView_H
#define _MapView_H

#include "wmapwidget.h"
#include "wgraphicsscene.h"
#include "qevent.h"

#include <boost/signals2.hpp>
using namespace boost;
using namespace boost::signals2;



//定义显示地图的窗口
class CMapView: public WMapWidget
{
public:
	typedef signal<void(CMapView*, double)> sigtype_updateRange;
	typedef signal<void(const CMapView*)> sigtype_initialize;
	typedef signal<void(CMapView*, const WWorldPoint&, const WWorldPoint&)> sigtype_addLocalScale;
public:
	 explicit CMapView(WGraphicsScene* scene);
 	~CMapView();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
 	virtual void wheelEvent(QWheelEvent* event);

private slots:
	void scale_value(double dscale);
	void telemeterFinished(WGraphicsItem* item);

public:
	sigtype_updateRange      m_sig_range;
	sigtype_initialize m_sig_initialize;
	sigtype_addLocalScale m_sig_localScale;

private:
	bool m_bEnableOnce;
	QPoint m_RightPressPoint;//记录右键压下时的坐标点
};




#endif