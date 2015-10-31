#ifndef _FDPPAKCET_HEADER
#define  _FDPPAKCET_HEADER
//���ļ�����fdpģ���õ��İ�

#include "..\serial_base.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"
#include "public\BaseTypeDefine\FDPTypeDefine.h"

//�����ƽ���
class FlightPlanHandoverPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPlanHandoverPacket);
public:
    std::string m_strMid;       //��������Mid��
    ENUM_HANDOVER_TYPE m_eType; //�ƽ�����
	std::string m_operSector;   //�����������������
    std::string m_RecvSector;   //���ܵ���������
private:
	SERIALIZE_PACKET(m_strMid & m_eType & m_operSector & m_RecvSector);
};

//����Ա�ƽ��ɻ���
class ControllerTransferPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ControllerTransferPacket);
public:
	int m_PlaneID;       //��������Mid��
	std::string m_operSector;   //�����������������
	std::string m_RecvSector;   //���ܵ���������
	int m_opercontrollerID;                    //���չ���ԱID
	int m_RecvcontrollerID;                    //���չ���ԱID
private:
	SERIALIZE_PACKET(m_PlaneID & m_operSector & m_RecvSector & m_opercontrollerID & m_RecvcontrollerID);
};

//���������
class SectorAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorAisgnPacket);
public:
    std::vector<ContrlSectorMap> m_vContrlSec;      //����ϯ��������Ӧ
private:
	SERIALIZE_PACKET(m_vContrlSec);
};

//���������ʼ����
class InitSectorAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitSectorAisgnPacket);
public:
	std::vector<ContrlSectorMap> m_vContrlSec;      //����ϯ��������Ӧ
private:
	SERIALIZE_PACKET(m_vContrlSec);
};


//���������
class PilotAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PilotAisgnPacket);
public:
    std::vector<ContrlPilotMap>   m_vContrlPlt;       //����ϯ�����ϯ��Ӧ
private:
	SERIALIZE_PACKET(m_vContrlPlt);
};

//���������
class InitPilotAisgnPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitPilotAisgnPacket);
public:
	std::vector<ContrlPilotMap>   m_vContrlPlt;       //����ϯ�����ϯ��Ӧ
private:
	SERIALIZE_PACKET(m_vContrlPlt);
};

//�������Ʒɻ���ʼ����
class PilotHandlePlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PilotHandlePlanePacket);
public:
    std::vector<PilotPlaneMap> m_vPilotPlan;       //����ϯ��ɻ���Ӧ
private:
	SERIALIZE_PACKET(m_vPilotPlan);
};

//�������Ʒɻ���ʼ����
class SectorAisgnPlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorAisgnPlanePacket);
public:
	std::vector<SectorPlaneMap> m_vPilotPlan;       //����ϯ��ɻ���Ӧ
private:
	SERIALIZE_PACKET(m_vPilotPlan);
};

//���мƻ���
class FlightPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPlanPacket);
public:
    std::vector<ST_FDP_FLIGHTPLAN_STATIC>  m_vStaticFlightPlan;
    std::vector<ST_FDP_FLIGHTPLAN_DYNAMIC> m_vDynamicFlightPlan; //���µķ��мƻ�
public:
	SERIALIZE_PACKET(m_vStaticFlightPlan & m_vDynamicFlightPlan);
};

//����/�޸ķ��мƻ�
class ADDMODIFYFlightPlanPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(ADDMODIFYFlightPlanPacket);
public:
    ENUM_FLIGHTPLAN_OPERRTYPE m_OperType;
    ST_FDP_FLIGHTPLAN  m_FlightPlan;
public:
    SERIALIZE_PACKET(m_OperType & m_FlightPlan);
};

//��ɾ�����мƻ���
class FlightPlanDeletedPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(FlightPlanDeletedPacket);
public:
    std::vector<std::string> m_vDeletedMIDs; 
public:
    SERIALIZE_PACKET(m_vDeletedMIDs);
};

//���мƻ��ȴ�״̬��
class HoldFlightPlanPacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(HoldFlightPlanPacket);
public:
    std::string	m_strMID;
    ENUM_HOLD_TYPE	m_OperType;	//��ʼ�ȴ�/�����ȴ�
    std::string	m_HoldPoint;	//�ȴ��ص㣨����	
    std::string	m_ResumeTime;	//Ԥ���˳��ȴ�ʱ��0830
public:
    SERIALIZE_PACKET(m_strMID & m_OperType & m_HoldPoint & m_ResumeTime);
};

//���мƻ��ֶ����/ȥ���
class FlightPlanCouplePacket : public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(FlightPlanCouplePacket);
public:
    std::string	m_strMID;
    ENUM_COUPLE_INFO m_OperType; //���/ȥ���
    int m_trackNo;
public:
    SERIALIZE_PACKET(m_strMID & m_OperType & m_trackNo);
};

//����Ƽƻ�
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