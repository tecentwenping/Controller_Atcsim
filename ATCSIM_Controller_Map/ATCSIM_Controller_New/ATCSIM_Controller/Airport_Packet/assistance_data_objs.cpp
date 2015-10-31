#include "assistance_data_objs.h"


/*----------------图元------------------- */
GlyphPt::GlyphPt(void)
{
	m_iGlyphPtID = 0;
	m_strGlyphPtName  = "图元名称";
	m_iPointType = 0;
	m_iPointID = -1;
	m_dLongtitude = 0;
	m_dLatitude = 0;
	m_dHeight = -1;
	m_iProcessMode = -1;
	m_iArcInfoID = -1;
}

GlyphPt::~GlyphPt(void)
{
}

int GlyphPt::GetId()
{
	return m_iGlyphPtID;
}

std::string GlyphPt::GetDisplayLabel()
{
	return m_strGlyphPtName;
}

//图元————拷贝、赋值函数
GlyphPt::GlyphPt(const GlyphPt &glyphPt)
{
	if (this == &glyphPt)
	{
		return;
	}

	*this = glyphPt;
}

GlyphPt& GlyphPt::operator=(const GlyphPt& glyphPt)
{
	if(this == &glyphPt)
	{
		return *this;
	}

	this->m_iGlyphPtID = glyphPt.m_iGlyphPtID;
	this->m_strGlyphPtName = glyphPt.m_strGlyphPtName;
	this->m_iPointType = glyphPt.m_iPointType;
	this->m_iPointID = glyphPt.m_iPointID;
	this->m_dLongtitude = glyphPt.m_dLongtitude;
	this->m_dLatitude = glyphPt.m_dLatitude;
	this->m_dHeight = glyphPt.m_dHeight;
	this->m_iProcessMode = glyphPt.m_iProcessMode;
	this->m_iArcInfoID = glyphPt.m_iArcInfoID;

	return *this;
}


//图元————Set 方法
void GlyphPt::SetGlyphPtID(int iGlyphID)
{
	m_iGlyphPtID = iGlyphID;
}

void GlyphPt::SetGlyphPtName(std::string strGlyphName)
{
	m_strGlyphPtName = strGlyphName;
}

void GlyphPt::SetPointType(int iType)
{
	m_iPointType = iType;
}

void GlyphPt::SetPointID(int iID)
{
	m_iPointID = iID;
}

void GlyphPt::SetLatitude(double dLatitude)
{
	m_dLatitude = dLatitude;
}

void GlyphPt::SetLongtitude(double dLongtitude)
{
	m_dLongtitude = dLongtitude;
}

void GlyphPt::SetHeight(double dHeight)
{
	m_dHeight = dHeight;
}

void GlyphPt::SetProcessMode(int iProcessMode)
{
	m_iProcessMode = iProcessMode;
}

void GlyphPt::SetArcInfoID(int iDetailID)
{
	m_iArcInfoID = iDetailID;
}

//图元————Get 方法
int GlyphPt::GetGlyphPtID()
{
	return m_iGlyphPtID;
}

std::string GlyphPt::GetGlyphPtName()
{
	return m_strGlyphPtName;
}

int GlyphPt::GetPointType()
{
	return m_iPointType;
}

int GlyphPt::GetPointID()
{
	return m_iPointID;
}

double GlyphPt::GetLongtitude()
{
	return m_dLongtitude;
}

double GlyphPt::GetLatitude()
{
	return m_dLatitude;
}

double GlyphPt::GetHeight()
{
	return m_dHeight;
}

int GlyphPt::GetProcessMode()
{
	return m_iProcessMode;
}

int GlyphPt::GetArcInfoID()
{
	return m_iArcInfoID;
}

//图元————序列化 方法
void GlyphPt::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iGlyphPtID, pTemp, sizeof(m_iGlyphPtID));
	pTemp += sizeof(m_iGlyphPtID);

	m_strGlyphPtName.assign(pTemp);
	pTemp += m_strGlyphPtName.size() + 1;

	memcpy(&m_iPointType, pTemp, sizeof(m_iPointType));
	pTemp += sizeof(m_iPointType);

	memcpy(&m_iPointID, pTemp, sizeof(m_iPointID));
	pTemp += sizeof(m_iPointID);

	memcpy(&m_dLongtitude, pTemp, sizeof(m_dLongtitude));
	pTemp += sizeof(m_dLongtitude);

	memcpy(&m_dLatitude, pTemp, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(&m_dHeight, pTemp, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(&m_iProcessMode, pTemp, sizeof(m_iProcessMode));
	pTemp += sizeof(m_iProcessMode);

	memcpy(&m_iArcInfoID, pTemp, sizeof(m_iArcInfoID));
	pTemp += sizeof(m_iArcInfoID);

	iOffSize = pTemp - pBuffer;
}

void GlyphPt::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iGlyphPtID, sizeof(m_iGlyphPtID));
	pTemp += sizeof(m_iGlyphPtID);

	memcpy(pTemp, m_strGlyphPtName.c_str(), m_strGlyphPtName.size() + 1);
	pTemp += m_strGlyphPtName.size() + 1;

	memcpy(pTemp, &m_iPointType, sizeof(m_iPointType));
	pTemp += sizeof(m_iPointType);

	memcpy(pTemp, &m_iPointID, sizeof(m_iPointID));
	pTemp += sizeof(m_iPointID);

	memcpy(pTemp, &m_dLongtitude, sizeof(m_dLongtitude));
	pTemp += sizeof(m_dLongtitude);

	memcpy(pTemp, &m_dLatitude, sizeof(m_dLatitude));
	pTemp += sizeof(m_dLatitude);

	memcpy(pTemp, &m_dHeight, sizeof(m_dHeight));
	pTemp += sizeof(m_dHeight);

	memcpy(pTemp, &m_iProcessMode, sizeof(m_iProcessMode));
	pTemp += sizeof(m_iProcessMode);

	memcpy(pTemp, &m_iArcInfoID, sizeof(m_iArcInfoID));
	pTemp += sizeof(m_iArcInfoID);

	iOffSize = pTemp - pBuffer;
}

int GlyphPt::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iGlyphPtID);
	iSize += m_strGlyphPtName.size() + 1;
	iSize += sizeof(m_iPointType);
	iSize += sizeof(m_iPointID);
	iSize += sizeof(m_dLongtitude);
	iSize += sizeof(m_dLatitude);
	iSize += sizeof(m_dHeight);
	iSize += sizeof(m_iProcessMode);
	iSize += sizeof(m_iArcInfoID);

	return iSize;
}




/*-------------图元详细信息------------------- */
GlyphPtArcInfo::GlyphPtArcInfo(void)
{
	m_iArcInfoID = 0;
	m_dTopLongitude = 0;
	m_dTopLatitude = 0;
	m_dBottomLongitude = 0;
	m_dBottomLatitude = 0;
	m_dStartAngle = 0;
	m_dEndAngle = 0;
	m_dRotateAngle = 0;
}

GlyphPtArcInfo::~GlyphPtArcInfo(void)
{
}

int GlyphPtArcInfo::GetId()
{
	return m_iArcInfoID;
}

std::string GlyphPtArcInfo::GetDisplayLabel()
{
	return "";
}

//图元详细信息————拷贝、赋值函数
GlyphPtArcInfo::GlyphPtArcInfo(const GlyphPtArcInfo &glyphPtArcInfo)
{
	if (this == &glyphPtArcInfo)
	{
		return;
	}

	*this = glyphPtArcInfo;
}

GlyphPtArcInfo& GlyphPtArcInfo::operator=(const GlyphPtArcInfo& glyphPtArcInfo)
{
	if(this == &glyphPtArcInfo)
	{
		return *this;
	}

	this->m_iArcInfoID = glyphPtArcInfo.m_iArcInfoID;
	this->m_dTopLongitude = glyphPtArcInfo.m_dTopLongitude;
	this->m_dTopLatitude = glyphPtArcInfo.m_dTopLatitude;
	this->m_dBottomLongitude = glyphPtArcInfo.m_dBottomLongitude;
	this->m_dBottomLatitude = glyphPtArcInfo.m_dBottomLatitude;
	this->m_dStartAngle = glyphPtArcInfo.m_dStartAngle;
	this->m_dEndAngle = glyphPtArcInfo.m_dEndAngle;
	this->m_dRotateAngle = glyphPtArcInfo.m_dRotateAngle;

	return *this;
}

//图元详细信息————Set 方法
void GlyphPtArcInfo::SetArcInfoID(int iArcInfoID)
{
	m_iArcInfoID = iArcInfoID;
}

void GlyphPtArcInfo::SetTopLongitude(double dTopLongitude)
{
	m_dTopLongitude = dTopLongitude;
}

void GlyphPtArcInfo::SetTopLatitude(double dTopLatitude)
{
	m_dTopLatitude = dTopLatitude;
}

void GlyphPtArcInfo::SetBottomLongitude(double dBottomLongitude)
{
	m_dBottomLongitude = dBottomLongitude;
}

void GlyphPtArcInfo::SetBottomLatitude(double dBottomLatitude)
{
	m_dBottomLatitude = dBottomLatitude;
}

void GlyphPtArcInfo::SetStartAngle(double dStartAngle)
{
	m_dStartAngle = dStartAngle;
}

void GlyphPtArcInfo::SetEndAngle(double dEndAngle)
{
	m_dEndAngle = dEndAngle;
}

void GlyphPtArcInfo::SetRotateAngle(double dRotateAngle)
{
	m_dRotateAngle = dRotateAngle;
}


//图元详细信息————Get 方法
int  GlyphPtArcInfo::GetArcInfoID()
{
	return m_iArcInfoID;
}

double GlyphPtArcInfo::GetTopLongitude()
{
	return m_dTopLongitude;
}

double GlyphPtArcInfo::GetTopLatitude()
{
	return m_dTopLatitude;
}

double GlyphPtArcInfo::GetBottomLongitude()
{
	return m_dBottomLongitude;
}

double GlyphPtArcInfo::GetBottomLatitude()
{
	return m_dBottomLatitude;
}

double GlyphPtArcInfo::GetStartAngle()
{
	return m_dStartAngle;
}

double GlyphPtArcInfo::GetEndAngle()
{
	return m_dEndAngle;
}

double GlyphPtArcInfo::GetRotateAngle()
{
	return m_dRotateAngle;
}

//图元详细信息————序列化 方法
void GlyphPtArcInfo::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iArcInfoID, pTemp, sizeof(m_iArcInfoID));
	pTemp += sizeof(m_iArcInfoID);

	memcpy(&m_dTopLongitude, pTemp, sizeof(m_dTopLongitude));
	pTemp += sizeof(m_dTopLongitude);

	memcpy(&m_dTopLatitude, pTemp, sizeof(m_dTopLatitude));
	pTemp += sizeof(m_dTopLatitude);

	memcpy(&m_dBottomLongitude, pTemp, sizeof(m_dBottomLongitude));
	pTemp += sizeof(m_dBottomLongitude);

	memcpy(&m_dBottomLatitude, pTemp, sizeof(m_dBottomLatitude));
	pTemp += sizeof(m_dBottomLatitude);

	memcpy(&m_dStartAngle, pTemp, sizeof(m_dStartAngle));
	pTemp += sizeof(m_dStartAngle);

	memcpy(&m_dEndAngle, pTemp, sizeof(m_dEndAngle));
	pTemp += sizeof(m_dEndAngle);

	memcpy(&m_dRotateAngle, pTemp, sizeof(m_dRotateAngle));
	pTemp += sizeof(m_dRotateAngle);

	iOffSize = pTemp - pBuffer;
}

void GlyphPtArcInfo::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iArcInfoID, sizeof(m_iArcInfoID));
	pTemp += sizeof(m_iArcInfoID);

	memcpy(pTemp, &m_dTopLongitude, sizeof(m_dTopLongitude));
	pTemp += sizeof(m_dTopLongitude);

	memcpy(pTemp, &m_dTopLatitude, sizeof(m_dTopLatitude));
	pTemp += sizeof(m_dTopLatitude);

	memcpy(pTemp, &m_dBottomLongitude, sizeof(m_dBottomLongitude));
	pTemp += sizeof(m_dBottomLongitude);

	memcpy(pTemp, &m_dBottomLatitude, sizeof(m_dBottomLatitude));
	pTemp += sizeof(m_dBottomLatitude);

	memcpy(pTemp, &m_dStartAngle, sizeof(m_dStartAngle));
	pTemp += sizeof(m_dStartAngle);

	memcpy(pTemp, &m_dEndAngle, sizeof(m_dEndAngle));
	pTemp += sizeof(m_dEndAngle);

	memcpy(pTemp, &m_dRotateAngle, sizeof(m_dRotateAngle));
	pTemp += sizeof(m_dRotateAngle);

	iOffSize = pTemp - pBuffer;
}

int GlyphPtArcInfo::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iArcInfoID);
	iSize += sizeof(m_dTopLongitude);
	iSize += sizeof(m_dTopLatitude);
	iSize += sizeof(m_dBottomLongitude);
	iSize += sizeof(m_dBottomLatitude);
	iSize += sizeof(m_dStartAngle);
	iSize += sizeof(m_dEndAngle);
	iSize += sizeof(m_dRotateAngle);

	return iSize;
}



/*-------------------柱面-----------------*/
Cylinder::Cylinder(void)
{
	m_iCylinderID = 0;
	m_strCylinderName = "柱面名称";
	m_dBottomLevel = 0;
	m_dTopLevel = 0;
	m_iOwnType = -1;
	m_iOwnID = -1;
}

Cylinder::~Cylinder(void)
{
}

int Cylinder::GetId()
{
	return m_iCylinderID;
}

std::string Cylinder::GetDisplayLabel()
{
	return m_strCylinderName;
}

//柱面————拷贝、赋值函数
Cylinder::Cylinder(const Cylinder &cylinder)
{
	if (this == &cylinder)
	{
		return;
	}

	*this = cylinder;
}

Cylinder& Cylinder::operator=(const Cylinder& cylinder)
{
	if(this == &cylinder)
	{
		return *this;
	}

	this->m_iCylinderID = cylinder.m_iCylinderID;
	this->m_strCylinderName = cylinder.m_strCylinderName;
	this->m_dBottomLevel = cylinder.m_dBottomLevel;
	this->m_dTopLevel = cylinder.m_dTopLevel;
	this->m_iOwnType = cylinder.m_iOwnType;
	this->m_iOwnID = cylinder.m_iOwnID;

	return *this;
}


//柱面————Set 方法
void Cylinder::SetCylinderID(int iCylinderID)
{
	m_iCylinderID = iCylinderID;
}

void Cylinder::SetCylinderName(std::string strCylinderName)
{
	m_strCylinderName = strCylinderName;
}

void Cylinder::SetBottomLevel(double bottomLevel)
{
	m_dBottomLevel = bottomLevel;
}

void Cylinder::SetTopLevel(double topLevel)
{
	m_dTopLevel = topLevel;
}

void Cylinder::SetOwnType(int iType)
{
	m_iOwnType = iType;
}

void Cylinder::SetOwnID(int iID)
{
	m_iOwnID = iID;
}

//柱面————Get 方法
int Cylinder::GetCylinderID()
{
	return m_iCylinderID;
}
std::string Cylinder::GetCylinderName()
{
	return m_strCylinderName;
}
double Cylinder::GetBottomLevel()
{
	return m_dBottomLevel;
}
double Cylinder::GetTopLevel()
{
	return m_dTopLevel;
}

int Cylinder::GetOwnType()
{
	return m_iOwnType;
}

int Cylinder::GetOwnID()
{
	return m_iOwnID;
}

//柱面————序列化 方法
void Cylinder::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iCylinderID, pTemp, sizeof(m_iCylinderID));
	pTemp += sizeof(m_iCylinderID);

	m_strCylinderName.assign(pTemp);
	pTemp += m_strCylinderName.size() + 1;

	memcpy(&m_dBottomLevel, pTemp, sizeof(m_dBottomLevel));
	pTemp += sizeof(m_dBottomLevel);

	memcpy(&m_dTopLevel, pTemp, sizeof(m_dTopLevel));
	pTemp += sizeof(m_dTopLevel);

	memcpy(&m_iOwnType, pTemp, sizeof(m_iOwnType));
	pTemp += sizeof(m_iOwnType);

	memcpy(&m_iOwnID, pTemp, sizeof(m_iOwnID));
	pTemp += sizeof(m_iOwnID);

	iOffSize = pTemp - pBuffer;
}

void Cylinder::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iCylinderID, sizeof(m_iCylinderID));
	pTemp += sizeof(m_iCylinderID);

	memcpy(pTemp, m_strCylinderName.c_str(), m_strCylinderName.size() + 1);
	pTemp += m_strCylinderName.size() + 1;

	memcpy(pTemp, &m_dBottomLevel, sizeof(m_dBottomLevel));
	pTemp += sizeof(m_dBottomLevel);

	memcpy(pTemp, &m_dTopLevel, sizeof(m_dTopLevel));
	pTemp += sizeof(m_dTopLevel);

	memcpy(pTemp, &m_iOwnType, sizeof(m_iOwnType));
	pTemp += sizeof(m_iOwnType);

	memcpy(pTemp, &m_iOwnID, sizeof(m_iOwnID));
	pTemp += sizeof(m_iOwnID);

	iOffSize = pTemp - pBuffer;
}

int Cylinder::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iCylinderID);
	iSize += m_strCylinderName.size() + 1;
	iSize += sizeof(m_dBottomLevel);
	iSize += sizeof(m_dTopLevel);
	iSize += sizeof(m_iOwnType);
	iSize += sizeof(m_iOwnID);

	return iSize;
}


/*-------------------柱面图元关联表-----------------*/
CylinderGlyph::CylinderGlyph(void)
{
	m_iCylinderID = 0;
	m_iGlyphPtID = 0;
	m_iSequence = 0;
}

CylinderGlyph::~CylinderGlyph(void)
{
}

//柱面图元关联表————拷贝、赋值函数
CylinderGlyph::CylinderGlyph(const CylinderGlyph &cylinderGlyph)
{
	if (this == &cylinderGlyph)
	{
		return;
	}

	*this = cylinderGlyph;
}

CylinderGlyph& CylinderGlyph::operator=(const CylinderGlyph& cylinderGlyph)
{
	if(this == &cylinderGlyph)
	{
		return *this;
	}

	this->m_iCylinderID = cylinderGlyph.m_iCylinderID;
	this->m_iGlyphPtID = cylinderGlyph.m_iGlyphPtID;
	this->m_iSequence = cylinderGlyph.m_iSequence;

	return *this;
}


//柱面图元关联表————Set 方法
void CylinderGlyph::SetCylinderID(int iCylinderID)
{
	m_iCylinderID = iCylinderID;
}

void CylinderGlyph::SetGlyphPtID(int iGlyphPtID)
{
	m_iGlyphPtID = iGlyphPtID;
}

void CylinderGlyph::SetSequence(int iSequence)
{
	m_iSequence = iSequence;
}


//柱面图元关联表————Get 方法
int CylinderGlyph::GetCylinderID()
{
	return m_iCylinderID;
}

int CylinderGlyph::GetGlyphPtID()
{
	return m_iGlyphPtID;
}

int CylinderGlyph::GetSequence()
{
	return m_iSequence;
}

//柱面图元关联表————序列化 方法
void CylinderGlyph::ReadFromBuffer( const char* pBuffer, int &iOffSize)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iCylinderID, pTemp, sizeof(m_iCylinderID));
	pTemp += sizeof(m_iCylinderID);

	memcpy(&m_iGlyphPtID, pTemp, sizeof(m_iGlyphPtID));
	pTemp += sizeof(m_iGlyphPtID);

	memcpy(&m_iSequence, pTemp, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	iOffSize = pTemp - pBuffer;
}

void CylinderGlyph::WriteToBuffer( char* pBuffer, int &iOffSize)
{
	char* pTemp = pBuffer;
	memcpy(pTemp, &m_iCylinderID, sizeof(m_iCylinderID));
	pTemp += sizeof(m_iCylinderID);

	memcpy(pTemp, &m_iGlyphPtID, sizeof(m_iGlyphPtID));
	pTemp += sizeof(m_iGlyphPtID);

	memcpy(pTemp, &m_iSequence, sizeof(m_iSequence));
	pTemp += sizeof(m_iSequence);

	iOffSize = pTemp - pBuffer;
}

int CylinderGlyph::GetBufferSize()
{
	int iSize = 0;

	iSize += sizeof(m_iCylinderID);
	iSize += sizeof(m_iGlyphPtID);
	iSize += sizeof(m_iSequence);

	return iSize;
}



RoutePt::RoutePt()
{
	m_iID = 0;
	m_eOwnerType = ROUTEPT_OWNER_TYPE_NONE;
    m_iOwnerID = 0;
    m_iSequence = 0;
	m_iRoutePtID  = 0;
	m_strRoutePtName = "";
	m_eRoutePtType = ROUTEPT_TYPE_NONE;
	m_dLatitude = 0;
	m_dLongtitude = 0;
	m_dAltitude = 0;
	m_eLegType = ROUTEPT_DIRECT_TO_FIX;
	m_dRadius = 0;
	m_bClockWise = 0;
	m_dGrade = 0;
	m_bSpiralTurnMode = false;
	m_eTurnDirt = ROUTEPT_TURN_DIRECTION_NONE;
}

RoutePt::~RoutePt()
{

}

//
int RoutePt::GetId()
{
	return m_iID;
}

int RoutePt::GetOwnerId()
{
	return m_iOwnerID;
}

std::string RoutePt::GetDisplayLabel()
{
	return m_strRoutePtName;
}

//拷贝、赋值函数
RoutePt::RoutePt(const RoutePt &routePt)
{
	if (this == &routePt) return;

	*this = routePt;
}

RoutePt& RoutePt::operator=(const RoutePt& routePt)
{
	if (this == &routePt)	return *this;

	this->m_iID = routePt.m_iID;
	this->m_eOwnerType = routePt.m_eOwnerType;
	this->m_iOwnerID = routePt.m_iOwnerID;
	this->m_iSequence = routePt.m_iSequence;
	this->m_iRoutePtID  = routePt.m_iRoutePtID;
	this->m_strRoutePtName = routePt.m_strRoutePtName;
	this->m_eRoutePtType = routePt.m_eRoutePtType;
	this->m_dLatitude = routePt.m_dLatitude;
	this->m_dLongtitude = routePt.m_dLongtitude;
	this->m_dAltitude = routePt.m_dAltitude;
	this->m_eLegType = routePt.m_eLegType;
	this->m_dRadius = routePt.m_dRadius;
	this->m_bClockWise = routePt.m_bClockWise;
	this->m_dGrade = routePt.m_dGrade;
	this->m_bSpiralTurnMode = routePt.m_bSpiralTurnMode;
	this->m_eTurnDirt = routePt.m_eTurnDirt;

	return *this;
}

void RoutePt::SetSequence( int iSeq )
{
	m_iSequence = iSeq;
}

int RoutePt::GetSequence()
{
	return m_iSequence;
}