#pragma once
#include "..\serial_base.h"
#include "site_info.h"
#include <string>
 
using namespace std;
//
///** 
// \brief		platfromʹ�õİ�
// \details   ��switch��center֮�䷢��Ex����
// \author    
// \date      2013-08-31
//*/
//class ExchangeConnectedPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ExchangeConnectedPacket);
//public:
//	int m_GroupID; 	// �����
//	std::string  m_GroupIP;			//����IP
//	short m_GroupPort;			//����port
//private:
//	SERIALIZE_PACKET(m_GroupID & m_GroupIP & m_GroupPort );
//};
//
///** 
// \brief		platfromʹ�õİ�
// \details   ��switch��center֮�䷢��ATG������Ex
// \author    
// \date      2013-08-31
//*/
//class ATGConnectedExPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ATGConnectedExPacket);
//public:
//	int m_GroupID; 	// �����
//	int m_ATGID; 	// ATG��
//private:
//	SERIALIZE_PACKET(m_GroupID & m_ATGID);
//};
//
///** 
// \brief		platfromʹ�õİ�
// \details   ��switch��center֮�䷢��Ex������DB
// \author    
// \date      2013-08-31
//*/
//class ExConnectedDBPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ExConnectedDBPacket);
//public:
//	int m_GroupID; 	// �����
//private:
//	SERIALIZE_PACKET(m_GroupID);
//};
//
///** 
// \brief		platfromʹ�õİ�
// \details   ��switch��center֮�䷢�͸�ϯλ������switch
// \author    
// \date      2013-08-31
//*/
//class PositionConnectedSwitchPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(PositionConnectedSwitchPacket);
//public:
//	site_info  m_site_info; 
//private:
//	SERIALIZE_PACKET(m_site_info);
//};
//
///** 
// \brief		platfromʹ�õİ�
// \details   ��switch��center֮�䷢�͸�ϯλ״̬�ı�
// \author    
// \date      2013-08-31
//*/
//enum POSITIONSTATUS
//{
//	INVALID_STATUS = 0,
//	FREE_STATUS = 1,
//	BUSY_STATUS = 2,
//};
//class PositionStatusChangePacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(PositionStatusChangePacket);
//public:
//	site_info  m_site_info; 
//	POSITIONSTATUS m_Status;
//private:
//	SERIALIZE_PACKET(m_site_info & m_Status);
//};

/** 
 \brief		���������IP��Port��Ϣ��
 \details   Switch--->����ExServer��ϯλ
 \author    
 \date      2013-08-31
*/
class ExServerIPPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ExServerIPPacket);

public:
	site_info m_ex_info;
	std::string m_IP;
	short m_Port;
private:
	SERIALIZE_PACKET(m_ex_info & m_IP & m_Port);
	
};

/** 
 \brief		���ݷ����IP��Port��Ϣ��
 \details   Switch--->����DataServer��ϯλ
 \author    
 \date      2013-08-31
*/
class DataServiceIPPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(DataServiceIPPacket);
public:
	std::string m_IP;
	short m_Port;
private:
	SERIALIZE_PACKET(m_IP & m_Port);
};

/** 
 \brief		֪ͨ����ϯλ�Ͽ���ExServer������
 \details   ��ϯλ���ϳ�����ʱ��Switch--->����ϯλ
 \author    
 \date      2013-08-31
*/
class GroupDisConnectPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(GroupDisConnectPacket);

public:
	site_info  m_site_info; 
private:
	SERIALIZE_PACKET(m_site_info);
};

//////////////////////////////////////////////////////////////////////////
enum ENUM_OPERATE_TYPE
{
	OT_ADD_IN_GROUP,		//!<�������
	OT_RELEASE_FROM_GROUP,	//!<�˳�����
};
/** 
 \brief		�������
 \details   Center���з��������Center--->Switch
 \author    
 \date      2013-08-13
*/
class PositionOperatePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionOperatePacket);

public:
	site_info m_ex_info;		//!<��������ϯλ��Ϣ
	site_info m_pos_info;		//!<����/�˳������ϯλ��Ϣ
	ENUM_OPERATE_TYPE m_eType;	//!<��������
private:
	SERIALIZE_PACKET(m_ex_info & m_pos_info & m_eType);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief		ϯλ����/�˳�����
 \details   ��ϯλ����/�˳����飬֪ͨ����ATG��ExServer--->����ATG
 \author    
 \date      2013-09-23
*/
class PositionConnectedPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionConnectedPacket);

public:
	site_info m_pos_info;		//!<����/�˳������ϯλ��Ϣ
	ENUM_OPERATE_TYPE m_eType;	//!<��������
private:
	SERIALIZE_PACKET(m_pos_info & m_eType);
};

//////////////////////////////////////////////////////////////////////////
enum ENUM_ATC_SERVICE_STATUS
{
	SS_INVALID_STATUS,				//!<��ʼ״̬
	SS_SERVICE_INITIALIZING,		//!<���ķ����ʼ����
	SS_SERVICE_INIT_FAILED,			//!<���ķ����ʼ��ʧ��
	SS_SERVICE_INIT_SUCCEED,		//!<���ķ����ʼ���ɹ�
};

/** 
 \brief		���ķ���״̬��
 \details   ���ķ���״̬�ı�ʱ����
			���ķ���--->ExServer
 \author    @lijin
 \date      2013-08-09
*/
class ServiceStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ServiceStatusPacket);

public:
	site_info  m_site_info;						//!<����ϯλ��Ϣ
	ENUM_ATC_SERVICE_STATUS m_eServiceStaus;	//!<���ķ���״̬��Ϣ
private:
	SERIALIZE_PACKET(m_site_info & m_eServiceStaus);	
};

//////////////////////////////////////////////////////////////////////////
enum ENUM_DATASERVER_STATUS
{
	DS_INVALID_STATUS,				//!<��ʼ״̬
	DS_CONNECT_DATABASE_FAILED,		//!<DataServer�������ݿ�ʧ��
	DS_CONNECT_DATABASE_SUCCEED,	//!<DataServer�������ݿ�ɹ�
	DS_DATASERVER_INITIALIZING,		//!<DataServer��ʼ����
	DS_DATASERVER_INIT_FAILED,		//!<DataServer��ʼ��ʧ��
	DS_DATASERVER_INIT_SUCCEED,		//!<DataServer��ʼ���ɹ�
};

/** 
 \brief		DataServer״̬��
 \details   DataServer״̬�ı�ʱ����
			DataServer--->ExServer
 \author    @lijin
 \date      2013-08-08
*/
class DataServerStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(DataServerStatusPacket);

public:
	ENUM_DATASERVER_STATUS m_eDataServerStaus;	//!<DataServer״̬��Ϣ
private:
	SERIALIZE_PACKET(m_eDataServerStaus);	
};
//
///** 
// \brief		��ʧЧ��
// \details   ATG,DB��ʧЧ����ߺ�����Ϊ�����ã�������Ϣ��center
// \author    
// \date      2013-08-05
//*/
//enum UNAVAILABLEREASON
//{
//	INVALID_REASON = 0,
//	ATG_UNAVAILABLE = 1,
//	DB_UNAVAILABLE = 2,
//};
//
//class GroupUnavailablePacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(GroupUnavailablePacket);
//
//public:
//	site_info  m_site_info;	//!<ϯλ��Ϣ
//	UNAVAILABLEREASON m_Reason;			//!<true����ʼ����ɣ�false����ʼ��δ���
//private:
//	SERIALIZE_PACKET(m_site_info & m_Reason);
//};

//////////////////////////////////////////////////////////////////////////
enum ENUM_GROUP_STATUS
{
	GS_INVALID_STATUS,			//!<��ʼ״̬
	GS_GROUP_CREATING,			//!<�鴴���У����������ķ�����������ExServer����ExServer��������DataServer����DataServer���ڳ�ʼ����
	GS_GROUP_CREATED_FAILED,	//!<�鴴��ʧ��
	GS_GROUP_CREATED_SUCCEED,	//!<�鴴���ɹ������������ķ���������ExServer����ExServer������DataServer����DataServer��ʼ���ɹ���
	GS_GROUP_DESTROYED,			//!<�������٣�ʧЧ��
	GS_EXERCISE_LOADING,		//!<ѵ���ƻ������У����������ķ����ʼ���У�
	GS_EXERCISE_LOAD_FAILED,	//!<ѵ���ƻ�����ʧ��
	GS_EXERCISE_LOAD_SUCCEED,	//!<ѵ���ƻ����سɹ������������ķ����ʼ���ɹ���
	GS_EXERCISE_RUNNING,		//!<ѵ���ƻ���������
	GS_EXERCISE_PAUSE,			//!<ѵ���ƻ���ͣ
	GS_EXERCISE_STOP,			//!<ѵ���ƻ�ֹͣ
};

inline std::string GetGoupStatusName(int group_status)
{
	switch (group_status)
	{
	case GS_INVALID_STATUS:				return "GS_INVALID_STATUS";
	case GS_GROUP_CREATING:				return "GS_GROUP_CREATING";
	case GS_GROUP_CREATED_FAILED:		return "GS_GROUP_CREATED_FAILED";
	case GS_GROUP_CREATED_SUCCEED:		return "GS_GROUP_CREATED_SUCCEED";
	case GS_GROUP_DESTROYED:			return "GS_GROUP_DESTROYED";
	case GS_EXERCISE_LOADING:			return "GS_EXERCISE_LOADING";
	case GS_EXERCISE_LOAD_FAILED:		return "GS_EXERCISE_LOAD_FAILED";
	case GS_EXERCISE_LOAD_SUCCEED:		return "GS_EXERCISE_LOAD_SUCCEED";
	case GS_EXERCISE_RUNNING:			return "GS_EXERCISE_RUNNING";
	case GS_EXERCISE_PAUSE:				return "GS_EXERCISE_PAUSE";
	case GS_EXERCISE_STOP:				return "GS_EXERCISE_STOP";
	default:					return "-";
	}
}
/** 
 \brief ��״̬��Ϣ�� 
\details   ����ϯλ��Exercise��Ϣ���и�����ʾ(״̬�仯��ŷ���)
        ExServer ----> Center/Coach
\author
\date      2013-08-06
*/
class GroupStatusInfoPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(GroupStatusInfoPacket);

public:
	site_info m_ex_info;					//!<���齻������ϯλ��Ϣ
	ENUM_GROUP_STATUS m_eGroupStatus;		//!<����״̬
	int m_nAirportID;						//!<����ID����ʼ��Ϊ-1��
	int m_nExerciseID;						//!<ѵ���ƻ�ID����ʼ��Ϊ-1��
	std::string m_strInfo;					//!<������Ϣ����ѵ���ƻ�����ʧ��ԭ��ȣ�
private:
   SERIALIZE_PACKET(m_ex_info & m_eGroupStatus & m_nAirportID & m_nExerciseID & m_strInfo);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief ������Ϣ�� 
\details   ��������ش�����Ϣ
        ExServer ----> Center/Coach/Switch
\author
\date      2013-08-09
*/
class ErrorInfoPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(ErrorInfoPacket);

public:
	site_info m_site_info;					//!<����ϯλ��Ϣ
	ENUM_GROUP_STATUS m_eGroupStatus;		//!<����״̬������ִ��ʧ��ʱ������״̬���أ�
	std::string m_strInfo;					//!<������Ϣ������ִ�д����統ǰ״̬���ܷ��顢��ǰ״̬����ִ�и����
private:
   SERIALIZE_PACKET(m_site_info & m_eGroupStatus & m_strInfo);
};

//////////////////////////////////////////////////////////////////////////
//enum ENUM_EXERCISE_STATUS
//{
//	ES_INVALID_STATUS,			//!<��ʼ״̬
//	ES_EXERCISE_LOADING,		//!<ѵ���ƻ������У����������ķ����ʼ���У�
//	ES_EXERCISE_LOAD_SUCCEED,	//!<ѵ���ƻ����سɹ������������ķ����ʼ���ɹ���
//	ES_EXERCISE_LOAD_FAILED,	//!<ѵ���ƻ�����ʧ��
//	ES_EXERCISE_RUNNING,		//!<ѵ���ƻ���������
//	ES_EXERCISE_PAUSE,			//!<ѵ���ƻ���ͣ
//	ES_EXERCISE_STOP,			//!<ѵ���ƻ�ֹͣ
//};
//
///** 
// \brief ѵ���ƻ�״̬��Ϣ�� 
//\details   ����ϯλ��Exercise��Ϣ���и�����ʾ(״̬�仯��ŷ���)
//        ExServer ----> Center/Coach
//\author
//\date      2013-08-06
//*/
//class ExerciseStatusInfoPacket : public CSerial_Base
//{
//   PKT_DECLARE_DYNCREATE(ExerciseStatusInfoPacket);
//
//public:
//	site_info m_site_info;					//!<ϯλ��Ϣ
//	ENUM_EXERCISE_STATUS m_eExerciseStatus;	//!<ѵ���ƻ�״̬
//	std::string m_strInfo;					//!<������Ϣ����ѵ���ƻ�����ʧ��ԭ��ȣ�
//private:
//   SERIALIZE_PACKET(m_eExerciseStatus & m_strInfo);
//};

//////////////////////////////////////////////////////////////////////////
enum ENUM_CONNECTED_TYPE
{
	CT_CONNECTED_SWITCH,		//!<���ӽ������
	CT_DISCONNECTED_SWITCH,		//!<�Ͽ��������
	CT_CONNECTED_EXSERVER,		//!<���ӽ�������
	CT_DISCONNECTED_EXSERVER,	//!<�Ͽ���������
};
/** 
 \brief ����ϯλ������Ϣ�� 
 \details   ��Ҫ����Switch���͸�Coach/Center����ÿ���ͻ������ӵ�״̬��Ϣ
		���ĳ���ͻ��˶Ͽ������˻������ӵ���Switch�ˣ�Ӧ��֪ͨCoach/Center�Խ�����и���
        Switch ----> Coach/Center
\author
\date      2013-08-06
*/
class PositionStatusInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionStatusInfoPacket);

public:
	site_info m_site_info;					//!<ϯλ��Ϣ�����ӻ�Ͽ���ϯλ��Ϣ��
	ENUM_CONNECTED_TYPE m_eConnectedType;	//!<����״̬
	int m_nExServerID;						//!<���ڷ����ID����δ������飬��IDΪ-1
private:
	SERIALIZE_PACKET(m_site_info & m_eConnectedType & m_nExServerID);
};

/** 
 \brief ������״̬��Ϣ�� 
 \details   ������/�ͻ���ϯλ����������ʱ�����Լ��ĵ�ǰ״̬
		��������Switchʱ���״����ӻ���Switch�Ͽ����������������ӣ����������ǰ��״̬
        ATG/ExServer/Controller/Pilot/Supervisor/VisServer ----> Switch
\author
\date      2013-10-10
*/
class InitStatusInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitStatusInfoPacket);

public:
	site_info m_site_info;					//!<ϯλ��Ϣ
	bool m_bAddedIntoGroup;					//!<�Ƿ��Ѽ������
	int m_nExServerID;						//!<���ڷ����ID����δ������飬��IDΪ-1
private:
	SERIALIZE_PACKET(m_site_info & m_bAddedIntoGroup & m_nExServerID);
};


/** 
 \brief   ����Ա�����Ƶ�Ԫ����������Ӧ��ϵ���°�
\details   ���ڹ���Ա���г�ʼ���Ƶ�Ԫ���������������
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class RadarControlUnitRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarControlUnitRelationsPacket);

public:
	std::map<int, std::vector<std::string> > m_rsRelations; //!<�״����id�������Ƶ�Ԫ����������Ӧ��ϵ: �ⲿ����Ϣ��������Center��Coach��������

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   ����Ա��������Ӧ��ϵ�����Լ����°�
\details   Center/Coach ---> Exchange (--->ATG, Coach/Center)
        Coach/Center�������ڽ�����ʾ��ϵ��ATG�������ڷ��͸����������еĹ���Ȩ�ޣ�Ӱ������Էɻ��Ŀ���Ȩ�ޣ�
\author    @hsb
\date      2013/08/06
*/

class RadarPilotRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarPilotRelationsPacket);
public:
   std::map<int, std::vector<int> > m_rpRelations; //!<����Ա������id)������������id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_rpRelations);

};

/** 
\brief   ����Ա��������Ӧ��ϵ�������ڱ��ݣ�
\details   Exchange ---> Coach/Center
		����Coach/Center�����󣬽�����ʾ��ϵ
\author    @lijin
\date      2013/09/22
*/

class BackRadarPilotRelationsPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(BackRadarPilotRelationsPacket);
public:
	int m_nExServerID;								//!<���ڷ����ID
	std::map<int, std::vector<int> > m_rpRelations; //!<����Ա������id)������������id����Ӧ��ϵ��
private:
	SERIALIZE_PACKET(m_nExServerID & m_rpRelations);
};

/** 
 \brief   �ɻ������Ƶ�Ԫ����������Ӧ��ϵ���°�
\details   �����ݿ��ṩ�����ɻ���Ӧ
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightControlUnitRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightControlUnitRelationsPacket);
public:
	std::map<std::string, std::vector<int> > m_sfRelations; //!<���Ƶ�Ԫ(����)���ɻ���id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_sfRelations);
};
/** 
 \brief   �ɻ���������Ӧ��ϵ��
\details   ������������ɸ�������������Ա���������߹�ϵ�ṩ�����ɻ���Ӧ
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightPilotRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightPilotRelationsPacket);
public:
   std::map<int, std::vector<int> > m_pfRelations; //!<����������id)���ɻ���id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_pfRelations);
};


/** 
 \brief   �����ƽ���
\details   ����ͬһ����Ա�µĻ������зɻ��ƽ�
        poilt ---> Exchange --->ATG--->polit
\author    @hsb
\date      2013/09/23
*/
class FlightPilotTransferPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPilotTransferPacket);
public:
	int m_iFlightId;		//!< �ƽ��ɻ�id
	int m_iSourcePilotId;	//!< �ƽ�Դ����id
	int m_iTargetPilotId;	//!< �ƽ�Ŀ�����id
private:
	SERIALIZE_PACKET(m_iFlightId&m_iSourcePilotId&m_iTargetPilotId);
};

/** 
 \brief   ����Ա�����Ƶ�Ԫ����������Ӧ��ϵ���°�
\details   ���ڹ���Ա���г�ʼ���Ƶ�Ԫ���������������
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class RadarControlUnitRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarControlUnitRelationsUpdatePacket);

public:
	std::map<int, std::vector<std::string> > m_rsRelations; //!<�״����id�������Ƶ�Ԫ����������Ӧ��ϵ: �ⲿ����Ϣ��������Center��Coach��������

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   �ɻ������Ƶ�Ԫ����������Ӧ��ϵ���°�
\details   �����ݿ��ṩ�����ɻ���Ӧ
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightControlUnitRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightControlUnitRelationsUpdatePacket);
public:
	std::map<std::string, std::vector<int> > m_sfRelations; //!<���Ƶ�Ԫ(����)���ɻ���id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_sfRelations);
};
/** 
 \brief   �ɻ���������Ӧ��ϵ��
\details   ������������ɸ�������������Ա���������߹�ϵ�ṩ�����ɻ���Ӧ
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightPilotRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightPilotRelationsUpdatePacket);
public:
   std::map<int, std::vector<int> > m_pfRelations; //!<����������id)���ɻ���id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_pfRelations);
};
////////////////////////////////////////////////////////////////////
/** 
 \brief   ����Ա��������Ӧ��ϵ���°�
\details   ���ڹ���Ա���г�ʼ�����������
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @zcw
\date      2013/08/06
*/
class RadarSectorRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarSectorRelationsUpdatePacket);

public:
   std::map<int, std::set<int> > m_rsRelations; //!<�״����id����������Ӧ��ϵ: �ⲿ����Ϣ��������Center��Coach��������

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   ����Ա��������Ӧ��ϵ�����Լ����°�
\details   Center/Coach ---> Exchange (--->ATG, Coach/Center)
        Coach/Center�������ڽ�����ʾ��ϵ��ATG�������ڷ��͸����������еĹ���Ȩ�ޣ�Ӱ������Էɻ��Ŀ���Ȩ�ޣ�
\author    @zcw
\date      2013/08/06
*/

class RadarPilotRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarPilotRelationsUpdatePacket);
public:
   std::map<int, std::vector<int> > m_rpRelations; //!<����Ա������id)������������id����Ӧ��ϵ��
private:
   SERIALIZE_PACKET(m_rpRelations);

};

/** 
 \brief		��������й���Ա��������Ӧ��ϵ��
 \details   
 \author    @JB 
 \date      2013-10-9
*/
class RequestGroupRPInfos : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RequestGroupRPInfos);
public:
	int m_nExServerID;		
private:
	SERIALIZE_PACKET(m_nExServerID);
};


/** 
\brief		��Աϯλ������ϯλ���͵��ʼ���Ϣ��
\details   
\author    @yyg
\date      2013-10-9
*/
/////////////////////////////////////////////////////////////////////////////
class CoachSendMailInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CoachSendMailInfoPacket);
public:
	std::string m_sMailInfo;		
private:
	SERIALIZE_PACKET(m_sMailInfo);

};