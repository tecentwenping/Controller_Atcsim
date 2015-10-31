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
   traces = m_hmTraces;
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
	RADAR_SIGNAL_TYPE type = static_cast<RADAR_SIGNAL_TYPE>(nRadarType);
	BOOST_FOREACH(hmFplTraces::value_type& value,m_hmTraces)
	{
		value.second->m_eCurSignalType = type;
	}
  
}


