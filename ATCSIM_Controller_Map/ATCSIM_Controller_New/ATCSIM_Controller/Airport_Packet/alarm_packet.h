#ifndef _WARNING_PACKET_H_
#define _WARNING_PACKET_H_

//#include "serial_base.h"
#include <string>
#include <map>
#include "public/site_info.h"
using namespace std;

#include "Serialization/wserialize.h"

//! �澯����
enum ENUM_ALARM_TYPE
{
    ALARM_SPI   = 0x0001,   //�������λ��
    ALARM_HJ    = 0x0002,   //�ٻ�
    ALARM_CF    = 0x0004,   //ͨѶʧЧ
    ALARM_EM    = 0x0008,   //�������
    ALARM_STCA  = 0x0010,   //��ͻ�澯
    ALARM_MSAW  = 0x0020,   //�͸߸澯
    ALARM_DAIW  = 0x0040,   //����澯
    ALARM_CLAM  = 0x0080,   //ƫ����ɸ߶�
    ALARM_RAM   = 0x0100,   //ƫ��
    ALARM_RVSM  = 0x0200,   //δ��׼��δ֪RVSM����Ŀ�����RVSM����
};

//! �澯���ṹ
struct AlarmInfo 
{
    int    AlarmFlag;           //�澯��־���ɵ�λ����λ�ֱ��ʾSPI,HJ,CF,EM,STCA,MSAW,DAIW,CLAM,RAM,RVSM
	int    STCAAlertTime;		//��ͻԤ��ʱ�䣨0-�澯����0-Ԥ������λ���룩
	int    MSAWAlertTime;		//�͸�Ԥ��ʱ�䣨0-�澯����0-Ԥ������λ���룩                      
	int    DAIWAlertTime;		//����Ԥ��ʱ�䣨0-�澯����0-Ԥ������λ���룩
	int    RVSMAlertTime;		//RVSMԤ��ʱ�䣨0-�澯����0-Ԥ������λ���룩
    AlarmInfo()
    {
        AlarmFlag = 0;
        STCAAlertTime = 0xffff;
        MSAWAlertTime = 0xffff;
        DAIWAlertTime = 0xffff;
        RVSMAlertTime = 0xffff;
    }
};

//�ṹ������л�����Ƕ��ʽ��
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
// 	map<int,AlarmInfo> m_mpAlarminfos;//int:�ɻ���id��AlarmInfo���ɻ��ĸ澯��Ϣ
// private:
// 	SERIALIZE_PACKET(m_mpAlarminfos);
// };

//!��������ϯλ�ĸ澯����Ŀǰֻ������ͻ�����Ϣ
//class PilotAlarmPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(PilotAlarmPacket);
//
//public:
//	map<int,AlarmInfo> m_mpPilotAlarminfos;//int:�ɻ���id��AlarmInfo���ɻ��ĸ澯��Ϣ
//private:
//	SERIALIZE_PACKET(m_mpPilotAlarminfos);
//};


#endif /*_WARNING_PACKET_H_*/