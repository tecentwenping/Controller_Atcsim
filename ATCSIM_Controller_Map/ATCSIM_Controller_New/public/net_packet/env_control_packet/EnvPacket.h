//// by  wmq 2010.3.5  环境包

#ifndef _ENV_PACKET_H_
#define _ENV_PACKET_H_

#include "Serial_Base.h"
#include "public\BaseTypeDefine\EnvTypeDefine/EnvStruct.h"
#include "public\TowerTime\TowerTime.h"

#pragma warning(disable:4786)


/*********************************************************************
PacketClass			Sender				-> Receiver
CEnvPacket			Server			    -> SuperVisor controler pilot
***********************************************************************/
 
// 环境包  因为 层次不清晰 by wmq 2010.3.5修改   
class EnvPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EnvPacket);
public: 		
	// 训练计划运行时间
	CTowerTime m_runTime;	//训练计划累计运行了多长时间.
	std::vector <ST_AirportEnvForEnvPacket> m_vEnvs;
private:
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
	SERIALIZE_PACKET(m_runTime & m_vEnvs);
};


#endif
