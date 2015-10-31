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
	SPI_ALARM = 0x01,				//�������λ�ø澯
	HJ_ALARM = 0x02,				//7500 
	CF_ALARM = 0x04,				//7600
	EM_ALARM = 0x08,				//7700
	STCA_ALARM = 0x10,	  	    //��ͻ�澯
	STCA_PREALARM = 0x20,       //��ͻԤ��
	MSAW_ALARM = 0x40,			//�͸߸澯
	MSAW_PREALARM = 0x80,       //�Ϳ�Ԥ��
	DAIW_ALARM = 0x100,			//�����澯 ������ ����
	DAIW_PREALARM = 0x200,      //����Ԥ��
	CLAM_ALARM = 0x400,			//CFL�澯
	RAM_ALARM = 0x800,				//ƫ��RAM�澯
	RVSM_ALARM = 0x1000, 		//δ��׼��δ֪RVSM����Ŀ�����RVSM����
	DUPE_ALARM = 0x2000,        //������澯
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
// 	int    SPI;				//�������λ�ø澯
// 	int    HJ;				//7500 
// 	int    CF;				//7600
// 	int    EM;				//7700
// 	int    STCA;	  	    //��ͻ�澯
// 	int    MSAW;			//�͸߸澯
// 	int    DAIW;			//�����澯 ������ ����
// 	int    CLAM;			//CFL�澯
// 	int    RAM;				//ƫ��RAM�澯
// 	int    rvsmAlarm;		//δ��׼��δ֪RVSM����Ŀ�����RVSM����

	//////////////////////////////////////////////////////////////////////////
	int    STCAAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  30
	int    MSAWAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  60                        
	int    DAIWAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  0xffe
	int    RVSMAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  0xffe

};





#endif