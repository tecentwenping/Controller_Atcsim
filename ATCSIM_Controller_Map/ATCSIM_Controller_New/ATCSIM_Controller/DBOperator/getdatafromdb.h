#ifndef GETDATAFROMDB_H
#define GETDATAFROMDB_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: GetDataFromDB
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/11/12
  【描  述】:  此类主要作用是从数据库中读取文件，并转存文件到TotalBaseData
  【其  它】:   
**************************************************************************/

#include <vector>
#include <map>
#include <QSqlQuery>
#include "airport_dbaccess.h"
#include "./boost/shared_ptr.hpp"
class TotalBaseData;
class AckAirportDataPacket;
class AckAirspaceDataPacket;
//机场点
class AirportData;
class RunwayData;
class RoadData;
class RoadFixpointData;
class FixpointData;
class GateData;
class Tower;
class AirportModel;
class Star;
//空域点
class Beacon;
class Sector;
class RestrictArea;
class Course;
class MsawArea;
class RoutePt;
class PointPosition;

class GetDataFromDB
{


public:
	GetDataFromDB();
	~GetDataFromDB();
	/*********************************************************
	*函数名：QueryDataFromDB
	*函数功能：提供给外部的函数，里面调用私有函数，将查询数据库得
	到的结果进行存储，具体承担存储任务的是TotalBaseData类的对象m_pDatabase，
	查询语句已经固定，这是初期版本
	*变量：
	**********************************************************/
	 void QueryDataFromDB();
	 /*********************************************************
	 *函数名：GetTotalBaseData
	 *函数功能：获取从数据库查询的数据
	 *变量：
	 **********************************************************/
	 TotalBaseData * GetTotalBaseData();
protected:
	/*********************************************************
	*函数名：OnBaseDataPacket
	*函数功能：转存信息的函数
	*变量：const AckAirportDataPacket* rParama机场数据包
	**********************************************************/
	void OnBaseDataPacket(const AckAirportDataPacket* rParama);
	/*********************************************************
	*函数名：OnBaseDataPacket
	*函数功能：转存信息的函数
	*变量：const AckAirportDataPacket* rParama空域数据包
	**********************************************************/
	void OnBaseDataPacket(const AckAirspaceDataPacket* rParama);
protected:
	/*********************************************************
	*函数名：SetBaseData
	*函数功能：具体承担转存数据包的函数，提供了不同的版本
	*变量：const AirportData& airportData机场数据
	**********************************************************/
	void SetBaseData(const AirportData& airportData);
	void SetBaseData(const std::vector<RunwayData>& vRunwayData);
	void SetBaseData(const std::vector<RoadData>& vRoadData);
	void SetBaseData(const std::vector<FixpointData>& vFixpointData);
	void SetBaseData(const std::vector<GateData>& vGateData);
	void SetBaseData(const std::vector<Tower>& vTowerData);
	void SetBaseData(const std::vector<AirportModel>& vAirportmodelData);
	void SetBaseData(const std::vector<AirportData>& vAirportData);
	void SetBaseData(const std::vector<Star>& vStarData);
	void SetBaseData(const std::vector<Beacon>& vBeaconData);
	void SetBaseData(const std::vector<Sector>& vGateData);
	void SetBaseData(const std::vector<RestrictArea>& vTowerData);
	void SetBaseData(const std::vector<Course>& vAirportmodelData);
	void SetBaseData(const std::vector<MsawArea>& vAirportData);
protected:
	/*********************************************************
	*函数名：GetSomething()
	*函数功能：从数据库获得数据
	*变量：
	**********************************************************/
	void GetAirportData();//从数据库查询机场数据
	void GetRunWayData();//从数据库查询跑道数据
	void GetRoadData();//道路数据
	void GetFixpointData();//固定点数据
	void GetGateData();//停机位信息
	void GetTowerData();//塔台信息
	void GetAirportModelData();//机场模型数据
	void GetStarData();//离场数据
	void GetBeaconData();//
	void GetSectorData();//扇区数据
	void GetRestricAreaData();//
	void GetCourseData();
	void GetMsawAreaData();//

protected:
	/*********************************************************
	*函数名：GetAirPortDataFromDB
	*函数功能：读取机场数据
	*变量：
	**********************************************************/
	void GetAirPortDataFromDB();
	/*********************************************************
	*函数名：GetAirPortDataFromDB
	*函数功能：读取空域数据
	*变量：
	**********************************************************/
	void GetAirSpaceDataFromDB();

	
private:
	AirPort_DBAccess *m_pDBAccessObj;/*数据库访问对象*/
	TotalBaseData    * m_pDataBase;/*存储从数据库读取的数据，以包的形式存储*/
	AckAirportDataPacket  *m_AckAirportDataPacket;
	AckAirspaceDataPacket *m_AckAirspaceDataPacket;//空域点存储数据结构
	std::multimap<int,boost::shared_ptr<RoadFixpointData> > m_mFixpointOnRoadData;//存放道路上临时点的映射表
	std::multimap<int,boost::shared_ptr<RoutePt> > m_mRoutePtData;//存放Route的映射表
	std::multimap<int,boost::shared_ptr<PointPosition> > m_mPointPosition;//存放点位置的映射表
};
#endif // GETDATAFROMDB_H
