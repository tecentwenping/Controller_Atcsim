#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <math.h>

class Coordinate
{
public:
    Coordinate();
	Coordinate(double dcenterLongitude, double dcenterLatitude);
	~Coordinate();
public:
	void SetCenterPos(double dcenterLongitude, double dcenterLatitude);
	int RadianToDegree(double dInRadian, double &dOutDegree, 
		double &dOutMinute, double &dOutSecond, bool bOffSet);

	double DegreeToRadian(double dInDegree, double dInMinute, double dInSecond, bool bOffSet);

	void ConvertLongLat2XY(double dInCenterLong, double dInCenterLat, double dInLongitude, double dInLatitude,
		double &dOutX, double &dOutY);

	void ConvertXY2LongLat(double dInCenterLong, double dInCenterLat, double dInX, double dInY,
		double &dOutLongitude, double &dOutLatitude);

	void ConvertLongLat2XY(double dInLongitude, double dInLatitude, double &dOutX, double &dOutY);
    void ConvertXY2LongLat(double dInX, double dInY, double &dOutLongitude, double &dOutLatitude);
private:
	double m_dAerodromeLongitude;
	double m_dAerodromeLatitude;
};

#endif