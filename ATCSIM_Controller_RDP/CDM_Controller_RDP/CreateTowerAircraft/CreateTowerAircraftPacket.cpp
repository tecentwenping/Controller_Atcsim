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
	m_iFlyPlanID = 1;//FlyID�ɳ���ָ������1��ʼ��ţ����ε���
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
	//������ŷ��мƻ����������������齨TowerAircraftPacket
	if(! vecFlyPlanFromDB.empty())
	{   
		//û���µķ��мƻ�
		if(m_iOldSize == vecFlyPlanFromDB.size())
		{
			return;
		}
		m_iOldSize = vecFlyPlanFromDB.size();
		BOOST_FOREACH(std::vector<PublicDataStruct::SFlyPlanFromDB>::value_type& value,vecFlyPlanFromDB)
		{
			FlyPlanFromDBTemp = value;
			CreateTowerFlightPlan(FlyPlanFromDBTemp,towerFlightPlanTemp);//������мƻ�
			CreateTowerObjPlan(towerFlightPlanTemp,towerObjectPlanTemp);//�齨Ŀ��ƻ�
			CreateTowerAircraft(towerFlightPlanTemp,towerObjectPlanTemp);//����ɻ��� 
	

		}
	}
}
void CreateTowerAircraftPacket::CreateTowerObjPlan(PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct,
												   PublicDataStruct::TowerObjectPlanStruct& towerObjectPlanStruct)
{
	switch(m_PlanType)
	{
	//�볡�ƻ�
	case PublicDataStruct::CDM_DEP_PLAN:
		strcpy(m_GateInformationStruct.sDepGate,towerFlightPlanStruct.sDepGate);
		towerObjectPlanStruct.dLongtitude = m_GateInformationStruct.dLongtitude;
		towerObjectPlanStruct.dLatitude = m_GateInformationStruct.dLatitude;
		break;
		//�����ƻ�
	case  PublicDataStruct::CDM_ARR_PLAN:
		//switch(m_enumTerminate_T)
		//{
		//case PublicDataStruct::T1_TERMINATE://ra1Ϊ�����
			towerObjectPlanStruct.dLongtitude = m_initialLongtitue_T1;//���ֵľ��ȣ���λ�����ȣ�
			towerObjectPlanStruct.dLatitude = m_initilaLatitue_T1;//���ֵ�γ�ȣ���λ�����ȣ�
		//	break;
		//case PublicDataStruct::T2_TERMINATE://re1Ϊ�����
		//	towerObjectPlanStruct.dLongtitude = m_initialLongtitue_T2;//���ֵľ��ȣ���λ�����ȣ�
		//	towerObjectPlanStruct.dLatitude =  m_initilaLatitue_T2;//���ֵ�γ�ȣ���λ�����ȣ�
		//	break;
	//	}
		break;
	}
	//����Ŀ��ƻ�
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd hh:mm:ss");//����ʱ��
    towerObjectPlanStruct.ObjType = PublicDataStruct::OT_PLANE;//���ͣ����÷ɻ�
	strcpy( towerObjectPlanStruct.strSSrcode,towerFlightPlanStruct.sSSRCode);//�������мƻ��Ķ�����
	towerObjectPlanStruct.dAltitude = 0;//��ʼ�߶ȣ���׼��ѹ�߶ȣ���λ���ף�
	towerObjectPlanStruct.dHeading = 0;//��ͷ���򣨵�λ�����ȣ�
	towerObjectPlanStruct.dIAS = 0;//��ʼ�ٶȣ����٣���λs����/�룩
	strcpy( towerObjectPlanStruct.sAppearTime, str.toStdString().c_str());
	strcpy( towerObjectPlanStruct.strModelType,"B737_300");
	strcpy( towerObjectPlanStruct.strRegNum,towerFlightPlanStruct.sFlightNum);
	towerObjectPlanStruct.bEngineStart = true;//���治����

}
void CreateTowerAircraftPacket::CreateTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& flyPlanFromDB,
													  PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct )
{
	////�����(���������ȷ���ɻ���ͣ��λ)
	//QString sFlightNum = QString::fromStdString(flyPlanFromDB.sFlyPlanNum);
	//QRegExp rx("(3U)");//3U�Ǵ����ĺ���
	////ȷ����վ¥�������ĺ���Ĭ���Ƿ���T1��վ¥
	//bool isMatch = sFlightNum.contains(rx);
	//if(isMatch)
	//{
	//	m_enumTerminate_T = PublicDataStruct::T1_TERMINATE;
	//}else
	//{
	//	m_enumTerminate_T = PublicDataStruct::T2_TERMINATE;
	//}
	//�������ݿ��ȡ�ķ��мƻ�ת��Ϊ���мƻ�
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
			//�ɻ�λ��ռ,�޷������۷ɻ�����ͣ��λ
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
			//�ɻ�λ��ռ,�޷������۷ɻ�����ͣ��λ
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
		//��λ������󣬽��û�λ��Ϣ��ռ��λ����Ϊ1
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
		++ m_iCount;//ָ����һ��ͣ��λ
		gateInformation.dLongtitude = GateInformationStringList.at(1).toDouble();//γ��
		gateInformation.dLatitude = GateInformationStringList.at(2).toDouble();//����
		std::string sDepRunway = GateInformationStringList.at(3).toStdString();
		std::string sArrRunway = GateInformationStringList.at(4).toStdString();
		std::string sDepGate = GateInformationStringList.at(5).toStdString();
		std::string sArrGate = GateInformationStringList.at(6).toStdString();
		std::string sVacateLine = GateInformationStringList.at(7).toStdString();
		std::string sInRunwayLine = GateInformationStringList.at(8).toStdString();
		gateInformation.sGateName = GateInformationStringList.at(0);//ͣ��λ��
		m_GateInformationStruct.sGateName = GateInformationStringList.at(0);
		strcpy(gateInformation.sDepGate,sDepGate.c_str());//�볡ͣ��λ
		strcpy(gateInformation.sArrGate,sArrGate.c_str());//����ͣ��λ
		strcpy(gateInformation.sVacateLine,sVacateLine.c_str());//�����
		strcpy(gateInformation.sInRunwayLine,sInRunwayLine.c_str());//�����
		strcpy(gateInformation.sDepRunway,sDepRunway.c_str());
		strcpy(gateInformation.sArrRunway,sArrRunway.c_str());

	}
	 return;
}

void CreateTowerAircraftPacket::CheckPlanState( PublicDataStruct::TowerFlightPlanStruct  &planAracrs )
{   

	//�����ɻ���Ϊ�ɶ�����ú���Ϊ�볡����
	QString sDepAp = QString::fromStdString(planAracrs.sDepDromeName);
	if(0 == strcmp("ZUUU",sDepAp))
	{
		planAracrs.iFlyPlanType=1;
		m_PlanType=PublicDataStruct::CDM_DEP_PLAN;
	}
	//���ۺ���
	else
	{
		planAracrs.iFlyPlanType=0;
		m_PlanType=PublicDataStruct::CDM_ARR_PLAN;
	}
}

void CreateTowerAircraftPacket::ConvertFlyPlanFromDBToTowerFlightPlan( PublicDataStruct::SFlyPlanFromDB& FlightPlanFromDB
																	 ,PublicDataStruct::TowerFlightPlanStruct& TowerFlightPlan )
{ 
	
	//����һ�����е�ͣ��λ
	//PublicDataStruct::GateInformationStruct gateInfo;
	////////////////////////////////////////////////////////////////////////
	/*
	   ����ͣ��λ�ں���Ҫ���㷨��ʵ�֣�������˭���оͷ���˭���ǰ���˳�����
	*/
	///////////////////////////////////////////////////////////////////////
	GateAllocate(m_enumTerminate_T,m_GateInformationStruct);
	TowerFlightPlan.iFlightPlanId = m_iFlyPlanID; ++ m_iFlyPlanID;//����ID��1
    strcpy(TowerFlightPlan.sFlightNum,FlightPlanFromDB.sFlyPlanNum.c_str());//�����
	strcpy( TowerFlightPlan.sSSRCode,FlightPlanFromDB.sSSRCode.c_str());//������
	strcpy( TowerFlightPlan.sDepDromeName,FlightPlanFromDB.sDepDromeName.c_str());//��ɻ���
	strcpy( TowerFlightPlan.sArrDromeName,FlightPlanFromDB.sArrDromeName.c_str());//�������
	strcpy( TowerFlightPlan.sAlternateDrome,FlightPlanFromDB.sAlternateDrome.c_str());
	strcpy( TowerFlightPlan.sArrRunway,m_GateInformationStruct.sArrRunway);//�����ܵ�
	strcpy( TowerFlightPlan.sDepRunway,m_GateInformationStruct.sDepRunway);//����ܵ�
	strcpy( TowerFlightPlan.sDepartureTime,FlightPlanFromDB.sDepartureTime.c_str());//Ԥ�����ʱ��
	strcpy( TowerFlightPlan.sArrivalTime,FlightPlanFromDB.sAArrTime.c_str());//Ԥ�ƽ���ʱ��
	strcpy( TowerFlightPlan.sDepGate,m_GateInformationStruct.sDepGate);//�볡ͣ��λ
	strcpy( TowerFlightPlan.sArrGate,m_GateInformationStruct.sArrGate);//����ͣ��λ
	strcpy( TowerFlightPlan.sVacateLine,m_GateInformationStruct.sVacateLine);//�����
	strcpy( TowerFlightPlan.sInRunwayLine,m_GateInformationStruct.sInRunwayLine);//�����

	TowerFlightPlan.iCruiseLvl = FlightPlanFromDB.iCruiseLvl;//Ѳ���ٶ�
	TowerFlightPlan.iCruiseSpd = FlightPlanFromDB.iCruiseSpd;//Ѳ���ٶ�
	TowerFlightPlan.bRVSM = FlightPlanFromDB.bRVSM;//�Ƿ�߱�RVSM����
	TowerFlightPlan.iFlyPlanType = FlightPlanFromDB.iFlyPlanType;//���мƻ�����
	strcpy(TowerFlightPlan.sSidName, "Start1");//�볡��������
	strcpy(TowerFlightPlan.sAirRoadPoint.sBeacon, "0");//����̨
	strcpy(TowerFlightPlan.sAirRoadPoint.sSpeed, "0");//�ٶ�
	strcpy(TowerFlightPlan.sAirRoadPoint.sHeight, "0");//�߶�
	strcpy( TowerFlightPlan.sWeight,"M");//����
	strcpy( TowerFlightPlan.sSectorName,"TWR");//��������
	strcpy( TowerFlightPlan.sCompany,"ZUUU");//���չ�˾Ϊ�ɶ�˫�����ʻ���
	strcpy(TowerFlightPlan.sCallSign,FlightPlanFromDB.sFlyPlanNum.c_str());
	//�жϺ������ͣ��������볡���ڸú����ڲ�������m_PlanType��ֵ
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
	//��ӡTowerAircraftPacket����Ϣ
	printInformation(m_TowerAircraftStruct,printTowerAicraftPacket);
	//�洢�ɻ�����iFlightPlanId���ڱ�ʶһ�����мƻ�
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
		����㵽ͣ��λ�ĵ�λ���ֶ�¼��ģ����ڱ��ص�һ���ļ�����
		������Ҫ�����ݿ���ֱ�Ӽ���
	*/
	///////////////////////////////////////////////////////////
	std::map<QString,QStringList> mapPathInformation;//���е�·����Ϣ
	switch(m_PlanType)
	{
		//�볡�ɻ�����ȡ��ͣ��λ����ɵ��·������Ϣ
	case PublicDataStruct::CDM_DEP_PLAN:
		theData::instance().GetPathInformation(mapPathInformation,2);
		break;
	//�����ɻ�	
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
	//������ŷɻ���������������ƻ����˵�ǰʱ�䣬����亽������·���滮
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
		case PublicDataStruct::CDM_DEP_PLAN://�볡�ƻ������
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
