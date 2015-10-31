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
	int m_iObjID;           //����ID
	int m_iPoiltID;
	std::string  m_Errorinfo; 
	bool m_bSucceed;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

/** 
 \brief		�����
 \details  
 \author    
 \date      2013-03-26
*/
class ReportPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ReportPacket);
	int m_iMovingObjID; //!<����ID
	int m_iPilotID;//!<����ID
	ENUM_REPORT_TYPE m_eReportType;//!��������
	string m_strReport; //!<��������
public:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBufffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//ѵ���ƻ����������ȡ��SysCommand��
enum EPlanCtrlCmd
{
	CMD_EXERCISE_INVALLID = 0,
	CMD_CREATE_PLAN,	//ѵ���ƻ�����
	CMD_START_PLAN,		//ѵ���ƻ���ʼ
	CMD_PAUSE_PLAN,		//ѵ���ƻ���ͣ
	CMD_STOP_PLAN,		//ѵ���ƻ�����
	CMD_SPEED_PLAN,		//ѵ���ƻ�����
	CMD_DELETE_PLAN,	//ѵ���ƻ�ɾ��
};

//ѵ���ƻ��������������Աϯλʹ�ã���ȡ��SysCommandPacket��
class EPlanCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(EPlanCtrlCmdPacket);

public:
	EPlanCtrlCmd cmd;
	int speed;//������(��������ʹ�ã������������)
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//����ִ��״̬�����ã�
enum CmdExcuteStatus
{
	STATUS_INVALLID = 0,
	STATUS_SUCCEED,		//ִ�гɹ�
	STATUS_FAILED,		//ִ��ʧ��
};

//ѵ���ƻ���������ִ��״̬�ظ���������˻ظ���
class AckExerciseCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckExerciseCtrlCmdPacket);

public:
	CmdExcuteStatus cmd;
	//std::string info;//������Ϣ��������
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//��������������
enum AcftCtrlCmd
{
	CMD_ACFT_INVALLID = 0,
	CMD_ACFT_HEADING,		//�ı亽��
	CMD_ACFT_SPEED,			//�ı��ٶ�
	CMD_ACFT_LEVEL,			//�ı�߶�
};

//���������������������ϯλʹ�ã�
class AcftCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AcftCtrlCmdPacket);

public:
	AcftCtrlCmd cmd;
	std::string info;//������Ϣ������˽������������
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//���������������ִ��״̬�ظ���������˻ظ���
class AckAcftCtrlCmdPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAcftCtrlCmdPacket);

public:
	CmdExcuteStatus cmd;
	//std::string info;//������Ϣ��������
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//////////////////////////////////////////////////////////////////////////
//! ATCʧЧ��
class ATCInvalidPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ATCInvalidPacket);

public:
	bool bFDPInvalid;               ///< FDP�Ƿ�ʧЧ
	bool bRDPInvalid;               ///< RDP�Ƿ�ʧЧ

private:
	SERIALIZE_PACKET(bFDPInvalid & bRDPInvalid);
};

//////////////////////////////////////////////////////////////////////////
//! ���Ӵ�����ʧЧ�ṹ��
struct SurveillanceSensorsInvalidInfo
{
	std::string strSensorName;    ///< ����������
	bool bIsInvalid;                ///< �Ƿ�ʧЧ
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, SurveillanceSensorsInvalidInfo& ud, const unsigned int version)
{
	return	ar & ud.strSensorName & ud.bIsInvalid;
}

//////////////////////////////////////////////////////////////////////////
//! ���Ӵ�����ʧЧ��
class SurveillanceSensorsInvalidInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SurveillanceSensorsInvalidInfoPacket);

public:
	std::vector<SurveillanceSensorsInvalidInfo> m_Sensors;

private:
	SERIALIZE_PACKET(m_Sensors)
};
