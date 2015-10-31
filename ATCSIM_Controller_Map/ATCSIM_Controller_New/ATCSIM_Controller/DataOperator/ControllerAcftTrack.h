#ifndef CONTROLLERACFTTRACK_H
#define CONTROLLERACFTTRACK_H

#include "AircraftTrace.h"

class ControllerAcftTrack:public AircraftTrace 
{
	

public:
	ControllerAcftTrack();
	~ControllerAcftTrack();
	ControllerAcftTrack(const ControllerAcftTrack& rhs);

	public:
	//std::vector<std::string> m_vSensors; ///< 检测到该航迹的传感器名称数组, 当用于单监视航迹时，该字段无用
    bool					 m_bSPIFlag;
	int						 m_nTrackCount;
	};

#endif // CONTROLLERACFTTRACK_H
