#ifndef SOCKETTEST_H
#define SOCKETTEST_H


#include <QObject>
#include <QUdpSocket>
#include <boost/thread/shared_mutex.hpp>
class AircraftTrace;
class CRecvAircraftTrace : public QObject
{
	Q_OBJECT

public:
	CRecvAircraftTrace();
	~CRecvAircraftTrace();
	private slots:
	     void RecvAircraftTraceSlot();

private:
	QUdpSocket* m_pUdpRecvAircraftTraceSocket;
	boost::shared_mutex   m_traceLocker;  //���溽�����ºͺ�������޸ĵ���

	//2015.10.09����
	std::map<int,AircraftTrace*> mapAircraftTracePtr;
signals:
	void sig_UpdateAircraftTrace(int iTraceID);
private:
	/**************************************************************************
	*��������SetAircraftTrace
	*�������ܣ����ú���
	*��������һ����Ŀ�ĺ������ڶ�����Դ����
	**************************************************************************/
	void ConvertAircraftTrace(AircraftTrace* vDesAircraftTrace,const AircraftTrace& vSourAircraftTrace);
};

#endif // SOCKETTEST_H
