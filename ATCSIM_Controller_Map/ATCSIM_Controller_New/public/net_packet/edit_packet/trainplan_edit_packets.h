//���ļ����ѵ���ƻ���ض���ı༭�����������¶���ı༭��

//����                                               �༭��
//ѵ���ƻ�(TrainPlanData)                        TrainPlanDataEditPacket
//���мƻ�(FlyPlanData)                          FlyPlanDataEditPacket

#ifndef _H_TRAINPLAN_EDIT_PACKETS_H
#define _H_TRAINPLAN_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"

//ѵ���ƻ���Ϣ�༭��
class TrainPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	TrainPlan m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

class ObjPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ObjPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	ObjPlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};
//�ɻ�Ŀ����Ϣ�༭��

//���мƻ���Ϣ�༭��
class TPFlyPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TPFlyPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	TPFlyPlan m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�Ƽƻ���Ϣ�༭��
class CloudPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CloudPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	CloudPlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�̼ƻ���Ϣ�༭��
class SmokePlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SmokePlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	SmokePlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�����ƻ���Ϣ�༭��
class VehiclePlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(VehiclePlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	VehiclePlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//��Ч�˶�����ƻ��༭��
class SpecialEffectObjPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SpecialEffectObjPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	SpecialEffectObjPlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};


//�����������ݽṹ����ǰ�����ṩ�������ݵ�
//ѵ���ƻ���Ϣ�༭��
class TrainPlanDataEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanDataEditPacket);
public:
	EDIT_TYPE m_edit_type;
	TrainPlanData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//���мƻ���Ϣ�༭��
class FlyPlanDataEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlyPlanDataEditPacket);
public:
	EDIT_TYPE m_edit_type;
	FlyPlanData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

class EnvPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EnvPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	EnvPlan m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

class EnvObjectPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EnvObjectPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	EnvObjectPlan m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};
#endif