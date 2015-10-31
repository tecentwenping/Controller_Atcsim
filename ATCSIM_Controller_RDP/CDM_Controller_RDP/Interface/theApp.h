#ifndef Controller_RDP_H
#define Controller_RDP_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: Controller_RDP
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/29
  ����  ����:  ���ļ���������Controller_RDP������������ǽӿ���
               ��������RDP������
  ����  ����:   
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
	*��������InitAppInstance
	*�������ܣ���ʼ��Ӧ�ó��򣬸ú���������RDP����ں���
	*������
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
	CreateTowerAircraftPacketPtr m_pCreateTowerAircraftPacket;		//�����ɻ������ö�����ATCCR��ϵ�������䷢�͹����ķ��мƻ�
	PathPlaningPtr				 m_pPathPlaning;					//·���滮���󣬸���CreateTowerAircraftPacket�ദ����˵ķɻ�����Ȼ��Ը÷ɻ�������·���滮
	DataManagerPtr				 m_pDataManager;					//���ݹ���
	NetManagerPtr				 m_pNetManager;						//�������
	GetFlyPlanFromDBPtr			 m_pGetFlyPlanFromDB;				//���ݿ���������ݿ��ж�ȡ���мƻ�
private:
	QThread						 m_CreateTowerAircraftPacketThread; //���շ��мƻ���������мƻ����߳�
	QThread						 m_PathPlaningThread;				//·���滮
	QThread						 m_NetWorkThread;					//����������߳�
	QThread                      m_GetFlyPlanFromDBThread;			//���ݲ����߳�
	QThread						 m_CDataManagerThread;				//���ݹ������߳�
};
//�������ݹ���������
typedef singleton_default<Controller_RDP> theApp;
#endif // Controller_RDP_H
