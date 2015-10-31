#ifndef _FDP_TYPE_DEFINE_HEADER
#define _FDP_TYPE_DEFINE_HEADER

#include <string>
#include <vector>

//飞机类别
enum ACFT_CLASS_TYPE
{
    ACFT_UNKNOWN = 0,
    ACFT_A, 
    ACFT_B, 
    ACFT_C1, 
    ACFT_C2, 
    ACFT_C3, 
    ACFT_C4, 
    ACFT_D, 
    ACFT_E
};

//飞行计划类别
enum PLAN_CLASS
{
    PLAN_CLS_NORMAL = 0,
    PLAN_CLS_TAG
};

//计划被修改的内容等级
enum PLAN_CHANGE
{
    CH_NONE = 0,        //没有改变
    CH_DESCRIPTION = 1, //描述性内容改变
    CH_STATUS = 2,      //状态改变
    CH_TIMESPEED = 4,   //时间、速度、高度改变
    CH_ROUTESTRING = 8, //航路串改变
    CH_CREATE = 16,     //计划创建
    CH_DELETE = 32      //计划删除
};

//计划的状态
enum PLAN_STATUS
{
    FUTR = 0, //未来(收到PLN)
    NACT,     //静止(收到FPL)
    PREA,     //预激活(预计起飞时间前半小时)
    COOR,     //协调
    HAND,     //移交
    CONT,     //控制
    FIN,      //完成
    CNL       //取消
};

//与航迹配对的状态
enum PAIR_STATUS
{
    NOTCOUPLE = 0,  //没有配对
    LOSSCOUPLE,     //丢失配对
    MANUALCOUPLE,   //人工配对
    DEMANUALCOUPLE, //人工去配对
    AUTOCOUPLE,     //自动配对
    DEAUTOCOUPLE    //自动去配对
};

// 飞行类型
enum CPL_TYPE
{ 
    UNKNOWN=0,      //未知
    EXTERNAL_INBD,	//区域外-入港
    DOMES_INBD,     //区域内-入港
    EXTERNAL_OUTBD, //区域外-出港
    DOMES_OUTBD,    //区域内-出港
    BYPASS,         //本场迂回(飞出飞入)						 

    EXTERNAL_ADP_INBD,  //区域外-其他机场入港
    EXTERNAL_ADP_OUTBD, //区域内-其他机场之间飞行
    DOMESTIC,           //区域内其他机场迂回(飞出飞入)	
    DOMES_BYPASS,

    OVERFLY             //飞越管制区
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

enum RVSM_STATUS
{
    RVSM_RVA = 0,   //获准RVSM运行
    RVSM_RVN,       //未获准RVSM运行
    RVSM_RVX,       //豁免RVSM运行
    RVSM_RVU,       //未知是否获准RVSM运行
    RVSM_RVT        //由于气流/故障等影响取消RVSM
};

//航路点位置类型
enum RPP_TYPE
{
    RPP_IN = 0, //区域内
    RPP_BPN,    //入界点
    RPP_BPX,    //出界点
    RPP_OUT     //区域外
};

//进程单航路点
struct TAG_STRIP_POINT
{
    std::string Code;      //航路点名称
    RPP_TYPE	Type;	   //航路点位置类型 ，用于判断点为区域内或区域外
    std::string ETOP;      //过点时间（预达此点时间/实际过点时间：根据过点序号判断）
    std::string PCL;       //过点高度（预设许可高度）
    int         Speed;     //速度
    double      Longitude; //经度
    double      Lat;       //纬度

public:
    template<typename Archive>
    Archive& serialize(Archive& ar, const unsigned int version)
    {
        return ar & Code & Type & ETOP & PCL & Speed & Longitude & Lat; 
    }
};

//管制移交包类型
enum ENUM_HANDOVER_TYPE
{
    HANDOVER_NONE = 0,     //未知
    HANDOVER_START,        //发起移交
    HANDOVER_CANCEL,       //取消移交
    HANDOVER_ACCEPTE,      //接收移交
    HANDOVER_REFUSE,       //拒绝移交
    HANDOVER_RELEASE,      //释放控制
    HANDOVER_FORCE,        //强制接管
}; 

enum ENUM_FLIGHTPLAN_OPERRTYPE
{
    FLIGHTPLAN_ADD = 0,    //增加飞行计划
    FLIGHTPLAN_MODIFY      //修改飞行计划
};

//等待类型
enum ENUM_HOLD_TYPE
{
    HOLD_START = 0,     //开始等待
    HOLD_END            //结束等待
};

//手动相关/去相关
enum ENUM_COUPLE_INFO
{
    COUPLE = 0,     //相关
    DECOUPLE        //去相关
};

//简标牌操作
enum ENUM_TAG_TYPE
{
    TAG_ADD = 0,   //增加
    TAG_DELETE,    //删除
    TAG_MODIFY     //修改
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
    std::vector<TAG_STRIP_POINT> stripPoints;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & CurMID & UpdateTime & CplStatus & ATD & ATA & CurSec 
            & CtrlSec & AcpSec & NextSecs & PRL & CFL & RouteStr & HoldPoint
			& HoldMinute & HoldTime & TrackNo & PairStatus & rvsmStatus & pointSum 
            & pointPassed & stripPoints; 
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

#endif //_FDP_TYPE_DEFINE_HEADER