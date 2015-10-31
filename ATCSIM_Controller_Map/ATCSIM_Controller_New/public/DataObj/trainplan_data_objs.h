//此文件中定义训练计划相关的对象类，包括以下对象：
//训练计划                TrainPlan
//训练计划_飞行计划       TPFlyPlan
//训练计划                TrainPlanData （demo4结构，待以后删除）
//飞行计划                FlyPlanData    （demo4结构，待以后删除）

#ifndef _H_TRAINPLAN_DATA_OBJS_H
#define _H_TRAINPLAN_DATA_OBJS_H
#include "DataObj.h"
#include "assistance_data_objs.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"

class TrainPlan : public DataObj
{
public:
	TrainPlan();
	~TrainPlan();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	TrainPlan(const TrainPlan &trainPlan);
	TrainPlan& operator=(const TrainPlan& trainPlan);

    //boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_strTrainPlanName & m_iAirportID 
			& m_iAirportModelID & m_iEnvironmentID & m_strDate & m_iStartTime & m_bUnion 
			& m_iControllerNum & m_mapControllerSector & m_vObjPlan & m_vCloudPlan & m_vSmokePlan & m_vVehiclePlan & m_vSpecialEffectObjPlan
			 & m_vEnvPlan;
	}

public:
	int m_iTrainPlanID;							  /* 训练计划ID */
	std::string m_strTrainPlanName;	      /* 训练计划名称*/
	int m_iAirportID;								  /* 机场ID */
	int m_iAirportModelID;						  /* 机场模型ID */
	int m_iEnvironmentID;						  /* 环境参数ID */
	std::string m_strDate;						  /* 训练日期*/
	int m_iStartTime;								  /* 训练开始时间 从0点开始以秒计算 */     
	bool m_bUnion;								  /* 是否联合训练*/
	int m_iControllerNum;                        /* 需要的管制席位数*/
	std::map<int, std::vector<int> >  m_mapControllerSector;   /* 管制席位和扇区的对应关系*/
	vector<int> m_vObjPlan;						//目标计划，引用目标计划ID
	vector<int> m_vCloudPlan;					//云计划
	vector<int> m_vSmokePlan;					//烟计划
	vector<int> m_vVehiclePlan;					//车辆计划
	vector<int> m_vSpecialEffectObjPlan;  //特效运动物体计划
	vector<int> m_vEnvPlan;//环境参数计划
};

/*----------------训练计划-飞行计划----------------------*/
class TPFlyPlan : public DataObj
{
public:
	TPFlyPlan();
	~TPFlyPlan();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	TPFlyPlan(const TPFlyPlan &flyPlan);
	TPFlyPlan& operator=(const TPFlyPlan& flyPlan);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlyPlanID & m_iObjPlanID &m_strFlyPlanName 
			& m_strSSRCode & m_iSectorID & m_iControllerID & m_iPilotID & m_bAutoTakeoff 
			& m_bRVSM & m_iFlyPlanType & m_iCompanyID & m_strCallSign 
			& m_iDepDromeID & m_iArrDromeID & m_iAlternateDromeID 
			& m_dFuelTime & m_dCruiseLvl & m_dCruiseSpd & m_iArrRunwayID 
			& m_iDepRunwayID & m_iWeight & m_iDepGateID & m_iArrGateID 
			& m_iVacateLineID & m_iInRunwayLineID & m_iDepartureTime 
			& m_iArrivalTime & m_strRemark & m_vecRoutePt;
	}

public:
	int m_iFlyPlanID;                    /* 飞行计划ID */
	string m_strFlyPlanName;             /* 飞行计划名称 */
	string m_strSSRCode;                 /*  二次码 */
	int m_iObjPlanID;				  /* 飞行计划目标ID*/
	int m_iSectorID;                   //所属管制扇区
	int m_iControllerID;                 /* 所属管制员席位ID */
	int m_iPilotID;                      /* 所属机长席位ID */
	bool m_bAutoTakeoff;		         /* 是否自动起飞*/
	bool m_bRVSM;			             /* 是否具备RVSM能力*/

	//以下是飞行计划模板中的内容，在训练计划中可做修改
	int	m_iFlyPlanType;	                 /* 飞行计划类型 0 进港，1 离港 ，2 飞跃*/
	int	m_iCompanyID;		             /* 航空公司 */
	string 	m_strCallSign;		         /* 呼号（航空公司+数字编码）*/
	int	m_iDepDromeID;		             /* 起飞机场 */
	int	m_iArrDromeID;       		     /* 降落机场 */
	int	m_iAlternateDromeID;	         /* 备降场 */
	int m_dFuelTime;		             /* 燃油时间(单位：秒) */
	int m_dCruiseLvl;		             /* 巡航高度(标准海压高度，单位：米) */
	int	m_dCruiseSpd;		             /* 巡航速度(表速或者马赫，表速单位：米/秒) */
	int	m_iArrRunwayID;		             /* 降落跑道 */
	int m_iDepRunwayID;                  /* 起飞跑道*/
	int	m_iWeight;		                 /* 载重 */
	int	m_iDepGateID;		             /* 离场的停机位 */
	int	m_iArrGateID;		             /* 进场的停机位 */
	int m_iVacateLineID;		         /* 脱离道ID */
	int m_iInRunwayLineID;               /* 进入道ID */
	int m_iDepartureTime;		         /* 预计起飞时间（单位：秒）*/
	int m_iArrivalTime;		             /* 预计到达时间（单位：秒）*/
	string m_strRemark;		             /* 备注信息 */
	vector<boost::shared_ptr<RoutePt> > m_vecRoutePt;	     /* 航路点 */

};

//飞机目标计划
class ObjPlan : public DataObj
{
public:
	ObjPlan();
	~ObjPlan();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//拷贝、赋值函数
	ObjPlan(const ObjPlan &objPlan);
	ObjPlan& operator=(const ObjPlan& objPlan);
	//boost序列化
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iObjPlanID &m_iTrainPlanID & m_strRegNum & m_strSSRCode 
			& m_iAppearTime & m_iAircraftTypeID & m_dLongtitude 
			& m_dLatitude & m_dAltitude & m_dHeading & m_dIAS 
			& m_strCmd & m_bEngineStart &m_vFlyPlan;
	}

	int     m_iObjPlanID;		//飞行计划ID（一个飞机全程可关联多个飞行计划，但同一时间只能关联一个，即一对一的关系）
	int m_iTrainPlanID;             /* 训练计划ID */
	string	m_strRegNum;		//注册号
	string 	m_strSSRCode;		//二次码xx
	int   	m_iAppearTime;		//飞机出现时间（单位：秒）
	int	m_iAircraftTypeID;	//机型
	double	m_dLongtitude;		//飞机出现的经度（单位：弧度）
	double	m_dLatitude;           	//飞机出现的纬度（单位：弧度）
	double 	m_dAltitude;		//飞机的初始高度（标准海压高度，单位：米）
	double 	m_dHeading;		//机头朝向（单位：弧度）
	double 	m_dIAS;			//初始速度（表速，单位：米/秒）
	string  m_strCmd;			//命令队列
	bool 	m_bEngineStart;		//引擎是否起动
	vector<int> m_vFlyPlan;     //一个目标计划下的飞行计划

};

/*-----------------训练计划------------*/
class TrainPlanData : public DataObj
{
public:
	int m_iTrainPlanID;		        /* 训练计划ID */
	std::string m_szTrainPlanName;  /* 训练计划名*/

	TrainPlanData();
	~TrainPlanData();

	//拷贝、赋值函数
	TrainPlanData(const TrainPlanData &trainPlanData);
	TrainPlanData& operator=(const TrainPlanData& train_plan_data);
	bool operator==(DataObj *dataobj);


	int GetId();
	std::string GetDisplayLabel();

	bool IsEqual(DataObj *dataobj);
	void Copy(DataObj *dataobj);


	//Set方法


	//Get方法



	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_szTrainPlanName;
	}
};


/*----------------车辆计划-----------------*/
class VehiclePlan  : public DataObj
{
public:
	VehiclePlan();
	~VehiclePlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	VehiclePlan(const VehiclePlan & vehiclePlan);
	VehiclePlan& operator=(const VehiclePlan & vehiclePlan);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar &m_iTrainPlanID	& m_iVehiclePlanId & m_strVehiclePlanName & m_strCallsign               
			& m_iVehicleId & m_iSectorId & m_eVehiclePlanType & m_eBelongedType        			
			& m_iBelongedId & m_iAppearTime & m_dLongitude & m_dLatitude				
			& m_dHeading& m_dSpeed &m_bEngineStart & m_strCmd & m_strRemark ;
	}


public:
	int    m_iTrainPlanID		; //训练计划ID
	int 	m_iVehiclePlanId     ; //车辆计划ID
	string 	m_strVehiclePlanName   ; //车辆计划名称
	string 	m_strCallsign              ; //车辆计划呼号
	int	m_iVehicleId             ; //车辆性能ID
	int	m_iSectorId				; //扇区ID
	int	m_eVehiclePlanType		; //车辆计划类型0 = 场内车辆，1= 场外车辆
	int	m_eBelongedType			; //本计划中使用的车辆所属类型，表示机场；表示航空公司
	int	m_iBelongedId			; //根据所属类型iBelongedType 确定所属单位，为0 表示机场ID；1表示航空公司ID
	int	m_iAppearTime			; //出现时间
	double	m_dLongitude				; //经度
	double	m_dLatitude				; //纬度
	double	m_dHeading				; //朝向
	double	m_dSpeed					; //速度
	bool	m_bEngineStart			; //引擎是否启动
	string	m_strCmd					; //命令
	string	m_strRemark                ; //备注
};

class FlyPlanData : public DataObj
{
public:
	int m_iTrainPlanID;		    /* 训练计划ID */
	int m_iFlyPlanID;			/* 飞行计划ID, 是从该飞行计划中复制过来的计划 下面的内容有可能和原来的值不一致 */
	std::string m_szFlyPlanName;
	std::string m_szSignName;
	double m_dX;                    /* 飞机出现的位置 X坐标 默认0 使用经纬度*/
	double m_dY;					/* Y坐标 默认0 使用经纬度*/
	double m_dZ;					/* Z坐标 默认0 使用经纬度*/
	double m_dHeading;			    /* 机头朝向 默认0 */
	double m_dSpeed;				/* 初始速度*/
	int m_iAircraftID;			    /* 机型*/

	FlyPlanData();
	~FlyPlanData();
	FlyPlanData(const FlyPlanData &flyPlanInfo);
	FlyPlanData& operator=(const FlyPlanData& flyPlanInfo);

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	bool IsEqual(DataObj *dataobj);
	void Copy(DataObj *dataobj);


	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iFlyPlanID & m_szFlyPlanName & m_szSignName 
			& m_dX & m_dY & m_dZ & m_dHeading & m_dSpeed & m_iAircraftID; 
	}
};



/*----------------训练计划-飞行计划（发给客户端）----------------------*/
/*! 
\brief     FPL信息结构体（与TPFlyPlan对应）
\details   提供经过封装后的FPL数据，而非直接提供数据表中的数据
\author    lijin
\date      2013-05-28
*/
class FplInfo : public DataObj
{
public:
	FplInfo();
	~FplInfo();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	FplInfo(const FplInfo & flyPlan);
	FplInfo& operator=(const FplInfo & flyPlan);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlyPlanID & m_strFlyPlanName 
			& m_strSSRCode & m_strSector & m_iControllerID & m_iPilotID & m_bAutoTakeoff 
			& m_bRVSM & m_iFlyPlanType & m_strCompanyName & m_strCallSign 
			& m_strDepDrome & m_strArrDrome & m_strAlternateDrome 
			& m_nFuelTime & m_nCruiseLvl & m_nCruiseSpd & m_strArrRunwayName 
			& m_strDepRunwayName & m_iWeight & m_strDepGateName & m_strArrGateName 
			& m_strVacateLineName & m_strInRunwayLineName & m_tDepartureTime 
			& m_tArrivalTime & m_strRemark & m_vecRoutePtNames;
	}

public:
	int		m_iFlyPlanID;                 /* 飞行计划ID */
	string	m_strFlyPlanName;             /* 飞行计划名称 */
	string	m_strSSRCode;                 /*  二次码 */
	string	m_strSector;                  //所属管制扇区
	int		m_iControllerID;              /* 所属管制员席位ID */
	int		m_iPilotID;                   /* 所属机长席位ID */
	bool	m_bAutoTakeoff;				  /* 是否自动起飞*/
	bool	m_bRVSM;					  /* 是否具备RVSM能力*/

	//以下是飞行计划模板中的内容，在训练计划中可做修改
	int		m_iFlyPlanType;	              /* 飞行计划类型 */
	string  m_strCompanyName;			  /* 航空公司 */
	string 	m_strCallSign;		          /* 呼号（航空公司+数字编码）*/
	string  m_strDepDrome;		          /* 起飞机场 */
	string  m_strArrDrome;       		  /* 降落机场 */
	string  m_strAlternateDrome;	      /* 备降场 */

	int     m_nFuelTime;		          /* 燃油时间(单位：秒) */
	int     m_nCruiseLvl;		          /* 巡航高度(标准海压高度，单位：米) */
	int		m_nCruiseSpd;		          /* 巡航速度(表速或者马赫，表速单位：米/秒) */
	string  m_strArrRunwayName;		      /* 降落跑道 */
	string  m_strDepRunwayName;           /* 起飞跑道*/
	int		m_iWeight;					  /* 载重 */
	string  m_strDepGateName;		      /* 离场的停机位 */
	string  m_strArrGateName;		      /* 进场的停机位 */

	string  m_strVacateLineName;		  /* 脱离道 */
	string  m_strInRunwayLineName;          /* 进入道 */
	time_t  m_tDepartureTime;		      /* 预计起飞时间（单位：秒）*/
	time_t  m_tArrivalTime;		          /* 预计到达时间（单位：秒）*/
	string	m_strRemark;		          /* 备注信息 */
	vector<std::string> m_vecRoutePtNames;/* 航路点名称 */
};

/*! 
\brief     云的类型
\details   
\author    JZH
\date      2013-06-04
*/
enum ENUM_CLOUD_TYPE
{
	ECT_DEFAULT_YUN = 0,  //默认的云
	ECT_CENG_YUN,     //层云
	ECT_JUAN_YUN,     //卷云
	ECT_DAN_JI_YUN,   //淡积云
	ECT_NONG_JI_YUN,  //浓积云
	ECT_JIYU_YUN,      //积雨云
};

/*! 
\brief     云计划
\details   训练计划中包括的云计划
\author   JZH
\date      2013-06-04
*/
class CloudPlan: public DataObj
{
public:
	CloudPlan();
	~CloudPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCloudID & m_strCloudName & m_eCloudType & m_iTrainPlanID 
			& m_dLongitude & m_dLatitude & m_dZ & m_dSize; 
	}
public:

	int m_iCloudID;		//!<云ID
	std::string m_strCloudName;  //!< 云名称
	ENUM_CLOUD_TYPE m_eCloudType;	//!<云类型
	int m_iTrainPlanID;	//!<训练计划ID
	double m_dLongitude;//!<云团的经度
	double m_dLatitude;	//!<云图的纬度
	double m_dZ;		//!<云图高度
	double m_dSize;		//!<云图直径大小
};

/*! 
\brief     烟的类型
\details   
\author    JZH
\date      2013-06-04
*/
enum SMOKE_TYPE
{
	EST_JIEGAN = 0,	//!<秸秆烟
};

/*! 
\brief     烟计划
\details   训练计划中包括的烟计划
\author    JZH
\date      2013-06-04
*/
class SmokePlan: public DataObj
{
public:
	SmokePlan();
	~SmokePlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSmokeID & m_strSmokeName & m_eSmokeType & m_iTrainPlanID 
			& m_dLongitude & m_dLatitude & m_dZ & m_dSize; 
	}	
public:

	int m_iSmokeID;		//!<烟ID
	std::string m_strSmokeName; //!< 烟名称
	SMOKE_TYPE m_eSmokeType;	//!<烟类型
	int m_iTrainPlanID;	//!<训练计划ID
	double m_dLongitude;//!<烟的经度
	double m_dLatitude;	//!<烟的纬度
	double m_dZ;		//!<烟的高度
	double m_dSize;		//!<烟的直径大小
};

/*! 
\brief     雾的类型
\details   
\author    JZH
\date      2013-06-04
*/
enum FOG_TYPE
{
	EFT_NONE = 0,	//!<无雾
	EFT_PINGLIU,	//!<平流雾
	EFT_FUSHE		//!<辐射雾
};



/*! 
\brief     特效运动物体计划
\details  
\author	   ZY
\date      2013-06-24
\modifer   DXQ 2013-06-24
*/
class SpecialEffectObjPlan : public DataObj
{
public:
	SpecialEffectObjPlan();
	~SpecialEffectObjPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	SpecialEffectObjPlan(const SpecialEffectObjPlan & effectObjPlan);
	SpecialEffectObjPlan& operator=(const SpecialEffectObjPlan & effectObjPlan);

public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iObjPlanId & m_eObjType & m_strName 
			& m_dLongitude & m_dLatitude & m_dAltitude & m_dSpeed & m_vecRoute & m_bLoop; 
	}

public:
	int m_iTrainPlanID;				//训练计划ID
	int m_iObjPlanId;				//特效物体id
	ENUM_OBJ_TYPE m_eObjType;		//特效物体具体类型
	string m_strName;				//特效物体名字
	double	m_dLongitude;			//经度（单位：弧度）
	double	m_dLatitude;			//纬度
	double 	m_dAltitude;			//初始高度（单位：米）
	double	m_dSpeed;				//速度(单位:km/h) 
	vector<stPoint> m_vecRoute;		//运动路径名(经纬度指定)
	bool m_bLoop;					//路径是否循环
};

/*!
\brief  特效运动物体经过的轨迹点
\details  
\author CX
\date 2013/06/29
*/
class RoutePointPosition : public DataObj
{
public:
	RoutePointPosition();
	~RoutePointPosition();
	virtual int GetOwnerId();
	void SetSequence(int iSeq);  //为了用于designer的模版类增加
	int GetSequence();			   //为了用于designer的模版类增加

	int m_iSequence;		//点的序号
	int m_iOwnerID;		//点所属特效运动物体计划的ID
	stPoint m_stPosion;  //点的位置
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iOwnerID & m_iSequence & m_stPosion;
	}
};


/*! 
\brief     环境子对象分类
\details   
\author    DXQ
\date      2013-06-25
*/
enum ENUM_ENV_OBJ_TYPE 
{
	ENV_OBJ_NONE = -1,				//未知类型
	ENV_OBJ_RAIN,					//雨
	ENV_OBJ_SNOW,					//雪
	ENV_OBJ_VISIBILITY,				//能见度
	ENV_OBJ_TEMPERATURE,			//温度
	ENV_OBJ_DEWPOINT,				//露点
	ENV_OBJ_DUST,					//尘
	ENV_OBJ_RISENDUST,					//扬沙
	ENV_OBJ_QNH,					//海压
	ENV_OBJ_HAZE,					//霾
	ENV_OBJ_FOG,					//雾
	ENV_OBJ_LIGHTINGT,				//闪电
	ENV_OBJ_WIND,					//风
	ENV_OBJ_QFE,					//气压
	ENV_OBJ_SMOKE,					//烟
	ENV_OBJ_SPECIALEFFECTOBJ,		//特效运动物体

};



/*! 
\brief     环境子对象在某一时间段内的计划
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvObjectPhasePlan : public DataObj
{
public:
	EnvObjectPhasePlan();
	~EnvObjectPhasePlan();

	//拷贝、赋值函数
	EnvObjectPhasePlan(const EnvObjectPhasePlan & envObjectPhasePlan);
	EnvObjectPhasePlan& operator=(const EnvObjectPhasePlan & envObjectPhasePlan);

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_dTimePoint & m_iLevel & m_bPhasePlanOn & m_dWindSpeed & m_dWindDirection 
			& m_dLightingDirection & m_dLightingRadious & m_dQFE & m_dSmokeDensity & m_dTemprature& m_dQNH & m_dRVR & m_dDewPoint; 
	}

public:
	double m_dTimePoint;			//相对开始时间的时间计数
	int m_iLevel;					//等级,EnvObjectPlan对象中的m_eEnvObjectType取值如下时，此值有意义
									//ENV_OBJ_RAIN,					//雨
									//ENV_OBJ_SNOW,					//雪
									//ENV_OBJ_DEWPOINT,				//露点
									//ENV_OBJ_DUST,					//尘
									//ENV_OBJ_RISENDUST,		//扬沙
									//ENV_OBJ_QNH,					//海压
									//ENV_OBJ_HAZE,					//霾
									//ENV_OBJ_FOG,					//雾
									//ENV_OBJ_LIGHTINGT,			//闪电
	bool m_bPhasePlanOn;			//该时间段内的计划是否可用。EnvObjectPlan对象中的m_eEnvObjectType取值如下时，此值有意义
									/*	
									ENV_OBJ_DUST,					//尘
									ENV_OBJ_RISENDUST,					//扬沙
									ENV_OBJ_HAZE,					//霾
									ENV_OBJ_FOG,					//雾
									ENV_OBJ_LIGHTINGT,				//闪电
									ENV_OBJ_SMOKE,					//烟*/
									
	double m_dWindSpeed;			//风速，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_WIND时，此值有意义
	double m_dWindDirection;		//风向，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_WIND时，此值有意义
	double m_dLightingDirection;	//闪电风位，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_LIGHTINGT时，此值有意义
	double m_dLightingRadious;		//闪电距离，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_LIGHTINGT时，此值有意义
	double m_dQFE;					//气压，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_QFE时，此值有意义
	double m_dSmokeDensity;			//烟的密度，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_SMOKE时，此值有意义
	double m_dTemprature;			//温度值，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_TEMPERATURE时，此值有意义
	double m_dQNH;						//海压值，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_QNH时，此值有意义
	double m_dRVR;						//能见度,EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_VISIBILITY时，此值有意义
	double m_dDewPoint;				//露点，EnvObjectPlan对象中的m_eEnvObjectType为ENV_OBJ_DEWPOINT时，此值有意义
};


/*! 
\brief     环境子对象计划
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvObjectPlan : public DataObj
{
public:
	EnvObjectPlan();
	~EnvObjectPlan();

	//拷贝、赋值函数
	EnvObjectPlan(const EnvObjectPlan & envObjectPlan);
	EnvObjectPlan& operator=(const EnvObjectPlan & envObjectPlan);

	int GetId();
	int GetOwnerId();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iEnvPlanID & m_iEnvObjectPlanID & m_eEnvObjectType & m_dStartTime 
			& m_dEndTime & m_vecEnvObjectPhasePlan; 
	}

public:
	int m_iEnvPlanID;					//环境计划ID
	int m_iEnvObjectPlanID;				//环境子对象计划ID
	ENUM_ENV_OBJ_TYPE m_eEnvObjectType;//环境子对象类别，取值如下：
										/*	ENV_OBJ_RAIN,				//雨
										ENV_OBJ_SNOW,					//雪
										ENV_OBJ_VISIBILITY,				//能见度
										ENV_OBJ_TEMPERATURE,			//温度
										ENV_OBJ_DEWPOINT,				//露点
										ENV_OBJ_DUST,					//尘
										ENV_OBJ_RISENDUST,					//扬沙
										ENV_OBJ_QNH,					//海压
										ENV_OBJ_HAZE,					//霾
										ENV_OBJ_FOG,					//雾
										ENV_OBJ_LIGHTINGT,				//闪电
										ENV_OBJ_WIND,					//风
										ENV_OBJ_QFE,					//气压
										ENV_OBJ_SMOKE,					//烟*/

	double m_dStartTime;				//计划开始时间
	double m_dEndTime;					//计划结束时间
	std::vector<EnvObjectPhasePlan> m_vecEnvObjectPhasePlan;	//不同时刻的环境子对象计划vector
};


/*! 
\brief     环境子对象计划——跑道环境计划
\details   
\author    DXQ
\date      2013-06-25
*/
class RunwayEnvPlan : public DataObj
{
public:
	RunwayEnvPlan();
	~RunwayEnvPlan();

	//拷贝、赋值函数
	RunwayEnvPlan(const RunwayEnvPlan & runwayEnvPlan);
	RunwayEnvPlan& operator=(const RunwayEnvPlan & runwayEnvPlan);

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iEnvPlanID & m_iRunwayID & m_dTemperatureRatio 
			& m_dDewpointRatio & m_dWindSpdRatio & m_dWindDirRatio & m_dQNHRatio & m_dQFERatio; 
	}

public:
	int m_iAirportID;				/* 机场ID*/
	int m_iEnvPlanID;				/* 环境计划ID*/
	int m_iRunwayID;				/* 跑道ID */ 

	double m_dTemperatureRatio;		/* 温度偏差比率默认1*/
	double m_dDewpointRatio;		/* 露点偏差比率默认1*/
	double m_dWindSpdRatio;			/* 风速变化偏差比默认1*/
	double m_dWindDirRatio;			/* 风向偏移默认0*/
	double m_dQNHRatio;				/* 修正海压偏差比率默认1*/		
	double m_dQFERatio;				/* 场压偏差比率默认1*/
};


/*! 
\brief     环境计划
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvPlan : public DataObj
{
public:
	EnvPlan();
	~EnvPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	EnvPlan(const EnvPlan & envPlan);
	EnvPlan& operator=(const EnvPlan & envPlan);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iEnvPlanID & m_strEnvPlanName & m_RainPlan 
			& m_SnowPlan & m_RVRPlan & m_TempraturePlan & m_DewPointPlan & m_DustPlan & m_RisenDustPlan & m_QNHPlan & m_HazePlan
			& m_FogPlan & m_LightingPlan & m_WindPlan & m_QFEPlan & m_SmokePlan & m_RunwayEnvPlan & m_SpecialEffectObjPlan; 
	}

public:
	int m_iTrainPlanID;					//训练计划ID
	int m_iEnvPlanID;					//环境计划ID
	std::string m_strEnvPlanName;		//环境计划名称
	RunwayEnvPlan m_RunwayEnvPlan;		//环境子对象计划——跑道环境计划
	EnvObjectPlan m_RainPlan;			//环境子对象计划——雨计划
	EnvObjectPlan m_SnowPlan;			//环境子对象计划——雪计划
	EnvObjectPlan m_RVRPlan;			//环境子对象计划——能见度计划
	EnvObjectPlan m_TempraturePlan;		//环境子对象计划——温度计划
	EnvObjectPlan m_DewPointPlan;		//环境子对象计划——露点计划
	EnvObjectPlan m_DustPlan;			//环境子对象计划——尘计划
	EnvObjectPlan m_RisenDustPlan;			//环境子对象计划——扬沙计划
	EnvObjectPlan m_QNHPlan;			//环境子对象计划——海压计划
	EnvObjectPlan m_HazePlan;			//环境子对象计划——霾计划
	EnvObjectPlan m_FogPlan;			//环境子对象计划——雾计划
	EnvObjectPlan m_LightingPlan;		//环境子对象计划——闪电计划
	EnvObjectPlan m_WindPlan;			//环境子对象计划——风计划
	EnvObjectPlan m_QFEPlan;			//环境子对象计划——气压计划
	EnvObjectPlan m_SmokePlan;			//环境子对象计划——烟计划
	EnvObjectPlan m_SpecialEffectObjPlan; //环境子对象计划——特效运动物体计划
};


/*! 
\brief     环境参数
\details   
\author    JZH
\date      2013-06-04
*/
class EnvData: public DataObj
{
public:
	EnvData();
	~EnvData();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRainLevel & m_iSnowLevel & m_enumFogType & m_dVis 
			& m_dSunRiseTime & m_dSunSetTime & m_strTerrainName & m_dTerrainPosX & m_dTerrainPosY & m_dTerrainPosZ
			& m_iVaneX & m_iVaneY & m_iDogVaneX & m_iDogVaneY; 
	}	
public:

	int m_iRainLevel;		//!<雨量，分1~3级，0代表无雨
	int m_iSnowLevel;		//!<雪量，分1~3级，0代表无雪
	FOG_TYPE m_enumFogType;	//!<0 = 无雾，1 = 平流雾，2=辐射雾 默认0
	double m_dVis;			//!<能见度

	double m_dSunRiseTime;	//!<日出时间
	double m_dSunSetTime;	//!<日落时间

	std::string m_strTerrainName;	//!<地形名字
	double  m_dTerrainPosX;	//!<地形坐标
	double  m_dTerrainPosY;	//!<地形坐标
	double  m_dTerrainPosZ;	//!<地形坐标
	int m_iVaneX;		//!<
	int m_iVaneY;		//!<
	int m_iDogVaneX;	//!<
	int m_iDogVaneY;	//!<
};




/*!
\brief  目标计划类型（用于视景）
\details  
\author DXQ
\date 2013/6/19
*/
enum ENUM_PLAN_TYPE
{
	PLAN_TYPE_AIRCRAFT = 0,	//目标计划
	PLAN_TYPE_VEHICLE,		//车辆计划
};


/*! 
\brief     目标计划（为视景使用）
\details   因为视景需要的目标计划的内容不多，为了减少网络包的大小，特写此类。
\author    JZH
\date      2013-06-04
\modifer   DXQ 2013-06-19
*/
class ObjPlanForVis: public DataObj
{
public:
	ObjPlanForVis();
	~ObjPlanForVis();

	int GetId();
	string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_eObjPlanType & m_iObjPlanID & m_iObjID & m_strCallSign & m_strCompanyName; 
	}	
public:
	ENUM_PLAN_TYPE	m_eObjPlanType;	//计划类型
	int	m_iObjPlanID;				//m_eObjPlanType 为PLAN_TYPE_AIRCRAFT时，代表视景要创建的目标计划ID，对应训练计划中的目标计划的ID
									//m_eObjPlanType 为PLAN_TYPE_VEHICLE时， 代表视景要创建的车辆计划ID，对应训练计划中的车辆计划的ID
	int m_iObjID;					//m_eObjPlanType 为PLAN_TYPE_AIRCRAFT时，代表机型ID，表示是哪种机型，引用AircraftForVis中的m_iAircraftID
									//m_eObjPlanType 为PLAN_TYPE_VEHICLE时,  代表车辆ID，表示是哪种车辆，引用VehicleForVis中的m_iVehicleID
	std::string	m_strCallSign;		//m_eObjPlanType 为PLAN_TYPE_AIRCRAFT时，如果目标计划挂了多个飞行计划，那此处保存第一个飞行计划的呼号
									//m_eObjPlanType 为PLAN_TYPE_VEHICLE时,	 车辆计划呼号
	std::string	m_strCompanyName;	//m_eObjPlanType 为PLAN_TYPE_AIRCRAFT时，所属公司名称，如果目标计划挂了多个飞行计划，那此处保存第一个飞行计划的所属公司名称
									//m_eObjPlanType 为PLAN_TYPE_VEHICLE时， 值没有意义
};

/*!
\brief     灯光计划
\details   设置在某个训练计划中的灯光开关情况。
\author    JZH
\date      2013-06-25
*/
class LightPlan: public DataObj
{
public:
	LightPlan();
	~LightPlan();
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightPlanID & m_iTrainPlanID & m_szLightPlanName & m_iLightCollectionID & m_iLightLevel;
	}
public:
	int m_iLightPlanID;	//!<灯光计划的ID
	int m_iTrainPlanID;	//!<训练计划ID
	std::string m_szLightPlanName;	//!<灯光计划名称
	int m_iLightCollectionID;	//!<灯光组组合ID
	int m_iLightLevel;	//!<灯光等级（0到5,0为关闭）
};

#endif