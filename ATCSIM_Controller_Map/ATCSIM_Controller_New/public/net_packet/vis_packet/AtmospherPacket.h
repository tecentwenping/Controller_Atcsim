#include "public/BaseTypeDefine/EnvTypeDefine/CloudDataDefine.h"
#include "public/BaseTypeDefine/EnvTypeDefine/EnvStruct.h"
struct ST_CloudDataForVisGen
{
public:
	int iCloudID;
	double m_dPosX; // 云中心所在的位置.
	double m_dPosY;
	double m_dPosZ;
	EM_CLOUD_TYPE eType;	//云的类型.
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCloudID & m_dPosX & m_dPosY & m_dPosZ & eType;
	}
};

struct ST_AirportEnvDataForVis // 视景位需要的环境信息
{
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iRainLevel & m_iSnowLevel & m_bLightningOn 
			& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dWindSpd & m_dWindDir
			& m_dVisibility & m_dTemperature & m_envTime &m_strModelName &m_vSmoke 
			& m_vRadiantFog  & m_bTriggerOneLightning & m_LightningInf;
	}
public:
	// !环境所属的机场
	int m_iAirportID;
	int m_iRainLevel;			//!<雨量，分1~3级，0代表无雨
	int m_iSnowLevel;			//!< 雪量，分1~3级，0代表无雪

	bool		m_bLightningOn;		//!<是否有闪电,有闪电,则视景端随机.
	bool		m_bFogOn;				//!<是否开启全局雾. 强度等级通过能见度来体现
	bool        m_bHazeOn;
	bool		m_bRisenDustOn;		//!<是否开启扬沙, 开启则速度与移动方向向关联. 与风速风开启扬沙则同时开启拂尘.

	////开启拂尘不一定开启扬沙暂时不管席位端和视景服务器端的处理.计算这样一个数据并切发送出去.
	int		m_iDustLevel;			//!<浮尘浓度等级, 0级表示没有浮尘.
	double  m_dWindSpd;		//!< 风速 默认0 
	double  m_dWindDir;		//!<风向 默认0 

	double m_dVisibility; // !<能见度
	double m_dTemperature; // !<温度
	std::vector<int> m_envTime;	//!<训练计划当前时间:X年X月X日X时X分X秒

	std::string  m_strModelName;// !<the index of used airport model file name
	std::vector<ST_POS_INTENSITY> m_vSmoke;		//烟---强度和位置信息
	std::vector<ST_POS_INTENSITY> m_vRadiantFog; //辐射雾---强度和位置信息
	bool		m_bTriggerOneLightning; //!<是否触发一次闪电
	ST_POS_INTENSITY	m_LightningInf;	//!<人为触发的闪电的信息
};

class AtmospherPacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AtmospherPacket );
public:
	AtmospherPacket& operator = (const AtmospherPacket& vRight)
	{
		m_EnvData = vRight.m_EnvData;
		m_CloudData = vRight.m_CloudData;
		return *this; 
	}

public:
	std::vector<ST_AirportEnvDataForVis>   m_EnvData;
	std::vector<ST_CloudDataForVisGen> m_CloudData;
	std::vector<SmokeCreateDeleteInfo> m_vSmoke;		//!<烟---动态创建信息
	std::vector<RFogCreateDeleteInfo> m_vRadiantFog; //!<辐射雾---动态创建信息
	std::vector<WorkAreaCreateDeleteInfo> m_vWorkArea;//!<施工区域创建信息
	SERIALIZE_PACKET( m_EnvData& m_CloudData )
};
