#include "NetManager.h"
#include "Net/NetDataDispenser.h"
#include "Net/NetProcess.h"
#include "Interface/theApp.h"
#include <QDebug>
CNetManager::CNetManager()
{
	InitNet();
}
CNetManager::~CNetManager()
{

}
NetDataDispenser* CNetManager::GetNetDataDispenserPtr()
{
	if(m_pNetDataDispenser)
	{
		return m_pNetDataDispenser.get();
	}
	return NULL;
}
NetProcess* CNetManager::GetNetProcessPtr()
{
	if(m_pNetProcess)
	{
		return m_pNetProcess.get();
	}
    return NULL;
   
}

void CNetManager::InitNet()
{
	if(! m_pNetDataDispenser)
	{
		m_pNetDataDispenser = boost::make_shared<NetDataDispenser>();
		m_Timer = new QTimer(this);
		bool isConnected = connect(m_Timer,SIGNAL(timeout()),this,SLOT(DisPenserPacketToClientSlot()),Qt::DirectConnection);
		m_Timer->start(2000);
		qDebug()<<"start NetDataDispenser.....";
	}
	if(! m_pNetProcess)
	{
		m_pNetProcess = boost::make_shared<NetProcess>();
		qDebug()<<"Init NetProcess.....";
	}
}

void CNetManager::DisPenserPacketToClientSlot()
{
	theApp::instance().GetNetManagerPtr()->GetNetDataDispenserPtr()->DispenserTraceToClient();
}

