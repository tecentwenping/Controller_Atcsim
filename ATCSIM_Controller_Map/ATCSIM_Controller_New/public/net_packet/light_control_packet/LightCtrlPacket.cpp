#include "LightCtrlPacket.h"
PKT_IMPLEMENT_DYNCREATE(LightCtrlPacket);
/*
void LightCtrlPacket::WriteToBuffer(char *pBuffer)
{
	char *pTemp = pBuffer;
	
	memcpy (pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy (pTemp, &m_iLightID, sizeof(m_iLightID));
	pTemp += sizeof(m_iLightID);

	memcpy(pTemp, &m_bTurnOn, sizeof(m_bTurnOn));
	pTemp+=sizeof(m_bTurnOn);

	memcpy(pTemp,&m_r,sizeof(m_r));
	pTemp+=sizeof(m_r);

	memcpy(pTemp,&m_g,sizeof(m_g));
	pTemp+=sizeof(m_g);

	memcpy(pTemp,&m_b,sizeof(m_b));
	pTemp+=sizeof(m_b);

	memcpy(pTemp,&m_LightInstensity,sizeof(m_LightInstensity));
	pTemp+=sizeof(m_LightInstensity);
}

void LightCtrlPacket::ReadFromBuffer(const char *pBuffer)
{
	const char *pTemp = pBuffer;

	memcpy (&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy (&m_iLightID, pTemp, sizeof(m_iLightID));
	pTemp += sizeof(m_iLightID);

	memcpy(&m_bTurnOn, pTemp, sizeof(m_bTurnOn));
	pTemp+=sizeof(m_bTurnOn);

	memcpy(&m_r,pTemp,sizeof(m_r));
	pTemp+=sizeof(m_r);

	memcpy(&m_g,pTemp,sizeof(m_g));
	pTemp+=sizeof(m_r);

	memcpy(&m_b,pTemp,sizeof(m_b));
	pTemp+=sizeof(m_b);

	memcpy(&m_LightInstensity,pTemp,sizeof(m_LightInstensity));
	pTemp+=sizeof(m_LightInstensity);
}

int LightCtrlPacket::GetBufferSize()
{
	return sizeof(m_iAirportID) + sizeof(m_iLightID) + sizeof(m_bTurnOn)+3*sizeof(m_r)
		    +sizeof(m_LightInstensity);
}
*/