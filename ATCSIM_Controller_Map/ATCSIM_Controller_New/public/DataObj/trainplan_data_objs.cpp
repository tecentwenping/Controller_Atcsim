#include "trainplan_data_objs.h"



/*-----------------训练计划-------------------*/
TrainPlan::TrainPlan()
{
	m_iTrainPlanID = 0;
	m_strTrainPlanName = "训练计划名称";
	m_iAirportID = 0;		
	m_iAirportModelID = 0;	
	m_iEnvironmentID = 0;				
	m_iStartTime = 0;
	m_strDate = "00000000";
	m_bUnion = false;
	m_iControllerNum = 0;
	m_mapControllerSector.clear();
	m_vObjPlan.clear();
}

TrainPlan::~TrainPlan()
{

}

TrainPlan::TrainPlan(const TrainPlan &trainPlan)
{
	if (this == &trainPlan) return;

	*this = trainPlan;
}

TrainPlan& TrainPlan::operator=(const TrainPlan& trainPlan)
{
	if (this == &trainPlan)	return *this;

	this->m_iTrainPlanID = trainPlan.m_iTrainPlanID;
	this->m_strTrainPlanName = trainPlan.m_strTrainPlanName;
	this->m_iAirportID = trainPlan.m_iAirportID;
	this->m_iAirportModelID = trainPlan.m_iAirportModelID;
	this->m_iEnvironmentID = trainPlan.m_iEnvironmentID;
	this->m_iStartTime = trainPlan.m_iStartTime;
	this->m_strDate = trainPlan.m_strDate;
	this->m_bUnion = trainPlan.m_bUnion;
	this->m_iControllerNum = trainPlan.m_iControllerNum;
	this->m_mapControllerSector = trainPlan.m_mapControllerSector;
	this->m_vObjPlan = trainPlan.m_vObjPlan;
	this->m_vCloudPlan = trainPlan.m_vCloudPlan;
	this->m_vSmokePlan = trainPlan.m_vSmokePlan;
	this->m_vVehiclePlan = trainPlan.m_vVehiclePlan;
	this->m_vSpecialEffectObjPlan = trainPlan.m_vSpecialEffectObjPlan;
	this->m_vEnvPlan = trainPlan.m_vEnvPlan;

	return *this;
}

int TrainPlan::GetId()
{
	return m_iTrainPlanID;
}

int TrainPlan::GetOwnerId()
{
	return m_iAirportID;
}

std::string TrainPlan::GetDisplayLabel()
{
	return m_strTrainPlanName;
}



/*-----------------训练计划_飞行计划-------------------*/
TPFlyPlan::TPFlyPlan()
{
	m_iObjPlanID = 0;
	m_iFlyPlanID = 0;
	m_strFlyPlanName = "飞行计划";       
	m_strSSRCode = "";
	m_iSectorID = 0;
	m_iControllerID = 0;
	m_iPilotID = 0;
	m_bAutoTakeoff = false;
	m_bRVSM = false;

	m_iFlyPlanType = 0;
	m_iCompanyID = 0;
	m_strCallSign = "呼号";
	m_iDepDromeID = 0;
	m_iArrDromeID = 0;
	m_iAlternateDromeID = 0;
	m_dFuelTime = 0;
	m_dCruiseLvl = 0;
	m_dCruiseSpd = 0;
	m_iArrRunwayID = 0;
	m_iDepRunwayID = 0;
	m_iWeight = 0;
	m_iDepGateID = 0;
	m_iArrGateID = 0;
	m_iVacateLineID = 0;
	m_iInRunwayLineID = 0;
	m_iDepartureTime = 0;
	m_iArrivalTime = 0;
	m_strRemark = "";		
	m_vecRoutePt.clear();
}

TPFlyPlan::~TPFlyPlan()
{

}

TPFlyPlan::TPFlyPlan(const TPFlyPlan & flyPlan)
{
	if (this == &flyPlan) return;

	*this = flyPlan;
}

TPFlyPlan& TPFlyPlan::operator=(const TPFlyPlan& flyPlan)
{
	if (this == &flyPlan)	return *this;

	//this->m_iTrainPlanID = flyPlan.m_iTrainPlanID;
	this->m_iFlyPlanID = flyPlan.m_iFlyPlanID;
	this->m_strFlyPlanName = flyPlan.m_strFlyPlanName;
	this->m_iObjPlanID = flyPlan.m_iObjPlanID;
	this->m_strSSRCode = flyPlan.m_strSSRCode;
	this->m_iSectorID = flyPlan.m_iSectorID;
	this->m_iControllerID = flyPlan.m_iControllerID;
	this->m_iPilotID = flyPlan.m_iPilotID;
	this->m_bAutoTakeoff = flyPlan.m_bAutoTakeoff;
	this->m_bRVSM = flyPlan.m_bRVSM;
	this->m_iFlyPlanType = flyPlan.m_iFlyPlanType;
	this->m_iCompanyID = flyPlan.m_iCompanyID;
	this->m_strCallSign = flyPlan.m_strCallSign;
	this->m_iDepDromeID = flyPlan.m_iDepDromeID;
	this->m_iArrDromeID = flyPlan.m_iArrDromeID;
	this->m_iAlternateDromeID = flyPlan.m_iAlternateDromeID;
	this->m_dFuelTime =  flyPlan.m_dFuelTime;
	this->m_dCruiseLvl = flyPlan.m_dCruiseLvl;
	this->m_dCruiseSpd = flyPlan.m_dCruiseSpd;
	this->m_iArrRunwayID = flyPlan.m_iArrRunwayID;
	this->m_iDepRunwayID = flyPlan.m_iDepRunwayID;
	this->m_iWeight = flyPlan.m_iWeight;
	this->m_iDepGateID = flyPlan.m_iDepGateID;
	this->m_iArrGateID = flyPlan.m_iArrGateID;
	this->m_iVacateLineID = flyPlan.m_iVacateLineID;
	this->m_iInRunwayLineID = flyPlan.m_iInRunwayLineID;
	this->m_iDepartureTime = flyPlan.m_iDepartureTime;
	this->m_iArrivalTime = flyPlan.m_iArrivalTime;
	this->m_strRemark = flyPlan.m_strRemark;
	this->m_vecRoutePt = flyPlan.m_vecRoutePt;

	return *this;
}

int TPFlyPlan::GetId()
{
	return m_iFlyPlanID;
}

int TPFlyPlan::GetOwnerId()
{
	return m_iObjPlanID;
}

std::string TPFlyPlan::GetDisplayLabel()
{
	return m_strFlyPlanName;
}

//飞机目标计划
int ObjPlan::GetId()
{
	return m_iObjPlanID;
}

std::string ObjPlan::GetDisplayLabel()
{
	return m_strRegNum;
}

int ObjPlan::GetOwnerId()
{
	return m_iTrainPlanID;
}

ObjPlan::ObjPlan( const ObjPlan &objPlan )
{
	if(this == &objPlan) return;
	this->m_iObjPlanID = objPlan.m_iObjPlanID;
	this->m_iTrainPlanID = objPlan.m_iTrainPlanID;
	this->m_strRegNum = objPlan.m_strRegNum;
	this->m_strSSRCode = objPlan.m_strSSRCode;
	this->m_iAppearTime = objPlan.m_iAppearTime;
	this->m_iAircraftTypeID = objPlan.m_iAircraftTypeID;
	this->m_dLongtitude = objPlan.m_dLongtitude;
	this->m_dLatitude = objPlan.m_dLatitude;
	this->m_dAltitude = objPlan.m_dAltitude;
	this->m_dHeading = objPlan.m_dHeading;
	this->m_dIAS = objPlan.m_dIAS;
	this->m_strCmd = objPlan.m_strCmd;
	this->m_bEngineStart = objPlan.m_bEngineStart;
	this->m_vFlyPlan = objPlan.m_vFlyPlan;

}

ObjPlan::ObjPlan()
{
	this->m_iObjPlanID = 0;
	this->m_iTrainPlanID = 0;
	this->m_strRegNum = "";
	this->m_strSSRCode = "ssrcode";
	this->m_iAppearTime = 0;
	this->m_iAircraftTypeID = 0;
	this->m_dLongtitude = 0;
	this->m_dLatitude = 0;
	this->m_dAltitude = 0;
	this->m_dHeading = 0;
	this->m_dIAS = 0;
	this->m_strCmd = "";
	this->m_bEngineStart = 0;
}

 ObjPlan& ObjPlan::operator=( const ObjPlan& objPlan )
 {
 	if(this == &objPlan) return *this;
 	this->m_iObjPlanID = objPlan.m_iObjPlanID;
 	this->m_iTrainPlanID = objPlan.m_iTrainPlanID;
 	this->m_strRegNum = objPlan.m_strRegNum;
 	this->m_strSSRCode = objPlan.m_strSSRCode;
 	this->m_iAppearTime = objPlan.m_iAppearTime;
 	this->m_iAircraftTypeID = objPlan.m_iAircraftTypeID;
 	this->m_dLongtitude = objPlan.m_dLongtitude;
 	this->m_dLatitude = objPlan.m_dLatitude;
 	this->m_dAltitude = objPlan.m_dAltitude;
 	this->m_dHeading = objPlan.m_dHeading;
 	this->m_dIAS = objPlan.m_dIAS;
 	this->m_strCmd = objPlan.m_strCmd;
 	this->m_bEngineStart = objPlan.m_bEngineStart;
 	this->m_vFlyPlan = objPlan.m_vFlyPlan;
 	return *this;
 }

 ObjPlan::~ObjPlan()
 {

 }
/*-----------------训练计划-------------------*/
TrainPlanData::TrainPlanData()
{
	m_iTrainPlanID = 0;
	m_szTrainPlanName = "训练计划名称";
}

TrainPlanData::~TrainPlanData()
{

}

TrainPlanData::TrainPlanData(const TrainPlanData &trainPlanData)
{
	if (this == &trainPlanData) return;
	this->m_iTrainPlanID = trainPlanData.m_iTrainPlanID;
	this->m_szTrainPlanName = trainPlanData.m_szTrainPlanName;
}

TrainPlanData& TrainPlanData::operator=(const TrainPlanData& train_plan_data)
{
	if (this == &train_plan_data)	return *this;

	this->m_iTrainPlanID = train_plan_data.m_iTrainPlanID;
	this->m_szTrainPlanName = train_plan_data.m_szTrainPlanName;

	return *this;
}

int TrainPlanData::GetId()
{
	return m_iTrainPlanID;
}

std::string TrainPlanData::GetDisplayLabel()
{
	return m_szTrainPlanName;
}

bool TrainPlanData::IsEqual(DataObj *dataobj)
{
	if(dataobj == NULL) return false;
	if(this == dataobj) return true;

	TrainPlanData *pdata = (TrainPlanData*)dataobj;
	if (this->m_iTrainPlanID == pdata->m_iTrainPlanID)
	{
		return true;
	}
	return false;
}
void TrainPlanData::Copy(DataObj *dataobj)
{
	if(dataobj == NULL) return;
	if(this == dataobj) return;

	TrainPlanData *pdata = (TrainPlanData*)dataobj;

	*this = *pdata;
}


VehiclePlan::VehiclePlan()
{
	m_iTrainPlanID		= 0; //训练计划ID
	m_iVehiclePlanId	=  0  ; //车辆计划ID
	m_strVehiclePlanName = "车辆" ; //车辆计划名称
	m_strCallsign		= "" ; //车辆计划呼号
	m_iVehicleId		= 0     ; //车辆性能ID
	m_iSectorId		= 0	; //扇区ID
	m_eVehiclePlanType	= 1	; //车辆计划类型x1 = 场内车辆，x2 = 场外车辆
	m_eBelongedType	=  1	; //本计划中使用的车辆所属类型，表示机场；表示航空公司
	m_iBelongedId		= 1; //根据所属类型iBelongedType 确定所属单位，为1 表示机场ID；表示航空公司ID
	m_iAppearTime		= 0	; //出现时间
	m_dLongitude		= 0		; //经度
	m_dLatitude		= 0		; //纬度
	m_dHeading			= 0	; //朝向
	m_dSpeed			= 0		; //速度
	m_bEngineStart		= 0	; //引擎是否启动
	m_strCmd				= ""		; //命令
	m_strRemark			= ""     ; //备注
}

VehiclePlan::VehiclePlan( const VehiclePlan & vehiclePlan )
{
	if (this == &vehiclePlan) return;
	*this = vehiclePlan;
}
VehiclePlan& VehiclePlan::operator=(const VehiclePlan & vehiclePlan)
{
	if (this == &vehiclePlan)	return *this;

	this->m_iTrainPlanID		= vehiclePlan.m_iTrainPlanID; //训练计划ID
	this->m_iVehiclePlanId	=  vehiclePlan.m_iVehiclePlanId  ; //车辆计划ID
	this->m_strVehiclePlanName = vehiclePlan.m_strVehiclePlanName ; //车辆计划名称
	this->m_strCallsign		= vehiclePlan.m_strCallsign         ; //车辆计划呼号
	this->m_iVehicleId		= vehiclePlan.m_iVehicleId       ; //车辆性能ID
	this->m_iSectorId		= vehiclePlan.m_iSectorId		; //扇区ID
	this->m_eVehiclePlanType	= vehiclePlan.m_eVehiclePlanType	; //车辆计划类型x1 = 场内车辆，x2 = 场外车辆
	this->m_eBelongedType	= vehiclePlan.m_eBelongedType			; //本计划中使用的车辆所属类型，表示机场；表示航空公司
	this->m_iBelongedId		= vehiclePlan.m_iBelongedId	; //根据所属类型iBelongedType 确定所属单位，为1 表示机场ID；表示航空公司ID
	this->m_iAppearTime		= vehiclePlan.m_iAppearTime	; //出现时间
	this->m_dLongitude		= vehiclePlan.m_dLongitude		; //经度
	this->m_dLatitude		= vehiclePlan.m_dLatitude		; //纬度
	this->m_dHeading			= vehiclePlan.m_dHeading		; //朝向
	this->m_dSpeed			= vehiclePlan.m_dSpeed			; //速度
	this->m_bEngineStart		= vehiclePlan.m_bEngineStart	; //引擎是否启动
	this->m_strCmd				= vehiclePlan.m_strCmd			; //命令
	this->m_strRemark			= vehiclePlan.m_strRemark     ; //备注
	return *this;
}

VehiclePlan::~VehiclePlan()
{

}

int VehiclePlan::GetId()
{	
	return m_iVehiclePlanId;
}

int VehiclePlan::GetOwnerId()
{
	return m_iTrainPlanID;
}

std::string VehiclePlan::GetDisplayLabel()
{
	
	return m_strVehiclePlanName;
}

//训练计划————序列化 方法
void TrainPlanData::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iTrainPlanID, pTemp, sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);

	m_szTrainPlanName.assign(pTemp);
	pTemp += m_szTrainPlanName.size() + 1;

	iOffSize = pTemp - pBuffer;
}

void TrainPlanData::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iTrainPlanID, sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);

	memcpy(pTemp, m_szTrainPlanName.c_str(), m_szTrainPlanName.size() + 1);
	pTemp += m_szTrainPlanName.size() + 1;

	iOffSize = pTemp - pBuffer;
}

int TrainPlanData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iTrainPlanID);
	iSize += m_szTrainPlanName.size() + 1;

	return iSize;
}


/*------------------------------------飞行计划----------------------------------*/
FlyPlanData::FlyPlanData()
{
	m_iTrainPlanID = 0;	
	m_iFlyPlanID = 0;
	m_szFlyPlanName = "飞行计划名称";
	m_szSignName = "呼号";
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
	m_dHeading = 0;
	m_dSpeed = 0;
	m_iAircraftID = 0;	
}

FlyPlanData::~FlyPlanData()
{

}

FlyPlanData::FlyPlanData(const FlyPlanData &flyPlanData)
{
	if (this == &flyPlanData) return;
	this->m_iTrainPlanID = flyPlanData.m_iTrainPlanID;
	this->m_iFlyPlanID = flyPlanData.m_iFlyPlanID;
	this->m_szFlyPlanName = flyPlanData.m_szFlyPlanName;
	this->m_szSignName = flyPlanData.m_szSignName;
	this->m_dX = flyPlanData.m_dX;
	this->m_dY = flyPlanData.m_dY;
	this->m_dZ = flyPlanData.m_dZ;
	this->m_dHeading = flyPlanData.m_dHeading;
	this->m_dSpeed = flyPlanData.m_dSpeed;
	this->m_iAircraftID = flyPlanData.m_iAircraftID;
}

FlyPlanData& FlyPlanData::operator=(const FlyPlanData& flyPlanInfo)
{
	if (this == &flyPlanInfo)	return *this;

	this->m_iTrainPlanID = flyPlanInfo.m_iTrainPlanID;		  
	this->m_iFlyPlanID = flyPlanInfo.m_iFlyPlanID;			
	this->m_szFlyPlanName = flyPlanInfo.m_szFlyPlanName;
	this->m_szSignName = flyPlanInfo.m_szSignName;
	this->m_dX = flyPlanInfo.m_dX;                    
	this->m_dY = flyPlanInfo.m_dY;					
	this->m_dZ = flyPlanInfo.m_dZ;				
	this->m_dHeading = flyPlanInfo.m_dHeading;			
	this->m_dSpeed = flyPlanInfo.m_dSpeed;			
	this->m_iAircraftID = flyPlanInfo.m_iAircraftID;	

	return *this;
}

int FlyPlanData::GetId()
{
	return m_iFlyPlanID;
}

int FlyPlanData::GetOwnerId()
{
	return m_iTrainPlanID;
}

std::string FlyPlanData::GetDisplayLabel()
{
	return m_szFlyPlanName;
}


bool FlyPlanData::IsEqual(DataObj *dataobj)
{
	if(dataobj == NULL) return false;
	if(this == dataobj) return true;
	FlyPlanData *pdata = (FlyPlanData*)dataobj;
	if ((this->m_iTrainPlanID == pdata->m_iTrainPlanID) && (this->m_iFlyPlanID == pdata->m_iFlyPlanID))
	{
		return true;
	}
	return false;
}
void FlyPlanData::Copy(DataObj *dataobj)
{
	if(dataobj == NULL) return;
	if(this == dataobj) return;

	FlyPlanData *pdata = (FlyPlanData*)dataobj;

	*this = *pdata;
}

//飞行计划————序列化 方法
void FlyPlanData::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iTrainPlanID, pTemp, sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);

	memcpy(&m_iFlyPlanID, pTemp, sizeof(m_iFlyPlanID));
	pTemp += sizeof(m_iFlyPlanID);

	m_szFlyPlanName.assign(pTemp);
	pTemp += m_szFlyPlanName.size() + 1;

	m_szSignName.assign(pTemp);
	pTemp += m_szSignName.size() + 1;

	memcpy(&m_dX, pTemp, sizeof(m_dX));
	pTemp += sizeof(m_dX);

	memcpy(&m_dY, pTemp, sizeof(m_dY));
	pTemp += sizeof(m_dY);

	memcpy(&m_dZ, pTemp, sizeof(m_dZ));
	pTemp += sizeof(m_dZ);

	memcpy(&m_dHeading, pTemp, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(&m_dSpeed, pTemp, sizeof(m_dSpeed));
	pTemp += sizeof(m_dSpeed);

	memcpy(&m_iAircraftID, pTemp, sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);

	iOffSize = pTemp - pBuffer;
}

void FlyPlanData::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iTrainPlanID, sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);

	memcpy(pTemp, &m_iFlyPlanID, sizeof(m_iFlyPlanID));
	pTemp += sizeof(m_iFlyPlanID);

	memcpy(pTemp, m_szFlyPlanName.c_str(), m_szFlyPlanName.size() + 1);
	pTemp += m_szFlyPlanName.size() + 1;

	memcpy(pTemp, m_szSignName.c_str(), m_szSignName.size() + 1);
	pTemp += m_szSignName.size() + 1;

	memcpy(pTemp, &m_dX, sizeof(m_dX));
	pTemp += sizeof(m_dX);

	memcpy(pTemp, &m_dY, sizeof(m_dY));
	pTemp += sizeof(m_dY);

	memcpy(pTemp, &m_dZ, sizeof(m_dZ));
	pTemp += sizeof(m_dZ);

	memcpy(pTemp, &m_dHeading, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(pTemp, &m_dSpeed, sizeof(m_dSpeed));
	pTemp += sizeof(m_dSpeed);

	memcpy(pTemp, &m_iAircraftID, sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);

	iOffSize = pTemp - pBuffer;
}

int FlyPlanData::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iTrainPlanID);
	iSize += sizeof(m_iFlyPlanID);
	iSize += m_szFlyPlanName.size() + 1;
	iSize += m_szSignName.size() + 1;
	iSize += sizeof(m_dX);
	iSize += sizeof(m_dY);
	iSize += sizeof(m_dZ);
	iSize += sizeof(m_dHeading);
	iSize += sizeof(m_dSpeed);
	iSize += sizeof(m_iAircraftID);

	return iSize;
}

/*-----------------训练计划_飞行计划（发给客户端）-------------------*/
FplInfo::FplInfo()
{
	m_iFlyPlanID = 0;
	m_strFlyPlanName = "飞行计划";       
	m_strSSRCode = "";
	m_strSector = "";
	m_iControllerID = 0;
	m_iPilotID = 0;
	m_bAutoTakeoff = false;
	m_bRVSM = false;

	m_iFlyPlanType = 0;
	m_strCompanyName = "";
	m_strCallSign = "呼号";
	m_strDepDrome = "";
	m_strArrDrome = "";
	m_strAlternateDrome = "";
	m_nFuelTime = 0;
	m_nCruiseLvl = 0;
	m_nCruiseSpd = 0;
	m_strArrRunwayName = "";
	m_strDepRunwayName = "";
	m_iWeight = 0;
	m_strDepGateName = "";
	m_strArrGateName = "";
	m_strVacateLineName = "";
	m_strInRunwayLineName = "";
	m_tDepartureTime = 0;
	m_tArrivalTime = 0;
	m_strRemark = "";		
	m_vecRoutePtNames.clear();
}

FplInfo::~FplInfo()
{

}

FplInfo::FplInfo(const FplInfo & flyPlan)
{
	if (this == &flyPlan) return;

	*this = flyPlan;
}

FplInfo& FplInfo::operator=(const FplInfo& flyPlan)
{
	if (this == &flyPlan)	return *this;

	//this->m_iTrainPlanID = flyPlan.m_iTrainPlanID;
	this->m_iFlyPlanID = flyPlan.m_iFlyPlanID;
	this->m_strFlyPlanName = flyPlan.m_strFlyPlanName;
	this->m_strSSRCode = flyPlan.m_strSSRCode;
	this->m_strSector = flyPlan.m_strSector;
	this->m_iControllerID = flyPlan.m_iControllerID;
	this->m_iPilotID = flyPlan.m_iPilotID;
	this->m_bAutoTakeoff = flyPlan.m_bAutoTakeoff;
	this->m_bRVSM = flyPlan.m_bRVSM;
	this->m_iFlyPlanType = flyPlan.m_iFlyPlanType;
	this->m_strCompanyName = flyPlan.m_strCompanyName;
	this->m_strCallSign = flyPlan.m_strCallSign;
	this->m_strDepDrome = flyPlan.m_strDepDrome;
	this->m_strArrDrome = flyPlan.m_strArrDrome;
	this->m_strAlternateDrome = flyPlan.m_strAlternateDrome;
	this->m_nFuelTime =  flyPlan.m_nFuelTime;
	this->m_nCruiseLvl = flyPlan.m_nCruiseLvl;
	this->m_nCruiseSpd = flyPlan.m_nCruiseSpd;
	this->m_strArrRunwayName = flyPlan.m_strArrRunwayName;
	this->m_strDepRunwayName = flyPlan.m_strDepRunwayName;
	this->m_iWeight = flyPlan.m_iWeight;
	this->m_strDepGateName = flyPlan.m_strDepGateName;
	this->m_strArrGateName = flyPlan.m_strArrGateName;
	this->m_strVacateLineName = flyPlan.m_strVacateLineName;
	this->m_strInRunwayLineName = flyPlan.m_strInRunwayLineName;
	this->m_tDepartureTime = flyPlan.m_tDepartureTime;
	this->m_tArrivalTime = flyPlan.m_tArrivalTime;
	this->m_strRemark = flyPlan.m_strRemark;
	this->m_vecRoutePtNames = flyPlan.m_vecRoutePtNames;

	return *this;
}

int FplInfo::GetId()
{
	return m_iFlyPlanID;
}

int FplInfo::GetOwnerId()
{
	return /*m_iObjPlanID*/-1;
}

std::string FplInfo::GetDisplayLabel()
{
	return m_strFlyPlanName;
}

/*-----------------云计划-------------------*/
CloudPlan::CloudPlan()
{
	m_iCloudID = 0;								//!<云ID
	m_strCloudName = "云";					//!< 云名称
	m_eCloudType = ECT_DEFAULT_YUN;	//!<云类型
	m_iTrainPlanID = 0;							//!<训练计划ID
	m_dLongitude = 0;							//!<云团的经度
	m_dLatitude = 0;								//!<云图的纬度
	m_dZ = 0;											//!<云图高度
	m_dSize = 0;										//!<云图直径大小
}

CloudPlan::~CloudPlan()
{

}

int CloudPlan::GetId()
{
	return m_iCloudID;
}
int CloudPlan::GetOwnerId()
{
	return m_iTrainPlanID;
}
string CloudPlan::GetDisplayLabel()
{
	return m_strCloudName;
}

/*-----------------烟计划-------------------*/
SmokePlan::SmokePlan()
{
	m_iSmokeID = 0;						  //!<烟ID
	m_strSmokeName = "烟计划";   //!< 烟名称
	m_eSmokeType = EST_JIEGAN;	 //!<烟类型
	m_iTrainPlanID = 0;					 //!<训练计划ID
	m_dLongitude = 0;					 //!<烟的经度
	m_dLatitude = 0;						 //!<烟的纬度
	m_dZ = 0;
	m_dSize = 0;								 //!<烟的直径大小
}

SmokePlan::~SmokePlan()
{

}

int SmokePlan::GetId()
{
	return m_iSmokeID;
}
int SmokePlan::GetOwnerId()
{
	return m_iTrainPlanID;
}
string SmokePlan::GetDisplayLabel()
{
	return m_strSmokeName;
}


/*-----------------特效运动物体计划-------------------*/
SpecialEffectObjPlan::SpecialEffectObjPlan()
{
	m_iTrainPlanID  = 0;
	m_iObjPlanId = 0;
	m_eObjType = OT_BIRD;
	m_strName = "特效物体";
	m_dLongitude = 0;
	m_dLatitude = 0;
	m_dAltitude = 0;
	m_dSpeed = 0;
	m_bLoop = 0;
}
SpecialEffectObjPlan::~SpecialEffectObjPlan()
{
	
}

int SpecialEffectObjPlan::GetId()
{
	return m_iObjPlanId;
}
int SpecialEffectObjPlan::GetOwnerId()
{
	return m_iTrainPlanID;
}
string SpecialEffectObjPlan::GetDisplayLabel()
{
	return m_strName;
}

SpecialEffectObjPlan::SpecialEffectObjPlan(const SpecialEffectObjPlan & effectObjPlan)
{
	if (this == &effectObjPlan) return;

	*this = effectObjPlan;
}

SpecialEffectObjPlan& SpecialEffectObjPlan::operator=(const SpecialEffectObjPlan & effectObjPlan)
{
	if (this == &effectObjPlan)	return *this;
	
	this->m_iTrainPlanID = effectObjPlan.m_iTrainPlanID;
	this->m_iObjPlanId = effectObjPlan.m_iObjPlanId;
	this->m_eObjType = effectObjPlan.m_eObjType;
	this->m_strName = effectObjPlan.m_strName;
	this->m_dLongitude = effectObjPlan.m_dLongitude;
	this->m_dLatitude = effectObjPlan.m_dLatitude;
	this->m_dAltitude = effectObjPlan.m_dAltitude;
	this->m_dSpeed = effectObjPlan.m_dSpeed;
	this->m_bLoop = effectObjPlan.m_bLoop;
	this->m_vecRoute = effectObjPlan.m_vecRoute;

	return *this;
}

/*-----------------环境子对象在某一时间段内的计划-------------------*/
EnvObjectPhasePlan::EnvObjectPhasePlan()
{
	m_dTimePoint = 0;
	m_iLevel = 0;
	m_bPhasePlanOn = false;
	m_dWindSpeed = 0;
	m_dWindDirection = 0;
	m_dLightingDirection = 0;
	m_dLightingRadious = 0;
	m_dQFE = 0;
	m_dQNH = 0;
	m_dSmokeDensity = 0;
	m_dTemprature = 0;
	m_dRVR = 0;
	m_dDewPoint = 0;
}
EnvObjectPhasePlan::~EnvObjectPhasePlan()
{

}

EnvObjectPhasePlan::EnvObjectPhasePlan(const EnvObjectPhasePlan & envObjectPhasePlan)
{
	if (this == &envObjectPhasePlan) return;

	*this = envObjectPhasePlan;
}
EnvObjectPhasePlan& EnvObjectPhasePlan::operator=(const EnvObjectPhasePlan & envObjectPhasePlan)
{
	if (this == &envObjectPhasePlan) return *this;
	
	this->m_dTimePoint = envObjectPhasePlan.m_dTimePoint;
	this->m_iLevel = envObjectPhasePlan.m_iLevel;
	this->m_bPhasePlanOn = envObjectPhasePlan.m_bPhasePlanOn;
	this->m_dWindSpeed = envObjectPhasePlan.m_dWindSpeed;
	this->m_dWindDirection = envObjectPhasePlan.m_dWindDirection;
	this->m_dLightingDirection = envObjectPhasePlan.m_dLightingDirection;
	this->m_dLightingRadious = envObjectPhasePlan.m_dLightingRadious;
	this->m_dQFE = envObjectPhasePlan.m_dQFE;
	this->m_dSmokeDensity = envObjectPhasePlan.m_dSmokeDensity;
	this->m_dTemprature = envObjectPhasePlan.m_dTemprature;
	this->m_dQNH = envObjectPhasePlan.m_dQNH;
	this->m_dRVR = envObjectPhasePlan.m_dRVR;
	this->m_dDewPoint = envObjectPhasePlan.m_dDewPoint;
	
	return *this;
}

/*-----------------环境子对象计划-------------------*/
EnvObjectPlan::EnvObjectPlan()
{
	m_iEnvPlanID = 0;
	m_iEnvObjectPlanID = 0;
	m_eEnvObjectType = ENV_OBJ_RAIN;
	m_dStartTime = 0;
	m_dEndTime = 0;
}
EnvObjectPlan::~EnvObjectPlan()
{

}

//拷贝、赋值函数
EnvObjectPlan::EnvObjectPlan(const EnvObjectPlan & envObjectPlan)
{
	if (this == &envObjectPlan) return;

	*this = envObjectPlan;
}

EnvObjectPlan& EnvObjectPlan::operator=(const EnvObjectPlan & envObjectPlan)
{
	if (this == &envObjectPlan) return *this;

	this->m_iEnvPlanID = envObjectPlan.m_iEnvPlanID;
	this->m_iEnvObjectPlanID = envObjectPlan.m_iEnvObjectPlanID;
	this->m_eEnvObjectType = envObjectPlan.m_eEnvObjectType;
	this->m_dStartTime = envObjectPlan.m_dStartTime;
	this->m_dEndTime = envObjectPlan.m_dEndTime;
	this->m_vecEnvObjectPhasePlan = envObjectPlan.m_vecEnvObjectPhasePlan;

	return *this;
}

int EnvObjectPlan::GetId()
{
	return m_iEnvObjectPlanID;
}

int EnvObjectPlan::GetOwnerId()
{
	return m_iEnvPlanID;
}
/*-----------------环境子对象计划——跑道环境计划-------------------*/
RunwayEnvPlan::RunwayEnvPlan()
{
	m_iAirportID = 0;
	m_iEnvPlanID = 0;
	m_iRunwayID = 0;

	m_dTemperatureRatio = 1.0;
	m_dDewpointRatio = 1.0;
	m_dWindSpdRatio = 1.0;
	m_dWindDirRatio = 1.0;
	m_dQNHRatio = 1.0;	
	m_dQFERatio = 1.0;
}

RunwayEnvPlan::~RunwayEnvPlan()
{

}

//拷贝、赋值函数
RunwayEnvPlan::RunwayEnvPlan(const RunwayEnvPlan & runwayEnvPlan)
{
	if(this == &runwayEnvPlan) return;

	*this = runwayEnvPlan;
}

RunwayEnvPlan& RunwayEnvPlan::operator=(const RunwayEnvPlan & runwayEnvPlan)
{
	if (this == &runwayEnvPlan) return *this;

	this->m_iAirportID = runwayEnvPlan.m_iAirportID;
	this->m_iEnvPlanID = runwayEnvPlan.m_iEnvPlanID;
	this->m_iRunwayID = runwayEnvPlan.m_iRunwayID;
	this->m_dTemperatureRatio = runwayEnvPlan.m_dTemperatureRatio;
	this->m_dDewpointRatio = runwayEnvPlan.m_dDewpointRatio;
	this->m_dWindSpdRatio = runwayEnvPlan.m_dWindSpdRatio;
	this->m_dWindDirRatio = runwayEnvPlan.m_dWindDirRatio;
	this->m_dQNHRatio = runwayEnvPlan.m_dQNHRatio;
	this->m_dQFERatio = runwayEnvPlan.m_dQFERatio;

	return *this;
}


/*-----------------环境计划-------------------*/
EnvPlan::EnvPlan()
{
	m_iTrainPlanID  = 0;
	m_iEnvPlanID = 0;
	m_strEnvPlanName = "环境计划";
	m_RainPlan.m_eEnvObjectType = ENV_OBJ_RAIN;			//环境子对象计划——雨计划
	m_SnowPlan.m_eEnvObjectType = ENV_OBJ_SNOW;				//环境子对象计划——雪计划
	m_RVRPlan.m_eEnvObjectType = ENV_OBJ_VISIBILITY;				//环境子对象计划——能见度计划
	m_TempraturePlan.m_eEnvObjectType = ENV_OBJ_TEMPERATURE;			//环境子对象计划——温度计划
	m_DewPointPlan.m_eEnvObjectType = ENV_OBJ_DEWPOINT;			//环境子对象计划——露点计划
	m_DustPlan.m_eEnvObjectType = ENV_OBJ_DUST;				//环境子对象计划——尘计划
	m_RisenDustPlan.m_eEnvObjectType = ENV_OBJ_RISENDUST;				//环境子对象计划——扬沙计划
	m_QNHPlan.m_eEnvObjectType = ENV_OBJ_QNH;				//环境子对象计划——海压计划
	m_HazePlan.m_eEnvObjectType = ENV_OBJ_HAZE;				//环境子对象计划——霾计划
	m_FogPlan.m_eEnvObjectType = ENV_OBJ_FOG;				//环境子对象计划——雾计划
	m_LightingPlan.m_eEnvObjectType = ENV_OBJ_LIGHTINGT;			//环境子对象计划——闪电计划
	m_WindPlan.m_eEnvObjectType = ENV_OBJ_WIND;			//环境子对象计划——风计划
	m_QFEPlan.m_eEnvObjectType = ENV_OBJ_QFE;				//环境子对象计划——气压计划
	m_SmokePlan.m_eEnvObjectType = ENV_OBJ_SMOKE;				//环境子对象计划——烟计划
}
EnvPlan::~EnvPlan()
{

}

int EnvPlan::GetId()
{
	return m_iEnvPlanID;
}
int EnvPlan::GetOwnerId()
{
	return m_iTrainPlanID;
}
string EnvPlan::GetDisplayLabel()
{
	return m_strEnvPlanName;
}

//拷贝、赋值函数
EnvPlan::EnvPlan(const EnvPlan & envPlan)
{
	if (this == &envPlan) return;

	*this = envPlan;
}

EnvPlan& EnvPlan::operator=(const EnvPlan & envPlan)
{
	if (this == &envPlan) return *this;

	this->m_iTrainPlanID = envPlan.m_iTrainPlanID;
	this->m_iEnvPlanID = envPlan.m_iEnvPlanID;
	this->m_strEnvPlanName = envPlan.m_strEnvPlanName;
	this->m_RainPlan = envPlan.m_RainPlan;
	this->m_SnowPlan = envPlan.m_SnowPlan;
	this->m_RVRPlan = envPlan.m_RVRPlan;
	this->m_TempraturePlan = envPlan.m_TempraturePlan;
	this->m_DewPointPlan = envPlan.m_DewPointPlan;
	this->m_DustPlan = envPlan.m_DustPlan;
	this->m_RisenDustPlan = envPlan.m_RisenDustPlan;
	this->m_QNHPlan = envPlan.m_QNHPlan;
	this->m_HazePlan = envPlan.m_HazePlan;
	this->m_FogPlan = envPlan.m_FogPlan;
	this->m_LightingPlan = envPlan.m_LightingPlan;
	this->m_WindPlan = envPlan.m_WindPlan;
	this->m_QFEPlan = envPlan.m_QFEPlan;
	this->m_SmokePlan = envPlan.m_SmokePlan;
	this->m_RunwayEnvPlan = envPlan.m_RunwayEnvPlan;


	return *this;
}

/*-----------------环境参数-------------------*/
EnvData::EnvData()
{
	m_iRainLevel = 0;							//!<雨量，分1~3级，0代表无雨
	m_iSnowLevel = 0;						//!<雪量，分1~3级，0代表无雪
	m_enumFogType = EFT_NONE;	//!<0 = 无雾，1 = 平流雾，2=辐射雾 默认0
	m_dVis = 0;									//!<能见度

	m_dSunRiseTime = 0;					//!<日出时间
	m_dSunSetTime = 0;					//!<日落时间

	m_strTerrainName = "地形";			//!<地形名字
	m_dTerrainPosX = 0;						//!<地形坐标
	m_dTerrainPosY = 0;						//!<地形坐标
	m_dTerrainPosZ = 0;						//!<地形坐标
	m_iVaneX = 0;								//!<
	m_iVaneY = 0;								//!<
	m_iDogVaneX = 0;						//!<
	m_iDogVaneY = 0;						//!<
}

EnvData::~EnvData()
{

}

int EnvData::GetId()
{
	return 0;
}
int EnvData::GetOwnerId()
{
	return 0;
}
string EnvData::GetDisplayLabel()
{
	return "";
}

/*-----------------目标计划（为视景使用）-------------------*/
ObjPlanForVis::ObjPlanForVis()
{
	m_eObjPlanType = PLAN_TYPE_AIRCRAFT;
	m_iObjPlanID = 0;
	m_iObjID = 0;
	m_strCallSign = "呼号";
	m_strCompanyName = "公司";
}

ObjPlanForVis::~ObjPlanForVis()
{

}

int ObjPlanForVis::GetId()
{
	return m_iObjPlanID;
}

string ObjPlanForVis::GetDisplayLabel()
{
	return m_strCallSign;
}

/*-----------------灯光计划-------------------*/
LightPlan::LightPlan()
{
	m_iLightPlanID = 0;							//!<灯光计划的ID
	m_iTrainPlanID = 0;							//!<训练计划ID
	m_szLightPlanName = "灯光计划";	//!<灯光计划名称
	m_iLightCollectionID = 0;					//!<灯光组组合ID
	m_iLightLevel = 0;							//!<灯光等级（0到5,0为关闭）
}

LightPlan::~LightPlan()
{

}

int LightPlan::GetId()
{
	return m_iLightPlanID;
}

int LightPlan::GetOwnerId()
{
	return m_iTrainPlanID;
}

string LightPlan::GetDisplayLabel()
{
	return m_szLightPlanName;
}

/*------------特效运动物体计划经过的轨迹点---------------*/
RoutePointPosition::RoutePointPosition()
{

}

RoutePointPosition::~RoutePointPosition()
{

}

int RoutePointPosition::GetOwnerId()
{
	return m_iOwnerID;
}

void RoutePointPosition::SetSequence( int iSeq )
{
	m_iSequence = iSeq;
}

int RoutePointPosition::GetSequence()
{
	return m_iSequence;
}