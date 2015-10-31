#include "CMainCallbackLogic.h"
#include "MapManager.h"
#include "MainApp.h"
#include "CSimMap.h"
#include "CGlyphUpdater.h"
#include "CGlyphCreator.h"
#include "CMapView.h"
CMainCallBackLogic::CMainCallBackLogic()

{
}

CMainCallBackLogic::~CMainCallBackLogic()
{

}

void CMainCallBackLogic::ProcessKeyEvent( QKeyEvent *event )
{
	CMapView *pMainView = theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->GetMainMapView();
	if(event->key() == Qt::Key_4)
	{
		QPoint mapPos = pMainView->mapFromGlobal(QCursor::pos());
		theApp::instance().GetMapMangerPtr()->GetGlyphCreatorPtr()->AddLongLatInfo(WWorldPointF(mapPos.x(),mapPos.y()));
	}

} 

void CMainCallBackLogic::ProcessMouseMoveEvent( QMouseEvent *event )
{
	theApp::instance().GetMapMangerPtr()->GetGlyphCreatorPtr()->UpdateMouseCoordinate(event->posF().x(),event->posF().y());
	theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->UpdateMap();

 
}

void CMainCallBackLogic::ProcessMousePressEvent( QMouseEvent *event )
{
	theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->UpdateMap();

}
