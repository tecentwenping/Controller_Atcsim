#pragma once
#define MAX_VALUE_WS 600000000 //定义最大极限值
#include "DataObj/dataobjs.h"
#include "net_packet/serial_base.h"

/*********************发包*************************/
//发包：管制员席位初始化包
class InitializeClientPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitializeClientPacket);
public:
	int m_nAirportID;//机场ID
private:
	SERIALIZE_PACKET(m_nAirportID)
};

//发包：初始化包（只更新机场数据）
class AirportDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportDataPacket);
public:
	int m_nAirportID;//机场ID
private:
	SERIALIZE_PACKET(m_nAirportID)
};


/**********************回复包**************************/

//回复包：机场数据包
class AckAirportDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAirportDataPacket);
public:
	AirportData m_airportdata;
	std::vector<AirportData> m_vecAirport; //所有机场
	std::vector<RunwayData> m_vcRunWayData;//跑道
	std::vector<RoadData> m_vcRoadData;//滑行道
	std::vector<FixpointData> m_vcFixpointData;//固定点
	std::vector<Tower> m_vecTower;
	std::vector<AirportModel> m_vecAirportModel;
	std::vector<GateData> m_vecGate;//停机位
	std::vector<Sid> m_vecSid; //标准进场
	std::vector<Star> m_vecStar; //标准离场
	std::vector<Macro> m_vecMacro; //宏
	std::vector<MacroGroup> m_vecMacroGroup; //宏组
	std::vector<Stdapch> m_vecStdapch;//进近程序
	std::vector<Hold> m_vecHold; //等待程序
	std::vector<Miss> m_vecMiss; //复飞程序

	std::vector<LightGroup> m_vecLightGroup; //灯光组
	std::vector<Route> m_vecRoute; //路线
	std::vector<Light> m_vecLight;  //灯
	std::vector<LightCollection> m_vecLightCollection; //灯光组组合
	std::vector<LightGroupDetail> m_vecLightGroupDetail; //灯光组与其对应的灯

private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_airportdata & m_vecAirport & m_vcRunWayData & m_vcRoadData 
		& m_vcFixpointData & m_vecTower & m_vecAirportModel & m_vecGate & m_vecSid & m_vecStar 
		& m_vecMacro & m_vecMacroGroup & m_vecStdapch & m_vecHold & m_vecMiss & m_vecLightGroup & m_vecRoute
		& m_vecLight & m_vecLightCollection & m_vecLightGroupDetail);

};

//回复包：空中数据包
class AckAirspaceDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAirspaceDataPacket);
public: 
	std::vector<Beacon> m_vecBeacon;				//导航台
	std::vector<SurveillanceSensor> m_vecSensor;	//监视传感器（雷达）
	std::vector<StcaArea> m_vecStcaArea;			//冲突告警区
	std::vector<MsawArea> m_vecMsawArea;			//最低引导扇区
	std::vector<RestrictArea> m_vecRestrictAera;    //限制区，禁区和危险区
	std::vector<ATS> m_vecATS;						//临时航路
	std::vector<Radarrobe> m_vecRadarrobe;			//雷达地理盲区
	std::vector<Course> m_vecCourse;				//固定航路
	std::vector<QnhArea> m_vecQnhArea;			//QNH区
	std::vector<InhibitoryArea> m_vecInhibitoryArea;	//告警抑制区

	//以下为扇区相关数据
	std::vector<Sector> m_vecSector;				//扇区
	std::vector<GlyphPt>  m_vecGlyphPt;
	std::vector<GlyphPtArcInfo> m_vecGlyphPtArcInfo;
	std::vector<Cylinder> m_vecCylinder;
	std::vector<CylinderGlyph> m_vecCylinderGlyph;


	//std::vector<ControlArea> m_vcControlAirspaceData;//管制区
	//std::vector<FinalControlArea> m_vcFinalControlAirspaceData;//终端管制区
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vecBeacon & m_vecSensor & m_vecStcaArea & m_vecMsawArea & m_vecRestrictAera & m_vecATS & m_vecRadarrobe & m_vecCourse & m_vecQnhArea & m_vecInhibitoryArea & m_vecSector & m_vecGlyphPt & m_vecGlyphPtArcInfo & m_vecCylinder & m_vecCylinderGlyph );

};

//回复包：基础数据包
class AckBaseDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckBaseDataPacket);
public: 
	std::vector<AircraftData> m_vcAircraftData;//机型数据
	std::vector<AircraftPerformance> m_vAicraftPerData;
	std::vector<Vehicle> m_vcVehicleData;//车辆数据
	std::vector<Company> m_vcCompanyData;//航空公司数据
	std::vector<Flight> m_vcFlightData; //航班数据
	std::vector<AircraftModel> m_vcAircraftModel; //机型模型
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vcAircraftData &m_vAicraftPerData &m_vcVehicleData &m_vcCompanyData &m_vcFlightData & m_vcAircraftModel)
};

//回复包：训练计划包 以前测试用，待删除
class AckExercisePacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckExercisePacket);
public: 
	std::vector<TrainPlan>		m_vecTrainPlan;//训练计划
	std::vector<ObjPlan>		m_vecObj;	//飞行目标计划
	std::vector<TPFlyPlan>		m_vecFlyPlan;    //飞行计划
	std::vector<VehiclePlan>	m_vecVehiclePlan ; //车辆计划
	std::vector<CloudPlan>      m_vecCloudPlan;   //云计划
	std::vector<SmokePlan>      m_vecSmokePlan;   //烟计划
	std::vector<SpecialEffectObjPlan> m_vecSpecialEffectObjPlan; //特效运动物体计划
	std::vector <EnvPlan> m_vecEnvPlan;//环境参数计划
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vecTrainPlan & m_vecObj & m_vecFlyPlan & m_vecVehiclePlan & m_vecCloudPlan & m_vecSmokePlan & m_vecSpecialEffectObjPlan & m_vecEnvPlan);
};

//回复包：教员席位训练计划请求回复包
class AckAllTrainPlanNamePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllTrainPlanNamePacket);
public:
	std::vector<std::string> m_vAllTrainPlanName;
private:
	SERIALIZE_PACKET(m_vAllTrainPlanName)
};

//回复包：单条训练计划以及相关飞行计划数据请求回复包
class AckSingleTrainPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleTrainPlanPacket);
public:
	TrainPlan m_TrainPlan;
	std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<TPFlyPlan> m_vFlyPlan;
	std::vector<VehiclePlan> m_vVehiclePlan;
	std::vector<SpecialEffectObjPlan> m_vSpecialEffectObjPlan;
private:
	SERIALIZE_PACKET(m_TrainPlan & m_vAllObjPlan & m_vFlyPlan & m_vVehiclePlan & m_vSpecialEffectObjPlan)
};

//回复包：单条训练计划以及相关飞行计划数据请求回复包（发给客户端）
class AckSingleTrainPlanPacket_S : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleTrainPlanPacket_S);
public:
	//TrainPlan m_TrainPlan;
	//std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<FplInfo> m_vFlyPlan;
private:
	SERIALIZE_PACKET(m_vFlyPlan)
};

//回复包：视景初始化需要的包
class VISInitPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(VISInitPacket);
public:
	//基础数据
	std::vector<LightGroup> m_vLightGroups;		//!<灯光组数据
	std::vector<AircraftForVis> m_vAircrafts;	//!<机型数据
	std::vector<VehicleForVis> m_vVehicles;		//车辆数据

	//与训练计划相关的数据
	int m_iTrainPlanID;					//!<训练计划ID
	std::string m_strTrainPlanName;		//!<训练计划名称
	std::string m_strDate;				//!<训练日期
	int m_iStartTime;					//!<训练开始时间 从0点开始以秒计算 */

	int m_iAirportID;					//!<机场ID
	std::string m_strAirportCode;		//!<机场四字码
	std::string m_strAirportModelName;	//!<机场模型名称
	double m_dAirportModelRotateAngle;	//!<机场模型旋转角度
	double m_dCenterPointLongitude;		//!<机场中心点经度(单位：弧度)
	double m_dCenterPointLatitude;		//!<机场中心点纬度(单位：弧度)

	std::vector<ObjPlanForVis> m_vObjPlans;	//!<目标计划
	std::vector<CloudPlan> m_vCloud;		//!<云
	std::vector<SmokePlan> m_vSmoke;		//!<烟
	EnvData m_envData;						//!<环境参数

	double m_dViewPointX;		//!<视点经度，视点初始化时，使用的主TOWER的参数
	double m_dViewPointY;		//!<视点纬度
	double m_dViewPointZ;		//!<视点高度
	double m_dViewPointHeading;	//!<视点的朝向
	double m_dViewPointPitch;	//!<视点的仰角
	double m_dViewPointRoll;	//!<视点水平翻转
private:
	SERIALIZE_PACKET(m_vLightGroups & m_vAircrafts & m_vVehicles & m_iTrainPlanID & m_strTrainPlanName & m_strDate & m_iStartTime 
		& m_iAirportID & m_strAirportCode & m_strAirportModelName & m_dAirportModelRotateAngle & m_dCenterPointLongitude
		& m_dCenterPointLatitude & m_vObjPlans & m_vCloud & m_vSmoke & m_envData & m_dViewPointX & m_dViewPointY 
		& m_dViewPointZ & m_dViewPointHeading & m_dViewPointPitch & m_dViewPointRoll)
};


/*!
\brief:		请求获得所有机场ID与map对的包
\details:	主要用于教员席位席位；
			教员席位在启动后发送该包请求所有机场ID与名字，以供选择训练计划使用；
			DataServer收到该包后回复AckAirportPacket包
\author DXQ
\date 2013/6/13
*/
class AllAirportPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AllAirportPacket);
public:
	int m_iSiteType; //席位类型
private:
	SERIALIZE_PACKET(m_iSiteType)
};



/*!
\brief:		包含全部机场名字与ID的map对包
\details:	主要用于教员席位
\author DXQ
\date 2013/6/13
*/
class AckAllAirportPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllAirportPacket);
public:
	std::map<string, int> m_mapAirport;	//机场名字与IDmap对
private:
	SERIALIZE_PACKET(m_mapAirport)
};


/*!
\brief:		请求获得某一机场所有训练计划ID与名字的map对包
\details:	主要用于教员席位；
			教员席位在切换机场的时候发送，以供选择训练计划使用；
			DataServer收到该包后回复AckAllExercisePacket包。
\author DXQ
\date 2013/6/13
*/
class AllExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AllExercisePacket);
public:
	int m_iAirportID;//机场ID
private:
	SERIALIZE_PACKET(m_iAirportID)
};


/*!
\brief:		包含某一机场的全部训练计划名字与ID的map对包
\details:	主要用于教员席位，以供选择训练计划使用。
\author DXQ
\date 2013/6/13
*/
class AckAllExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllExercisePacket);
public:
	int m_nAirportID;						//机场ID
	std::map<string, int> m_mapExercise;	//训练计划名字和IDmap对
private:
	SERIALIZE_PACKET(m_nAirportID & m_mapExercise)
};



/*!
\brief:		单条训练计划以及相关飞行计划数据请求回复包
\details:	主要用于核心计算。
\author DXQ
\date 2013/6/14
*/
class AckSingleExrecisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleExrecisePacket);
public:
	TrainPlan m_TrainPlan;
	std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<TPFlyPlan> m_vAllFlyPlan;
	std::vector<VehiclePlan> m_vAllVehiclePlan;
	std::vector<EnvPlan> m_vecEnvPlan;
	std::vector<LightPlan> m_vecLightPlan;
private:
	SERIALIZE_PACKET(m_TrainPlan & m_vAllObjPlan & m_vAllFlyPlan & m_vAllVehiclePlan & m_vecEnvPlan & m_vecLightPlan)
};



/*!
\brief:		单条训练计划包，发送给客户端
\details:	主要用于客户端。
\author DXQ
\date 2013/6/18
*/
class AckSingleExrecisePacket_S : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleExrecisePacket_S);
public:
	std::string m_strTrainPlanName;		//训练名
	std::string m_strAirportName;		//机场名
	int m_iStartTime;					//训练开始时间
	std::map<int, std::vector<std::string>> m_mapControllerSector;//管制员扇区对应关系(未分配到任何管制区的管制员为-1)
	std::map<std::string, std::vector<int>> m_mapSectorFlight;//扇区与扇区下管制飞机对应关系
private:
	SERIALIZE_PACKET(m_strTrainPlanName & m_strAirportName & m_iStartTime & m_mapControllerSector & m_mapSectorFlight)
};



/*!
\brief:		包含某一机场ID与训练计划ID
\details:	主要用于教员席位；
			教员席位在选择了某个机场中的某个训练计划后，点击准备时发送该包；
			DataServer收到该包后，回复一系列包；
			DataServer回复的包如下：
								AckBaseDataPacket（基础数据包）
								AckAirportDataPacket（机场数据包）
								AckAirspaceDataPacket（空中数据包）
								AckSingleExrecisePacket（单条训练计划包）
								AckSingleTrainPlanPacket_S（客户端训练计划包）
								VISInitPacket（视景初始化包）

\author DXQ
\date 2013/6/13
*/
class InitExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitExercisePacket);
public:
	int m_iAirportID;	//机场ID
	int m_iTrainPlanID; //训练计划ID
private:
	SERIALIZE_PACKET(m_iAirportID & m_iTrainPlanID)
};



/*!
\brief:		切换机场包
\details:	主要用于Designer席位，初始化时以及切换机场时使用；
			Designer初始化时，发送该包；
			Designer切换机场时，发送该包
			DataServer收到该包后，回复一系列包；
			DataServer回复的包如下：
									AckBaseDataPacket（基础数据包）
									AckAirportDataPacket（机场数据包）
									AckAirspaceDataPacket（空中数据包）
									AckExercisePacket（训练计划包）
\author DXQ
\date 2013/6/17
*/
class AirportChangePacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportChangePacket);
public:
	int m_iAirportID;				//机场ID，机场ID<=0时根据机场名字决定
	std::string m_strAirportName;	//机场名
private:
	SERIALIZE_PACKET(m_iAirportID & m_strAirportName)
};

/*!
\brief: 包含某一机场ID与训练计划ID
\details: 主要用于教员席位；
教员席位在选择了某个机场中的某个训练计划后，点击准备时发送该包；
DataServer收到该包后，回复一系列包；
DataServer回复的包如下：
AckSingleTrainPlanPacket_S（客户端训练计划包）
\author JZH
\date 2013/9/16
*/
class ExerciseInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ExerciseInfoPacket);
public:
	int m_iAirportID; //机场ID
	int m_iTrainPlanID; //训练计划ID
private:
	SERIALIZE_PACKET(m_iAirportID & m_iTrainPlanID)
};