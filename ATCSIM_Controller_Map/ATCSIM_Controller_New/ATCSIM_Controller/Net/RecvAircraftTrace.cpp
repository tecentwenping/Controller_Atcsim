#include "RecvAircraftTrace.h"
#include <iostream>
#include <QThread>
#include <QByteArray>
#include <QDataStream>
#include "AircraftTrace.h"
#include "DataManager.h"
#include "DataOperator/TotalAircraftTrace.h"
#include "MainApp.h"
#include  "Manager/MapManager.h"
#include "Glyph/CGlyphUpdater.h"
#include "Glyph/CGlyphCreator.h"
#include "DataOperator/ControllerAcftTrack.h"
const int RECVAIRCRAFTTRACEPORT = 13000;
CRecvAircraftTrace::CRecvAircraftTrace()
{
	//初始化接收飞行计划ID的套接字对象
	m_pUdpRecvAircraftTraceSocket = NULL;
	m_pUdpRecvAircraftTraceSocket = new QUdpSocket(this);
	bool isBind = m_pUdpRecvAircraftTraceSocket->bind(QHostAddress::Any,RECVAIRCRAFTTRACEPORT);
	bool isConnected = connect(m_pUdpRecvAircraftTraceSocket, SIGNAL(readyRead()), this, SLOT(RecvAircraftTraceSlot()));
	bool bIsConnected = connect(this,SIGNAL(sig_UpdateAircraftTrace(int)),theApp::instance().GetMapMangerPtr().get()->GetGlyphUpdaterPtr().get(),
		         SLOT(UpdateAircraftTraceSlot(int)),Qt::QueuedConnection);
}

CRecvAircraftTrace::~CRecvAircraftTrace()
{
	

}

void CRecvAircraftTrace::RecvAircraftTraceSlot()
{
	
	while (m_pUdpRecvAircraftTraceSocket->hasPendingDatagrams())
	{
       QByteArray dtagram;
	   dtagram.resize(m_pUdpRecvAircraftTraceSocket->pendingDatagramSize());
	   m_pUdpRecvAircraftTraceSocket->readDatagram(dtagram.data(),dtagram.size());
	   QDataStream in(&dtagram,QIODevice::ReadOnly);
	   in.setVersion(QDataStream::Qt_4_6);
		AircraftTrace vAircraftTrace;
		in>>vAircraftTrace;
	  // int readsize = m_pUdpRecvAircraftTraceSocket->readDatagram((char *)&vAircraftTrace, sizeof(AircraftTrace));

 		if(vAircraftTrace.m_nTraceID >= 0)
 		{
			// for no network test, keep!!!!!!
			int iTraceID = vAircraftTrace.m_nTraceID;
			AircraftTrace* pAircraftTrace=NULL;
			std::map<int,AircraftTrace*>::iterator Iter=mapAircraftTracePtr.find(iTraceID);
			if(Iter!=mapAircraftTracePtr.end()){
				pAircraftTrace=Iter->second;
			}else{
				pAircraftTrace=new AircraftTrace();
				mapAircraftTracePtr.insert(std::make_pair(iTraceID,pAircraftTrace));
			}
			memcpy(pAircraftTrace,&vAircraftTrace,dtagram.size());
		    //ConvertAircraftTrace(pAircraftTrace,vAircraftTrace);
			theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()->SetAircraftTrace(iTraceID,pAircraftTrace);
		    theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()->UpdateSingleAircraftTrace(pAircraftTrace);
        }
   }
}

void CRecvAircraftTrace::ConvertAircraftTrace( AircraftTrace* vDesAircraftTrace,const AircraftTrace& vSourAircraftTrace )
{
	vDesAircraftTrace->m_nTraceID			= vSourAircraftTrace.m_nTraceID;
	vDesAircraftTrace->m_euTrackType		= vSourAircraftTrace.m_euTrackType;
	vDesAircraftTrace->m_nICAOAddress		= vSourAircraftTrace.m_nICAOAddress;
	vDesAircraftTrace->m_strName			= vSourAircraftTrace.m_strName;
	vDesAircraftTrace->m_strSSR				= vSourAircraftTrace.m_strSSR;
	vDesAircraftTrace->m_dLongitude			= vSourAircraftTrace.m_dLongitude;
	vDesAircraftTrace->m_dLatitude			= vSourAircraftTrace.m_dLatitude;
	vDesAircraftTrace->m_euAltitudeType		= vSourAircraftTrace.m_euAltitudeType;
	vDesAircraftTrace->m_nDesAltitude		= vSourAircraftTrace.m_nDesAltitude;
	vDesAircraftTrace->m_euDesAltitudeType  = vSourAircraftTrace.m_euDesAltitudeType;
	vDesAircraftTrace->m_dGAS				= vSourAircraftTrace.m_dGAS;
	vDesAircraftTrace->m_dHeading			= vSourAircraftTrace.m_dHeading;
	vDesAircraftTrace->m_dTrackAngle		= vSourAircraftTrace.m_dTrackAngle;
	vDesAircraftTrace->m_euObjType			= vSourAircraftTrace.m_euObjType;
	vDesAircraftTrace->m_euEmergencyType	= vSourAircraftTrace.m_euEmergencyType;
	vDesAircraftTrace->m_bHide				= vSourAircraftTrace.m_bHide;
	vDesAircraftTrace->m_fAbsX				= vSourAircraftTrace.m_fAbsX;
	vDesAircraftTrace->m_fAbsY				= vSourAircraftTrace.m_fAbsY;
	vDesAircraftTrace->m_byAtt				= vSourAircraftTrace.m_byAtt;
	vDesAircraftTrace->eStateType			= vSourAircraftTrace.eStateType;
	vDesAircraftTrace->m_fPRLTime = 3;
	vDesAircraftTrace->m_nHistoryNum		= vSourAircraftTrace.m_nHistoryNum;
	vDesAircraftTrace->m_wPRLPos			= vSourAircraftTrace.m_wPRLPos;
	vDesAircraftTrace->m_eCurSignalType		= SIGNAL_COMBINED;
	vDesAircraftTrace->m_bShowLabel			= vSourAircraftTrace.m_bShowLabel;
	vDesAircraftTrace->m_iCount = 3;

}
