#include "basedata_edit_packets.h"

//������Ϣ�༭��
PKT_IMPLEMENT_DYNCREATE(AircraftDataEditPacket);
//void AircraftDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer;
//	int iOffSize = 0;
//
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	m_data.WriteToBuffer(pTemp, iOffSize);
//
//	pTemp += iOffSize;
//}
//
//void AircraftDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	int iOffSize = 0;
//
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	m_data.ReadFromBuffer(pTemp, iOffSize);
//	pTemp += iOffSize;
//}
//
//int AircraftDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += m_data.GetBufferSize();
//	return size;	
//}

PKT_IMPLEMENT_DYNCREATE(AircraftPerformanceEditPacket)
/*----------------�����༭��---------------*/
PKT_IMPLEMENT_DYNCREATE(VehicleEditPacket)
//void VehicleEditPacket::ReadFromBuffer( const char* pBuffer )
//{
//	const char* pTemp = pBuffer;
//	int iOffSize = 0;
//
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	m_data.ReadFromBuffer(pTemp, iOffSize);
//	pTemp += iOffSize;
//}
//
//void VehicleEditPacket::WriteToBuffer( char* pBuffer )
//{
//	char* pTemp = pBuffer;
//	int iOffSize = 0;
//
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//
//	m_data.WriteToBuffer(pTemp, iOffSize);
//
//	pTemp += iOffSize;
//}
//
//int VehicleEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += m_data.GetBufferSize();
//	return size;	
//}

/*----------------���չ�˾�༭��---------------*/
PKT_IMPLEMENT_DYNCREATE(CompanyEditPacket)

/*-------------����༭��---------------*/
PKT_IMPLEMENT_DYNCREATE(FlightEditPacket)

/*-------------����ģ�ͱ༭��---------------*/
PKT_IMPLEMENT_DYNCREATE(AircraftModelEditPacket)