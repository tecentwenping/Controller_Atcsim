#ifndef _LIGHT_CTRL_PACKET_H_
#define _LIGHT_CTRL_PACKET_H_

#include "Serial_Base.h"
class LightCtrlPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightCtrlPacket);
public:

	int m_iAirportID; // ����һ�������ĵƽ��п���
	int m_iLightID; // ���Ƶĵƹ��ID
	double m_LightInstensity;//�ƹ�ǿ��
private:
	SERIALIZE_PACKET(m_iAirportID & m_iLightID & m_LightInstensity);
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
};

#endif