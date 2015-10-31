#include "basedata_edit_packets.h"

//机型信息编辑包
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
/*----------------车辆编辑包---------------*/
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

/*----------------航空公司编辑包---------------*/
PKT_IMPLEMENT_DYNCREATE(CompanyEditPacket)

/*-------------航班编辑包---------------*/
PKT_IMPLEMENT_DYNCREATE(FlightEditPacket)

/*-------------机型模型编辑包---------------*/
PKT_IMPLEMENT_DYNCREATE(AircraftModelEditPacket)