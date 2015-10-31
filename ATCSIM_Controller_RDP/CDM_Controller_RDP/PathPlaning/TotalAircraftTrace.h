#ifndef TOTALAIRCRAFTTRACE_H
#define TOTALAIRCRAFTTRACE_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: TotalAircraftTrace
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/11/12
  ����  ����:  ���ļ���������TotalAircraftTrace�����ౣ�������еķ��мƻ�����
  ����  ����:   
**************************************************************************/

#include <hash_map>
#include <vector>
#include "wworldpoint.h"
#include <deque>
#include <boost/thread/shared_mutex.hpp>
class AircraftTrace;
class TotalAircraftTrace 
{
public:
	typedef stdext::hash_map<int,AircraftTrace*> hmFplTraces;
	typedef stdext::hash_map<int,std::vector<WPointF> > hmFplTracePoint;//��ź������ϣ��
	typedef stdext::hash_map<int,std::deque<WPointF> > hmFplTracePoint1;
	typedef std::map<int,AircraftTrace*> mpFplTraces;

public:
	TotalAircraftTrace();
	~TotalAircraftTrace();
public:
	void SetCurAircraftTrace(int iID);

	AircraftTrace* GetCurAircraftTrace();

	template<class T>
	T* GetAircraftTrace(int nTraceNo);

	AircraftTrace* GetAircraftTrace(int nTraceNo);

	template<class T>
	void UpdateAircraftTrace(int nTraceNo,T* pTrace);
	//void UpdateAircraftTracePoint(int iTraceno,const std::vector<WPointF>& vTracePoint);
	//void GetAircraftTracePoint( int nTraceno,std::vector<WPointF>& tracePoint);
	//void GetAircraftTracePoint( hmFplTracePoint& hmTracePoint);

	void UpdateTracksType(int nRadarType);

	void GetTraces(hmFplTraces& traces);
	void ClearTraces();

	/////////////////////////////////////////////
	void UpdateAircraftTracePoint1(int iTraceno,const std::deque<WPointF>& dTracePoint);
	void GetAircraftTracePoint1(int iTraceno,std::deque<WPointF>& dTracePoint);
	void GetAircraftTracePoint1( hmFplTracePoint1& hmTracePoint);
private:
	static hmFplTraces m_hmTraces;
	AircraftTrace* m_pCurTraces;
	hmFplTracePoint m_hmTracePoint;
	mpFplTraces	m_mpTraces;

	hmFplTracePoint1 m_hmTracePoint1;

	
};
template<class T>
T * TotalAircraftTrace::GetAircraftTrace(int nTraceNo)
{
	hmFplTraces::iterator iter = m_hmTraces.find(nTraceNo);
	if (iter != m_hmTraces.end())
	{
		return dynamic_cast<T*>(iter->second);
	}
	return NULL;
}
template<class T>
void TotalAircraftTrace::UpdateAircraftTrace(int nTraceNo, T* pTrace)
{
	//boost::shared_mutex vMutex;
	///vMutex.lock();
	m_hmTraces[nTraceNo] = pTrace;
	//vMutex.unlock();
}
#endif // TOTALAIRCRAFTTRACE_H
