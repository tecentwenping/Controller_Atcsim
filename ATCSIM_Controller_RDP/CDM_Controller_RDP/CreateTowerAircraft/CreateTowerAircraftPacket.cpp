#include "CreateTowerAircraftPacket.h"
#include <QRegExp>
#include <string>
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <iostream>
#include <boost/thread/shared_mutex.hpp>
#include <boost/foreach.hpp>
#include "Interface/theApp.h"
#include "Manager/DataManager.h"
#include "public/PublicData.h"
#include "DBOperator/DataBase.h"
#include "PublicStruct.h"
#include "Interface/theApp.h"
#include "Manager/DataManager.h"
#include "public/printFunc.h"
#include "Mutex.h"
double CreateTowerAircraftPacket:: m_initialLongtitue_T1=1.8140786372526054;
double CreateTowerAircraftPacket::m_initilaLatitue_T1=0.5334360886950167;
double CreateTowerAircraftPacket::m_initialLongtitue_T2=1.8139889250182442;
double CreateTowerAircraftPacket::m_initilaLatitue_T2=0.5326736899541124;
CreateTowerAircraftPacket::CreateTowerAircraftPacket()
{
	m_iFlyPlanID = 1;//FlyID由程序指定，从1开始编号，依次递增
	m_iCount = 0;
	m_iOldSize = 0;
}
CreateTowerAircraftPacket::~CreateTowerAircraftPacket()
{

}
void CreateTowerAircraftPacket::Init()
{
	while(1)
	{
		slot_RecvPlanAircraftPacket();
	}
}

void CreateTowerAircraftPacket::slot_RecvPlanAircraftPacket()
{
	PublicDataStruct::TowerFlightPlanStruct towerFlightPlanTemp;
	PublicDataStruct::SFlyPlanFromDB   FlyPlanFromDBTemp;
	PublicDataStruct::TowerObjectPlanStruct towerObjectPlanTemp;
	std::vector<PublicDataStruct::SFlyPlanFromDB> vecFlyPlanFromDB;
	boost::shared_mutex sMutex;
	sMutex.lock();
	theApp::instance().GetDataManagerPtr()->GetFlyPlan(vecFlyPlanFromDB);
	sMutex.unlock();
	//遍历存放飞行计划的容器，并最终组建TowerAircraftPacket
	if(! vecFlyPlanFromDB.empty())
	{   
		//没有新的飞行计划
		if(m_iOldSize == vecFlyPlanFromDB.size())
		{
			return;
		}
		m_iOldSize = vecFlyPlanFromDB.size();
		BOOST_FOREACH(std::vector<PublicDataStruct::SFlyPlanFromDB>::value_type& value,vecFlyPlanFromDB)
		{
			FlyPlanFromDBTemp = value;
			CreateTowerFlightPlan(FlyPlanFromDBTemp,towerFlightPlanTemp);//组件飞行计划
			CreateTowerObjPlan(towerFlightPlanTemp,towerObjectPlanTemp);//组建目标计划
			CreateTowerAircraft(towerFlightPlanTemp,towerObjectPlanTemp);//组件飞机包 
	

		}
	}
}
void CreateTowerAircraftPacket::CreateTowerObjPlan(PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct,
												   PublicDataStruct::TowerObjectPlanStruct& towerObjectPlanStruct)
{
	switch(m_PlanType)
	{
	//离场计划
	case PublicDataStruct::CDM_DEP_PLAN:
		strcpy(m_GateInformationStruct.sDepGate,towerFlightPlanStruct.sDepGate);
		towerObjectPlanStruct.dLongtitude = m_GateInformationStruct.dLongtitude;
		towerObjectPlanStruct.dLatitude = m_GateInformationStruct.dLatitude;
		break;
		//进场计划
	case  PublicDataStruct::CDM_ARR_PLAN:
		//switch(m_enumTerminate_T)
		//{
		//case PublicDataStruct::T1_TERMINATE://ra1为进入点
			towerObjectPlanStruct.dLongtitude = m_initialLongtitue_T1;//出现的经度（单位：弧度）
			towerObjectPlanStruct.dLatitude = m_initilaLatitue_T1;//出现的纬度（单位：弧度）
		//	break;
		//case PublicDataStruct::T2_TERMINATE://re1为进入点
		//	towerObjectPlanStruct.dLongtitude = m_initialLongtitue_T2;//出现的经度（单位：弧度）
		//	towerObjectPlanStruct.dLatitude =  m_initilaLatitue_T2;//出现的纬度（单位：弧度）
		//	break;
	//	}
		break;
	}
	//创建目标计划
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss");//出现时间
    towerObjectPlanStruct.ObjType = PublicDataStruct::OT_PLANE;//类型，民用飞机
	strcpy( towerObjectPlanStruct.strSSrcode,towerFlightPlanStruct.sSSRCode);//关联飞行计划的二次码
	towerObjectPlanStruct.dAltitude = 0;//初始高度（标准海压高度，单位：米）
	towerObjectPlanStruct.dHeading = 0;//机头朝向（单位：弧度）
	towerObjectPlanStruct.dIAS = 0;//初始速度（表速，单位s：米/秒）
	strcpy( towerObjectPlanStruct.sAppearTime, str.toStdString().c_str());
	strcpy( towerObjectPlanStruct.strModelType,"B737_300");
	strcpy( towerObjectPlanStruct.strRegNum,towerFlightPlanStruct.sFlightNum);
	towerObjectPlanStruct.bEngineStart = true;//引擎不开启

}
void CreateTowerAircraftPacket::CreateTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& flyPlanFromDB,
													  PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct )
{
	////航班号(航班号用于确定飞机的停机位)
	//QString sFlightNum = QString::fromStdString(flyPlanFromDB.sFlyPlanNum);
	//QRegExp rx("(3U)");//3U是川航的航班
	////确定航站楼，川航的航班默认是放在T1航站楼
	//bool isMatch = sFlightNum.contains(rx);
	//if(isMatch)
	//{
	//	m_enumTerminate_T = PublicDataStruct::T1_TERMINATE;
	//}else
	//{
	//	m_enumTerminate_T = PublicDataStruct::T2_TERMINATE;
	//}
	//将从数据库读取的飞行计划转换为飞行计划
	ConvertFlyPlanFromDBToTowerFlightPlan(flyPlanFromDB,towerFlightPlanStruct);
}
void CreateTowerAircraftPacket::GateAllocate( PublicDataStruct::PLAN_TERMINATE enumTerminate_T,PublicDataStruct::GateInformationStruct& gateInformation )
{
	QStringList GateInformationStringList;
	switch(enumTerminate_T)
	{
	case PublicDataStruct::T1_TERMINATE:
		while(m_iCount < theData::instance().GetGateInformation_T1().size())
		{
			GateInformationStringList = theData::instance().GetGateInformation_T1().at(m_iCount);
			//飞机位被占,无法给进港飞机分配停机位
			if("1" == GateInformationStringList.at(9))
			{
				++ m_iCount;
			}

			else break;
		}
		break;
	case PublicDataStruct::T2_TERMINATE:
		while(m_iCount < theData::instance().GetGateInformation_T2().size())
		{
			GateInformationStringList = theData::instance().GetGateInformation_T2().at(m_iCount);
			//飞机位被占,无法给进港飞机分配停机位
			if("1" == GateInformationStringList.at(9))
			{
				++ m_iCount;
			}
			else break;
		}
		break;
	}
	if(! GateInformationStringList.empty())
	{
		//机位被分配后，将该机位信息的占用位设置为1
		CQMutex mutex;
		mutex.MyLock();
		const QString flag("1");
		switch(enumTerminate_T)
		{
		case PublicDataStruct::T1_TERMINATE:

			theData::instance().GetGateInformation_T1().at(m_iCount).replace(9,flag);
			break;
		case PublicDataStruct::T2_TERMINATE:
			theData::instance().GetGateInformation_T2().at(m_iCount).replace(9,flag);
			break;
		}
		mutex.MyUnlock();
		++ m_iCount;//指向下一个停机位
		gateInformation.dLongtitude = GateInformationStringList.at(1).toDouble();//纬度
		gateInformation.dLatitude = GateInformationStringList.at(2).toDouble();//经度
		std::string sDepRunway = GateInformationStringList.at(3).toStdString();
		std::string sArrRunway = GateInformationStringList.at(4).toStdString();
		std::string sDepGate = GateInformationStringList.at(5).toStdString();
		std::string sArrGate = GateInformationStringList.at(6).toStdString();
		std::string sVacateLine = GateInformationStringList.at(7).toStdString();
		std::string sInRunwayLine = GateInformationStringList.at(8).toStdString();
		gateInformation.sGateName = GateInformationStringList.at(0);//停机位名
		m_GateInformationStruct.sGateName = GateInformationStringList.at(0);
		strcpy(gateInformation.sDepGate,sDepGate.c_str());//离场停机位
		strcpy(gateInformation.sArrGate,sArrGate.c_str());//进场停机位
		strcpy(gateInformation.sVacateLine,sVacateLine.c_str());//脱离道
		strcpy(gateInformation.sInRunwayLine,sInRunwayLine.c_str());//进入道
		strcpy(gateInformation.sDepRunway,sDepRunway.c_str());
		strcpy(gateInformation.sArrRunway,sArrRunway.c_str());

	}
	 return;
}

void CreateTowerAircraftPacket::CheckPlanState( PublicDataStruct::TowerFlightPlanStruct  &planAracrs )
{   

	//如果起飞机场为成都，则该航班为离场航班
	QString sDepAp = QString::fromStdString(planAracrs.sDepDromeName);
	if(0 == strcmp("ZUUU",sDepAp))
	{
		planAracrs.iFlyPlanType=1;
		m_PlanType=PublicDataStruct::CDM_DEP_PLAN;
	}
	//进港航班
	else
	{
		planAracrs.iFlyPlanType=0;
		m_PlanType=PublicDataStruct::CDM_ARR_PLAN;
	}
}

void CreateTowerAircraftPacket::ConvertFlyPlanFromDBToTowerFlightPlan( PublicDataStruct::SFlyPlanFromDB& FlightPlanFromDB
																	 ,PublicDataStruct::TowerFlightPlanStruct& TowerFlightPlan )
{ 
	
	//分配一个空闲的停机位
	//PublicDataStruct::GateInformationStruct gateInfo;
	////////////////////////////////////////////////////////////////////////
	/*
	   分配停机位在后期要用算法来实现，现在是谁空闲就分配谁，是按照顺序分配
	*/
	///////////////////////////////////////////////////////////////////////
	GateAllocate(m_enumTerminate_T,m_GateInformationStruct);
	TowerFlightPlan.iFlightPlanId = m_iFlyPlanID; ++ m_iFlyPlanID;//航班ID加1
    strcpy(TowerFlightPlan.sFlightNum,FlightPlanFromDB.sFlyPlanNum.c_str());//航班号
	strcpy( TowerFlightPlan.sSSRCode,FlightPlanFromDB.sSSRCode.c_str());//二次码
	strcpy( TowerFlightPlan.sDepDromeName,FlightPlanFromDB.sDepDromeName.c_str());//起飞机场
	strcpy( TowerFlightPlan.sArrDromeName,FlightPlanFromDB.sArrDromeName.c_str());//降落机场
	strcpy( TowerFlightPlan.sAlternateDrome,FlightPlanFromDB.sAlternateDrome.c_str());
	strcpy( TowerFlightPlan.sArrRunway,m_GateInformationStruct.sArrRunway);//降落跑道
	strcpy( TowerFlightPlan.sDepRunway,m_GateInformationStruct.sDepRunway);//起飞跑道
	strcpy( TowerFlightPlan.sDepartureTime,FlightPlanFromDB.sDepartureTime.c_str());//预计起飞时间
	strcpy( TowerFlightPlan.sArrivalTime,FlightPlanFromDB.sAArrTime.c_str());//预计降落时间
	strcpy( TowerFlightPlan.sDepGate,m_GateInformationStruct.sDepGate);//离场停机位
	strcpy( TowerFlightPlan.sArrGate,m_GateInformationStruct.sArrGate);//进场停机位
	strcpy( TowerFlightPlan.sVacateLine,m_GateInformationStruct.sVacateLine);//脱离道
	strcpy( TowerFlightPlan.sInRunwayLine,m_GateInformationStruct.sInRunwayLine);//进入道

	TowerFlightPlan.iCruiseLvl = FlightPlanFromDB.iCruiseLvl;//巡航速度
	TowerFlightPlan.iCruiseSpd = FlightPlanFromDB.iCruiseSpd;//巡航速度
	TowerFlightPlan.bRVSM = FlightPlanFromDB.bRVSM;//是否具备RVSM能力
	TowerFlightPlan.iFlyPlanType = FlightPlanFromDB.iFlyPlanType;//飞行计划类型
	strcpy(TowerFlightPlan.sSidName, "Start1");//离场程序名称
	strcpy(TowerFlightPlan.sAirRoadPoint.sBeacon, "0");//导航台
	strcpy(TowerFlightPlan.sAirRoadPoint.sSpeed, "0");//速度
	strcpy(TowerFlightPlan.sAirRoadPoint.sHeight, "0");//高度
	strcpy( TowerFlightPlan.sWeight,"M");//载重
	strcpy( TowerFlightPlan.sSectorName,"TWR");//扇区名字
	strcpy( TowerFlightPlan.sCompany,"ZUUU");//航空公司为成都双流国际机场
	strcpy(TowerFlightPlan.sCallSign,FlightPlanFromDB.sFlyPlanNum.c_str());
	//判断航班类型，即进场离场，在该函数内部会设置m_PlanType的值
	CheckPlanState(TowerFlightPlan);
}

void CreateTowerAircraftPacket::CreateTowerAircraft( PublicDataStruct::TowerFlightPlanStruct& TowerFlightPlan,
													PublicDataStruct::TowerObjectPlanStruct& TowerObjectPlan)
{
	m_TowerAircraftStruct.TowerplanFlight = TowerFlightPlan;
	m_TowerAircraftStruct.TowerobjFlight =  TowerObjectPlan;
	QStringList pathPointList;
	GetPathPoint(m_GateInformationStruct.sGateName,pathPointList);
	if(!pathPointList.empty())
	{
		theData::instance().SetPathPoint(m_TowerAircraftStruct.TowerplanFlight.iFlightPlanId,pathPointList);

	}
	//打印TowerAircraftPacket的信息
	printInformation(m_TowerAircraftStruct,printTowerAicraftPacket);
	//存储飞机包，iFlightPlanId用于标识一个飞行计划
	CQMutex mutex;
	mutex.MyLock();
	theData::instance().GetMapTowerAircraftPacket().insert(std::make_pair(m_TowerAircraftStruct.TowerplanFlight.iFlightPlanId,m_TowerAircraftStruct));
	mutex.MyUnlock();
	emit sig_StartPathPlaning(m_TowerAircraftStruct.TowerplanFlight.iFlightPlanId);
	//ParaseAircraftPacketByTime();
	
}
void CreateTowerAircraftPacket::GetPathPoint( const QString& sGateName,QStringList& PathPointList )
{
	///////////////////////////////////////////////////////////
	/*
		降落点到停机位的点位是手动录入的，放在本地的一个文件里面
		后期需要从数据库中直接加载
	*/
	///////////////////////////////////////////////////////////
	std::map<QString,QStringList> mapPathInformation;//所有的路径信息
	switch(m_PlanType)
	{
		//离场飞机，读取从停机位到起飞点的路径点信息
	case PublicDataStruct::CDM_DEP_PLAN:
		theData::instance().GetPathInformation(mapPathInformation,2);
		break;
	//进场飞机	
	case  PublicDataStruct::CDM_ARR_PLAN:
		theData::instance().GetPathInformation(mapPathInformation,1);
		break;
	}
	std::map<QString,QStringList>::iterator Iter = mapPathInformation.find(sGateName);
	if(Iter != mapPathInformation.end())
	{
		PathPointList = Iter->second;
	}
	return;
}
void CreateTowerAircraftPacket::ParaseAircraftPacketByTime()
{
	//遍历存放飞机包的容器，如果计划到了当前时间，则对其航迹进行路径规划
	MapTowerAircraftPacket &tmp = theData::instance().GetMapTowerAircraftPacket();
	if(tmp.empty())
	{
		return;
	}	
	MapTowerAircraftPacket::iterator Iter = tmp.begin();
	while(Iter != tmp.end())
	{
		QString sCurSystemTime(DataBaseAccessObj::GetInstance()->func_getCurrentSystemTime());
		PublicDataStruct::TowerAircraftPacketStruct &towerAircraftPacket = Iter->second;
		switch(m_PlanType)
		{
		case PublicDataStruct::CDM_DEP_PLAN://离场计划的情况
			if(towerAircraftPacket.TowerplanFlight.sDepartureTime == sCurSystemTime)
			{
				emit sig_StartPathPlaning(towerAircraftPacket.TowerplanFlight.iFlightPlanId);
			}
			break;
		case  PublicDataStruct::CDM_ARR_PLAN:
			if(towerAircraftPacket.TowerplanFlight.sArrivalTime == sCurSystemTime)
			{
				emit sig_StartPathPlaning(towerAircraftPacket.TowerplanFlight.iFlightPlanId);
			}
			break;
		}
		++ Iter;
	////////////}	
}
}

void CreateTowerAircraftPacket::slot_ReTranslateTowerAircraftPacket( int iFlightID )
{
	emit sig_StartPathPlaning(m_TowerAircraftStruct.TowerplanFlight.iFlightPlanId);
}
