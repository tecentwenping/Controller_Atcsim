#include <limits>
#include "wglobal.h"

/**
\brief      bit
\Access    public 
\param  int i
\retval     int MAPAPI
\remark    ����һ�����Ķ�����λ�� 
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