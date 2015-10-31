#include "CGlyphUpdater.h"
#include "Manager/DataManager.h"
#include "MainApp.h"
#include "Glyph/AircraftTrace.h"
#include "DataOperator/TotalAircraftTrace.h"
#include "Manager/MapManager.h"
#include "Glyph/CGlyphCreator.h"
#include "wworldpoint.h"
#include <hash_map>
#include <boost/thread/shared_mutex.hpp>
CGlyphUpdater::CGlyphUpdater()
{ 
	m_iCount = 0;

}

CGlyphUpdater::~CGlyphUpdater()
{

}

void CGlyphUpdater::UpdateTrace()
{
	//不断的监视看是否有新的航迹需要更新
  while(1)
  {
      boost::shared_mutex   m_traceLocker;
	  m_traceLocker.lock();
	  stdext::hash_map<int,AircraftTrace*>& tmp = theApp::instance().GetDataManagerPtr().get()->GetTotalAircraftTraceInstance()->GetTraces();
	  if(! tmp.empty())
	  {
		  stdext::hash_map<int,AircraftTrace*>::iterator Iter = tmp.begin();
		  while(Iter != tmp.end())
		  {
			 theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()->UpdateSingleAircraftTrace(Iter->second);
		  }
		  ++ Iter;
	  }
	  m_traceLocker.unlock();
  }
}

void CGlyphUpdater::UpdateAircraftTraceSlot( int iTraceID )
{
    m_iTraceID = iTraceID;
	/*QTimer *vTimer = new QTimer;
	connect(vTimer,SIGNAL(timeout()),this,SLOT(UpdateAircraftTraceSlot_1()));
	vTimer->start(3000);*/
	UpdateAircraftTraceSlot_1();
}

void CGlyphUpdater::UpdateAircraftTraceSlot_1()
{

	boost::shared_mutex   m_traceLocker;
	m_traceLocker.lock();
	//stdext::hash_map<int,AircraftTrace*>& tmp = theApp::instance().GetDataManagerPtr().get()->GetTotalAircraftTraceInstance()->GetTraces();
	stdext::hash_map<int,AircraftTrace*>& tmp = theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()->GetTrace();
	if(! tmp.empty())
	{
		stdext::hash_map<int,AircraftTrace*>::iterator Iter = tmp.find(m_iTraceID);
		if(Iter != tmp.end())
		{
			theApp::instance().GetMapMangerPtr().get()->GetGlyphCreatorPtr().get()->UpdateSingleAircraftTrace(Iter->second);
		}
	}
	m_traceLocker.unlock();

}

