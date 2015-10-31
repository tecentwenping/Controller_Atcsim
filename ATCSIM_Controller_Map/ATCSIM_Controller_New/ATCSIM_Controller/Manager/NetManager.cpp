#include "NetManager.h"
#include "Net/RecvAircraftTrace.h"
CNetManager::CNetManager()
{
	Init();

}

CNetManager::~CNetManager()
{

}

void CNetManager::Init()
{
   if(! m_pRecvAircraftTrace)
   {
	   m_pRecvAircraftTrace = boost::make_shared<CRecvAircraftTrace>();
   }
}

RecvAircraftTracePtr CNetManager::GetRecvAircraftTracePtr()
{
	 return m_pRecvAircraftTrace;
}
