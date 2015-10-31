#ifndef CPathPlanning_H
#define CPathPlanning_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: 
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/23
  ����  ����:  ���ļ���������CDM_PathPlaning�࣬�������Ҫ�����ǹ滮�����ɻ���
               ��㵽�յ��·���������һ��·�������پ�������ģ�齫��Щ·������
			   ���͵���ʾ���棬��ʾ���������Ӧ����ʾ
  ����  ����:   
**************************************************************************/

#include <QObject>
#include <vector>
#include <QTimer>
#include "PublicStruct.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/shared_mutex.hpp>
class AircraftTrace;
class ControllerPresenter;
class NetProcess;
class ControllerAircraftTrace;
//////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<AircraftTrace> AircraftTracePtr;
typedef boost::shared_ptr<ControllerPresenter> ControllerPresenterPtr;
typedef boost::shared_ptr<NetProcess> NetProcessPtr;
typedef boost::shared_ptr<ControllerAircraftTrace> ControllerAircraftTracePtr;
class CPathPlanning : public QObject
{
	Q_OBJECT
public:
	typedef PublicDataStruct::SDPSTrack track_type;
public:
	CPathPlanning();
	~CPathPlanning();
     void PathPlaning();
protected:
	/*********************************************************
	*��������GetAircraftBaseInformation
	*�������ܣ���ȡ�ƻ��Ļ�����Ϣ
	*������towAircraftPacket
	**********************************************************/
	void GetPlanBaseInformation(const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket);
private:
	/*********************************************************
	*��������GetSourceAndDest
	*�������ܣ��õ�·���滮�������յ㣬������Դ��TowerAircraftPacket
	*������towAircraftPacket�ɻ���
	**********************************************************/
	void GetSourceAndDest(const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket);
	/**************************************************************************
	*��������SettAircraftTraceDefaulValue
	*�������ܣ���Ϊ���趨һЩ����Ĭ��ֵ���ú�����Ҫ�ǲ��Խ׶�ʹ��
	*������
	**************************************************************************/
	void SettAircraftTraceDefaulValue(AircraftTrace& vAircraftTrace);
private slots:
	/*********************************************************
	*��������PathPlaningStart
	*�������ܣ���ʼ·���滮
	*������
	**********************************************************/
	void slot_StartPathPlaning(int iFlightID);
signals:
	void sig_ReTranslateTowerAircraftPacket(int iFlightID);
private:
	double					m_dInitLongtitude; //�ɻ����ֵĳ�ʼ����
	double					m_dInitLatitude;   //�ɻ����ֵĳ�ʼγ��
	std::string				m_DepGate;			//�볡ͣ��λ
	std::string				m_ArrGate;			//����ͣ��λ
	double					m_dSpeed;//�ٶ�
	double					m_dFinishTime;//����ָ��λ�õĹ̶�ʱ��
	double					m_dInternalTime;//���º�����ʱ����
	track_type				m_Track;
	ControllerPresenterPtr	m_pControllerPressenter;
	AircraftTracePtr		m_pAircraftTrace;
	NetProcessPtr			m_pSendAircraftTrace;
	PublicDataStruct::AircraftTrace m_aircraftTrace;
	boost::shared_mutex     m_traceCheckLocker;  //���溽�����ºͺ�������޸ĵ���
	//////////////////////////////////////////////////////////////////////////
	int iCount;//���ڱ�ʾ������һ��������
	QTimer					m_Timer;
	bool					m_isFinished;	
};

#endif // CPathPlanning_H
