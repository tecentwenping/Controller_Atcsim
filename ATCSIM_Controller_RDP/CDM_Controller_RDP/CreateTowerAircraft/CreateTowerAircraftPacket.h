#ifndef CreateTowerAircraftPacket_H
#define CreateTowerAircraftPacket_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: 
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/22
  ����  ����:  ���ļ���Ҫ��������ɻ���TowerAircraftPacket
  ����  ����:   
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
	 *��������Init
	 *�������ܣ���ʼ����������Ҫ�Ǳ����һЩָ�����
	 *������
	 **********************************************************/
	 void Init();
protected:
	/*********************************************************
	*��������CreateTowerObjPlan
	*�������ܣ�����Ŀ��ƻ�
	*������
	**********************************************************/
	void CreateTowerObjPlan(PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct,
							PublicDataStruct::TowerObjectPlanStruct& towerObjectPlanStruct);
	/*********************************************************
	*��������CreateFlightPlan
	*�������ܣ��������мƻ�
	*������towerFlightPlan
	**********************************************************/
	void CreateTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& flyPlanFromDB,
							   PublicDataStruct::TowerFlightPlanStruct& towerFlightPlan);
	/*********************************************************
	*��������CreateTowerAircraft
	*�������ܣ�������̨�ɻ���
	*������
	**********************************************************/
	void CreateTowerAircraft(PublicDataStruct::TowerFlightPlanStruct&,
							 PublicDataStruct::TowerObjectPlanStruct&);
	/**************************************************************************
	*��������ParaseAircraftPacketByTime
	*�������ܣ����ռƻ�ʱ���������
	*������
	**************************************************************************/
	void ParaseAircraftPacketByTime();
private:
	/*********************************************************
	*��������GetGateInformation
	*�������ܣ���ȡͣ��λ��Ϣ
	*������
	**********************************************************/
	void GetGateInformation();
	/*********************************************************
	*��������func_CheckPlanState
	*�������ܣ���麽��״̬
	*������
	**********************************************************/
	void CheckPlanState( PublicDataStruct::TowerFlightPlanStruct  &planAracrs );
	/*********************************************************
	*��������GateAllocate
	*�������ܣ�����ͣ��λ
	*������
	**********************************************************/
	void GateAllocate(PublicDataStruct::PLAN_TERMINATE enumTerminate_T,
					  PublicDataStruct::GateInformationStruct& gateInformation);
	/*********************************************************
	*��������ConvertFlyPlanFromDBToTowerFlightPlan
	*�������ܣ��������ݿ��ȡ���мƻ�����ת��Ϊ��̨ģ������мƻ�
	*������(1)PublicDataStruct::FlyPlanFromDBStruct& sourceStruct����Դ
	       (2)PublicDataStruct::TowerFlightPlanStruct& destStructĿ�ĵ�
	**********************************************************/
	void ConvertFlyPlanFromDBToTowerFlightPlan(PublicDataStruct::SFlyPlanFromDB& sourceStruct,
											   PublicDataStruct::TowerFlightPlanStruct& destStruct);
	/**************************************************************************
	*��������GetPathPoint
	*�������ܣ�
	*������sGateNameͣ��λ���ƣ�vecPathPoint�����㵽ͣ��λ��Ҫ�����ĵ������
	**************************************************************************/
	void GetPathPoint(const QString& sGateName,QStringList& PathPointList);
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void GateAllocate_New(PublicDataStruct::GateInformationStruct& gateInformation);
/////////////////////////////////////////////////////////////////////////////////////////////////////
	void ConvertFlyPlanFromDBToTowerFlightPlan_Test(PublicDataStruct::SFlyPlanFromDB& source,
													PublicDataStruct::TowerFlightPlanStruct& dest);
	
signals:
	/*********************************************************
	*��������sig_StartPathPlaning
	*�������ܣ��źź�������ʼ�滮·��
	*������iFlightID���ڱ�ʶΨһ��һ�����мƻ�
	**********************************************************/
	void sig_StartPathPlaning(int iFlightID);
private slots:
	/*********************************************************
	*��������slot_StoreTowerAircraftPacket
	*�������ܣ��ۺ������洢CDM���мƻ���
	*������
	**********************************************************/
	void slot_RecvPlanAircraftPacket();
	void slot_ReTranslateTowerAircraftPacket(int iFlightID);
private:
	QUdpSocketPtr									m_pRecvPlanAircraftPacketSocket;//���շ��мƻ���UDP�׽��ֶ���
	QThread											m_RecvPlanAircraftPacketThread;//���շ��мƻ����߳���
	PublicDataStruct::TowerFlightPlanStruct			m_PlanAircraftPacket; //���շ��мƻ��ı��Ľṹ
	PublicDataStruct::TowerAircraftPacketStruct		m_TowerAircraftStruct;
	PublicDataStruct::ENUM_PLAN_TYPE				m_PlanType;//���мƻ�����(ö������)
	PublicDataStruct::PLAN_TERMINATE				m_enumTerminate_T;//��վ¥
	PublicDataStruct::GateInformationStruct			m_GateInformationStruct;//���ͣ��λ��Ϣ�����ݽṹ
	static  double									m_initialLongtitue_T2;//�����ɻ�T2��վ¥ͣ��λ�������ֵ�re1�ľ���
	static  double									m_initilaLatitue_T2;//�����ɻ�T2��վ¥ͣ��λ�������ֵ�re1��γ��
	static  double									m_initialLongtitue_T1;//�����ɻ�T1��վ¥ͣ��λ�������ֵ�ra1�ľ���
	static  double									m_initilaLatitue_T1;//�����ɻ�T1��վ¥ͣ��λ�������ֵ�ra1��γ��
	QStringList										m_GateInformationStringList;//���ͣ��λ��Ϣ��QStringList
	int												m_iCount;//��¼����ͣ��λ��ռ�õı��
	int												m_iFlyPlanID;//���мƻ�ID�ţ���0��ʼ������
	int												m_iOldSize;//��ŷ��мƻ��������Ĵ�С��ֻ�д�С�ı��ʱ�򣬲Ż�����µķ��мƻ�
};

#endif // CreateTowerAircraftPacket_H
