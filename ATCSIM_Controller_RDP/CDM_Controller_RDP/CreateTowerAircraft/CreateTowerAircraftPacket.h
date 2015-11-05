#ifndef CreateTowerAircraftPacket_H
#define CreateTowerAircraftPacket_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: 
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/22
  【描  述】:  此文件主要用于组件飞机包TowerAircraftPacket
  【其  它】:   
**************************************************************************/

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QStringList>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "PublicStruct.h"
#include "wworldpoint.h"
typedef boost::shared_ptr<QUdpSocket> QUdpSocketPtr;
class CreateTowerAircraftPacket :public QObject
{
	Q_OBJECT
public:
	CreateTowerAircraftPacket();
	~CreateTowerAircraftPacket();
	 /*********************************************************
	 *函数名：Init
	 *函数功能：初始化变量，主要是本类的一些指针变量
	 *变量：
	 **********************************************************/
	 void Init();
protected:
	/*********************************************************
	*函数名：CreateTowerObjPlan
	*函数功能：创建目标计划
	*变量：
	**********************************************************/
	void CreateTowerObjPlan(PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct,
							PublicDataStruct::TowerObjectPlanStruct& towerObjectPlanStruct);
	/*********************************************************
	*函数名：CreateFlightPlan
	*函数功能：创建飞行计划
	*变量：towerFlightPlan
	**********************************************************/
	void CreateTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& flyPlanFromDB,
							   PublicDataStruct::TowerFlightPlanStruct& towerFlightPlan);
	/*********************************************************
	*函数名：CreateTowerAircraft
	*函数功能：创建塔台飞机包
	*变量：
	**********************************************************/
	void CreateTowerAircraft(PublicDataStruct::TowerFlightPlanStruct&,
							 PublicDataStruct::TowerObjectPlanStruct&);
	/**************************************************************************
	*函数名：ParaseAircraftPacketByTime
	*函数功能：按照计划时间解析航迹
	*变量：
	**************************************************************************/
	void ParaseAircraftPacketByTime();
private:
	/*********************************************************
	*函数名：GetGateInformation
	*函数功能：获取停机位信息
	*变量：
	**********************************************************/
	void GetGateInformation();
	/*********************************************************
	*函数名：func_CheckPlanState
	*函数功能：检查航班状态
	*变量：
	**********************************************************/
	void CheckPlanState( PublicDataStruct::TowerFlightPlanStruct  &planAracrs );
	/*********************************************************
	*函数名：GateAllocate
	*函数功能：分配停机位
	*变量：
	**********************************************************/
	void GateAllocate(PublicDataStruct::PLAN_TERMINATE enumTerminate_T,
					  PublicDataStruct::GateInformationStruct& gateInformation);
	/*********************************************************
	*函数名：ConvertFlyPlanFromDBToTowerFlightPlan
	*函数功能：将从数据库读取飞行计划数据转换为塔台模拟机飞行计划
	*变量：(1)PublicDataStruct::FlyPlanFromDBStruct& sourceStruct数据源
	       (2)PublicDataStruct::TowerFlightPlanStruct& destStruct目的地
	**********************************************************/
	void ConvertFlyPlanFromDBToTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& sourceStruct,
											   PublicDataStruct::TowerFlightPlanStruct& destStruct);
	/**************************************************************************
	*函数名：GetPathPoint
	*函数功能：
	*变量：sGateName停机位名称，vecPathPoint存放起点到停机位所要经过的点的容器
	**************************************************************************/
	void GetPathPoint(const QString& sGateName,QStringList& PathPointList);
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void GateAllocate_New(PublicDataStruct::GateInformationStruct& gateInformation);
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void ConvertFlyPlanFromDBToTowerFlightPlan_Test(PublicDataStruct::SFlyPlanFromDB& source,
													PublicDataStruct::TowerFlightPlanStruct& dest);
	
signals:
	/*********************************************************
	*函数名：sig_StartPathPlaning
	*函数功能：信号函数，开始规划路径
	*变量：iFlightID用于标识唯一的一条飞行计划
	**********************************************************/
	void sig_StartPathPlaning(int iFlightID);
private slots:
	/*********************************************************
	*函数名：slot_StoreTowerAircraftPacket
	*函数功能：槽函数，存储CDM飞行计划包
	*变量：
	**********************************************************/
	void slot_RecvPlanAircraftPacket();
	void slot_ReTranslateTowerAircraftPacket(int iFlightID);
private:
	QUdpSocketPtr									m_pRecvPlanAircraftPacketSocket;//接收飞行计划的UDP套接字对象
	QThread											m_RecvPlanAircraftPacketThread;//接收飞行计划的线程类
	PublicDataStruct::TowerFlightPlanStruct			m_PlanAircraftPacket; //接收飞行计划的报文结构
	PublicDataStruct::TowerAircraftPacketStruct		m_TowerAircraftStruct;
	PublicDataStruct::ENUM_PLAN_TYPE				m_PlanType;//飞行计划类型(枚举类型)
	PublicDataStruct::PLAN_TERMINATE				m_enumTerminate_T;//航站楼
	PublicDataStruct::GateInformationStruct			m_GateInformationStruct;//存放停机位信息的数据结构
	static  double									m_initialLongtitue_T2;//进场飞机T2航站楼停机位进场出现点re1的经度
	static  double									m_initilaLatitue_T2;//进场飞机T2航站楼停机位进场出现点re1的纬度
	static  double									m_initialLongtitue_T1;//进场飞机T1航站楼停机位进场出现点ra1的经度
	static  double									m_initilaLatitue_T1;//进场飞机T1航站楼停机位进场出现点ra1的纬度
	QStringList										m_GateInformationStringList;//存放停机位信息的QStringList
	int												m_iCount;//记录的是停机位被占用的编号
	int												m_iFlyPlanID;//飞行计划ID号，从0开始递增。
	int												m_iOldSize;//存放飞行计划的容器的大小，只有大小改变的时候，才会解析新的飞行计划
};

#endif // CreateTowerAircraftPacket_H
