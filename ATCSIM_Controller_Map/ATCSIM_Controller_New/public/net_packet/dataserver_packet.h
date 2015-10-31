#ifndef _DATASERVER_PACKET_H_
#define _DATASERVER_PACKET_H_

#include "serial_base.h"
#include <string>
#include <vector>
#include "public/site_info.h"
#include "DataObj/dataobjs.h"
#include "edit_packet/edit_type.h"

//假定限定字符串最长50个字符
static const int MAX_NAME_NUM = 50;

enum DATA_KEY_TYPE
{
	DATA_KEY_NONE = 0,
	DATE_KEY_SINGLE_AIRCRAFT,
	DATE_KEY_SINGLE_TRAINPLAN,
	DATE_KEY_SINGLE_FLYPLAN,
	DATE_KEY_ALL_AIRCRAFT,
	DATE_KEY_ALL_TRAINPLAN,
	DATE_KEY_ALL_FLYPLAN
};

struct FlyPlanKey
{
	/*int itrainplan_id;*/
	char trainplan_name[MAX_NAME_NUM];
	char flyplan_name[MAX_NAME_NUM];
};

struct DataKey
{
	DATA_KEY_TYPE type;
	union
	{
		char single_aircraft_key[MAX_NAME_NUM];
		char single_trainplan_key[MAX_NAME_NUM];
		FlyPlanKey single_flyplan_key;
		char all_aircraft_key[MAX_NAME_NUM];
		char all_trainplan_key[MAX_NAME_NUM];
		char all_flyplan_key[MAX_NAME_NUM];
	}key;
};

struct FlyPlanKeyID
{
	/*int itrainplan_id;*/
	int trainplan_id;
	int flyplan_id;
};

struct DataKeyID
{
	DATA_KEY_TYPE type;
	union
	{
		int single_aircraft_key;
		int single_trainplan_key;
		FlyPlanKeyID single_flyplan_key;
		int all_aircraft_key;
		int all_trainplan_key;
		int all_flyplan_key;
	}key;
};

////编辑类型
//enum EDIT_TYPE
//{
//	EDIT_TYPE_NONE = 0,
//	EDIT_TYPE_INSERT,
//	EDIT_TYPE_MODIFY,
//	EDIT_TYPE_DELETE
//};


/*------------------------发包------------------------ */

//发包：初始化包
class InitializePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitializePacket);
public:
	site_info  m_site_info;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//发包：获得单条/全部记录的包，根据名字
class KeyDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(KeyDataPacket);
public:
	DataKey  m_DataKey;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//发包：获得单条/全部记录的包，根据ID
class KeyDataIDPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(KeyDataIDPacket);
public:
	DataKeyID  m_DataKeyID;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

////发包：机型信息编辑包
//class AircraftDataEditPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(AircraftDataEditPacket);
//public:
//	EDIT_TYPE m_edit_type;
//	AircraftData m_AircraftData;
//private:
//	virtual void ReadFromBuffer(const char* pBuffer);
//	virtual void WriteToBuffer(char* pBuffer);
//	virtual int GetBufferSize();
//};
//
////发包：训练计划信息编辑包
//class TrainPlanDataEditPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(TrainPlanDataEditPacket);
//public:
//	EDIT_TYPE m_edit_type;
//	TrainPlanData m_TrainPlanData;
//private:
//	virtual void ReadFromBuffer(const char* pBuffer);
//	virtual void WriteToBuffer(char* pBuffer);
//	virtual int GetBufferSize();
//};
//
////发包：飞机计划信息编辑包
//class FlyPlanDataEditPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(FlyPlanDataEditPacket);
//public:
//	EDIT_TYPE m_edit_type;
//	FlyPlanData m_FlyPlanData;
//private:
//	virtual void ReadFromBuffer(const char* pBuffer);
//	virtual void WriteToBuffer(char* pBuffer);
//	virtual int GetBufferSize();
//};

/*-----------------------回复包----------------------*/

//回复包：数据库席位初始化化回复包
class AckInitializePacket_Exer : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckInitializePacket_Exer);
public:
	std::vector<std::string> m_vecAllTrainPlanName;
	std::vector<std::string> m_vecAllAircraftName;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：单条机型信息
class AckKeyDataPacket_SingleAircraft : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_SingleAircraft);
public:
	AircraftData  m_AircraftData;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：全部机型信息
class AckKeyDataPacket_AllAircraft : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_AllAircraft);
public:
	std::vector<AircraftData>  m_vAircraftData;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：单条训练计划信息
class AckKeyDataPacket_SingleTrainPlan : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_SingleTrainPlan);
public:
	TrainPlanData  m_TrainPlanData;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：全部训练计划信息
class AckKeyDataPacket_AllTrainPlan : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_AllTrainPlan);
public:
	std::vector<TrainPlanData>  m_vTrainPlanData;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：单条飞行计划信息
class AckKeyDataPacket_SingleFlyPlan : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_SingleFlyPlan);
public:
	FlyPlanData  m_FlyPlanData;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//回复包：全部飞行计划信息
class AckKeyDataPacket_AllFlyPlan : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckKeyDataPacket_AllFlyPlan);
public:
	std::vector<FlyPlanData> m_vFlyPlanData; /* 所有飞行计划 */
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

////回复包：回复编辑包
//class AckDataEditPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(AckDataEditPacket);
//public:
//	EDIT_TYPE m_edit_type;
//	bool m_bSuccessed;
//private:
//	virtual void ReadFromBuffer(const char* pBuffer);
//	virtual void WriteToBuffer(char* pBuffer);
//	virtual int GetBufferSize();
//};


#endif
