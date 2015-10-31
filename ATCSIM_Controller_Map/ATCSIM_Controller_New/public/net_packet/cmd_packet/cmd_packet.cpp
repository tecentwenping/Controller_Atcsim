#include "cmd_packet.h"
#include <memory.h>


PKT_IMPLEMENT_DYNCREATE(CMDPacket);

void CMDPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_type,sizeof(ENUM_OBJ_TYPE));
	pTemp += sizeof(ENUM_OBJ_TYPE);
	memcpy(pTemp, &m_id, sizeof(int));
	pTemp += sizeof(int);
	memcpy(pTemp, &m_iPoiltID, sizeof(int));
	pTemp += sizeof(int);
	memcpy(pTemp, m_cmdString.c_str(),m_cmdString.size()+1);
	pTemp += m_cmdString.size()+1;
	memcpy(pTemp, &m_eExeMode, sizeof(ENUM_EXECUTE_MODE));
}

void CMDPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_type, pTemp, sizeof(ENUM_OBJ_TYPE));
	pTemp += sizeof(ENUM_OBJ_TYPE);
	memcpy(&m_id, pTemp, sizeof(int));
	pTemp += sizeof(int);
	memcpy(&m_iPoiltID, pTemp, sizeof(int));
	pTemp += sizeof(int);
	m_cmdString.assign(pTemp);
	pTemp += m_cmdString.size()+1;
	memcpy(&m_eExeMode, pTemp, sizeof(ENUM_EXECUTE_MODE));

}

int CMDPacket::GetBufferSize()
{
	return sizeof(ENUM_OBJ_TYPE) + sizeof(int)  + sizeof(int) + m_cmdString.size()+1 + sizeof(ENUM_EXECUTE_MODE);
}

PKT_IMPLEMENT_DYNCREATE(ACK_CMDPacket);

void ACK_CMDPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_iObjID,sizeof(m_iObjID));
	pTemp+=sizeof(m_iObjID);
	memcpy(pTemp,&m_iPoiltID,sizeof(m_iPoiltID));
	pTemp += sizeof(m_iPoiltID);
	memcpy(pTemp, m_Errorinfo.c_str(),m_Errorinfo.size()+1);
	pTemp += m_Errorinfo.size()+1;
	memcpy(pTemp, &m_bSucceed, sizeof(m_bSucceed));
	pTemp += sizeof(m_bSucceed);
}

void ACK_CMDPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iObjID,pBuffer,sizeof(m_iObjID));
	pTemp+=sizeof(m_iObjID);
	memcpy(&m_iPoiltID, pTemp, sizeof(m_iPoiltID));
	pTemp += sizeof(m_iPoiltID);
	m_Errorinfo.assign(pTemp);
	pTemp += m_Errorinfo.size()+1;
	memcpy(&m_bSucceed, pTemp, sizeof(m_bSucceed));
	pTemp += sizeof(m_bSucceed);
}

int ACK_CMDPacket::GetBufferSize()
{
	return sizeof(m_iObjID)+sizeof(m_iPoiltID) + sizeof(m_bSucceed) + m_Errorinfo.size()+1;
}

//////////////////////////////////////////////////////////////////////////
//训练计划控制命令包（拟取代SysCommandPacket）
PKT_IMPLEMENT_DYNCREATE(EPlanCtrlCmdPacket);

void EPlanCtrlCmdPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
	pTemp += sizeof(cmd);
	memcpy(pTemp, &speed, sizeof(speed));
	pTemp += sizeof(speed);
}

void EPlanCtrlCmdPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
	pTemp += sizeof(cmd);
	memcpy(&speed, pTemp, sizeof(speed));
	pTemp += sizeof(speed);
}

int EPlanCtrlCmdPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(cmd);
	size += sizeof(speed);
	return  size;
}

//////////////////////////////////////////////////////////////////////////
//训练计划控制命令执行状态回复包（服务端回复）
PKT_IMPLEMENT_DYNCREATE(AckExerciseCtrlCmdPacket);

void AckExerciseCtrlCmdPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
	pTemp += sizeof(cmd);
}

void AckExerciseCtrlCmdPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
	pTemp += sizeof(cmd);
}

int AckExerciseCtrlCmdPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(cmd);
	return  size;
}

//////////////////////////////////////////////////////////////////////////
//航空器控制命令包（机长席位使用）
PKT_IMPLEMENT_DYNCREATE(AcftCtrlCmdPacket);

void AcftCtrlCmdPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
	pTemp += sizeof(cmd);
	memcpy(pTemp, info.c_str(), info.size()+1);
	pTemp += info.size()+1;
}

void AcftCtrlCmdPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
	pTemp += sizeof(cmd);
	info.assign(pTemp);
}

int AcftCtrlCmdPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(cmd);
	size += info.size()+1;
	return  size;
}

//////////////////////////////////////////////////////////////////////////
//航空器控制命令包执行状态回复包（服务端回复）
PKT_IMPLEMENT_DYNCREATE(AckAcftCtrlCmdPacket);

void AckAcftCtrlCmdPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
	pTemp += sizeof(cmd);
}

void AckAcftCtrlCmdPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
	pTemp += sizeof(cmd);
}

int AckAcftCtrlCmdPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(cmd);
	return  size;
}

PKT_IMPLEMENT_DYNCREATE(ATCInvalidPacket);

PKT_IMPLEMENT_DYNCREATE(SurveillanceSensorsInvalidInfoPacket);

PKT_IMPLEMENT_DYNCREATE(ReportPacket);
void ReportPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_iMovingObjID,sizeof(m_iMovingObjID));
	pTemp += sizeof(m_iMovingObjID);
	memcpy(pTemp,&m_iPilotID,sizeof(m_iPilotID));
	pTemp += sizeof(m_iPilotID);
	memcpy(pTemp, &m_eReportType,sizeof(m_eReportType));
	pTemp += sizeof(m_eReportType);
	memcpy(pTemp, m_strReport.c_str(),m_strReport.size()+1);
	pTemp += m_strReport.size()+1;
}

void ReportPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iMovingObjID, pTemp, sizeof(m_iMovingObjID));
	pTemp += sizeof(m_iMovingObjID);
	memcpy(&m_iPilotID, pTemp, sizeof(m_iPilotID));
	pTemp += sizeof(m_iPilotID);
	memcpy(&m_eReportType, pTemp, sizeof(m_eReportType));
	pTemp += sizeof(m_eReportType);
	m_strReport.assign(pTemp);
	pTemp += m_strReport.size()+1;
}

int ReportPacket::GetBufferSize()
{
	return sizeof(m_iMovingObjID)+sizeof(m_iPilotID)+sizeof(m_eReportType)+m_strReport.size()+1;
}