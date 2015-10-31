#include "SendFlyPlanToRDP.h"
#include "GetFlyPlanFromDB.h"
#include "ConstParam/constStruct.h"
#include <iostream>
#include <QTimer>

CSendFlyPlanToRDP::CSendFlyPlanToRDP()
{
	m_iCount = 0;
	m_UdpSendFlyPlanToRDPSocket = NULL;
}
CSendFlyPlanToRDP::~CSendFlyPlanToRDP()
{
   
}

void CSendFlyPlanToRDP::slot_SendFlyPlanToRDP()
{
	if(m_iCount != CGetFlyPlanFromDB::GetFlyPlan().size())
	{
		FlyPlanFromDBStruct &flyPlanTemp = CGetFlyPlanFromDB::GetFlyPlan().at(m_iCount);
		++ m_iCount;
		m_UdpSendFlyPlanToRDPSocket = (NULL == m_UdpSendFlyPlanToRDPSocket)?(new QUdpSocket(this)):m_UdpSendFlyPlanToRDPSocket;
		bool isBind = m_UdpSendFlyPlanToRDPSocket->bind(SENDFLYPLANPORT);
		std::cout<<isBind<<std::endl;
		m_UdpSendFlyPlanToRDPSocket->writeDatagram((char *)&flyPlanTemp, sizeof(flyPlanTemp), QHostAddress::Broadcast, SENDFLYPLANPORT);
		delete m_UdpSendFlyPlanToRDPSocket;
		m_UdpSendFlyPlanToRDPSocket = NULL;
	}
}

void CSendFlyPlanToRDP::slot_StartSendFlyPlanToRDP()
{
	QTimer *qTimer = new QTimer;
	connect(qTimer,SIGNAL(timeout()),this,SLOT(slot_SendFlyPlanToRDP()));
	//4s发送一个报文
	qTimer->start(4000);
}
