#include "ControllerPresenter.h"
#include "ControllerAcftTrack.h"
#include "TotalAircraftTrace.h"
#include "public/coordinate.h"
#include "Manager/DataManager.h"
#include <iostream>
ControllerPresenter::ControllerPresenter()

{
	if(! m_pAcftTraces)
	{
		m_pAcftTraces = boost::make_shared<TotalAircraftTrace>();
	}
	double vDCenterLongtitude = 0.00;
	double vDCenterLatitude = 0.00;
	theData::instance().GetCenterCoordinate(vDCenterLongtitude,vDCenterLatitude);
	if(! m_pCoordinate)
	{
		m_pCoordinate = boost::make_shared<Coordinate>(vDCenterLongtitude,vDCenterLatitude);
	}

}

ControllerPresenter::~ControllerPresenter()
{

}

AircraftTrace* ControllerPresenter::UpdateSingleTrace( const track_type& track,PublicDataStruct::RADAR_SIGNAL_TYPE radarType )
{
   ControllerAcftTrack* pTrack = m_pAcftTraces->GetAircraftTrace<ControllerAcftTrack>(track.iTrackID);
   if(NULL == pTrack)
   {
	   pTrack = new ControllerAcftTrack;
       pTrack->m_nTraceID = track.iTrackID;
   }
  // pTrack->m_strName = track.flight
   pTrack->m_nTrackCount = 0;
   pTrack->m_euTrackType		= track.TrackType;
   pTrack->m_nICAOAddress		= track.iICAOAddr;
   pTrack->m_dLongitude			= track.dLongitude;
   pTrack->m_dLatitude			= track.dLatitude;
   pTrack->m_euAltitudeType		= track.AltitudeType;
   pTrack->m_dGAS				= track.dGS;
   pTrack->m_strName			= track.strCallSign;
   pTrack->m_strSSR				= track.strSSR;
   pTrack->m_bSPIFlag			= true;
   pTrack->m_euEmergencyType	= track.Emergency;
   pTrack->m_euObjType			= track.ObjType;
   pTrack->m_dTrackAngle		= track.dTrackAngle;
   if(track.dROCD >0)
   {
	   pTrack->m_byAtt = 1;//上升
   }
   else if(track.dROCD < 0)
   {
	   pTrack->m_byAtt = 2;//下降
   }
   else
   {
	   pTrack->m_byAtt = 0;//平飞
   }
   pTrack->m_bHide = false;
   //更新航迹的雷达类型
   pTrack->m_eCurSignalType =  radarType;
   double dx = 0.00;
   double dy = 0.00;
   m_pCoordinate.get()->ConvertLongLat2XY(pTrack->m_dLongitude,pTrack->m_dLatitude,dx,dy);
   pTrack->m_fAbsX = static_cast<float>(dx);
   pTrack->m_fAbsY = static_cast<float>(dy);
   pTrack->m_bShowLabel = true;
   pTrack->ComputPRLPos(pTrack->m_nTraceID);
   return pTrack;
}
