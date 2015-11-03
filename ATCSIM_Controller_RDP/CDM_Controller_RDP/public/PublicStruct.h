/*********************************************************************
 * Copyright(c) Reserved, WiseSoft Corporation.
 *   FileName: CDM_GlobalVariable.h
 *     Author: 陈文平
 *       Date: 2014/08/31
 *Description: 程序所用到的公共结构定义
 ********************************************************************/
#ifndef CDM_GLOBALVARIABLE_H
#define CDM_GLOBALVARIABLE_H
#include <QMetaType>
#include <QString>
#include<vector>
#include <string>
#define M_PI       3.14159265358979323846
namespace PublicDataStruct
{
	const int   BUFFERSZE=4096;
	const int	SENDFLIGHTPLANUDPPORT	= 10000;//发送飞行计划的UDP端口号
	const int	RECVFLIGHTPLANIDPORT	= 9902; //接收航班ID的UDP端口号
	const int	SENDCOMMANDUDPPORT		= 9901; //发送命令的UDP端口号
	const int	RECVFLYPLANPORT			= 9903; //接收飞行计划的UDP端口，来自CDM系统，和CDM保持一致
	const int   SENDAIRCRAFTTRACEPORT	= 13000;//发送航迹的UDP端口
	// 计划的状态:未来(收到PLN)、静止(收到FPL)、预激活(预计起飞时间前半小时)、协调、移交、控制、完成、取消
	enum PLAN_STATUS{FUTR=0, NACT=1, PREA=2, COOR=3, HAND=4, CONT=5, FIN=6, CNL=7};
	//航站楼信息
	enum PLAN_TERMINATE{T1_TERMINATE=0,T2_TERMINATE};
	//目标类型，常用为OT_PLAN
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
	//飞行计划类型
	enum ENUM_PLAN_TYPE
	{
		
		CDM_ARR_PLAN=0,			//进场计划
		CDM_DEP_PLAN,			//离场计划
	};
	//! 航迹类型
	enum ENUM_TRACKTYPE
	{
		TRACKTYPE_INVALID,
		TRACKTYPE_INAIR,
		TRACKTYPE_ONGROUND,
	};
	//! 高度类型
	enum ENUM_AltitudeType
	{
		ALTTYPE_INVALID,
		ALTTYPE_QNE,    //标压
		ALTTYPE_QFE,    //场压高度
		ALTTYPE_QNH,   //海压高度
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
	//雷达信号类型
	enum RADAR_SIGNAL_TYPE
	{
		SIGNAL_NONE = 0, //未被扫描到
		SIGNAL_PRIMARY,  //一次雷达信号
		SIGNAL_SECONDARY,//二次雷达信号
		SIGNAL_ADSB,	 //ADSB雷达信号，暂无概念归类
		SIGNAL_COMBINED  //一二次雷达融合信号
	};
	enum HMI_STAT
	{
		HMI_NONE = 0,
		HMI_UNCONCERN,
		HMI_PREA,
		HMI_HND_IN,
		HMI_ANNOUNCE,
		HMI_HND_OUT,
		HMI_JURI,
	};
	//飞行计划来源
	enum PLAN_SOURCE
	{
		LPL = 0, //本地编辑 
		RPL,	 //重复性飞行计划		
		TELE,	 //飞行计划报 	
		STL,     //模板飞行计划
		TAG      //简标牌
	};
	// 飞行类型：未知、       区域外-入港、		 区域内-入港、		  区域外-出港、	   区域内-出港、 本场迂回(飞出飞入)
	enum CPL_TYPE{ UNKNOWN=0, EXTERNAL_INBD,	 DOMES_INBD,		  EXTERNAL_OUTBD,  DOMES_OUTBD,	 BYPASS,
		//					   区域外-其他机场入港、 区域外-其他机场出港、区域内-其他机场之间飞行、	区域内其他机场迂回(飞出飞入)						 
		EXTERNAL_ADP_INBD,	 EXTERNAL_ADP_OUTBD,  DOMESTIC,					DOMES_BYPASS, 	
		//						飞越管制区
		OVERFLY };
	//与航迹配对的状态：没有配对、丢失配对、     人工配对、     人工去配对、    自动配对	、自动去配对
	enum PAIR_STATUS{NOTCOUPLE=0, LOSSCOUPLE, MANUALCOUPLE, DEMANUALCOUPLE, AUTOCOUPLE, DEAUTOCOUPLE};
	enum RVSM_STATUS{
		RVSM_RVA = 0, 					//获准RVSM运行
		RVSM_RVN, 						//未获准RVSM运行
		RVSM_RVX, 						//豁免RVSM运行
		RVSM_RVU, 						//未知是否获准RVSM运行
		RVSM_RVT 						//由于气流/故障等影响取消RVSM
	};

	//航路点位置类型：区域内，  入界点， 出界点， 区域外
	enum RPP_TYPE { RPP_IN = 0, RPP_BPN, RPP_BPX, RPP_OUT};
	class FplListItemInfo
	{
	public:
		int m_nAcftID;
		std::string m_strMid;        //唯一标识符
		int         m_nRowID;        //保存该条信息显示的行号

		std::string m_strType;
		std::string m_strACID;       //呼号
		std::string m_strSSR;        //二次码
		std::string m_strPSource;    //计划来源
		std::string m_strPState;     //计划状态
		std::string m_strHMIState;   //人机界面状态
		std::string m_strCouple;
		std::string m_strRadarID;
		std::string m_strTrackID;
		std::string m_strFplType;
		std::string m_strADDep;
		std::string m_strEtd;
		std::string m_strAtd;
		std::string m_strAddArr;
		std::string m_strETA;
		std::string m_strATA;
		std::string m_strCtrlSec;
		std::string m_strCurSec;
		std::string m_strAcpSec;
		std::string m_strNextSec;
		std::string m_strBPN;
		std::string m_strETN;
		std::string m_strBPX;
		std::string m_strETX;
	};

	//飞行计划静态部分
	struct ST_FDP_FLIGHTPLAN_STATIC
	{
		std::string curMID;         //计划ID:年月日[8]+航班号[7/6]+起飞机场[4]＋降落机场[4]

		//计划总体信息
		std::string CplDate;        //计划执行日期(年月日[8])
		PLAN_SOURCE	CplSrc;      	//计划来源
		CPL_TYPE	CplType;	    //飞行计划类型

		//飞行描述
		std::string CallSign;  	    //呼号
		std::string	ASSR;        	//ASSR码
		std::string FlyRule;     	//飞行规则
		std::string FlyType;     	//飞行种类用途
		short AcftNum;              //架次
		std::string AcftType;  	    //飞机类型
		short AcftClass;        	//飞机所属级别 0 - A; 1 - B; 2 - C; 3 - C1; 4 - C2; 5 - C3...
		std::string Turbo;	      	//尾流
		std::string AcftRegst;	    //飞机注册号
		std::string SelSign;   	    //选呼
		std::string WirelessEp;		//无线电通信设备
		std::string SurveilEp;		//监视设备
		std::string SUP;	  		//计划附加信息
		std::string OTHER;    		//对应AFTN报18分组内容
		std::string OP_DATA; 	    //标牌上的OP_DATA信息

		//起飞降落信息
		std::string ADDEP;	  	    //起飞机场
		std::string ETD;	      	//预计起飞时间
		std::string ADARR;	  	    //落地机场
		std::string ALTN1;	  	    //备降机场1
		std::string ALTN2;     	    //备降机场2
		std::string EET;	      	//预计飞行时间
		std::string ETA;       	    //预计到达时间
		//其他信息
		std::string TAS;	      	//预计巡航速度
		std::string RFL;	      	//预计巡航高度层
		std::string RouteStr;    	//计划航路串
		std::string	BPN;            //入界点
		std::string	ETN;            //入界时间
		std::string	BPX;            //出界点
		std::string	ETX;	     	//出界时间
		std::string GATE;     	    //停机位
		std::string ARWY;	      	//入场跑道	
		std::string DRWY;	      	//离场跑道
		std::string SID;	      	//标准离场过程	
		std::string STAR;	      	//标准进场过程
		std::string GlobalInfo;     //全局信息
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar, const unsigned int version)
		{
			return ar & curMID & CplDate & CplSrc & CplType & CallSign 
				& ASSR & FlyRule & FlyType & AcftNum & AcftType & AcftClass & Turbo 
				& AcftRegst & SelSign & WirelessEp & SurveilEp & SUP & OTHER 
				& OP_DATA & ADDEP & ETD & ADARR & ALTN1 & ALTN2 & EET & ETA
				& TAS & RFL & RouteStr & BPN & ETN &BPX & ETX & GATE & ARWY 
				& DRWY & SID & STAR & GlobalInfo; 
		}
	};
	//进程单航路点
	struct TAG_STRIP_POINT
	{
		char		Code[15+1];			//航路点名称
		RPP_TYPE	Type;				//航路点位置类型 ，用于判断点为区域内或区域外
		char		ETOP[4+2];			//过点时间（预达此点时间/实际过点时间：根据过点序号判断）
		char		PCL[4+2];			//过点高度（预设许可高度）
		int			Speed;				//速度
		double		Longitude;          //经度
		double		Lat;                //纬度
	};

	//飞行计划动态部分
	struct ST_FDP_FLIGHTPLAN_DYNAMIC
	{
		//计划标志
		std::string CurMID;
		//计划总体信息
		time_t UpdateTime;              //更新时间
		PLAN_STATUS CplStatus;    		//计划状态
		//起飞降落信息
		std::string ATD;	     	    //实际起飞时间
		std::string ATA;       	        //实际到达时间
		//扇区信息
		std::string CurSec;		//当前扇
		std::string CtrlSec;    //控制扇
		std::string AcpSec;		//移交接受扇
		std::vector<std::string>	NextSecs;  	//下N扇
		//其他信息
		std::string PRL;	      	    //飞行员报告飞行高度
		std::string CFL;	     	    //管制员指定飞行高度
		std::string RouteStr;    	    //航路串
		std::string HoldPoint;  	    //HOLD点名称
		int HoldMinute;       	        //HOLD时长(分钟)
		std::string HoldTime;  	        //离开HOLD点时间
		//配对信息
		int TrackNo;		            //TRACK_NO,相关的系统航迹号,没有配对时置为-1
		PAIR_STATUS PairStatus;         //相关状态

		RVSM_STATUS rvsmStatus;     //RVSM状态

		int pointSum;        		    //航路点总数
		int pointPassed;        	    //已过航路序号[从 0 计数, -1表示未过点]
		//std::vector<TAG_STRIP_POINT> stripPoints;
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar & CurMID & UpdateTime & CplStatus & ATD & ATA & CurSec 
				& CtrlSec & AcpSec & NextSecs & PRL & CFL & RouteStr & HoldPoint
				& HoldMinute & HoldTime & TrackNo & PairStatus & rvsmStatus & pointSum 
				& pointPassed ; 
		}
	};

	//飞行计划 
	struct ST_FDP_FLIGHTPLAN
	{
		ST_FDP_FLIGHTPLAN_STATIC staticFlightPlan;
		ST_FDP_FLIGHTPLAN_DYNAMIC dynamicFlightPlan;
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar, const unsigned int version)
		{
			return ar & staticFlightPlan & dynamicFlightPlan; 
		}
	};

	//航路点结构
	struct TowerAirRoadStruct
	{
		char sBeacon[64];//导航台
		char sHeight[64];//高度
		char sSpeed[64];//速度
		TowerAirRoadStruct()
		{
			strcpy(sBeacon,"");
			strcpy(sHeight,"");
			strcpy(sSpeed,"");
		}
		TowerAirRoadStruct(const TowerAirRoadStruct& rhs)
		{
			strcpy(this->sBeacon,rhs.sBeacon);
			strcpy(this->sHeight,rhs.sHeight);
			strcpy(this->sSpeed,rhs.sSpeed);
		}
	};
	//飞行计划结构
	struct TowerFlightPlanStruct
	{
		int				iFlightPlanId;					//飞行计划id，由RDP指定
		char			sFlightNum[64];                     //飞行计划航班号
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


		std::string toString(){

			char* buf=new char[BUFFERSZE];
			memset(buf,0,BUFFERSZE);
			sprintf(buf,"TowerFlightPlanStruct:[FlightPlanId:%d;FlightNum:%s;SSRCode:%s;RVSM:%d;FlyPlanType:%d;SectorName:%s;Company:%s;CallSign:%s;\
DepDromeName:%d;ArrDromeName:%d;AlternateDrome:%s;CruiseLvl:%d;CruiseSpd:%d;ArrRunway:%s;DepRunway:%s;Weight:%s;DepGate:%s;\
ArrGate:%s;VacateLine:%s;InRunwayLine:%d;DepartureTime:%s;ArrivalTime:%s;SidName:%s]",iFlightPlanId,sFlightNum,sSSRCode,bRVSM,iFlyPlanType,sSectorName,sCompany,sCallSign,
sDepDromeName,sArrDromeName,sAlternateDrome,iCruiseLvl,iCruiseSpd,sArrRunway,sDepRunway,sWeight,sDepGate,sArrGate,sVacateLine,sInRunwayLine,sDepartureTime,
sArrivalTime,sSidName);

			return buf;

		}
        
	
	};
	//目标计划
	struct TowerObjectPlanStruct
	{
		ENUM_OBJ_TYPE   ObjType;						//类型
		char			strSSrcode[64];					//关联飞行计划的二次码，和飞行计划的SSR保持一致
		double			dLongtitude;					//出现的经度（单位：弧度）
		double			dLatitude;           			//出现的纬度（单位：弧度）
		double 			dAltitude;						//初始高度（标准海压高度，单位：米）
		double 			dHeading;						//机头朝向（单位：弧度）
		double 			dIAS;							//初始速度（表速，单位s：米/秒）
		char			sAppearTime[64];		        //出现时间（单位：秒）
		char			strModelType[64];				//机型名
		char			strRegNum[64];		            //注册号
		bool 			bEngineStart;					//引擎是否起动

		std::string  toString(){

		char* buf=new char[BUFFERSZE];
	    memset(buf,0,BUFFERSZE);

		
	   sprintf(buf,"TowerObjectPlanStruct:[ObjType:%d;SSR:%s;Longtitude:%L;Latitude:%L;Altitude:%L;Heading:%L;IAS:%L;AppearTime:%s;ModelType:%d;RegNum:%d;EngineStart:%s;]"
		      ,static_cast<int>(ObjType),strSSrcode,dLongtitude,dLatitude,dAltitude,dHeading,dIAS,sAppearTime,strModelType,strRegNum,bEngineStart);
		return buf;

	}
	};
	//动态创建飞机包
	struct TowerAircraftPacketStruct
	{
		TowerObjectPlanStruct TowerobjFlight;	//目标计划 /* 这里目标计划和飞行计划一一对应*/
		TowerFlightPlanStruct TowerplanFlight;	//飞行计划
		std::string toString(){

			return TowerobjFlight.toString()+TowerplanFlight.toString();
		}
	};
	//停机位信息
	struct GateInformationStruct
	{
		QString     sGateName;//停机位名
		double		dLongtitude;//停机位经度（单位：弧度）
		double		dLatitude; //停机位纬度（单位：弧度）
		char	    sArrRunway[64];	/* 降落跑道 */
		char		sDepRunway[64];  /* 起飞跑道*/
		char		sDepGate[64];	/* 离场的停机位 */
		char		sArrGate[64];	/* 进场的停机位 */
		char		sVacateLine[64];/* 脱离道 */
		char		sInRunwayLine[64];/* 进入道 */
	};
	////从数据库读取的数据
	struct FlyPlanFromDBStruct
	{
		std::string			sFlyPlanNum;				 /*航班号*/
		std::string		    sSSRCode;					 /*  二次码 */
		bool			    bRVSM;					     /* 是否具备RVSM能力*/
		int				    iFlyPlanType;				/* 飞行计划类型,0进港，1离港 */
		std::string			sSectorName;				//所属扇区名
		std::string			sDepDromeName;		        /* 起飞机场 */
		std::string			sArrDromeName;       		/* 降落机场 */
		std::string			sAlternateDrome;	        /* 备降场 */
		int				    iCruiseLvl;					/* 巡航高度(标准海压高度，单位：米) */
		int				    iCruiseSpd;					/* 巡航速度(表速或者马赫，表速单位：米/秒) */
		std::string			sArrRunway;					/* 降落跑道 */
		std::string			sDepRunway;                 /* 起飞跑道*/
		std::string			sWeight;		            /* 载重 */
		std::string			sDepartureTime;				/* 预计起飞时间*/
		std::string			sArrivalTime;		        /* 预计到达时间*/
		std::string         sADepTime;//实际起飞时间
		std::string         sAArrTime;//实际到达时间
		std::string         sRegNum;                   /*飞机注册号*/
		std::string         sModlType;				   /*机型名*/
		bool                bIsPlanFinished;          //该计划是否完成
		FlyPlanFromDBStruct()
		{
		   bIsPlanFinished=false;
		}
	};

	//控制飞机运动所包含的结构信息
	struct ControlFlightStruct
	{
		int     sFlightNo;
		char	sNetCommand[64];//控制飞机运动指令
	};
	//从文件读取的飞行计划解析后的数据结构
    struct FlyPlanStruct
	{
		
		QString	sSSRCode;/*  二次码 */
		bool	bRVSM;	/* 是否具备RVSM能力*/
		int		iFlyPlanType;/* 飞行计划类型,0进港，1离港 */
		QString	sSectorName;//所属扇区名
		QString sPlane_ID;//飞机的ID(人为添加的部分，因为存在两个航班号共用一架飞机的情况)
		QString sFly_ID;//航班号
		QString sPlaneType;//飞机类型
		QString sDEPAp;//起飞机场
		QString sARRAp;//落地机场
		QString sAlterAp;//备降场
		QString sDEPTime;//起飞时间
		QString sARRTime;//降落时间
		int		iCruiseLvl;	/* 巡航高度(标准海压高度，单位：米) */
		int		iCruiseSpd;/* 巡航速度(表速或者马赫，表速单位：米/秒) */
		QString	sArrRunway;	/* 降落跑道 */
		QString	sDepRunway;   /* 起飞跑道*/
		QString	sWeight;	/* 载重 */
		QString sRegNum;   /*飞机注册号*/
		QString sModlType;	 /*机型名*/
		QString sTeriminal;//航站楼
		bool    bIsPlanFinished; //该计划是否完成
		FlyPlanStruct()
		{
			iFlyPlanType=0;
		}
		
	};
	//RDP核心程序发送给Display模块的数据包，给定的是飞机当前的位置信息
	struct RDP_Display_Struct
	{
		int			 iPlanID;         //飞行计划ID，必须和RDPStruct的iPlanID保持一致
		double		 dLongtitude;  //飞机当前的经度
		double		 dLatitude;    //飞机当前的纬度 
		/*飞机标牌信息*/                                                                   
		std::string	 sSSRCode;	/*  二次码*/                                   
		std::string  sPlanNum;    //航班号                                          
		double 		 dIAS;		//速度（表速，单位s：米/秒）               
		double 		 dAltitude;	//高度（标准海压高度，单位：米）            
		char		 strModelType[64];	//机型名    
	};
	class TaxiLine
	{
		int				m_iRoadId;		 //道路ID
		std::string		m_sRoadName;	 //道路名称
		int				m_iFixPointID;	 //固定点ID
		std::string		m_sFixPointName; //固定点名称
		double			m_dFixPoint_x;	 //固定点的x坐标
		double			m_dFixPoint_y;	 //固定点的y坐标
	public:
		void			SetRoadID(const int iRoadId) { m_iFixPointID = iRoadId;}
		void			SetRoadName(const std::string& sRoadName) {m_sRoadName = sRoadName;}
		void			SetFixPointID(const int iFixPointId) {m_iFixPointID = iFixPointId;}
		void			SetFixPointName(const std::string& sFixPointName) { m_sFixPointName = sFixPointName;}
		void			SetFixPoint_X(const double& dFixPoint_X)  {m_dFixPoint_x = dFixPoint_X;}
		void			SetFixPoiint_Y(const double& dFixPoint_Y) {m_dFixPoint_y = dFixPoint_Y;}
		int				GetRoadID(){return m_iRoadId;}
		std::string&	GetRoadName(){return m_sRoadName;}
		int				GetFixPointID(){return m_iFixPointID;}
		std::string&	GetFixPointName(){return m_sFixPointName;}
		double			GetFixPoint_X(){return m_dFixPoint_x;}
		double			GetFixPoint_Y(){return m_dFixPoint_y;}
       };
	/**************************************************************************
	   版权所有 (C), 2013 - 2014, 四川大学空管实验室
	  【类  名】: AircraftTrace
	  【作  者】: 陈文平
	  【版  本】:1.0
	  【完成日期】:2014/12/28
	  【描  述】:  此文件定义了类AircraftTrace，该类是RDP发向Display模块的航迹包
	  【其  它】:   
	**************************************************************************/
	class AircraftPos

	{
		double			m_dLongtitude;  //飞机当前的经度                                           
		double			m_dLatitude;    //飞机当前的纬度 
	public:
		AircraftPos(){}
		AircraftPos(const AircraftPos& rhs)
		{
			m_dLongtitude = rhs.m_dLongtitude;
			m_dLatitude = rhs.m_dLatitude;
		}
		void SetLongtitude(const double& dLongtitude){ m_dLongtitude = dLongtitude;}
		void SetLatitude(const double& dLatitude){m_dLatitude = dLatitude;}
		const double& GetLongtitude(){return m_dLongtitude;}
		const double& GetLatitude(){return m_dLatitude;}
	};
	class AircraftTrace
	{
		int				m_iPlanID;				//飞行计划ID，必须和TowerAircraftPacketStruct的iPlanID保持一致                                                                                                                     
		std::string	    m_sSSRCode;	           /*  二次码*/                                   
		std::string     m_sPlanNum ;           //航班号
		double 		    m_dIAS;		          //速度（表速，单位s：米/秒）               
		double 			m_dAltitude;	     //高度（标准海压高度，单位：米）            
		char			m_strModelType[64];	 //机型名 
		std::vector<AircraftPos> m_vecTracePoint;//存放飞机滑行航迹点的容器
	public:
		void				SetPlanID(const int iPlanID){ m_iPlanID = iPlanID;}
		void				SetSSRCode(const std::string& sSSRCode){m_sSSRCode = sSSRCode;}
		void				SetPlanNum(const std::string& sPlanNum){m_sPlanNum = sPlanNum;}
		void				SetIAS(const double& dIAS){m_dIAS = dIAS;}
		void				SetAltitude(const double& dAltitude){ m_dAltitude = dAltitude;}
		void				SetModeType(const char* strModeType){strcpy(const_cast<char*>(strModeType),m_strModelType);}
		void				SetVecAircraftTrace(std::vector<AircraftPos>& vecTracePoint){ m_vecTracePoint = vecTracePoint;}
		const int			GetPlanID(){return m_iPlanID;}
		const std::string&  GetSSRCode(){return m_sSSRCode;}
		const std::string&  GetPlanNum(){return m_sPlanNum;}
		const double		GetIAS(){return m_dIAS;}
		const double		GetAltitude(){return m_dAltitude;}
		const char*			GetModeType(){return m_strModelType;}
		const std::vector<AircraftPos>& GetVecTracePoint(){return m_vecTracePoint;}
	};
	class FixPoint
	{
		int					m_iFixpointId;		//固定点ID
		std::string			m_sFixpointName;	//固定点名称
		double				m_dFixpoint_X;		//X坐标
		double				m_dFixpoint_Y;		//Y坐标
		double				m_dFixpoint_Z;		//Z坐标
	public:
		void				SetFixPointID(const int iFixpointId){m_iFixpointId = iFixpointId;}
		void				SetFixPointName(const std::string& sFixPointName){m_sFixpointName = sFixPointName;}
		void				SetFixPointX(const double& dFixpoint_X){m_dFixpoint_X = dFixpoint_X;}
		void				SetFixPointY(const double& dFixpoint_Y){m_dFixpoint_Y = dFixpoint_Y;}
		void				SetFixPointZ(const double& dFixPoint_Z){m_dFixpoint_Z = dFixPoint_Z;}
		const int			GetFixPointID(){return m_iFixpointId;}
		const std::string&  GetFixPointName(){return m_sFixpointName;}
		const double&		GetFixPointX(){return m_dFixpoint_X;}
		const double&		GetFixPointY(){return m_dFixpoint_Y;}
		const double&		GetFixPointZ(){return m_dFixpoint_Z;}
	};
	struct SDPSTrack 
	{
		SDPSTrack::SDPSTrack(){}

		int									iTrackID;               ///< 航迹ID
		PublicDataStruct::ENUM_TRACKTYPE	TrackType;          ///< 航迹类型
		int									iICAOAddr;             ///< 航空器ICAO地址
		double								dLongitude;         ///< 航空器经度
		double								dLatitude;            ///< 航空器纬度
		int									iAltitude;		    ///< 高度 m
		PublicDataStruct::ENUM_AltitudeType	AltitudeType;       ///< 高度类型
		double								dGS;			  ///< GS km/h
		double								dTrackAngle;	 ///< 航迹朝向
		std::string							strSSR;          ///< 二次雷达码
		std::string							strCallSign;    ///< 航空器呼号
		std::vector<std::string>			vecSensors;     ///< 检测到该航迹的传感器名称数组, 当用于单监视航迹时，该字段无用
		bool								bSPIFlag;       ///< SPI标志
		int									Emergency;      ///< 特殊情况类型
		PublicDataStruct::ENUM_OBJ_TYPE		ObjType;        ///< 目标类型
		double								dROCD;          ///< 上升下降率，上升为正，下降为负，平飞为0

		//串行化
		template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar & iTrackID & TrackType & iICAOAddr & dLongitude & dLatitude & iAltitude &
				AltitudeType & dGS & dTrackAngle & strSSR & strCallSign & vecSensors & bSPIFlag & Emergency & ObjType & dROCD;
		}
	};
	//add by 陈文平
	//从数据库读取的飞行计划数据
	struct SFlyPlanFromDB
	{
		std::string			sFlyPlanNum;				 /*航班号*/
		std::string		    sSSRCode;					 /*  二次码 */
		bool			    bRVSM;					     /* 是否具备RVSM能力*/
		int				    iFlyPlanType;				/* 飞行计划类型,0进港，1离港 */
		std::string			sSectorName;				//所属扇区名
		std::string			sDepDromeName;		        /* 起飞机场 */
		std::string			sArrDromeName;       		/* 降落机场 */
		std::string			sAlternateDrome;	        /* 备降场 */
		int				    iCruiseLvl;					/* 巡航高度(标准海压高度，单位：米) */
		int				    iCruiseSpd;					/* 巡航速度(表速或者马赫，表速单位：米/秒) */
		std::string			sArrRunway;					/* 降落跑道 */
		std::string			sDepRunway;                 /* 起飞跑道*/
		std::string			sWeight;		            /* 载重 */
		std::string			sDepartureTime;				/* 预计起飞时间*/
		std::string			sArrivalTime;		        /* 预计到达时间*/
		std::string         sADepTime;                  //实际起飞时间
		std::string         sAArrTime;                  //实际到达时间
		std::string         sRegNum;                   /*飞机注册号*/
		std::string         sModlType;				   /*机型名*/
		bool                bIsPlanFinished;           //该计划是否完成
		SFlyPlanFromDB()
		{
			bIsPlanFinished=false;
			bRVSM=true;//默认情况下，开启RVSM能力
			sAlternateDrome="ZUUU";//默认情况下为ZUUU
			sModlType="B001";
			sWeight="M";
			sSSRCode="A1234";
		}
		std::string toString(){

			char* buf=new char[BUFFERSZE];
			memset(buf,0,BUFFERSZE);
			sprintf(buf,"SFlyPlanFromDB:[FlyPlanNum:%s;SSR:%s;RVSM:%d;FlyPlanType:%d;SectorName:%s;DepDromeName:%s;ArrDromeName:%s;AlternateDrome:%s;\
CruiseLvl:%d;CruiseSpd:%d;ArrRunway:%s;DepRunway:%s;Weight:%s;DepartureTime:%s;ArrivalTime:%s;ADepTime:%s;AArrTime:%s;\
RegNum:%s;ModlType:%s;IsPlanFinished:%d]",sFlyPlanNum.c_str(),sSSRCode.c_str(),bRVSM,iFlyPlanType,sSectorName.c_str(),sDepDromeName.c_str(),sArrDromeName.c_str(),
sAlternateDrome.c_str(),iCruiseLvl,iCruiseSpd,sArrRunway.c_str(),sDepRunway.c_str(),sWeight.c_str(),sDepartureTime.c_str(),sArrivalTime.c_str(),sADepTime.c_str(),
sAArrTime.c_str(),sRegNum.c_str(),sModlType.c_str(),bIsPlanFinished);

			return buf;
   
		}
	};
	//////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	//add by 2015.10.30
	const double BRAKE_FACTOR=0.6; //刹车力因子
	const double REVERSE_FACTOR=0.4;//反推力因子
	const double AIRFRICTION_FACTOR=0.15; //空气阻力因子
	const int RESPONSETIME=5;//反应时间=管制人员反应时间+驾驶员反应时间+信息传递时间，单位秒
	

	//enum AIRCRAFT_TYPE{S=0,H=1,M=2};
	enum WAKE_INTERVAL{//尾流间隔，采用的是FAA尾流标准
		//H代表重型机，M代表中型机，S代表小型机
		//双流机场基本上都是中型机和重型机
		//尾流标准只有航空器在空中的是有用，而在地面滑行时，则不采用此套标准
		HH=7400,HM=9260,HS=11110,MH=5560,MM=5560,MS=7400,SH=5560,SM=5560,SS=5560
	};
	enum TAX_INTERVAL{//地面滑行尾流间隔，此规定为仿真实验设定值，并不是标准参考
		HH1=700,HM1=900,HS1=1100,MH1=600,MM1=600,MS1=700,SH1=600,SM1=600,SS1=600
	};
	enum TAX_SPEED{
		HIGHEST_SPD=29,  //最高滑行时速29km/h
		NORMAL_SPD=24,   //正常滑行时速
		TURN_SPD=15,    //转弯滑行时速
		STOP_SPD=5		//进出停机坪的初始滑行时速
	};
	//enum AIRCRAFT_MASS{
	//	//航空器质量，设定为最大降落质量，单位为千克，主要是成都双流常用的一些飞机类型
	//	B737=58604,		B733=52550,		B736=58604,		B738=66361,		B739=66361,		B763=136078,
	//	B764=158800,	B772=201800,	B773=237680,	B741=265300,	B742=285700,	B743=260320,
	//	B744=285764,	B783=158757,	B788=165561,	B789=185519,	B762=123377,	A342=275000,
	//	A343=192000,	A345=243000,	A346=256000,	A358=182500,	A359=202500,	A312=123500,
	//	A313=124000,	A318=56000,		A319=61000,		A320=63000,		A321=71500,		A332=180000,
	//	A333=185000,
	//};

	//enum AIRCRAFT_LENGTH{//机长，单位：米
	//	B737=32.18,	B733=32.18,	B736=31.42,	B738=38.02,	B739=40.67,	B763=55,
	//	B764=61.4,	B772=62.94,	B773=73.08,	B741=68.6,	B742=68.6,	B743=68.6,
	//	B744=68.6,	B783=55.9,	B788=55.9,	B789=62,	B762=48.51,	A342=59.42,
	//	A343=63.69,	A345=66.03,	A346=73.46,	A358=60.5,	A359=65.2,	A312=45.89,
	//	A313=45.89,	A318=31.45,	A319=33.84,	A320=37.57,	A321=44.5,	A332=58.37,
	//	A333=63.69
	//};
	//enum AIRCRAFT_WINGSPAN{//翼展，单位：米
	//	B737=34.3,	B733=28.9,	B736=34.31,	B738=34.3,	B739=34.3,	B763=47.57,
	//	B764=51.82,	B772=60.9,	B773=60.9,	B741=60.93,	B742=60.93,	B743=60.93,
	//	B744=60.93,	B783=60,	B788=60,	B789=60,	B762=47.57,	A342=60.3,
	//	A343=60.3,	A345=60.3,	A346=60.3,	A358=61.1,	A359=61.1,	A312=43.89,
	//	A313=43.89,	A318=34.09,	A319=34.09,	A320=34.09,	A321=34.09,	A332=60.3,
	//	A333=60.3
	//};
	//enum AIRCRAFT_WAKE{//尾流标准，H--重型机，M--中型机，S--轻型机
	//	M=0,H=1,
	//	B737=M,	B733=M,	B736=M,	B738=M,	B739=M,	B763=H,
	//	B764=H,	B772=H,	B773=H,	B741=H,	B742=H,	B743=H,
	//	B744=H,	B783=H,	B788=H,	B789=H,	B762=H,	A342=H,
	//	A343=H,	A345=H,	A346=H,	A358=H,	A359=H,	A312=H,
	//	A313=H,	A318=M,	A319=M,	A320=M,	A321=M,	A332=H,
	//	A333=H
	//};
	struct Aircraft{
		int  iTraceID;
		std::string sFlightNum;//航班号，唯一识别一架航空器
		std::string sWake;//尾流级别
		std::string sType;//机型名
		double dLength;//机身长度
		double dWingSpan;//翼展
		double dMass;//质量
		double dCurTaxSpd;//当前滑行速度
		double dBaseDistance;//基本层
		double dProtectDistance;//保护层
		double dAlarmDistance;//告警层
		//double dX;//x坐标
		//double dY;//y坐标
		//double dAngle;//角度
		double dSafeDistance;//基本层+保护层+告警层
		bool   bStop;
		Aircraft(){
			bStop=false;
			if(sWake=="H")
				dProtectDistance=HS1;
			else if(sWake=="M")
				dProtectDistance=MS1;
			else if(sWake=="S")
				dProtectDistance=SS1;
			dSafeDistance+=dProtectDistance;
		}
	};
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	//===============================================================================
	/*
	*以下的数据结构，是用于机场碰撞检测的数据结构。
	*碰撞检测：从数据库中读取在场航空器的位置，机型，关键尺寸构造基层；
	           获取航空器在不同区域运行时的安全净距构造保护层；
	           根据航空器的速度，性能参数实现告警层
	每隔一段时间，判断航空器之间的告警层是否有交集。
	*/
	//尾流间隔

	
}
Q_DECLARE_METATYPE(PublicDataStruct::ControlFlightStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerFlightPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerAirRoadStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerObjectPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::GateInformationStruct);
Q_DECLARE_METATYPE(PublicDataStruct::FlyPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::PLAN_TERMINATE);
#endif