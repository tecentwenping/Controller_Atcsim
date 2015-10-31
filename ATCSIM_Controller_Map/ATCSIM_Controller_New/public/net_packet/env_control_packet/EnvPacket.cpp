#include "EnvPacket.h"
 
PKT_IMPLEMENT_DYNCREATE(EnvPacket);

/*
//环境包实现
void CEnvPacket::WriteToBuffer(char *pBuffer)
{

	char *pTemp = pBuffer;

	m_runTime.Serialize(pTemp);
	pTemp += m_runTime.GetSize();

	int num = m_vEnvs.size();
	memcpy(pTemp, &num, sizeof(num));
	pTemp += sizeof(num);

	ST_AirportEnvForEnvPacket Env;
	for (int i=0; i<num; i++)
	{
		Env =m_vEnvs.at(i);
		Env.WriteToBuffer(pTemp);
		pTemp += Env.GetBufferSize();
	}

}

void CEnvPacket::ReadFromBuffer(const char *pBuffer)
{

	const char *pTemp = pBuffer;

	m_runTime.UnSerialize(pTemp);
	pTemp += m_runTime.GetSize();

	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	ST_AirportEnvForEnvPacket Env;
	for (int i=0; i<num; i++)
	{
			Env.ReadFromBuffer(pTemp);
		pTemp += Env.GetBufferSize();

		m_vEnvs.push_back(Env);
	}

}

int CEnvPacket::GetBufferSize()
{

	int size = 0;

	size += m_runTime.GetSize();

	int num = m_vEnvs.size();
	size += sizeof(num);

	ST_AirportEnvForEnvPacket Env;
	for (int i=0; i<num; i++)
	{
		Env =m_vEnvs.at(i);
		size += Env.GetBufferSize();
	}
	return size;
}
*/