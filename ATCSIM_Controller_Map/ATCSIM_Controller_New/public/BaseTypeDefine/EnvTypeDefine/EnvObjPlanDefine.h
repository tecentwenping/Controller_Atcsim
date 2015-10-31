#ifndef PUBLIC_BASICTYPE_H
#define PUBLIC_BASICTYPE_H
#include "public/BaseTypeDefine/PublicTypeDefine.h"
#include <vector>
using namespace std;
struct ST_TimePlan
{
	double dPlanStartTime;//<计划的开始时间
	double  dPlanEndTime;//<计划的结束时间
	ST_TimePlan()
	{
		dPlanStartTime=0;
		dPlanEndTime=0;
	}
	ST_TimePlan& operator=(ST_TimePlan const &p)
	{
		this->dPlanStartTime=p.dPlanStartTime;
		this->dPlanEndTime=p.dPlanEndTime;
		return *this;
	}
};

//风的计划信息
struct ST_WindPhasePlan
{
	int iTimePoint;//<相对于本计划中ST_TimePlan的开始时间的时间计数
	double dWindSpeed;//风速
	double dWindDirection;//风向
};
struct ST_WindPlan
{
	ST_TimePlan windTimePlan;
	std::vector<ST_WindPhasePlan> vWindPlan;//在每个时刻上的风等级值。
};
//雨计划
struct ST_RainPhasePlan
{
	int iTimePoint;//相对开始时间的时间计数D
	int iRainLevel;
};
struct ST_RainPlan
{
	ST_TimePlan rainTimePlan;
	std::vector<ST_RainPhasePlan> vRainPlan;
};

struct ST_SnowPhasePlan //雪的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	int  iSnowLevel;//雪等级
};
struct ST_SnowPlan //雪的全部计划
{
	ST_TimePlan snowTimePlan;
	std::vector<ST_SnowPhasePlan> vSnowPlan;//在每个时刻上的雪等级值。
};

struct ST_TemperaturePhasePlan //温度的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	double dTemperature;//温度等级
};
struct ST_TemperaturePlan //温度的全部计划
{
	ST_TimePlan temperatureTimePlan;
	std::vector<ST_TemperaturePhasePlan> vTemperaturePlan;//在每个时刻上的温度等级值。
};

struct ST_DewpointPhasePlan //露点的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	double dDewPoint;//露点等级
};
struct ST_DewpointPlan //露点的全部计划
{
	ST_TimePlan dewpointTimePlan;
	std::vector<ST_DewpointPhasePlan> vDewpointPlan;//在每个时刻上的温度等级值。
};

struct ST_VisibilityPhasePlan //能见度的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	double dVisibility;//能见度值
};
struct ST_VisibilityPlan //能见度的全部计划
{
	ST_TimePlan visibilityTimePlan;
	std::vector<ST_VisibilityPhasePlan> vVisibilityPlan;//在每个时刻上的能见度值。
};

struct ST_QFEPhasePlan //QFE的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	double dQFE;//QFE值
};
struct ST_QFEPlan //QFE的全部计划
{
	ST_TimePlan QFETimePlan;
	std::vector<ST_QFEPhasePlan> vQFEPlan;//在每个时刻上的QFE值。
};

struct ST_QNHPhasePlan //QNH的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	double dQNH;//QNH值
};
struct ST_QNHPlan //QNH的全部计划
{
	ST_TimePlan QNHTimePlan;
	std::vector<ST_QNHPhasePlan> vQNHPlan;//在每个时刻上的QNH值。
};


struct ST_FogPhasePlan //Fog的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	bool bFogOn;//Fog值
};

struct ST_FogPlan //Fog的全部计划
{
	ST_TimePlan FogTimePlan;
	std::vector<ST_FogPhasePlan> vFogPlan;//在每个时刻上的Fog值。
};

struct ST_HazePhasePlan //霾的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	bool bHazeOn;//霾值
};

struct ST_HazePlan
{
	ST_TimePlan HazeTimePlan;
	std::vector<ST_HazePhasePlan> vHazePlan;//在每个时刻上的尘。
};

struct ST_DustPhasePlan //尘的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	bool bDustOn;//尘值
};

struct ST_DustPlan
{
	ST_TimePlan DustTimePlan;
	std::vector<ST_DustPhasePlan> vDustPlan;//在每个时刻上的尘值。
};


struct ST_RisenDustPhasePlan //尘的阶段计划
{
	int iTimePoint;//相对开始时间的时间计数
	bool bRisenDustOn;//尘值
};

struct ST_RisenDustPlan
{
	ST_TimePlan RisenDustTimePlan;
	std::vector<ST_RisenDustPhasePlan> vRisenDustPlan;//在每个时刻上的尘值。
};

struct ST_LightingPhasePlan
{
	int iTimePoint;//相对开始时间的时间计数
	int iLightingLevel;
	double dRadious;//距离
	double dDirection;//方位
};
struct ST_LightingPlan
{
	ST_TimePlan LightingTimePlan;
	std::vector<ST_LightingPhasePlan> vLightingPlan;//在每个时刻上的闪电值。
};

struct ST_RVRPhasePlan
{

};
struct ST_RVRPlan
{

};
struct SKY_TYPE
{
	EM_CLOUD_TYPE eType;//天空类型
	int nShapeID;//外形ID,当前每种类型的天空提供3种表现形式，0,1,2.
};

struct EnviromentPlan
{
int m_iStartTime;//环境仿真起始时间
ST_WindPlan m_WindPlan;
ST_RainPlan m_RainPlan;
ST_SnowPlan m_SnowPlan;
ST_TemperaturePlan m_TemperaturePlan;
ST_DewpointPlan m_DewPointPlan;
ST_VisibilityPlan m_VisibilityPlan;
ST_QFEPlan m_QFEPlan;
ST_QNHPlan m_QNHPlan;
ST_FogPlan m_FogPlan;
ST_HazePlan m_HazePlan;
ST_DustPlan m_DustPlan;
ST_RisenDustPlan m_RisenDustPlan;
ST_LightingPlan m_LightingPlan;
};
#endif