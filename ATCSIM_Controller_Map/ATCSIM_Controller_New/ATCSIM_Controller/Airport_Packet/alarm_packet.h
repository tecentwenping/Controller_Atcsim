#ifndef _WARNING_PACKET_H_
#define _WARNING_PACKET_H_

//#include "serial_base.h"
#include <string>
#include <map>
#include "public/site_info.h"
using namespace std;

#include "Serialization/wserialize.h"

//! 告警类型
enum ENUM_ALARM_TYPE
{
    ALARM_SPI   = 0x0001,   //特殊地理位置
    ALARM_HJ    = 0x0002,   //劫机
    ALARM_CF    = 0x0004,   //通讯失效
    ALARM_EM    = 0x0008,   //紧急情况
    ALARM_STCA  = 0x0010,   //冲突告警
    ALARM_MSAW  = 0x0020,   //低高告警
    ALARM_DAIW  = 0x0040,   //区域告警
    ALARM_CLAM  = 0x0080,   //偏离许可高度
    ALARM_RAM   = 0x0100,   //偏航
    ALARM_RVSM  = 0x0200,   //未获准或未知RVSM运行目标进入RVSM空域
};

//! 告警包结构
struct AlarmInfo 
{
    int    AlarmFlag;           //告警标志，由低位到高位分别表示SPI,HJ,CF,EM,STCA,MSAW,DAIW,CLAM,RAM,RVSM
	int    STCAAlertTime;		//冲突预警时间（0-告警，非0-预警，单位：秒）
	int    MSAWAlertTime;		//低高预警时间（0-告警，非0-预警，单位：秒）                      
	int    DAIWAlertTime;		//区域预警时间（0-告警，非0-预警，单位：秒）
	int    RVSMAlertTime;		//RVSM预警时间（0-告警，非0-预警，单位：秒）
    AlarmInfo()
    {
        AlarmFlag = 0;
        STCAAlertTime = 0xffff;
        MSAWAlertTime = 0xffff;
        DAIWAlertTime = 0xffff;
        RVSMAlertTime = 0xffff;
    }
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, AlarmInfo& ud, const unsigned int version)
{
	return	ar & ud.AlarmFlag & ud.STCAAlertTime & ud.MSAWAlertTime & ud.DAIWAlertTime & ud.RVSMAlertTime;
}

// class AlarmPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(AlarmPacket);
// 
// public:
// 	map<int,AlarmInfo> m_mpAlarminfos;//int:飞机的id，AlarmInfo：飞机的告警信息
// private:
// 	SERIALIZE_PACKET(m_mpAlarminfos);
// };

//!发给机长席位的告警包，目前只包含冲突检测信息
//class PilotAlarmPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(PilotAlarmPacket);
//
//public:
//	map<int,AlarmInfo> m_mpPilotAlarminfos;//int:飞机的id，AlarmInfo：飞机的告警信息
//private:
//	SERIALIZE_PACKET(m_mpPilotAlarminfos);
//};


#endif /*_WARNING_PACKET_H_*/