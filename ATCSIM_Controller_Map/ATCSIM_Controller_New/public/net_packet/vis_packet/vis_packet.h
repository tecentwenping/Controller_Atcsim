#pragma once
#include "..\serial_base.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"
#include "public/BaseTypeDefine/EnvTypeDefine/EnvStruct.h"

/** 
 \brief		����������
 \details   ��ATG���͸��Ӿ�ʹ�õĻ���
 \author    
 \date      2013-06-03
*/
class AirportEnvData
{
public:
	int m_iAirportID;			// ���������Ļ���
	int m_iRainLevel;			/* ��������1~3����0�������� */
	int m_iSnowLevel;			/* ѩ������1~3����0������ѩ */

	//��ɳ�������ǿ��ͨ�������ܼ���������.
	bool		m_bLightningOn;		//�Ƿ�������,������,���Ӿ������.
	bool		m_bFogOn;				//�Ƿ���ȫ����. ǿ�ȵȼ�ͨ���ܼ���������
	bool        m_bHazeOn;
	bool		m_bRisenDustOn;		//�Ƿ�����ɳ, �������ٶ����ƶ���������ٷ������. ������ɳ��ͬʱ��������.

	////����������һ��������ɳ��ʱ����ϯλ�˺��Ӿ��������˵Ĵ���.��������һ�����ݲ��з��ͳ�ȥ.
	int		m_iDustLevel;			//����Ũ�ȵȼ�, 0����ʾû�и���.
	double  m_dWindSpd;		/* ���� Ĭ��0 */
	double  m_dWindDir;		/* ���� Ĭ��0 */

	double m_dVisibility; // �ܼ���
	double m_dTemperature; // �¶�
	std::vector<int> m_vectEnvTime;	//ѵ���ƻ���ǰʱ��:X��X��X��XʱX��X��

	std::string  m_strModelName;// the index of used airport model file name
	std::vector<ST_POS_INTENSITY> m_vSmoke;		//��---ǿ�Ⱥ�λ����Ϣ
	std::vector<ST_POS_INTENSITY> m_vRadiantFog; //������---ǿ�Ⱥ�λ����Ϣ
	bool				m_bTriggerOneLightning; //�Ƿ񴥷�һ������
	ST_POS_INTENSITY	m_LightningInf;	//��Ϊ�������������Ϣ
	//boost���л�
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
 \brief		��������
 \details   ��ATG���͸��Ӿ�ʹ�õ�������
 \author    
 \date      2013-06-03
*/

class CloudData
{
public:
	int iCloudID;
	double m_dPosX; // ���������ڵ�λ��.
	double m_dPosY;
	double m_dPosZ;
	EM_CLOUD_TYPE eType;	//�Ƶ�����.
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCloudID & m_dPosX & m_dPosY & m_dPosZ & eType;
	}
};

/** 
 \brief		�˶�Ŀ��������
 \details   ��ATG���͸��Ӿ�ʹ�õĶ���Ŀ��
 \author    
 \date      2013-06-03
*/
class MovingObjForVIS
{
public:
	double dSpd;
	int     ObjID;
	int     iMainAirportID; 

	double	PosX;           //x, y,	zλ����Ϣ	�ڻ�����/�ĵ������е�λ��
	double	PosY;
	double	PosZ;

	double	Heading;           //h,p,rλ����Ϣ
	double	Pitch;
	double	Roll;

	double	TrackHdg;

	unsigned char WheelFire; 
	unsigned char GearStatus;  // every bit indicates a gear's status �����
	unsigned char EngineSmoke; // every bit indicates a engine's smoke's status on/off
	unsigned char EngineFire;  // every bit indicates a engine's fire's status on/off

	ENUM_STATE_TYPE eStateType; //�˶�״̬
		unsigned  char SignalStatus; //�źŵ�״̬
	int Status; //Ŀ��״̬

	// 32-bit�ӵ͵��߷ֱ��ʾ			  1  / 0
	// 0: �ɻ���״̬:					  SHOW / HIDE
	// 1: Ӱ�ӵ�״̬:					  SHOW / HIDE
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
	// 23: aileron         	              ON / OFF //������
	// 24: yellow soil smoke              ON / OFF
	// 21~31: Reserved
	//boost���л�
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
 \brief		��Ч������
 \details   ��ATG���͸��Ӿ�ʹ�õ���Ч
 \author    
 \date      2013-06-03
*/

class EffectOBJPacket
{
public:

	int	ObjID; //Ψһ��ʶ

	double	PosX;           //x, y,	zλ����Ϣ	�ڻ�����/�ĵ������е�λ��
	double	PosY;
	double	PosZ;

	double	Heading;           //h,p,rλ����Ϣ
	double	Pitch;
	double	Roll;

	double	dSpd; //�ٶ�
	bool	bShow; //�Ƿ���ʾ
	ENUM_OBJ_TYPE  eObjType; // �˶�Ŀ������ͣ��ɻ����������ơ���������ӣ�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjID & PosX & PosY & PosZ & Heading & Pitch & Roll
			& dSpd & bShow & eObjType;
	}
};

//���������������������ϯλʹ�ã�
class FramePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FramePacket);

public:
	std::vector<MovingObjForVIS> m_vObjs;
	vector<AirportEnvData> m_vEnvs;	
	std::vector<CloudData> m_vClouds;
	std::vector<EffectOBJPacket> m_vEffectObj;

	int m_iTickCount;	// ֡������
private:
	SERIALIZE_PACKET(m_vObjs & m_vEnvs & m_vClouds & m_vEffectObj & m_iTickCount);
};

