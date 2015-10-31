#include "CMapView.h"
#include "MainApp.h"
#include "CMainCallbackLogic.h"
#include "guitransform.h"
#include "CSimMap.h"
#include "MapManager.h"
CMapView::CMapView(WGraphicsScene* scene):WMapWidget(scene)
{
	setBackgroundColor(QColor(150, 150, 140));
	setEnableDrag(true);
	setEnableWheelScale(true);
	setAutoFillBackground(true);
	/*int iScreenWidth = theData::instance().GetConfigManager()->GetSystemPara()->GetScreenWidth();
	int iScreenHeight = theData::instance().GetConfigManager()->GetSystemPara()->GetScreenHeight();*/
	m_bEnableOnce = true;
	connect(this, SIGNAL(scaled(double)), this, SLOT(scale_value(double)));
}


CMapView::~CMapView()
{

}

void CMapView::mousePressEvent(QMouseEvent* event)
{

	//鼠标点击地图时，隐藏部分菜单窗口
	if (Qt::LeftButton == event->button())
	{
		//获取焦点来响应键盘快捷键
		parentWidget()->setFocus();

	}
	
	if (Qt::RightButton == event->button())
	{
		
			scene()->defaultLayer()->setEditable(true);
			m_RightPressPoint = event->pos();
		
	}


	if (Qt::MidButton & event->buttons())
	{
	}
	theApp::instance().GetMainCallbackLogic()->ProcessMousePressEvent(event);
 	WMapWidget::mousePressEvent(event);
}

void CMapView::wheelEvent(QWheelEvent* event)
{
	
	WMapWidget::wheelEvent(event);
	theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->UpdateMap();
}


void CMapView::scale_value(double dscale)
{
	m_sig_range(this, dscale);
}

/**
\brief      telemeterFinished
\Access    private 
\param  WGraphicsItem * item
\retval     void
\remark     
*/
void CMapView::telemeterFinished( WGraphicsItem* item )
{
// 	Q_UNUSED(item)
// 
// 	if (item != NULL)
// 	{
// 		theApp::instance().GetMapManagerPtr()->GetGlyphManagerPtr()->AddGlyph(GLYPH_TELEMETER, item);
// 	}
// 
// 	m_telCreator = NULL;
// 
// 	scene()->defaultLayer()->setEditable(false);
}

/**
\brief      mouseMoveEvent
\Access    virtual protected 
\param  QMouseEvent * event
\retval     void
\remark     
*/
void CMapView::mouseMoveEvent( QMouseEvent* event )
{
	

	theApp::instance().GetMainCallbackLogic()->ProcessMouseMoveEvent(event);
	WMapWidget::mouseMoveEvent(event);

}

/**
\brief      mouseReleaseEvent
\Access    virtual protected 
\param  QMouseEvent * event
\retval     void
\remark     
*/
void CMapView::mouseReleaseEvent( QMouseEvent* event )
{
	//m_telCreator = NULL;
	//m_bEnableOnce = true;

	//地图局部放大
	if (Qt::RightButton == event->button())
	{
		m_sig_localScale(this, transform(m_RightPressPoint), transform(event->pos()));
	}

// 	else if (Qt::MidButton == event->button())
// 	{
// 		theApp::instance().GetMapMangerPtr()->GetGlyphCreatorPtr()->DeleteLongLatInfo(WWorldPointF(event->pos().x(), event->pos().y()));
// 	}

	WMapWidget::mouseReleaseEvent(event);

	//m_frameCreator = NULL;
}

/**
\brief      paintEvent
\Access    virtual protected 
\param  QPaintEvent * event
\retval     void
\remark     
*/
void CMapView::paintEvent( QPaintEvent* event )
{
	//g_eplan_state.lock();
	//RUNNING_STATUS status = theApp::instance().GetPlanStatus();
	
	//if (status != END)
	//{
		WMapWidget::paintEvent(event);
	//}
	//g_eplan_state.unlock();
}


