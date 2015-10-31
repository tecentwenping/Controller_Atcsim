//环境包所需要的结构 by  wmq 2010.3.5

#ifndef _ENV_STRUCT_H_
#define _ENV_STRUCT_H_

#include "Serial_Base.h"
#include <vector>
#include <string>

using namespace std;

struct RunWayFricInfo
{
	int m_iRunWayID;
	double m_dFricNum;
	RunWayFricInfo()
	{
		m_iRunWayID=-1;
		m_dFricNum=-1.0;
	}
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRunWayID & m_dFricNum;
	}

};
//!动态环境数据结构
struct AirportRunInfo
{
	AirportRunInfo()
	{
		m_iAirportID=0;
		m_dQFE=-1;
		m_dQNH=-1;
		m_dVisibility=-1;
		m_dWindSpd=-1;
		m_dWindDir=-1;
	}

	int m_iAirportID;
	double m_dQFE;
	double m_dQNH;
	double m_dVisibility;
	double m_dWindSpd;
	double m_dWindDir;
	vector<int> m_envTime;
	std::vector<RunWayFricInfo>m_vRunWayFricInfo;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_dQFE & m_dQNH & m_dVisibility & m_dWindSpd & m_dWindDir & m_envTime & m_vRunWayFricInfo;
	}
};

enum ENV_OBJ_TYPE
{
	NONETYPE=0,
	CLOUD=9,
	CLOUDTYPE=15,
	STRAW_SMOKE=100,
	FIRE_WORKS=101,
	RADIANT_FOG=102,
	WORKAREA=103,
};

struct ST_POS_INTENSITY
{
public:
	ST_POS_INTENSITY();
	ST_POS_INTENSITY(ST_POS_INTENSITY const& lightningInf);
	virtual ~ST_POS_INTENSITY();

	ST_POS_INTENSITY& operator=(ST_POS_INTENSITY const& lightningInf);
public:
	int iLevel;			//强度等级
	//x, y, z位置信息	在机场中心点坐标中的位置
	double dXPos;
	double dYPos;
	double dZPos;

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iLevel & dXPos & dYPos & dZPos;
	}
};


struct RFogCreateDeleteInfo
{
	int iRFogID;
	bool bIsCreate;//true 创建 false删除
	ST_POS_INTENSITY RFogInfo;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iRFogID & bIsCreate & RFogInfo;
	}
};

enum SmokeType
{
	JIGAN=0,
	YANHUA=1,
};

struct SmokeCreateDeleteInfo
{
	int iSmokeID;
	SmokeType smokeType;
	bool bIsCreate;//true 创建 false删除
	ST_POS_INTENSITY SmokeInfo;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iSmokeID & smokeType & bIsCreate & SmokeInfo;
	}
};

struct ST_WorkArea
{
	double dCenterX;
	double dCenterY;
	double dCenterZ;
	double dLength;
	double dWidth;
	double dHeading;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & dCenterX & dCenterY& dCenterZ &dLength & dWidth &dHeading;
	}
};

struct WorkAreaCreateDeleteInfo
{
	int iWorkAreaID;
	bool bIsCreate;
	ST_WorkArea workArea;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iWorkAreaID & bIsCreate & workArea;
	}
};
// 跑道视程的定义
struct ST_RVR
{
	int iRunwayID;
	int iPosInRunway;  //在跑道上的点  0: 跑道起点，1: 跑道中点, 2. 跑道结束点
	double dRVR;
};

struct ST_RUNWAY_ENV
{
public:
	ST_RUNWAY_ENV();
	ST_RUNWAY_ENV(ST_RUNWAY_ENV const& runwayEnv);
	virtual ~ST_RUNWAY_ENV();
	ST_RUNWAY_ENV& operator=(ST_RUNWAY_ENV const& runwayEnv);
public:
	int iRunwayID;			/* 跑道ID */ 
	double dTemperature;	/* 温度 默认0 */
	double dDewpoint;		/* 露点 默认0 */
	double dWindSpd;		/* 风速 默认0 */
	double dWindDir;		/* 风向 默认0 */
	double dStartCBase;		/* 跑道起点 最低云低高 默认3000*/
	double dEndCBase;		/* 跑道终点 最低云低高 默认3000*/
	double dStartRVR;		/* 开始段 视程 */
	double dMidRVR;			/* 中间段 视程 */
	double dEndRVR;			/* 结束段 视程 */
	//double dVis;			/* 能见度 */
	double dQNH;			/* 修正海压 默认1000 */
	double dQFE;			/* 场压 默认1000 */
	int iLight;				/* 该跑道的边灯灯光等级相关 */	

	//lichun 2011.03.30
	double dRandomWindSpd;		/* 保存由核心随机出来的风速 平均风*/
	double dRandomWindDir;		/* 保存由核心随机出来的风向 平均风*/

	int    m_iIsGuestingWindSpd;/* 是否为实时风速；1：不设置实时风速；2实时风速*/
	double dWindMaxSpd;			/* 保存教员位设置的风速最大值*/
	double dWindMinSpd;			/* 保存教员位设置的风速最小值*/
	double dRandomWindMaxSpd;	/* 保存由核心随机出来的风速最大值*/
	double dRandomWindMinSpd;	/* 保存由核心随机出来的风速最小值*/

	int    m_iIsGuestingWindDir;/* 是否为实时风向；1：不设置实时风向；2实时风向*/
	int    m_iWindDirection;	/* 1：向左；2：向右*/
	double m_dGuestingWindDir;	/* 保存教员位设置的实时风向*/
	double m_dGuestingRandomWindDir;	/* 保存核心随机出来的实时风向*/
	double m_dFrictionNum;       //摩擦系数
public:
	/*
	void ReadFromBuffer(const char* pBuffer);
	void WriteToBuffer(char* pBuffer);
	int GetBufferSize();
	*/
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iRunwayID & dTemperature & dDewpoint & dWindSpd & dWindDir & dStartCBase & dEndCBase & dStartRVR
			& dMidRVR & dEndRVR & dQNH & dQFE & iLight	 & dRandomWindSpd & dRandomWindDir & m_iIsGuestingWindSpd
			& dWindMaxSpd & dWindMinSpd & dRandomWindMaxSpd & dRandomWindMinSpd & m_iIsGuestingWindDir
			& m_iWindDirection & m_dGuestingWindDir & m_dGuestingRandomWindDir & m_dFrictionNum;
	}
};




struct ST_AirportEnvBaseData
{
public:
	ST_AirportEnvBaseData();
	virtual ~ST_AirportEnvBaseData();
	ST_AirportEnvBaseData& operator=(ST_AirportEnvBaseData const& envBaseData);

public:
	// 环境所属的机场
	int m_iAirportID;
	int m_iAirspaceID;			/* 适用于哪个管制区 */
	int m_iRainLevel;			/* 雨量，分1~3级，0代表无雨 */
	int m_iSnowLevel;			/* 雪量，分1~3级，0代表无雪 */

	//扬沙拂尘雾的强度通过调整能见度来体现.
	bool m_bLightningOn;		//是否有闪电,有闪电,则视景端随机.
	bool m_bFogOn;	//是否开启全局雾. 强度等级通过能见度来体现
	bool m_bHazeOn;
	bool m_bRisenDustOn;		//是否开启扬沙, 开启则速度与移动方向与风速风向关联. 开启扬沙则同时开启拂尘.

	////开启拂尘不一定开启扬沙暂时不管席位端和视景服务器端的处理.计算这样一个数据并切发送出去.
	int m_iDustLevel;			//浮尘浓度等级, 0级表示没有浮尘.
	double m_dDewpoint;		//整个机场的露点信息。
	double m_dWindSpd;		/* 风速 默认0 */
	double m_dWindDir;		/* 风向 默认0 */
	double m_dQFE; // 场压
	double m_dQNH; // 修正海压

	double m_dVisibility; // 能见度
	double m_dTemperature; // 温度
	//SYSTEMTIME m_envTime;	//训练计划在几时几分几秒开始.然后按这个时间往下走.如9:00:00开始,过一分钟
	//就是9:01:00.(显示在席位时钟上).目前这个时间时钟是1899年12月30日0:00:00.
	//去除对Windows的依赖, vector里分别放, 年 月 日 时 分 秒的信息
	vector<int> m_envTime;
	std::string  m_strModelName;// the index of used airport model file name

	std::vector<ST_POS_INTENSITY> m_vSmoke;		//烟---动态创建信息
	std::vector<ST_POS_INTENSITY> m_vRadiantFog; //辐射雾---动态创建信息
	std::vector<ST_POS_INTENSITY> m_vWorkArea;//施工区域创建信息

public:
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
	//boost序列化
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iAirspaceID & m_iRainLevel & m_iSnowLevel & m_bLightningOn
			& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dDewpoint & m_dWindSpd
			& m_dWindDir & m_dQFE & m_dQNH & m_dVisibility & m_dTemperature & m_envTime & m_strModelName
			& m_vSmoke & m_vRadiantFog & m_vWorkArea;
	}
};
//修改 2010.3.5 

struct ST_AirportEnvForEnvPacket
{
public:
	ST_AirportEnvForEnvPacket();
	virtual ~ST_AirportEnvForEnvPacket();
public:
	ST_AirportEnvBaseData m_airportEnvBaseData;
	vector<ST_RUNWAY_ENV> m_vRunwayEnv;	//跑道环境
	ST_AirportEnvForEnvPacket &operator=(ST_AirportEnvForEnvPacket const& temp);
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_airportEnvBaseData & m_vRunwayEnv;
	}
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
};
/*
//视景要求数据独立出来,单独维护, 单独处理
struct ST_AirportEnvBaseData_VS
{
public:
ST_AirportEnvBaseData_VS();
virtual ~ST_AirportEnvBaseData_VS();
ST_AirportEnvBaseData_VS& operator=(ST_AirportEnvBaseData_VS const& envBaseData);

public:
// 环境所属的机场
int m_iAirportID;
int m_iRainLevel;			/* 雨量，分1~3级，0代表无雨 */
//int m_iSnowLevel;			/* 雪量，分1~3级，0代表无雪*/
/*
//扬沙拂尘雾的强度通过调整能见度来体现.
bool m_bLightningOn;		//是否有闪电,有闪电,则视景端随机.
bool m_bFogOn;	//是否开启全局雾. 强度等级通过能见度来体现
bool m_bHazeOn;
bool m_bRisenDustOn;		//是否开启扬沙, 开启则速度与移动方向与风速风向关联. 开启扬沙则同时开启拂尘.

////开启拂尘不一定开启扬沙暂时不管席位端和视景服务器端的处理.计算这样一个数据并切发送出去.
int m_iDustLevel;			//浮尘浓度等级, 0级表示没有浮尘.
double m_dWindSpd;		/* 风速 默认0 */
//double m_dWindDir;		/* 风向 默认0 */

//double m_dVisibility; // 能见度
//double m_dTemperature; // 温度

//SYSTEMTIME m_envTime;	//训练计划在几时几分几秒开始.然后按这个时间往下走.如9:00:00开始,过一分钟
//就是9:01:00.(显示在席位时钟上).目前这个时间时钟是1899年12月30日0:00:00.
//去除对Windows的依赖, vector里分别放, 年 月 日 时 分 秒的信息
//vector<int> m_envTime;
/*
std::string  m_strModelName;// the index of used airport model file name
vector<ST_POS_INTENSITY> m_vSmoke;		//烟---强度和位置信息
vector<ST_POS_INTENSITY> m_vRadiantFog; //辐射雾---强度和位置信息
bool m_bTriggerOneLightning;
bool m_LightningInf;
public:
//boost序列化
template<typename Archive>
Archive& serialize(Archive& ar,const unsigned int version)
{
return ar & m_iAirportID & m_iRainLevel & m_iSnowLevel & m_bLightningOn
& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dWindSpd
& m_dWindDir & m_dVisibility & m_dTemperature & m_envTime & m_strModelName
& m_vSmoke & m_vRadiantFog & m_bTriggerOneLightning & m_LightningInf;
}
*/
/*
virtual void ReadFromBuffer(const char* pBuffer);
virtual void WriteToBuffer(char* pBuffer);
virtual int GetBufferSize();
*/
//};
/*
struct ST_AirportEnvForVisServer
{
public:
ST_AirportEnvForVisServer();
virtual ~ST_AirportEnvForVisServer();
ST_AirportEnvForVisServer& operator=(ST_AirportEnvForVisServer const& temp);
public:
ST_AirportEnvBaseData_VS m_airportEnvBaseData;
bool m_bTriggerOneLightning; //是否触发一次闪电
ST_POS_INTENSITY m_LightningInf;	//人为触发的闪电的信息
public:
/*
virtual void ReadFromBuffer(const char* pBuffer);
virtual void WriteToBuffer(char* pBuffer);
virtual int GetBufferSize();
*/
/*
template<typename Archive>
Archive& serialize(Archive& ar,const unsigned int version)
{
return ar &m_airportEnvBaseData&m_bTriggerOneLightning&m_LightningInf;
}
};
*/
#endif
