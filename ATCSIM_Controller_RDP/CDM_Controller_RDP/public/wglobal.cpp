#include <limits>
#include "wglobal.h"

/**
\brief      bit
\Access    public 
\param  int i
\retval     int MAPAPI
\remark    返回一个数的二进制位数 
*/
int bit(int i)
{
	int ret = 0;
	while (i)
	{
		++ret;
		i >>= 1;
	}
	return ret;
}