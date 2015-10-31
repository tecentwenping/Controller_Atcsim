#ifndef CLIENTLIGHTCTRLPACKET_H
#define CLIENTLIGHTCTRLPACKET_H

#include "Serial_Base.h"
enum ENUM_LIGHTCTRLTYPE
{
	LIGHTGROUPCTRL,  //�ƹ���
	LIGHTCOLLECTIONCTRL, //�ƹ⼯
};

class ClientLightCtrlPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ClientLightCtrlPacket);
public:

	int m_iAirportID; // ����һ�������ĵƽ��п���
    ENUM_LIGHTCTRLTYPE m_eLightCtrlType;
	int m_iLightID; // ���Ƶĵƹ��ID
	float m_LightInstensity;//�ƹ�ǿ��
private:
	SERIALIZE_PACKET(m_iAirportID & m_eLightCtrlType & m_iLightID & m_LightInstensity);

};
struct LightGroupInfoVIS
{
	int m_iAirportID; // ����һ�������ĵƽ��п���
	int m_iLightID; // ���Ƶĵƹ����ID
	float m_LightInstensity;//�ƹ�ǿ��
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