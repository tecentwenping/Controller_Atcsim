#include "checkin_packet.h"
#include <memory.h>


PKT_IMPLEMENT_DYNCREATE(CCheckInPacket);

void CCheckInPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_site_info.site_type,sizeof(int));
	pTemp += sizeof(int);
	memcpy(pTemp, &m_site_info.site_id, sizeof(int));
	pTemp += sizeof(unsigned);
	memcpy(pTemp, &m_site_info.topic_pub, sizeof(unsigned));
	pTemp += sizeof(unsigned);
	memcpy(pTemp, &m_site_info.topic_sub, sizeof(unsigned));
}

void CCheckInPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_site_info.site_type, pTemp, sizeof(int));
	pTemp += sizeof(int);
	memcpy(&m_site_info.site_id, pTemp, sizeof(int));
	pTemp += sizeof(unsigned);
	memcpy(&m_site_info.topic_pub, pTemp, sizeof(unsigned));
	pTemp += sizeof(unsigned);
	memcpy(&m_site_info.topic_sub, pTemp, sizeof(unsigned));
}

int CCheckInPacket::GetBufferSize()
{
	return sizeof(int) + sizeof(int) + sizeof(unsigned) + sizeof(unsigned);
}
