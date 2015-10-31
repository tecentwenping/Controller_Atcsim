#ifndef _REGIONCTRL_PACKET_H_
#define _REGIONCTRL_PACKET_H_

#include "serial_base.h"
#include <string>
using namespace std;

#include "Serialization/wserialize.h"

struct RegionCtrlInfo 
{
	std::string m_strAreaName;		//区域名
	std::string m_strActiveTime;    //激活时间(HHMM，如：0830)
	std::string m_strDeactiveTime;  //关闭时间(HHMM，如：0835)
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, RegionCtrlInfo& ud, const unsigned int version)
{
	return	ar & ud.m_strAreaName & ud.m_strActiveTime & ud.m_strDeactiveTime;
}

class RegionCtrlInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RegionCtrlInfoPacket);

public:
	std::vector<RegionCtrlInfo> m_vRegionCtrlInfo;
private:
	SERIALIZE_PACKET(m_vRegionCtrlInfo);
};


#endif