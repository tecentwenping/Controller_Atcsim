#include "publicdata.h"
double					CPublicData::m_dCenterLongtitude = 0.00;
double					CPublicData::m_dCenterLatitude = 0.00;
MapGateName				CPublicData::m_mapGateName;
MapTaxiLine				CPublicData::m_mapTaxiLine;
MapFixPoint				CPublicData::m_mapFixPoint;
VecGateInformation		CPublicData::m_VecGateInformation_T1;
VecGateInformation		CPublicData::m_VecGateInformation_T2;
MapTowerAircraftPacket	CPublicData::m_mapTowerAircraftPacket;
MapAircraftTrace		CPublicData::m_mapAircraftTrace;
VecFlyPlanFromDB		CPublicData::m_vecFlyPlanFromDB;
VecGateInformation		CPublicData::m_VecInPathInformation;
VecGateInformation		CPublicData::m_VecOutPathInformation;
MapPathPoint			CPublicData::m_MapPathPoint;
MapPath					CPublicData::m_MapInPath;
MapPath					CPublicData::m_MapOutPath;
std::vector<QString>	CPublicData::m_vecCurrentFlyPlan;
#include "public/Coordinate.h"
CPublicData::CPublicData()
{

}

CPublicData::CPublicData( double dCenterLongtitude,double dCenterLatitude )
{
	m_dCenterLongtitude = dCenterLongtitude;
	m_dCenterLatitude   = dCenterLatitude;
	//Coordinate test;
	//double dCenterX = 0.0,dCenterY = 0.0;
	//test.ConvertLongLat2XY(m_dCenterLongtitude,m_dCenterLatitude,dCenterX,dCenterY);
}
CPublicData::~CPublicData()
{

}

void CPublicData::GetGateInformation_T1( VecGateInformation& vecGateInforamtion )
{
	vecGateInforamtion = m_VecGateInformation_T1;
}

void CPublicData::GetGateInformation_T2( VecGateInformation& vecGateInformation )
{
	vecGateInformation = m_VecGateInformation_T2;

}
VecGateInformation& CPublicData::GetGateInformation_T1()
{
	return m_VecGateInformation_T1;
}
VecGateInformation& CPublicData::GetGateInformaiton_T2()
{
	return m_VecGateInformation_T2;

}
void CPublicData::SetGateInformation_T1( const VecGateInformation& VecGateInformation )
{
      m_VecGateInformation_T1 = VecGateInformation;
}
void CPublicData::SetGateInformation_T2( const VecGateInformation& VecGateInformation )
{
	m_VecGateInformation_T2 = VecGateInformation;
}
void CPublicData::SetGateName( const MapGateName& mapGateName )
{
	m_mapGateName = mapGateName;
}
void CPublicData::SetTaxiLine( const MapTaxiLine& mapTaxiLine )
{
	m_mapTaxiLine = mapTaxiLine;
}
void CPublicData::SetFixPoint( const MapFixPoint& mapFixPoint )
{
	m_mapFixPoint = mapFixPoint;
}

void CPublicData::SetTowerAircraftPacket( const MapTowerAircraftPacket& mapTowerAircraftPacket )
{
	m_mapTowerAircraftPacket = mapTowerAircraftPacket;

}
void CPublicData::SetCenterCoordinate( double& dCenterLongtitude,double& dCenterLatitude )
{
	dCenterLongtitude = m_dCenterLongtitude;
	dCenterLatitude	  = m_dCenterLatitude;
}

void CPublicData::SetAircraftTrace( const MapAircraftTrace& mapAircraftTraceNewVersion )
{
	m_mapAircraftTrace = mapAircraftTraceNewVersion;
}

MapAircraftTrace& CPublicData::GetMapAircraftTrace() const
{

	return m_mapAircraftTrace;
}

void CPublicData::GetMapAircraftTrace( MapAircraftTrace& mpAircraftTrace)
{
     mpAircraftTrace = m_mapAircraftTrace;
}

void CPublicData::GetVecFlyPlanFromDB( VecFlyPlanFromDB& vecFlyPlanFromDB )
{

	vecFlyPlanFromDB = m_vecFlyPlanFromDB;
}  

void CPublicData::SetVecFlyPlanFromDB( VecFlyPlanFromDB& vecFlyPlanFromDB )
{
	m_vecFlyPlanFromDB = vecFlyPlanFromDB;
}

void CPublicData::SetInPathInformation( const MapPath& mapPathInformation )
{
    m_MapInPath = mapPathInformation;
}

void CPublicData::SetOutPathInformation( const MapPath& mapPathInformation )
{
	m_MapOutPath = mapPathInformation;

}

void CPublicData::SetPathPoint( int iFlyID,QStringList& PathPointList )
{
	m_MapPathPoint.insert(std::make_pair(iFlyID,PathPointList));
}

void CPublicData::GetPathPoint( int iFlyID,QStringList& vecPathPoint )
{
	MapPathPoint::iterator Iter = m_MapPathPoint.find(iFlyID);
	if(Iter != m_MapPathPoint.end())
	{
		vecPathPoint = Iter->second;
	}

}

void CPublicData::GetPathInformation( MapPath& mapPath,int flag )
{
	switch(flag)
	{
	case 1:
		mapPath = m_MapInPath;
		break;
	case  2:
		mapPath = m_MapOutPath;
	}

}

void CPublicData::GetMapGateName( MapGateName& mpGateName)
{
	mpGateName = m_mapGateName;
}

void CPublicData::GetMapTaxiLine( MapTaxiLine& mpTaxLine)
{
	mpTaxLine = m_mapTaxiLine;

}

void CPublicData::GetMapFixPoint( MapFixPoint& mpFixPoint)
{
	mpFixPoint = m_mapFixPoint;

}
void CPublicData::GetMapTowerAircraftPacket( MapTowerAircraftPacket& mpTowerAircraft)
{
	mpTowerAircraft = m_mapTowerAircraftPacket;

}

MapTowerAircraftPacket& CPublicData::GetMapTowerAircraftPacket()
{
   return m_mapTowerAircraftPacket;
}
void CPublicData::SetCurrentFlyPlan(const QString& singleFlyPlan)
{
	m_vecCurrentFlyPlan.push_back(singleFlyPlan);
}
void CPublicData::GetCurrentFlyPlan(std::vector<QString>& vecCurFLyPlan)
{
   vecCurFLyPlan = m_vecCurrentFlyPlan;
}






