#ifndef CONTROLLERACFTTRACK_H
#define CONTROLLERACFTTRACK_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: ControllerAcftTrack
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/03
  【描  述】:  此文件定义了类ControllerAcftTrack，该类是航迹类
  【其  它】:   
**************************************************************************/

#include "AircraftTrace.h"
class ControllerAcftTrack:public AircraftTrace 
{
	

public:
	ControllerAcftTrack();
	~ControllerAcftTrack();

public:
	std::vector<std::string> m_vSensors; ///< 检测到该航迹的传感器名称数组, 当用于单监视航迹时，该字段无用
    bool					 m_bSPIFlag;
	int						 m_nTrackCount;
};
#endif // CONTROLLERACFTTRACK_H
