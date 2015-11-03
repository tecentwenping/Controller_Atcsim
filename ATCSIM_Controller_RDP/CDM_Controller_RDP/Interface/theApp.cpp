#include <QDebug>
#include <QTimer>
#include <QTime>
#include "theApp.h"
#include "CreateTowerAircraft/CreateTowerAircraftPacket.h"
#include "PathPlaning/PathPlanning.h"
#include "Manager/DataManager.h"
#include "Manager/NetManager.h"
#include "CreateTowerAircraft/GetFlyPlanFromDB.h"
Controller_RDP::Controller_RDP()

{	
}

Controller_RDP::~Controller_RDP()
{
   
}
bool  Controller_RDP::InitAppInstance()
{
	qDebug()<<"info in InitAppInstace()  Info:start init.......	Time:"+QTime::currentTime().toString();
	InitDataManagerPtr();
	InitPathPlanningPtr();
	InitCreateAircraftPacketPtr();
	InitNetManagerPtr();
	InitGetPlanFromDBPtr();
	if(!m_pDataManager||!m_pPathPlaning||!m_pCreateTowerAircraftPacket|| !m_pNetManager || !m_pGetFlyPlanFromDB)
	{
		return false;
	}
	connect(m_pCreateTowerAircraftPacket.get(),SIGNAL(sig_StartPathPlaning(int)),m_pPathPlaning.get(),SLOT(slot_StartPathPlaning(int)),Qt::DirectConnection);
	connect(m_pPathPlaning.get(),SIGNAL(sig_ReTranslateTowerAircraftPacket(int)),m_pCreateTowerAircraftPacket.get(),SLOT(slot_ReTranslateTowerAircraftPacket(int)));
	m_pCreateTowerAircraftPacket.get()->Init();
	return true;
}
void Controller_RDP::InitDataManagerPtr()
{
	if(! m_pDataManager)
	{
		m_pDataManager = boost::make_shared<CDataManager>();
		qDebug()<<"info in InitDataManagerPtr()  Info:start init.......	Time:"+QTime::currentTime().toString();
		m_pDataManager->Init();
	}
}
void Controller_RDP::InitNetManagerPtr()
{
	if(! m_pNetManager)
	{
		
		m_pNetManager = boost::make_shared<CNetManager>();
		qDebug()<<"info in InitNetManagerPtr()  Info:Network thread start.......	Time:"+QTime::currentTime().toString();
		m_pNetManager->moveToThread(&m_NetWorkThread);
		m_NetWorkThread.start();
	}
}
void Controller_RDP::InitCreateAircraftPacketPtr()
{

	if(! m_pCreateTowerAircraftPacket)
	{ 
		m_pCreateTowerAircraftPacket = boost::make_shared<CreateTowerAircraftPacket>();
		qDebug()<<"info in InitCreateAircraftPacketPtr()  Info:CreateAircraftPacket thread is starting......	Time:"+QTime::currentTime().toString();
		m_pCreateTowerAircraftPacket.get()->moveToThread(&m_CreateTowerAircraftPacketThread);
		m_CreateTowerAircraftPacketThread.start();
	}
}
void Controller_RDP::InitPathPlanningPtr()
{
	if(! m_pPathPlaning)
	{
		m_pPathPlaning = boost::make_shared<CPathPlanning>();
		qDebug()<<"info in InitPathPlanningPtr()  Info:PathPlanning thread is starting......	Time:"+QTime::currentTime().toString();
		m_pPathPlaning.get()->moveToThread(&m_PathPlaningThread);
		m_PathPlaningThread.start();
	}
}
void Controller_RDP::InitGetPlanFromDBPtr()
{
	if(! m_pGetFlyPlanFromDB)
	{
		m_pGetFlyPlanFromDB = boost::make_shared<CGetFlyPlanFromDB>();
		qDebug()<<"info in InitGetPlanFromDBPtr()  Info:DataBase thread is starting......	Time:"+QTime::currentTime().toString();
		m_pGetFlyPlanFromDB.get()->moveToThread(&m_GetFlyPlanFromDBThread);
		m_GetFlyPlanFromDBThread.start();
	}
}
CDataManager* Controller_RDP::GetDataManagerPtr()
{
	return m_pDataManager ? m_pDataManager.get() : NULL;
}
CNetManager* Controller_RDP::GetNetManagerPtr()
{
	return m_pNetManager ? m_pNetManager.get() : NULL;
}
CreateTowerAircraftPacket* Controller_RDP::GetCreateTowerAircraftPacketPtr()
{
	return m_pCreateTowerAircraftPacket ? m_pCreateTowerAircraftPacket.get() : NULL;
}
CPathPlanning* Controller_RDP::GetPathPlaningPtr()
{
	return m_pPathPlaning ? m_pPathPlaning.get() : NULL;
}
CGetFlyPlanFromDB*	Controller_RDP::GetPlanFromDBPtr()
{
	return m_pGetFlyPlanFromDB ? m_pGetFlyPlanFromDB.get() : NULL;
}