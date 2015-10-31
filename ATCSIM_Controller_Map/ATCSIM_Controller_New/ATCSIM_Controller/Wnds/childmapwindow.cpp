#include "childmapwindow.h"

#include "childmapview.h"
#include <QVBoxLayout>

ChildMapWindow::ChildMapWindow( WGraphicsScene* s,QWidget *parent )
{
   m_pChildMapView=new ChildMapView(s);
   m_pScene=s;
   QVBoxLayout *vLayout=new QVBoxLayout;
   vLayout->setSpacing(0);
   vLayout->setMargin(0);
   vLayout->addWidget(m_pChildMapView);
   m_pChildMapView->reset();

}

ChildMapWindow::~ChildMapWindow()
{

}

ChildMapView* ChildMapWindow::GetChildMapView()
{
	return m_pChildMapView;

}

void ChildMapWindow::keyPressEvent( QKeyEvent *event )
{
	if (event->key() == Qt::Key_Home)
	{

		m_pChildMapView->reset();	
	}

	if (event->key() == Qt::Key_End)
	{
		m_pChildMapView->scale(1.2, true);
	}

	if (event->key() == Qt::Key_PageUp)
	{
		QPoint point = m_pChildMapView->mapFromGlobal(QCursor::pos());
		m_pChildMapView->setCenter(WWorldPointF(point.x(), point.y()));
	}

	if (event->key() == Qt::Key_PageDown)
	{	
		m_pChildMapView->scale(1/1.2, true);
	}

	//ÒÆ¶¯µØÍ¼¿ì½Ý¼ü
	if (event->key() == Qt::Key_Up)
	{
		m_pChildMapView->translate(WWorldPointF(0, 200));
	}

	if (event->key() == Qt::Key_Down)
	{
		m_pChildMapView->translate(WWorldPointF(0, -200));
	}

	if (event->key() == Qt::Key_Left)
	{
		m_pChildMapView->translate(WWorldPointF(200, 0));
	}

	if (event->key() == Qt::Key_Right)
	{
		m_pChildMapView->translate(WWorldPointF(-200, 0));
	}
	m_pScene->update();

}
