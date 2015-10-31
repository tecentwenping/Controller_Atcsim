#include "coordinate.h"

#define WS_PI 3.14

Coordinate::Coordinate() : m_dAerodromeLongitude(0),
                           m_dAerodromeLatitude(0)
{
}

Coordinate::Coordinate(double dcenterLongitude, double dcenterLatitude) :
    m_dAerodromeLongitude(dcenterLongitude),
	m_dAerodromeLatitude(dcenterLatitude)
{

}
Coordinate::~Coordinate()
{

}

//���߷���
//���룺dInRaian ����ֵ, bOffSet �Ƿ���ж�����ƫ�ơ� �����ݿ��б��������������ѧֱ������ϵΪ׼��
//�����dOutDegree ����, dOutMinute ������dOutSecond ����
//���أ�-1 ������С��0�� 1 �������0
int Coordinate::RadianToDegree(double dInRadian, double &dOutDegree, 
							   double &dOutMinute, double &dOutSecond, bool bOffSet)
{
	int ret = 0;
	if (dInRadian >= 0)
		ret = 1;
	else
		ret = -1;

	dInRadian = fabs(dInRadian);
	if (dInRadian >= 2 * WS_PI)
	{
		dInRadian = fmod(dInRadian, 2 * WS_PI);
	}

	//��Ϊ���ݱ༭���ʹ�õ�����ϵ ��������Ϊ0�ȣ�˳ʱ����ת�ģ�������ʹ�õ�����ѧֱ������ϵ������Ϊ0�ȡ�
	if (bOffSet)
	{
		if (dInRadian <= (90*WS_PI/180))
			dInRadian = 90*WS_PI/180 - dInRadian;
		else
			dInRadian = 450*WS_PI/180 - dInRadian;
	}

	dOutDegree = (int)(dInRadian / WS_PI * 180);									//��	
	dOutMinute = (int)(dInRadian / WS_PI * 180 * 60 - dOutDegree * 60) ;			//��
	dOutSecond = dInRadian / WS_PI * 180 * 3600 - dOutDegree * 3600 - dOutMinute * 60;	//��

	//���λ���ֺͶ�
	if (dOutSecond >= 60)
	{
		dOutSecond = 60 - dOutSecond;
		dOutMinute = dOutMinute + 1;
	}

	if (dOutMinute >= 60)
	{
		dOutMinute = 60 - dOutMinute;
		dOutDegree++;
	}

	return ret;
}

double Coordinate::DegreeToRadian(double dInDegree, double dInMinute, double dInSecond, bool bOffSet)
{
	double dRadian = (((int)dInDegree) * 3600 + ((int)dInMinute) * 60 + dInSecond) / 3600 / 180 * WS_PI;

	//�������ĽǶ� �Ǿ���ƫ�Ƶ� ����Ҫ�ָ�����ѧֱ������ϵ
	if (bOffSet)
	{
		if (dRadian <= (90*WS_PI/180))
			dRadian = 90*WS_PI/180 - dRadian;
		else
			dRadian = 450*WS_PI/180 - dRadian;
	}
	return dRadian;
}

void Coordinate::ConvertLongLat2XY(double dInCenterLong, double dInCenterLat, double dInLongitude, double dInLatitude,
								  double &dOutX, double &dOutY)
{
	double dEarthRadian = 6371000;	// ����뾶
	double dDeltaLongitude = 0;
	double dTemp = 0;

	dDeltaLongitude = dInLongitude - dInCenterLong;
	dTemp = sin(dInLatitude) * sin(dInCenterLat) + cos(dInLatitude) * cos(dInCenterLat) * cos(dDeltaLongitude);
	dOutX = (dEarthRadian * cos(dInLatitude) * sin(dDeltaLongitude)) / dTemp;
	dOutY = (dEarthRadian * (sin(dInLatitude)*cos(dInCenterLat) - cos(dInLatitude)*sin(dInCenterLat)*cos(dDeltaLongitude))) / dTemp;
}

void Coordinate::ConvertXY2LongLat(double dInCenterLong, double dInCenterLat, double dInX, double dInY,
								  double &dOutLongitude, double &dOutLatitude)
{
	double dEarthRadian = 6371000;	// ����뾶
	double dTemp = 0;

	double dPx = 0;
	double dPy = 0;
	double dC = 0;

	dPx = dInX / dEarthRadian;
	dPy = dInY / dEarthRadian;
	dTemp = sqrt(dPx * dPx + dPy * dPy);

	if (dTemp < abs(exp(-16.0)))
	{
		dOutLongitude = dInCenterLong;
		dOutLatitude = dInCenterLat;
		return;
	}

	dC = atan(dTemp);
	dOutLongitude = dInCenterLong + atan(dPx *sin(dC) / (dTemp * cos(dInCenterLat) * cos(dC) - dPy * sin(dInCenterLat) * sin(dC)));
	dOutLatitude = asin(cos(dC) * sin(dInCenterLat) + dPy * sin(dC) * cos(dInCenterLat) / dTemp);
}

//ת����γ�ȵ���������,���ĵ��ǵ�ǰ���������ĵ�
void Coordinate::ConvertLongLat2XY(double dInLongitude, double dInLatitude, double &dOutX, double &dOutY)
{
	ConvertLongLat2XY(m_dAerodromeLongitude, m_dAerodromeLatitude,
		dInLongitude, dInLatitude, dOutX, dOutY);
}

//ת���������굽��γ��,���ĵ��ǵ�ǰ���������ĵ�
void Coordinate::ConvertXY2LongLat(double dInX, double dInY, double &dOutLongitude, double &dOutLatitude)
{
	ConvertXY2LongLat(m_dAerodromeLongitude, m_dAerodromeLatitude,
		dInX, dInY, dOutLongitude, dOutLatitude);
}


/**
\brief     SetCenterPos
\Access    public 
\param     double dcenterLongitude
\param     double dcenterLatitude
\retval    void
\remark     
*/
void Coordinate::SetCenterPos( double dcenterLongitude, double dcenterLatitude )
{
	m_dAerodromeLongitude = dcenterLongitude;
	m_dAerodromeLatitude  = dcenterLatitude;
}

