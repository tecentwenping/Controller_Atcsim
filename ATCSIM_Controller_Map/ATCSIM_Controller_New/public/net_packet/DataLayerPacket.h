#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
#include "public\DataObj\dataobjs.h"

class TrainPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanDataPacket);
public:
	int m_iTrainPlanID;		        /* 训练计划ID */
	std::string m_szTrainPlanName;  /* 训练计划名*/
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class FlyPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(FlyPlanDataPacket);
public:
	int m_iTrainPlanID;		    /* 训练计划ID */
	int m_iFlyPlanID;			/* 飞行计划ID, 是从该飞行计划中复制过来的计划 下面的内容有可能和原来的值不一致 */
	std::string m_szFlyPlanName;
	std::string m_szSignName;
	double m_dX;                    /* 飞机出现的位置 X坐标 默认0 使用经纬度*/
	double m_dY;					/* Y坐标 默认0 使用经纬度*/
	double m_dZ;					/* Z坐标 默认0 使用经纬度*/
	double m_dHeading;			    /* 机头朝向 默认0 */
	double m_dSpeed;				/* 初始速度*/
	int m_iAircraftID;			    /* 机型*/
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};
class ALLFlyPlanDataPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ALLFlyPlanDataPacket);
public:
	std::vector<FlyPlanData> m_vFlyPlanData; /* 所有飞行计划 */
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