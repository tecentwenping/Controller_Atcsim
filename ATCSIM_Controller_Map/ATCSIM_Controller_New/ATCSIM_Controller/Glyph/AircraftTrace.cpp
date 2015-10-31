#include "AircraftTrace.h"
#include "AircraftInfo.h"
#include "DataOperator/ControllerAcftInfo.h"
#include <boost/make_shared.hpp>

double AircraftTrace::PI =  3.14159265358979323846;
AircraftTrace::AircraftTrace():
m_nTraceID(-1), m_nAttitude(0),
m_dHeading(0.0), m_fAbsX(0.0), m_fAbsY(0.0), m_byAtt(1),
m_strName(""), m_strSSR(""), eStateType(STATE_NONE),
m_pAcftInfo(NULL), m_wPRLPos(0, 0), m_fPRLTime(3.0), 
m_nHistoryNum(10),m_eCurSignalType(SIGNAL_COMBINED),
m_bShowLabel(true), m_bHide(false), m_iCount(-1)
{
	//m_vHistoryPos.reserve(5000);
}

AircraftTrace::AircraftTrace( const AircraftTrace& rhs )
{
	m_nTraceID			= rhs.m_nTraceID;
	m_euTrackType		= rhs.m_euTrackType;
	m_nICAOAddress		= rhs.m_nICAOAddress;
	m_strName			= rhs.m_strName;
	m_strSSR			= rhs.m_strSSR;
	m_dLongitude		= rhs.m_dLongitude;
	m_dLatitude			= rhs.m_dLatitude;
	m_euAltitudeType	= rhs.m_euAltitudeType;
	m_nDesAltitude		= rhs.m_nDesAltitude;
	m_euDesAltitudeType = rhs.m_euDesAltitudeType;
	m_dGAS				= rhs.m_dGAS;
	m_dHeading			= rhs.m_dHeading;
	m_dTrackAngle		= rhs.m_dTrackAngle;
	m_euObjType			= rhs.m_euObjType;
	m_euEmergencyType	= rhs.m_euEmergencyType;
	m_bHide				= rhs.m_bHide;
	m_fAbsX				= m_fAbsY;
	m_fAbsY				= m_fAbsY;
	m_byAtt				= rhs.m_byAtt;
	eStateType			= rhs.eStateType;
	m_fPRLTime			= rhs.m_fPRLTime;
	m_nHistoryNum		= rhs.m_nHistoryNum;
	m_wPRLPos			= rhs.m_wPRLPos;
	m_pAcftInfo			= new ControllerAcftInfo();
	m_pAcftInfo			= rhs.m_pAcftInfo;
	m_eCurSignalType	= rhs.m_eCurSignalType;
	m_bShowLabel		= rhs.m_bShowLabel;
	m_iCount			= rhs.m_iCount;




}



AircraftTrace::~AircraftTrace()
{

}

void AircraftTrace::ComputeMapXY()
{
	//double dx = 0.00;
	//double dy = 0.00;
	//theApp::instance().GetMapManagerPtr()->GetMapCoordinatePtr()->\
	//	ConvertLongLat2XY(m_dLongitude, m_dLatitude, dx, dy);

	//m_fAbsX = static_cast<float>(dx);
	//m_fAbsY = static_cast<float>(dy);
}


void AircraftTrace::ComputPRLPos()
{
	//if (!m_vHistoryPos.empty())
	//{
	//	//如果历史航迹不为空时
	//	float            s  = 0.0f;
	//	double           dTmpx = 0.0;
	//	double           dTmpty = 0.0;
	//	double           root = 0.0;

	//	dTmpx  = m_vHistoryPos.back()->x() - m_fAbsX;      /* the x different per 6s.*///dong 05.3.1
	//	dTmpty = m_vHistoryPos.back()->y() - m_fAbsY;      /* the y different per 6s.*/

	//	root  = sqrt(dTmpx*dTmpx + dTmpty*dTmpty);     //一次更新前后两飞机之间的距离
	//	if (root<1e-10)
	//	{
	//		root = 1.0;
	//	}

	//	//将速度换算为m/s后计算m_fPRLTime分钟内的路程
	//	//s = (float)(m_fPRLTime*60*(m_nIas * 10 / 36));  //10分钟*60秒*（当前速度（km/h）*(1000)/(60*60)） m/s  = m
	//	s = (float)(m_fPRLTime*60*(m_dGAS * 10 / 36));  //10分钟*60秒*（当前速度（km/h）*(1000)/(60*60)） m/s  = m
	//	/*///////////////////////////////
	//	1         B
	//	1        /|
	//	1 root  / |dTmpty
	//	1      /  |
	//	1     /   |
	//	1    ----- dTmpx
	//	1    A
	//	|  dTmpx/root = t/s
	//	///////////////////////////////*/
	//	m_wPRLPos.setX(m_fAbsX - dTmpx / root * s);
	//	m_wPRLPos.setY(m_fAbsY - dTmpty / root * s);

	//	//预计线角度更新
	//	int iAngle = (int)(asin(-dTmpx/root)*(180/PI));

	//	if (dTmpty > 0)
	//	{
	//		iAngle = 180 - iAngle;
	//	}
	//	m_dTrackAngle = (iAngle+360)%360;
	//}
	//else
	//{
	//	m_wPRLPos.setXY(m_fAbsX, m_fAbsY);
	//}

	//if(5000 == m_vHistoryPos.size())
	//{
	//	m_vHistoryPos.erase(m_vHistoryPos.begin());
	//}

	//m_vHistoryPos.push_back(boost::make_shared<WPointF>(m_fAbsX, m_fAbsY));
}


void AircraftTrace::SetPRLTime(const float fTime)
{
	double dTmpX = 0;
	double dTmpY = 0;
	dTmpX = (m_wPRLPos.x() - m_fAbsX) * fTime / m_fPRLTime;
	dTmpY = (m_wPRLPos.y() - m_fAbsY) * fTime / m_fPRLTime;
	m_wPRLPos.setX(m_fAbsX + dTmpX);
	m_wPRLPos.setY(m_fAbsY + dTmpY);
	m_fPRLTime = fTime;
}


/**
\brief     SetHistoryNum
\Access    public 
\param     const int nHistoryNum
\retval    void
\remark		//TODO @hxl 当前历史航迹点是按照设置num来存储还是按照设置num来显示   
*/
void AircraftTrace::SetHistoryNum( const int nHistoryNum )
{
	m_nHistoryNum = nHistoryNum;
}

void AircraftTrace::GetSSRCode( int &iSSR ) const
{
	std::string numberics("0123456789");
	std::string::size_type pos = m_strSSR.find_first_of(numberics);
	if (pos != std::string::npos)
	{
		iSSR = atoi(m_strSSR.substr(pos).c_str());
	}
	else
	{
		iSSR = -2;
	}
}