#ifndef Controller_RDP_H
#define Controller_RDP_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: Controller_RDP
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/29
  【描  述】:  此文件定义了类Controller_RDP，该类的作用是接口类
               操作整个RDP的流程
  【其  它】:   
**************************************************************************/
#include<boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QObject>
#include <QThread>
#include <boost/pool/detail/singleton.hpp>
using boost::details::pool::singleton_default;
class CreateTowerAircraftPacket;
class CPathPlanning;
class CDataManager;
class CNetManager;
class CGetFlyPlanFromDB;
typedef boost::shared_ptr<CreateTowerAircraftPacket>	CreateTowerAircraftPacketPtr;
typedef boost::shared_ptr<CPathPlanning>				PathPlaningPtr;
typedef boost::shared_ptr<CDataManager>					DataManagerPtr;
typedef boost::shared_ptr<CNetManager>					NetManagerPtr;
typedef boost::shared_ptr<CGetFlyPlanFromDB>			GetFlyPlanFromDBPtr;
class Controller_RDP : public QObject
{
	Q_OBJECT

public:
	Controller_RDP();
	~Controller_RDP();
public:
	/**************************************************************************
	*函数名：InitAppInstance
	*函数功能：初始化应用程序，该函数是整个RDP的入口函数
	*变量：
	**************************************************************************/
	bool						 InitAppInstance();
	void						 InitDataManagerPtr();
	void						 InitNetManagerPtr();
	void						 InitCreateAircraftPacketPtr();
	void						 InitPathPlanningPtr();
	void						 InitGetPlanFromDBPtr();
	CDataManager*				 GetDataManagerPtr();
	CNetManager*				 GetNetManagerPtr();
	CreateTowerAircraftPacket*	 GetCreateTowerAircraftPacketPtr();
	CPathPlanning*				 GetPathPlaningPtr();
	CGetFlyPlanFromDB*			 GetPlanFromDBPtr();
private:
	CreateTowerAircraftPacketPtr m_pCreateTowerAircraftPacket;		//创建飞机包，该对象与ATCCR联系，接收其发送过来的飞行计划
	PathPlaningPtr				 m_pPathPlaning;					//路径规划对象，根据CreateTowerAircraftPacket类处理好了的飞机包，然后对该飞机包进行路径规划
	DataManagerPtr				 m_pDataManager;					//数据管理
	NetManagerPtr				 m_pNetManager;						//网络管理
	GetFlyPlanFromDBPtr			 m_pGetFlyPlanFromDB;				//数据库管理，从数据库中读取飞行计划
private:
	QThread						 m_CreateTowerAircraftPacketThread; //接收飞行计划并处理飞行计划的线程
	QThread						 m_PathPlaningThread;				//路径规划
	QThread						 m_NetWorkThread;					//处理网络的线程
	QThread                      m_GetFlyPlanFromDBThread;			//数据操作线程
	QThread						 m_CDataManagerThread;				//数据管理器线程
};
//创建数据管理器单件
typedef singleton_default<Controller_RDP> theApp;
#endif // Controller_RDP_H
