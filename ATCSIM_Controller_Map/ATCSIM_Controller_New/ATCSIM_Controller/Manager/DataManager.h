#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <utility>
#include <QThread>
#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pool/detail/singleton.hpp>
#include <QTimer>
using boost::details::pool::singleton_default;
class TotalAircraftTrace;
class CRecvAircraftTrace;
class CGlyphCreator;
class AircraftTrace;
typedef boost::shared_ptr<TotalAircraftTrace> TotalAircraftTracePtr;
typedef boost::shared_ptr<CRecvAircraftTrace> RecvAircraftTracePtr;
typedef boost::shared_ptr<QTimer>			  PTimerPtr;
class CDataManager:public QObject
{
	Q_OBJECT
public:
	CDataManager();
	~CDataManager();
public:
	void InitNet();
	TotalAircraftTrace*  GetTotalAircraftTraceInstance();
    void UpdatePRLTime(AircraftTrace* pAircraftTrace,const float& fTime);
	//RecvAircraftTrace*	 GetRecvAircraftTraceInstance();
private:
	void UpdatePRLTime(const float& fTime);
private slots:
	
	void UpdatePRLTimeSlot();

private:
	QThread					m_RecvAircraftTraceThread;
	TotalAircraftTracePtr   m_pTotalAircraftTrace;
	RecvAircraftTracePtr	m_pRecvAircraftTrace;
	PTimerPtr				m_pTimer;
};
//typedef singleton_default<CDataManager> theData;
#endif // DATAMANAGER_H
