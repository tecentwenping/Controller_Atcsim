#include "wperformancequery.h"
#include "wperformancequerymanager.h"

WPerformanceQuery::WPerformanceQuery(const char* func_name) : m_func_name(func_name)
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_counter);
}

WPerformanceQuery::~WPerformanceQuery()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	LONGLONG offset = *reinterpret_cast<LONGLONG*>(&counter) - *reinterpret_cast<LONGLONG*>(&m_counter);
	double time_used = static_cast<double>(offset) / *reinterpret_cast<LONGLONG*>(&m_frequency) * 1000000;

	WPerformanceQueryManager::Ref().AddItem(m_func_name, time_used);
}