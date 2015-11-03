#include "Tools.h"
#include <sstream>
void CTools::ConvertInt2String( int number,std::string& resultStr )
{
	std::stringstream stream;
	stream<<number;
	resultStr=stream.str(); 
}

int CTools::ConvertString2Int( int number,const std::string& sourceStr )
{
	std::stringstream stream(sourceStr);
	stream>>number;
	return number;
}

double CTools::DistancePoint2Point( WPointF p1,WPointF p2 )
{
	
	double dX=p1.x()-p2.x();
	double dY=p1.y()-p2.y();
	double distance=sqrt(dX*dX+dY*dY);
	return distance;
}

//int CTools::CompuTimeDiff( std::string time )
//{
//
//}
