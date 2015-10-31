#include "DataManager.h"
#include "Net/RecvAircraftTrace.h"
#include "DataOperator/TotalAircraftTrace.h"
#include "Glyph/AircraftTrace.h"
#include "MainApp.h"
#include "Manager/MapManager.h"
#include "Glyph/CGlyphCreator.h"
#include <hash_map>
#include <boost/foreach.hpp>
CDataManager::CDataManager()
{
	if(! m_pTotalAircraftTrace)
		
	{
		m_pTotalAircraftTrace = boost::make_shared<TotalAircraftTrace>();
		
		//if(!m_pTimer)
		//{
		//	//m_pTimer = boost::make_shared<QTimer>();
		//	//connect(m_pTimer.get(),SIGNAL(timeout()),this,SLOT(UpdatePRLTimeSlot()));
		//	//m_pTimer.get()->start(30000);
		//}
	}
    
	
}
CDataManager::~CDataManager()
{

}
TotalAircraftTrace* CDataManager::GetTotalAircraftTraceInstance()
{
	if(m_pTotalAircraftTrace)
	{
      return m_pTotalAircraftTrace.get();
	}
	return NULL;
	
}

void CDataManager::UpdatePRLTime(AircraftTrace* pAircraftTrace,const float& fTime)
{	
     		pAircraftTrace->SetPRLTime(fTime);
			theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()
			->UpdateSingleAircraftPRLPos(pAircraftTrace->m_strName,pAircraftTrace->m_wPRLPos);
}

void CDataManager::UpdatePRLTime( const float& fTime )
{
	if( m_pTotalAircraftTrace)
	{
		typedef TotalAircraftTrace::hmFplTraces hmFplTraces;
		hmFplTraces traces;
		m_pTotalAircraftTrace->GetTraces(traces);
		if(!traces.empty())
		{
			BOOST_FOREACH(hmFplTraces::value_type& value, traces)
			{
				UpdatePRLTime(value.second,fTime);
			}
		}
	}
}

void CDataManager::UpdatePRLTimeSlot()
{
	float fTime = 4;
	UpdatePRLTime(fTime);

}
