#include "childmapview.h"

ChildMapView::ChildMapView( WGraphicsScene *scne )
:CMapView(scne)
{
     setEnableWheelScale(true);
}

ChildMapView::~ChildMapView()
{

}

void ChildMapView::mouseMoveEvent( QMouseEvent* event )
{

}

void ChildMapView::mousePressEvent( QMouseEvent* event )
{
	if(Qt::LeftButton==event->button())
	{
		parentWidget()->setFocus();
	}

}

void ChildMapView::mouseReleaseEvent( QMouseEvent* event )
{

}

void ChildMapView::wheelEvent( QWheelEvent* event )
{
	
	WMapWidget::wheelEvent(event);
}
