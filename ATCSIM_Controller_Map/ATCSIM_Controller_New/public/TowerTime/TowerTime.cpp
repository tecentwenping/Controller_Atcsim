#pragma warning(disable:4786)
#include "TowerTime.h"

//PKT_IMPLEMENT_DYNCREATE(CTowerTime);
//--------------------------------------
CTowerTime::CTowerTime(int points)
{
	m_points=points;
	m_millisecond = 0;
}
//--------------------------------------
CTowerTime::CTowerTime()
{
	m_points=0;
	m_millisecond = 0;
}
//------------------------------------
CTowerTime & CTowerTime::operator =(const CTowerTime & v)
{
	m_points = v.m_points;
	return *this;
}
//arithmatic operations===================
CTowerTime CTowerTime::operator + ( CTowerTime &v)
{
	return (CTowerTime( m_points + v.m_points)); 
}
CTowerTime CTowerTime::operator - ( CTowerTime &v)
{
	return (CTowerTime( m_points - v.m_points));
}
CTowerTime CTowerTime::operator + ( int v)
{
	return (CTowerTime( m_points + v));
}
CTowerTime CTowerTime::operator - ( int v)
{
	return (CTowerTime( m_points - v));
}
//logic operations===============================
int CTowerTime::operator == (const CTowerTime & v) const 
{
	return (m_points == v.m_points);
}
int CTowerTime::operator != (const CTowerTime & v) const
{
	return (m_points != v.m_points);
}
int CTowerTime::operator >= (const CTowerTime & v) const
{
	return (m_points >= v.m_points);
}
int CTowerTime::operator <= (const CTowerTime & v) const
{
	return (m_points <= v.m_points); 
}
int CTowerTime::operator > (const CTowerTime & v) const
{ 
	return (m_points > v.m_points);
}
int CTowerTime::operator < (const CTowerTime & v) const
{
	return (m_points < v.m_points); 
}
int CTowerTime::operator == (const int v) const
{
	return (m_points == v); 
}
int CTowerTime::operator != (const int v) const
{
	return (m_points != v); 
}
int CTowerTime::operator >= (const int v) const
{
	return (m_points >= v); 
}
int CTowerTime::operator <= (const int v) const
{
	return (m_points <= v); 
}
int CTowerTime::operator > (const int v) const
{
	return (m_points > v); 
}
int CTowerTime::operator < (const int v) const
{
	return (m_points < v); 
}
// type casting=================================
CTowerTime::operator int()
{
	return m_points; 
}
/*
void CTowerTime::WriteToBuffer(char* pBuffer)
{
	memcpy(pBuffer, &m_points, sizeof(m_points));
}

void CTowerTime::ReadFromBuffer(const char* pBuffer)
{
    memcpy(&m_points, pBuffer, sizeof(m_points));
}

int CTowerTime::GetBufferSize()
{
	return sizeof(m_points);
}
*/
int CTowerTime::SecondToPoint(double second)//秒转换成毫秒
{
	int point=static_cast<int>(second*1000);
	return point;
}
double CTowerTime::PointToSecond(int point)//毫秒转换成秒
{
	return (double)point/1000.0;
}