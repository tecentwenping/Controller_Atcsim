#ifndef _FDPPAKCET_HEADER
#define  _FDPPAKCET_HEADER
//该文件定义fdp模块用到的包

#include "..\serial_base.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"
#include "public\BaseTypeDefine\FDPTypeDefine.h"

//管制移交包
class FlightPlanHandoverPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPlanHandoverPacket);
public:
    std::string m_strMid;       //操作对象Mid名
    ENUM_HANDOVER_TYPE m_eType; //移交类型
	std::string m_operSector;   //发出命令的物理扇区
    std::string m_RecvSector;   //接受的物理扇区
private:
	SERIALIZE_PACKET(m_strMid & m_eType & m_operSector & m_RecvSector);
};

//管制员移交飞机包
class ControllerTransferPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ControllerTransferPacket);
public:
	int m_PlaneID;       //操作对象Mid名
	std::string m_operSector;   //发出命令的物理扇区
	std::string m_RecvSector;   //接受的物理扇区
	int m_opercontrollerID;                    //接收管制员ID
	int m_RecvcontrollerID;                    //接收管制员ID
private:
	SERIALIZE_PACKET(m_PlaneID & m_operSector & m_RecvSector & m_opercontrollerID & m_RecvcontrollerID);
};

//扇区分配包
class SectorAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorAisgnPacket);
public:
    std::vector<ContrlSectorMap> m_vContrlSec;      //管制席与扇区对应
private:
	SERIALIZE_PACKET(m_vContrlSec);
};

//扇区分配初始化包
class InitSectorAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitSectorAisgnPacket);
public:
	std::vector<ContrlSectorMap> m_vContrlSec;      //管制席与扇区对应
private:
	SERIALIZE_PACKET(m_vContrlSec);
};


//机长分配包
class PilotAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PilotAisgnPacket);
public:
    std::vector<ContrlPilotMap>   m_vContrlPlt;       //管制席与机长席对应
private:
	SERIALIZE_PACKET(m_vContrlPlt);
};

//机长分配包
class InitPilotAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitPilotAisgnPacket);
public:
	std::vector<ContrlPilotMap>   m_vContrlPlt;       //管制席与机长席对应
private:
	SERIALIZE_PACKET(m_vContrlPlt);
};

//机长管制飞机初始化包
class PilotHandlePlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PilotHandlePlanePacket);
public:
    std::vector<PilotPlaneMap> m_vPilotPlan;       //机长席与飞机对应
private:
	SERIALIZE_PACKET(m_vPilotPlan);
};

//机长管制飞机初始化包
class SectorAisgnPlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorAisgnPlanePacket);
public:
	std::vector<SectorPlaneMap> m_vPilotPlan;       //机长席与飞机对应
private:
	SERIALIZE_PACKET(m_vPilotPlan);
};

//飞行计划包
class FlightPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPlanPacket);
public:
    std::vector<ST_FDP_FLIGHTPLAN_STATIC>  m_vStaticFlightPlan;
    std::vector<ST_FDP_FLIGHTPLAN_DYNAMIC> m_vDynamicFlightPlan; //更新的飞行计划
public:
	SERIALIZE_PACKET(m_vStaticFlightPlan & m_vDynamicFlightPlan);
};

//增加/修改飞行计划
class ADDMODIFYFlightPlanPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(ADDMODIFYFlightPlanPacket);
public:
    ENUM_FLIGHTPLAN_OPERRTYPE m_OperType;
    ST_FDP_FLIGHTPLAN  m_FlightPlan;
public:
    SERIALIZE_PACKET(m_OperType & m_FlightPlan);
};

//已删除飞行计划包
class FlightPlanDeletedPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(FlightPlanDeletedPacket);
public:
    std::vector<std::string> m_vDeletedMIDs; 
public:
    SERIALIZE_PACKET(m_vDeletedMIDs);
};

//飞行计划等待状态包
class HoldFlightPlanPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(HoldFlightPlanPacket);
public:
    std::string	m_strMID;
    ENUM_HOLD_TYPE	m_OperType;	//开始等待/结束等待
    std::string	m_HoldPoint;	//等待地点（空域）	
    std::string	m_ResumeTime;	//预计退出等待时刻0830
public:
    SERIALIZE_PACKET(m_strMID & m_OperType & m_HoldPoint & m_ResumeTime);
};

//飞行计划手动相关/去相关
class FlightPlanCouplePacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(FlightPlanCouplePacket);
public:
    std::string	m_strMID;
    ENUM_COUPLE_INFO m_OperType; //相关/去相关
    int m_trackNo;
public:
    SERIALIZE_PACKET(m_strMID & m_OperType & m_trackNo);
};

//简标牌计划
class TagFlightPlanPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(TagFlightPlanPacket);
public:
    int m_trackNo;
    ENUM_TAG_TYPE m_OperType;
    std::string m_ACID;
    std::string m_ASSR;
    int m_iCFL;
    std::string m_opData;
    std::string m_CSEC;
public:
    SERIALIZE_PACKET(m_trackNo & m_OperType & m_ACID & m_ASSR & m_iCFL 
        & m_opData & m_CSEC);
};

class FlightPlanCFLPacket :  public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(FlightPlanCFLPacket);
public:
    std::string	m_strMID;
    int m_iCFL;
public:
    SERIALIZE_PACKET(m_strMID & m_iCFL);
};
#endif