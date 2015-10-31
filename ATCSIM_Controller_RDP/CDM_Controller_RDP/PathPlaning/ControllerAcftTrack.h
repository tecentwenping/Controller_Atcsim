#ifndef CONTROLLERACFTTRACK_H
#define CONTROLLERACFTTRACK_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: ControllerAcftTrack
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/03
  ����  ����:  ���ļ���������ControllerAcftTrack�������Ǻ�����
  ����  ����:   
**************************************************************************/

#include "AircraftTrace.h"
class ControllerAcftTrack:public AircraftTrace 
{
	

public:
	ControllerAcftTrack();
	~ControllerAcftTrack();

public:
	std::vector<std::string> m_vSensors; ///< ��⵽�ú����Ĵ�������������, �����ڵ����Ӻ���ʱ�����ֶ�����
    bool					 m_bSPIFlag;
	int						 m_nTrackCount;
};
#endif // CONTROLLERACFTTRACK_H
