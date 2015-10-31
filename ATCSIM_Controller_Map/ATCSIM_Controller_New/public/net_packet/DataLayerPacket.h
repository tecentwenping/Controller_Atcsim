#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
#include "public\DataObj\dataobjs.h"

class TrainPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanDataPacket);
public:
	int m_iTrainPlanID;		        /* ѵ���ƻ�ID */
	std::string m_szTrainPlanName;  /* ѵ���ƻ���*/
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class FlyPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlyPlanDataPacket);
public:
	int m_iTrainPlanID;		    /* ѵ���ƻ�ID */
	int m_iFlyPlanID;			/* ���мƻ�ID, �ǴӸ÷��мƻ��и��ƹ����ļƻ� ����������п��ܺ�ԭ����ֵ��һ�� */
	std::string m_szFlyPlanName;
	std::string m_szSignName;
	double m_dX;                    /* �ɻ����ֵ�λ�� X���� Ĭ��0 ʹ�þ�γ��*/
	double m_dY;					/* Y���� Ĭ��0 ʹ�þ�γ��*/
	double m_dZ;					/* Z���� Ĭ��0 ʹ�þ�γ��*/
	double m_dHeading;			    /* ��ͷ���� Ĭ��0 */
	double m_dSpeed;				/* ��ʼ�ٶ�*/
	int m_iAircraftID;			    /* ����*/
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};
class ALLFlyPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ALLFlyPlanDataPacket);
public:
	std::vector<FlyPlanData> m_vFlyPlanData; /* ���з��мƻ� */
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};
class AircraftDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AircraftDataPacket);
public:
	int m_iAircraftID;
	std::string m_szAircraftName;
	double m_dIAS;
	double m_dAcceleration;
	double m_dDeceleration;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};