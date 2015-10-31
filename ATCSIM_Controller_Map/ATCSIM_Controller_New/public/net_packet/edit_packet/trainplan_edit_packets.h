//此文件存放训练计划相关对象的编辑包，包括以下对象的编辑包

//对象                                               编辑包
//训练计划(TrainPlanData)                        TrainPlanDataEditPacket
//飞行计划(FlyPlanData)                          FlyPlanDataEditPacket

#ifndef _H_TRAINPLAN_EDIT_PACKETS_H
#define _H_TRAINPLAN_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"

//训练计划信息编辑包
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
//飞机目标信息编辑包

//飞行计划信息编辑包
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

//云计划信息编辑包
class CloudPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CloudPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	CloudPlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//烟计划信息编辑包
class SmokePlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SmokePlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	SmokePlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//车辆计划信息编辑包
class VehiclePlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(VehiclePlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	VehiclePlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//特效运动物体计划编辑包
class SpecialEffectObjPlanEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SpecialEffectObjPlanEditPacket);
public:
	EDIT_TYPE m_edit_type;
	SpecialEffectObjPlan m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};


//下面两个数据结构是以前用于提供测试数据的
//训练计划信息编辑包
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

//飞行计划信息编辑包
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