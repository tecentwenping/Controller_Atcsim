#ifndef CONTROLLERPRESENTER_H
#define CONTROLLERPRESENTER_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: ControllerPresenter
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/03
  【描  述】:  此文件定义了类ControllerPresenter，该类是航迹处理类
  【其  它】:   
**************************************************************************/
#include "public/PublicStruct.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class AircraftTrace;
class TotalAircraftTrace;
class ControllerAcftTrack;
class Coordinate;
typedef boost::shared_ptr<TotalAircraftTrace> AcftTracesPtr;
typedef boost::shared_ptr<Coordinate> CoordinatePtr;
class ControllerPresenter 
{
public:
	typedef  PublicDataStruct::SDPSTrack   track_type;
public:
	ControllerPresenter();
	~ControllerPresenter();
public:

public:
	AircraftTrace* UpdateSingleTrace(const track_type& track,PublicDataStruct::RADAR_SIGNAL_TYPE radarType);
private:
	AcftTracesPtr				m_pAcftTraces;
	boost::shared_mutex         m_traceCheckLocker;  //保存航迹更新和航迹检测修改的锁
	CoordinatePtr				m_pCoordinate;
};

#endif // CONTROLLERPRESENTER_H
