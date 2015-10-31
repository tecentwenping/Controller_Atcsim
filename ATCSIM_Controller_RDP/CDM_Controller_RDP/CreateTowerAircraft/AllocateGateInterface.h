#ifndef ALLOCATEGATEPINTERFACE_H
#define ALLOCATEGATEPINTERFACE_H
///*********************************************************************///
//@类名：AllocateGatePInterface
//@Author:陈文平                                                          
//@Time:2014-10-09                                                        
//@Descirption:停机位分配程序的接口类                                                           
////*********************************************************************//

#include <QObject>
#include <QThread>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
///*********************************************************************///
//@类名：CDM_InitGateInformation
//@Author:陈文平                                                          
//@Time:2014-10-09                                                        
//@Descirption:停机位分配类，主要完成的功能有：(1)从数据库读取飞机信息；
//(2)读取空闲机位信息，包括停机位名，经纬度等
////*********************************************************************//
class CDM_InitGateInformation;
///*********************************************************************///
//@类名：CDM_SendFlyPlan
//@Author:陈文平                                                          
//@Time:2014-10-09                                                        
//@Descirption:发送飞行计划类，主要功能为通过CDM_InitGateInformation发送过来
//的飞行计划信息和停机位信息，创建飞行计划和目标计划，并将其发送给二维图形
//显示界面，并返回一个PlanID号
////*********************************************************************//
class CDM_SendFlyPlan;
///*********************************************************************///
//@类名：CDM_GetFlyPlanByTime
//@Author:陈文平                                                          
//@Time:2014-10-21                                                        
//@Descirption:  定时发送飞行计划到类CDM_SendFlyPlan                                                         
////*********************************************************************//
class CDM_GetFlyPlanByTime;

typedef boost::shared_ptr<CDM_InitGateInformation> CDM_InitGateInformationPtr;
typedef boost::shared_ptr<CDM_SendFlyPlan> CDM_SendFlyPlanPtr;
class AllocateGatePInterface : public QObject
{
	Q_OBJECT
public:
	AllocateGatePInterface();
	~AllocateGatePInterface();
private:

	CDM_GetFlyPlanByTime  *m_GetPlanByTimeObj;
	CDM_InitGateInformationPtr m_pAllocateGatePosObj;
	CDM_SendFlyPlanPtr	   m_pSendFlyPlanObj;
	QThread sendFlyPlanThread;
	QThread getFlyPlanByTimeThread;
private:
	void initial();
signals:
	void signal_StartExec();
};

#endif // ALLOCATEGATEPINTERFACE_H
