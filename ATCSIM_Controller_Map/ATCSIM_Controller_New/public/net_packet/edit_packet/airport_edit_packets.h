//此文件存放机场相关对象的编辑包，包括以下对象的编辑包

//对象                                        编辑包
//机场(AirportData)                        AirportEditPacket
//固定点(Fixpoint)                         FixpointEditPacket
//跑道(RunwayData)                         RunwayEditPacket
//道路(RoadData)                           RoadEditPacket

#ifndef _H_AIRPORT_EDIT_PACKETS_H
#define _H_AIRPORT_EDIT_PACKETS_H

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"


//机场编辑包
class AirportEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportEditPacket);
public:
	EDIT_TYPE m_edit_type;  //编辑类型（增、删、改）
	AirportData m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_data);
};

//固定点编辑包
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

//跑道编辑包
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

//道路编辑包
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
//塔台编辑包
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

//停机位编辑包
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

//机场模型编辑包
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

//离场程序编辑包
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

//进场程序编辑包
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

//宏编辑包
class MacroEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MacroEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Macro  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//宏组编辑包
class MacroGroupEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MacroGroupEditPacket);

public:
	EDIT_TYPE m_edit_type;
	MacroGroup  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//进近程序编辑包
class StdapchEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(StdapchEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Stdapch  m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};


//等待程序编辑包
class HoldEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(HoldEditPacket);

public:
	EDIT_TYPE m_edit_type;
	Hold m_data;

private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//复飞程序编辑包
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
\brief  灯光组编辑包
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

//路线编辑包
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
\brief  灯编辑包
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