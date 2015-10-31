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
	*函数名：GetNetDataDispenserPtr
	*函数功能：获取网络数据分发器管理指针
	*变量：void
	*返回值：NetDataDispenser类型的指针
	**************************************************************************/
	NetDataDispenser*  GetNetDataDispenserPtr();
	/**************************************************************************
	*函数名：GetNetProcessPtr
	*函数功能：获取处理网络数据类的指针
	*变量：void
	*返回值：NetProcess类型的指针
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
