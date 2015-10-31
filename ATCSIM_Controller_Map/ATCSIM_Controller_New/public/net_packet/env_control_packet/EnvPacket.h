//// by  wmq 2010.3.5  ������

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
 
// ������  ��Ϊ ��β����� by wmq 2010.3.5�޸�   
class EnvPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EnvPacket);
public: 		
	// ѵ���ƻ�����ʱ��
	CTowerTime m_runTime;	//ѵ���ƻ��ۼ������˶೤ʱ��.
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
