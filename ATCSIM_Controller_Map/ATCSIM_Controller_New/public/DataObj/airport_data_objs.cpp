#include "airport_data_objs.h"


/*-----------------机场--------------*/
AirportData::AirportData(void)
{
	m_iAirportID = 0;		
	m_iAirspaceID = 0;		
	m_szAirportName = "机场";		
	m_szAirportCode = "AAAA";	
	m_dCenterPointLongitude = 0;	
	m_dCenterPointLatitude = 0;		
	m_dElevation = 0;				
	m_dMegaticDiff = 0;		
	m_iMainRunway = 0;		
	m_iDefaultEnvID = 0;		
}

AirportData::~AirportData(void)
{
}


int AirportData::GetId()
{
	return m_iAirportID;
}

int AirportData::GetOwnerId()
{
	return m_iAirspaceID;
}

std::string AirportData::GetDisplayLabel()
{
	return m_szAirportCode;
}


void AirportData::Copy( boost::shared_ptr<AirportData> spAirport )
{

}

void AirportData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}

void AirportData::SetAirspaceID(int iAirspaceID)
{
	m_iAirspaceID = iAirspaceID;
}

void AirportData::SetAirportName(string szAirportName)
{
	m_szAirportName = szAirportName;
}

void AirportData::SetAirportCode(string szCode)
{
	m_szAirportCode = szCode;
}

void AirportData::SetCenterPointLongitude(double dCenterPointLongitude)
{
	m_dCenterPointLongitude = dCenterPointLongitude;
}

void AirportData::SetCenterPointLatitude(double dCenterPointLatitude)
{
	m_dCenterPointLatitude = dCenterPointLatitude;
}

void AirportData::SetElevation(double dElevation)
{
	m_dElevation = dElevation;
}

void AirportData::SetMegaticDiff(double dMegaticDiff)
{
	m_dMegaticDiff = dMegaticDiff;
}

void AirportData::SetMainRunway(int iMainRunway)
{
	m_iMainRunway = iMainRunway;
}

void AirportData::SetDefaultEnvID(int iDefaultEnvID)
{
	m_iDefaultEnvID = iDefaultEnvID;
}

void AirportData::SetHeading(double dHeading)
{
	m_dHeading = dHeading;
}

int AirportData::GetAirportID()
{
	return m_iAirportID;
}

int AirportData::GetAirspaceID()
{
	return m_iAirspaceID;
}

string AirportData::GetAirportName()
{
	return m_szAirportName;
}

string AirportData::GetAirportCode()
{
	return m_szAirportCode;
}

double AirportData::GetCenterPointLongitude()
{
	return m_dCenterPointLongitude;
}

double AirportData::GetCenterPointLatitude()
{
	return m_dCenterPointLatitude;
}

double AirportData::GetElevation()
{
	return m_dElevation;
}

double AirportData::GetMegaticDiff()
{
	return m_dMegaticDiff;
}

int AirportData::GetMainRunway()
{
	return m_iMainRunway;
}

int AirportData::GetDefaultEnvID()
{
	return m_iDefaultEnvID;
}

double AirportData::GetHeading()
{
	return m_dHeading;
}

void AirportData::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(&m_iAirspaceID, pTemp, sizeof(m_iAirspaceID));
	pTemp += sizeof(m_iAirspaceID);

	m_szAirportName.assign(pTemp);
	pTemp += m_szAirportName.size() + 1;

	m_szAirportCode.assign(pTemp);
	pTemp += m_szAirportCode.size() + 1;

	memcpy(&m_dCenterPointLongitude, pTemp, sizeof(m_dCenterPointLongitude));
	pTemp += sizeof(m_dCenterPointLongitude);

	memcpy(&m_dCenterPointLatitude, pTemp, sizeof(m_dCenterPointLatitude));
	pTemp += sizeof(m_dCenterPointLatitude);

	memcpy(&m_dElevation, pTemp, sizeof(m_dElevation));
	pTemp += sizeof(m_dElevation);

	memcpy(&m_dMegaticDiff, pTemp, sizeof(m_dMegaticDiff));
	pTemp += sizeof(m_dMegaticDiff);

	memcpy(&m_iMainRunway, pTemp, sizeof(m_iMainRunway));
	pTemp += sizeof(m_iMainRunway);

	memcpy(&m_iDefaultEnvID, pTemp, sizeof(m_iDefaultEnvID));
	pTemp += sizeof(m_iDefaultEnvID);

	memcpy(&m_dHeading, pTemp, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	iOffSize = pTemp - pBuffer;
}

void AirportData::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, &m_iAirspaceID, sizeof(m_iAirspaceID));
	pTemp += sizeof(m_iAirspaceID);

	memcpy(pTemp, m_szAirportName.c_str(), m_szAirportName.size() + 1);;
	pTemp += m_szAirportName.size() + 1;

	memcpy(pTemp, m_szAirportCode.c_str(), m_szAirportCode.size() + 1);
	pTemp += m_szAirportCode.size() + 1;

	memcpy(pTemp, &m_dCenterPointLongitude, sizeof(m_dCenterPointLongitude));
	pTemp += sizeof(m_dCenterPointLongitude);

	memcpy(pTemp, &m_dCenterPointLatitude, sizeof(m_dCenterPointLatitude));
	pTemp += sizeof(m_dCenterPointLatitude);

	memcpy(pTemp, &m_dElevation, sizeof(m_dElevation));
	pTemp += sizeof(m_dElevation);

	memcpy(pTemp, &m_dMegaticDiff, sizeof(m_dMegaticDiff));
	pTemp += sizeof(m_dMegaticDiff);

	memcpy(pTemp, &m_iMainRunway, sizeof(m_iMainRunway));
	pTemp += sizeof(m_iMainRunway);

	memcpy(pTemp, &m_iDefaultEnvID, sizeof(m_iDefaultEnvID));
	pTemp += sizeof(m_iDefaultEnvID);

	memcpy(pTemp, &m_dHeading, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	iOffSize = pTemp - pBuffer;
}

int AirportData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iAirportID);
	iSize += sizeof(m_iAirspaceID);
	iSize += m_szAirportName.size() + 1;
	iSize += m_szAirportCode.size() + 1;
	iSize += sizeof(m_dCenterPointLongitude);
	iSize += sizeof(m_dCenterPointLatitude);
	iSize += sizeof(m_dElevation);
	iSize += sizeof(m_dMegaticDiff);
	iSize += sizeof(m_iMainRunway);
	iSize += sizeof(m_iDefaultEnvID);
	iSize += sizeof(m_dHeading);
	return iSize;
}


/*-----------------固定点--------------*/
FixpointData::FixpointData(void)
{
	 m_iFixpointID = 0 ;
	 m_iIconID= 0	;		
	 m_szFixpointName  = "固定点" ;	
	 m_iAirportID  = 0;			
	 m_iFixpointType =0;			
	 m_dX =0;				
	 m_dY =0;			
	 m_dZ =0;				
   m_bWaitingPoint =false;
}

FixpointData::~FixpointData(void)
{
}

int FixpointData::GetId()
{
	return m_iFixpointID;
}

int FixpointData::GetOwnerId()
{
	return m_iAirportID;
}

std::string FixpointData::GetDisplayLabel()
{
	return m_szFixpointName;
}

void FixpointData::Copy(boost::shared_ptr<FixpointData> spFixpoint)
{

}

void FixpointData::SetFixpointID(int iFixpointID)
{
	m_iFixpointID = iFixpointID;
}

void FixpointData::SetIconID(int iIConID)
{
	m_iIconID = iIConID;
}

void FixpointData::SetFixpointName(string szFixpointName)
{
	m_szFixpointName = szFixpointName;
}

void FixpointData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}

void FixpointData::SetFixpointType(int iFixpointType)
{
	m_iFixpointType = iFixpointType;
}

void FixpointData::SetX(double dX)
{
	m_dX = dX;
}

void FixpointData::SetY(double dY)
{
	m_dY = dY;
}

void FixpointData::SetZ( double dZ )
{
	m_dZ = dZ;
}

void FixpointData::SetIsWaitingPoint(bool bWaitingPoint)
{
	m_bWaitingPoint = bWaitingPoint;
}

int FixpointData::GetFixpointID()
{
	return m_iFixpointID;
}

int FixpointData::GetIconID()
{
	return m_iIconID;
}

string FixpointData::GetFixpointName()
{
	return m_szFixpointName;
}

int FixpointData::GetAirportID()
{
	return m_iAirportID;
}

int FixpointData::GetFixpointType()
{
	return m_iFixpointType;
}

double FixpointData::GetX()
{
	return m_dX;
}

double FixpointData::GetY()
{
	return m_dY;
}

double FixpointData::GetZ()
{
	return m_dZ;
}

bool FixpointData::GetIsWaitingPoint()
{
	return m_bWaitingPoint;
}

void FixpointData::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iFixpointID, pTemp, sizeof(m_iFixpointID));
	pTemp += sizeof(m_iFixpointID);

	memcpy(&m_iIconID, pTemp, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	m_szFixpointName.assign(pTemp);
	pTemp += m_szFixpointName.size() + 1;

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(&m_iFixpointType, pTemp, sizeof(m_iFixpointType));
	pTemp += sizeof(m_iFixpointType);

	memcpy(&m_dX, pTemp, sizeof(m_dX));
	pTemp += sizeof(m_dX);

	memcpy(&m_dY, pTemp, sizeof(m_dY));
	pTemp += sizeof(m_dY);

	memcpy(&m_dZ, pTemp, sizeof(m_dZ));
	pTemp += sizeof(m_dZ);

	memcpy(&m_bWaitingPoint, pTemp, sizeof(m_bWaitingPoint));
	pTemp += sizeof(m_bWaitingPoint);

	iOffSize = pTemp - pBuffer;
}

void FixpointData::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iFixpointID, sizeof(m_iFixpointID));
	pTemp += sizeof(m_iFixpointID);

	memcpy(pTemp, &m_iIconID, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	memcpy(pTemp, m_szFixpointName.c_str(), m_szFixpointName.size() + 1);
	pTemp += m_szFixpointName.size() + 1;

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, &m_iFixpointType, sizeof(m_iFixpointType));
	pTemp += sizeof(m_iFixpointType);

	memcpy(pTemp, &m_dX, sizeof(m_dX));
	pTemp += sizeof(m_dX);

	memcpy(pTemp, &m_dY, sizeof(m_dY));
	pTemp += sizeof(m_dY);

	memcpy(pTemp, &m_dZ, sizeof(m_dZ));
	pTemp += sizeof(m_dZ);

	memcpy(pTemp, &m_bWaitingPoint, sizeof(m_bWaitingPoint));
	pTemp += sizeof(m_bWaitingPoint);

	iOffSize = pTemp - pBuffer;
}

int FixpointData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iFixpointID);
	iSize += sizeof(m_iIconID);
	iSize += m_szFixpointName.size() + 1;
	iSize += sizeof(m_iAirportID);
	iSize += sizeof(m_iFixpointType);
	iSize += sizeof(m_dX);
	iSize += sizeof(m_dY);
	iSize += sizeof(m_dZ);
	iSize += sizeof(m_bWaitingPoint);
	return iSize;
}


/*-----------------道路上的固定点--------------*/
RoadFixpointData::RoadFixpointData(void)
{
	 m_iRoadID = 0;			/*道路ID*/
	 m_iSequence = 0;			/*固定点的序号 not null*/
	 m_iFixpointID = 0;			/*固定点*/
}

RoadFixpointData::~RoadFixpointData(void)
{
}

int RoadFixpointData::GetId()
{
	return m_iRoadID;
}

std::string RoadFixpointData::GetDisplayLabel()
{
	return "";
}

void RoadFixpointData::Copy(boost::shared_ptr<RoadFixpointData> spRoadFixpoint)
{

}

void RoadFixpointData::SetRoadID(int iRoadID)
{
	m_iRoadID = iRoadID;
}

void RoadFixpointData::SetSequence(int iSeq)
{
	m_iSequence = iSeq;
}

void RoadFixpointData::SetFixpointID(int iFixpointID)
{
	m_iFixpointID = iFixpointID;
}

int RoadFixpointData::GetRoadID()
{
	return m_iRoadID;
}

int RoadFixpointData::GetSequence()
{
	return m_iSequence;
}

int RoadFixpointData::GetFixpointID()
{
	return m_iFixpointID;
}

void RoadFixpointData::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iRoadID, pTemp, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(&m_iSequence, pTemp, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(&m_iFixpointID, pTemp, sizeof(m_iFixpointID));
	pTemp += sizeof(m_iFixpointID);

	iOffSize = pTemp - pBuffer;
}

void RoadFixpointData::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iRoadID, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(pTemp, &m_iSequence, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(pTemp, &m_iFixpointID, sizeof(m_iFixpointID));
	pTemp += sizeof(m_iFixpointID);

	iOffSize = pTemp - pBuffer;
}

int RoadFixpointData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iRoadID);
	iSize += sizeof(m_iSequence);
	iSize += sizeof(m_iFixpointID);
	return iSize;
}


/*-----------------道路--------------*/
RoadData::RoadData(void)
{
	m_iRoadID = 0;
	m_iAirportID = 0;
	m_szRoadName = "道路";
	m_iRoadType = 1;	
	m_dWidth = 20;
}

RoadData::~RoadData(void)
{
}


RoadData::RoadData(const RoadData &roadData)
{
	if(this == &roadData)
	{
		return;
	}
	*this = roadData;
}

RoadData& RoadData::operator=(const RoadData& roadData)
{
	if (this == &roadData)
	{
		return *this;
	}
	this->m_iRoadID = roadData.m_iRoadID;
	this->m_iAirportID = roadData.m_iAirportID;
	this->m_szRoadName = roadData.m_szRoadName;
	this->m_iRoadType = roadData.m_iRoadType ;
	this->m_dWidth = roadData.m_dWidth;
	this->m_iMaxAircraft = roadData.m_iMaxAircraft;
	this->m_vRoadFixpoints.clear();
	for(unsigned int i = 0; i < roadData.m_vRoadFixpoints.size(); i++)
	{
		boost::shared_ptr<RoadFixpointData> spData = boost::make_shared<RoadFixpointData>();
		*(spData.get()) = *(roadData.m_vRoadFixpoints.at(i).get());
		this->m_vRoadFixpoints.push_back(spData);
	}
	return *this;
}

void RoadData::Copy(boost::shared_ptr<RoadData> spRoad)
{

}

int RoadData::GetId()
{
	return m_iRoadID;
}

int RoadData::GetOwnerId()
{
	return m_iAirportID;
}

std::string RoadData::GetDisplayLabel()
{
	return m_szRoadName;
}

void RoadData::SetRoadID(int iRoadID)
{
	m_iRoadID = iRoadID;
}

void RoadData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}
void RoadData::SetRoadName(string szRoadName)
{
	m_szRoadName = szRoadName;
}
void RoadData::SetRoadType(int iRoadType)
{
	m_iRoadType = iRoadType;
}
void RoadData::SetWidth(double dRoadWidth)
{
	m_dWidth = dRoadWidth;
}
void RoadData::SetMaxAircraft(int iMaxAirCraft)
{
	m_iMaxAircraft =  iMaxAirCraft;
}

int RoadData::GetRoadID()
{
	return m_iRoadID;
}

int RoadData::GetAirportID()
{
	return m_iAirportID;
}

std::string RoadData::GetRoadName()
{
	return m_szRoadName;
}

int RoadData::GetRoadType()
{
	return m_iRoadType;
}

double RoadData::GetRoadWidth()
{
	return m_dWidth;
}

int RoadData::GetMaxAircraft()
{
	return m_iMaxAircraft;
}

vector<boost::shared_ptr<RoadFixpointData> >&  RoadData::GetFixpoints()
{
	return m_vRoadFixpoints;
}

void RoadData::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iRoadID, pTemp, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	m_szRoadName.assign(pTemp);
	pTemp += m_szRoadName.size() + 1;

	memcpy(&m_iRoadType, pTemp, sizeof(m_iRoadType));
	pTemp += sizeof(m_iRoadType);

	memcpy(&m_dWidth, pTemp, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(&m_iMaxAircraft, pTemp, sizeof(m_iMaxAircraft));
	pTemp += sizeof(m_iMaxAircraft);

	int iRoadFixpointCount = 0;
	memcpy(&iRoadFixpointCount, pTemp, sizeof(iRoadFixpointCount));
	pTemp += sizeof(iRoadFixpointCount);

	for(unsigned int i = 0; i < iRoadFixpointCount; i++)
	{
		int iOffSize_inline = 0;
		shared_ptr<RoadFixpointData> spRoadFixpointData = make_shared<RoadFixpointData>();
		spRoadFixpointData->ReadFromBuffer(pTemp, iOffSize_inline);
		m_vRoadFixpoints.push_back(spRoadFixpointData);
		//pTemp += spRoadFixpointData->GetBufferSize();
		pTemp += iOffSize_inline;
	}

	iOffSize = pTemp - pBuffer;
}

void RoadData::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iRoadID, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, m_szRoadName.c_str(), m_szRoadName.size() + 1);
	//memcpy(pTemp, &m_szRoadName, m_szRoadName.size() + 1);
	pTemp += m_szRoadName.size() + 1;

	memcpy(pTemp, &m_iRoadType, sizeof(m_iRoadType));
	pTemp += sizeof(m_iRoadType);

	memcpy(pTemp, &m_dWidth, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(pTemp, &m_iMaxAircraft, sizeof(m_iMaxAircraft));
	pTemp += sizeof(m_iMaxAircraft);

	int iRoadFixpointCount = m_vRoadFixpoints.size();
	memcpy(pTemp, &iRoadFixpointCount, sizeof(iRoadFixpointCount));
	pTemp += sizeof(iRoadFixpointCount);

	for(unsigned int i = 0; i < iRoadFixpointCount; i++)
	{
		int iOffSize_inline = 0;
		shared_ptr<RoadFixpointData> spRoadFixpointData = m_vRoadFixpoints.at(i);
		spRoadFixpointData->WriteToBuffer(pTemp, iOffSize_inline);
		pTemp += iOffSize_inline;
		//pTemp += spRoadFixpointData->GetBufferSize();
	}

	iOffSize = pTemp - pBuffer;
}

int RoadData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iRoadID);
	iSize += sizeof(m_iAirportID);
	iSize += m_szRoadName.size() + 1;
	iSize += sizeof(m_iRoadType);
	iSize += sizeof(m_dWidth);
	iSize += sizeof(m_iMaxAircraft);
	iSize += sizeof(int);
	if(m_vRoadFixpoints.size() != 0)
	{
		iSize += m_vRoadFixpoints.size() * m_vRoadFixpoints.at(0)->GetBufferSize();
	}

	return iSize;
}

void RoadData::SetFixpoints( vector<boost::shared_ptr<RoadFixpointData> >& vData )
{
	m_vRoadFixpoints.clear();
	m_vRoadFixpoints = vData;
}

/*------------------路线中的固定点或道路*/
RouteFixpointRoad::RouteFixpointRoad()
{
	m_iRouteID		= 0;
	m_iSequence	= 0;
	m_iFactorType  = 1;
	m_iFactorID		= 0;

}

RouteFixpointRoad::~RouteFixpointRoad( void )
{

}

int RouteFixpointRoad::GetId()
{
	return m_iRouteID;
}

std::string RouteFixpointRoad::GetDisplayLabel()
{
	return "";
}

void RouteFixpointRoad::Copy( boost::shared_ptr<RouteFixpointRoad> spRoadFixpoint )
{
	
}

int RouteFixpointRoad::GetSequence()
{
	return m_iSequence;
}

void RouteFixpointRoad::SetSequence( int iSeq )
{
	m_iSequence = iSeq;
}
/*------------------路线---------------*/
int Route::GetId()
{
	return m_iRouteID;
}

int Route::GetOwnerId()
{
	return m_iAirportID;
}

std::string Route::GetDisplayLabel()
{
	return m_szRouteName;
}

void Route::Copy( boost::shared_ptr<Route> spRoad )
{

}

Route::Route( void )
{
	m_iRouteID = 0;					/*路线ID*/
	m_iAirportID = 0;					/*机场ID*/
	m_szRouteName = "路线";	/*路线名称*/
	m_iType = 1;			/*路线适合给什么对象使用，1飞机，2车辆 */
	m_dLength = 0;	/*路线的长度（单位：千米）not null default 0 */
	m_dWidth = 0;		/*路线的宽度*/
	m_dWaitX = 0;		/*等待点X坐标*/
	m_dWaitY = 0;		/*等待点Y坐标*/
}

Route::Route( const Route &routeFixpointRoadData )
{
	if(this == &routeFixpointRoadData)
	{
		return;
	}
	*this = routeFixpointRoadData;
}

Route::~Route( void )
{

}

Route& Route::operator=( const Route& routeFixpointRoadData )
{
	if (this == &routeFixpointRoadData)
	{
		return *this;
	}
	this->m_iRouteID = routeFixpointRoadData.m_iRouteID;
	this->m_iAirportID = routeFixpointRoadData.m_iAirportID;
	this->m_szRouteName = routeFixpointRoadData.m_szRouteName;
	this->m_iType = routeFixpointRoadData.m_iType ;
	this->m_dLength = routeFixpointRoadData.m_dLength;
	this->m_dWidth = routeFixpointRoadData.m_dWidth;
	this->m_dWaitX = routeFixpointRoadData.m_dWaitX;
	this->m_dWaitY = routeFixpointRoadData.m_dWaitY;
	this->m_vRouteFixpointRoad.clear();
	for(unsigned int i = 0; i < routeFixpointRoadData.m_vRouteFixpointRoad.size(); i++)
	{
		boost::shared_ptr<RouteFixpointRoad> spData = boost::make_shared<RouteFixpointRoad>();
		*(spData.get()) = *(routeFixpointRoadData.m_vRouteFixpointRoad.at(i).get());
		this->m_vRouteFixpointRoad.push_back(spData);
	}
	return *this;
}


/*-----------------停机位--------------*/
GateData::GateData(void)
{
	 m_iGateID = 0;			
	m_iAirportID = 0;		
	 m_szGateDataName = "停机位名称";		
	 m_iRoadID = 0;			
	 m_iInGateDataFixpointID = 0;	
	 m_iGateFixpointID = 0;		
	 m_dLength = 0;		
	 m_iMaxAircraftID = 0;		
	 m_iInternationalType = 0;	
	 m_iBelongedCompanyID = 0;		
	 m_iStartPosition = 0;		
	 m_bIsDirectTax  =false;	
	 m_iRoutineInLine = 0;	
	 m_iRoutineOutLine = 0;
	 m_iRoutineToRunway = 0;	
}

GateData::~GateData(void)
{
}

int GateData::GetId()
{
	return m_iGateID;
}

int GateData::GetOwnerId()
{
	return m_iAirportID;
}

std::string GateData::GetDisplayLabel()
{
	return m_szGateDataName;
}

void GateData::SetGateID(int iGateID)
{
	m_iGateID = iGateID;
}

void GateData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}

void GateData::SetGateName( string szName )
{
	m_szGateDataName = szName;
}

void GateData::SetRoadID(int iRoadID)
{
	m_iRoadID = iRoadID;
}

void GateData::SetInGateDataFixpointID(int iInGateDataFixpointID)
{
	m_iInGateDataFixpointID = iInGateDataFixpointID;
}

void GateData::SetGateFixpointID(int iGateFixpointID)
{
	m_iGateFixpointID = iGateFixpointID;
}

void GateData::SetLength(double dLength)
{
	m_dLength = dLength;
}
void GateData::SetMaxAircraftID(int iMaxAircraftID)
{
	m_iMaxAircraftID = iMaxAircraftID;
}

void GateData::SetInternationalType(int  iInternationalType)
{
	m_iInternationalType = iInternationalType;
}

void GateData::SetBelongedCompanyID(int iBelongedCompanyID)
{
	m_iBelongedCompanyID = iBelongedCompanyID;
}

void GateData::SetStartPosition(int iStartPosition)
{
	m_iStartPosition = iStartPosition;
}

void GateData::SetIsDirectTax(bool bIsDirectTax)
{
	m_bIsDirectTax = bIsDirectTax;
}

void GateData::SetRoutineInLine(int iRoutineInLine)
{
	m_iRoutineInLine = iRoutineInLine;
}

void GateData::SetRoutinOutLine(int iRoutineOutLine)
{
	m_iRoutineOutLine = iRoutineOutLine;
}

void GateData::SetRoutinToRunway(int iRoutineToRunway)
{
	m_iRoutineToRunway = iRoutineToRunway;
}

int GateData::GetGateID()
{
	return m_iGateID;
}

int GateData::GetAirportID()
{
	return m_iAirportID;
}

std::string GateData::GetGateName()
{
	return m_szGateDataName;
}

int GateData::GetRoadID()
{
	return m_iRoadID;
}

int GateData::GetInGateDataFixpointID()
{
	return m_iInGateDataFixpointID;
}

int GateData::GetGateFixpointID()
{
	return m_iGateFixpointID;
}

double GateData::GetLength()
{
	return m_dLength;
}

int GateData::GetMaxAircraftID()
{
	return m_iMaxAircraftID;
}

int GateData::GetInternationalType()
{
	return m_iInternationalType;
}

int GateData::GetBelongedCompanyID()
{
	return m_iBelongedCompanyID;
}

int GateData::GetStartPosition()
{
	return m_iStartPosition;
}

bool GateData::GetIsDirectTax()
{
	return m_bIsDirectTax;
}

int GateData::GetRoutineInLine()
{
	return m_iRoutineInLine;
}

int GateData::GetRoutinOutLine()
{
	return m_iRoutineOutLine;
}

int GateData::GetRoutinToRunway()
{
	return m_iRoutineToRunway;
}

void GateData::ReadFromBuffer( const char* pBuffer, int &iOffSize )
{
	const char* pTemp = pBuffer;
	memcpy(&m_iGateID, pTemp, sizeof(m_iGateID));
	pTemp += sizeof(m_iGateID);
	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);
	m_szGateDataName.assign(pTemp);
	pTemp += m_szGateDataName.size() + 1;
	memcpy(&m_iRoadID, pTemp, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);
	memcpy(&m_iInGateDataFixpointID, pTemp, sizeof(m_iInGateDataFixpointID));
	pTemp += sizeof(m_iInGateDataFixpointID);
	memcpy(&m_iGateFixpointID, pTemp, sizeof(m_iGateFixpointID));
	pTemp += sizeof(m_iGateFixpointID);
	memcpy(&m_dLength, pTemp, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);
	memcpy(&m_iMaxAircraftID, pTemp, sizeof(m_iMaxAircraftID));
	pTemp += sizeof(m_iMaxAircraftID);
	memcpy(&m_iInternationalType, pTemp, sizeof(m_iInternationalType));
	pTemp += sizeof(m_iInternationalType);
	memcpy(&m_iBelongedCompanyID, pTemp, sizeof(m_iBelongedCompanyID));
	pTemp += sizeof(m_iBelongedCompanyID);
	memcpy(&m_iStartPosition, pTemp, sizeof(m_iStartPosition));
	pTemp += sizeof(m_iStartPosition);
	memcpy(&m_bIsDirectTax, pTemp, sizeof(m_bIsDirectTax));
	pTemp += sizeof(m_bIsDirectTax);
	memcpy(&m_iRoutineInLine, pTemp, sizeof(m_iRoutineInLine));
	pTemp += sizeof(m_iRoutineInLine);
	memcpy(&m_iRoutineOutLine, pTemp, sizeof(m_iRoutineOutLine));
	pTemp += sizeof(m_iRoutineOutLine);
	memcpy(&m_iRoutineToRunway, pTemp, sizeof(m_iRoutineToRunway));
	pTemp += sizeof(m_iRoutineToRunway);

	iOffSize = pTemp - pBuffer;
}

void GateData::WriteToBuffer( char* pBuffer, int &iOffSize )
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iGateID, sizeof(m_iGateID));
	pTemp += sizeof(m_iGateID);
	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);
	memcpy(pTemp, m_szGateDataName.c_str(), m_szGateDataName.size() + 1);
	pTemp += m_szGateDataName.size() + 1;
	memcpy(pTemp, &m_iRoadID, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);
	memcpy(pTemp, &m_iInGateDataFixpointID, sizeof(m_iInGateDataFixpointID));
	pTemp += sizeof(m_iInGateDataFixpointID);
	memcpy(pTemp, &m_iGateFixpointID, sizeof(m_iGateFixpointID));
	pTemp += sizeof(m_iGateFixpointID);
	memcpy(pTemp, &m_dLength, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);
	memcpy(pTemp, &m_iMaxAircraftID, sizeof(m_iMaxAircraftID));
	pTemp += sizeof(m_iMaxAircraftID);
	memcpy(pTemp, &m_iInternationalType, sizeof(m_iInternationalType));
	pTemp += sizeof(m_iInternationalType);
	memcpy(pTemp, &m_iBelongedCompanyID, sizeof(m_iBelongedCompanyID));
	pTemp += sizeof(m_iBelongedCompanyID);
	memcpy(pTemp, &m_iStartPosition, sizeof(m_iStartPosition));
	pTemp += sizeof(m_iStartPosition);
	memcpy(pTemp, &m_bIsDirectTax, sizeof(m_bIsDirectTax));
	pTemp += sizeof(m_bIsDirectTax);
	memcpy(pTemp, &m_iRoutineInLine, sizeof(m_iRoutineInLine));
	pTemp += sizeof(m_iRoutineInLine);
	memcpy(pTemp, &m_iRoutineOutLine, sizeof(m_iRoutineOutLine));
	pTemp += sizeof(m_iRoutineOutLine);
	memcpy(pTemp, &m_iRoutineToRunway, sizeof(m_iRoutineToRunway));
	pTemp += sizeof(m_iRoutineToRunway);

	iOffSize = pTemp - pBuffer;
}

int GateData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iGateID);
	iSize += sizeof(m_iAirportID);
	iSize += m_szGateDataName.size() + 1;
	iSize += sizeof(m_iRoadID);
	iSize += sizeof(m_iInGateDataFixpointID);
	iSize += sizeof(m_iGateFixpointID);
	iSize += sizeof(m_dLength);
	iSize += sizeof(m_iMaxAircraftID);
	iSize += sizeof(m_iInternationalType);
	iSize += sizeof(m_iBelongedCompanyID);
	iSize += sizeof(m_iStartPosition);
	iSize += sizeof(m_bIsDirectTax);
	iSize += sizeof(m_iRoutineInLine);
	iSize += sizeof(m_iRoutineToRunway);
	return iSize;
}


/*-----------------跑道进入道--------------*/
InRunwayLineData::InRunwayLineData(void)
{
	m_iInRunwayLineID = 0;
	m_iRunwayID = 0;
	m_szInRunwayLineName = "进入道名称";
	m_iSequence = 0;
	m_iRoadID = 0;
	m_iInPointID = 0;
	m_iStartPointID = 0;
	m_iWaitingPointID = 0;
}

InRunwayLineData::~InRunwayLineData(void)
{
}

//跑道进入道————拷贝、赋值函数
InRunwayLineData::InRunwayLineData(const InRunwayLineData& inRunwayLine)
{
	if (this == &inRunwayLine)
	{
		return;
	}

	*this = inRunwayLine;
}

InRunwayLineData& InRunwayLineData::operator=(const InRunwayLineData& inRunwayLine)
{
	if (this == &inRunwayLine)
	{
		return *this;
	}
	this->m_iInRunwayLineID = inRunwayLine.m_iInRunwayLineID;
	this->m_iRunwayID =inRunwayLine.m_iRunwayID;
	this->m_szInRunwayLineName = inRunwayLine.m_szInRunwayLineName;
	this->m_iSequence = inRunwayLine.m_iSequence;
	this->m_iRoadID = inRunwayLine.m_iRoadID;
	this->m_iInPointID = inRunwayLine.m_iInPointID;
	this->m_iStartPointID = inRunwayLine.m_iStartPointID;
	this->m_iWaitingPointID = inRunwayLine.m_iWaitingPointID;

	return *this;
}

int InRunwayLineData::GetId()
{
	return m_iInRunwayLineID;
}

void InRunwayLineData::Copy(boost::shared_ptr<InRunwayLineData> spInRunwayLineData)
{

}

std::string InRunwayLineData::GetDisplayLabel()
{
	return m_szInRunwayLineName;
}

//跑道进入道————Set 方法
void InRunwayLineData::SetInRunwayLineID(int iID)
{
	m_iInRunwayLineID = iID;
}

void InRunwayLineData::SetInRunwayLineName(string szName)
{
	m_szInRunwayLineName = szName;
}

void InRunwayLineData::SetRunwayID(int iRunwayID)
{
	m_iRunwayID = iRunwayID;
}

void InRunwayLineData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}

void InRunwayLineData::SetSequence(int iSequence)
{
	m_iSequence = iSequence;
}

void InRunwayLineData::SetRoadID(int iRoadID)
{
	m_iRoadID = iRoadID;
}

void InRunwayLineData::SetInPointID(int iInPointID)
{
	m_iInPointID = iInPointID;
}

void InRunwayLineData::SetStartPointID(int iStartPointID)
{
	m_iStartPointID = iStartPointID;
}

void InRunwayLineData::SetWaitingPointID(int iWaitingPointID)
{
	m_iWaitingPointID = iWaitingPointID;
}

//跑道进入道————Get 方法
int InRunwayLineData::GetInRunwayLineID()
{
	return m_iInRunwayLineID;
}
string InRunwayLineData::GetInRunwayLineName()
{
	return m_szInRunwayLineName;
}

int InRunwayLineData::GetRunwayID()
{
	return m_iRunwayID;
}

int InRunwayLineData::GetAirportID()
{
	return m_iAirportID;
}

int InRunwayLineData::GetSequence()
{
	return m_iSequence;
}

int InRunwayLineData::GetRoadID()
{
	return m_iRoadID;
}

int InRunwayLineData::GetInPointID()
{
	return m_iInPointID;
}

int InRunwayLineData::GetStartPointID()
{
	return m_iStartPointID;
}

int InRunwayLineData::GetWaitingPointID()
{
	return m_iWaitingPointID;
}


//跑道进入道————序列化 方法
void InRunwayLineData::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iRunwayID, pTemp, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	m_szInRunwayLineName.assign(pTemp);
	pTemp += m_szInRunwayLineName.size() + 1;

	memcpy(&m_iSequence, pTemp, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(&m_iRoadID, pTemp, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(&m_iInPointID, pTemp, sizeof(m_iInPointID));
	pTemp += sizeof(m_iInPointID);

	memcpy(&m_iStartPointID, pTemp, sizeof(m_iStartPointID));
	pTemp += sizeof(m_iStartPointID);

	memcpy(&m_iWaitingPointID, pTemp, sizeof(m_iWaitingPointID));
	pTemp += sizeof(m_iWaitingPointID);

	iOffSize = pTemp - pBuffer;
}

void InRunwayLineData::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iRunwayID, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);


	memcpy(pTemp, m_szInRunwayLineName.c_str(), m_szInRunwayLineName.size() + 1);
	pTemp += m_szInRunwayLineName.size() + 1;

	memcpy(pTemp, &m_iSequence, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(pTemp, &m_iRoadID, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(pTemp, &m_iInPointID, sizeof(m_iInPointID));
	pTemp += sizeof(m_iInPointID);

	memcpy(pTemp, &m_iStartPointID, sizeof(m_iStartPointID));
	pTemp += sizeof(m_iStartPointID);

	memcpy(pTemp, &m_iWaitingPointID, sizeof(m_iWaitingPointID));
	pTemp += sizeof(m_iWaitingPointID);

	iOffSize = pTemp - pBuffer;
}

int InRunwayLineData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iRunwayID);
	iSize += sizeof(m_iAirportID);
	iSize += m_szInRunwayLineName.size() + 1;
	iSize += sizeof(m_iSequence);
	iSize += sizeof(m_iRoadID);
	iSize += sizeof(m_iInPointID);
	iSize += sizeof(m_iStartPointID);
	iSize += sizeof(m_iWaitingPointID);

	return iSize;
}

/*-----------------跑道脱离道--------------*/
VacateLineData::VacateLineData(void)
{
	m_iVacateLineID = 0;
	m_szVacateLineName = "脱离道名称";
	m_iSequence = 0;
	m_iRunwayID = 0;			
	m_iRoadID = 0;				
	m_iStartPointID = 0;	
	m_iWaitingPointID = 0;
}

VacateLineData::~VacateLineData(void)
{
}

//跑道脱离道————拷贝、赋值函数
VacateLineData::VacateLineData(const VacateLineData& vacateline)
{
	if (this == &vacateline)
	{
		return;
	}

	*this = vacateline;
}

VacateLineData& VacateLineData::operator=(const VacateLineData& vacateline)
{
	if (this == &vacateline)
	{
		return *this;
	}

	this->m_iVacateLineID = vacateline.m_iVacateLineID;
	this->m_iAirportID = vacateline.m_iAirportID;
	this->m_szVacateLineName = vacateline.m_szVacateLineName;
	this->m_iSequence = vacateline.m_iSequence;
	this->m_iRunwayID = vacateline.m_iRunwayID;
	this->m_iRoadID   = vacateline.m_iRoadID;
	this->m_iStartPointID = vacateline.m_iStartPointID;
	this->m_iWaitingPointID = vacateline.m_iWaitingPointID;

	return *this;
}

int VacateLineData::GetId()
{
	return this->m_iVacateLineID;
}

std::string VacateLineData::GetDisplayLabel()
{
	return this->m_szVacateLineName;
}

//跑道脱离道————Set 方法
void VacateLineData::SetVacateLineID( int iVacateLineID )
{
	m_iVacateLineID = iVacateLineID;
}

void VacateLineData::SetAirportID( int iAirportID )
{
	m_iAirportID = iAirportID;
}

void VacateLineData::SetVacateLineName(string szName)
{
	m_szVacateLineName = szName;
}

void VacateLineData::SetSequence(int iSequence)
{
	m_iSequence = iSequence;
}

void VacateLineData::SetRunwayID(int iRunwayID)
{
	m_iRunwayID = iRunwayID;
}

void VacateLineData::SetRoadID(int iRoadID)
{
	m_iRoadID = iRoadID;
}

void VacateLineData::SetStartPointID(int iStartPointID)
{
	m_iStartPointID = iStartPointID;
}

void VacateLineData::SetWaitingPointID(int iWaitingPointID)
{
	m_iWaitingPointID = iWaitingPointID;
}

//跑道脱离道————Get 方法
int VacateLineData::GetVacateLineID()
{
	return m_iVacateLineID;
}

int VacateLineData::GetAirportID()
{
	return m_iAirportID;
}

string VacateLineData::GetVacateLineName()
{
	return m_szVacateLineName;
}

int VacateLineData::GetSequence()
{
	return m_iSequence;		
}

int VacateLineData::GetRunwayID()
{
	return m_iRunwayID;	
}

int VacateLineData::GetRoadID()
{
	return m_iRoadID;
}

int VacateLineData::GetStartPointID()
{
	return m_iStartPointID;
}

int VacateLineData::GetWaitingPointID()
{
	return m_iWaitingPointID;
}

//跑道脱离道————序列化 方法
void VacateLineData::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;

	memcpy(&m_iVacateLineID, pTemp, sizeof(m_iVacateLineID));
	pTemp += sizeof(m_iVacateLineID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	m_szVacateLineName.assign(pTemp);
	pTemp += m_szVacateLineName.size() + 1;

	memcpy(&m_iSequence, pTemp, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(&m_iRunwayID, pTemp, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(&m_iRoadID, pTemp, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(&m_iStartPointID, pTemp, sizeof(m_iStartPointID));
	pTemp += sizeof(m_iStartPointID);

	memcpy(&m_iWaitingPointID, pTemp, sizeof(m_iWaitingPointID));
	pTemp += sizeof(m_iWaitingPointID);

	iOffSize = pTemp - pBuffer;
}

void VacateLineData::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iVacateLineID, sizeof(m_iVacateLineID));
	pTemp += sizeof(m_iVacateLineID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, m_szVacateLineName.c_str(), m_szVacateLineName.size() + 1);
	pTemp += m_szVacateLineName.size() + 1;

	memcpy(pTemp, &m_iSequence, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	memcpy(pTemp, &m_iRunwayID, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(pTemp, &m_iRoadID, sizeof(m_iRoadID));
	pTemp += sizeof(m_iRoadID);

	memcpy(pTemp, &m_iStartPointID, sizeof(m_iStartPointID));
	pTemp += sizeof(m_iStartPointID);

	memcpy(pTemp, &m_iWaitingPointID, sizeof(m_iWaitingPointID));
	pTemp += sizeof(m_iWaitingPointID);

	iOffSize = pTemp - pBuffer;
}

int VacateLineData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iVacateLineID);
	iSize += sizeof(m_iAirportID);
	iSize += m_szVacateLineName.size() + 1;
	iSize += sizeof(m_iSequence);
	iSize += sizeof(m_iRunwayID);
	iSize += sizeof(m_iRoadID);
	iSize += sizeof(m_iStartPointID);
	iSize += sizeof(m_iWaitingPointID);

	return iSize;
}


/*-----------------跑道--------------*/
RunwayData::RunwayData(void)
{
	m_iRunwayID = 0;			
	m_iAirportID = 0;	
	m_szRunwayName = "跑道";	
	m_dCenterPointLongitude = 0;	
	m_dCenterPointLatitude = 0;	
	m_dLength = 0;				
	m_dWidth = 0;		
	m_dHeading = 0;	
	m_dDryFrictionfactor = 0;
	m_dDryFrictionfactor_start = 0;	
	m_dDryFrictionfactor_mid = 0;	
	m_dDryFrictionfactor_end = 0;	
	m_dGradient = 0;	

	m_dStartX = 0;	
	m_dStartY = 0;	
	m_dEndX = 0;		
	m_dEndY = 0;	
	m_dLandingPoint = 0;
}

RunwayData::~RunwayData(void)
{
}
int RunwayData::GetId()
{
	return m_iRunwayID;
}

int RunwayData::GetOwnerId()
{
	return m_iAirportID;
}

std::string RunwayData::GetDisplayLabel()
{
	return m_szRunwayName;
}

RunwayData& RunwayData::operator=( const RunwayData& runway )
{
	if(this == &runway)
	{
		return *this;
	}
	this->m_iRunwayID = runway.m_iRunwayID;
	this->m_iAirportID = runway.m_iAirportID;
	this->m_szRunwayName = runway.m_szRunwayName;
	this->m_dCenterPointLongitude = runway.m_dCenterPointLongitude;
	this->m_dCenterPointLatitude = runway.m_dCenterPointLatitude;
	this->m_dLength = runway.m_dLength;
	this->m_dWidth = runway.m_dWidth;
	this->m_dHeading = runway.m_dHeading;
	this->m_dDryFrictionfactor = runway.m_dDryFrictionfactor;
	this->m_dDryFrictionfactor_start = runway.m_dDryFrictionfactor_start;
	this->m_dDryFrictionfactor_mid = runway.m_dDryFrictionfactor_mid;
	this->m_dDryFrictionfactor_end = runway.m_dDryFrictionfactor_end;
	this->m_dGradient = runway.m_dGradient;
	this->m_dStartX = runway.m_dStartX;
	this->m_dStartY = runway.m_dStartY;
	this->m_dEndX = runway.m_dEndX;
	this->m_dEndY = runway.m_dEndY;
	this->m_dHeight = runway.m_dHeight;
	this->m_dMegaticDiff = runway.m_dMegaticDiff;
	this->m_dLandingPoint = runway.m_dLandingPoint;
	
	//进入道
	for(unsigned int i = 0; i < runway.m_vInRunwayLine.size(); i++)
	{
		boost::shared_ptr<InRunwayLineData> newInRunwayLine = boost::make_shared<InRunwayLineData>();
		*newInRunwayLine = *(runway.m_vInRunwayLine.at(i));
		this->m_vInRunwayLine.push_back(newInRunwayLine);
	}
	//脱离道
	for(unsigned int i = 0; i < runway.m_vVacateLine.size(); i++)
	{
		boost::shared_ptr<VacateLineData> newVacateLine = boost::make_shared<VacateLineData>();
		*newVacateLine = *(runway.m_vVacateLine.at(i));
		this->m_vVacateLine.push_back(newVacateLine);
	}
	return *this;
}

void RunwayData::Copy(boost::shared_ptr<RunwayData> spRunway)
{

}

void RunwayData::SetRunWayID(int iRunwayID)
{
	m_iRunwayID = iRunwayID;
}

void RunwayData::SetAirportID(int iAirportID)
{
	m_iAirportID = iAirportID;
}

void RunwayData::SetRunwayName(string szRunwayName)
{
	m_szRunwayName = szRunwayName;
}

void RunwayData::SetWidth( double dWidth )
{
	m_dWidth = dWidth;
}

void RunwayData::SetCenterPointLongitude(double dCenterPointLongitude)
{
	m_dCenterPointLongitude = dCenterPointLongitude;
}

void RunwayData::SetCenterPointLatitude(double dCenterPointLatitude)
{
	m_dCenterPointLatitude = dCenterPointLatitude;
}

void RunwayData::SetLength(double dLength)
{
	m_dLength = dLength;
}

void RunwayData::SetHeading(double dHeading)
{
	m_dHeading = dHeading;
}

void RunwayData::SetDryFrictionfactor(double dDryFrictionfactor)
{
	m_dDryFrictionfactor = dDryFrictionfactor;
}

void RunwayData::SetDryFrictionfactor_start(double dDryFrictionfactor_start)
{
	m_dDryFrictionfactor_start = dDryFrictionfactor_start;
}

void RunwayData::SetDryFrictionfactor_mid(double dDryFrictionfactor_mid)
{
	m_dDryFrictionfactor_mid = dDryFrictionfactor_mid;
}

void RunwayData::SetDryFrictionfactor_end(double dDryFrictionfactor_end)
{
	m_dDryFrictionfactor_end = dDryFrictionfactor_end;
}

void RunwayData::SetGradient( double dGradient )
{
	m_dGradient = dGradient;
}

void RunwayData::SetStartX(double dStartX)
{
	m_dStartX = dStartX;
}

void RunwayData::SetStartY(double dStartY)
{
	m_dStartY = dStartY;
}

void RunwayData::SetEndX(double dEndX)
{
	m_dEndX = dEndX;
}

void RunwayData::SetEndY(double dEndY)
{
	m_dEndY = dEndY;
}

void RunwayData::SetHeight(double dHeight)
{
	m_dHeight = dHeight;
}

void RunwayData::SetMegaticDiff(double dGradient)
{
	m_dMegaticDiff = dGradient;
}

void RunwayData::SetLandingPoint(double dLandingPoint)
{
	m_dLandingPoint = dLandingPoint;
}

void RunwayData::SetInRunwayLines( vector<boost::shared_ptr<InRunwayLineData> >& vInRunwayLine )
{
	m_vInRunwayLine.clear();
	m_vInRunwayLine = vInRunwayLine;
}

void RunwayData::SetVacateLines( vector<boost::shared_ptr<VacateLineData> >& vVacateLine )
{
	m_vVacateLine.clear();
	m_vVacateLine = vVacateLine;
}

int RunwayData::GetRunWayID()
{
	return m_iRunwayID;
}

int RunwayData::GetAirportID()
{
	return m_iAirportID;
}

std::string RunwayData::GetRunwayName()
{
	return m_szRunwayName;
}

double RunwayData::GetWidth()
{
	return m_dWidth;
}

double RunwayData::GetCenterPointLongitude()
{
	return m_dCenterPointLongitude;
}

double RunwayData::GetCenterPointLatitude()
{
	return m_dCenterPointLatitude;
}

double RunwayData::GetLength()
{
	return m_dLength;
}

double RunwayData::GetHeading()
{
	return m_dHeading;
}

double RunwayData::GetDryFrictionfactor()
{
	return m_dDryFrictionfactor;
}

double RunwayData::GetDryFrictionfactor_start()
{
	return m_dDryFrictionfactor_start;
}

double RunwayData::GetDryFrictionfactor_mid()
{
	return m_dDryFrictionfactor_mid;
}

double RunwayData::GetDryFrictionfactor_end()
{
	return m_dDryFrictionfactor_end;
}

double RunwayData::GetGradient()
{
	return m_dGradient;
}

double RunwayData::GetStartX()
{
	return m_dStartX;
}

double RunwayData::GetStartY()
{
	return m_dStartY;
}

double RunwayData::GetEndX()
{
	return m_dEndX;
}

double RunwayData::GetEndY()
{
	return m_dEndY;
}

double RunwayData::GetHeight()
{
	return m_dHeight;
}

double RunwayData::GetMegaticDiff()
{
	return m_dMegaticDiff;
}

double RunwayData::GetLandingPoint()
{
	return m_dLandingPoint;
}

vector<boost::shared_ptr<InRunwayLineData> >& RunwayData::GetInRunwayLines()
{
	return m_vInRunwayLine;
}

vector<boost::shared_ptr<VacateLineData> >& RunwayData::GetVacateLines()
{
	return m_vVacateLine;
}

void RunwayData::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iRunwayID, pTemp, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	m_szRunwayName.assign(pTemp);
	pTemp += m_szRunwayName.size() + 1;

	memcpy(&m_dCenterPointLongitude, pTemp, sizeof(m_dCenterPointLongitude));
	pTemp += sizeof(m_dCenterPointLongitude);

	memcpy(&m_dCenterPointLatitude, pTemp, sizeof(m_dCenterPointLatitude));
	pTemp += sizeof(m_dCenterPointLatitude);

	memcpy(&m_dLength, pTemp, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);

	memcpy(&m_dWidth, pTemp, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(&m_dHeading, pTemp, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(&m_dDryFrictionfactor, pTemp, sizeof(m_dDryFrictionfactor));
	pTemp += sizeof(m_dDryFrictionfactor);

	memcpy(&m_dDryFrictionfactor_start, pTemp, sizeof(m_dDryFrictionfactor_start));
	pTemp += sizeof(m_dDryFrictionfactor_start);

	memcpy(&m_dDryFrictionfactor_mid, pTemp, sizeof(m_dDryFrictionfactor_mid));
	pTemp += sizeof(m_dDryFrictionfactor_mid);

	memcpy(&m_dDryFrictionfactor_end, pTemp, sizeof(m_dDryFrictionfactor_end));
	pTemp += sizeof(m_dDryFrictionfactor_end);

	memcpy(&m_dGradient, pTemp, sizeof(m_dGradient));
	pTemp += sizeof(m_dGradient);

	memcpy(&m_dStartX, pTemp, sizeof(m_dStartX));
	pTemp += sizeof(m_dStartX);

	memcpy(&m_dStartY, pTemp, sizeof(m_dStartY));
	pTemp += sizeof(m_dStartY);

	memcpy(&m_dEndX, pTemp, sizeof(m_dEndX));
	pTemp += sizeof(m_dEndX);

	memcpy(&m_dEndY, pTemp, sizeof(m_dEndY));
	pTemp += sizeof(m_dEndY);

	memcpy(&m_dHeight, pTemp, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(&m_dMegaticDiff, pTemp, sizeof(m_dMegaticDiff));
	pTemp += sizeof(m_dMegaticDiff);

	memcpy(&m_dLandingPoint, pTemp, sizeof(m_dLandingPoint));
	pTemp += sizeof(m_dLandingPoint);

	/*int iInRunwayLineCount = 0;
	memcpy(&iInRunwayLineCount, pTemp, sizeof(iInRunwayLineCount));
	pTemp += sizeof(iInRunwayLineCount);


	for(unsigned int i = 0; i < iInRunwayLineCount; i++)
	{
		int iOffSize_inline = 0;
		shared_ptr<InRunwayLineData> spInRunwayLineData = make_shared<InRunwayLineData>();
		spInRunwayLineData->ReadFromBuffer(pTemp, iOffSize_inline);
		m_vInRunwayLine.push_back(spInRunwayLineData);
		pTemp += iOffSize_inline;
	}*/

	/*int iVacateLineCount = 0;
	memcpy(&iVacateLineCount, pTemp, sizeof(iVacateLineCount));
	pTemp += sizeof(iVacateLineCount);

	for(unsigned int i = 0; i < iVacateLineCount; i++)
	{
		int iOffSize_inline = 0;
		shared_ptr<VacateLineData> spVacateLine = make_shared<VacateLineData>();
		spVacateLine->ReadFromBuffer(pTemp,iOffSize_inline);
		m_vVacateLine.push_back(spVacateLine);
		pTemp += iOffSize_inline;
	}*/

	iOffSize = pTemp - pBuffer;
}

void RunwayData::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iRunwayID, sizeof(m_iRunwayID));
	pTemp += sizeof(m_iRunwayID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, m_szRunwayName.c_str(), m_szRunwayName.size() + 1);
	pTemp += m_szRunwayName.size() + 1;

	memcpy(pTemp, &m_dCenterPointLongitude, sizeof(m_dCenterPointLongitude));
	pTemp += sizeof(m_dCenterPointLongitude);

	memcpy(pTemp, &m_dCenterPointLatitude, sizeof(m_dCenterPointLatitude));
	pTemp += sizeof(m_dCenterPointLatitude);

	memcpy(pTemp, &m_dLength, sizeof(m_dLength));
	pTemp += sizeof(m_dLength);

	memcpy(pTemp, &m_dWidth, sizeof(m_dWidth));
	pTemp += sizeof(m_dWidth);

	memcpy(pTemp, &m_dHeading, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(pTemp, &m_dDryFrictionfactor, sizeof(m_dDryFrictionfactor));
	pTemp += sizeof(m_dDryFrictionfactor);

	memcpy(pTemp, &m_dDryFrictionfactor_start, sizeof(m_dDryFrictionfactor_start));
	pTemp += sizeof(m_dDryFrictionfactor_start);

	memcpy(pTemp, &m_dDryFrictionfactor_mid, sizeof(m_dDryFrictionfactor_mid));
	pTemp += sizeof(m_dDryFrictionfactor_mid);

	memcpy(pTemp, &m_dDryFrictionfactor_end, sizeof(m_dDryFrictionfactor_end));
	pTemp += sizeof(m_dDryFrictionfactor_end);

	memcpy(pTemp, &m_dGradient, sizeof(m_dGradient));
	pTemp += sizeof(m_dGradient);

	memcpy(pTemp, &m_dStartX, sizeof(m_dStartX));
	pTemp += sizeof(m_dStartX);

	memcpy(pTemp, &m_dStartY, sizeof(m_dStartY));
	pTemp += sizeof(m_dStartY);

	memcpy(pTemp, &m_dEndX, sizeof(m_dEndX));
	pTemp += sizeof(m_dEndX);

	memcpy(pTemp, &m_dEndY, sizeof(m_dEndY));
	pTemp += sizeof(m_dEndY);

	memcpy(pTemp, &m_dHeight, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(pTemp, &m_dMegaticDiff, sizeof(m_dMegaticDiff));
	pTemp += sizeof(m_dMegaticDiff);

	memcpy(pTemp, &m_dLandingPoint, sizeof(m_dLandingPoint));
	pTemp += sizeof(m_dLandingPoint);

	iOffSize = pTemp - pBuffer;
}

int RunwayData::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iRunwayID);
	iSize += sizeof(m_iAirportID);
	iSize += m_szRunwayName.size()+ 1;
	iSize += sizeof(m_dCenterPointLongitude);
	iSize += sizeof(m_dCenterPointLatitude);
	iSize += sizeof(m_dLength);
	iSize += sizeof(m_dWidth);
	iSize += sizeof(m_dHeading);
	iSize += sizeof(m_dDryFrictionfactor);
	iSize += sizeof(m_dDryFrictionfactor_start);
	iSize += sizeof(m_dDryFrictionfactor_mid);
	iSize += sizeof(m_dDryFrictionfactor_end);
	iSize += sizeof(m_dGradient);
	iSize += sizeof(m_dStartX);
	iSize += sizeof(m_dStartY);
	iSize += sizeof(m_dEndX);
	iSize += sizeof(m_dEndY);
	iSize += sizeof(m_dHeight);
	iSize += sizeof(m_dMegaticDiff);
	iSize += sizeof(m_dLandingPoint);
	return iSize;
}


/*-------------------塔台-------------------*/
Tower::Tower(void)
{
	m_iTowerID = 0;
	m_iAirportID = 0;
	m_iIconID = 0;		
	m_strTowerName = "";	
	m_dLongitude = 0;		
	m_dLatitude = 0;		
	m_dHeight= 0;			
	m_dHeading = 0;		
	m_dPitch = 0;			
	m_dRoll = 0;			
}

Tower::~Tower(void)
{
}

int Tower::GetId()
{
	return m_iTowerID;
}

int Tower::GetOwnerId()
{
	return m_iAirportID;
}

std::string Tower::GetDisplayLabel()
{
	return m_strTowerName;
}

/*****************Set方法****************/
void Tower::SetTowerID( int iTowerID )
{
	m_iTowerID = iTowerID;
}

void Tower::SetAirportID( int iAirportID )
{
	m_iAirportID = iAirportID;
}

void Tower::SetIconID( int iIconID )
{
	m_iIconID = iIconID;
}

void Tower::SetTowerName( string strTowerName )
{
	m_strTowerName = strTowerName;
}

void Tower::SetLongitude( double dLongitude )
{
	m_dLongitude = dLongitude;
}

void Tower::SetHeight( double dHeight )
{
	m_dHeight = dHeight;
}

void Tower::SetHeading( double dHeading )
{
	m_dHeading = dHeading;
}

void Tower::SetPitch( double dPitch )
{
	m_dPitch = dPitch;
}

void Tower::SetRoll( double dRoll )
{
	m_dRoll = dRoll;
}

void Tower::SetLatitude( double dLatitude )
{
	m_dLatitude = dLatitude;

}

/************  Get方法*********************/
int Tower::GetTowerID()
{
	return m_iTowerID;
}

int Tower::GetAirportID()
{
	return m_iAirportID;
}

int Tower::GetIconID()
{
	return m_iIconID;
}

std::string Tower::GetTowerName()
{
	return m_strTowerName;
}

double Tower::GetLongitude()
{
	return m_dLongitude;
}

double Tower::GetHeight()
{
	return m_dHeight;
}

double Tower::GetHeading()
{
	return m_dHeading;
}

double Tower::GetPitch()
{
	return m_dPitch;
}

double Tower::GetRoll()
{
	return m_dRoll;
}


double Tower::GetLatitude()
{
	return m_dLatitude;
}

void Tower::ReadFromBuffer( const char* pBuffer, int &iOffSize )
{
	const char* pTemp = pBuffer;
	memcpy(&m_iTowerID, pTemp, sizeof(m_iTowerID));
	pTemp += sizeof(m_iTowerID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(&m_iIconID, pTemp, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	m_strTowerName.assign(pTemp);
	pTemp += m_strTowerName.size() + 1;

	memcpy(&m_dLongitude, pTemp, sizeof(m_dLongitude));
	pTemp += sizeof(m_dLongitude);

	memcpy(&m_dLatitude, pTemp, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(&m_dHeight, pTemp, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(&m_dHeading, pTemp, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(&m_dPitch, pTemp, sizeof(m_dPitch));
	pTemp += sizeof(m_dPitch);

	memcpy(&m_dRoll, pTemp, sizeof(m_dRoll));
	pTemp += sizeof(m_dRoll);

	iOffSize = pTemp - pBuffer;
}

void Tower::WriteToBuffer( char* pBuffer, int &iOffSize )
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iTowerID, sizeof(m_iTowerID));
	pTemp += sizeof(m_iTowerID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, &m_iIconID, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	memcpy(pTemp, m_strTowerName.c_str(), m_strTowerName.size() + 1);
	pTemp += m_strTowerName.size() + 1;

	memcpy(pTemp, &m_dLongitude, sizeof(m_dLongitude));
	pTemp += sizeof(m_dLongitude);

	memcpy(pTemp, &m_dLatitude, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(pTemp, &m_dHeight, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(pTemp, &m_dHeading, sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);

	memcpy(pTemp, &m_dPitch, sizeof(m_dPitch));
	pTemp += sizeof(m_dPitch);

	memcpy(pTemp, &m_dRoll, sizeof(m_dRoll));
	pTemp += sizeof(m_dRoll);

	iOffSize = pTemp - pBuffer;
}

int Tower::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iTowerID);
	iSize += sizeof(m_iAirportID);
	iSize += sizeof(m_iIconID);
	iSize += m_strTowerName.size() + 1;
	iSize += sizeof(m_dLongitude);
	iSize += sizeof(m_dLatitude);
	iSize += sizeof(m_dHeight);
	iSize += sizeof(m_dHeading);
	iSize += sizeof(m_dPitch);
	iSize += sizeof(m_dRoll);
	return iSize;
}


/*-------------机场模型-----------------*/
AirportModel::AirportModel(void)
{
	m_iModelID = 0;	
	m_iAirportID = 0;		
	m_strModelName = "机场模型";
	m_strModelFile = "机场模型文件名";
}

AirportModel::~AirportModel(void)
{
}

int AirportModel::GetId()
{
	return m_iModelID;
}

int AirportModel::GetOwnerId()
{
	return m_iAirportID;
}

std::string AirportModel::GetDisplayLabel()
{
	return m_strModelName;
}

void AirportModel::SetModelID( int iModelID )
{
	m_iModelID = iModelID;
}

void AirportModel::SetAirportID( int iAirportID )
{
	m_iAirportID = iAirportID;
}

void AirportModel::SetModelName( string strModelName )
{
	m_strModelName = strModelName;
}

void AirportModel::SetModelFile( string strModelFile )
{
	m_strModelFile = strModelFile;
}

int AirportModel::GetModelID()
{
	return m_iModelID;
}

int AirportModel::GetAirportID()
{
	return m_iAirportID;
}

std::string AirportModel::GetModelName()
{
	return m_strModelName;
}

std::string AirportModel::GetModelFile()
{
	return m_strModelFile;
}

void AirportModel::ReadFromBuffer( const char* pBuffer, int &iOffSize )
{
	const char* pTemp = pBuffer;
	memcpy(&m_iModelID, pTemp, sizeof(m_iModelID));
	pTemp += sizeof(m_iModelID);

	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	m_strModelName.assign(pTemp);
	pTemp += m_strModelName.size() + 1;

	m_strModelFile.assign(pTemp);
	pTemp += m_strModelFile.size() + 1;

	iOffSize = pTemp - pBuffer;
}

void AirportModel::WriteToBuffer( char* pBuffer, int &iOffSize )
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iModelID, sizeof(m_iModelID));
	pTemp += sizeof(m_iModelID);

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, m_strModelName.c_str(), m_strModelName.size() + 1);
	pTemp += m_strModelName.size() + 1;

	memcpy(pTemp, m_strModelFile.c_str(), m_strModelFile.size() + 1);
	pTemp += m_strModelFile.size() + 1;

	iOffSize = pTemp - pBuffer;
}

int AirportModel::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iModelID);
	iSize += sizeof(m_iAirportID);
	iSize += m_strModelName.size() + 1;
	iSize += m_strModelFile.size() + 1;
	return iSize;
}


/*----------------------离场程序-----------------------*/
Sid::Sid()
{
	m_iSidId = 0;
	m_strSidName = "离场程序";
	m_iAirportID = 0;
	m_iRunwayID = 0;
	m_vecRoutePt.clear();
}

Sid::~Sid()
{

}

//
int Sid::GetId()
{
	return m_iSidId;
}

int Sid::GetOwnerId()
{
	return m_iAirportID;
}

string Sid::GetDisplayLabel()
{
	return m_strSidName;
}

//拷贝、赋值函数
Sid::Sid(const Sid &sid)
{
	if(this == &sid) return;

	*this = sid;
}

Sid& Sid::operator=(const Sid& sid)
{
	if (this == &sid) return *this;

	this->m_iSidId = sid.m_iSidId;
	this->m_strSidName = sid.m_strSidName;
	this->m_iAirportID = sid.m_iAirportID;
	this->m_iRunwayID = sid.m_iRunwayID;
	this->m_vecRoutePt = sid.m_vecRoutePt;

	return *this;
}


/*----------------------进场程序-----------------------*/
Star::Star()
{
	m_iStarId = 0;
	m_strStarName = "离场程序";
	m_iAirportID  = 0;
	m_iRunwayID = 0;
	m_vecRoutePt.clear();
}
Star::~Star()
{

}

//
int Star::GetId()
{
	return m_iStarId;
}
int Star::GetOwnerId()
{
	return m_iAirportID;
}
string Star::GetDisplayLabel()
{
	return m_strStarName;
}

//拷贝、赋值函数
Star::Star(const Star &star)
{
	if(this == &star) return;

	*this = star;
}
Star& Star::operator=(const Star& star)
{
	if (this == &star) return *this;

	this->m_iStarId = star.m_iStarId;
	this->m_strStarName = star.m_strStarName;
	this->m_iAirportID  = star.m_iAirportID;
	this->m_iRunwayID = star.m_iRunwayID;
	this->m_vecRoutePt = star.m_vecRoutePt;

	return *this;
}

/*----------------------宏-----------------------*/
Macro::Macro()
{
	m_iMacroID = 0;
	m_iMacroGroupID = 0;		
	m_szMacroName = "宏命令";
	m_szCmd = "";		
	m_szRemark = "";
}

Macro::~Macro()
{

}

int Macro::GetId()
{
	return m_iMacroID;
}

int Macro::GetOwnerId()
{
	return m_iMacroGroupID;
}

string Macro::GetDisplayLabel()
{
	return m_szMacroName;
}

/*----------------------宏组-----------------------*/
MacroGroup::MacroGroup()
{
	m_iMacroGroupID = 0;                 
	m_iAirportID = 0;					 
	m_szMacroGroupName = "宏组";		 
	m_szRemark = "";	
}

MacroGroup::~MacroGroup()
{

}

int MacroGroup::GetId()
{
	return m_iMacroGroupID;
}

int MacroGroup::GetOwnerId()
{
	return m_iAirportID;
}

string MacroGroup::GetDisplayLabel()
{
	return m_szMacroGroupName;
}


/*----------------------进近程序-----------------------*/
int Stdapch::GetId()
{
	return m_iStdapchID;
}

int Stdapch::GetOwnerId()
{
	return m_iAirportID;
}

std::string Stdapch::GetDisplayLabel()
{
	return m_szStdapchName;
}

Stdapch::Stdapch()
{
	m_iStdapchID = 0;	
	m_iAirportID = 0;	
	m_iBeaconID = 0;	
	m_szStdapchName = "进近程序名称";	
	m_iRunwayID = 0;	
	m_eTurnType = STT_LT;	
	m_dInBoundHeading = 0;
	m_eAircraftType = AT_A;
	m_iHighLevel = 0;	
	m_iLowLevel = 0;	
	m_iOutBoundLegTime = 0;
}

Stdapch::~Stdapch()
{

}

/*----------------------等待程序-----------------------*/
Hold::Hold()
{
	m_iHoldID = 0;			
	m_szHoldName = "等待程序";		
	m_iAirportID = 0;		
	m_iBeaconID = 0;			
	m_eTurnType = HTT_LT;		
	m_iAltitudeLevel1 = 0;
	m_iAltitudeLevel2 = 0;	
	m_dHeading = 0;		
	m_iHoldIasAL = 0;		
	m_iHoldIasAM = 0;		
	m_iHoldIasAH = 0;		
	m_iHoldIasBL = 0;		
	m_iHoldIasBM = 0;		
	m_iHoldIasBH = 0;		
	m_iHoldIasCDL = 0;		
	m_iHoldIasCDM = 0;		
	m_iHoldIasCDH = 0;		
	m_iOutBoundLegTimeA = 0;	
	m_iOutBoundLegTimeB = 0;	
	m_iOutBoundLegTimeCD = 0;
}

Hold::~Hold()
{

}

int Hold::GetId()
{
	return m_iHoldID;
}

int Hold::GetOwnerId()
{
	return m_iAirportID;
}

string Hold::GetDisplayLabel()
{
	return m_szHoldName;
}

/*----------------------复飞程序-----------------------*/
Miss::Miss()
{
	m_iMissID = 0;			/* 复飞程序ID,主键码*/
	m_iAirportID = 0;		/*机场ID not null default 0*/	
	m_szMissName = "复飞程序";		/* 复飞程序名称varchar(50) */
	m_iBeaconAltitude = 0;	/* 飞机过点高度int default 0 */
	m_iRunwayID = 0;		/*跑道ID */
	m_vecRoutePt.clear();
}
Miss::~Miss()
{

}

//
int Miss::GetId()
{
	return m_iMissID;
}
int Miss::GetOwnerId()
{
	return m_iAirportID;
}
string Miss::GetDisplayLabel()
{
	return m_szMissName;
}

//拷贝、赋值函数
Miss::Miss(const Miss &miss)
{
	if(this == &miss) return;

	*this = miss;
}

Miss& Miss::operator=(const Miss& miss)
{
	if (this == &miss) return *this;

	this->m_iMissID = miss.m_iMissID;
	this->m_iAirportID = miss.m_iAirportID;
	this->m_szMissName = miss.m_szMissName;
	this->m_iBeaconAltitude = miss.m_iBeaconAltitude;
	this->m_iRunwayID = miss.m_iRunwayID;
	this->m_vecRoutePt = miss.m_vecRoutePt;

	return *this;
}

/*----------------------灯光组-----------------------*/
LightGroup::LightGroup()
{
	m_iLightGroupID = 0;											//!<灯光组ID
	m_strLightGroupName = "灯光组";						//!<灯光组名称
	m_strLightGroupNodeName = "灯光组模型节点";	//!<灯光组模型的节点名称
	m_iAirportID = 0;													//!<机场ID
	m_enumType = ELT_NOMAL;								//!<灯光类型
	m_iLightCollectionID = 0;										//!<灯光组所属灯光组组合ID
	m_iGlimmerRate = 0;											//!<障碍灯的闪烁频率，如果是障碍灯此字段有效
	m_iGlimmerTime = 0;											//!<障碍灯亮起时的时长
}

LightGroup::~LightGroup()
{

}

int LightGroup::GetId()
{
	return m_iLightGroupID;
}
int LightGroup::GetOwnerId()
{
	return m_iAirportID;
}
string LightGroup::GetDisplayLabel()
{
	return m_strLightGroupName;
}

/*----------------------灯-----------------------*/
Light::Light()
{
	m_iLightID = 0;				//!<灯的ID
	m_iLightGroupID = 0;	//所属灯光组ID
	m_iAirportID = 0;			//!<机场ID
	m_iSequence = 0;			//灯的点序
	m_dX = 0;						//!<灯的X坐标
	m_dY = 0;						//!<灯的Y坐标
	m_dZ = 0;						//!<灯的Z坐标
	m_dRed = 0;					//!<灯光颜色Red值
	m_dGreen = 0;				//!<灯光颜色Green值
	m_dBlue = 0;				//!<灯光颜色Blue值
	m_dHeading = 0;			//!<水平方向可以看见灯光的角度
	m_dUpPitch = 0;			//!<垂直方向可以看见灯光的上角度
	m_dDownPitch = 0;		//!<垂直方向可以看见灯光的下角度
}

Light::~Light()
{

}

int Light::GetId()
{
	return m_iLightID;
}

int Light::GetOwnerId()
{
	return m_iLightGroupID;
}

string Light::GetDisplayLabel()
{
	return "";
}

/*----------------------灯光组组合-----------------------*/
LightCollection::LightCollection()
{
	m_iLightCollectionID = 0;								//!<灯光组组合编号
	m_iAirportID = 0;											//!<机场ID
	m_szLightCollectionName = "灯光组组合";	//!<灯光组组合名称
	m_vLightGroups.clear();								//!</灯光组组合中的灯光组
}

LightCollection::~LightCollection()
{

}

int LightCollection::GetId()
{
	return m_iLightCollectionID;
}

int LightCollection::GetOwnerId()
{
	return m_iAirportID;
}

string LightCollection::GetDisplayLabel()
{
	return m_szLightCollectionName;
}

/*----------------------灯光组与其对应的灯-----------------------*/
LightGroupDetail::LightGroupDetail()
{
	m_iLightGroupID = 0;		//!<灯光组ID
	m_vLights.clear();				//!<构成灯光组的灯
}

LightGroupDetail::~LightGroupDetail()
{

}

int LightGroupDetail::GetId()
{
	return m_iLightGroupID;
}

int LightGroupDetail::GetOwnerId()
{
	return 0;
}

string LightGroupDetail::GetDisplayLabel()
{
	return "";
}