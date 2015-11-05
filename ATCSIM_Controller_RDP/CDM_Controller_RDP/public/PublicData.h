#ifndef PUBLICDATA_H
#define PUBLICDATA_H
///*********************************************************************///
//@类名：CPublicData
//@Author:陈文平                                                          
//@Time:2014-09-30                                                        
//@Descirption:存放全局变量                                                           
////*********************************************************************//

#include <QStringList>
#include <QMutex>
#include <vector>
#include <map>
#include <QString>
#include <QStringList>
#include <utility>
#include "PublicStruct.h"
#include "CreateTowerAircraft/CreateTowerAircraftPacket.h"
#include "wworldpoint.h"
typedef std::map<int,std::vector<WPointF> >							MapAircraftTrace;
typedef std::vector<QStringList>									VecGateInformation;
typedef std::multimap<QString,QString>								MapGateName;
typedef std::multimap<int,PublicDataStruct::TaxiLine>				MapTaxiLine;
typedef std::multimap<std::string,PublicDataStruct::FixPoint>		MapFixPoint;
typedef std::map<int,PublicDataStruct::TowerAircraftPacketStruct>	MapTowerAircraftPacket;
typedef std::vector<PublicDataStruct::SFlyPlanFromDB>				VecFlyPlanFromDB;
typedef std::map<int,QStringList >									MapPathPoint;
typedef std::multimap<QString,QStringList>								MapPath;
class CPublicData
{
private:
	 static double						m_dCenterLongtitude;
	 static double						m_dCenterLatitude;
	 static MapGateName					m_mapGateName;              //存放停机位名称的映射表
	 static MapTaxiLine					m_mapTaxiLine;			  //存放滑行道信息的映射表
	 static MapFixPoint					m_mapFixPoint;			  //存放固定点信息的映射表
	 static VecGateInformation			m_VecGateInformation_T1;//t1 航站楼的停机位信息
	 static VecGateInformation			m_VecGateInformation_T2;//t2 航站楼的停机位信息			
	 static MapTowerAircraftPacket		m_mapTowerAircraftPacket; //存放飞机包的映射表
	 static VecFlyPlanFromDB			m_vecFlyPlanFromDB;//从数据库读取的飞行计划
	 static VecGateInformation			m_VecInPathInformation;//所有进入T1航站楼停机位的离线路径信息
	 static VecGateInformation			m_VecOutPathInformation;//所有退出航站楼飞机的离线路径信息
	 static MapPathPoint				m_MapPathPoint;//存放某个航迹的路径点信息
	 static MapPath						m_MapInPath;
	 static MapPath						m_MapOutPath;
	 static MapAircraftTrace			m_mapAircraftTrace;//存放航迹的映射表
	 static std::vector<QString>		m_vecCurrentFlyPlan;

	 ///////////////////////////////////////////////////////////////////////////////
	 static VecGateInformation			m_vecGateInformation;//所有停机位信息
public:
	CPublicData();
	CPublicData(double dCenterLongtitude,double dCenterLatitude);
	~CPublicData();
	void					SetCenterCoordinate(double& dCenterLongtitude,double& dCenterLatitude);
	/*void					SetGateInformation_T1(const VecGateInformation& VecGateInformation);
	void					SetGateInformation_T2(const VecGateInformation& VecGateInformation);*/
	void					SetGateName(const MapGateName& mapGateName);
	void					SetTaxiLine(const MapTaxiLine& mapTaxiLine);
	void					SetFixPoint(const MapFixPoint& mapFixPoint);
	void					SetTowerAircraftPacket(const MapTowerAircraftPacket& mapTowerAircraftPacket);
	void					SetInPathInformation(const MapPath& mapPathInformation);
	void					SetOutPathInformation(const MapPath& mapPathInformation);
	void					SetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					SetAircraftTrace(const MapAircraftTrace& mapAircraftTraceNewVersion);
	void				    SetCurrentFlyPlan(const QString& singleFlyPlan);
/////////////////////////////////////////////////////////////////////////////////////////
	void					GetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					GetPathInformation(MapPath& mapPath,int flag);
	void					GetMapGateName(MapGateName&);
	void					GetMapTaxiLine(MapTaxiLine&);
	void					GetMapFixPoint(MapFixPoint&);
	void					GetMapTowerAircraftPacket(MapTowerAircraftPacket&);
	MapTowerAircraftPacket& GetMapTowerAircraftPacket();
	MapAircraftTrace&		GetMapAircraftTrace()const;
	void					GetMapAircraftTrace(MapAircraftTrace&);
	void					GetVecFlyPlanFromDB(VecFlyPlanFromDB& vecFlyPlanFromDB);
	void					SetVecFlyPlanFromDB(VecFlyPlanFromDB& vecFlyPlanFromDB);
	/*void					GetGateInformation_T1(VecGateInformation& vecGateInforamtion);
	void					GetGateInformation_T2(VecGateInformation& vecGateInformation);
	VecGateInformation&     GetGateInformation_T1();
	VecGateInformation&		GetGateInformaiton_T2();*/
	void					GetCurrentFlyPlan(std::vector<QString>& vecCurFLyPlan);

	//////////////////////////////////////////////////////////////////////////////////
	void				GetPathInformation_New(MapPath&,int flag);
	void				SetGateInformation_New(const VecGateInformation& vecGateInformation);
	void				GetGateInformation_New(VecGateInformation& vecGateInforamtion);
	VecGateInformation&	GetGateInformation_New();


};
#endif // PUBLICDATA_H
