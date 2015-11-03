#ifndef NetDataDispenser_H
#define NetDataDispenser_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: NetDataDispenser
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/15
  ����  ����:  ���ļ���������NetDataDispenser������ַ��������ฺ��ַ����е������
               �����ѭ��ɨ�����RDP����ʾ�նˣ����ηַ���ǰ���µĺ�������Ϣ
			   1.��ȡ�ڳ�������
			   2����ͻ���
			   3����������
  ����  ����:   
**************************************************************************/
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QList>
#include <hash_map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <deque>
#include "wworldpoint.h"
#include "public/PublicStruct.h"
#include "Tools.h"
class AircraftTrace;
typedef boost::shared_ptr<AircraftTrace>			AircraftTracePtr;
typedef stdext::hash_map<int,AircraftTrace*>		hmFplTraces;
//typedef stdext::hash_map<int,std::vector<WPointF> > hmFplTracePoint;
typedef stdext::hash_map<int,std::deque<WPointF> > hmFplTracePoint;
class NetDataDispenser:public QObject
{
	Q_OBJECT

public:
	NetDataDispenser();
	~NetDataDispenser();
	 bool InitData();
	 void UpdateAircraftTrace(AircraftTrace* pTrace);
public:
	 void DispenserTraceToClient();
private:
	/**************************************************************************
	*��������AircraftTraceToDispenser
	*�������ܣ�������Щ�ڵ�ǰʱ��Ӧ�÷��ͺ����ĺ��༯��
	*����������Ĳ�������Ψһʶ��һ������
	**************************************************************************/
	void AircraftTraceToDispenser();
	/**************************************************************************
	*��������_SetSafeDistance
	*�������ܣ�����һ���������������澯��ͻ�����ĺͣ���������Ҫ����β����ȷ��
	*������
	**************************************************************************/
	void _SetSafeDistance(PublicDataStruct::Aircraft& aircraft);
    /**************************************************************************
    *��������_CollectionDetect
    *�������ܣ���ͻ���
    *������
    **************************************************************************/
	void _CollectionDetect();
	/**************************************************************************
	*��������CompuAngle
	*�������ܣ�����TraceID������������ĽǶ�
	*������
	**************************************************************************/
	int CompuAngle(int iTraceID);
	/**************************************************************************
	*��������_CollisionDectect_Aux
	*�������ܣ��������������֮��ľ���
	*����������ֵ�Ǻ���ID
	**************************************************************************/
	void  _CollisionDectect_Aux(int iTraceID1,int iTraceID2);
	
	/**************************************************************************
	*��������_DisPenserTraceToClient
	*�������ܣ�ִ�зַ�����ľ��庯��
	*������
	**************************************************************************/
	void _DisPenserTraceToClient();

private:
	bool							m_bInitDataSucess;
	std::map<AircraftTrace*,int>	m_mpTracePointCount;//����������������ڱ�ʶ��ǰĳһ������Ӧ�����ڵ�����λ��
	hmFplTraces						m_hmTrace;
	hmFplTracePoint					m_hmTracePoint;
	QTimer							*m_pTimer;
	//========================================================================
	std::vector<int>				m_aircrftTraceToDispenserVec;
	std::vector<int>				m_aircraftTraceVec;
	std::vector<int>				m_aircraftStopVec;//��Ҫͣ�ȵĺ�������ID
	
};

#endif // NetDataDispenser_H
