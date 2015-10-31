/*
* Copyright (c) 2012,四川川大智胜软件股份有限公司仿真模拟部
* All rights reserved.
*
* 文件名称：CheckTime.h
* 功能介绍：时间统计类，统计代码运行时间
* 当前版本：2.1
* 新 特 性：2.1 （1）在#include "windows.h"前增加#define WIN32_LEAN_AND_MEAN，
*				以解决在与boost asio混用时“WinSock.h has already been included”的错误
*				（2）修改部分注释，使其表意更准确
*
*			2.0 （1）适用于多线程
* 作    者：lijin
* 完成日期：2012年10月24日
*/

#ifndef _CheckTime_H_
#define _CheckTime_H_

#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef pair<LONGLONG, float> TimePair;//<起始时间，流逝时间>
typedef map<string, TimePair> TimeTable;//<代码段名称，<起始时间，流逝时间>>

class CheckTime
{
	//public:
private:
	CheckTime();

public:
	static CheckTime * GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CheckTime;
		}
		return m_pInstance;
	}

	static TimeTable& GetTimeTable()
	{
		return m_timeTable;
	}

	static void ClearTimeTable()
	{
		m_timeTable.clear();
	}

	static void PrintTimeTable();
	static void Begin(string func_name, bool b_addin_table = true);
	static void End(string func_name);// returns time in microseconds

private:
	//static void Reset();
	//static float GetTime(bool reset); // returns time in seconds

protected:
	static LONGLONG m_CounterFrequency;
	static LONGLONG m_ResetTime;

private:
	static CheckTime * m_pInstance;
	static TimeTable m_timeTable;
	static bool m_bAddInTable;
};

#endif   // _CheckTime_H_
