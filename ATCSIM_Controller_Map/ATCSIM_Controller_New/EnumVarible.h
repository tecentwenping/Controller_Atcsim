#ifndef _ENUMVARIBLE_H
#define _ENUMVARIBLE_H

//可调整亮度的图元类型
enum BRIGHTNESS_SUB_TYPE
{
	SUB_DEFAULT = 0,
	SUB_SYMBOL,
	SUB_LABEL,
	SUB_STRIP,
	SUB_MAP,
	SUB_TOOL,
	SUB_ROUTE,
	SUB_END
};

//标牌字体大小
enum LABEL_FONT_SIZE
{
	SIZE_SMALL = 0,
	SIZE_MIDDLE,
	SIZE_LARGE
};

//雷达类型
enum ENUM_RADAR_TYPE
{
	TYPE_NORM = 0, //综合雷达
	TYPE_MONO,     //单雷达
	TYPE_BYPASS
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

//航迹类型
enum AIRCRAFT_SYMBOL_TYPE
{
	SYMBOL_INVALID = -1,
	SYMBOL_COMBINED = 0,  //一二次雷达融合航迹
	SYMBOL_PRIMARY,       //一次雷达航迹
	SYMBOL_SECONDARY,     //二次雷达航迹
	SYMBOL_PLAN,          //计划航迹
	SYMBOL_COAST,         //外推航迹
	SYMBOL_SPI,           //SPI告警航迹
	SYMBOL_ADSB,		  //ADSB航迹
	SYMBOL_VEHICLE,       //车辆航迹
	SYMBOL_PIC_AIRCRAFT,  //航空器图片航迹
	SYMBOL_PIC_HELICOPTER,//直升机图片
	SYMBOL_PIC_VEHICLE,   //车辆图片航迹
};

//告警类型
enum WARNING_TYPE
{
	TYPE_EMG = 0,
	TYPE_RCF,
	TYPE_HIJ,
	TYPE_STCA,
	TYPE_MSAW,
	TYPE_CLAM,
	TYPE_DAIW,
	TYPE_SPI,
	TYPE_SC,
	TYPE_YAW,
	TYPE_RVSM
};

//单位类型，公英制
enum UNIT_TYPE
{
	UNIT_METRIC = 0,//公制
	UNIT_IMPERIAL,  //英制
	UNIT_END
};

enum ALARM_TYPE
{
	ALARM_BEGIN = 0,
	EMG = 0,
	HIJ,
	RCF,
	STCA,
	MSAW,
	CLAM,
	DAIW,
	SPI,
	RAM,
	TDAW,
	DUPE,
	ALARM_END
};

enum LABEL_TYPE
{
	CTRL_DEFAULT,
	OWN_CONTROLLED, //自我管制
	UN_CONTROLLED,	//未管制
	PREACTIVE,      //预激活
	HAND_IN,        //移交入
	HAND_OUT,       //移交出
};//标牌类型


enum RUNNING_STATUS
{
	RUNNING = 0,
	FROZEN,
	END
};

//随机作图中点的类型
enum ENUM_RANDOMPOINT_TYPE
{
	RPT_TRIANGLE = 0,
	RPT_CIRCLE,
	RPT_RECT,
};


#endif