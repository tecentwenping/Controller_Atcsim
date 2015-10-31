/************************************************************************/
/* Author: 梁文快
   Time:2014.2.23
   Description:TowerSimuFPlanStruct.h文件主要定义了塔台模拟机中飞行计划以及
   目标计划的结构信息，在这里目标计划与飞行计划是一对一的关系，StructConstParam.h
   文件中定义的FDO飞行计划结构FlightPlanStruct要与AircraftPacketStruct结构相结合，
   准确的说是要将FlightPlanStruct结构信息融入到AircraftPacketStruct中，因为只有
   AircraftPacketStruct的结构信息发送到显示终端以后，才能显示出对应的航班。
*/
#ifndef _TOWERSIMUFPLANSTRUCT_H_
#define _TOWERSIMUFPLANSTRUCT_H_
#include <QObject>
#include <QString>
#include <vector>
#include <QMetaType>
using std::vector;

namespace TowerSimuSpace{

	const int	SENDFLIGHTPLANUDPPORT	= 10000;//发送飞行计划的UDP端口号
	const int	SENDPACKETUDPPORT		= 10001;//发送报文的UDP端口号
	const int	SENDCOMMANDUDPPORT		= 9901; //发送命令的UDP端口号
	const int	RECVFLIGHTPLANIDPORT	= 9902; //接收航班ID的UDP端口号
	const double Pi = 3.14159265358979323846;

	enum ENUM_OBJ_TYPE 
	{
		OT_OBJ_NONE = 0,			//未知类型
		OT_PLANE,					//民用飞机(除直升机外)
		OT_HELICOPTER,				//直升机
		OT_VEHICLE,					//车辆
		OT_ENV,              
		OT_BIRD,					//鸟
		OT_CATTLE,					//牛
		OT_DOG,						//狗
		OT_BALLOON,					//气球
		OT_SERVICE_CAR = 120,		//服务车辆
	};

	struct FlightPlanInfo
	{
		bool m_autoTakeof;
		int  m_arrRunway_id;
		int  m_depRunway_id;
		int  m_depGate_id;
		int  m_arrGate_id;
		int  m_vacateLine_id;
		int  m_inRunway_id;
		int  m_sector_id;
	};
	struct TowerObjectPlanStruct
	{
		ENUM_OBJ_TYPE   ObjType;						//类型
		char			strSSrcode[64];					//关联飞行计划的二次码
		double			dLongtitude;					//出现的经度（单位：弧度）
		double			dLatitude;           			//出现的纬度（单位：弧度）
		double 			dAltitude;						//初始高度（标准海压高度，单位：米）
		double 			dHeading;						//机头朝向（单位：弧度）
		double 			dIAS;							//初始速度（表速，单位s：米/秒）
		char			sAppearTime[64];		        //出现时间（单位：秒）
		char			strModelType[64];				//机型名
		char			strRegNum[64];		            //注册号
		bool 			bEngineStart;					//引擎是否起动
	};
	//航路点结构
	struct TowerAirRoadStruct
	{
		char sBeacon[64];//导航台
		char sHeight[64];//高度
		char sSpeed[64];//速度
	};
	//飞行计划结构
	struct TowerFlightPlanStruct
	{
		int				iFlightPlanId;					//飞行计划id
		char			sSSRCode[64];					/*  二次码 */
		bool			bRVSM;							/* 是否具备RVSM能力*/
		int				iFlyPlanType;					/* 飞行计划类型,0进港，1离港 */
		char			sSectorName[64];				//所属扇区名
		char			sCompany[64];		            /* 航空公司 */
		char			sCallSign[64];					/* 呼号（航空公司+数字编码）*/
		char			sDepDromeName[64];		        /* 起飞机场 */
		char			sArrDromeName[64];       		/* 降落机场 */
		char			sAlternateDrome[64];	        /* 备降场 */
		int				iCruiseLvl;						/* 巡航高度(标准海压高度，单位：米) */
		int				iCruiseSpd;						/* 巡航速度(表速或者马赫，表速单位：米/秒) */
		char			sArrRunway[64];					/* 降落跑道 */
		char			sDepRunway[64];                 /* 起飞跑道*/
		char			sWeight[64];		            /* 载重 */
		char			sDepGate[64];		            /* 离场的停机位 */
		char			sArrGate[64];		            /* 进场的停机位 */
		char			sVacateLine[64];		        /* 脱离道 */
		char			sInRunwayLine[64];              /* 进入道 */
		char			sDepartureTime[64];				/* 预计起飞时间*/
		char			sArrivalTime[64];		        /* 预计到达时间*/
		char			sSidName[64];                   /*离场程序名称*/

		TowerAirRoadStruct	sAirRoadPoint;
	};
	//动态创建飞机包
	struct TowerAircraftPacketStruct
	{
		TowerObjectPlanStruct TowerobjFlight;	//目标计划 /* 这里目标计划和飞行计划一一对应*/
		TowerFlightPlanStruct TowerplanFlight;	//飞行计划

	};
   
	//控制飞机运动所包含的结构信息
	struct TowerControlFlightStruct
	{
		int		sFlightNo;
		char	sNetCommand[64];//控制飞机运动指令
	};
	
}

Q_DECLARE_METATYPE(TowerSimuSpace::FlightPlanInfo);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerFlightPlanStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerAirRoadStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerObjectPlanStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerAircraftPacketStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerControlFlightStruct);
#endif