#ifndef _STRUCT_DEFINE_HEADER
#define _STRUCT_DEFINE_HEADER
/******************************************
功能：该文件定公共使用的结构和类型
*******************************************/

#include <vector>
#include <string>
using namespace std;

//命令执行模式
enum ENUM_EXECUTE_MODE
{
	EXCUTE_NONE=0,       //未知
	EXCUTE_ATONCE=1,     //立即
	EXCUTE_AFTER=2,      //插入当前命令后,并删除之后的所有状态
	EXCUTE_QUEUED=3,     //添加到队列尾
};

// 运动目标的分类（飞机、车辆）
enum ENUM_OBJ_TYPE 
{
	OT_OBJ_NONE=0,         //未知类型
	OT_PLANE,					//民用飞机(除直升机外)
	OT_HELICOPTER,			//直升机
	OT_VEHICLE,					//车辆
	OT_ENV,              
	OT_BIRD,						//鸟
	OT_CATTLE,					//牛
	OT_DOG,						//狗
	OT_BALLOON,				//气球
	OT_SERVICE_CAR = 120,      //服务车辆
};

// 运动目标状态类型定义
enum ENUM_STATE_TYPE
{
	STATE_NONE=0,             //未定义状态
	STAT_COOL_WAIT = 1,       //冷等待(关闭引擎)
	STAT_START_UP = 2,          //开引擎状态
	STAT_CLOSE_DOWN = 3,      //关引擎状态
	STAT_WARM_WAIT = 4,        //热等待(开引擎)
	STAT_TAXING = 5,              //地面滑行状态
	STAT_LAUNCHING = 6,       //起飞状态
	STAT_LANDING = 7,            //降落状态
	STAT_HOLD = 9,                  //空中盘旋状态
	STAT_SPECIAL_OPER = 11,         //特殊命令状态
	STAT_IN_AIR = 13,                  //空中飞行状态
	STAT_SID=14,         //标准离港程序
	STAT_STAR=15,     //标准进港程序
	STAT_CRASHED=16,   //撞毁
	STAT_HELI_TDF = 17, //直升机贴地飞
	STAT_HELI_XT = 18,  //直升机悬停
	STAT_HELI_MOVE = 19,//直升机移动
	STAT_CAR_SERVICE = 20,//服务车辆
	STAT_AIRKINEMATIC = 21,//坠毁
	STAT_SIMPLE_TOWER,         //简单塔台状态
};

//管制席与扇区对应
struct ContrlSectorMap
{
	int iCotrlId;      //管制席位号
	vector<string>  vSector;     //管制的扇区
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCotrlId & vSector; 
	}
};

//管制席与机长对应
struct ContrlPilotMap
{
	string iCotrlId;      //管制席位号
    vector<int> vPilot;      //管制机长席位号
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCotrlId & vPilot; 
	}
};

//机长席位号与飞机对应
struct PilotPlaneMap
{
	int iPilotId;     //机长席位号
	vector<int> vPlane;     //管制飞机ID
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iPilotId & vPlane; 
	}
};

//扇区与飞机对应
struct SectorPlaneMap
{
	string Sector;     //扇区
	vector<int> vPlane;     //管制飞机
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & Sector & vPlane; 
	}
};

/** 
 \brief		云类型              
 \details  
 \author    
 \date      2013-06-03
*/
enum EM_CLOUD_TYPE
{
	DEFAULT_YUN,  //默认的云
	CENG_YUN,     //层云
	JUAN_YUN,     //卷云
	DAN_JI_YUN,   //淡积云
	NONG_JI_YUN,  //浓积云
	JIYU_YUN,      //积雨云
};

//! 高度类型
enum ENUM_AltitudeType
{
	ALTTYPE_INVALID,
	ALTTYPE_QNE,    //标压
	ALTTYPE_QFE,    //场压高度
	ALTTYPE_QNH,   //海压高度
};

//! 航迹类型
enum ENUM_TRACKTYPE
{
	TRACKTYPE_INVALID,
	TRACKTYPE_INAIR,
	TRACKTYPE_ONGROUND,
};

//! 特殊情况类型
enum ENUM_EMERGENCYTYPE
{
	EMERGENCY_INVALID = 0x00000000,
	EMERGENCY_RF = 0x00000001,
	EMERGENCY_EM = 0x00000002,
	EMERGENCY_HJ = 0x00000004,
};

//坐标结构
struct stPoint
{
   double dLongtitude;      //经度,单位:弧度
   double dLatitude;         //纬度,单位:弧度
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & dLongtitude & dLatitude; 
	}
};

//!报告类型
enum ENUM_REPORT_TYPE
{
	RQ_REPORT = 1,  ///<请求产生类报告
	SEARCH_REPORT = 2, ///<查询类报告
	STANDARD_REPORT = 3, ///<标准过台报告
	LVL_REACH_REPORT = 4, ///<高度到达报告
	ESTABLISHED_REPORT = 5, ///<盲降建立报
	PROCEDURE_REPORT = 6, ///<过程报告，机长FPLLIST中的报告
};

//!气压类型
enum ENUM_QNH_TYPE
{
    TYPE_QNE,    //标准气压
    TYPE_QNH,    //修正海压
    TYPE_QFE,    //场压
};
#endif