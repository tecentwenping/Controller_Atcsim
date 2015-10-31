#ifndef NETMANAGER_H
#define NETMANAGER_H
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class CRecvAircraftTrace;
typedef boost::shared_ptr<CRecvAircraftTrace> RecvAircraftTracePtr;
class CNetManager
{
public:
	CNetManager();
	~CNetManager();
public:
	RecvAircraftTracePtr GetRecvAircraftTracePtr();
protected:
	void Init();

private:
	RecvAircraftTracePtr m_pRecvAircraftTrace;
	
};

#endif // NETMANAGER_H
