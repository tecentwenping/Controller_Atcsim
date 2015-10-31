#pragma once
#include "..\serial_base.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"
#include "public/BaseTypeDefine/EnvTypeDefine/EnvStruct.h"

/** 
 \brief		环境数据类
 \details   有ATG发送给视景使用的环境
 \author    
 \date      2013-06-03
*/
class AirportEnvData
{
public:
	int m_iAirportID;			// 环境所属的机场
	int m_iRainLevel;			/* 雨量，分1~3级，0代表无雨 */
	int m_iSnowLevel;			/* 雪量，分1~3级，0代表无雪 */

	//扬沙拂尘雾的强度通过调整能见度来体现.
	bool		m_bLightningOn;		//是否有闪电,有闪电,则视景端随机.
	bool		m_bFogOn;				//是否开启全局雾. 强度等级通过能见度来体现
	bool        m_bHazeOn;
	bool		m_bRisenDustOn;		//是否开启扬沙, 开启则速度与移动方向与风速风向关联. 开启扬沙则同时开启拂尘.

	////开启拂尘不一定开启扬沙暂时不管席位端和视景服务器端的处理.计算这样一个数据并切发送出去.
	int		m_iDustLevel;			//浮尘浓度等级, 0级表示没有浮尘.
	double  m_dWindSpd;		/* 风速 默认0 */
	double  m_dWindDir;		/* 风向 默认0 */

	double m_dVisibility; // 能见度
	double m_dTemperature; // 温度
	std::vector<int> m_vectEnvTime;	//训练计划当前时间:X年X月X日X时X分X秒

	std::string  m_strModelName;// the index of used airport model file name
	std::vector<ST_POS_INTENSITY> m_vSmoke;		//烟---强度和位置信息
	std::vector<ST_POS_INTENSITY> m_vRadiantFog; //辐射雾---强度和位置信息
	bool				m_bTriggerOneLightning; //是否触发一次闪电
	ST_POS_INTENSITY	m_LightningInf;	//人为触发的闪电的信息
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iRainLevel & m_iSnowLevel & m_bLightningOn 
			& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dWindSpd & m_dWindDir
			& m_dVisibility & m_dTemperature & m_vectEnvTime &m_strModelName &m_vSmoke 
			& m_vRadiantFog & m_bTriggerOneLightning & m_LightningInf;
	}
};

/** 
 \brief		云数据类
 \details   由ATG发送给视景使用的云数据
 \author    
 \date      2013-06-03
*/

class CloudData
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

/** 
 \brief		运动目标数据类
 \details   有ATG发送给视景使用的对象目标
 \author    
 \date      2013-06-03
*/
class MovingObjForVIS
{
public:
	double dSpd;
	int     ObjID;
	int     iMainAirportID; 

	double	PosX;           //x, y,	z位置信息	在机场中/心点坐标中的位置
	double	PosY;
	double	PosZ;

	double	Heading;           //h,p,r位置信息
	double	Pitch;
	double	Roll;

	double	TrackHdg;

	unsigned char WheelFire; 
	unsigned char GearStatus;  // every bit indicates a gear's status 起落架
	unsigned char EngineSmoke; // every bit indicates a engine's smoke's status on/off
	unsigned char EngineFire;  // every bit indicates a engine's fire's status on/off

	ENUM_STATE_TYPE eStateType; //运动状态
		unsigned  char SignalStatus; //信号灯状态
	int Status; //目标状态

	// 32-bit从低到高分别表示			  1  / 0
	// 0: 飞机的状态:					  SHOW / HIDE
	// 1: 影子的状态:					  SHOW / HIDE
	// 2: Taxing Light Status:			  ON / OFF 
	// 3: Strobe Light Status:			  ON / OFF
	// 4: Collision Light Status:		  ON / OFF
	// 5: Search Light Status:			  ON / OFF
	// 6: Search Light's Shade Status:	  ON / OFF
	// 7: Landing Light Status:			  ON / OFF
	// 8: Landing Light's Shade Status:	  ON / OFF
	// 9: Airscrew Status:				  ON / OFF if ON check bit 10
	// 10: Airscrew Status:				  FAST / SLOW 
	// 11: Touch Smoke					  ON / OFF
	// 12: Force Smoke					  ON / OFF
	// 13: Crash						  ON / OFF
	// 14: Flap							  IN / OUT // reserved in this version
	// 15: Parachute					  OPEN / DISCARD
	// 16: left rub smoke
	// 17: right rub smoke
	// 18: splash mub show
	// 19: JinYi                          ON / OFF
	// 20: JianSuBan                      ON / OFF
	// 21: FANPEN                         ON / OFF
	// 22: Trail Smoke                    ON / OFF
	// 23: aileron         	              ON / OFF //副翼开关
	// 24: yellow soil smoke              ON / OFF
	// 21~31: Reserved
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & dSpd & ObjID & iMainAirportID & PosX & PosY & PosZ & Heading & Pitch & Roll
			& TrackHdg & WheelFire & GearStatus & EngineSmoke & EngineFire & eStateType
			& SignalStatus & Status;
	}
};

/** 
 \brief		特效数据类
 \details   有ATG发送给视景使用的特效
 \author    
 \date      2013-06-03
*/

class EffectOBJPacket
{
public:

	int	ObjID; //唯一标识

	double	PosX;           //x, y,	z位置信息	在机场中/心点坐标中的位置
	double	PosY;
	double	PosZ;

	double	Heading;           //h,p,r位置信息
	double	Pitch;
	double	Roll;

	double	dSpd; //速度
	bool	bShow; //是否显示
	ENUM_OBJ_TYPE  eObjType; // 运动目标的类型（飞机、车辆、云、环境、编队）
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjID & PosX & PosY & PosZ & Heading & Pitch & Roll
			& dSpd & bShow & eObjType;
	}
};

//航空器控制命令包（机长席位使用）
class FramePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FramePacket);

public:
	std::vector<MovingObjForVIS> m_vObjs;
	vector<AirportEnvData> m_vEnvs;	
	std::vector<CloudData> m_vClouds;
	std::vector<EffectOBJPacket> m_vEffectObj;

	int m_iTickCount;	// 帧包计数
private:
	SERIALIZE_PACKET(m_vObjs & m_vEnvs & m_vClouds & m_vEffectObj & m_iTickCount);
};

