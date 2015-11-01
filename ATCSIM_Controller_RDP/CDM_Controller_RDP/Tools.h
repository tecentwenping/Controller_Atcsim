#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include "wworldpoint.h"
class CTools 
{
public:
	static void ConvertInt2String(int number,std::string& result);
	static int ConvertString2Int(int mumber,const std::string& sourceStr);
	static double DistancePoint2Point(WPointF p1,WPointF p2);
	static int CompuTimeDiff(std::string time);
	
	
};

#endif // TOOLS_H
