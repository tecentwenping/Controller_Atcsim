#include <fstream>
#include <vector>
#include "wperformancequerymanager.h"

WPerformanceQueryManager::~WPerformanceQueryManager()
{
}

void WPerformanceQueryManager::Clear()
{
	m_mmp.clear();
}

void WPerformanceQueryManager::AddItem(const char* func_name, double time_used)
{
	m_mmp.insert(std::make_pair(func_name, time_used));
}

std::multimap<const char*, double> WPerformanceQueryManager::GetData() const 
{ 
	return m_mmp;
}