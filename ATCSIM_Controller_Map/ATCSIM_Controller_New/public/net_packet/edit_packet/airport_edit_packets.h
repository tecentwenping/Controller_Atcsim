//���ļ���Ż�����ض���ı༭�����������¶���ı༭��

//����                                        �༭��
//����(AirportData)                        AirportEditPacket
//�̶���(Fixpoint)                         FixpointEditPacket
//�ܵ�(RunwayData)                         RunwayEditPacket
//��·(RoadData)                           RoadEditPacket

#ifndef _H_AIRPORT_EDIT_PACKETS_H
#define _H_AIRPORT_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"


//�����༭��
class AirportEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportEditPacket);
public:
	EDIT_TYPE m_edit_type;  //�༭���ͣ�����ɾ���ģ�
	AirportData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�̶���༭��
class FixpointEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FixpointEditPacket);
public:
	EDIT_TYPE m_edit_type;
	FixpointData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�ܵ��༭��
class RunwayEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RunwayEditPacket);
public:
	EDIT_TYPE m_edit_type;
	RunwayData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//��·�༭��
class RoadEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RoadEditPacket);
public:
	EDIT_TYPE m_edit_type;
	RoadData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};
//��̨�༭��
class TowerEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TowerEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Tower m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//ͣ��λ�༭��
class GateEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(GateEditPacket);
public:
	EDIT_TYPE m_edit_type;
	GateData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//����ģ�ͱ༭��
class AirportModelEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportModelEditPacket);
public:
	EDIT_TYPE m_edit_type;
	AirportModel m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�볡����༭��
class	SidEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SidEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Sid			 m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//��������༭��
class StarEditPacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(StarEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Star  m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//��༭��
class MacroEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MacroEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Macro  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//����༭��
class MacroGroupEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MacroGroupEditPacket);

public:
	EDIT_TYPE m_edit_type;
	MacroGroup  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//��������༭��
class StdapchEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(StdapchEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Stdapch  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};


//�ȴ�����༭��
class HoldEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(HoldEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Hold m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//���ɳ���༭��
class MissEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MissEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Miss m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  �ƹ���༭��
\details  
\author JZH
\date 2013/6/13
*/
class LightGroupEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightGroupEditPacket);

public:
	EDIT_TYPE m_edit_type;
	LightGroup m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//·�߱༭��
class RouteEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RouteEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Route m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  �Ʊ༭��
\details  
\author ZJ
\date 2013/7/13
*/
class LightEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Light m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

#endif