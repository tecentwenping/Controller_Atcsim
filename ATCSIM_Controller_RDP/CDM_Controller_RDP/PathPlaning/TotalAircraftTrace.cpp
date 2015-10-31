#include "TotalAircraftTrace.h"
#include "AircraftTrace.h"
#include <boost/foreach.hpp>
TotalAircraftTrace::TotalAircraftTrace()
{
    m_pCurTraces = NULL;
}

TotalAircraftTrace::~TotalAircraftTrace()
{

}

void TotalAircraftTrace::SetCurAircraftTrace( int iID )
{
	if(-1 == iID)
	{
		m_pCurTraces = NULL;
	}
	else
	{
      m_pCurTraces = GetAircraftTrace<AircraftTrace>(iID);
	}

}

AircraftTrace* TotalAircraftTrace::GetAircraftTrace( int nTraceNo )
{
	hmFplTraces::iterator iter = m_hmTraces.find(nTraceNo);
	if(iter != m_hmTraces.end())
	{
		return iter->second;
	}
	return NULL;
}

AircraftTrace* TotalAircraftTrace::GetCurAircraftTrace()
{
	return m_pCurTraces;

}

void TotalAircraftTrace::GetTraces( hmFplTraces& traces )
{
	boost::shared_mutex vMutex;
	vMutex.lock();
   traces = m_hmTraces;
   vMutex.unlock();
}

void TotalAircraftTrace::ClearTraces()
{
	BOOST_FOREACH(hmFplTraces::value_type& value, m_hmTraces)
	{
		if (value.second != NULL)
		{
			delete value.second;
			value.second = NULL;
		}
	}
	m_hmTraces.clear();
	m_pCurTraces = NULL;

}

void TotalAircraftTrace::UpdateTracksType( int nRadarType )
{
	PublicDataStruct::RADAR_SIGNAL_TYPE type = static_cast<PublicDataStruct::RADAR_SIGNAL_TYPE>(nRadarType);
	BOOST_FOREACH(hmFplTraces::value_type& value,m_hmTraces)
	{
		value.second->m_eCurSignalType = type;
	}
  
}
//void TotalAircraftTrace::GetAircraftTracePoint( int nTraceno,std::vector<WPointF>& tracePoint)
//{
//	hmFplTracePoint::iterator Iter = m_hmTracePoint.find(nTraceno);
//	if(Iter != m_hmTracePoint.end())
//		tracePoint = Iter->second;
//}
//
//void TotalAircraftTrace::GetAircraftTracePoint( hmFplTracePoint& hmTracePoint )
//{
//	hmTracePoint = m_hmTracePoint;
//}
//void TotalAircraftTrace::UpdateAircraftTracePoint( int iTraceno,const std::vector<WPointF>& vTracePoint )
//{
//	m_hmTracePoint[iTraceno] = vTracePoint;
//}

void TotalAircraftTrace::UpdateAircraftTracePoint1( int iTraceno,const std::deque<WPointF>& dTracePoint )
{
       m_hmTracePoint1[iTraceno]=dTracePoint;
}

void TotalAircraftTrace::GetAircraftTracePoint1( int iTraceno,std::deque<WPointF>& dTracePoint )
{
	hmFplTracePoint1::iterator Iter=m_hmTracePoint1.find(iTraceno);
	if(Iter!=m_hmTracePoint1.end())
		dTracePoint=Iter->second;
}
void TotalAircraftTrace::GetAircraftTracePoint1(hmFplTracePoint1& hmTracePoint){
	
	hmTracePoint=m_hmTracePoint1;
}
TotalAircraftTrace::hmFplTraces TotalAircraftTrace::m_hmTraces;



