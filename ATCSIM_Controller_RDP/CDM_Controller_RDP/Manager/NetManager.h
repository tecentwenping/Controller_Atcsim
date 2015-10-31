#ifndef CNetManager_H
#define CNetManager_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class NetDataDispenser;
class AircraftTrace;
class NetProcess;
typedef boost::shared_ptr<NetProcess>    NetProcessPtr;
typedef boost::shared_ptr<AircraftTrace> AircraftTracePtr;
typedef boost::shared_ptr<NetDataDispenser>  NetDataDispenserPtr;
class CNetManager : public QObject
{
	Q_OBJECT

public:
	CNetManager();
	~CNetManager();
public:
	/**************************************************************************
	*��������GetNetDataDispenserPtr
	*�������ܣ���ȡ�������ݷַ�������ָ��
	*������void
	*����ֵ��NetDataDispenser���͵�ָ��
	**************************************************************************/
	NetDataDispenser*  GetNetDataDispenserPtr();
	/**************************************************************************
	*��������GetNetProcessPtr
	*�������ܣ���ȡ���������������ָ��
	*������void
	*����ֵ��NetProcess���͵�ָ��
	**************************************************************************/
	NetProcess*		   GetNetProcessPtr();
	void			   InitNet();
private slots:
	void				DisPenserPacketToClientSlot();
private:
	NetDataDispenserPtr	m_pNetDataDispenser;
	QThread				m_NetDataDispenserThread;
	NetProcessPtr		m_pNetProcess;
	QTimer				*m_Timer;
};

#endif // CNetManager_H
