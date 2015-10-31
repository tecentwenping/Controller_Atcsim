#ifndef PUBLIC_BASICTYPE_H
#define PUBLIC_BASICTYPE_H
#include "public/BaseTypeDefine/PublicTypeDefine.h"
#include <vector>
using namespace std;
struct ST_TimePlan
{
	double dPlanStartTime;//<�ƻ��Ŀ�ʼʱ��
	double  dPlanEndTime;//<�ƻ��Ľ���ʱ��
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

//��ļƻ���Ϣ
struct ST_WindPhasePlan
{
	int iTimePoint;//<����ڱ��ƻ���ST_TimePlan�Ŀ�ʼʱ���ʱ�����
	double dWindSpeed;//����
	double dWindDirection;//����
};
struct ST_WindPlan
{
	ST_TimePlan windTimePlan;
	std::vector<ST_WindPhasePlan> vWindPlan;//��ÿ��ʱ���ϵķ�ȼ�ֵ��
};
//��ƻ�
struct ST_RainPhasePlan
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����D
	int iRainLevel;
};
struct ST_RainPlan
{
	ST_TimePlan rainTimePlan;
	std::vector<ST_RainPhasePlan> vRainPlan;
};

struct ST_SnowPhasePlan //ѩ�Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	int  iSnowLevel;//ѩ�ȼ�
};
struct ST_SnowPlan //ѩ��ȫ���ƻ�
{
	ST_TimePlan snowTimePlan;
	std::vector<ST_SnowPhasePlan> vSnowPlan;//��ÿ��ʱ���ϵ�ѩ�ȼ�ֵ��
};

struct ST_TemperaturePhasePlan //�¶ȵĽ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	double dTemperature;//�¶ȵȼ�
};
struct ST_TemperaturePlan //�¶ȵ�ȫ���ƻ�
{
	ST_TimePlan temperatureTimePlan;
	std::vector<ST_TemperaturePhasePlan> vTemperaturePlan;//��ÿ��ʱ���ϵ��¶ȵȼ�ֵ��
};

struct ST_DewpointPhasePlan //¶��Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	double dDewPoint;//¶��ȼ�
};
struct ST_DewpointPlan //¶���ȫ���ƻ�
{
	ST_TimePlan dewpointTimePlan;
	std::vector<ST_DewpointPhasePlan> vDewpointPlan;//��ÿ��ʱ���ϵ��¶ȵȼ�ֵ��
};

struct ST_VisibilityPhasePlan //�ܼ��ȵĽ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	double dVisibility;//�ܼ���ֵ
};
struct ST_VisibilityPlan //�ܼ��ȵ�ȫ���ƻ�
{
	ST_TimePlan visibilityTimePlan;
	std::vector<ST_VisibilityPhasePlan> vVisibilityPlan;//��ÿ��ʱ���ϵ��ܼ���ֵ��
};

struct ST_QFEPhasePlan //QFE�Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	double dQFE;//QFEֵ
};
struct ST_QFEPlan //QFE��ȫ���ƻ�
{
	ST_TimePlan QFETimePlan;
	std::vector<ST_QFEPhasePlan> vQFEPlan;//��ÿ��ʱ���ϵ�QFEֵ��
};

struct ST_QNHPhasePlan //QNH�Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	double dQNH;//QNHֵ
};
struct ST_QNHPlan //QNH��ȫ���ƻ�
{
	ST_TimePlan QNHTimePlan;
	std::vector<ST_QNHPhasePlan> vQNHPlan;//��ÿ��ʱ���ϵ�QNHֵ��
};


struct ST_FogPhasePlan //Fog�Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	bool bFogOn;//Fogֵ
};

struct ST_FogPlan //Fog��ȫ���ƻ�
{
	ST_TimePlan FogTimePlan;
	std::vector<ST_FogPhasePlan> vFogPlan;//��ÿ��ʱ���ϵ�Fogֵ��
};

struct ST_HazePhasePlan //���Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	bool bHazeOn;//��ֵ
};

struct ST_HazePlan
{
	ST_TimePlan HazeTimePlan;
	std::vector<ST_HazePhasePlan> vHazePlan;//��ÿ��ʱ���ϵĳ���
};

struct ST_DustPhasePlan //���Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	bool bDustOn;//��ֵ
};

struct ST_DustPlan
{
	ST_TimePlan DustTimePlan;
	std::vector<ST_DustPhasePlan> vDustPlan;//��ÿ��ʱ���ϵĳ�ֵ��
};


struct ST_RisenDustPhasePlan //���Ľ׶μƻ�
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	bool bRisenDustOn;//��ֵ
};

struct ST_RisenDustPlan
{
	ST_TimePlan RisenDustTimePlan;
	std::vector<ST_RisenDustPhasePlan> vRisenDustPlan;//��ÿ��ʱ���ϵĳ�ֵ��
};

struct ST_LightingPhasePlan
{
	int iTimePoint;//��Կ�ʼʱ���ʱ�����
	int iLightingLevel;
	double dRadious;//����
	double dDirection;//��λ
};
struct ST_LightingPlan
{
	ST_TimePlan LightingTimePlan;
	std::vector<ST_LightingPhasePlan> vLightingPlan;//��ÿ��ʱ���ϵ�����ֵ��
};

struct ST_RVRPhasePlan
{

};
struct ST_RVRPlan
{

};
struct SKY_TYPE
{
	EM_CLOUD_TYPE eType;//�������
	int nShapeID;//����ID,��ǰÿ�����͵�����ṩ3�ֱ�����ʽ��0,1,2.
};

struct EnviromentPlan
{
int m_iStartTime;//����������ʼʱ��
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