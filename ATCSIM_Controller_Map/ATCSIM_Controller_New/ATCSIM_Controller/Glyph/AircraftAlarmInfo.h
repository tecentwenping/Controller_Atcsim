#ifndef _AIRCRAFT_ALARMINFO_H
#define _AIRCRAFT_ALARMINFO_H

#include "alarm_packet.h"

enum WarnType
{
	no_warn = 0,
	pre_warn,
	warnning,
};

enum ENUM_ALARMTYPE
{
	NO_ALARM  = 0x00,
	SPI_ALARM = 0x01,				//特殊地理位置告警
	HJ_ALARM = 0x02,				//7500 
	CF_ALARM = 0x04,				//7600
	EM_ALARM = 0x08,				//7700
	STCA_ALARM = 0x10,	  	    //冲突告警
	STCA_PREALARM = 0x20,       //冲突预警
	MSAW_ALARM = 0x40,			//低高告警
	MSAW_PREALARM = 0x80,       //低空预警
	DAIW_ALARM = 0x100,			//三区告警 限制区 禁区
	DAIW_PREALARM = 0x200,      //三区预警
	CLAM_ALARM = 0x400,			//CFL告警
	RAM_ALARM = 0x800,				//偏航RAM告警
	RVSM_ALARM = 0x1000, 		//未获准或未知RVSM运行目标进入RVSM空域
	DUPE_ALARM = 0x2000,        //二次码告警
};
//define alarm flags
class AircraftAlarmInfo
{
public:
	AircraftAlarmInfo();
	~AircraftAlarmInfo();
public:
	void UpdateAlarmInfo(const AlarmInfo& alarmInfo);
	void UpdateSTCAAlarmInfo(const AlarmInfo& alarmInfo);
	void AlarmStrings(std::vector<std::string>& vStrings);
	bool GetIsAlarmOrWarnning();
public:
	int m_eAlarmFlag;
// 	int    SPI;				//特殊地理位置告警
// 	int    HJ;				//7500 
// 	int    CF;				//7600
// 	int    EM;				//7700
// 	int    STCA;	  	    //冲突告警
// 	int    MSAW;			//低高告警
// 	int    DAIW;			//三区告警 限制区 禁区
// 	int    CLAM;			//CFL告警
// 	int    RAM;				//偏航RAM告警
// 	int    rvsmAlarm;		//未获准或未知RVSM运行目标进入RVSM空域

	//////////////////////////////////////////////////////////////////////////
	int    STCAAlertTime;		//0-告警  非0-预警时间(秒)  30
	int    MSAWAlertTime;		//0-告警  非0-预警时间(秒)  60                        
	int    DAIWAlertTime;		//0-告警  非0-预警时间(秒)  0xffe
	int    RVSMAlertTime;		//0-告警  非0-预警时间(秒)  0xffe

};





#endif