#ifndef _CLOUD_PACKET_H_
#define _CLOUD_PACKET_H_
#include "Serial_Base.h"
#include "public/BaseTypeDefine/EnvTypeDefine/CloudDataDefine.h"
class CloudPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CloudPacket);
public:
	std::vector <ST_CloudData> m_vClouds;
private:
	SERIALIZE_PACKET(m_vClouds);
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
};

#endif