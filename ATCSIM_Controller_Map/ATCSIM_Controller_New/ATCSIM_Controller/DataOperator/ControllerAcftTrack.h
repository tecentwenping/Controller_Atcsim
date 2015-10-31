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
	//std::vector<std::string> m_vSensors; ///< ��⵽�ú����Ĵ�������������, �����ڵ����Ӻ���ʱ�����ֶ�����
    bool					 m_bSPIFlag;
	int						 m_nTrackCount;
	};

#endif // CONTROLLERACFTTRACK_H
