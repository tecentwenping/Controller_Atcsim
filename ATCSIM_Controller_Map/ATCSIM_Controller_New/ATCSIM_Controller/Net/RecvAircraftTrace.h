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
	boost::shared_mutex   m_traceLocker;  //保存航迹更新和航迹检测修改的锁

	//2015.10.09新增
	std::map<int,AircraftTrace*> mapAircraftTracePtr;
signals:
	void sig_UpdateAircraftTrace(int iTraceID);
private:
	/**************************************************************************
	*函数名：SetAircraftTrace
	*函数功能：设置航迹
	*变量：第一个是目的航迹，第二个是源航迹
	**************************************************************************/
	void ConvertAircraftTrace(AircraftTrace* vDesAircraftTrace,const AircraftTrace& vSourAircraftTrace);
};

#endif // SOCKETTEST_H
