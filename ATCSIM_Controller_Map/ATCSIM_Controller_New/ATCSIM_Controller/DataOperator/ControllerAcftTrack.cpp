#include "ControllerAcftTrack.h"

ControllerAcftTrack::ControllerAcftTrack()
{

}

ControllerAcftTrack::ControllerAcftTrack( const ControllerAcftTrack& rhs )
{
	m_bSPIFlag = rhs.m_bSPIFlag;
	m_nTrackCount = rhs.m_nTrackCount;
}

ControllerAcftTrack::~ControllerAcftTrack()
{

}
