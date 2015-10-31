#ifndef _WPERFORMANCE_QUERY_H_
#define _WPERFORMANCE_QUERY_H_

#include <Windows.h>

class WPerformanceQuery
{
public:
	explicit WPerformanceQuery(const char* func_name);
	~WPerformanceQuery();

private:
	const char* m_func_name;
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_counter;
};

#define PERFORMANCE_QUERY_IMPL(func_name) WPerformanceQuery __performace_query__(func_name);

#ifdef _USE_PERFORMANCE_QUERY
#define PERFORMANCE_QUERY PERFORMANCE_QUERY_IMPL(__FUNCDNAME__)
#define PERFORMANCE_QUERY_EX(block_name) PERFORMANCE_QUERY_IMPL(block_name)
#else
#define PERFORMANCE_QUERY 0;
#define PERFORMANCE_QUERY_EX(block_name) 0;
#endif

#endif