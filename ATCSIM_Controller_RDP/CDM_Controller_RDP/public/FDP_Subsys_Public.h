/*********************************************************************
 * Copyright(c) Reserved, WiseSoft Corporation.
 *   FileName: fdp_subsys_public.h
 *     Author: huangyu
 *  $Revision: 52 $ 
 *       Date: 2004/05/28
 *Description: FDP相关子系统[FDP, FDD, FDO, FDPTEL]公共结构定义
 ********************************************************************/

#ifndef _FDP_SUBSYS_PUBLIC_H_
#define _FDP_SUBSYS_PUBLIC_H_

#include <time.h>

#include "simple_type_def.h"
#include "base_type_def.h"
#include "radp_type.h"

#pragma	pack(2)

// --------------------------------
// 枚举类型定义 [四字节有符号整数]
// --------------------------------

//计划被修改的内容等级(0:没有改变 1:描述性内容改变 2: 状态改变 4:时间、速度、高度改变 8:航路串改变)
enum PLAN_CHANGE{CH_NONE=0, CH_DESCRIPTION=1, CH_STATUS=2, CH_TIMESPEED=4, CH_ROUTESTRING=8};

// 计划的状态:未来(收到PLN)、静止(收到FPL)、预激活(预计起飞时间前半小时)、协调、移交、控制、完成、取消
enum PLAN_STATUS{FUTR=0, NACT=1, PREA=2, COOR=3, HAND=4, CONT=5, FIN=6, CNL=7};

// 计划的AIDC状态:初始态、   通知、		初始协调、	再协商、	移交    、完成
enum AIDC_STATUS{AIDC_NONE=0, INFORM=1, NEGOTIATE=2, AGAIN=3, TRANSFER=4, FINISH=5};


//航迹状态(0=确认 1=尝试 2=滑行 3=等待 4=悬挂 5=移交 6=最后 7=外部输入 8=紧急 9=飞行计划模拟)
enum TRACK_TYPE{CH_CONFIRM=0, CH_ATTEMPT=1, CH_COAST=2, CH_WATI=3, CH_SUSP=4, CH_HAND=5, CH_FINAL=6, CH_EXTERN=7,CH_EMERG=8,CH_SIMU=9};

// 飞行类型：未知、       区域外-入港、		 区域内-入港、		  区域外-出港、	   区域内-出港、 本场迂回(飞出飞入)
enum CPL_TYPE{ UNKNOWN=0, EXTERNAL_INBD,	 DOMES_INBD,		  EXTERNAL_OUTBD,  DOMES_OUTBD,	 BYPASS,
//					   区域外-其他机场入港、 区域外-其他机场出港、区域内-其他机场之间飞行、	区域内其他机场迂回(飞出飞入)						 
						 EXTERNAL_ADP_INBD,	 EXTERNAL_ADP_OUTBD,  DOMESTIC,					DOMES_BYPASS, 	
//						飞越管制区
						 OVERFLY };
//与航迹配对的状态：没有配对、丢失配对、     人工配对、     人工去配对、    自动配对	、自动去配对
enum PAIR_STATUS{NOTCOUPLE=0, LOSSCOUPLE, MANUALCOUPLE, DEMANUALCOUPLE, AUTOCOUPLE, DEAUTOCOUPLE};

//飞行计划来源: 本地编辑, 重复性飞行计划, 飞行计划报,	模板飞行计划，简标牌
enum PLAN_SOURCE{LPL=0,   RPL=1,			TELE=2,		STL=3   , TAG = 4};


//报文的人工处理状态:	值班未处理, 值班已处理
enum DUTYSTATUS {		DUTY_NO = 0, DUTY_DONE };

//报文的系统处理状态 --    收报状态： 报文解析错， 报文解析成功，收报干预计划错，收报干预计划成功，报文正确处理, 错报强制忽略, AIDC运行响应逻辑错报
enum FINSTATUS{			RECVSTATUS=0,  RESOLVE_ERR, RESOLVE_SUCC, RDISPOSE_ERR, RDISPOSE_SUCC, DISPOSE_SUCC,    ERRMSG_IGNORE, AIDCLOGIC_ERR,
// 						  发报状态:	    组报错误，     组报成功，  	发报干预计划错，发报干预计划成功, 发送成功， 发送失败
			 			SENDSTATUS = 20, COMPOSE_ERR, COMPOSE_SUCC, SDISPOSE_ERR,   SDISPOSE_SUCC, SEND_SUCC,	SEND_FAILURE,
};


// 静态航路点类型
// NDB-无方向信标台，VOR-全向信标台，VORLOC-VOR和航向台组合，DME-测距台，VORTAC-VOR和塔康组合，VORDME-全向信标测距台，
// VORDMET-兼容制的VOR/DME和塔康，TACAN-塔康，NONE-其他一般地标点，LOC-航线台、示位台，AIRPORT机场，ZA 障碍物, TEMP 经纬度表示的点, 空域代码
enum RPS_TYPE { NONE=0, REPORT, NDB, VORDME, VOR, DME, NDBDME, AIRPORT, VORLOC, VORTAC, VORDMET, TACAN, LOC, ZA, TEMP, AIRSPACE, HANDOVER};
	
//动态航路点类型: 一般点，起飞机场、降落机场、入界点、出界点、管制区内扇区间交点、离场点、进场点，走廊点, 监视点
enum RPD_TYPE {RPD_GEN = 0, RPD_DEP = 1 , RPD_ARR = 2, RPD_BPN = 4, RPD_BPX = 8, RPD_SECP=16,
		RPD_SID = 32, RPD_STAR=64, RPD_CORRIDOR=128, RPD_AIRWAY=256, RPD_FTYP=512, RPD_KTYP=1024,
		RPD_JTYP=2048, RPD_CTYP=4096, RPD_ATYP=8192, RPD_SURVTYP = 16384};

//航路点位置类型：区域内，  入界点， 出界点， 区域外
enum RPP_TYPE { RPP_IN = 0, RPP_BPN, RPP_BPX, RPP_OUT};

// 返回处理结果的代码
// 增加时请将说明和代码对齐,以便更新
enum ACK_NO
{
	// 0
	SUCCESS=0,                              // 成功
	PLAN_NOT_FOUND,                         // 对应的计划未找到
	NOT_FOUND,                              // 未找到
	ACCESS_DENIED,                          // 没有相应的权限
	STATUS_DENIED,                          // 飞行计划状态不允许
	FIELD_DENIED,                           // 字段不允许修改
	FIELD_ERROR,                            // 字段内容错误
	NOT_CURRENT,                            // 传过来的内容不是最新的
	ACK_ERROR,                              // 失败

	// 11
	ERR_PLAN_NOT_EXIST = 11,                // 计划不存在
	ERR_TRACK_NOT_EXIST,                    // 航迹不存在
	ERR_MID_REPEAT,                         // MID重复
	ERR_OPTYPE,                             // 错误的操作类型
	ERR_TIMEZONE_MISMATCH,                  // FDP 与  FIEP  时区不一致
	ERR_NOT_CURRENT,                        // 传过来的内容不是最新的
	ERR_OUT_OF_RANGE,						// 值超过范围
	ERR_FIELD,								// 计划的字段错误
	ERR_ACCESS_DENIED,						// 没有相应的权限
	ERR_STATUS_DENIED,						// 飞行计划状态不允许

	// 21
	// 计划字段错误
	ERR_FIELD_EMPTY    = 21,                // 字段不允许为空
	ERR_FILED_MODIFY_DENIED,                // 字段不允许修改
	ERR_FIELD_FORMAT,                       // 字段格式错误
	ERR_FIELD_OUT_OF_RANGE,                 // 字段的值超过范围
	ERR_FIELD_LENGTH_OVERFLOW,              // 字段的长度超界
	ERR_FIELD_NOT_CHANGE,                   // 字段内容相同，不作修改

	// 41
	// 字段在数据库中找不到
	ERR_POINT_NOT_EXIST = 41,               // 点不存在
	ERR_ACFT_NOT_EXIST,                     // 机型不存在
	ERR_HEIGHT_NOT_EXIST,                   // 此高度层不存在
	ERR_FLYCOURSE_NOT_EXIST,                // 科目不存在
	ERR_TELE_ADDR_NOT_EXIST,                // 收报地址不存在
	ERR_FLYTASK_NOT_EXIST,                  // 任务不存在
	ERR_ROUTE,								// 航线解析错误
	ERR_TRAJECTORY_CALC,					// 轨迹估算
	ERR_ACFT_SPEED,							// 机型缺速度
	ERR_ACFT_CLASS,							// 机型缺分类

	// 61
	ERR_RPL_ALREADY_COMMIT = 61,            // 已经提交 (RPL)
	ERR_RPL_NO_MISSION,                     // 当天没有计划
	ERR_RPL_ERROR,                          // RPL 有错误，不能生成计划
	ERR_RPL_EXTRACT,                        // RPL 提交错误，不能生成计划
	ERR_RPL_INPROCESSING,                   // 正在提交全部 RPL，不再响应命令
	ERR_RPL_NOT_EXIST,                      // RPL 计划不存在
	ERR_RPL_SUBMIT_MODIFIED,                // 用户提交被修改过的固定RPL,
	ERR_CITYROUTE_ACFT_MISMATCH,			// 城市班机对航线没有对该机型开放

	// 81
	// 进程单操作航路时的错误
	ERR_ROUTEPOINT_NUMBER = 81,             // 航路点序号超界，或顺序颠倒
	ERR_ROUTEPOINT_MISMATCH,                // 航路点的名称和序号不一致

	// 101
	// 人工配对处理错误
	ERR_PLAN_ALREADY_COUPLED = 101,         // 计划已经配对
	ERR_TRACK_ALREADY_COUPLED,              // 航迹已经配对
	ERR_NOT_COUPLED,                        // 要求去配对时，航迹和计划没有配对

	// 121
	// SSR 代码分配错误
	ERR_SSR_MISMATCH      = 121,            // 航迹和计划的 SSR 不一致
	ERR_SSR_NOT_EXIST,                      // SSR 代码不存在, 不属于本地的资源
	ERR_SSR_REPEAT,                         // SSR 代码重复
	ERR_SSR_ASSIGN,							// SSR 分配错误

	ERR_CALLSIGN          = 141             // 飞机标识错误
};


enum REQ_PLAN_TYPE
{
	SINGLE_PLAN = 0,			// 根据cpl_id,请求一条计划
	DYNAMIC_TODAY,				// 今日动态
	DYNAMIC_TOMORROW,			// 明日动态
	DYNAMIC_ALL,				// 所有计划
//	LIST_PREDYNAMIC,			// 准动态列表
//	LIST_TPITPO_DELAY,			// TPI/TPO延误列表
//	LIST_PREDEP,				// 起飞协调列表
//	LIST_PREARR,				// 入界协调列表
//	LIST_ACTIVE,				// 激活列表
//	LIST_WAIT,					// 等待列表
//	LIST_HOLD,					// 挂起列表
//	LIST_ARR,					// 着陆顺序列表
//	LIST_WATCH					// 监视点列表
	DYNAMIC_CHKSUM = 50			//fdpsub use only
};

// DATA_ID 计划字段枚举类型
enum DATA_ID
{
	CPL_ID=0, MID, DATE_EXE, TIME_CREATED, ACID, TYPE, RELA_TYPE, CPL_SOURCE, STATUS,
	
	FLY_CLASS, FLY_COURSE, FLY_TASK, IS_INTERNATIONAL, IS_VIP, FLY_RULE, EQUIPMENT,	UNIT,
	WATCH,	COMMANDER, PILOT, PILOT_POST, PSN_NUM,	TOTAL_SORTIE, REAL_SORTIE, TURBO, 
	AIRCRAFT_STR,	HOLD_POINT_TYPE, REGIST_NO,	METO_STR, CALLSIGN, COMM_STR, COMMENT,
	
	CPLTYPE, AP_DEP, AP_DEP_LAT, AP_DEP_LONG, STID, RWAY_DEP, TIME_DEP_PLAN, TIME_DEP_EST,	
	TIME_DEP_REAL, AP_ARR,	STAR, RWAY_ARR,	TIME_ARR_PLAN, TIME_ARR_EST, TIME_ARR_REAL,	AP_ALT,	
	
	CTRL_STATUS, CTRL_SEC, CTRL_OPS,	NEXT_SEC, NEXT_OPS,	CUR_SEC, 
		
	TRACK_NO, PAIRSTATUS, SSR_CODE,
	
	TAS, RFL, RFL2,	AFL, AFL2, CFL,	HOLD_POINT,	HOLD_HEIGHT, TIME_HOLD,	TIME_RESUME,
	SUSP_POINT,	TIME_SUSP, ROUTE_STR, ROUTE_STR_ALT,ROUTE_STR_ALT_FLAG,	EET_BP,	BPN, ETN, 
	BPX, ETX, CUR_POINT_NO, PR_POINT_NO, TOTAL_POINT_NO, ROUTE_POINTS,
	
	QUASI_STATUS, QUASI_INFO, PLAN_REL_NO, PLN_REL,	DEP_REL_NO,	DEP_REL, ARR_REL_NO, ARR_REL,

	BPN_HEIGHT, BPX_HEIGHT, SUSP_HEIGHT,

	PRESTATUS, TIME_STATUS_CHANGED, IS_MAN_STATUS, PLAN_CHANGE_FLAG, NEED_RTCD, AP_DEP_HEIGHT
};


enum RVSM_STATUS{
	RVSM_RVA = 0, 					//获准RVSM运行
 	RVSM_RVN, 						//未获准RVSM运行
 	RVSM_RVX, 						//豁免RVSM运行
 	RVSM_RVU, 						//未知是否获准RVSM运行
 	RVSM_RVT 						//由于气流/故障等影响取消RVSM
};

// -------------------------------------------
// 系统计划，报文分组，报文头结构构类型定义
// -------------------------------------------
//AIDC关联移交单位AIDC状态[TAG_PLAN中支持同一航班与两个管制移交相关]
struct TAG_AIDC_STATUS 
{
	char		ATCCode[10];		//关联管制移交单位代码
	AIDC_STATUS	AIDCStatus;			//AIDC阶段 
	BYTE		ResStatus;			//响应状态,按BIT位标示,1为响应中,0为非响应中:
									//0位-应用响应；1位 - 运行响应
	char		LastAIDCMsg[6];		//最后一封AIDC报文类型
	char		RSFlag;				//最后一封AIDC报文的收发标志: r/R-收；s/S-发
	BYTE		IOFlag;				//移交入/移交出标志：1 - 从该关联管制部门移交入本管制部门
									//					 2 - 从本管制部门移交出至该关联管制部门
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

//////////////////////////////////////////////////////////////////////////
//飞行计划 
typedef struct TAG_PLAN
{      
	//计划标志
    char        CurMID[29+1];		//计划ID:年月日[8]+航班号[7/6]+起飞机场[4]＋降落机场[4]
    //计划总体信息
    char    	CplDate[8+1+1];   	//计划执行日期(年月日[8])
	INT32  		UpdateTime;		    //更新时间
    PLAN_STATUS CplStatus;    		//计划状态
	PLAN_SOURCE	CplSrc;      	    //计划来源
	CPL_TYPE	CplType;	      	//飞行类型
	//飞行描述
	char		CallSign[8+1+1];  	//呼号		
	char		ASSR[5+1];        	//ASSR码	
	char		FlyRule[1+1];     	//飞行规则		
	char		FlyType[1+1];     	//飞行种类用途			                            
	short		AcftNum;           	//架次
	char		AcftType[4+1+1];  	//飞机类型      			
	short   	AcftClass;        	//飞机所属类别[1-A类,2-B类,3-C1类,4-C2类,5-C3类,6-C4类,7-D类,8-E类]
	char		Turbo[1+1];	      	//尾流
	char		AcftRegst[12+1+1];	//飞机注册号
	char    	SelSign[4+1+1];   	//选呼
	char		WirelessEp[30];		//无线电通信设备
	char		SurveilEp[30];		//监视设备
	char		SUP[40];	  		//计划附加信息
	char		OTHER[120];	    	//对应AFTN报18分组内容
	char		OP_DATA[10+1+1]; 	//标牌上的OP_DATA信息
	//起飞降落信息
	char		ADDEP[4+1+1];	  	//起飞机场
	char    	ETD[4+1+1];	      	//预计起飞时间
	char    	ATD[4+1+1];	     	//实际起飞时间	
	char		ADARR[4+1+1];	  	//落地机场
	char		ALTN1[4+1+1];	  	//备降机场1	                                
	char    	ALTN2[4+1+1];     	//备降机场2	                                
	char		EET[4+1+1];	      	//预计飞行时间
	char    	ETA[4+1+1];       	//预计到达时间	                                
	char    	ATA[4+1+1];       	//实际到达时间
    //扇区信息
	char		CurSec[10+1];		//当前扇
	char   		CtrlSec[10+1];      //控制扇
	char		AcpSec[10+1];		//移交接受扇
	char    	NextSec[5][10+1];  	//下一扇
	//其他信息
	char		TAS[5+1];	      	//预计巡航速度
	char		RFL[5+1];	      	//预计巡航高度层
	char		PRL[5+1];	      	//飞行员报告飞行高度
	char		CFL[5+1];	     	//管制员指定飞行高度
	char		RouteStr[420];    	//计划航路串
	char		HoldPoint[15+1];  	//HOLD点名称
	int     	HoldMinute;       	//HOLD时长(分钟)
	char		HoldTime[4+1+1];  	//离开HOLD点时间
	char		BPN[15+1];	     	//入界点
	char		ETN[4+1+1];	     	//入界时间
	char		BPX[15+1];	     	//出界点
	char		ETX[4+1+1];	     	//出界时间
    char	    XFL[5+1];	      	//协调移交(交接点)高度
    char		GATE[4+1+1];     	//停机位	
	char		ARWY[10+1];	      	//入场跑道	
	char		DRWY[10+1];	      	//离场跑道
	char		SID[15+1];	      	//标准离场过程	
	char		STAR[15+1];	      	//标准进场过程
	char 		GlobalInfo[10+2];   //全局信息[电子进程单使用]
	BYTE		OtherStatus;		//计划其他状态,按BIT位标示,1为TRUE,0为FALSE: 
									// 0位-计划有FPL报;1 - DLA; 2 - ALN; 3 - RTN
	//配对信息
	WORD			TrackNo;		    //TRACK_NO,相关的系统雷达航迹号,没有配对时置为0xffff;
	WORD			TrackIndexAdsb;	    //TRACK_INDEX_ADSB,相关的系统ADSB航迹号,没有配对时置为0xffff;
    PAIR_STATUS		PairStatus;         //相关状态
	//告警信息
	short			AlarmYAWType;       // 值为0 - 未告警; 0位为1 - 垂直偏航； 1位为1 - 侧向偏航 ; 
										// 2位为1 - 对未获准RVSM运行目标的CFL值进入或穿越RVSM空域的告警	
	//AIDC信息
	TAG_AIDC_STATUS	AIDCStatus[2];		//AIDC阶段
	//RVSM状态
	RVSM_STATUS 	rvsmStatus;    
	//航路点信息
	short			PntSum;        		//航路点总数
	short			PntPassed;        	//已过航路序号[从 0 计数, -1表示未过点]
	TAG_STRIP_POINT	STRIP_POINT[15];
	short			s_FlightID;			//记录航班ID
}TAG_PLAN_STRIP;


// -------------------------------------------
//	计划拆分为静态/动态两部分
// -------------------------------------------
struct TAG_STC_PLAN		/**静态计划**/
{
	//计划标志
    char        CurMID[29+1];
    //计划总体信息
    char    	CplDate[8+1+1];   	//计划执行日期
	PLAN_SOURCE	CplSrc;      	    //计划来源
	CPL_TYPE	CplType;	      	//飞行计划类型
	//飞行描述
	char		CallSign[8+1+1];  	//呼号		
	char		ASSR[5+1];        	//ASSR码	
	char		FlyRule[1+1];     	//飞行规则		
	char		FlyType[1+1];     	//飞行种类用途			                            
	short		AcftNum;           	//架次
	char		AcftType[4+1+1];  	//飞机类型      			
	short   	AcftClass;        	//飞机所属级别 0 - A; 1 - B; 2 - C; 3 - C1; 4 - C2; 5 - C3...
	char		Turbo[1+1];	      	//尾流
	char		AcftRegst[12+1+1];	//飞机注册号
	char    	SelSign[4+1+1];   	//选呼
	char		WirelessEp[30];		//无线电通信设备 
	char		SurveilEp[30];		//监视设备
	char		SUP[40];	  		//计划附加信息
	char		OTHER[120];    		//对应AFTN报18分组内容
	char		OP_DATA[10+1+1]; 	//标牌上的OP_DATA信息
	//起飞降落信息
	char		ADDEP[4+1+1];	  	//起飞机场
	char    	ETD[4+1+1];	      	//预计起飞时间
	char		ADARR[4+1+1];	  	//落地机场
	char		ALTN1[4+1+1];	  	//备降机场1	                                
	char    	ALTN2[4+1+1];     	//备降机场2	                                
	char		EET[4+1+1];	      	//预计飞行时间
	char    	ETA[4+1+1];       	//预计到达时间	                                
	//其他信息
	char		TAS[5+1];	      	//预计巡航速度
	char		RFL[5+1];	      	//预计巡航高度层
	char		RouteStr[420];    	//计划航路串   
	char		BPN[15+1];	     	//入界点
	char		ETN[4+1+1];	     	//入界时间
	char		BPX[15+1];	     	//出界点
	char		ETX[4+1+1];	     	//出界时间
    char	    XFL[5+1];	      	//协调移交(交接点)高度
    char		GATE[4+1+1];     	//停机位	
	char		ARWY[10+1];	      	//入场跑道	
	char		DRWY[10+1];	      	//离场跑道
	char		SID[15+1];	      	//标准离场过程	
	char		STAR[15+1];	      	//标准进场过程
	char 		GlobalInfo[10+2];   //全局信息
};

struct TAG_DYN_PLAN		/**动态计划**/
{
	//计划标志
	char        CurMID[29+1];
    //计划总体信息
 	INT32  		UpdateTime;		    //更新时间
	PLAN_STATUS CplStatus;    		//计划状态
 	//起飞降落信息
	char    	ATD[4+1+1];	     	//实际起飞时间	
	char    	ATA[4+1+1];       	//实际到达时间
   //扇区信息
	char		CurSec[10+1];		//当前扇
	char   		CtrlSec[10+1];      //控制扇
	char		AcpSec[10+1];		//移交接受扇
	char    	NextSec[5][10+1];  	//下一扇
	//其他信息
	char		PRL[5+1];	      	//飞行员报告飞行高度	
	char		CFL[5+1];	     	//管制员指定飞行高度                         	                                
	char		HoldPoint[15+1];  	//HOLD点名称
	int     	HoldMinute;       	//HOLD时长(分钟)
	char		HoldTime[4+1+1];  	//离开HOLD点时间
	//配对信息
	WORD		TrackNo;		    //TRACK_NO,相关的系统航迹号,没有配对时置为-1;
    PAIR_STATUS PairStatus;         //相关状态
	//告警信息
	short		AlarmYAWType;       // 值为0 - 未告警; 0位为1 - 垂直偏航； 1位为1 - 侧向偏航 	
									// 2位为1 - 对未获准RVSM运行目标的CFL值进入或穿越RVSM空域的告警	
	short		PntSum;        		//航路点总数
	short		PntPassed;        	//已过航路序号[从 0 计数, -1表示未过点]
	TAG_STRIP_POINT	STRIP_POINT[15];
};


// -------------------------------------------
//	计划基本信息包[分发给RDP、OUTTELL相关进程]
// -------------------------------------------
struct TAG_PLAN_BASE_INFO
{
	//计划标志
    char        CurMID[29+1];		//计划ID:年月日[8]+航班号[7/6]+起飞机场[4]＋降落机场[4]
    //计划总体信息
    char    	CplDate[8+1+1];   	//计划执行日期(年月日[8])
    PLAN_STATUS CplStatus;    		//计划状态
	CPL_TYPE	CplType;	      	//飞行类型
	//飞行描述
	char		CallSign[8+1+1];  	//呼号		
	char		ASSR[5+1];        	//ASSR码	
	char		FlyRule[1+1];     	//飞行规则		
	char		FlyType[1+1];     	//飞行种类用途			                            
	char		AcftType[4+1+1];  	//飞机类型      			
	char		AcftRegst[12+1+1];	//飞机注册号
	char		WirelessEp[30];		//无线电通信设备 
	char		SurveilEp[30];		//监视设备
	//起飞降落信息
	char		ADDEP[4+1+1];	  	//起飞机场
	char		ADARR[4+1+1];	  	//落地机场
	//其他信息
	char		CFL[5+1];	     	//管制员指定飞行高度                         	                                
	//相关信息
	WORD			TrackNo;		    //TRACK_NO,相关的系统航迹号,没有配对时置为0xffff;
	WORD			TrackIndexAdsb;	    //TRACK_INDEX_ADSB,相关的系统ADSB航迹号,没有配对时置为0xffff;
    PAIR_STATUS		PairStatus;         //相关状态
	//RVSM状态
	RVSM_STATUS 	rvsmStatus;   
	//多雷达融合信息
	WORD		LocalRadarTrack[MAX_FUSION_RADAR_NUM];	//参与融合的单雷达的航迹号 无效的TrackNo=0xffff
	 	
};

//今日计划
struct TAG_TODAYPLAN
{
    int 	ID;
    char	PlanDate[10]; 					//计划执行日期
    char 	FlyRule[2];						//飞行规则
    char 	FlyType[2];						//飞行种类
    char 	FlySubType[30];					//飞行种类中文缩写
	char	RVSM[2];						//是否具有RVSM能力
    char 	CallSign[10];	 				//航班号
    char  	MID[30];						//飞行计划MID、由FDP产生的唯一识别号
    char 	Aircraftype[10];				//机型
    char    Turbo[2];						//尾流
    char 	PlaneRegCode[10]; 				//注册号
    char 	Equipment[60];	 				//机载设备
    char	SSR[6];							//应答机编码
    char	Addep[5]; 						//起飞机场
    char	Adarr[5]; 						//落地机场
    char	TAS[6]; 						//预计巡航速度
    char	RFL[6]; 						//预计巡航高度层
    char	ETD[5]; 						//预计起飞时间
    char	TELETD[5]; 						//报文预计起飞时间
    char	ATD[5];							//实际起飞时间
    char	ETA[5]; 						//预计降落时间
    char	TELETA[5]; 						//报文预计落地时间
    char	ATA[5]; 						//实际降落时间
    char	EET[5]; 						//预计飞行时间
    char	ADALTN1[5]; 					//备降机场1
    char	ADALTN2[5]; 					//备降机场2
    char	Route[256]; 					//计划航路串
    char	PlanStatus[10];	 					//状态
    char	Remark[256];					//备注
	char	Abnormality[32];				//不正常原因
	char 	Airline[32];					//执行航空公司
};

//报文报头结构TAG_TELE_HEADER
struct TAG_TELE_HEADER
{
	char    teleid[30];					//  报文标识[与FinID一致]
	char	rsflag;						//	接收/发送标志: R/S
	char	linecode[6];				//	收/发报电报线路号
	char	serialno[6];				//	流水号
	char	rank[4];					//	电报等级
	char	rcvtime[8];					//	收报时间
	char	rcvaddr[370];				//	AFTN地址(28X8)、SITA地址(32X7)，地址间用空格隔开
	char	sndtime[8];					//	发报时间
	char	sndaddr[10];				//	发报地址
	char	msgtype[10];				//  报文类型(AFTN,WEATHER,SITA,BUREAU,OTHER，AIDC)
	char	typestr[26];				//	AFTN/SITA报文类型，多个类型为第一个类型
	UCHAR   typechar;					// 
};

//编组3 定义 -- 电报类别
struct TAG_TELE_GR3
{	
	char	tele_type[3+1];				//电报代号
	char	tele_no[12+1+1];			//电报号码 后面的一个字节是为了凑成偶数字节,下同.
	char	ref_data[12+1+1];			//参考数据
};

//编组5	定义 -- 紧急情况说明
struct TAG_TELE_GR5
{
	char	danger_class[8+1+1];		//危险等级ALERFA(告警) INCERFA(不明) DETRESFA(遇险)
	char	tele_sign[8+1+1];			//电报签发者 地名代码+单位代码+部门代码
	char	G5C[120+1+1];				//紧急情况说明短文，长度暂定120
};

//编组7 定义-- 航空器标志及SSR模式和编码
struct TAG_TELE_GR7
{	
	char	aircraft_id [8+1+1];		//飞机标识
	char 	ssr_mode[1+1];				//SSR模式
	char	ssr_code[4+1+1];			//SSR编码
};

//编组8 定义 -- 飞行规则及种类
struct TAG_TELE_GR8
{	
	char	fly_rule[1+1];				//飞行规则
	char	fly_type[1+1];				//飞行类型
};

//编组9定义 -- 航空器数目、机型和尾流等级
struct TAG_TELE_GR9
{
	char 	aircraft_num[2+1+1];	    //航空器数目
	char 	aircraft_type[4+1+1];       //航空器机型
	char	tail_stream[1+1];			//尾流等级
};

//编组10定义 -- 机载设备
struct TAG_TELE_GR10
{	
	char	equipmenta[30];				//无线电通信设备
	char	equipmentb[30];				//监视设备
};

//编组13定义 -- 起飞机场和时间
struct TAG_TELE_GR13
{
	char	dep_airport[4+1+1];			//起飞机场
	char	dep_time[4+1+1];			//预计或实际起飞时间
};

//编组14定义 -- 预计飞越边界数据
struct TAG_TELE_GR14
{
	char	location[30+1+1];			//位置点
	char	est_fly_time[4+1+1];		//预计飞越时间
	char	est_fly_height[5+5+1+1];	//预计飞越高度层 包括补充飞越数据及飞越条件
} ;

//编组15定义 -- 航路
struct TAG_TELE_GR15
{
	char	speed[5+1];					//巡航速度
	char	height[5+1];				//巡航高度层
	char	route[400+1+1];				//航线, 包括分组格式中的一个空格字符
};

//编组16定义 -- 目的机场、预计经过总时间、备降机场
struct TAG_TELE_GR16
{
	char	dest_airport[4+1+1];		//目的机场
	char	est_flight_time[4+1+1];	    //预计飞行总时间,包括一个空格
	char	standby_airport[4+1+4+1];	//备降机场
};

//编组17定义 -- 落地机场和时间
struct TAG_TELE_GR17
{
	char	landing_airport[4+1+1];		//落地机场
	char	landing_time[4+1+1];		//实际落地时间
	char	airport_name[32+1+1];	    //若落地机场中使用ZZZZ时，则此处填机场英文全称
};

//编组18定义 -- 其他情报
struct TAG_TELE_GR18
{
	char	EET[20+1+1];				//EET/累计的预计经过总时间，包括一个空格，以下类推
	char	RIF[300+1+1];				//RIF/返航或备降时的新航路，需重新申请
	char	REG[32+1+1];				//航空器注册标志
	char	SEL[10+1+1];				//SEL/选择呼叫编码，长度9
	char	OPR[32+1+1];				//OPR/营运人，长度17
	char	STS[64+1+1];				//STS/当遇有特殊情况时根据需要填写
	char	TYP[64+1+1];				//TYP/飞机架数及类型，在G9ab不全时填写
	char	PER[64+1+1];				//PER/按规定填写航空器性能数据
	char	COM[32+1+1];				//COM/机载通讯设备
	char	DAT[10+1+1];				//与数据链能力有关的重要数据
	char 	NAV[64+1+1]; 				//NAV/ 与导航设备有关的重要数据
	char	DEP[32+1+1];				//DEP/起飞机场全称（G13a为ZZZZ时填写）
	char	DEST[32+1+1];				//DEST/目的机场全称（G16a为ZZZZ时填写）
	char	ALTN[2*32+1+1]; 		//ALTN/目的地备降机场的英文全称
	char	RALT[2*32+1+1];   	//航路备降机场英文全称
	
	char	PBN[32+1+1];				//区域导航和/或所需导航性能的能力
	char	SUR[32+1+1];				//10a 中未注明的监视用途或能力
	char	DOF[10+1+1];				//飞行起飞日期以6 位数表示（YYMMDD，YY 表示年，MM 表示月，DD 表示日）
	char	CODE[10+1+1];				//按有关空中交通服务当局要求的航空器地址 (以6 位16 进制字符的字母代码形式表示)
	char	DLE[32+1+1];				//航路延误或等待，填入计划发生延误的航路重要点，随后用时分（小时分钟）4 位数表示延误长度。
	char	ORGN[32+1+1];				//如果无法立即识别飞行计划发报人，填入有关空中交通服务当局要求的发报人的8 字母AFTN地址或其他相关联络细节。
	char	TALT[32+1+1];				//按Doc 7910 号文件《地名代码》的规定填入起飞备降机场的国际民航组织四字代码。
	
	char	RMK[400+1+1];				//RMK/明语备注
};

//编组19定义 - 补充情报 19,20,21结构内字段名应与电报格式定义统一
struct TAG_TELE_GR19
{
	char	E[4+1+1];					//E/ 后跟4位数字表示燃料持续时间，包括一个空格。
	char	P[3+1];						//P/ 后跟1~3位数字表示总人数，包括一个空格，以下类推。
	char	R[6+1+1];					//R/ 后跟1-3个字符，表示机上通信设备
	char	S[6+1+1];					//S/ 后跟1-4个字符，表示救生设备类型
	char	J[6+1+1];					//J/ 后跟1-4个字符，表示救生衣情况
	char	D[32+1+1];					//D/ 后跟不定长项目，表示橡皮艇情况
	char	A[64+1+1];					//A/ 后跟不定长项目，表示飞机颜色和标志情况
	char	N[64+1+1];					//N/ 后跟简语字串，说明其它记载救生设备和有用备注	
	char	C[32+1+1];					//C/ 后跟长机姓名
};

//编组20定义 -- 搜寻和救援告警情报
struct TAG_TELE_GR20
{
	char	A[32+1+1];					//营运人代号，包括一个空格,以下类推
	char	B[20+1+1];					//最后一次双向联系的单位
	char	C[4+1+1]; 					//最后一次双向联系时间
	char	D[20+1+1];					//最后一次联系发送/接收频率
	char	E[34+1+1];					//最后报告位置及飞越位置点的时间
	char	F[64+1+1]; 					//确定最后所知位置的方法，用明语叙述
	char	G[64+1+1];					//报告单位采取的行动，用明语叙述
	char	H[64+1+1];					//其它有关资料
};

//编组21 -- 无线电失效情报
struct TAG_TELE_GR21
{	
	char	A[4+1+1];					// 最后一次双向联系时间, 包括一个空格,以下类推
	char	B[20+1+1]; 					// 最后一次联系发送/接收频率
	char	C[30+1+1];					// 最后报道位置：位置点
	char	D[4+1+1];					// 最后报告位置的时间
	char	E[64+1+1];					// 尚存通信能力
	char	F[64+1+1];		    		// 必要说明
};

//编组22定义 [变长结构：后面按分组号依次排列对应的分组结构]
struct TAG_TELE_GR22
{
	char	revise_data[300];			//22分组内容[主要用于组报]
	int		revise_sum;					//修订的分组总数
	int		revise_groupno[16];			//分组号
//	TAG_TELE_GR3~22 [];
};

//涉及TAG_GROUP结构的网络包[如:TAG_FDPTEL_AFTNGROUP]由于编组22变长而变为变长网络包
struct TAG_GROUP
{	
	char				fly_fcast_date[8];  //飞行预报日期，只用于PLN，COR，ABS报,SITA各类报。
	TAG_TELE_GR3    	G3;					//G3分组	
	TAG_TELE_GR5		G5;					//G5分组	
	TAG_TELE_GR7		G7;					//G7分组	
	TAG_TELE_GR8		G8;					//G8分组
	TAG_TELE_GR9		G9;					//G9分组
	TAG_TELE_GR10		G10;				//G10分组
	TAG_TELE_GR13		G13;				//G13分组
	TAG_TELE_GR14		G14;				//G14分组
	TAG_TELE_GR15		G15;				//G15分组
	TAG_TELE_GR16		G16;				//G16分组
	TAG_TELE_GR17		G17;				//G17分组
	TAG_TELE_GR18		G18;				//G18分组
	TAG_TELE_GR19		G19;				//G19分组
	TAG_TELE_GR20		G20;				//G20分组
	TAG_TELE_GR21		G21;				//G21分组
	TAG_TELE_GR22		G22;				//G22分组
};

//SITA报体分组结构
//多起降段航班的起降描述
struct TAG_SITA_MUTIDEPARR
{
	char				ADDEP[6];			//起飞机场[4字码,如"ZUUU"]
	char				ETD[6];				//预计起飞时间
};
struct TAG_SITA_GROUP
{
	char				FlightDate[10];		//计划执行日期：4位月日[MMDD]
	char				CallSign[128];		//航班号[AFTN报文航班号格式,如"CCA4181"]
											//多航班用空格间隔[满足非规范报文中存在多航班的情况]
	char				RegstNo[8];			//飞机注册号
	char				TaskPro[8];			//任务性质[PLN报使用]
	char				ADDEP[6];			//起飞机场[4字码,如"ZUUU"]
	char				ADARR[6];			//降落机场[4字码,如"ZBAA"]
	char				ETD[6];				//预计起飞时间
	char				ETA[6];				//预计降落时间
	char				ATD[6];				//实际起飞时间
	char				ATA[6];				//实际降落时间
	TAG_SITA_MUTIDEPARR mutiDepArr[4];		//多起降段航班的起降描述[仅非正班PLN使用]
	char				PutDownTime[6];		//撤轮档时间
	char				PutOnTime[6];		//挡轮档时间
	char				NextRptTime[6];		//下次通报时间[长期延误报使用]
	char				DLReason[64];		//延误原因[起飞延误\延误、长期延误报使用]
	unsigned short		DLTime;				//延误分钟数[起飞延误报使用]
	unsigned short		NumofAircrew;		//机组人数
	char				Weahter[10];		//天气标准
	char				SupInfo[128];		//SI补充信息
};

#ifdef AIX
#pragma	pack(pop)
#else
#pragma	pack()
#endif

#endif
