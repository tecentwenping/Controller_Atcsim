#pragma once
#include "serial_base.h"
#include "public/site_info.h"
#include "Serialization/wserialize.h"

class EnvVoiceCtrlPacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EnvVoiceCtrlPacket);
public:
	unsigned char   m_usoundState;  // 存放声音的种类
	float          m_fVolume;     //声音的大小 
private:
	SERIALIZE_PACKET(m_usoundState & m_fVolume);
};