#include "base_data_objs.h"

/*-----------------机型--------------*/
AircraftData::AircraftData()
{
	m_iAircraftID = 0;
	m_szAircraftName = "航空器名称";
	m_dIAS = 0;
	m_dAcceleration = 0;
	m_dDeceleration= 0;
}

AircraftData::~AircraftData()
{

}

AircraftData::AircraftData(const AircraftData &aircraftData)
{
	if(this == &aircraftData) return;

	this->m_iAircraftID = aircraftData.m_iAircraftID;
	this->m_szAircraftName = aircraftData.m_szAircraftName;
	this->m_dIAS = aircraftData.m_dIAS;
	this->m_dAcceleration = aircraftData.m_dAcceleration;
	this->m_dDeceleration = aircraftData.m_dDeceleration;
}

AircraftData& AircraftData::operator=(const AircraftData& aircraft_data)
{
	if (this == &aircraft_data)	return *this;

	this->m_iAircraftID = aircraft_data.m_iAircraftID;
	this->m_szAircraftName = aircraft_data.m_szAircraftName;
	this->m_dIAS = aircraft_data.m_dIAS;
	this->m_dAcceleration = aircraft_data.m_dAcceleration;
	this->m_dDeceleration = aircraft_data.m_dDeceleration;

	return *this;
}

int AircraftData::GetId()
{
	return m_iAircraftID;
}

std::string AircraftData::GetDisplayLabel()
{
	return m_szAircraftName;
}

bool AircraftData::IsEqual(DataObj *dataobj)
{
	if(dataobj == NULL) return false;
	if(this == dataobj) return true;
	AircraftData *pdata = (AircraftData*)dataobj;
	if (this->m_iAircraftID == pdata->m_iAircraftID)
	{
		return true;
	}
	return false;
}
void AircraftData::Copy(DataObj *dataobj)
{
	if(dataobj == NULL) return;
	if(this == dataobj) return;

	AircraftData *pdata = (AircraftData*)dataobj;

	*this = *pdata;
}

//机型————序列化方法
void AircraftData::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&this->m_iAircraftID,pTemp,sizeof(this->m_iAircraftID));
	pTemp += sizeof(this->m_iAircraftID);

	this->m_szAircraftName.assign(pTemp);
	pTemp += this->m_szAircraftName.size()+1;

	memcpy(&this->m_dIAS,pTemp,sizeof(this->m_dIAS));
	pTemp += sizeof(this->m_dIAS);

	memcpy(&this->m_dAcceleration,pTemp,sizeof(this->m_dAcceleration));
	pTemp += sizeof(this->m_dAcceleration);

	memcpy(&this->m_dDeceleration,pTemp,sizeof(this->m_dDeceleration));
	pTemp += sizeof(this->m_dDeceleration);

	iOffSize = pTemp - pBuffer;

}

void AircraftData::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&this->m_iAircraftID,sizeof(this->m_iAircraftID));
	pTemp += sizeof(this->m_iAircraftID);

	memcpy(pTemp,this->m_szAircraftName.c_str(),this->m_szAircraftName.size()+1);
	pTemp += this->m_szAircraftName.size()+1;

	memcpy(pTemp,&this->m_dIAS,sizeof(this->m_dIAS));
	pTemp += sizeof(this->m_dIAS);

	memcpy(pTemp,&this->m_dAcceleration,sizeof(this->m_dAcceleration));
	pTemp += sizeof(this->m_dAcceleration);

	memcpy(pTemp,&this->m_dDeceleration,sizeof(this->m_dDeceleration));
	pTemp += sizeof(this->m_dDeceleration);

	iOffSize = pTemp - pBuffer;
}

int AircraftData::GetBufferSize()
{
	int size = 0;
	size += sizeof(this->m_iAircraftID);
	size += this->m_szAircraftName.size()+1;
	size += sizeof(this->m_dIAS);
	size += sizeof(this->m_dAcceleration);
	size += sizeof(this->m_dDeceleration);
	return size;	
}


/*-----------------车辆--------------*/

Vehicle::Vehicle(void)
{
	m_iVehicleID = 0;		 
	m_strVehicleName = "";   	
	m_iType = 0;			  
	m_dLength = 0;	      
	m_dHeight = 0;	      
	m_dWidth = 0;		  
	m_dNormalTaxSpeed = 0;   
	m_dMinTaxSpeed = 0;	  
	m_dMaxTaxSpeed = 0;	  
	m_dTurnSpeed = 0;		  
	m_dNormalAccSpeed = 0;   
	m_dMinAccSpeed = 0;	  
	m_dMaxAccSpeed = 0;	  
	m_dNormalDecSpeed = 0;   
	m_dMinDecSpeed = 0;	  
	m_dMaxDecSpeed = 0;	  
	m_dMaxTaxBackSpd = 0;	  
	m_dMaxFrontGearTurnHdg = 0;     
	m_dReverseSpeed =0;
	m_dSizeTreadLen = 0;   		 
	m_dSizeTreadWidth = 0;     	 
	m_dMinBrakeDis = 0;		
	m_dAttachHeading = 0;		
	m_strModelFile = "";
	m_strTaxingSoundFile = "";
	m_strStartEngineSoundFile = "";
	m_strShutdownEngineSoundFile = "";
	m_strWarmwaitingSoundFile = "";
}

Vehicle::~Vehicle(void)
{
}

int Vehicle::GetId()
{
	return m_iVehicleID;
}

std::string Vehicle::GetDisplayLabel()
{
	return m_strVehicleName;
}

//void Vehicle::Copy( boost::shared_ptr<Vehicle> spVehicle )
//{
//
//}

void Vehicle::SetVehicleID( int iVehicleID )
{
	m_iVehicleID = iVehicleID;
}

void Vehicle::SetVehicleName( string strVehicleName )
{
	m_strVehicleName = strVehicleName;
}

void Vehicle::SetType( int iType )
{
	m_iType = iType;
}

void Vehicle::SetLength( double dLength )
{
	m_dLength = dLength;
}

void Vehicle::SetHeight( double dHeight )
{
	m_dHeight = dHeight;
}

void Vehicle::SetWidth( double dWidth )
{
	m_dWidth = dWidth;
}

void Vehicle::SetNormalTaxSpeed( double dNormalTaxSpeed )
{
	m_dNormalTaxSpeed= dNormalTaxSpeed;
}

void Vehicle::SetMinTaxSpeed( double dMinTaxSpeed )
{
	m_dMinTaxSpeed = dMinTaxSpeed;
}

void Vehicle::SetMaxTaxSpeed( double dMaxTaxSpeed )
{
	m_dMaxTaxSpeed = dMaxTaxSpeed;
}

void Vehicle::SetTurnSpeed( double dTurnSpeed )
{
	m_dTurnSpeed = dTurnSpeed;
}

void Vehicle::SetNormalAccSpeed( double dNormalAccSpeed )
{
	m_dNormalAccSpeed = dNormalAccSpeed;
}

void Vehicle::SetMinAccSpeed( double dMinAccSpeed )
{
	m_dMinAccSpeed = dMinAccSpeed;
}

void Vehicle::SetMaxAccSpeed( double dMaxAccSpeed )
{
	m_dMaxAccSpeed = dMaxAccSpeed;
}

void Vehicle::SetNormalDecSpeed( double dNormalDecSpeed )
{
	m_dNormalDecSpeed = dNormalDecSpeed;
}

void Vehicle::SetMinDecSpeed( double dMinDecSpeed )
{
	m_dMinDecSpeed = dMinDecSpeed;
}

void Vehicle::SetMaxDecSpeed( double dMaxDecSpeed )
{
	m_dMaxDecSpeed = dMaxDecSpeed;
}

void Vehicle::SetMaxTaxBackSpd( double dMaxTaxBackSpd )
{
	m_dMaxTaxBackSpd = dMaxTaxBackSpd;
}

void Vehicle::SetMaxFrontGearTurnHdg( double dMaxFrontGearTurnHdg )
{
	m_dMaxFrontGearTurnHdg = dMaxFrontGearTurnHdg;
}

void Vehicle::SetSizeTreadLen( double dSizeTreadLen )
{
	m_dSizeTreadLen = dSizeTreadLen;
}

void Vehicle::SetSizeTreadWidth( double dSizeTreadWidth )
{
	m_dSizeTreadWidth = dSizeTreadWidth;
}

void Vehicle::SetMinBrakeDis( double dMinBrakeDis )
{
	m_dMinBrakeDis = dMinBrakeDis;
}

void Vehicle::SetAttachHeading( double dAttachHeading )
{
	m_dAttachHeading = dAttachHeading;
}

void Vehicle::SetModelFile( string strModelFile )
{
	m_strModelFile = strModelFile;
}

void Vehicle::SetTaxingSoundFile( string strTaxingSoundFile )
{
	m_strTaxingSoundFile = strTaxingSoundFile;
}

void Vehicle::SetStartEngineSoundFile( string strStartEngineSoundFile )
{
	m_strStartEngineSoundFile = strStartEngineSoundFile;
}

void Vehicle::SetShutdownEngineSoundFile( string strShutdownEngineSoundFile )
{
	m_strShutdownEngineSoundFile = strShutdownEngineSoundFile;
}

void Vehicle::SetWarmwaitingSoundFile( string strWarmwaitingSoundFile )
{
	m_strWarmwaitingSoundFile = strWarmwaitingSoundFile;
}

int Vehicle::GetVehicleID()
{
	return m_iVehicleID;
}

std::string Vehicle::GetVehicleName()
{
	return m_strVehicleName;
}

int Vehicle::GetType()
{
	return m_iType;
}

double Vehicle::GetLength()
{
	return m_dLength;
}

double Vehicle::GetHeight()
{
	return m_dHeight;
}

double Vehicle::GetWidth()
{
	return m_dWidth;
}

double Vehicle::GetNormalTaxSpeed()
{
	return m_dNormalTaxSpeed;
}

double Vehicle::GetMinTaxSpeed()
{
	return m_dMinTaxSpeed;
}

double Vehicle::GetMaxTaxSpeed()
{
	return m_dMaxTaxSpeed;
}

double Vehicle::GetTurnSpeed()
{
	return m_dTurnSpeed;
}
double  Vehicle::GetReserveSpeed()
{
	return m_dReverseSpeed;
}
double Vehicle::GetNormalAccSpeed()
{
	return m_dNormalAccSpeed;
}

double Vehicle::GetMinAccSpeed()
{
	return m_dMinAccSpeed;
}

double Vehicle::GetMaxAccSpeed()
{
	return m_dMaxAccSpeed;
}

double Vehicle::GetNormalDecSpeed()
{
	return m_dNormalDecSpeed;
}

double Vehicle::GetMinDecSpeed()
{
	return m_dMinDecSpeed;
}

double Vehicle::GetMaxDecSpeed()
{
	return m_dMaxDecSpeed;
}

double Vehicle::GetMaxTaxBackSpd()
{
	return m_dMaxTaxSpeed;
}

double Vehicle::GetMaxFrontGearTurnHdg()
{
	return m_dMaxFrontGearTurnHdg;
}

double Vehicle::GetSizeTreadLen()
{
	return m_dSizeTreadLen;
}

double Vehicle::GetSizeTreadWidth()
{
	return m_dSizeTreadWidth;
}

double Vehicle::GetMinBrakeDis()
{
	return m_dMinBrakeDis;
}

double Vehicle::GetAttachHeading()
{
	return m_dAttachHeading;
}

std::string Vehicle::GetModelFile()
{
	return m_strModelFile;
}

std::string Vehicle::GetTaxingSoundFile()
{
	return m_strTaxingSoundFile;
}

std::string Vehicle::GetStartEngineSoundFile()
{
	return m_strStartEngineSoundFile;
}

std::string Vehicle::GetShutdownEngineSoundFile()
{
	return m_strShutdownEngineSoundFile;
}

std::string Vehicle::GetWarmwaitingSoundFile()
{
	return m_strWarmwaitingSoundFile;
}

void Vehicle::SetReverseSpeed( double dReverseSpeed )
{
	m_dReverseSpeed =dReverseSpeed;
}


void Vehicle::ReadFromBuffer( const char* pBuffer, int &iOffSize )
{
	const char* pTemp = pBuffer;
	memcpy(&m_iVehicleID, pTemp, sizeof(m_iVehicleID));
	pTemp += sizeof(m_iVehicleID);

	m_strVehicleName.assign(pTemp);
	pTemp += m_strVehicleName.size() + 1;

	memcpy(&m_dLength, pTemp, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);

	memcpy(&m_dHeight, pTemp, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(&m_dWidth, pTemp, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(&m_dNormalTaxSpeed, pTemp, sizeof(m_dNormalTaxSpeed));
	pTemp += sizeof(m_dNormalTaxSpeed);

	memcpy(&m_dMinTaxSpeed, pTemp, sizeof(m_dMinTaxSpeed));
	pTemp += sizeof(m_dMinTaxSpeed);

	memcpy(&m_dMaxTaxSpeed, pTemp, sizeof(m_dMaxTaxSpeed));
	pTemp += sizeof(m_dMaxTaxSpeed);

	memcpy(&m_dTurnSpeed, pTemp, sizeof(m_dTurnSpeed));
	pTemp += sizeof(m_dTurnSpeed);

	memcpy(&m_dNormalAccSpeed, pTemp, sizeof(m_dNormalAccSpeed));
	pTemp += sizeof(m_dNormalAccSpeed);

	memcpy(&m_dMinAccSpeed, pTemp, sizeof(m_dMinAccSpeed));
	pTemp += sizeof(m_dMinAccSpeed);

	memcpy(&m_dMaxAccSpeed, pTemp, sizeof(m_dMaxAccSpeed));
	pTemp += sizeof(m_dMaxAccSpeed);

	memcpy(&m_dNormalDecSpeed, pTemp, sizeof(m_dNormalDecSpeed));
	pTemp += sizeof(m_dNormalDecSpeed);

	memcpy(&m_dMinDecSpeed, pTemp, sizeof(m_dMinDecSpeed));
	pTemp += sizeof(m_dMinDecSpeed);

	memcpy(&m_dMaxDecSpeed, pTemp, sizeof(m_dMaxDecSpeed));
	pTemp += sizeof(m_dMaxDecSpeed);

	memcpy(&m_dMaxTaxBackSpd, pTemp, sizeof(m_dMaxTaxBackSpd));
	pTemp += sizeof(m_dMaxTaxBackSpd);

	memcpy(&m_dMaxFrontGearTurnHdg, pTemp, sizeof(m_dMaxFrontGearTurnHdg));
	pTemp += sizeof(m_dMaxFrontGearTurnHdg);

	memcpy(&m_dSizeTreadLen, pTemp, sizeof(m_dSizeTreadLen));
	pTemp += sizeof(m_dSizeTreadLen);

	memcpy(&m_dSizeTreadWidth, pTemp, sizeof(m_dSizeTreadWidth));
	pTemp += sizeof(m_dSizeTreadWidth);

	memcpy(&m_dMinBrakeDis, pTemp, sizeof(m_dMinBrakeDis));
	pTemp += sizeof(m_dMinBrakeDis);

	memcpy(&m_dAttachHeading, pTemp, sizeof(m_dAttachHeading));
	pTemp += sizeof(m_dAttachHeading);


	m_strModelFile.assign(pTemp);
	pTemp += m_strModelFile.size() + 1;

	m_strTaxingSoundFile.assign(pTemp);
	pTemp += m_strTaxingSoundFile.size() + 1;

	m_strStartEngineSoundFile.assign(pTemp);
	pTemp += m_strStartEngineSoundFile.size() + 1;

	m_strShutdownEngineSoundFile.assign(pTemp);
	pTemp += m_strShutdownEngineSoundFile.size() + 1;

	m_strWarmwaitingSoundFile.assign(pTemp);
	pTemp += m_strWarmwaitingSoundFile.size() + 1;

	iOffSize = pTemp - pBuffer;

}

void Vehicle::WriteToBuffer( char* pBuffer, int &iOffSize )
{
	char* pTemp = pBuffer;
	memcpy( pTemp, &m_iVehicleID,sizeof(m_iVehicleID));
	pTemp += sizeof(m_iVehicleID);

	memcpy(pTemp, m_strVehicleName.c_str(), m_strVehicleName.size() + 1);
	pTemp += m_strVehicleName.size() + 1;

	memcpy(pTemp, &m_dLength, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);

	memcpy(pTemp, &m_dHeight, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(pTemp, &m_dWidth, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(pTemp, &m_dNormalTaxSpeed, sizeof(m_dNormalTaxSpeed));
	pTemp += sizeof(m_dNormalTaxSpeed);

	memcpy(pTemp, &m_dMinTaxSpeed, sizeof(m_dMinTaxSpeed));
	pTemp += sizeof(m_dMinTaxSpeed);

	memcpy(pTemp, &m_dMaxTaxSpeed, sizeof(m_dMaxTaxSpeed));
	pTemp += sizeof(m_dMaxTaxSpeed);

	memcpy(pTemp, &m_dTurnSpeed, sizeof(m_dTurnSpeed));
	pTemp += sizeof(m_dTurnSpeed);

	memcpy(pTemp, &m_dNormalAccSpeed, sizeof(m_dNormalAccSpeed));
	pTemp += sizeof(m_dNormalAccSpeed);

	memcpy(pTemp, &m_dMinAccSpeed, sizeof(m_dMinAccSpeed));
	pTemp += sizeof(m_dMinAccSpeed);

	memcpy(pTemp, &m_dMaxAccSpeed, sizeof(m_dMaxAccSpeed));
	pTemp += sizeof(m_dMaxAccSpeed);

	memcpy(pTemp, &m_dNormalDecSpeed, sizeof(m_dNormalDecSpeed));
	pTemp += sizeof(m_dNormalDecSpeed);

	memcpy(pTemp, &m_dMinDecSpeed, sizeof(m_dMinDecSpeed));
	pTemp += sizeof(m_dMinDecSpeed);

	memcpy(pTemp, &m_dMaxDecSpeed, sizeof(m_dMaxDecSpeed));
	pTemp += sizeof(m_dMaxDecSpeed);

	memcpy(pTemp, &m_dMaxTaxBackSpd, sizeof(m_dMaxTaxBackSpd));
	pTemp += sizeof(m_dMaxTaxBackSpd);

	memcpy(pTemp, &m_dMaxFrontGearTurnHdg, sizeof(m_dMaxFrontGearTurnHdg));
	pTemp += sizeof(m_dMaxFrontGearTurnHdg);

	memcpy(pTemp, &m_dSizeTreadLen, sizeof(m_dSizeTreadLen));
	pTemp += sizeof(m_dSizeTreadLen);

	memcpy(pTemp, &m_dSizeTreadWidth, sizeof(m_dSizeTreadWidth));
	pTemp += sizeof(m_dSizeTreadWidth);

	memcpy(pTemp, &m_dMinBrakeDis, sizeof(m_dMinBrakeDis));
	pTemp += sizeof(m_dMinBrakeDis);

	memcpy(pTemp, &m_dAttachHeading, sizeof(m_dAttachHeading));
	pTemp += sizeof(m_dAttachHeading);

	memcpy(pTemp, m_strModelFile.c_str(), m_strModelFile.size() + 1);
	pTemp += m_strModelFile.size() + 1;

	memcpy(pTemp, m_strTaxingSoundFile.c_str(), m_strTaxingSoundFile.size() + 1);
	pTemp += m_strTaxingSoundFile.size() + 1;

	memcpy(pTemp,m_strStartEngineSoundFile.c_str(), m_strStartEngineSoundFile.size() + 1);
	pTemp += m_strStartEngineSoundFile.size() + 1;

	memcpy(pTemp,m_strShutdownEngineSoundFile.c_str(), m_strShutdownEngineSoundFile.size() + 1);
	pTemp += m_strShutdownEngineSoundFile.size() + 1;

	memcpy(pTemp,  m_strWarmwaitingSoundFile.c_str(),  m_strWarmwaitingSoundFile.size() + 1);
	pTemp +=  m_strWarmwaitingSoundFile.size() + 1;

	iOffSize = pTemp - pBuffer;
}

int Vehicle::GetBufferSize()
{	int iSize = 0;
iSize += sizeof(m_iVehicleID);	 
iSize += m_strVehicleName.size() + 1;   	
iSize += sizeof(m_iType);			  
iSize += sizeof(m_dLength);    
iSize += sizeof(m_dHeight);      
iSize += sizeof(m_dWidth);		  
iSize += sizeof(m_dNormalTaxSpeed);  
iSize += sizeof(m_dMinTaxSpeed);	  
iSize += sizeof(m_dMaxTaxSpeed);	    
iSize += sizeof(m_dTurnSpeed);	  	  
iSize += sizeof(m_dNormalAccSpeed);	    
iSize += sizeof(m_dMinAccSpeed);	    
iSize += sizeof(m_dMaxAccSpeed);	   
iSize += sizeof(m_dNormalDecSpeed);	    
iSize += sizeof(m_dMinDecSpeed);	    
iSize += sizeof(m_dMaxDecSpeed);	  	  
iSize += sizeof(m_dMaxTaxBackSpd);	  	  
iSize += sizeof(m_dMaxFrontGearTurnHdg);	      
iSize += sizeof(m_dSizeTreadLen);	   		 
iSize += sizeof(m_dSizeTreadWidth);	      	 
iSize += sizeof(m_dMinBrakeDis);	  	
iSize += sizeof(m_dAttachHeading);	  		
iSize += m_strModelFile.size() + 1;	 
iSize += m_strTaxingSoundFile.size() + 1;	
iSize += m_strStartEngineSoundFile.size() + 1;	
iSize += m_strShutdownEngineSoundFile.size() + 1;	
iSize += m_strWarmwaitingSoundFile.size() + 1;	
return iSize;
}

/*-----------------航空公司--------------*/
Company::Company()
{
	m_iCompanyID = 0;
	m_iIconID = 0;
	m_szCode = "";
	m_szCompanyName = "";
}

Company::Company( const Company &company )
{
	if (this == &company)
	{
		return;
	}
	this->m_iCompanyID = company.m_iCompanyID;
	this->m_szCompanyName = company.m_szCompanyName;
	this->m_szCode = company.m_szCode;
	this->m_iIconID = company.m_iIconID;
	this->m_vAircrafts = company.m_vAircrafts;
}

Company::~Company()
{

}

Company& Company::operator=( const Company& company_data )
{
	if (this == &company_data)
	{
		return *this;
	}
	this->m_iCompanyID = company_data.m_iCompanyID;
	this->m_szCompanyName = company_data.m_szCompanyName;
	this->m_szCode = company_data.m_szCode;
	this->m_iIconID = company_data.m_iIconID;
	this->m_vAircrafts = company_data.m_vAircrafts;
	return *this;
}

int Company::GetId()
{
	return m_iCompanyID;
}

std::string Company::GetDisplayLabel()
{
	return m_szCode;
}

void Company::SetCompanyID( int iCompanyID )
{
	m_iCompanyID = iCompanyID;
}

void Company::SetCompanyName( string szCompanyName )
{
	m_szCompanyName = szCompanyName;
}

void Company::SetCode( string szCode )
{
	m_szCode = szCode;
}

void Company::SetIconID( int iIconID )
{
	m_iIconID = iIconID;
}

void Company::SetAircrafts( std::vector<int>& vAircraftData )
{
	m_vAircrafts = vAircraftData;
}

int Company::GetCompanyID()
{
	return m_iCompanyID;
}

std::string Company::GetCompanyName()
{
	return m_szCompanyName;
}

std::string Company::GetCode()
{
	return m_szCode;
}

int Company::GetIconID()
{
	return m_iIconID;
}

std::vector<int>& Company::GetAircrafts()
{
	return m_vAircrafts;
}

/*-----------------航班--------------*/
Flight::Flight()
{
	m_iFlightID = 0;					/* 航班主键码 */
	m_iCompanyID = 0;				/* 航空公司ID */
	m_strCallsignNum = "";			/* 呼号编码 */
	m_iDefaultAircraft = 0;			/* 默认机型 */
	m_iDepartureAirportID = 0;	/* 出发机场ID */
	m_iArrivalAirportID = 0;		/* 到达机场ID */
	m_iAlternateAirportID = 0;	/* 备降机场ID */
	m_iDepartureTime = 0;			/* 预计起飞时间 从0点开始起的秒数 */
	m_iArrivalTime = 0;			/* 预计到达时间 从0点开始起的秒数 */
	m_iPeriod = 0;				/* 执行周期 每bit位从低到高表示星期数 */
}
Flight::Flight(const Flight &filght)
{
	if(this == &filght)
	{
		return;
	}
	*this =filght;
}
Flight& Flight::operator=(const Flight& flight)
{
	m_iFlightID = flight.m_iFlightID ;
	m_iCompanyID = flight.m_iCompanyID;
	m_strCallsignNum = flight.m_strCallsignNum;
	m_iDefaultAircraft = flight.m_iDefaultAircraft;
	m_iDepartureAirportID = flight.m_iDepartureAirportID;
	m_iArrivalAirportID = flight.m_iArrivalAirportID;
	m_iAlternateAirportID = flight.m_iAlternateAirportID;
	m_iDepartureTime = flight.m_iDepartureTime;
	m_iArrivalTime = flight.m_iArrivalTime;
	m_iPeriod = flight.m_iPeriod;
	return *this ;
}
std::string Flight::GetDisplayLabel()
{
	return m_strCallsignNum;
}
void Flight::Copy(boost::shared_ptr<Flight> spFlight)
{

}
int Flight::GetAlternateAirportId()
{
	return m_iAlternateAirportID;
}
int Flight::GetArrivalAirportId()
{
	return m_iArrivalAirportID;
}
int Flight::GetDepartureAirportId()
{
	return m_iDepartureAirportID;
}
int Flight::GetCompanyId()
{
	return m_iCompanyID;
}
int Flight::GetFlightId()
{
	return m_iFlightID;
}
int Flight::GetDefaultAircraft()
{
	return m_iDefaultAircraft;
}
int Flight::GetArrivalTime()
{
	return m_iArrivalTime;
}
int Flight::GetDepartureTime()
{
	return m_iDepartureTime;
}
int Flight::GetPeriod()
{
	return m_iPeriod;
}

std::string Flight::GetCallsignNum()
{
	return m_strCallsignNum;
}

void Flight::SetFlightId(int iFlightID)
{
	m_iFlightID = iFlightID;
}
void Flight::SetCallSignNum(std::string strCallsignNum)
{
	m_strCallsignNum = strCallsignNum;
}
void Flight::SetCompanyId(int iCompanyID)
{
	m_iCompanyID = iCompanyID;
}
void Flight::SetDefaultAircraft(int iDefaultAircraft)
{
	m_iDefaultAircraft = iDefaultAircraft;
}
void Flight::SetDepartureAirportId(int iDepartureAirportID)
{
	m_iDepartureAirportID = iDepartureAirportID;
}
void Flight::SetArrivalAirportId(int iArrivalAirportID)
{
	m_iArrivalAirportID = iArrivalAirportID; 
}
void Flight::SetAlternateAirportId(int iAlternateAirportID)
{
	m_iAlternateAirportID = iAlternateAirportID; 
}

void Flight::SetArrivalTime(int iArrivalTime)
{
	m_iArrivalTime = iArrivalTime;
}
void Flight::SetDepartureTime(int iDepartureTime)
{
	m_iDepartureTime = iDepartureTime;
}
void Flight::SetPeriod(int iPeriod)
{
	m_iPeriod = iPeriod ;
}

void Flight::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iFlightID, pTemp, sizeof(m_iFlightID));
	pTemp += sizeof(m_iFlightID);

	memcpy(&m_iCompanyID, pTemp, sizeof(m_iCompanyID));
	pTemp += sizeof(m_iCompanyID);

	m_strCallsignNum.assign(pTemp);
	pTemp += m_strCallsignNum.size() + 1;

	memcpy(&m_iDefaultAircraft, pTemp, sizeof(m_iDefaultAircraft));
	pTemp += sizeof(m_iDefaultAircraft);

	memcpy(&m_iDepartureAirportID, pTemp, sizeof(m_iDepartureAirportID));
	pTemp += sizeof(m_iDepartureAirportID);

	memcpy(&m_iArrivalAirportID, pTemp, sizeof(m_iArrivalAirportID));
	pTemp += sizeof(m_iArrivalAirportID);

	memcpy(&m_iAlternateAirportID, pTemp, sizeof(m_iAlternateAirportID));
	pTemp += sizeof(m_iAlternateAirportID);

	memcpy(&m_iDepartureTime, pTemp, sizeof(m_iDepartureTime));
	pTemp += sizeof(m_iDepartureTime);

	memcpy(&m_iArrivalTime, pTemp, sizeof(m_iArrivalTime));
	pTemp += sizeof(m_iArrivalTime);

	memcpy(&m_iPeriod, pTemp, sizeof(m_iPeriod));
	pTemp += sizeof(m_iPeriod);

	iOffSize = pTemp - pBuffer;

}
void Flight::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iFlightID, sizeof(m_iFlightID));
	pTemp += sizeof(m_iFlightID);

	memcpy(pTemp, &m_iCompanyID, sizeof(m_iCompanyID));
	pTemp += sizeof(m_iCompanyID);

	memcpy(pTemp, m_strCallsignNum.c_str(), m_strCallsignNum.size() + 1);
	pTemp += m_strCallsignNum.size() + 1;

	memcpy(pTemp, &m_iDefaultAircraft, sizeof(m_iDefaultAircraft));
	pTemp += sizeof(m_iDefaultAircraft);

	memcpy(pTemp, &m_iDepartureAirportID, sizeof(m_iDepartureAirportID));
	pTemp += sizeof(m_iDepartureAirportID);

	memcpy(pTemp, &m_iArrivalAirportID, sizeof(m_iArrivalAirportID));
	pTemp += sizeof(m_iArrivalAirportID);

	memcpy(pTemp, &m_iDepartureTime, sizeof(m_iDepartureTime));
	pTemp += sizeof(m_iDepartureTime);

	memcpy(pTemp, &m_iArrivalTime, sizeof(m_iArrivalTime));
	pTemp += sizeof(m_iArrivalTime);

	memcpy(pTemp, &m_iPeriod, sizeof(m_iPeriod));
	pTemp += sizeof(m_iPeriod);
	iOffSize = pTemp - pBuffer;
}
int Flight::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iFlightID);
	iSize += sizeof(m_iCompanyID);
	iSize += m_strCallsignNum.size() + 1;
	iSize += sizeof(m_iDefaultAircraft);
	iSize += sizeof(m_iArrivalAirportID);
	iSize += sizeof(m_iAlternateAirportID);
	iSize += sizeof(m_iDepartureTime);
	iSize += sizeof(m_iArrivalTime);
	iSize += sizeof(m_iPeriod);
	iSize += sizeof(int);
	return iSize;
}

AircraftPerformance::AircraftPerformance()
{

}

AircraftPerformance::~AircraftPerformance()
{

}

int AircraftPerformance::GetId()
{
	return m_iAircraftPerformaceID;
}

std::string AircraftPerformance::GetDisplayLabel()
{
	return m_strNameICAO;
}

AltSimulate::AltSimulate()
{

}

AltSimulate::~AltSimulate()
{

}

int AltSimulate::GetId()
{
	return m_iAltsimulateId;
}

int AltSimulate::GetOwnerId()
{
	return m_iAircraftPerformanceId;
}

SpdSimulate::SpdSimulate()
{

}

SpdSimulate::~SpdSimulate()
{

}

int SpdSimulate::GetId()
{
	return m_iSpdSimulateId;
}

int SpdSimulate::GetOwnerId()
{
	return m_iAircraftPerformanceId;
}

FlyEnvelope::FlyEnvelope()
{

}

FlyEnvelope::~FlyEnvelope()
{

}

int FlyEnvelope::GetId()
{
	return m_iFlyEnvelopeId;
}

int FlyEnvelope::GetOwnerId()
{
	return m_iAircraftPerformanceId;
}

LandPhase::LandPhase()
{

}

LandPhase::~LandPhase()
{

}

int LandPhase::GetId()
{
	return m_iLandPhaseID;
}

int LandPhase::GetOwnerId()
{
	return m_iAircraftPerformanceID;
}

AircraftModel::AircraftModel()
{

}

AircraftModel::~AircraftModel()
{

}

int AircraftModel::GetId()
{
	return m_iAircraftModelID;
}

int AircraftModel::GetOwnerId()
{
	return m_iAircraftPerformanceID;
}

PhaseOnRunway::PhaseOnRunway()
{

}

PhaseOnRunway::~PhaseOnRunway()
{

}

int PhaseOnRunway::GetId()
{
	return m_dPhaseOnRunwayId;
}

int PhaseOnRunway::GetOwnerId()
{
	return m_dAircraftPerformanceId;
}

/*-----------------机型(视景用)--------------*/
AircraftForVis::AircraftForVis()
{
	m_iAircraftID = 0;
	m_strModelFile = "飞机模型";		//!<飞机的模型文件名称
	m_dSizeWidth = 0;			//!<宽度
	m_dSizeLength = 0;			//!<长度
	m_dSizeHeight = 0;			//!<高度
	m_dDisFrontRearWheel = 0;	//!<前后轮距
	m_dDisBetweenRearWheel = 0;	//!<左右轮距
	m_dGearHeight = 0;			//!<起落架高度
	m_dDisFrontWheel2Nose = 0;	//!<前轮到机头距离
	m_dDisRearWheel2Tail = 0;	//!<后起落架到尾部距离

	m_strStartEngineSoundFile = "";	//!<启动引擎声音文件
	m_strShutEngineSoundFile = "";	//!<关引擎声音文件
	m_strLaunchSoundFile = "";		//!<起飞声音文件
	m_strLandSoundFile = "";			//!<降落声音文件
	m_strTaxSoundFile = "";			//!<滑行声音文件
	m_strFlySoundFile = "";			//!<飞行声音文件

	m_dAirframeLength = 0;	//!<Length of plane (from origin to door)
	m_dAirframeWidth = 0;	//!<Width of Plane(Excluding swing)
	m_dAirframeHeight = 0;	//!<the height of plane's door to earth

	m_bIsPlane = false;		//!<是否是飞机
	m_bIsHelicopter = false;	//!<是否是直升机
	m_bIsAirForce = false;		//!<是否为军机
}

AircraftForVis::~AircraftForVis()
{

}

//
int AircraftForVis::GetId()
{
	return m_iAircraftID;
}
int AircraftForVis::GetOwnerId()
{
	return 0;
}
string AircraftForVis::GetDisplayLabel()
{
	return "";
}


/*-----------------车辆(视景用)--------------*/
VehicleForVis::VehicleForVis()
{
	m_iVehicleID = 0;
	m_strModelFile = "车辆模型";
	m_dSizeWidth = 0;
	m_dSizeLength = 0;
	m_dSizeHeight = 0;
	m_strStartEngineSoundFile = "";	
	m_strShutEngineSoundFile = "";	
	m_strTaxSoundFile = "";			
}

VehicleForVis::~VehicleForVis()
{

}