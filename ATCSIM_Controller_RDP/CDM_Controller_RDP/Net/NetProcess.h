#ifndef NETPROCESS_H
#define NETPROCESS_H

/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: NetProcess
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/01
  ����  ����:  ���ļ���������NetProcess����������ô��������
  ����  ����:   
**************************************************************************/
#include <QUdpSocket>
#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class AircraftTrace;
class NetProcess:public QObject
{
	Q_OBJECT
public:

public:
	NetProcess();
	~NetProcess();
	QUdpSocket& GetSendTraceUdpSocket(){return *m_pUdpSendTraceSocket;}
	/*********************************************************
	*��������SendSingleTrace
	*�������ܣ�����ʾ���淢�ͺ���
	*������
	**********************************************************/
	void SendAircraftTrace(const AircraftTrace& vAircraftTrace);

private:
	QUdpSocket *m_pUdpSendTraceSocket;//���ͺ�������ʾ�����Socket
};

#endif // NETPROCESS_H
