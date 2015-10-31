#include "PathPlanning.h"
#include "Manager/DataManager.h"
#include "AircraftTrace.h"
#include "ControllerPresenter.h"
#include "Net/NetProcess.h"
#include "AircraftInfo.h"
#include "Interface/theApp.h"
#include "Manager/NetManager.h"
#include "Net/NetDataDispenser.h"
#include <valarray>
#include <iostream>
typedef boost::shared_ptr<QTimer> TimerPtr;
//////////////////////////////////////////////////////////////////////////
#include "ControllerAcftTrack.h"
CPathPlanning::CPathPlanning():m_dSpeed(29.0),m_dFinishTime(3.0),m_dInternalTime(4.0)
{
    if(! m_pControllerPressenter)
	{
		m_pControllerPressenter = boost::make_shared<ControllerPresenter>();
	}
	if(! m_pAircraftTrace)
	{
		m_pAircraftTrace = boost::make_shared<AircraftTrace>();
	}
	if(! m_pSendAircraftTrace)
	{
		m_pSendAircraftTrace = boost::make_shared<NetProcess>();
		
	}
	/////////////////////////////////////////////////////////////////////////
	iCount = 0;
	m_isFinished = true;
}
CPathPlanning::~CPathPlanning()
{
}
void CPathPlanning::GetSourceAndDest( const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket )
{

	m_dInitLongtitude = towAircraftPacket.TowerobjFlight.dLongtitude;
	m_dInitLatitude = towAircraftPacket.TowerobjFlight.dLatitude;
	m_DepGate = towAircraftPacket.TowerplanFlight.sDepDromeName;
	m_ArrGate = towAircraftPacket.TowerplanFlight.sArrDromeName;
}

void CPathPlanning::GetPlanBaseInformation( const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket )
{
	m_isFinished = false;//���Ƚ���־λ��Ϊfalse
	m_Track.iTrackID = towAircraftPacket.TowerplanFlight.iFlightPlanId;//�Ժ���ID��Ϊ����ID
	m_Track.dLongitude = towAircraftPacket.TowerobjFlight.dLongtitude;//�ɻ��ĳ�ʼ����
	m_Track.dLatitude = towAircraftPacket.TowerobjFlight.dLatitude;//��ʼγ��
	m_Track.iAltitude = towAircraftPacket.TowerobjFlight.dAltitude;//��ʼ�߶�
	m_Track.strSSR = towAircraftPacket.TowerplanFlight.sSSRCode;//SSR�� 
	m_Track.strCallSign = towAircraftPacket.TowerplanFlight.sCallSign;//����
	m_Track.ObjType = towAircraftPacket.TowerobjFlight.ObjType;//
	//////////////////////////////////////////////////////////////////////////
	//��Ϊ�趨һЩ����
	m_Track.TrackType = PublicDataStruct::TRACKTYPE_ONGROUND;//��������
	m_Track.iICAOAddr = 0;
	m_Track.AltitudeType = PublicDataStruct::ALTTYPE_QNE;
	m_Track.dGS = 29;
	m_Track.Emergency = 0;
	m_Track.dROCD = 0;//ƽ��
	//����������
	//m_traceCheckLocker.lock();

	//�Ѿ��洢��һ����㵽һ���յ㾭�����е㣬�������ٶȼ�������Ӧ�Ĳ�ֵ��
	AircraftTrace *pTrace = m_pControllerPressenter.get()->UpdateSingleTrace(m_Track,PublicDataStruct::SIGNAL_COMBINED);
	//���ú���Ĭ��ֵ
	 SettAircraftTraceDefaulValue(*pTrace);
	// �洢������
	m_traceCheckLocker.lock();
	theData::instance().SetAircraftTrace(pTrace->m_nTraceID,pTrace);
	m_traceCheckLocker.unlock();
	theApp::instance().GetNetManagerPtr()->GetNetDataDispenserPtr()->UpdateAircraftTrace(pTrace);
	m_isFinished = true;
}
void CPathPlanning::slot_StartPathPlaning(int iFlightID)
{
	if(m_isFinished)
	{
		// 	   //��ô����̨�ɻ�����ӳ���

		MapTowerAircraftPacket temp; 
		theData::instance().GetMapTowerAircraftPacket(temp);
		// 	   //����ָ��ID����̨�ɻ���
		MapTowerAircraftPacket::iterator Iter = temp.find(iFlightID);
		if(Iter != temp.end())
		{
			PublicDataStruct::TowerAircraftPacketStruct &towerAircraftPacket = Iter->second;
			//��ȡ�ɻ�����Ϣ
			GetPlanBaseInformation(towerAircraftPacket);
		}
		return;
	}
	emit sig_ReTranslateTowerAircraftPacket(iFlightID);

}
void CPathPlanning::SettAircraftTraceDefaulValue( AircraftTrace& vAircraftTrace )
{
	ControllerAcftInfo tmpControllerAcftInfo;
	vAircraftTrace.m_nDesAltitude = 1;
	vAircraftTrace.m_euDesAltitudeType = PublicDataStruct::ALTTYPE_QNE;
	vAircraftTrace.m_dGAS = 29;
	vAircraftTrace.m_dHeading = 180;
	vAircraftTrace.m_dTrackAngle = 180;
	vAircraftTrace.m_bHide = false;
	vAircraftTrace.m_byAtt = 0;
	vAircraftTrace.eStateType = PublicDataStruct::STAT_TAXING;
	vAircraftTrace.m_fPRLTime = 3;
	vAircraftTrace.m_nHistoryNum = 5000;
	vAircraftTrace.m_bShowLabel = true;
	vAircraftTrace.m_iCount = 3;
	vAircraftTrace.m_eCurSignalType = PublicDataStruct::SIGNAL_COMBINED;
	vAircraftTrace.m_nHistoryNum = 0;
}
