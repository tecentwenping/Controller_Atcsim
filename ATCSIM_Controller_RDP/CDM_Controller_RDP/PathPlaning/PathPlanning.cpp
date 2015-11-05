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
	//vAircraftTrace.m_nHistoryNum = 5000;
	vAircraftTrace.m_bShowLabel = true;
	vAircraftTrace.m_iCount = 3;
	vAircraftTrace.m_eCurSignalType = PublicDataStruct::SIGNAL_COMBINED;
	vAircraftTrace.m_nHistoryNum = 0;

	//////////////////////////////////////////////////////////////////////
	/*
	 目前机型全部为B733，后期改动的时候需要根据双流机场的飞行计划中指定的
	 航班来确定机型，机型的各项参数参照PublicStruct.h文件
	*/
	/////////////////////////////////////////////////////////////////////
	vAircraftTrace.m_aircraftInfo.dMass=52550;//质量
	vAircraftTrace.m_aircraftInfo.dLength=32.18;//机身长度
	vAircraftTrace.m_aircraftInfo.dWingSpan=28.9;//翼展长度
	vAircraftTrace.m_aircraftInfo.sWake="M";//中型机
	vAircraftTrace.m_aircraftInfo.sType="B733";
	vAircraftTrace.m_aircraftInfo.dCurTaxSpd=vAircraftTrace.m_dGAS;

	_SetSafeDistance(vAircraftTrace);


}
void CPathPlanning::_SetSafeDistance( AircraftTrace& aircraft )
{
	 /*
	 告警层:L'=V*t+m*V*V/2(f1+f2+f3)
	 V:当前速度
	 t:反应时间，设定为5s
	 m:航空器质量
	 f1:刹车力，为质量的40%
	 f2:反推力，质量的40%
	 f3：空气阻力，为质量的10%
	 中小型飞机，反推力和空气阻力为0
	*/
	double dSpd=aircraft.m_aircraftInfo.dCurTaxSpd;
	double dTime=PublicDataStruct::RESPONSETIME;
	double dMass=aircraft.m_aircraftInfo.dMass;
	double F1=dMass*0.4;
	double F2=0.0,F3=0.0;
	if(aircraft.m_aircraftInfo.sWake=="H"){
		F2=dMass*0.4;
		F3=dMass*0.1;
	}
	double dAlarmDistance=dSpd*dTime+(dMass*dSpd*dSpd)/(F1+F2+F3)*0.5;

	aircraft.m_aircraftInfo.dAlarmDistance=dAlarmDistance;
	aircraft.m_aircraftInfo.dBaseDistance=aircraft.m_aircraftInfo.dLength;
	aircraft.m_aircraftInfo.dSafeDistance=aircraft.m_aircraftInfo.dAlarmDistance+aircraft.m_aircraftInfo.dBaseDistance;
}
