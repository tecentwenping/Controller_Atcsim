#pragma once
#include "serial_base.h"
#include "public/site_info.h"

class CCheckInPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CCheckInPacket);

public:
	site_info  m_site_info; 
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();

};

