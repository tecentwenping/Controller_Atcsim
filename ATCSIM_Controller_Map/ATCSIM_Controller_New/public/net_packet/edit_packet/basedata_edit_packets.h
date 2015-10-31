//此文件存放基础数据相关对象的编辑包，包括以下对象的编辑包

//对象                                        编辑包
//机型(AircraftData)                       AircraftDataEditPacket

#ifndef _H_BASE_DATA_EDIT_PACKETS_H
#define _H_BASE_DATA_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"


//机型信息编辑包
class AircraftDataEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AircraftDataEditPacket);
public:
	EDIT_TYPE m_edit_type;
	AircraftData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};


//机型数据编辑包
class AircraftPerformanceEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AircraftPerformanceEditPacket);
public:
	EDIT_TYPE m_edit_type;
	AircraftPerformance m_data;
private:

	SERIALIZE_PACKET(m_edit_type & m_data);
};
//车辆信息编辑包
class VehicleEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(VehicleEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Vehicle m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//航空公司编辑包
class CompanyEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CompanyEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Company m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//航班编辑包
class FlightEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Flight m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//机型模型编辑包
class AircraftModelEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AircraftModelEditPacket);
public:
	EDIT_TYPE m_edit_type;
	AircraftModel m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

#endif