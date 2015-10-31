#include "InitPointInformation.h"
#include "DBOperator/DataBase.h"
#include "public/PublicStruct.h"
#include "Manager/DataManager.h"
#include "public/Mutex.h"
#include <QString>
#include <QSqlQuery>
#include <assert.h>
CInitPointInformation::CInitPointInformation()
{
	DataBaseAccessObj::GetSQLAccessInstance()->OpenDB();
}

CInitPointInformation::~CInitPointInformation()
{
	DataBaseAccessObj::GetSQLAccessInstance()->CloseDB();
}

void CInitPointInformation::GetRoadFixPointFromDB()
{

	
}
void CInitPointInformation::GetFixPointFromDB()
{
	QString fixPointSqlStr = QString("select fixpoint_id,fixpoint_name,x,y,z from fixpoint");
	QSqlQuery fixpointQuery = QueryDataFromDB(fixPointSqlStr);
    typedef std::multimap<std::string,PublicDataStruct::FixPoint> MapFixPoint;
	CQMutex mutex;
	MapFixPoint mpFixPoint;
	while(fixpointQuery.next())
	{
		PublicDataStruct::FixPoint fixPointTemp;
		fixPointTemp.SetFixPointID(fixpointQuery.value(0).toInt());
		fixPointTemp.SetFixPointName(fixpointQuery.value(1).toString().toStdString());
		fixPointTemp.SetFixPointX(fixpointQuery.value(2).toDouble());
		fixPointTemp.SetFixPointY(fixpointQuery.value(3).toDouble());
		fixPointTemp.SetFixPointZ(fixpointQuery.value(4).toDouble());
		mpFixPoint.insert(std::make_pair(fixpointQuery.value(1).toString().toStdString(),fixPointTemp));
		
	}
	mutex.MyLock();
	theData::instance().SetMapFixPoint(mpFixPoint);
	mutex.MyUnlock();
}
void CInitPointInformation::GetTaxiLineFromDB()
{
	QString taxiLineSqlStr = QString("select road.road_id,road.road_name,road_fixpoint.key_id,fixpoint.fixpoint_name,\
									 fixpoint.x,fixpoint.y from road,fixpoint,road_fixpoint where \
									 road.road_id = road_fixpoint.road_id and road_fixpoint.key_id = fixpoint.fixpoint_id \
									 and road.type = 1");
	QSqlQuery resultQuery = QueryDataFromDB(taxiLineSqlStr);
	typedef std::multimap<int,PublicDataStruct::TaxiLine>  MapTaxiLine;
	MapTaxiLine mpTaxiLine;
	CQMutex mutex;
	while(resultQuery.next())
	{
		PublicDataStruct::TaxiLine TaxiLineStructTemp;
		TaxiLineStructTemp.SetRoadID(resultQuery.value(0).toInt());
		TaxiLineStructTemp.SetRoadName(resultQuery.value(1).toString().toStdString());
		TaxiLineStructTemp.SetFixPointID(resultQuery.value(2).toInt());
		TaxiLineStructTemp.SetFixPointName(resultQuery.value(3).toString().toStdString());
		TaxiLineStructTemp.SetFixPoint_X(resultQuery.value(4).toDouble());
		TaxiLineStructTemp.SetFixPoiint_Y(resultQuery.value(5).toDouble());
		mpTaxiLine.insert(std::make_pair(TaxiLineStructTemp.GetRoadID(),TaxiLineStructTemp));
	}
	mutex.MyLock();
	theData::instance().SetMapTaxLine(mpTaxiLine);
	mutex.MyUnlock();
}
QSqlQuery& CInitPointInformation::QueryDataFromDB( const QString& sqlStr )
{
	QString sSqlStr = sqlStr;
	//DataBaseAccessObj::GetSQLAccessInstance()->OpenDB();
	m_queryObj = DataBaseAccessObj::GetSQLAccessInstance()->SQLQuery(sSqlStr);
	return m_queryObj;
}
void CInitPointInformation::Init()
{
	GetFixPointFromDB();
	GetTaxiLineFromDB();
	//DataBaseAccessObj::GetSQLAccessInstance()->CloseDB();
}
