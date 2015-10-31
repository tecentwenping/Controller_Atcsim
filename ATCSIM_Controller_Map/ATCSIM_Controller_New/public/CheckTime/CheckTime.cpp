#include "CheckTime.h"
#include <iostream>
using namespace std;

LONGLONG CheckTime::m_CounterFrequency = 0;
LONGLONG CheckTime::m_ResetTime = 0;
CheckTime * CheckTime::m_pInstance = NULL;
TimeTable CheckTime::m_timeTable;
bool CheckTime::m_bAddInTable = false;

CheckTime::CheckTime()
{
}

//void CheckTime::Reset()
//{
//	QueryPerformanceCounter((LARGE_INTEGER *) &m_ResetTime);
//}

void CheckTime::Begin(string func_name, bool b_addin_table)
{
	m_bAddInTable = b_addin_table;
	if (!m_bAddInTable)
	{
		return;
	}

	QueryPerformanceFrequency((LARGE_INTEGER *) &m_CounterFrequency);
	//Reset();

	LONGLONG begin_counter;
	QueryPerformanceCounter((LARGE_INTEGER *) &begin_counter);

	TimePair time_pair = make_pair(begin_counter,-1.0f);
	m_timeTable[func_name] = time_pair;
}

void CheckTime::End(string func_name)
{
	//float time_elapse = GetTime(true) * 1000000;//microsecond

	if (!m_bAddInTable)
	{
		return;
	}

	LONGLONG end_counter;
	QueryPerformanceCounter((LARGE_INTEGER *) &end_counter);

	TimeTable::iterator it = m_timeTable.find(func_name);
	if (it != m_timeTable.end())
	{
		TimePair &time_pair = (*it).second;
		LONGLONG diffTime = end_counter - time_pair.first;
		time_pair.second = (float) diffTime / (float) m_CounterFrequency * 1000000;//microsecond
	}
}

//float CheckTime::GetTime(bool reset)
//{
//	// Get current time
//	LONGLONG currentTime;
//	QueryPerformanceCounter((LARGE_INTEGER *) &currentTime);
//
//	// Compute difference from last reset
//	LONGLONG diffTime = currentTime - m_ResetTime;
//
//	// Reset time
//	if (reset)
//		m_ResetTime = currentTime;
//
//	// Return time in seconds
//	return (float) diffTime / (float) m_CounterFrequency;
//}

void CheckTime::PrintTimeTable()
{
	TimeTable::iterator it = m_timeTable.begin();
	for (; it != m_timeTable.end(); ++it)
	{
		TimePair &time_pair = (*it).second;
		cout << "[Func Name] " << (*it).first.c_str() << " [Use Time(um)] " << time_pair.second << endl;
	}
}