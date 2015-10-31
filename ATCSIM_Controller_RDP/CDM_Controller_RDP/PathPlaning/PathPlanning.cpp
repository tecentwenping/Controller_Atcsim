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
	m_isFinished = false;//首先将标志位置为false
	m_Track.iTrackID = towAircraftPacket.TowerplanFlight.iFlightPlanId;//以航班ID作为航迹ID
	m_Track.dLongitude = towAircraftPacket.TowerobjFlight.dLongtitude;//飞机的初始经度
	m_Track.dLatitude = towAircraftPacket.TowerobjFlight.dLatitude;//初始纬度
	m_Track.iAltitude = towAircraftPacket.TowerobjFlight.dAltitude;//初始高度
	m_Track.strSSR = towAircraftPacket.TowerplanFlight.sSSRCode;//SSR码 
	m_Track.strCallSign = towAircraftPacket.TowerplanFlight.sCallSign;//呼号
	m_Track.ObjType = towAircraftPacket.TowerobjFlight.ObjType;//
	//////////////////////////////////////////////////////////////////////////
	//认为设定一些参数
	m_Track.TrackType = PublicDataStruct::TRACKTYPE_ONGROUND;//航迹类型
	m_Track.iICAOAddr = 0;
	m_Track.AltitudeType = PublicDataStruct::ALTTYPE_QNE;
	m_Track.dGS = 29;
	m_Track.Emergency = 0;
	m_Track.dROCD = 0;//平飞
	//解析航迹点
	//m_traceCheckLocker.lock();

	//已经存储了一个起点到一个终点经过所有点，并根据速度计算量相应的插值点
	AircraftTrace *pTrace = m_pControllerPressenter.get()->UpdateSingleTrace(m_Track,PublicDataStruct::SIGNAL_COMBINED);
	//设置航迹默认值
	 SettAircraftTraceDefaulValue(*pTrace);
	// 存储航迹点
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
		// 	   //获得存放塔台飞机包的映射表

		MapTowerAircraftPacket temp; 
		theData::instance().GetMapTowerAircraftPacket(temp);
		// 	   //查找指定ID的塔台飞机包
		MapTowerAircraftPacket::iterator Iter = temp.find(iFlightID);
		if(Iter != temp.end())
		{
			PublicDataStruct::TowerAircraftPacketStruct &towerAircraftPacket = Iter->second;
			//析取飞机包信息
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
