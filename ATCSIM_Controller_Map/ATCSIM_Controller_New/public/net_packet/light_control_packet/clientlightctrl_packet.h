#ifndef CLIENTLIGHTCTRLPACKET_H
#define CLIENTLIGHTCTRLPACKET_H

#include "Serial_Base.h"
enum ENUM_LIGHTCTRLTYPE
{
	LIGHTGROUPCTRL,  //灯光组
	LIGHTCOLLECTIONCTRL, //灯光集
};

class ClientLightCtrlPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ClientLightCtrlPacket);
public:

	int m_iAirportID; // 对哪一个机场的灯进行控制
    ENUM_LIGHTCTRLTYPE m_eLightCtrlType;
	int m_iLightID; // 控制的灯光的ID
	float m_LightInstensity;//灯光强度
private:
	SERIALIZE_PACKET(m_iAirportID & m_eLightCtrlType & m_iLightID & m_LightInstensity);

};
struct LightGroupInfoVIS
{
	int m_iAirportID; // 对哪一个机场的灯进行控制
	int m_iLightID; // 控制的灯光组的ID
	float m_LightInstensity;//灯光强度
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iLightID & m_LightInstensity ;
	}
};
class ClientLightCtrlPacketACK2VIS : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ClientLightCtrlPacketACK2VIS);
public:

	std::vector<LightGroupInfoVIS> m_vLightGroupInfoVIS;
private:
	SERIALIZE_PACKET(m_vLightGroupInfoVIS);

};

#endif