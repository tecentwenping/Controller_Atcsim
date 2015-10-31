//����������Ҫ�Ľṹ by  wmq 2010.3.5

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
//!��̬�������ݽṹ
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
	int iLevel;			//ǿ�ȵȼ�
	//x, y, zλ����Ϣ	�ڻ������ĵ������е�λ��
	double dXPos;
	double dYPos;
	double dZPos;

	//boost���л�
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
	bool bIsCreate;//true ���� falseɾ��
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
	bool bIsCreate;//true ���� falseɾ��
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
// �ܵ��ӳ̵Ķ���
struct ST_RVR
{
	int iRunwayID;
	int iPosInRunway;  //���ܵ��ϵĵ�  0: �ܵ���㣬1: �ܵ��е�, 2. �ܵ�������
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
	int iRunwayID;			/* �ܵ�ID */ 
	double dTemperature;	/* �¶� Ĭ��0 */
	double dDewpoint;		/* ¶�� Ĭ��0 */
	double dWindSpd;		/* ���� Ĭ��0 */
	double dWindDir;		/* ���� Ĭ��0 */
	double dStartCBase;		/* �ܵ���� ����Ƶ͸� Ĭ��3000*/
	double dEndCBase;		/* �ܵ��յ� ����Ƶ͸� Ĭ��3000*/
	double dStartRVR;		/* ��ʼ�� �ӳ� */
	double dMidRVR;			/* �м�� �ӳ� */
	double dEndRVR;			/* ������ �ӳ� */
	//double dVis;			/* �ܼ��� */
	double dQNH;			/* ������ѹ Ĭ��1000 */
	double dQFE;			/* ��ѹ Ĭ��1000 */
	int iLight;				/* ���ܵ��ıߵƵƹ�ȼ���� */	

	//lichun 2011.03.30
	double dRandomWindSpd;		/* �����ɺ�����������ķ��� ƽ����*/
	double dRandomWindDir;		/* �����ɺ�����������ķ��� ƽ����*/

	int    m_iIsGuestingWindSpd;/* �Ƿ�Ϊʵʱ���٣�1��������ʵʱ���٣�2ʵʱ����*/
	double dWindMaxSpd;			/* �����Աλ���õķ������ֵ*/
	double dWindMinSpd;			/* �����Աλ���õķ�����Сֵ*/
	double dRandomWindMaxSpd;	/* �����ɺ�����������ķ������ֵ*/
	double dRandomWindMinSpd;	/* �����ɺ�����������ķ�����Сֵ*/

	int    m_iIsGuestingWindDir;/* �Ƿ�Ϊʵʱ����1��������ʵʱ����2ʵʱ����*/
	int    m_iWindDirection;	/* 1������2������*/
	double m_dGuestingWindDir;	/* �����Աλ���õ�ʵʱ����*/
	double m_dGuestingRandomWindDir;	/* ����������������ʵʱ����*/
	double m_dFrictionNum;       //Ħ��ϵ��
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
	// ���������Ļ���
	int m_iAirportID;
	int m_iAirspaceID;			/* �������ĸ������� */
	int m_iRainLevel;			/* ��������1~3����0�������� */
	int m_iSnowLevel;			/* ѩ������1~3����0������ѩ */

	//��ɳ�������ǿ��ͨ�������ܼ���������.
	bool m_bLightningOn;		//�Ƿ�������,������,���Ӿ������.
	bool m_bFogOn;	//�Ƿ���ȫ����. ǿ�ȵȼ�ͨ���ܼ���������
	bool m_bHazeOn;
	bool m_bRisenDustOn;		//�Ƿ�����ɳ, �������ٶ����ƶ���������ٷ������. ������ɳ��ͬʱ��������.

	////����������һ��������ɳ��ʱ����ϯλ�˺��Ӿ��������˵Ĵ���.��������һ�����ݲ��з��ͳ�ȥ.
	int m_iDustLevel;			//����Ũ�ȵȼ�, 0����ʾû�и���.
	double m_dDewpoint;		//����������¶����Ϣ��
	double m_dWindSpd;		/* ���� Ĭ��0 */
	double m_dWindDir;		/* ���� Ĭ��0 */
	double m_dQFE; // ��ѹ
	double m_dQNH; // ������ѹ

	double m_dVisibility; // �ܼ���
	double m_dTemperature; // �¶�
	//SYSTEMTIME m_envTime;	//ѵ���ƻ��ڼ�ʱ���ּ��뿪ʼ.Ȼ�����ʱ��������.��9:00:00��ʼ,��һ����
	//����9:01:00.(��ʾ��ϯλʱ����).Ŀǰ���ʱ��ʱ����1899��12��30��0:00:00.
	//ȥ����Windows������, vector��ֱ��, �� �� �� ʱ �� �����Ϣ
	vector<int> m_envTime;
	std::string  m_strModelName;// the index of used airport model file name

	std::vector<ST_POS_INTENSITY> m_vSmoke;		//��---��̬������Ϣ
	std::vector<ST_POS_INTENSITY> m_vRadiantFog; //������---��̬������Ϣ
	std::vector<ST_POS_INTENSITY> m_vWorkArea;//ʩ�����򴴽���Ϣ

public:
	/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
	//boost���л�
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iAirspaceID & m_iRainLevel & m_iSnowLevel & m_bLightningOn
			& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dDewpoint & m_dWindSpd
			& m_dWindDir & m_dQFE & m_dQNH & m_dVisibility & m_dTemperature & m_envTime & m_strModelName
			& m_vSmoke & m_vRadiantFog & m_vWorkArea;
	}
};
//�޸� 2010.3.5 

struct ST_AirportEnvForEnvPacket
{
public:
	ST_AirportEnvForEnvPacket();
	virtual ~ST_AirportEnvForEnvPacket();
public:
	ST_AirportEnvBaseData m_airportEnvBaseData;
	vector<ST_RUNWAY_ENV> m_vRunwayEnv;	//�ܵ�����
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
//�Ӿ�Ҫ�����ݶ�������,����ά��, ��������
struct ST_AirportEnvBaseData_VS
{
public:
ST_AirportEnvBaseData_VS();
virtual ~ST_AirportEnvBaseData_VS();
ST_AirportEnvBaseData_VS& operator=(ST_AirportEnvBaseData_VS const& envBaseData);

public:
// ���������Ļ���
int m_iAirportID;
int m_iRainLevel;			/* ��������1~3����0�������� */
//int m_iSnowLevel;			/* ѩ������1~3����0������ѩ*/
/*
//��ɳ�������ǿ��ͨ�������ܼ���������.
bool m_bLightningOn;		//�Ƿ�������,������,���Ӿ������.
bool m_bFogOn;	//�Ƿ���ȫ����. ǿ�ȵȼ�ͨ���ܼ���������
bool m_bHazeOn;
bool m_bRisenDustOn;		//�Ƿ�����ɳ, �������ٶ����ƶ���������ٷ������. ������ɳ��ͬʱ��������.

////����������һ��������ɳ��ʱ����ϯλ�˺��Ӿ��������˵Ĵ���.��������һ�����ݲ��з��ͳ�ȥ.
int m_iDustLevel;			//����Ũ�ȵȼ�, 0����ʾû�и���.
double m_dWindSpd;		/* ���� Ĭ��0 */
//double m_dWindDir;		/* ���� Ĭ��0 */

//double m_dVisibility; // �ܼ���
//double m_dTemperature; // �¶�

//SYSTEMTIME m_envTime;	//ѵ���ƻ��ڼ�ʱ���ּ��뿪ʼ.Ȼ�����ʱ��������.��9:00:00��ʼ,��һ����
//����9:01:00.(��ʾ��ϯλʱ����).Ŀǰ���ʱ��ʱ����1899��12��30��0:00:00.
//ȥ����Windows������, vector��ֱ��, �� �� �� ʱ �� �����Ϣ
//vector<int> m_envTime;
/*
std::string  m_strModelName;// the index of used airport model file name
vector<ST_POS_INTENSITY> m_vSmoke;		//��---ǿ�Ⱥ�λ����Ϣ
vector<ST_POS_INTENSITY> m_vRadiantFog; //������---ǿ�Ⱥ�λ����Ϣ
bool m_bTriggerOneLightning;
bool m_LightningInf;
public:
//boost���л�
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
bool m_bTriggerOneLightning; //�Ƿ񴥷�һ������
ST_POS_INTENSITY m_LightningInf;	//��Ϊ�������������Ϣ
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
