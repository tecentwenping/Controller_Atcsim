#ifndef _WPERFORMANCE_QUERY_MANAGER_H_
#define _WPERFORMANCE_QUERY_MANAGER_H_

#include <map>
#include "singleton.h"

class WPerformanceQueryManager : public WSingleton<WPerformanceQueryManager>
{
	DECLARE_SINGLETON(WPerformanceQueryManager)

public:
	~WPerformanceQueryManager();
	
	void Clear();

	void AddItem(const char* func_name, double time_used);
	std::multimap<const char*, double> GetData() const;

private:
	std::multimap<const char*, double> m_mmp;
};

#endif