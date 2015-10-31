#include "NetProcess.h"
#include "public/PublicStruct.h"
#include "AircraftTrace.h"
#include "public/printFunc.h"
#include <QDebug>
#include <QBuffer>
#include <Windows.h>
#include "ControllerAcftTrack.h"
NetProcess::NetProcess()
{
	m_pUdpSendTraceSocket = NULL;
}
NetProcess::~NetProcess()
{
	if( NULL != m_pUdpSendTraceSocket)
	{
		delete m_pUdpSendTraceSocket;
		m_pUdpSendTraceSocket = NULL;
	}
}
void NetProcess::SendAircraftTrace(const AircraftTrace& vAircraftTrace)
{
	QByteArray dtaArray;
	dtaArray.resize(sizeof(AircraftTrace));
	QBuffer dtaBuffer(&dtaArray);
	dtaBuffer.open(QIODevice::WriteOnly);
	// ‰»Î ˝æ›
	QDataStream out(&dtaBuffer);
	out.setVersion(QDataStream::Qt_4_6);
	out<<vAircraftTrace;
	dtaBuffer.close();  
	m_pUdpSendTraceSocket = (NULL == m_pUdpSendTraceSocket) ? (new QUdpSocket(this)):m_pUdpSendTraceSocket;
	bool isBind = m_pUdpSendTraceSocket->bind(PublicDataStruct::SENDAIRCRAFTTRACEPORT);
	int bytesWritten = m_pUdpSendTraceSocket->writeDatagram(dtaArray,QHostAddress::LocalHost,PublicDataStruct::SENDAIRCRAFTTRACEPORT);
	printInformation(vAircraftTrace,printAircraftTrace);
	delete m_pUdpSendTraceSocket;
	m_pUdpSendTraceSocket = NULL;
}