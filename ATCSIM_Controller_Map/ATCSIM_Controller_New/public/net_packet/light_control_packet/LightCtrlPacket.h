#ifndef _LIGHT_CTRL_PACKET_H_
#define _LIGHT_CTRL_PACKET_H_

#include "Serial_Base.h"
class LightCtrlPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightCtrlPacket);
public:

	int m_iAirportID; // 对哪一个机场的灯进行控制
	int m_iLightID; // 控制的灯光的ID
	double m_LightInstensity;//灯光强度
private:
	SERIALIZE_PACKET(m_iAirportID & m_iLightID & m_LightInstensity);
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
};

#endif