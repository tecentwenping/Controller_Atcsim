#ifndef CDataManager_H
#define CDataManager_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CDataManager
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/29
  【描  述】:  此文件定义了类CDataManager，管理所有的数据
  【其  它】:   
**************************************************************************/
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pool/detail/singleton.hpp>
#include <map>
#include <QString>
#include <QStringList>
#include <vector>
#include <hash_map>
#include "public/PublicStruct.h"
#include "Manager/TaxiLineInformation.h"
#include "wworldpoint.h"
#include <deque>
using boost::details::pool::singleton_default;
class CFile;
class CInitPointInformation;
class CPublicData;
class TowerAircraftPacketStruct;
class TotalAircraftTrace;
class AircraftTrace;
class AircraftTraceNewVersion;
///////////////////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<CFile>									FilePtr;//文件操作类
typedef boost::shared_ptr<CInitPointInformation>					InitPointInformationPtr;
typedef boost::shared_ptr<CPublicData>	        					CPublicDataPtr;
typedef boost::shared_ptr<TotalAircraftTrace>						TotalAircraftTracePtr;
typedef boost::shared_ptr<CTaxiLineInformation>						TaxiLineInformationPtr;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef std::map<int,std::vector<WPointF> >							MapAircraftTrace;
typedef stdext::hash_map<int,AircraftTrace*>						hmFplTraces;				
typedef std::vector<QStringList>									VecGateInformation;
typedef std::multimap<QString,QString>								MapGateName;
typedef std::multimap<int,PublicDataStruct::TaxiLine>				MapTaxiLine;
typedef std::multimap<std::string,PublicDataStruct::FixPoint>		MapFixPoint;
typedef std::map<int,PublicDataStruct::TowerAircraftPacketStruct>	MapTowerAircraftPacket;
typedef std::multimap<QString,QStringList>								MapPath;
////////////////////////////////////////////////////////////////////////////////////////////
typedef stdext::hash_map<int,std::deque<WPointF> >					hmFplTracePoint;
class CDataManager
{

public:
	CDataManager();
	~CDataManager();
	void	  Init();
public:
	void					GetCenterCoordinate(double& dCenterLongtitude,double& dLatitude);//设置机场中心坐标（默认为双流机场）
	//void					GetGateInformation_T1(VecGateInformation& vecGateInformation);//获取T1航站楼停机位信息
	//void					GetGateInformation_T2(VecGateInformation& vecGateInformation);//获取T2航站楼停机位信息
	//VecGateInformation&		GetGateInformation_T1();
	//VecGateInformation&     GetGateInformation_T2();
	void					GetMapGateName(MapGateName& mapGateName);//获取停机位名称
	void					GetMapTaxiLine(MapTaxiLine& mapTaxiLine);//获取滑行道
	void					GetMapFixPoint(MapFixPoint& mapFixPoint);//获取固定点
	void					GetMapTowerAircraftPacket(MapTowerAircraftPacket& mapTowerAircraft);//获取飞机包
	MapTowerAircraftPacket& GetMapTowerAircraftPacket();
	void					GetMapAirTrace(MapAircraftTrace& mapAircraftTrace);
	//void					GetTracePoint(int iTraceno,std::vector<WPointF>& vecTracePoint);
	void					GetAircraftTrace(hmFplTraces& hmFplTrace);
	TotalAircraftTrace*     GetTotalAircraftTracePtr();
	void					GetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	void					GetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					GetPathInformation(MapPath& mapPath,int flag);
	void					GetCurrentFlyPlan(std::vector<QString>& vecCurFlyPlan);
	//////////////////////////////////////////////////////////////////////////////////
	void					SetMapAirTrace(const MapAircraftTrace& mapAircraftTrace);
	//void					SetTracePoint(int iTraceno,const std::vector<WPointF>& vecTracePoint);
	void					SetPathInformation(const MapPath& mapPath,int flag);
	void					SetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	//void					SetGateInformation(const VecGateInformation& vecGateInformation,int flag);
	void					SetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					SetAircraftTrace(int iTraceno,AircraftTrace* aicraftTrace);
	void					SetMapFixPoint(const MapFixPoint& mpFixPoint);
	void					SetMapTaxLine(const MapTaxiLine& mpTaxLine);
	void					SetMapGateName(const MapGateName& mpGateName);
	void					SetMapTowerAircraftPacket(const MapTowerAircraftPacket& mpTowerAircraft);
	void					SetCurrentFlyPlan(const QString& singleFlyPlan);
	//===================================================================================
	void					SetAircraftTracePoint1(int traceID,const std::deque<WPointF>& dTrace);
	void					GetAircraftTracePoint1(int traceID, std::deque<WPointF>& dTrace);
    void					GetGateInformation_New(VecGateInformation& vecGateInformation);
	void					SetGateInformation_New(const VecGateInformation& vecGateInformation);
	VecGateInformation&     GetGateInformation_New();
private:
	FilePtr					m_pInitGateInformation;//停机位信息
	FilePtr					m_pInitPathInformation;//路径信息
	InitPointInformationPtr m_pInitPointInformaton;//点的信息
	CPublicDataPtr			m_pPublicData;//公共数据
	TotalAircraftTracePtr	m_pTotalTrace;
	TotalAircraftTrace      *m_pTotalTracePtr;
	TaxiLineInformationPtr  m_pTaxLineInformation;
public:
	TotalAircraftTracePtr	GetTotalAircraftTracePtr_New();
};
//创建数据管理器单件
typedef singleton_default<CDataManager> theData;
#endif // CDataManager_H
