#ifndef _AIRCRAFTINFO_H
#define _AIRCRAFTINFO_H


#include "wworldpoint.h"
#include "AircraftAlarmInfo.h"
#include <boost/shared_ptr.hpp>


//该类主要是作为飞行计划信息的基类使用
class AircraftInfo
{
public:
	AircraftInfo(){};
	virtual ~AircraftInfo(){};
public:
	void UpdateAlarmInfo(const AircraftAlarmInfo& info){m_AlarmInfo = info;};
	AircraftAlarmInfo* GetAlarmInfoPtr(){ return &m_AlarmInfo; }
	virtual void UpdateTrackNo(const int nTrackNo){}
public:
	//尾流
	virtual std::string& GetTurbo() = 0;
	virtual std::string& GetArrAerodrome() = 0;
	virtual std::string& GetAcftType() = 0;
	virtual std::string& GetSectorName() = 0;
private:
	AircraftAlarmInfo m_AlarmInfo;
};


typedef boost::shared_ptr<AircraftInfo> AircraftInfoPtr;


#endif