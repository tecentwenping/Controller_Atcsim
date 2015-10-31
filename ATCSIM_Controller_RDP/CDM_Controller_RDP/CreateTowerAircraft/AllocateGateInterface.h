#ifndef ALLOCATEGATEPINTERFACE_H
#define ALLOCATEGATEPINTERFACE_H
///*********************************************************************///
//@������AllocateGatePInterface
//@Author:����ƽ                                                          
//@Time:2014-10-09                                                        
//@Descirption:ͣ��λ�������Ľӿ���                                                           
////*********************************************************************//

#include <QObject>
#include <QThread>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
///*********************************************************************///
//@������CDM_InitGateInformation
//@Author:����ƽ                                                          
//@Time:2014-10-09                                                        
//@Descirption:ͣ��λ�����࣬��Ҫ��ɵĹ����У�(1)�����ݿ��ȡ�ɻ���Ϣ��
//(2)��ȡ���л�λ��Ϣ������ͣ��λ������γ�ȵ�
////*********************************************************************//
class CDM_InitGateInformation;
///*********************************************************************///
//@������CDM_SendFlyPlan
//@Author:����ƽ                                                          
//@Time:2014-10-09                                                        
//@Descirption:���ͷ��мƻ��࣬��Ҫ����Ϊͨ��CDM_InitGateInformation���͹���
//�ķ��мƻ���Ϣ��ͣ��λ��Ϣ���������мƻ���Ŀ��ƻ��������䷢�͸���άͼ��
//��ʾ���棬������һ��PlanID��
////*********************************************************************//
class CDM_SendFlyPlan;
///*********************************************************************///
//@������CDM_GetFlyPlanByTime
//@Author:����ƽ                                                          
//@Time:2014-10-21                                                        
//@Descirption:  ��ʱ���ͷ��мƻ�����CDM_SendFlyPlan                                                         
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
