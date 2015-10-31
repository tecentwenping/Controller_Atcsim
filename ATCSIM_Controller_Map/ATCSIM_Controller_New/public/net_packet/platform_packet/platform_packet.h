#pragma once
#include "..\serial_base.h"
#include "site_info.h"
#include <string>
 
using namespace std;
//
///** 
// \brief		platfrom使用的包
// \details   有switch向center之间发送Ex创建
// \author    
// \date      2013-08-31
//*/
//class ExchangeConnectedPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ExchangeConnectedPacket);
//public:
//	int m_GroupID; 	// 分组号
//	std::string  m_GroupIP;			//分组IP
//	short m_GroupPort;			//分组port
//private:
//	SERIALIZE_PACKET(m_GroupID & m_GroupIP & m_GroupPort );
//};
//
///** 
// \brief		platfrom使用的包
// \details   有switch向center之间发送ATG连接上Ex
// \author    
// \date      2013-08-31
//*/
//class ATGConnectedExPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ATGConnectedExPacket);
//public:
//	int m_GroupID; 	// 分组号
//	int m_ATGID; 	// ATG号
//private:
//	SERIALIZE_PACKET(m_GroupID & m_ATGID);
//};
//
///** 
// \brief		platfrom使用的包
// \details   有switch向center之间发送Ex连接上DB
// \author    
// \date      2013-08-31
//*/
//class ExConnectedDBPacket : public CSerial_Base
//{
//	PKT_DECLARE_DYNCREATE(ExConnectedDBPacket);
//public:
//	int m_GroupID; 	// 分组号
//private:
//	SERIALIZE_PACKET(m_GroupID);
//};
//
///** 
// \brief		platfrom使用的包
// \details   有switch向center之间发送各席位连接上switch
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
// \brief		platfrom使用的包
// \details   有switch向center之间发送各席位状态改变
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
 \brief		交换服务的IP、Port信息包
 \details   Switch--->连接ExServer的席位
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
 \brief		数据服务的IP、Port信息包
 \details   Switch--->连接DataServer的席位
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
 \brief		通知其他席位断开与ExServer的连接
 \details   当席位被拖出分组时，Switch--->其他席位
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
	OT_ADD_IN_GROUP,		//!<加入分组
	OT_RELEASE_FROM_GROUP,	//!<退出分组
};
/** 
 \brief		分组操作
 \details   Center进行分组操作，Center--->Switch
 \author    
 \date      2013-08-13
*/
class PositionOperatePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionOperatePacket);

public:
	site_info m_ex_info;		//!<交换服务席位信息
	site_info m_pos_info;		//!<加入/退出分组的席位信息
	ENUM_OPERATE_TYPE m_eType;	//!<操作类型
private:
	SERIALIZE_PACKET(m_ex_info & m_pos_info & m_eType);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief		席位加入/退出分组
 \details   有席位加入/退出分组，通知本组ATG，ExServer--->本组ATG
 \author    
 \date      2013-09-23
*/
class PositionConnectedPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionConnectedPacket);

public:
	site_info m_pos_info;		//!<加入/退出分组的席位信息
	ENUM_OPERATE_TYPE m_eType;	//!<操作类型
private:
	SERIALIZE_PACKET(m_pos_info & m_eType);
};

//////////////////////////////////////////////////////////////////////////
enum ENUM_ATC_SERVICE_STATUS
{
	SS_INVALID_STATUS,				//!<初始状态
	SS_SERVICE_INITIALIZING,		//!<核心服务初始化中
	SS_SERVICE_INIT_FAILED,			//!<核心服务初始化失败
	SS_SERVICE_INIT_SUCCEED,		//!<核心服务初始化成功
};

/** 
 \brief		核心服务状态包
 \details   核心服务状态改变时发送
			核心服务--->ExServer
 \author    @lijin
 \date      2013-08-09
*/
class ServiceStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ServiceStatusPacket);

public:
	site_info  m_site_info;						//!<核心席位信息
	ENUM_ATC_SERVICE_STATUS m_eServiceStaus;	//!<核心服务状态信息
private:
	SERIALIZE_PACKET(m_site_info & m_eServiceStaus);	
};

//////////////////////////////////////////////////////////////////////////
enum ENUM_DATASERVER_STATUS
{
	DS_INVALID_STATUS,				//!<初始状态
	DS_CONNECT_DATABASE_FAILED,		//!<DataServer连接数据库失败
	DS_CONNECT_DATABASE_SUCCEED,	//!<DataServer连接数据库成功
	DS_DATASERVER_INITIALIZING,		//!<DataServer初始化中
	DS_DATASERVER_INIT_FAILED,		//!<DataServer初始化失败
	DS_DATASERVER_INIT_SUCCEED,		//!<DataServer初始化成功
};

/** 
 \brief		DataServer状态包
 \details   DataServer状态改变时发送
			DataServer--->ExServer
 \author    @lijin
 \date      2013-08-08
*/
class DataServerStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(DataServerStatusPacket);

public:
	ENUM_DATASERVER_STATUS m_eDataServerStaus;	//!<DataServer状态信息
private:
	SERIALIZE_PACKET(m_eDataServerStaus);	
};
//
///** 
// \brief		组失效包
// \details   ATG,DB等失效或掉线后分组变为不可用，返回信息给center
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
//	site_info  m_site_info;	//!<席位信息
//	UNAVAILABLEREASON m_Reason;			//!<true：初始化完成；false：初始化未完成
//private:
//	SERIALIZE_PACKET(m_site_info & m_Reason);
//};

//////////////////////////////////////////////////////////////////////////
enum ENUM_GROUP_STATUS
{
	GS_INVALID_STATUS,			//!<初始状态
	GS_GROUP_CREATING,			//!<组创建中（条件：核心服务正在连接ExServer，或ExServer正在连接DataServer，或DataServer正在初始化）
	GS_GROUP_CREATED_FAILED,	//!<组创建失败
	GS_GROUP_CREATED_SUCCEED,	//!<组创建成功（条件：核心服务已连接ExServer，且ExServer已连接DataServer，且DataServer初始化成功）
	GS_GROUP_DESTROYED,			//!<组已销毁（失效）
	GS_EXERCISE_LOADING,		//!<训练计划加载中（条件：核心服务初始化中）
	GS_EXERCISE_LOAD_FAILED,	//!<训练计划加载失败
	GS_EXERCISE_LOAD_SUCCEED,	//!<训练计划加载成功（条件：核心服务初始化成功）
	GS_EXERCISE_RUNNING,		//!<训练计划正在运行
	GS_EXERCISE_PAUSE,			//!<训练计划暂停
	GS_EXERCISE_STOP,			//!<训练计划停止
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
 \brief 组状态信息包 
\details   用于席位对Exercise信息进行更新显示(状态变化后才发送)
        ExServer ----> Center/Coach
\author
\date      2013-08-06
*/
class GroupStatusInfoPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(GroupStatusInfoPacket);

public:
	site_info m_ex_info;					//!<本组交换服务席位信息
	ENUM_GROUP_STATUS m_eGroupStatus;		//!<本组状态
	int m_nAirportID;						//!<机场ID（初始化为-1）
	int m_nExerciseID;						//!<训练计划ID（初始化为-1）
	std::string m_strInfo;					//!<附加信息（如训练计划加载失败原因等）
private:
   SERIALIZE_PACKET(m_ex_info & m_eGroupStatus & m_nAirportID & m_nExerciseID & m_strInfo);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief 错误信息包 
\details   组操作返回错误信息
        ExServer ----> Center/Coach/Switch
\author
\date      2013-08-09
*/
class ErrorInfoPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(ErrorInfoPacket);

public:
	site_info m_site_info;					//!<本组席位信息
	ENUM_GROUP_STATUS m_eGroupStatus;		//!<本组状态（操作执行失败时将本组状态返回）
	std::string m_strInfo;					//!<附加信息（操作执行错误：如当前状态不能分组、当前状态不能执行该命令）
private:
   SERIALIZE_PACKET(m_site_info & m_eGroupStatus & m_strInfo);
};

//////////////////////////////////////////////////////////////////////////
//enum ENUM_EXERCISE_STATUS
//{
//	ES_INVALID_STATUS,			//!<初始状态
//	ES_EXERCISE_LOADING,		//!<训练计划加载中（条件：核心服务初始化中）
//	ES_EXERCISE_LOAD_SUCCEED,	//!<训练计划加载成功（条件：核心服务初始化成功）
//	ES_EXERCISE_LOAD_FAILED,	//!<训练计划加载失败
//	ES_EXERCISE_RUNNING,		//!<训练计划正在运行
//	ES_EXERCISE_PAUSE,			//!<训练计划暂停
//	ES_EXERCISE_STOP,			//!<训练计划停止
//};
//
///** 
// \brief 训练计划状态信息包 
//\details   用于席位对Exercise信息进行更新显示(状态变化后才发送)
//        ExServer ----> Center/Coach
//\author
//\date      2013-08-06
//*/
//class ExerciseStatusInfoPacket : public CSerial_Base
//{
//   PKT_DECLARE_DYNCREATE(ExerciseStatusInfoPacket);
//
//public:
//	site_info m_site_info;					//!<席位信息
//	ENUM_EXERCISE_STATUS m_eExerciseStatus;	//!<训练计划状态
//	std::string m_strInfo;					//!<附加信息（如训练计划加载失败原因等）
//private:
//   SERIALIZE_PACKET(m_eExerciseStatus & m_strInfo);
//};

//////////////////////////////////////////////////////////////////////////
enum ENUM_CONNECTED_TYPE
{
	CT_CONNECTED_SWITCH,		//!<连接接入服务
	CT_DISCONNECTED_SWITCH,		//!<断开接入服务
	CT_CONNECTED_EXSERVER,		//!<连接交换服务
	CT_DISCONNECTED_EXSERVER,	//!<断开交换服务
};
/** 
 \brief 分组席位连接信息包 
 \details   主要是由Switch发送给Coach/Center关于每个客户端连接的状态信息
		如果某个客户端断开连接了或者连接到了Switch了，应该通知Coach/Center对界面进行更新
        Switch ----> Coach/Center
\author
\date      2013-08-06
*/
class PositionStatusInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(PositionStatusInfoPacket);

public:
	site_info m_site_info;					//!<席位信息（连接或断开的席位信息）
	ENUM_CONNECTED_TYPE m_eConnectedType;	//!<连接状态
	int m_nExServerID;						//!<所在分组的ID，若未加入分组，则ID为-1
private:
	SERIALIZE_PACKET(m_site_info & m_eConnectedType & m_nExServerID);
};

/** 
 \brief 本程序状态信息包 
 \details   当服务/客户端席位连入接入服务时报告自己的当前状态
		程序连接Switch时（首次连接或者Switch断开后重启发生的连接），报告程序当前的状态
        ATG/ExServer/Controller/Pilot/Supervisor/VisServer ----> Switch
\author
\date      2013-10-10
*/
class InitStatusInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitStatusInfoPacket);

public:
	site_info m_site_info;					//!<席位信息
	bool m_bAddedIntoGroup;					//!<是否已加入分组
	int m_nExServerID;						//!<所在分组的ID，若未加入分组，则ID为-1
private:
	SERIALIZE_PACKET(m_site_info & m_bAddedIntoGroup & m_nExServerID);
};


/** 
 \brief   管制员、管制单元（扇区）对应关系更新包
\details   用于管制员进行初始管制单元（扇区）分配管制
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class RadarControlUnitRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarControlUnitRelationsPacket);

public:
	std::map<int, std::vector<std::string> > m_rsRelations; //!<雷达（物理id）、管制单元（扇区）对应关系: 这部分信息，考虑由Center、Coach进行配置

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   管制员、机长对应关系分配以及更新包
\details   Center/Coach ---> Exchange (--->ATG, Coach/Center)
        Coach/Center订阅用于界面显示关系，ATG订阅用于发送给机长航迹中的管制权限（影响机长对飞机的控制权限）
\author    @hsb
\date      2013/08/06
*/

class RadarPilotRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarPilotRelationsPacket);
public:
   std::map<int, std::vector<int> > m_rpRelations; //!<管制员（物理id)、机长（物理id）对应关系：
private:
   SERIALIZE_PACKET(m_rpRelations);

};

/** 
\brief   管制员、机长对应关系包（用于备份）
\details   Exchange ---> Coach/Center
		用于Coach/Center重启后，界面显示关系
\author    @lijin
\date      2013/09/22
*/

class BackRadarPilotRelationsPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(BackRadarPilotRelationsPacket);
public:
	int m_nExServerID;								//!<所在分组的ID
	std::map<int, std::vector<int> > m_rpRelations; //!<管制员（物理id)、机长（物理id）对应关系：
private:
	SERIALIZE_PACKET(m_nExServerID & m_rpRelations);
};

/** 
 \brief   飞机、管制单元（扇区）对应关系更新包
\details   用数据库提供扇区飞机对应
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightControlUnitRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightControlUnitRelationsPacket);
public:
	std::map<std::string, std::vector<int> > m_sfRelations; //!<管制单元(扇区)、飞机（id）对应关系：
private:
   SERIALIZE_PACKET(m_sfRelations);
};
/** 
 \brief   飞机、机长对应关系包
\details   用扇区分配后，由各种扇区，管制员，机长三者关系提供机长飞机对应
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightPilotRelationsPacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightPilotRelationsPacket);
public:
   std::map<int, std::vector<int> > m_pfRelations; //!<机长（物理id)、飞机（id）对应关系：
private:
   SERIALIZE_PACKET(m_pfRelations);
};


/** 
 \brief   机长移交包
\details   用于同一管制员下的机长进行飞机移交
        poilt ---> Exchange --->ATG--->polit
\author    @hsb
\date      2013/09/23
*/
class FlightPilotTransferPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlightPilotTransferPacket);
public:
	int m_iFlightId;		//!< 移交飞机id
	int m_iSourcePilotId;	//!< 移交源机长id
	int m_iTargetPilotId;	//!< 移交目标机长id
private:
	SERIALIZE_PACKET(m_iFlightId&m_iSourcePilotId&m_iTargetPilotId);
};

/** 
 \brief   管制员、管制单元（扇区）对应关系更新包
\details   用于管制员进行初始管制单元（扇区）分配管制
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class RadarControlUnitRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarControlUnitRelationsUpdatePacket);

public:
	std::map<int, std::vector<std::string> > m_rsRelations; //!<雷达（物理id）、管制单元（扇区）对应关系: 这部分信息，考虑由Center、Coach进行配置

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   飞机、管制单元（扇区）对应关系更新包
\details   用数据库提供扇区飞机对应
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightControlUnitRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightControlUnitRelationsUpdatePacket);
public:
	std::map<std::string, std::vector<int> > m_sfRelations; //!<管制单元(扇区)、飞机（id）对应关系：
private:
   SERIALIZE_PACKET(m_sfRelations);
};
/** 
 \brief   飞机、机长对应关系包
\details   用扇区分配后，由各种扇区，管制员，机长三者关系提供机长飞机对应
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @hsb
\date      2013/08/06
*/
class FlightPilotRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(FlightPilotRelationsUpdatePacket);
public:
   std::map<int, std::vector<int> > m_pfRelations; //!<机长（物理id)、飞机（id）对应关系：
private:
   SERIALIZE_PACKET(m_pfRelations);
};
////////////////////////////////////////////////////////////////////
/** 
 \brief   管制员、扇区对应关系更新包
\details   用于管制员进行初始扇区分配管制
        Center/Coach ---> Exchange (--->Controller, ATG...)
\author    @zcw
\date      2013/08/06
*/
class RadarSectorRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarSectorRelationsUpdatePacket);

public:
   std::map<int, std::set<int> > m_rsRelations; //!<雷达（物理id）、扇区对应关系: 这部分信息，考虑由Center、Coach进行配置

private:
   SERIALIZE_PACKET(m_rsRelations);

};

/** 
 \brief   管制员、机长对应关系分配以及更新包
\details   Center/Coach ---> Exchange (--->ATG, Coach/Center)
        Coach/Center订阅用于界面显示关系，ATG订阅用于发送给机长航迹中的管制权限（影响机长对飞机的控制权限）
\author    @zcw
\date      2013/08/06
*/

class RadarPilotRelationsUpdatePacket : public CSerial_Base
{
   PKT_DECLARE_DYNCREATE(RadarPilotRelationsUpdatePacket);
public:
   std::map<int, std::vector<int> > m_rpRelations; //!<管制员（物理id)、机长（物理id）对应关系：
private:
   SERIALIZE_PACKET(m_rpRelations);

};

/** 
 \brief		请求分组中管制员、机长对应关系包
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
\brief		教员席位向其他席位发送的邮件信息包
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