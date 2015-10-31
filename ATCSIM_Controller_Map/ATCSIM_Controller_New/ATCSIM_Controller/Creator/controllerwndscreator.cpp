#include "controllerwndscreator.h"
#include "childmapwindow.h"
#include "CSimMap.h"
#include "wgraphicsscene.h"
#include "totalbasedata.h"
#include "airport_data_objs.h"
#include "coordinate.h"
#include "wrunwayglyph.h"
#include "wglyphidentity.h"
#include "getdatafromdb.h"
#include "CMapView.h"
#include "wunclosedlineglyph.h"
#include "wnavpointglyph.h"
#include "wgateglyph.h"
#include "wpainter.h"
#include "wqtpainter.h"
#include "WndsManager.h"
#include "MapManager.h"
#include "MainApp.h"
#include <iostream>
#include <QMainWindow>
#include <QVBoxLayout>
#include "./boost/shared_ptr.hpp"
ControllerWndsCreator::ControllerWndsCreator( QMainWindow *pMainWindow )
:WndsCreator(pMainWindow)
{
}

ControllerWndsCreator::ControllerWndsCreator( boost::shared_ptr<CWndsManager> pWndsManager,QMainWindow* pMainWindow )
:WndsCreator(pWndsManager,pMainWindow)
{
     m_pMainWindow = pMainWindow;
}
ControllerWndsCreator::~ControllerWndsCreator()
{

}

void ControllerWndsCreator::InitAppWnds()
{
	WGraphicsScene *scene = theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->GetMapScene().get();
    ChildMapWindow* childMapWindow = new ChildMapWindow(scene,m_pMainWindow);
	m_pWndsManager->AddSimWnd(WND_SECONDMAP,childMapWindow);
	QWidget *pMapWnd=new QWidget(m_pMainWindow);
	QVBoxLayout* pHLayout=new QVBoxLayout;
	pHLayout->addWidget(theApp::instance().GetMapMangerPtr()->GetSimMapPtr()->GetMainMapView(),1);
	pHLayout->setSpacing(0);
	pHLayout->setMargin(0);
	pMapWnd->setLayout(pHLayout);
	m_pMainWindow->setCentralWidget(pMapWnd);
	m_pMainWindow->showFullScreen();
}


