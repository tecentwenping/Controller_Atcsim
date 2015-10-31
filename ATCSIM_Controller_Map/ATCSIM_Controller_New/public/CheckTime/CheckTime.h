/*
* Copyright (c) 2012,�Ĵ�������ʤ����ɷ����޹�˾����ģ�ⲿ
* All rights reserved.
*
* �ļ����ƣ�CheckTime.h
* ���ܽ��ܣ�ʱ��ͳ���࣬ͳ�ƴ�������ʱ��
* ��ǰ�汾��2.1
* �� �� �ԣ�2.1 ��1����#include "windows.h"ǰ����#define WIN32_LEAN_AND_MEAN��
*				�Խ������boost asio����ʱ��WinSock.h has already been included���Ĵ���
*				��2���޸Ĳ���ע�ͣ�ʹ������׼ȷ
*
*			2.0 ��1�������ڶ��߳�
* ��    �ߣ�lijin
* ������ڣ�2012��10��24��
*/

#ifndef _CheckTime_H_
#define _CheckTime_H_

#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef pair<LONGLONG, float> TimePair;//<��ʼʱ�䣬����ʱ��>
typedef map<string, TimePair> TimeTable;//<��������ƣ�<��ʼʱ�䣬����ʱ��>>

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
