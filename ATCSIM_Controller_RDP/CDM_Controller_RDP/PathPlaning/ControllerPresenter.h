#ifndef CONTROLLERPRESENTER_H
#define CONTROLLERPRESENTER_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: ControllerPresenter
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/03
  ����  ����:  ���ļ���������ControllerPresenter�������Ǻ���������
  ����  ����:   
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
	boost::shared_mutex         m_traceCheckLocker;  //���溽�����ºͺ�������޸ĵ���
	CoordinatePtr				m_pCoordinate;
};

#endif // CONTROLLERPRESENTER_H
