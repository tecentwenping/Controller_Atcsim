#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
//#include "Global_Struct.h"
#include "DataObj/dataobjs.h"
#include "BaseTypeDefine/PublicTypeDefine.h"
#include "Serialization/wserialize.h"
#include "DataObj/trainplan_data_objs.h"


#define MESSAGE_SIZE_LEN				(30 * 1024)
#define MAX_VALUE_WS 600000000 //定义最大极限值
#define MIN_VALUE -600000000//定义最小极限值


struct Trace 
{
	Trace::Trace(){}
	Trace::Trace(int arg_attitude, int arg_gas, int arg_ias, float arg_heading,
		float arg_fAbsX, float arg_fAbsY, unsigned char arg_byAtt,
		int arg_ID, int arg_PlanID, std::string arg_szName,std::string arg_strSSR,bool arg_bHide) :
	attitude(arg_attitude),
	gas(arg_gas),
	ias(arg_ias),
	heading(arg_heading),
	fAbsX(arg_fAbsX),
	fAbsY(arg_fAbsY),
	byAtt(arg_byAtt),
	ID(arg_ID),
	PlanID(arg_PlanID),
	szName(arg_szName),
	strSSR(arg_strSSR),
	bHide(arg_bHide)
	{

	}
	int attitude;		//高度		Unit : m
	int gas;			//GAS		Unit : km/h
	int ias;			//IAS		Unit : km/h
	float heading;		//方向		Unit : centigrade
	float fAbsX;		//坐标位置x	Unit : km. Absolute position of aircraft.
	float fAbsY;		//坐标位置y	Unit : km. Absolute position of aircraft.
	unsigned char byAtt;//姿态attitude，: cruising , 1: climb ; 2: decent
	int ID;//对机长是objID，sdd是航迹号;
	int PlanID;//对机长是飞行计划ID
	std::string szName;
	std::string strSSR;
	bool bHide; //是否隐藏
	ENUM_STATE_TYPE	eStateType;	//飞机状态：坠毁、阻塞、冷等待、热等待、滑行、起飞、在空中、降落等
	bool bRVSM; //当前飞机是否具备RVSM能力。
	double dCDR; //正：爬升率，负：下降率
	ENUM_OBJ_TYPE m_type;
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & attitude & gas & ias & heading 
			& fAbsX & fAbsY & byAtt 
			& ID & PlanID &szName & strSSR &bHide & eStateType & bRVSM & dCDR & m_type;
	}
};

class TracePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TracePacket);

public:
	Trace m_trce;
private:
	SERIALIZE_PACKET(m_trce)
};

//心跳包：
class TimePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TimePacket);
public:
	int hour;
	int minute;
	int second;
	int msec;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();
	SERIALIZE_PACKET(hour & minute & second & msec)
};

class CTestPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CTestPacket);

public:
	std::string  m_msg;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

struct ST_ObjID
{
	int iObjID;
	std::string strName;
};

class InitPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitPacket);

public:
	int  m_AircraftNum;
	std::vector <ST_ObjID> m_vObjIDs;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class TraceArrayPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TraceArrayPacket);

public:
	int hour;
	int minute;
	int second;
	int msec;
	std::vector<Trace> m_vTrace;
private:
	SERIALIZE_PACKET(hour & minute & second & msec & m_vTrace)
};

//读取lua脚本增加飞机时发给client的提示包：内容包括所有属性数据
class ProAddPlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ProAddPlanePacket);
public:
	//int m_FlyPlanNum;
	std::vector <FlyPlanData> m_vFlyPlans;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class TrainPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanPacket);

public:
	int PlaneinAirNum;
	int PlaneonGroundNum;
	int Frequency;

private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum Command
{
	INVALID = 0,
	CIRCLE_CMD = 1,
	DIRECTLY_CMD = 2,
	TAX_LEFT_CMD = 3,
	TAX_RIGHT_CMD = 4,
};

class CommandPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CommandPacket);

public:
	Command cmd;
	int id;//飞机ID
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum SysCommand
{
	START_PLAN = 1,
	END_PLAN = 2,
	READY_PLAN = 3,
};

class SysCommandPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SysCommandPacket);

public:
	SysCommand cmd;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum SysStatus
{
	START_STATUS = 1,
	END_STATUS= 2,
	PAUSE_STATUS = 3,
};

enum OperatorMemcache
{
	CACHE_UPDATE = 1,
	CACHE_FETCH= 2,
	CACHE_DELETE = 3,
};

class SysStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SysStatusPacket);

public:
	int GroupID;
	SysStatus Status;
	OperatorMemcache OpCache;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

// class ExServerIPPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(ExServerIPPacket);
// 
// public:
// 	std::string ip;
// 	short port;
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

// class DataServiceIPPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(DataServiceIPPacket);
// 
// public:
// 	std::string ip;
// 	short port;
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

class MemcacheServiceIPPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MemcacheServiceIPPacket);

public:
	std::string ip;
	short port;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

// class GroupDisConnectPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(GroupDisConnectPacket);
// 
// public:
// 
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

//! 运动目标信息(非SDD航迹)
struct MovingObjTrack
{ 
	int iID;                            ///< 目标ID
	int PlanID;                         ///< 飞行计划ID
	ENUM_TRACKTYPE TrackType;           ///< 航迹类型
	int iICAOAddress;                   ///< 航空器ICAO地址
	int iSurveilEquip;                  ///< 航空器监视设备
	std::string strRegisterCode;        ///< 航空器注册号  
	std::string strCallSign;            ///< 航空器呼号
	std::string strSSRCode;             ///< 二次雷达码
	double dLongitude;                  ///< 航空器经度
	double dLatitude;                   ///< 航空器纬度
	int iAltitude;                      ///< 航空器高度m
	ENUM_AltitudeType AltitudeType;     ///< 航空器高度类型
	double dIAS;                        ///< 航空器IAS km/h
	double dTAS;                        ///< 航空器TAS km/h
	double dGAS;                        ///< 航空器GAS km/h
	double dHeading;                    ///< 航空器机头朝向
	double dTrackAngle;                 ///< 航空器航迹朝向
	int iVerticalState;                 ///< 航空器垂直状态：上升、平飞、下降
	double dVerticalRate;               ///< 上升下降率，为正值
	double dRollAngle;                  ///< 航空器横滚角
	int iDesAltitude;                   ///< 航空器目的高度
	ENUM_AltitudeType DesAltitudeType;  ///< 航空器目的高度类型
	double dDesHeading;                 ///< 设置航空器目的朝向
	bool bSPIFlag;                      ///< 设置航空器SPI标志
	int EmergencyType;                  ///< 设置航空器紧急情况类型
	bool bHide;                         ///< 是否隐藏
	bool bRVSM;                         ///< 当前飞机是否具备RVSM能力
	ENUM_STATE_TYPE eStateType;         ///< 飞机状态：坠毁、阻塞、冷等待、热等待、滑行、起飞、在空中、降落等
	ENUM_OBJ_TYPE ObjType;              ///< 目标类型
    double dQNEAlt;                     ///< 当前QNE高度，避免将QNH/QFE高度转回QNE高度

	//新添加 shenjk
	double dROC; ///< 目标爬升率
	double	dROD;	///< 目标下降率
	double	dMaxROC;///< 最大爬升率
	double	dMaxROD; ///< 最大下降率
	std::string	strRespMode;///< 应答机模式（mode）
	double	dTurnRate	; ///< 转弯率
	double	dDestIas; ///< 目标速度（真速）
	double	dMaxIas; ///< 最大速度
	double	dCurMach; ///<当前马赫数
	double	dDestMach; ///<	 目标马赫数   
	std::vector<std::string> vRouteName; ///<   飞行航路
	int iCurRouteIndex; ///< 当前航路序号
	double	dDSSpd; ///<	V1速度
	std::vector<std::string>	vCmdList; ///<       执行命令列表   
	int	 iCurCmdIndex; ///<   当前命令序号        
	
	MovingObjTrack()
	{
		 iID = -1;                            ///< 目标ID
		 PlanID = -1;                         ///< 飞行计划ID
		//ENUM_TRACKTYPE TrackType;           ///< 航迹类型
		 iICAOAddress = -1;                   ///< 航空器ICAO地址
		 iSurveilEquip = -1;                  ///< 航空器监视设备
		//std::string strRegisterCode;        ///< 航空器注册号  
		//std::string strCallSign;            ///< 航空器呼号
		//std::string strSSRCode;             ///< 二次雷达码
		 dLongitude = -1.0;                  ///< 航空器经度
		 dLatitude = -1.0;                   ///< 航空器纬度
		 iAltitude = -1;                      ///< 航空器高度m
		//ENUM_AltitudeType AltitudeType;     ///< 航空器高度类型
		 dIAS = -1.0;                        ///< 航空器IAS km/h
		 dTAS = -1.0;                        ///< 航空器TAS km/h
		 dGAS = -1.0;                        ///< 航空器GAS km/h
		 dHeading = -1.0;                    ///< 航空器机头朝向
		 dTrackAngle = -1.0;                 ///< 航空器航迹朝向
		 iVerticalState = -1;                 ///< 航空器垂直状态：上升、平飞、下降
		 dVerticalRate = -1.0;               ///< 上升下降率，为正值
		 dRollAngle = -1.0;                  ///< 航空器横滚角
		 iDesAltitude = -1;                   ///< 航空器目的高度
		//ENUM_AltitudeType DesAltitudeType;  ///< 航空器目的高度类型
		 dDesHeading = -1.0;                 ///< 设置航空器目的朝向
		 //bSPIFlag = false;                      ///< 设置航空器SPI标志
		 EmergencyType = -1;                  ///< 设置航空器紧急情况类型
		//bool bHide;                         ///< 是否隐藏
		//bool bRVSM;                         ///< 当前飞机是否具备RVSM能力
		//ENUM_STATE_TYPE eStateType;         ///< 飞机状态：坠毁、阻塞、冷等待、热等待、滑行、起飞、在空中、降落等
		//ENUM_OBJ_TYPE ObjType;              ///< 目标类型
		 dQNEAlt = -1.0;                     ///< 当前QNE高度，避免将QNH/QFE高度转回QNE高度

		//新添加 shenjk
		 dROC = -1.0;	///< 目标爬升率
		 dROD = -1.0;	///< 目标下降率
		 dMaxROC = -1.0;	///< 最大爬升率
		 dMaxROD = -1.0; ///< 最大下降率
		//ENUM_SURVEILANCEEQUIPMENT	eRespMode;	///< 应答机模式（mode）
		dTurnRate	 = -1.0; ///< 转弯率
		dDestIas = -1.0; ///< 目标速度（真速）
		dMaxIas = -1.0; ///< 最大速度
		dCurMach = -1.0; ///<当前马赫数
		dDestMach = -1.0; ///<	 目标马赫数   
	    vRouteName.clear(); ///<   飞行航路
	    iCurRouteIndex = -1; ///< 当前航路序号
		dDSSpd = -1.0; ///<	V1速度
		vCmdList.clear(); ///<       执行命令列表   
    	 iCurCmdIndex = -1; ///<   当前命令序号        

	}

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iID & PlanID & TrackType & iICAOAddress & iSurveilEquip & strRegisterCode &
			strCallSign & strSSRCode & dLongitude & dLatitude & iAltitude  &
			AltitudeType& dIAS & dTAS & dGAS & dHeading &
			dTrackAngle & iVerticalState & dVerticalRate & dRollAngle & iDesAltitude  &
			DesAltitudeType& dDesHeading & bSPIFlag &
			EmergencyType & bHide & bRVSM &eStateType & ObjType & dQNEAlt & dROC & dROD & dMaxROC & dMaxROD & strRespMode
			& dTurnRate & dDestIas & dMaxIas & dCurMach & dDestMach & vRouteName & iCurRouteIndex &dDSSpd & vCmdList & iCurCmdIndex;
	}
};

//! 运动目标信息包(非SDD航迹包)
class MovingObjPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MovingObjPacket);

public:
	std::vector<MovingObjTrack> m_vTrace;

private:
	SERIALIZE_PACKET(m_vTrace);
};

//特物体动态创建包(只用于运动的特效物体，如鸟、牛、狗、气球等)
class MoveSpelEffectCreatePacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(MoveSpelEffectCreatePacket);
public:
	SpecialEffectObjPlan effectPlan;        //特效物体计划
private:
	SERIALIZE_PACKET(effectPlan);
};

//特效运动物体创建回复包
class MoveSpelEffectCreateAckPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectCreateAckPacket);
public:
	int		m_ObjID;    //id编号
	ENUM_OBJ_TYPE	m_eObjType;       //特效物体类型
	string		m_strName;            //特效物体名字
private:
	SERIALIZE_PACKET(m_ObjID & m_eObjType & m_strName)
};

//运动特效物体删除包
class MoveSpelEffectDeletePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectDeletePacket);
public:
	int		m_ObjID;      //id编号
private:
	SERIALIZE_PACKET(m_ObjID)
};

//特效运动物体创建回复和删除包,用于视景
class MoveSpelEffectOperatorPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectOperatorPacket);
public:
	ENUM_OBJ_TYPE	 m_eObjType;     //类型
	int		 m_iObjID;         //id
	string	 m_sName;           //名字
	int		 m_iPerformanceID;	//性能ID(飞机使用)
	string	 m_sComSign;		  //航空公司名(飞机使用)
	bool             m_bIsDelete;      //是否删除
	double         m_dPosX;          //位置想
	double         m_dPosY;
	double         m_dPosZ;
	double 		   m_dHdg;                  //朝向
	double 		   m_dPith;             //仰角
	double 		   m_dRoll;                //横滚
private:
	SERIALIZE_PACKET(m_eObjType&m_iObjID&m_sName&m_iPerformanceID&m_sComSign&m_bIsDelete&m_dPosX&m_dPosY&m_dPosZ&m_dHdg&m_dPith&m_dRoll)
};

//动态创建运动物体查询包
class ReqTmpObjPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(ReqTmpObjPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//动态创建飞行计划包
class DynamicCreateFlightPlanPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateFlightPlanPacket);
public:
	int iFlightPlanId;                //飞行计划id
	string  sSSRCode;                   /*  二次码 */
	bool  bRVSM;			               /* 是否具备RVSM能力*/
	int	iFlyPlanType;	               /* 飞行计划类型,0进港，1离港 */
	string sSectorName;            //所属扇区名
	string sCompany;		               /* 航空公司 */
	string sCallSign;		           /* 呼号（航空公司+数字编码）*/
	string sDepDromeName;		           /* 起飞机场 */
	string sArrDromeName;       		       /* 降落机场 */
	string sAlternateDrome;	           /* 备降场 */
	int iCruiseLvl;		               /* 巡航高度(标准海压高度，单位：米) */
	int	iCruiseSpd;		               /* 巡航速度(表速或者马赫，表速单位：米/秒) */
	string sArrRunway;		           /* 降落跑道 */
	string sDepRunway;                  /* 起飞跑道*/
	string sWeight;		               /* 载重 */
	string sDepGate;		               /* 离场的停机位 */
	string sArrGate;		               /* 进场的停机位 */
	string sVacateLine;		           /* 脱离道 */
	string sInRunwayLine;               /* 进入道 */
	string sDepartureTime;		           /* 预计起飞时间*/
	string sArrivalTime;		           /* 预计到达时间*/
	string  sSidName;                     /*离场程序名称*/
	vector<string> vRoutePt;	      /* 航路点 ,航路点格式:xxx/kxxmxx,其中xxx表示导航台名，xx表示高度，以10米为单位，xx表示真速，单位km/h */
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iFlightPlanId & sSSRCode & bRVSM & iFlyPlanType &sSectorName& sCompany & sCallSign & sDepDromeName &
			sArrDromeName & sAlternateDrome & iCruiseLvl & iCruiseSpd & sArrRunway  &
			sDepRunway& sWeight & sDepGate & sArrGate & sVacateLine &
			sInRunwayLine & sDepartureTime & sArrivalTime  & sSidName  &
			vRoutePt;
	}
private:
	SERIALIZE_PACKET(iFlightPlanId & sSSRCode&bRVSM&iFlyPlanType&sSectorName&sCompany&sCallSign&sDepDromeName&sArrDromeName&sAlternateDrome&iCruiseLvl&iCruiseSpd&sArrRunway&sDepRunway
		&sWeight&sDepGate&sArrGate&sVacateLine&sInRunwayLine&sDepartureTime&sArrivalTime&sSidName&vRoutePt)
};

//动态创建目标计划包
class DynamicCreateFlightObjPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateFlightObjPacket);
public:
	ENUM_OBJ_TYPE   ObjType;              //类型
	string strSSrcode;               //关联飞行计的二次码
	double	dLongtitude;		        //出现的经度（单位：弧度）
	double	dLatitude;           	    //出现的纬度（单位：弧度）
	double 	dAltitude;		            //初始高度（标准海压高度，单位：米）
	double 	dHeading;		            //机头朝向（单位：弧度）
	double 	dIAS;			            //初始速度（表速，单位s：米/秒）
	string sAppearTime;		        //出现时间（单位：秒）
	string strModelType;	        //机型名
	string	strRegNum;		            //注册号
	bool 	bEngineStart;		        //引擎是否起动
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjType & strSSrcode & dLongtitude & dLatitude & dAltitude & dHeading &
			dIAS & sAppearTime & strModelType & strRegNum & bEngineStart;
	}
private:
	SERIALIZE_PACKET(ObjType&strSSrcode&dLongtitude&dLatitude&dAltitude&dHeading&dIAS&sAppearTime&strModelType&strRegNum&bEngineStart)
};

//动态创建飞机包
class DynamicCreateAircraftPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateAircraftPacket);
public:
	DynamicCreateFlightObjPacket ObjFlight;        //目标计划
	vector<DynamicCreateFlightPlanPacket> PlanFlight;         //关联的飞行计划
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjFlight & PlanFlight;
	}
private:
	SERIALIZE_PACKET(ObjFlight&PlanFlight)
};

//动态创建飞机回复包
class DynamicCreateAircraftAckPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateAircraftAckPacket);
public:
	vector<DynamicCreateFlightPlanPacket> PlanFlight;         //飞行计划
	int iObjId;            //目标计划id
	bool bOk;      //创建结果
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & PlanFlight &iObjId& bOk;
	}
private:
	SERIALIZE_PACKET(PlanFlight&iObjId&bOk)
};

//查询动态创建飞机包
class QueryDynamicCreateAircraftPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(QueryDynamicCreateAircraftPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};


struct ParkInfo
{
	int m_iParkBayID; //!< 停机位ID

	int m_iCurUseObjID; //!<当前使用停机位飞机ID
	std::string m_sCurUseObjCallsign; //!<当前使用停机位飞机呼号

	int m_iPlanUseObjID;//!< 计划使用当前停机位飞机ID
	std::string m_sPlanUseObjICallsign; //!<计划使用停机位飞机呼号
	std::string m_iCurUsePlaneType; //!<停机位实际使用飞机机型
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iParkBayID & m_iCurUseObjID & m_sCurUseObjCallsign & m_iPlanUseObjID
			& m_sPlanUseObjICallsign & m_iCurUsePlaneType ;
	}
};
//停机位信息更新包
class ParkingBayInfoACKPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ParkingBayInfoACKPacket);
public:
	std::vector<ParkInfo> m_vParkInfo;

private:
	SERIALIZE_PACKET(m_vParkInfo);
};

//分配停机位信息
class AssignParkingBayPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AssignParkingBayPacket);
public:
	int m_iParkBayID; //!< 停机位ID
	
	int m_iAssignObjID; //!<准备分配给停机位飞机ID
private:
	SERIALIZE_PACKET(m_iParkBayID&m_iAssignObjID);
};
//停机位分配回复包
class AssignParkingBayACKPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AssignParkingBayACKPacket);
public:
	bool m_bOK;               //是否分配失败
	std::string m_sAckMsg;//如果分配失败，回复失败原因
private:
	SERIALIZE_PACKET(m_bOK&m_sAckMsg);
};


//停机位查询更新包
class ReqTmpParkingBayPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ReqTmpParkingBayPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};