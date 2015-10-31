//���ļ���Ż���������ض���ı༭�����������¶���ı༭��

//����                                        �༭��
//����(AircraftData)                       AircraftDataEditPacket

#ifndef _H_BASE_DATA_EDIT_PACKETS_H
#define _H_BASE_DATA_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"


//������Ϣ�༭��
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


//�������ݱ༭��
class AircraftPerformanceEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AircraftPerformanceEditPacket);
public:
	EDIT_TYPE m_edit_type;
	AircraftPerformance m_data;
private:

	SERIALIZE_PACKET(m_edit_type & m_data);
};
//������Ϣ�༭��
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

//���չ�˾�༭��
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

//����༭��
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

//����ģ�ͱ༭��
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