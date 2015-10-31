#ifndef _CONTROLLER_ACFTINFO_H
#define _CONTROLLER_ACFTINFO_H

#include "public/PublicStruct.h"
#include <hash_map>
#include "AircraftInfo.h"


typedef enum ACFTTYPE
{
	ACFT_INVALIDTRACK = -1,
	ACFT_NORMAL,            //计划中的飞机
	ACFT_PLANTRACK,         //计划航迹创建的飞机
	ACFT_DYNAMICCREATE,     //动态创建的飞机
	ACFT_MODIFYPLAN,        //修改信息后的飞机
}ACFTTYPE;


//process fplmodel
class ControllerAcftInfo: public AircraftInfo
{
public:
	typedef std::vector<std::string> vstrings;

	ControllerAcftInfo();
	virtual ~ControllerAcftInfo();
public:
	void UpdateStaticFpl(const PublicDataStruct::ST_FDP_FLIGHTPLAN_STATIC& info);
	void UpdateDynamicFpl(const PublicDataStruct::ST_FDP_FLIGHTPLAN_DYNAMIC& info);
public:
	int GetTrackNo();
	std::string& GetMid();
	std::string& GetCallsignName();
	std::string& GetSSRCode();
	std::string& GetArrRunwayName();
	//std::vector<PublicDataStruct::TAG_STRIP_POINT>& GetAcftRoute();
	void UpdateHMIState();

	bool GetCoupleFlag();
	bool IsADEPInFDRG();
	PublicDataStruct::PLAN_STATUS GetPlanStatus();
	PublicDataStruct::HMI_STAT    GetHmiStat();
	bool GetHoldPlanFlag();
	ACFTTYPE GetAcftPlanType();
	std::string& GetSectorName();
	bool GetAtdEmptyFlag();
private:
	bool IsSectorInCtrlSector(const std::string& sec, const vstrings& vSec);
public:
	//virtual 
	virtual std::string& GetTurbo();
	virtual std::string& GetArrAerodrome();
	virtual std::string& GetAcftType();
private:
	PublicDataStruct::HMI_STAT ComputeHMIState();
public:
	PublicDataStruct::ST_FDP_FLIGHTPLAN_DYNAMIC m_DynamicFpl;
	PublicDataStruct::ST_FDP_FLIGHTPLAN_STATIC  m_StaticFpl;
	PublicDataStruct::HMI_STAT m_hmiStat;
	ACFTTYPE m_AcftType;
};




#endif