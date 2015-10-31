#include "getdatafromdb.h"
#include "airport_data_objs.h"
#include "airspace_data_objs.h"
#include "airport_packet.h"
#include "totalbasedata.h"
#include <QVariant>
#include <iostream>
#include <assert.h>

GetDataFromDB::GetDataFromDB()
{
	m_AckAirportDataPacket = NULL;
	m_AckAirspaceDataPacket = NULL;
	m_pDBAccessObj = NULL;
	m_pDataBase = NULL;
   m_pDataBase=new TotalBaseData;
}
GetDataFromDB::~GetDataFromDB()
{
	if(m_pDBAccessObj!=NULL)
	{
		delete m_pDBAccessObj;
	     m_pDBAccessObj=NULL;
	}
	if(NULL !=m_pDataBase)
	{
		delete m_pDataBase;
		m_pDataBase = NULL;
	}
	if(m_AckAirportDataPacket!=NULL)
	{
		delete m_AckAirportDataPacket;
		m_AckAirportDataPacket=NULL;
	}
}
void GetDataFromDB::OnBaseDataPacket( const AckAirportDataPacket* sAirportDataPacket )
{
   SetBaseData(sAirportDataPacket->m_vecAirport);
   SetBaseData(sAirportDataPacket->m_vcRunWayData);
   SetBaseData(sAirportDataPacket->m_vcRoadData);
   SetBaseData(sAirportDataPacket->m_vcFixpointData);
   SetBaseData(sAirportDataPacket->m_vecGate);
   SetBaseData(sAirportDataPacket->m_vecTower);
   SetBaseData(sAirportDataPacket->m_vecAirportModel);
   SetBaseData(sAirportDataPacket->m_vecStar);

}
void GetDataFromDB::OnBaseDataPacket( const AckAirspaceDataPacket* sAirspaceDataPacket )
{

	SetBaseData(sAirspaceDataPacket->m_vecBeacon);
	SetBaseData(sAirspaceDataPacket->m_vecSector);
	SetBaseData(sAirspaceDataPacket->m_vecRestrictAera);
	SetBaseData(sAirspaceDataPacket->m_vecCourse);
	SetBaseData(sAirspaceDataPacket->m_vecMsawArea);
}
void GetDataFromDB::QueryDataFromDB()
{
	 m_pDBAccessObj=new AirPort_DBAccess;
	 assert(m_pDBAccessObj != NULL);
	if(!m_pDBAccessObj->OpenDB())
	{
		std::cout<<"Open database failed!"<<std::endl;
		return;
	}
	GetAirPortDataFromDB();
	GetAirSpaceDataFromDB();
	OnBaseDataPacket(m_AckAirportDataPacket);
	OnBaseDataPacket(m_AckAirspaceDataPacket);
	m_pDBAccessObj->CloseDB();

}
void GetDataFromDB::GetAirPortDataFromDB()
{
	m_AckAirportDataPacket = new AckAirportDataPacket;
	GetAirportData();
	GetRunWayData();
	GetRoadData();
	GetFixpointData();
	GetGateData();
	GetTowerData();
	GetAirportModelData();
	OnBaseDataPacket(m_AckAirportDataPacket);
}

void GetDataFromDB::GetAirSpaceDataFromDB()
{
	m_AckAirspaceDataPacket = new AckAirspaceDataPacket;
	GetBeaconData();
	GetSectorData();
	GetRestricAreaData();
	GetCourseData();
	GetMsawAreaData();
}
TotalBaseData * GetDataFromDB::GetTotalBaseData()
{
	return m_pDataBase;
   
}
void GetDataFromDB::GetAirportData()
{
	 AirportData airportDataTemp;
	 QString qAirprotDataStr("select * from airport");
	 QSqlQuery qAirportQuery = m_pDBAccessObj->SQLQuery(qAirprotDataStr);
	 while(qAirportQuery.next())
	 {
		 airportDataTemp.SetAirportID(qAirportQuery.value(0).toInt());
		 airportDataTemp.SetAirspaceID(qAirportQuery.value(1).toInt());
		 airportDataTemp.SetAirportCode(qAirportQuery.value(2).toString().toStdString());
		 airportDataTemp.SetAirportName(qAirportQuery.value(3).toString().toStdString());
		 airportDataTemp.SetCenterPointLongitude(qAirportQuery.value(4).toDouble());
		 airportDataTemp.SetCenterPointLatitude(qAirportQuery.value(5).toDouble());
		 airportDataTemp.SetElevation(qAirportQuery.value(6).toDouble());
		 airportDataTemp.SetMegaticDiff(qAirportQuery.value(7).toDouble());
		 airportDataTemp.SetMainRunway(qAirportQuery.value(8).toInt());
		 airportDataTemp.SetDefaultEnvID(qAirportQuery.value(9).toInt());
		 airportDataTemp.SetHeading(qAirportQuery.value(10).toDouble());
		 m_AckAirportDataPacket->m_vecAirport.push_back(airportDataTemp);
	 }
}
void GetDataFromDB::GetRunWayData()
{
	RunwayData  runwayDataTemp;
	 QString qRunwayDataStr("select * from runway");
	 QSqlQuery qRunwayQuery  = m_pDBAccessObj->SQLQuery(qRunwayDataStr);
	  while(qRunwayQuery.next())
	  {
		  runwayDataTemp.SetRunWayID(qRunwayQuery.value(0).toInt());
		  runwayDataTemp.SetAirportID(qRunwayQuery.value(1).toInt());
		  runwayDataTemp.SetRunwayName(qRunwayQuery.value(2).toString().toStdString());
		  runwayDataTemp.SetCenterPointLongitude(qRunwayQuery.value(3).toDouble());
		  runwayDataTemp.SetCenterPointLatitude(qRunwayQuery.value(4).toDouble());
		  runwayDataTemp.SetLength(qRunwayQuery.value(5).toDouble());
		  runwayDataTemp.SetHeight(qRunwayQuery.value(6).toDouble());
		  runwayDataTemp.SetWidth(qRunwayQuery.value(7).toDouble());
		  runwayDataTemp.SetHeading(qRunwayQuery.value(8).toDouble());
		  runwayDataTemp.SetDryFrictionfactor(qRunwayQuery.value(9).toInt());
		  runwayDataTemp.SetGradient(qRunwayQuery.value(10).toDouble());
		  runwayDataTemp.SetStartX(qRunwayQuery.value(11).toDouble());
		  runwayDataTemp.SetStartY(qRunwayQuery.value(12).toDouble());
		  runwayDataTemp.SetEndX(qRunwayQuery.value(13).toDouble());
		  runwayDataTemp.SetEndY(qRunwayQuery.value(14).toDouble());
		  runwayDataTemp.SetDryFrictionfactor_start(qRunwayQuery.value(15).toDouble());
		  runwayDataTemp.SetDryFrictionfactor_mid(qRunwayQuery.value(16).toDouble());
		  runwayDataTemp.SetDryFrictionfactor_end(qRunwayQuery.value(17).toDouble());
		  runwayDataTemp.SetDryFrictionfactor(qRunwayQuery.value(18).toDouble());
		  runwayDataTemp.SetMegaticDiff(qRunwayQuery.value(19).toDouble());
		  runwayDataTemp.SetLandingPoint(qRunwayQuery.value(20).toDouble());
		  m_AckAirportDataPacket->m_vcRunWayData.push_back(runwayDataTemp);
	  }
}
void GetDataFromDB::GetRoadData()
{
	  RoadData    roadDataTemp;
	  QString qFixpointOnRoadStr("select * from road_fixpoint");
	  QString qRoadDataStr("select * from road");
	  QSqlQuery qRoadQuery    = m_pDBAccessObj->SQLQuery(qRoadDataStr);
	  QSqlQuery qFixpointOnRoadQuery = m_pDBAccessObj->SQLQuery(qFixpointOnRoadStr);
	  while(qFixpointOnRoadQuery.next())
	  {
		  RoadFixpointData *roadFixpointData=new RoadFixpointData;
		  boost::shared_ptr<RoadFixpointData> roadFixpointDataTemp(roadFixpointData);
		  roadFixpointDataTemp.get()->SetRoadID(qFixpointOnRoadQuery.value(0).toInt());
		  roadFixpointDataTemp.get()->SetSequence(qFixpointOnRoadQuery.value(1).toInt());
		  roadFixpointDataTemp.get()->SetFixpointID(qFixpointOnRoadQuery.value(3).toInt());
		  m_mFixpointOnRoadData.insert(std::make_pair(roadFixpointDataTemp.get()->GetRoadID(),roadFixpointDataTemp));
	  }
	  while(qRoadQuery.next())
	  {
		  roadDataTemp.SetRoadID(qRoadQuery.value(0).toInt());
		  roadDataTemp.SetAirportID(qRoadQuery.value(0).toInt());
		  roadDataTemp.SetRoadName(qRoadQuery.value(1).toString().toStdString());
		  roadDataTemp.SetRoadType(qRoadQuery.value(2).toInt());
		  roadDataTemp.SetWidth(qRoadQuery.value(3).toInt());
		  roadDataTemp.SetMaxAircraft(qRoadQuery.value(4).toInt());
		  std::vector<boost::shared_ptr<RoadFixpointData> > vRoadFixpointdata;
		  int iFixpointOnRoad = m_mFixpointOnRoadData.count(roadDataTemp.GetRoadID());
		  for(int i = 0; i != iFixpointOnRoad; ++ i)
		  {
			  std::multimap<int,boost::shared_ptr<RoadFixpointData> >::iterator iter = m_mFixpointOnRoadData.find(roadDataTemp.GetRoadID());
			  if(iter != m_mFixpointOnRoadData.end())
			  {
				  vRoadFixpointdata.push_back(iter->second);
				  m_mFixpointOnRoadData.erase(iter);
				  iter = m_mFixpointOnRoadData.begin();
			  }
		  }
		  roadDataTemp.SetFixpoints(vRoadFixpointdata);
		  vRoadFixpointdata.clear();
		  m_AckAirportDataPacket->m_vcRoadData.push_back(roadDataTemp);
	  } 
}
void GetDataFromDB::GetFixpointData()
{
	 FixpointData fixpointDataTemp;
	QString qFixpointDataStr("select * from fixpoint");
	 QSqlQuery qFixpointQuery = m_pDBAccessObj->SQLQuery(qFixpointDataStr);
	 while(qFixpointQuery.next())
	 {
		 fixpointDataTemp.SetFixpointID(qFixpointQuery.value(0).toInt());
		 fixpointDataTemp.SetIconID(qFixpointQuery.value(1).toInt());
		 fixpointDataTemp.SetFixpointName(qFixpointQuery.value(2).toString().toStdString());
		 fixpointDataTemp.SetAirportID(qFixpointQuery.value(3).toInt());
		 fixpointDataTemp.SetFixpointType(qFixpointQuery.value(4).toDouble());
		 fixpointDataTemp.SetX(qFixpointQuery.value(5).toDouble());
		 fixpointDataTemp.SetY(qFixpointQuery.value(6).toDouble());
		 fixpointDataTemp.SetZ(qFixpointQuery.value(7).toDouble());
		 fixpointDataTemp.SetIsWaitingPoint(qFixpointQuery.value(8).toInt());
		 m_AckAirportDataPacket->m_vcFixpointData.push_back(fixpointDataTemp);
	 }
}
void GetDataFromDB::GetGateData()
{
	  GateData    gateDataTemp;
	  QString qGateDataStr("select * from gate");
      QSqlQuery qGateQuery = m_pDBAccessObj->SQLQuery(qGateDataStr);
      while (qGateQuery.next())
     {
	gateDataTemp.SetGateID(qGateQuery.value(0).toInt());
	gateDataTemp.SetAirportID(qGateQuery.value(1).toInt());
	gateDataTemp.SetGateName(qGateQuery.value(2).toString().toStdString());
	gateDataTemp.SetRoadID(qGateQuery.value(3).toInt());
	gateDataTemp.SetLength(qGateQuery.value(4).toDouble());
	gateDataTemp.SetInGateDataFixpointID(qGateQuery.value(5).toInt());
	gateDataTemp.SetGateFixpointID(qGateQuery.value(6).toInt());
	gateDataTemp.SetMaxAircraftID(qGateQuery.value(7).toInt());
	gateDataTemp.SetInternationalType(qGateQuery.value(8).toInt());
	gateDataTemp.SetBelongedCompanyID(qGateQuery.value(9).toInt());
	gateDataTemp.SetStartPosition(qGateQuery.value(10).toInt());
	gateDataTemp.SetIsDirectTax(qGateQuery.value(11).toInt());
	gateDataTemp.SetRoutineInLine(qGateQuery.value(12).toInt());
	gateDataTemp.SetRoutinOutLine(qGateQuery.value(13).toInt());
	gateDataTemp.SetRoutinToRunway(qGateQuery.value(14).toInt());
	m_AckAirportDataPacket->m_vecGate.push_back(gateDataTemp);
}
}
void GetDataFromDB::GetTowerData()
{
	 Tower       towerDataTemp;
	 QString qTowerDataStr("select * from tower");
	 QSqlQuery qTowerQuery = m_pDBAccessObj->SQLQuery(qTowerDataStr);
	 while(qTowerQuery.next())
	{
	  towerDataTemp.SetTowerID(qTowerQuery.value(0).toInt());
	  towerDataTemp.SetAirportID(qTowerQuery.value(1).toInt());
	  towerDataTemp.SetIconID(qTowerQuery.value(2).toInt());
	  towerDataTemp.SetTowerName(qTowerQuery.value(3).toString().toStdString());
	  towerDataTemp.SetLongitude(qTowerQuery.value(4).toDouble());
	  towerDataTemp.SetLatitude(qTowerQuery.value(5).toDouble());
	  towerDataTemp.SetHeight(qTowerQuery.value(6).toDouble());
	  towerDataTemp.SetHeading(qTowerQuery.value(7).toDouble());
	  towerDataTemp.SetPitch(qTowerQuery.value(8).toDouble());
	  towerDataTemp.SetRoll(qTowerQuery.value(9).toDouble());
	  m_AckAirportDataPacket->m_vecTower.push_back(towerDataTemp);
  }
}
void GetDataFromDB::GetAirportModelData()
{
	  AirportModel airportModelTemp;
	  QString qAirportDataModelStr("select * from airport_model");
	  QSqlQuery qAirportModelQuery = m_pDBAccessObj->SQLQuery(qAirportDataModelStr);
	  while(qAirportModelQuery.next())
	  {
		  airportModelTemp.SetModelID(qAirportModelQuery.value(0).toInt());
		  airportModelTemp.SetAirportID(qAirportModelQuery.value(1).toInt());
		  airportModelTemp.SetModelName(qAirportModelQuery.value(2).toString().toStdString());
		  airportModelTemp.SetModelFile(qAirportModelQuery.value(3).toString().toStdString());
		  m_AckAirportDataPacket->m_vecAirportModel.push_back(airportModelTemp);
	  }
}
void GetDataFromDB::GetBeaconData()
{    
	    Beacon beaconTemp;
	    QString qBeaconStr("select * from beacon");
	    QSqlQuery qBeaconQuery = m_pDBAccessObj->SQLQuery(qBeaconStr);
		while(qBeaconQuery.next())
		{
			beaconTemp.SetBeaconID(qBeaconQuery.value(0).toInt());
			beaconTemp.SetBeaconCode(qBeaconQuery.value(2).toString().toStdString());
			beaconTemp.SetBeaconName(qBeaconQuery.value(3).toString().toStdString());
			beaconTemp.SetLongitude(qBeaconQuery.value(4).toDouble());
			beaconTemp.SetLatitude(qBeaconQuery.value(5).toDouble());
			beaconTemp.SetHeight(qBeaconQuery.value(6).toDouble());
			beaconTemp.SetType(qBeaconQuery.value(7).toInt());
			beaconTemp.SetIconID(qBeaconQuery.value(8).toInt());
			// beaconTemp.SetIsStdReport(qBeaconQuery.value(9).toBit());
			m_AckAirspaceDataPacket->m_vecBeacon.push_back(beaconTemp);
		}
}
void GetDataFromDB::GetSectorData()
{
	  Sector	sectorTemp;
      QString qSectorStr("select * from sector");
      QSqlQuery qSectorQuery = m_pDBAccessObj->SQLQuery(qSectorStr);
      while (qSectorQuery.next())
    {
	 sectorTemp.SetSectorID(qSectorQuery.value(0).toInt());
	 sectorTemp.SetSectorName(qSectorQuery.value(1).toString().toStdString());
	 sectorTemp.SetSectorFrequency(qSectorQuery.value(2).toDouble());
	 m_AckAirspaceDataPacket->m_vecSector.push_back(sectorTemp);
 }
}
void GetDataFromDB::GetRestricAreaData()
{
	 RestrictArea restricAreaTemp;
	QString qRestricAreaStr("select * from restrict_area");
	QSqlQuery qRestricAreaQuery = m_pDBAccessObj->SQLQuery(qRestricAreaStr);
	while(qRestricAreaQuery.next())
  {
	  restricAreaTemp.m_iRestrictAreaID = qRestricAreaQuery.value(0).toInt();
	  restricAreaTemp.m_enumAreaType = (AREA_TYPE)qRestricAreaQuery.value(1).toInt();
	  restricAreaTemp.m_strRestrictAreaName = qRestricAreaQuery.value(2).toString().toStdString();
	  int is_used = qRestricAreaQuery.value(3).toInt();
	  if(is_used == 0)
	  {
		  restricAreaTemp.m_bIsUsed = false;
	  }
	  else
	  {
		  restricAreaTemp.m_bIsUsed = true;
	  }
	  restricAreaTemp.m_iLineStyle = qRestricAreaQuery.value(4).toInt();
	  restricAreaTemp.m_iColor = qRestricAreaQuery.value(5).toInt();
	  restricAreaTemp.m_dLowestAlt = qRestricAreaQuery.value(6).toDouble();
	  restricAreaTemp.m_dHighestAlt = qRestricAreaQuery.value(7).toDouble();
	  restricAreaTemp.m_dStartTime = qRestricAreaQuery.value(8).toDouble();
	  restricAreaTemp.m_dEndTime = qRestricAreaQuery.value(9).toDouble();
	  m_AckAirspaceDataPacket->m_vecRestrictAera.push_back(restricAreaTemp);
  }
}
void GetDataFromDB::GetCourseData()
{
	Course	courseTemp;
	QString qRoutePtStr("select * from route_pt");
	QString qCourseStr("select * from course");
	QSqlQuery qRoutePtQuery = m_pDBAccessObj->SQLQuery(qRoutePtStr);
	QSqlQuery qCourseQuery = m_pDBAccessObj->SQLQuery(qCourseStr);

	while(qRoutePtQuery.next())
  {
	RoutePt   *routePtData = new RoutePt;
	boost::shared_ptr<RoutePt> routePtTemp(routePtData);
    routePtTemp.get()->m_iID = qRoutePtQuery.value(0).toInt();
	routePtTemp.get()->m_eOwnerType = (ENUM_ROUTEPT_OWNER_TYPE)qRoutePtQuery.value(1).toInt();
	routePtTemp.get()->m_iOwnerID = qRoutePtQuery.value(2).toInt();
	routePtTemp.get()->m_iSequence = qRoutePtQuery.value(3).toInt();
	routePtTemp.get()->m_iRoutePtID = qRoutePtQuery.value(4).toInt();
	routePtTemp.get()->m_strRoutePtName = qRoutePtQuery.value(5).toString().toStdString();
	routePtTemp.get()->m_eRoutePtType =(ENUM_ROUTEPT_TYPE) qRoutePtQuery.value(6).toInt();
	routePtTemp.get()->m_dLatitude = qRoutePtQuery.value(7).toDouble();
	routePtTemp.get()->m_dLongtitude = qRoutePtQuery.value(8).toDouble();
	routePtTemp.get()->m_dAltitude = qRoutePtQuery.value(9).toDouble();
	routePtTemp.get()->m_eLegType = (ENUM_ROUTEPT_LEG_TYPE)qRoutePtQuery.value(10).toInt();
	routePtTemp.get()->m_dRadius = qRoutePtQuery.value(11).toDouble();
	int iClockWise = qRoutePtQuery.value(12).toInt();
	switch(iClockWise)
	{
	case 0:
		routePtTemp.get()->m_bClockWise = false;
		break;
	case 1:
		routePtTemp.get()->m_bClockWise = true;
		break;
	}
	routePtTemp.get()->m_dGrade = qRoutePtQuery.value(13).toDouble();
	int iSprialTurnMode = qRoutePtQuery.value(14).toInt();
	switch(iSprialTurnMode)
	{
	case 0:
		routePtTemp.get()->m_dGrade = false;
		break;
	case 1:
		routePtTemp.get()->m_dGrade = true;
		break;
	}
	routePtTemp.get()->m_eTurnDirt = (ENUM_ROUTEPT_TURN_DIRECTION)qRoutePtQuery.value(15).toInt();
	m_mRoutePtData.insert(std::make_pair(routePtTemp.get()->m_iOwnerID,routePtTemp));

  }
  while(qCourseQuery.next())
  {
	  courseTemp.m_iCourseId = qCourseQuery.value(0).toInt();
	  courseTemp.m_iAirspaceId = qCourseQuery.value(1).toInt();
	  courseTemp.m_strCourseName = qCourseQuery.value(2).toString().toStdString();
	  courseTemp.m_bDoubleLine = qCourseQuery.value(3).toDouble();
	  courseTemp.m_dWidth = qCourseQuery.value(4).toDouble();
      int iCount = m_mRoutePtData.count(courseTemp.m_iCourseId);
	  std::vector<boost::shared_ptr<RoutePt> > vRoutePtDdata;
	  for(int i=0; i!=iCount; ++i)
	  {
		  std::multimap<int,boost::shared_ptr<RoutePt> >::iterator iter = m_mRoutePtData.find(courseTemp.m_iCourseId);
		  if(iter != m_mRoutePtData.end())
		  {
			  vRoutePtDdata.push_back(iter->second);
			  m_mRoutePtData.erase(iter);
			  iter = m_mRoutePtData.begin();
		  }
	  }
	  courseTemp.m_vecRoutePt = vRoutePtDdata;
	  vRoutePtDdata.clear();
	  m_AckAirspaceDataPacket->m_vecCourse.push_back(courseTemp);
  }
}
void GetDataFromDB::GetMsawAreaData()
{
	MsawArea	msawAreaTemp;
	QString qPointPostionStr("select * from point_postion");
	QString qMsawAreaStr("select * from msaw_area");
	QSqlQuery qPointPostionQuery = m_pDBAccessObj->SQLQuery(qPointPostionStr);
	QSqlQuery qMsawAreaQuery = m_pDBAccessObj->SQLQuery(qMsawAreaStr);
	while(qPointPostionQuery.next())
	{
		PointPosition *pointPostion = new PointPosition;
		boost::shared_ptr<PointPosition> pointPostionTemp(pointPostion);
		pointPostionTemp.get()->m_iPointPositionID = qPointPostionQuery.value(0).toInt();
		pointPostionTemp.get()->m_strPointPositionName = qPointPostionQuery.value(1).toString().toStdString();
		pointPostionTemp.get()->m_iSequence = qPointPostionQuery.value(2).toInt();
		pointPostionTemp.get()->m_enumOwnerType =(POINT_OWNER_TYPE)qPointPostionQuery.value(3).toInt();
		pointPostionTemp.get()->m_iOwnerID = qPointPostionQuery.value(4).toInt();
		pointPostionTemp.get()->m_dLongtitude = qPointPostionQuery.value(5).toDouble();
		pointPostionTemp.get()->m_dLatitude = qPointPostionQuery.value(6).toDouble();
		pointPostionTemp.get()->m_dHeight = qPointPostionQuery.value(7).toDouble();
		m_mPointPosition.insert(std::make_pair(pointPostionTemp.get()->m_iOwnerID,pointPostionTemp));

	}
	while(qMsawAreaQuery.next())
	{
		msawAreaTemp.m_iMsawAreaID = qMsawAreaQuery.value(0).toInt();
		msawAreaTemp.m_strMsawAreaName = qMsawAreaQuery.value(1).toString().toStdString();
		msawAreaTemp.m_iLineStyle = qMsawAreaQuery.value(2).toInt();
		msawAreaTemp.m_iColor = qMsawAreaQuery.value(3).toInt();
		msawAreaTemp.m_dHeight = qMsawAreaQuery.value(4).toDouble();
		int iCount = m_mPointPosition.count(msawAreaTemp.m_iMsawAreaID);
		std::vector<boost::shared_ptr<PointPosition> > vPointPostionData;
		for(int i = 0; i!= iCount; ++i)
		{
			std::multimap<int,boost::shared_ptr<PointPosition> >::iterator iter = m_mPointPosition.find(msawAreaTemp.m_iMsawAreaID);
			if(iter != m_mPointPosition.end())
			{
				vPointPostionData.push_back(iter->second);
				m_mPointPosition.erase(iter);
				iter = m_mPointPosition.begin();
			}
		}
		msawAreaTemp.m_vMsawAreaPoint = vPointPostionData;
		vPointPostionData.clear();
		m_AckAirspaceDataPacket->m_vecMsawArea.push_back(msawAreaTemp);
	}
}
void GetDataFromDB::SetBaseData( const AirportData& airportData )
{
	m_pDataBase->SetBaseData(airportData);
}
void GetDataFromDB::SetBaseData( const std::vector<RunwayData>& vRunwayData )
{
	m_pDataBase->SetBaseData(vRunwayData);
}
void GetDataFromDB::SetBaseData( const std::vector<RoadData>& vRoadData )
{
	m_pDataBase->SetBaseData(vRoadData);
}
void GetDataFromDB::SetBaseData( const std::vector<FixpointData>& vFixpointData )
{
	m_pDataBase->SetBaseData(vFixpointData);
}
void GetDataFromDB::SetBaseData( const std::vector<GateData>& vGateData )
{
	m_pDataBase->SetBaseData(vGateData);
}
void GetDataFromDB::SetBaseData( const std::vector<Tower>& vTowerData )
{
	m_pDataBase->SetBaseData(vTowerData);
}
void GetDataFromDB::SetBaseData( const std::vector<AirportModel>& vAirportmodelData )
{
	m_pDataBase->SetBaseData(vAirportmodelData);
}
void GetDataFromDB::SetBaseData( const std::vector<AirportData>& vAirportData )
{
	m_pDataBase->SetBaseData(vAirportData);
}
void GetDataFromDB::SetBaseData( const std::vector<Star>& vStarData )
{
	m_pDataBase->SetBaseData(vStarData);
}
void GetDataFromDB::SetBaseData( const std::vector<Beacon>& vBeaconData )
{
	m_pDataBase->SetBaseData(vBeaconData);
}
void GetDataFromDB::SetBaseData( const std::vector<Sector>& vSectorData )
{
	m_pDataBase->SetBaseData(vSectorData);
}
void GetDataFromDB::SetBaseData( const std::vector<RestrictArea>& vRestricAreaData )
{
	m_pDataBase->SetBaseData(vRestricAreaData);
}
void GetDataFromDB::SetBaseData( const std::vector<Course>& vCourseData )
{
	m_pDataBase->SetBaseData(vCourseData);
}
void GetDataFromDB::SetBaseData( const std::vector<MsawArea>& vMsawAreaData )
{
	m_pDataBase->SetBaseData(vMsawAreaData);
}

