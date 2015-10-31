#include "MainApp.h"
#include "CSimMap.h"
#include "cmainwindow.h"
#include "WndsManager.h"
#include "coordinate.h"
#include "wndscreator.h"
#include "MapManager.h"
#include <boost/make_shared.hpp>
#include "CMapView.h"
#include "Manager/DataManager.h"
#include "Manager/NetManager.h"
#include "Net/RecvAircraftTrace.h"
CMainApp::CMainApp():m_eStatus(END)
{

}

CMainApp::~CMainApp()
{

}

void CMainApp::SetMainCallbackPtr( MainCallbackLogicPtr pCallback )
{
   m_pMainCallback = pCallback;
}

void CMainApp::SetWndsMangerPtr( WndsMangerPtr pWndsManager )
{
	m_pWndsManager = pWndsManager;

}

void CMainApp::SetMainWindowPtr( WMainWindowPtr pMainWindow )
{
  m_pMainWindow = pMainWindow;
}

void CMainApp::SetWndsCreatorPtr( WndsCreatorPtr pWndsCreator )
{
  m_pWndsCreator = pWndsCreator;
}

bool CMainApp::InitAppInstance( )
{
	//初始化数据
	InitData();
    //初始化地图(场景)
	InitSimMap();
	//初始化窗口&视图
	InitWnds();

	//初始化图元
	InitGlyphs();
	//初始化网络
	InitNetWork();
	m_pMapManager->GetSimMapPtr()->GetMainMapView()->reset();
	return true;
}

void CMainApp::InitWnds()
{
  if(m_pWndsCreator)
  {
	  m_pWndsCreator->InitAppWnds();
  }
}

void CMainApp::InitSimMap()
{
   //创建并初始化地图管理器
	if(!m_pMapManager)
	{
		m_pMapManager = boost::make_shared<CMapManager>();
		m_pMapManager->InitMapScene();

	}
}

void CMainApp::InitCoordinate()
{

}

void CMainApp::InitGlyphs()
{
	if(!m_pMapManager)
	{
		m_pMapManager = boost::make_shared<CMapManager>();
	}
	m_pMapManager->InitGlyphs();

}

bool CMainApp::IsRunning()
{
	return ((m_eStatus == RUNNING) ||(m_eStatus == FROZEN));

}

void CMainApp::ExitApp()
{
	if(m_pMainWindow)
	{
		m_pMainWindow->hide();
	}
	ClearData();
	if(m_pMainWindow)
	{
		m_pMainWindow->close();
	}


}

void CMainApp::ClearData()
{
	if(m_pMapManager)
	{
		m_pMapManager->GetSimMapPtr()->ClearAllLayers();
		m_pMapManager->GetSimMapPtr()->UpdateMap();
	}

}

WndsMangerPtr CMainApp::GetWndsManagerPtr() const
{
  return m_pWndsManager;
}

MapMangerPtr CMainApp::GetMapMangerPtr() const
{
	return m_pMapManager;

}

WMainWindowPtr CMainApp::GetWMainWindowPtr() const
{
	return m_pMainWindow;

}


MainCallbackLogicPtr CMainApp::GetMainCallbackLogic() const
{
  return m_pMainCallback;
}
DataManagerPtr CMainApp::GetDataManagerPtr() const
{
	return m_pDataManager;
}

NetManagerPtr CMainApp::GetNetManagerPtr() const
{
	return m_pNetManager;
}
TimerPtr CMainApp::GetTimerPtr() const
{
	return m_pTimer;

}
void CMainApp::InitData()
{
   if(! m_pDataManager)
   {
	   m_pDataManager = boost::make_shared<CDataManager>();
   }
}

void CMainApp::InitNetWork()
{
   if(! m_pNetManager)
   {
	   m_pNetManager = boost::make_shared<CNetManager>();
	   m_pNetManager->GetRecvAircraftTracePtr().get()->moveToThread(&m_RecvAircraftTraceThread);
	   m_RecvAircraftTraceThread.start();
	   bool bIsRunning = m_RecvAircraftTraceThread.isRunning();
   }
}



