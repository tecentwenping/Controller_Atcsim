#include "airspace_data_objs.h"


/*---------------导航台------------*/
Beacon::Beacon(void)
{
	m_iBeaconID = 0;
	m_strBeaconCode = "导航台代码";
	m_strBeaconName = "导航台名称";
	m_dLongitude = 0;
	m_dLatitude = 0;
	m_dHeight = 0;
	m_iType = 0;	
	m_iIconID = 0;
	m_bIsStdReport = false;
}

Beacon::~Beacon(void)
{
}

int Beacon::GetId()
{
	return m_iBeaconID;
}

std::string Beacon::GetDisplayLabel()
{
	return m_strBeaconCode;
}

//导航台————Set方法
void Beacon::SetBeaconID( int iBeaconID )
{
	m_iBeaconID = iBeaconID;
}

void Beacon::SetBeaconCode( std::string strCode )
{
	m_strBeaconCode = strCode;
}

void Beacon::SetBeaconName( std::string strBeaconName )
{
	m_strBeaconName = strBeaconName;
}

void Beacon::SetLongitude( double dLongitude )
{
	m_dLongitude = dLongitude;
}

void Beacon::SetLatitude( double dLatitude )
{
	m_dLatitude = dLatitude;
}

void Beacon::SetHeight( double dHeight )
{
	m_dHeight = dHeight;
}

void Beacon::SetType( int iType )
{
	m_iType = iType;
}

void Beacon::SetIconID( int iIconID )
{
	m_iIconID = iIconID;
}

void Beacon::SetIsStdReport( bool bIsStdReport )
{
	m_bIsStdReport = bIsStdReport;
}

//导航台————Get方法
int Beacon::GetBeaconID()
{
	return m_iBeaconID;
}

std::string Beacon::GetBeaconCode()
{
	return m_strBeaconCode;
}

std::string Beacon::GetBeaconName()
{
	return m_strBeaconName;
}	

double Beacon::GetLongitude()
{
	return m_dLongitude;
}

double Beacon::GetLatitude()
{
	return m_dLatitude;
}

double Beacon::GetHeight()
{
	return m_dHeight;
}

int Beacon::GetType()
{
	return m_iType;
}

int Beacon::GetIconID()
{
	return m_iIconID;
}

bool Beacon::GetIsStdReport()
{
	return m_bIsStdReport;
}

//导航台————序列化方法
void Beacon::ReadFromBuffer( const char* pBuffer, int &iOffSize )
{
	const char* pTemp = pBuffer;
	memcpy(&m_iBeaconID, pTemp, sizeof(m_iBeaconID));
	pTemp += sizeof(m_iBeaconID);

	m_strBeaconCode.assign(pTemp);
	pTemp += m_strBeaconCode.size() + 1;

	m_strBeaconName.assign(pTemp);
	pTemp += m_strBeaconName.size() + 1;

	memcpy(&m_dLongitude, pTemp, sizeof(m_dLongitude));
	pTemp += sizeof(m_dLongitude);

	memcpy(&m_dLatitude, pTemp, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(&m_dHeight, pTemp, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(&m_iType, pTemp, sizeof(m_iType));
	pTemp += sizeof(m_iType);

	memcpy(&m_iIconID, pTemp, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	memcpy(&m_bIsStdReport, pTemp, sizeof(m_bIsStdReport));
	pTemp += sizeof(m_bIsStdReport);

	iOffSize = pTemp - pBuffer;
}

void Beacon::WriteToBuffer( char* pBuffer, int &iOffSize )
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iBeaconID, sizeof(m_iBeaconID));
	pTemp += sizeof(m_iBeaconID);

	memcpy(pTemp, m_strBeaconCode.c_str(), m_strBeaconCode.size() + 1);
	pTemp += m_strBeaconCode.size() + 1;

	memcpy(pTemp, m_strBeaconName.c_str(), m_strBeaconName.size() + 1);
	pTemp += m_strBeaconName.size() + 1;

	memcpy(pTemp, &m_dLongitude, sizeof(m_dLongitude));
	pTemp += sizeof(m_dLongitude);

	memcpy(pTemp, &m_dLatitude, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(pTemp, &m_dHeight, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(pTemp, &m_iType, sizeof(m_iType));
	pTemp += sizeof(m_iType);

	memcpy(pTemp, &m_iIconID, sizeof(m_iIconID));
	pTemp += sizeof(m_iIconID);

	memcpy(pTemp, &m_bIsStdReport, sizeof(m_bIsStdReport));
	pTemp += sizeof(m_bIsStdReport);

	iOffSize = pTemp - pBuffer;
}

int Beacon::GetBufferSize()
{
	int iSize = 0;
	iSize += sizeof(m_iBeaconID);
	iSize += m_strBeaconCode.size() + 1;
	iSize += m_strBeaconName.size() + 1;
	iSize += sizeof(m_dLongitude);
	iSize += sizeof(m_dLatitude);
	iSize += sizeof(m_dHeight);
	iSize += sizeof(m_iType);
	iSize += sizeof(m_iIconID);
	iSize += sizeof(m_bIsStdReport);

	return iSize;
}


/*----------------监视传感器（雷达）--------------*/
SurveillanceSensor::SurveillanceSensor(void)
{
	m_iSensorId = 0;
	m_strSensorName = "监视传感器";
	m_eSensorType = SENSOR_NULL;
	m_dLongitude = 0;
	m_dLatitude = 0;
	m_dAltitude = 0;
	m_iPeriod = 0;
	m_iRange = 0;
	m_dElevationAngle = 0;
	m_dDepressionAngle = 0;
}

SurveillanceSensor::~SurveillanceSensor(void)
{
}

int SurveillanceSensor::GetId()
{
	return m_iSensorId;
}
std::string SurveillanceSensor::GetDisplayLabel()
{
	return m_strSensorName;
}


SurveillanceSensor::SurveillanceSensor(const SurveillanceSensor &sensor)
{
	if (this == &sensor)
	{
		return;
	}

	*this = sensor;
}

SurveillanceSensor& SurveillanceSensor::operator=(const SurveillanceSensor& sensor)
{
	if(this == &sensor)
	{
		return *this;
	}

	this->m_iSensorId = sensor.m_iSensorId;
	this->m_strSensorName = sensor.m_strSensorName;
	this->m_eSensorType = sensor.m_eSensorType;
	this->m_dLongitude = sensor.m_dLongitude;
	this->m_dLatitude = sensor.m_dLatitude;
	this->m_dAltitude = sensor.m_dAltitude;
	this->m_iPeriod = sensor.m_iPeriod;
	this->m_iRange = sensor.m_iRange;
	this->m_dElevationAngle = sensor.m_dElevationAngle;
	this->m_dDepressionAngle = sensor.m_dDepressionAngle;
	
	return *this;
}


/*----------------扇区--------------*/
Sector::Sector(void)
{
	m_iSectorID = 0;
	m_strSectorName = "扇区名称";
	m_dFrequency = 0;
}

Sector::~Sector(void)
{
}

int Sector::GetId()
{
	return m_iSectorID;
}
std::string Sector::GetDisplayLabel()
{
	return m_strSectorName;
}

//扇区————拷贝、赋值函数
Sector::Sector(const Sector &sector)
{
	if (this == &sector)
	{
		return;
	}

	*this = sector;
}

Sector& Sector::operator=(const Sector& sector)
{
	if(this == &sector)
	{
		return *this;
	}

	this->m_iSectorID = sector.m_iSectorID;
	this->m_strSectorName = sector.m_strSectorName;
	this->m_dFrequency = sector.m_dFrequency;

	return *this;
}

//扇区————Set 方法

void Sector::SetSectorID(int iSectorID)
{
	m_iSectorID = iSectorID;
}

void Sector::SetSectorName(std::string strSectorName)
{
	m_strSectorName = strSectorName;
}	


void Sector::SetSectorFrequency(double dFrequency)
{
	m_dFrequency = dFrequency;
}

//扇区————Get 方法
int Sector::GetSectorID()
{
	return m_iSectorID;
}

std::string Sector::GetSectorName()
{
	return m_strSectorName;
}


double Sector::GetSectorFrequency()
{
	return m_dFrequency;
}

//扇区————序列化 方法
void Sector::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iSectorID, pTemp, sizeof(m_iSectorID));
	pTemp += sizeof(m_iSectorID);

	m_strSectorName.assign(pTemp);
	pTemp += m_strSectorName.size() + 1;

	memcpy(&m_dFrequency, pTemp, sizeof(m_dFrequency));
	pTemp += sizeof(m_dFrequency);

	iOffSize = pTemp - pBuffer;
}

void Sector::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iSectorID, sizeof(m_iSectorID));
	pTemp += sizeof(m_iSectorID);

	memcpy(pTemp, m_strSectorName.c_str(), m_strSectorName.size() + 1);
	pTemp += m_strSectorName.size() + 1;


	memcpy(pTemp, &m_dFrequency, sizeof(m_dFrequency));
	pTemp += sizeof(m_dFrequency);

	iOffSize = pTemp - pBuffer;
}

int Sector::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iSectorID);
	iSize += m_strSectorName.size() + 1;
	iSize += sizeof(m_dFrequency);

	return iSize;
}


///*--------------------航路上的导航台-------------------*/
//CourseBeacon::CourseBeacon(void)
//{
//
//	m_iCourseID = 0;
//	m_iSequence = 0;
//	m_iBeaconID = 0;
//	m_dAltitude = 0;
//	m_bIsQietai = false;
//}
//
//CourseBeacon::~CourseBeacon(void)
//{
//}
//
////航路上的导航台————拷贝、赋值函数
//CourseBeacon::CourseBeacon(const CourseBeacon& courseBeacon)
//{
//	if (this == &courseBeacon)
//	{
//		return;
//	}
//
//	*this = courseBeacon;
//}
//
//
//CourseBeacon& CourseBeacon::operator=(const CourseBeacon& courseBeacon)
//{
//	if (this == &courseBeacon)
//	{
//		return *this;
//	}
//
//	this->m_iCourseID = courseBeacon.m_iCourseID;
//	this->m_iSequence = courseBeacon.m_iSequence;
//	this->m_iBeaconID = courseBeacon.m_iBeaconID;
//	this->m_dAltitude = courseBeacon.m_dAltitude;
//	this->m_bIsQietai = courseBeacon.m_bIsQietai;
//
//	return *this;
//}
//
//
////航路上的导航台————Set 方法
//void CourseBeacon::SetCourseID(int iCourseID)
//{
//	m_iCourseID = iCourseID;
//}
//
//void CourseBeacon::SetBeaconSequence(int iSeq)
//{
//	m_iSequence = iSeq;
//}
//
//void CourseBeacon::SetBeaconID(int iBeaconID)
//{
//	m_iBeaconID = iBeaconID;
//}
//
//void CourseBeacon::SetAltitude(double dAltitude)
//{
//	m_dAltitude = dAltitude;
//}
//
//void CourseBeacon::SetIsQietai(bool bIsQietai)
//{
//	m_bIsQietai = bIsQietai;
//}
//
////航路上的导航台————Get 方法
//int CourseBeacon::GetCourseID()
//{
//	return m_iCourseID;
//}
//
//int CourseBeacon::GetBeaconSequence()
//{
//	return m_iSequence;
//}
//
//int CourseBeacon::GetBeaconID()
//{
//	return m_iBeaconID;
//}
//
//double CourseBeacon::GetAltitude()
//{
//	return m_dAltitude;
//}
//
//bool CourseBeacon::GetIsQietai()
//{
//	return m_bIsQietai;
//}
//
////航路上的导航台————序列化 方法
//void CourseBeacon::ReadFromBuffer( const char* pBuffer, int &iOffSize)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_iCourseID, pTemp, sizeof(m_iCourseID));
//	pTemp += sizeof(m_iCourseID);
//
//	memcpy(&m_iSequence, pTemp, sizeof(m_iSequence));
//	pTemp += sizeof(m_iSequence);
//
//	memcpy(&m_iBeaconID, pTemp, sizeof(m_iBeaconID));
//	pTemp += sizeof(m_iBeaconID);
//
//	memcpy(&m_dAltitude, pTemp, sizeof(m_dAltitude));
//	pTemp += sizeof(m_dAltitude);
//
//	memcpy(&m_bIsQietai, pTemp, sizeof(m_bIsQietai));
//	pTemp += sizeof(m_bIsQietai);
//
//	iOffSize = pTemp - pBuffer;
//}
//
//void CourseBeacon::WriteToBuffer( char* pBuffer, int &iOffSize)
//{
//	char* pTemp = pBuffer;
//	memcpy(pTemp, &m_iCourseID, sizeof(m_iCourseID));
//	pTemp += sizeof(m_iCourseID);
//
//	memcpy(pTemp, &m_iSequence, sizeof(m_iSequence));
//	pTemp += sizeof(m_iSequence);
//
//	memcpy(pTemp, &m_iBeaconID, sizeof(m_iBeaconID));
//	pTemp += sizeof(m_iBeaconID);
//
//	memcpy(pTemp, &m_dAltitude, sizeof(m_dAltitude));
//	pTemp += sizeof(m_dAltitude);
//
//	memcpy(pTemp, &m_bIsQietai, sizeof(m_bIsQietai));
//	pTemp += sizeof(m_bIsQietai);
//
//	iOffSize = pTemp - pBuffer;
//}
//
//int CourseBeacon::GetBufferSize()
//{
//	int iSize = 0;
//	iSize += sizeof(m_iCourseID);
//	iSize += sizeof(m_iSequence);
//	iSize += sizeof(m_iBeaconID);
//	iSize += sizeof(m_dAltitude);
//	iSize += sizeof(m_bIsQietai);
//
//	return iSize;
//}
//
//
///*--------------------航路-------------------*/
//Course::Course(void)
//{
//	m_iCourseID = 0;
//	m_strCourseName = "航线名称";
//	m_iDepartureAirportID = 0;
//	m_iArrivalAirportID = 0;
//	m_strFlyInfo = "航线信息";
//}
//
//Course::~Course(void)
//{
//}
//
//int Course::GetId()
//{
//	return m_iCourseID;
//}
//
//std::string Course::GetDisplayLabel()
//{
//	return m_strCourseName;
//}
//
////航路————拷贝、赋值函数
//Course::Course(const Course &course)
//{
//	if (this == &course)
//	{
//		return;
//	}
//
//	this->m_iCourseID = course.m_iCourseID;
//	this->m_strCourseName = course.m_strCourseName;
//	this->m_iDepartureAirportID = course.m_iDepartureAirportID;
//	this->m_iDepartureAirportID = course.m_iDepartureAirportID;
//	this->m_strFlyInfo = course.m_strFlyInfo;
//
//	this->m_vecCourseBeacons.clear();
//	for(unsigned int i = 0; i < course.m_vecCourseBeacons.size(); i++)
//	{
//		boost::shared_ptr<CourseBeacon> spData = boost::make_shared<CourseBeacon>();
//		*(spData.get()) = *(course.m_vecCourseBeacons.at(i).get());
//		this->m_vecCourseBeacons.push_back(spData);
//	}
//}
//
//Course& Course::operator=(const Course& course)
//{
//	if(this == &course)
//	{
//		return *this;
//	}
//
//	this->m_iCourseID = course.m_iCourseID;
//	this->m_strCourseName = course.m_strCourseName;
//	this->m_iDepartureAirportID = course.m_iDepartureAirportID;
//	this->m_iDepartureAirportID = course.m_iDepartureAirportID;
//	this->m_strFlyInfo = course.m_strFlyInfo;
//
//	this->m_vecCourseBeacons.clear();
//	for(unsigned int i = 0; i < course.m_vecCourseBeacons.size(); i++)
//	{
//		boost::shared_ptr<CourseBeacon> spData = boost::make_shared<CourseBeacon>();
//		*(spData.get()) = *(course.m_vecCourseBeacons.at(i).get());
//		this->m_vecCourseBeacons.push_back(spData);
//	}
//
//	return *this;
//}
//
//
////航路————Set 方法
//void Course::SetCourseID(int iCourseID)
//{
//	m_iCourseID = iCourseID;
//}
//
//void Course::SetCourseName(std::string strCourseName)
//{
//	m_strCourseName = strCourseName;
//}
//
//void Course::SetDepartureAirportID(int iDepartureAiportID)
//{
//	m_iDepartureAirportID = iDepartureAiportID;
//}
//
//void Course::SetArrivalAirportID(int iArrivalAirportID)
//{
//	m_iArrivalAirportID = iArrivalAirportID;
//}
//
//void Course::SetFlyInfo(std::string strFlyInfo)
//{
//	m_strFlyInfo = strFlyInfo;
//}	
//
////航路————Get 方法
//int Course::GetCourseID()
//{
//	return m_iCourseID;
//}
//
//std::string Course::GetCourseName()
//{
//	return m_strCourseName;
//}
//
//int Course::GetDepartureAirportID()
//{
//	return m_iDepartureAirportID;
//}
//
//int Course::GetArrivalAirportID()
//{
//	return m_iArrivalAirportID;
//}
//
//std::string Course::GetFlyInfo()
//{
//	return m_strFlyInfo;
//}
//
//std::vector<boost::shared_ptr<CourseBeacon> >& Course::GetCourseBeacon()
//{
//	return m_vecCourseBeacons;
//}
//
////航路————序列化 方法
//void Course::ReadFromBuffer( const char* pBuffer, int &iOffSize)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_iCourseID, pTemp, sizeof(m_iCourseID));
//	pTemp += sizeof(m_iCourseID);
//
//	m_strCourseName.assign(pTemp);
//	pTemp += m_strCourseName.size() + 1;
//
//	memcpy(&m_iDepartureAirportID, pTemp, sizeof(m_iDepartureAirportID));
//	pTemp += sizeof(m_iDepartureAirportID);
//
//	memcpy(&m_iArrivalAirportID, pTemp, sizeof(m_iArrivalAirportID));
//	pTemp += sizeof(m_iArrivalAirportID);
//
//	m_strFlyInfo.assign(pTemp);
//	pTemp += m_strFlyInfo.size() + 1;
//
//	//取出航线上的导航台个数
//	int iNum;
//	memcpy(&iNum, pTemp, sizeof(iNum));
//	pTemp += sizeof(iNum);
//
//	//取出航线上的导航台
//	int iOffSize_inline = 0;
//	for (int i=0; i<iNum; i++)
//	{
//		iOffSize_inline = 0;
//		boost::shared_ptr<CourseBeacon> spCourseBeacon = boost::make_shared<CourseBeacon>();
//		spCourseBeacon->ReadFromBuffer(pTemp,iOffSize_inline);
//		m_vecCourseBeacons.push_back(spCourseBeacon);
//
//		pTemp += iOffSize_inline;
//	}
//
//	iOffSize = pTemp - pBuffer;
//}
//
//void Course::WriteToBuffer( char* pBuffer, int &iOffSize)
//{
//	char* pTemp = pBuffer;
//	memcpy(pTemp, &m_iCourseID, sizeof(m_iCourseID));
//	pTemp += sizeof(m_iCourseID);
//
//	memcpy(pTemp, m_strCourseName.c_str(), m_strCourseName.size() + 1);
//	pTemp += m_strCourseName.size() + 1;
//
//	memcpy(pTemp, &m_iDepartureAirportID, sizeof(m_iDepartureAirportID));
//	pTemp += sizeof(m_iDepartureAirportID);
//
//	memcpy(pTemp, &m_iArrivalAirportID, sizeof(m_iArrivalAirportID));
//	pTemp += sizeof(m_iArrivalAirportID);
//
//	memcpy(pTemp, m_strFlyInfo.c_str(), m_strFlyInfo.size() + 1);
//	pTemp += m_strFlyInfo.size() + 1;
//
//	//写入航线上的导航台个数
//	int iNum = 0;
//	iNum = m_vecCourseBeacons.size();
//	memcpy(&pTemp, &iNum, sizeof(iNum));
//	pTemp += sizeof(iNum);
//
//	//写入航线上的导航台
//	int iOffSize_inline = 0;
//	for (int i=0; i<iNum; i++)
//	{
//		boost::shared_ptr<CourseBeacon> spCourseBeacon = m_vecCourseBeacons.at(i);
//		spCourseBeacon->WriteToBuffer(pTemp, iOffSize_inline);
//		pTemp += iOffSize_inline;
//	}
//
//	iOffSize = pTemp - pBuffer;
//}
//
//int Course::GetBufferSize()
//{
//	int iSize = 0;
//	iSize += sizeof(m_iCourseID);
//	iSize += m_strCourseName.size() + 1;
//	iSize += sizeof(m_iDepartureAirportID);
//	iSize += sizeof(m_iArrivalAirportID);
//	iSize += m_strFlyInfo.size() + 1;
//
//	if(m_vecCourseBeacons.size() != 0)
//	{
//		//CourseBeacon中没有可变长度的变量，故可以通过个数*每个GetBufferSize获得。
//		iSize += m_vecCourseBeacons.size() * m_vecCourseBeacons.at(0)->GetBufferSize();
//	}
//
//	return iSize;
//}


PointPosition::PointPosition()
{
	m_iPointPositionID = 0;
	m_strPointPositionName = "tempPoint";
	m_iSequence = 0;
	m_enumOwnerType = POT_STCA_AREA;
	m_iOwnerID = 0;
	m_dLongtitude = 0;
	m_dLatitude = 0;
	m_dHeight = 0;
}

PointPosition::~PointPosition()
{

}

int PointPosition::GetId()
{
	return m_iPointPositionID;
}

int PointPosition::GetOwnerId()
{
	return m_iOwnerID;
}

std::string PointPosition::GetDisplayLabel()
{
	return m_strPointPositionName;
}

void PointPosition::SetSequence(int iSeq)
{
	m_iSequence = iSeq;
}

int PointPosition::GetSequence()
{
	return m_iSequence;
}

StcaArea::StcaArea()
{
	m_iStcaAreaID = 0;
	m_strStcaAreaName = "StcaArea";
	m_iLineStyle = 0;
	m_iColor = 0;
	m_itype = DEFAULT;
	m_dLowestAlt = 0;
	m_dHighestAlt = 0;
	m_dHorizontalAlarmRange = 0;
	m_dVerticalAlarmRange = 0;
	m_dConverseTime = 0;
	m_dSuitableTime = 0;
	m_dCrossTime = 0;
	m_dFinalSideDis = 0;
	m_dFinalEndDis = 0;
}

StcaArea::~StcaArea()
{

}

int StcaArea::GetId()
{
	return m_iStcaAreaID;
}

std::string StcaArea::GetDisplayLabel()
{
	return m_strStcaAreaName;
}


MsawArea::MsawArea()
{
	m_iMsawAreaID = 0;
	m_strMsawAreaName = "MsawArea";
	m_iLineStyle = 0;
	m_iColor = 0;
	m_dHeight  = 0;
}

MsawArea::~MsawArea()
{

}

int MsawArea::GetId()
{
	return m_iMsawAreaID;
}

std::string MsawArea::GetDisplayLabel()
{
	return m_strMsawAreaName;
}

RestrictArea::RestrictArea()
{
	m_iRestrictAreaID = 0;
	m_strRestrictAreaName  = "RestrictArea";
	m_enumAreaType = AT_RESTRICT;
	m_bIsUsed  = true;
	m_dLowestAlt = 0;
	m_dHighestAlt = 0;
	m_dStartTime = 0;
	m_dEndTime = 0;
	m_iLineStyle = 0;
	m_iColor  = 0;
}

RestrictArea::~RestrictArea()
{

}

int RestrictArea::GetId()
{
	return m_iRestrictAreaID;
}

std::string RestrictArea::GetDisplayLabel()
{
	return m_strRestrictAreaName;
}

//ATS
ATS::ATS()
{
	m_iATSId = 0;
	m_strATSName = "ATS";
	m_vecRoutePt.clear();
}

ATS::ATS( const ATS &ATS )
{
	if(this == &ATS) return;

	*this = ATS;
}
ATS::~ATS()
{

}

int ATS::GetId()
{
	return m_iATSId;
}

std::string ATS::GetDisplayLabel()
{
	return m_strATSName;
}

ATS& ATS::operator=( const ATS& ATS )
{
	if (this == &ATS) return *this;

	this->m_iATSId = ATS.m_iATSId;
	this->m_strATSName = ATS.m_strATSName;
	this->m_vecRoutePt = ATS.m_vecRoutePt;

	return *this;
}

//雷达地理盲区
Radarrobe::Radarrobe()
{
	m_iRadarrobeId = 0;		                /* 雷达盲区ID */
	m_iAirspaceId = 0;						/* 所属空域ID */
	m_strRadarrobeName = "Radarrobe";	/* 雷达盲区名称*/
	m_dHeight = 0;						/* 雷达地理盲区高度(单位：米)*/
	m_vRadarrobePoint.clear(); //点组成的区域
}

Radarrobe::Radarrobe( const Radarrobe &radarrobe )
{
	if(this == &radarrobe) return;

	*this = radarrobe;
}

Radarrobe::~Radarrobe()
{

}

int Radarrobe::GetId()
{
	return m_iRadarrobeId;
}

std::string Radarrobe::GetDisplayLabel()
{
	return m_strRadarrobeName;
}

Radarrobe& Radarrobe::operator=( const Radarrobe& radarrobe )
{
	if (this == &radarrobe) return *this;

	this->m_iRadarrobeId = radarrobe.m_iRadarrobeId;
	this->m_iAirspaceId = radarrobe.m_iAirspaceId;
	this->m_strRadarrobeName = radarrobe.m_strRadarrobeName;
	this->m_dHeight = radarrobe.m_dHeight;
	this->m_vRadarrobePoint = radarrobe.m_vRadarrobePoint;

	return *this;
}

//航路
Course::Course()
{
	m_iCourseId = 0;							 /* 航路ID */
	m_iAirspaceId = 0;						 /*所属空域ID*/
	m_strCourseName = "Course";	     /* 航路名称*/
	m_bDoubleLine = false;				 /*航路是否是双线*/
	m_dWidth = 0;								 /*双线航路宽度(单位：千米)*/
	m_vecRoutePt.clear();					 /* 航路包括的航路点 */
}

Course::Course( const Course &course )
{
	if(this == &course) return;

	*this = course;
}

Course::~Course()
{

}

int Course::GetId()
{
	return m_iCourseId;
}

std::string Course::GetDisplayLabel()
{
	return m_strCourseName;
}

Course& Course::operator=( const Course& course )
{
	if (this == &course) return *this;
	this->m_iCourseId = course.m_iCourseId;
	this->m_iAirspaceId = course.m_iAirspaceId;
	this->m_strCourseName = course.m_strCourseName;
	this->m_bDoubleLine = course.m_bDoubleLine;
	this->m_dWidth = course.m_dWidth;
	this->m_vecRoutePt = course.m_vecRoutePt;

	return *this;
}

QnhArea::QnhArea()
{
	m_iQnhAreaID = 0;
	m_strQnhAreaName  = "QnhArea";
	m_bIsUsed  = true;
	m_dLowestAlt = 0;
	m_dHighestAlt = 0;
	m_iLineStyle = 0;
	m_iColor  = 0;
	m_dQnhValue = 0;
}

QnhArea::~QnhArea()
{
	
}

int QnhArea::GetId()
{
	return m_iQnhAreaID;
}

std::string QnhArea::GetDisplayLabel()
{
	return m_strQnhAreaName;
	}

InhibitoryArea::InhibitoryArea()
{
	m_iInhibitoryAreaID = 0;
	m_strInhibitoryAreaName = "告警抑制区";
	m_enumType = IAT_STCA_AREA_TYPE;
	m_dLowestAlt = 0;
	m_dHighestAlt = 0;
}

InhibitoryArea::InhibitoryArea( const InhibitoryArea &inhibitoryArea )
{
	if(this == &inhibitoryArea) return;

	*this = inhibitoryArea;
}

InhibitoryArea& InhibitoryArea::operator=( const InhibitoryArea& inhibitoryArea )
{
	if (this == &inhibitoryArea) return *this;
	this->m_iInhibitoryAreaID = inhibitoryArea.m_iInhibitoryAreaID;
	this->m_strInhibitoryAreaName = inhibitoryArea.m_strInhibitoryAreaName;
	this->m_enumType = inhibitoryArea.m_enumType;
	this->m_dLowestAlt = inhibitoryArea.m_dLowestAlt;
	this->m_dHighestAlt = inhibitoryArea.m_dHighestAlt;
	this->m_vInhibitoryAreaPoint = inhibitoryArea.m_vInhibitoryAreaPoint;

	return *this;
}

InhibitoryArea::~InhibitoryArea()
{

}

int InhibitoryArea::GetId()
{
	return m_iInhibitoryAreaID;
}

std::string InhibitoryArea::GetDisplayLabel()
{
	return m_strInhibitoryAreaName;
}