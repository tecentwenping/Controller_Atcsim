#pragma once
#include "serial_base.h"
#include "public/site_info.h"
#include "public/BaseTypeDefine/PublicTypeDefine.h"
#include "Serialization/wserialize.h"

class CMDPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CMDPacket);

public:
	ENUM_OBJ_TYPE m_type;
	int m_id;
	int m_iPoiltID;
	std::string  m_cmdString; 
	ENUM_EXECUTE_MODE m_eExeMode;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();

};

class ACK_CMDPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ACK_CMDPacket);
public:
	int m_iObjID;           //对象ID
	int m_iPoiltID;
	std::string  m_Errorinfo; 
	bool m_bSucceed;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

/** 
 \brief		报告包
 \details  
 \author    
 \date      2013-03-26
*/
class ReportPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ReportPacket);
	int m_iMovingObjID; //!<对象ID
	int m_iPilotID;//!<机长ID
	ENUM_REPORT_TYPE m_eReportType;//!报告类型
	string m_strReport; //!<报告内容
public:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBufffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//训练计划控制命令（拟取代SysCommand）
enum EPlanCtrlCmd
{
	CMD_EXERCISE_INVALLID = 0,
	CMD_CREATE_PLAN,	//训练计划创建
	CMD_START_PLAN,		//训练计划开始
	CMD_PAUSE_PLAN,		//训练计划暂停
	CMD_STOP_PLAN,		//训练计划结束
	CMD_SPEED_PLAN,		//训练计划加速
	CMD_DELETE_PLAN,	//训练计划删除
};

//训练计划控制命令包（教员席位使用，拟取代SysCommandPacket）
class EPlanCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EPlanCtrlCmdPacket);

public:
	EPlanCtrlCmd cmd;
	int speed;//几倍速(加速命令使用，其他命令忽略)
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//命令执行状态（公用）
enum CmdExcuteStatus
{
	STATUS_INVALLID = 0,
	STATUS_SUCCEED,		//执行成功
	STATUS_FAILED,		//执行失败
};

//训练计划控制命令执行状态回复包（服务端回复）
class AckExerciseCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckExerciseCtrlCmdPacket);

public:
	CmdExcuteStatus cmd;
	//std::string info;//附加信息（待定）
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//航空器控制命令
enum AcftCtrlCmd
{
	CMD_ACFT_INVALLID = 0,
	CMD_ACFT_HEADING,		//改变航向
	CMD_ACFT_SPEED,			//改变速度
	CMD_ACFT_LEVEL,			//改变高度
};

//航空器控制命令包（机长席位使用）
class AcftCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AcftCtrlCmdPacket);

public:
	AcftCtrlCmd cmd;
	std::string info;//附加信息（服务端进行命令解析）
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//航空器控制命令包执行状态回复包（服务端回复）
class AckAcftCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAcftCtrlCmdPacket);

public:
	CmdExcuteStatus cmd;
	//std::string info;//附加信息（待定）
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//! ATC失效包
class ATCInvalidPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ATCInvalidPacket);

public:
	bool bFDPInvalid;               ///< FDP是否失效
	bool bRDPInvalid;               ///< RDP是否失效

private:
	SERIALIZE_PACKET(bFDPInvalid & bRDPInvalid);
};

//////////////////////////////////////////////////////////////////////////
//! 监视传感器失效结构体
struct SurveillanceSensorsInvalidInfo
{
	std::string strSensorName;    ///< 传感器名称
	bool bIsInvalid;                ///< 是否失效
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, SurveillanceSensorsInvalidInfo& ud, const unsigned int version)
{
	return	ar & ud.strSensorName & ud.bIsInvalid;
}

//////////////////////////////////////////////////////////////////////////
//! 监视传感器失效包
class SurveillanceSensorsInvalidInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SurveillanceSensorsInvalidInfoPacket);

public:
	std::vector<SurveillanceSensorsInvalidInfo> m_Sensors;

private:
	SERIALIZE_PACKET(m_Sensors)
};
