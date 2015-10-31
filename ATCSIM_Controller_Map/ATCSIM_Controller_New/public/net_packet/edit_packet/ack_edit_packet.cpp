#include "ack_edit_packet.h"
#include <memory>

//»Ø¸´±à¼­°ü
PKT_IMPLEMENT_DYNCREATE(AckDataEditPacket)
//void AckDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer ;
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	memcpy(pTemp,&m_bSuccessed,sizeof(m_bSuccessed));
//	pTemp += sizeof(m_bSuccessed);
//
//	memcpy(pTemp, m_strErrorInfo.c_str(), m_strErrorInfo.size()+1);
//	pTemp += m_strErrorInfo.size() + 1;
//
//}
//
//void AckDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	memcpy(&m_bSuccessed,pTemp,sizeof(m_bSuccessed));
//	pTemp += sizeof(m_bSuccessed);
//
//	m_strErrorInfo.assign(pTemp);
//	pTemp += m_strErrorInfo.size() + 1;
//}
//
//int AckDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += sizeof(m_bSuccessed);
//	size += m_strErrorInfo.size() + 1;
//
//	return size;	
//}
