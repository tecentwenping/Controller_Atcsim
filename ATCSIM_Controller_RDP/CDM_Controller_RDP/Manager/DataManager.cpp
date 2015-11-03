#include "Manager/DataManager.h"
//#include "Manager/.h"
#include "Manager/InitPointInformation.h"
#include "PathPlaning/TotalAircraftTrace.h"
#include "PathPlaning/AircraftTrace.h"
#include "public/PublicData.h"
#include "Manager/PathInformation.h"
#include "Manager/GateInformation.h"

//双流机场的经纬度
const double dCenterLongtitude = 1.81421157980637;
const double dCenterLatitude   = 0.533692596438999;
CDataManager::CDataManager()
{

}

CDataManager::~CDataManager()
{
    
}

void CDataManager::Init()
{
	if( ! m_pPublicData)
	{
		qDebug()<<"PublicData initing....";
		m_pPublicData = boost::make_shared<CPublicData>(dCenterLongtitude,dCenterLatitude);
	}
 	if(! m_pInitGateInformation)
 	{
 		qDebug()<<"Reading GateInformation.....";
 		m_pInitGateInformation = boost::make_shared<CGateInformation>();
        m_pInitGateInformation.get()->ReadInformationFromFile();
 	}
	/*if(! m_pInitPathInformation)
	{
		qDebug()<<"Reading PathInformation....";
		m_pInitPathInformation = boost::make_shared<CInitPathInformation>();
		m_pInitPathInformation.get()->ReadInformationFromFile();
	}*/
	if(! m_pInitPointInformaton)
	{
		qDebug()<<"Reading PointInformation.....";
		m_pInitPointInformaton = boost::make_shared<CInitPointInformation>();
		m_pInitPointInformaton.get()->Init();
	}
	if(! m_pTotalTrace)
	{
		qDebug()<<"TotalTracePtr initing....";
		m_pTotalTrace = boost::make_shared<TotalAircraftTrace>();
		//m_pTotalTracePtr = new TotalAircraftTrace();
	}
	if(!m_pTaxLineInformation){
		qDebug()<<"offline taxline information initing..........";
		m_pTaxLineInformation=boost::make_shared<CTaxiLineInformation>();
		m_pTaxLineInformation.get()->GetTaxiLineInformation();
	}
}

void CDataManager::GetCenterCoordinate( double& dCenterLongtitude,double& dLatitude )
{
    m_pPublicData.get()->SetCenterCoordinate(dCenterLongtitude,dLatitude);
}

void CDataManager::GetMapAirTrace( MapAircraftTrace& mpAircraftTrace )
{
    m_pPublicData.get()->GetMapAircraftTrace(mpAircraftTrace);
}

void CDataManager::SetMapAirTrace(const MapAircraftTrace& mapAircraftTrace)
{
	m_pPublicData->SetAircraftTrace(mapAircraftTrace);

}

//void CDataManager::SetTracePoint(int iTraceno, const std::vector<WPointF>& vecTracePoint )
//{
//    m_pTotalTrace.get()->UpdateAircraftTracePoint(iTraceno,vecTracePoint);
//
//}
//
//void CDataManager::GetTracePoint( int iTraceno,std::vector<WPointF>& vecTracePoint )
//{
//   m_pTotalTrace.get()->GetAircraftTracePoint(iTraceno,vecTracePoint);
//}

void CDataManager::SetAircraftTrace( int iTraceno, AircraftTrace* aicraftTrace )
{
	m_pTotalTrace.get()->UpdateAircraftTrace(iTraceno,aicraftTrace);
	//m_pTotalTracePtr->UpdateAircraftTrace(iTraceno,aicraftTrace);

}

void CDataManager::GetAircraftTrace( hmFplTraces& hmFplTrace )
{
	m_pTotalTrace->GetTraces(hmFplTrace);

}
TotalAircraftTrace* CDataManager::GetTotalAircraftTracePtr()
{
	if(m_pTotalTrace)
	{
	   return m_pTotalTrace.get();
	}
	return NULL;
}
void CDataManager::GetFlyPlan( std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan )
{
	m_pPublicData.get()->GetVecFlyPlanFromDB(vecFlyPlan);
}
void CDataManager::SetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan )
{
	m_pPublicData.get()->SetVecFlyPlanFromDB(vecFlyPlan);
}

void CDataManager::SetGateInformation(const VecGateInformation& vecGateInformation,int flag )
{
	switch(flag)
	{
	case 1:
		m_pPublicData.get()->SetGateInformation_T1(vecGateInformation);
		break;
	case  2:
		m_pPublicData.get()->SetGateInformation_T2(vecGateInformation);
		break;
	}
}


void CDataManager::SetPathInformation( const MapPath& mapPath,int flag )
{
	switch(flag)
	{
	case 1:
		m_pPublicData.get()->SetInPathInformation(mapPath);
		break;
	case  2:
		m_pPublicData.get()->SetOutPathInformation(mapPath);
		break;
	}
}


void CDataManager::SetPathPoint(int iFlyID,QStringList& vecPathPoint)
{
	m_pPublicData.get()->SetPathPoint(iFlyID,vecPathPoint);
}
void CDataManager::GetPathPoint(int iFlyID,QStringList& vecPathPoint)
{
	m_pPublicData.get()->GetPathPoint(iFlyID,vecPathPoint);
}

void CDataManager::GetPathInformation( MapPath& mapPath,int flag )
{
	m_pPublicData.get()->GetPathInformation(mapPath,flag);
}

void CDataManager::GetGateInformation_T1( VecGateInformation& vecGateInformation )
{
	m_pPublicData.get()->GetGateInformation_T1(vecGateInformation);

}
VecGateInformation& CDataManager::GetGateInformation_T1()
{
	return m_pPublicData.get()->GetGateInformation_T1();
}
void CDataManager::GetGateInformation_T2( VecGateInformation& vecGateInformation )
{
	m_pPublicData.get()->GetGateInformation_T2(vecGateInformation);

}
VecGateInformation& CDataManager::GetGateInformation_T2()
{
	return m_pPublicData.get()->GetGateInformaiton_T2();
}
void CDataManager::GetMapGateName( MapGateName& mapGateName )
{
	m_pPublicData.get()->GetMapGateName(mapGateName);

}

void CDataManager::GetMapTaxiLine( MapTaxiLine& mapTaxiLine )
{
  m_pPublicData.get()->GetMapTaxiLine(mapTaxiLine);
}

void CDataManager::GetMapFixPoint( MapFixPoint& mapFixPoint )
{
	m_pPublicData.get()->GetMapFixPoint(mapFixPoint);

}

void CDataManager::GetMapTowerAircraftPacket( MapTowerAircraftPacket& mapTowerAircraft )
{
	m_pPublicData.get()->GetMapTowerAircraftPacket(mapTowerAircraft);
}

MapTowerAircraftPacket& CDataManager::GetMapTowerAircraftPacket()
{
	return m_pPublicData.get()->GetMapTowerAircraftPacket();

}

void CDataManager::SetMapFixPoint( const MapFixPoint& mpFixPoint )
{
	m_pPublicData.get()->SetFixPoint(mpFixPoint);

}

void CDataManager::SetMapTaxLine( const MapTaxiLine& mpTaxLine )
{
   m_pPublicData.get()->SetTaxiLine(mpTaxLine);
}

void CDataManager::SetMapGateName( const MapGateName& mpGateName )
{
	m_pPublicData.get()->SetGateName(mpGateName);

}

void CDataManager::SetMapTowerAircraftPacket( const MapTowerAircraftPacket& mpTowerAircraft )
{
	m_pPublicData.get()->SetTowerAircraftPacket(mpTowerAircraft);

}
void CDataManager::SetCurrentFlyPlan(const QString& singleFlyPlan)
{
	m_pPublicData.get()->SetCurrentFlyPlan(singleFlyPlan);
}
void CDataManager::GetCurrentFlyPlan(std::vector<QString>& vecCurFlyPlan)
{
	m_pPublicData.get()->GetCurrentFlyPlan(vecCurFlyPlan);
}

void CDataManager::SetAircraftTracePoint1( int traceID,const std::deque<WPointF>& dTrace )
{
    m_pTotalTrace.get()->UpdateAircraftTracePoint1(traceID,dTrace);

}

void CDataManager::GetAircraftTracePoint1( int traceID, std::deque<WPointF>& dTrace )
{
	m_pTotalTrace.get()->GetAircraftTracePoint1(traceID,dTrace);

}
