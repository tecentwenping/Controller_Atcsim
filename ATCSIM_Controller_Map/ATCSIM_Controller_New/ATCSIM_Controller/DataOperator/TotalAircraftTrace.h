#ifndef TOTALAIRCRAFTTRACE_H
#define TOTALAIRCRAFTTRACE_H

#include <hash_map>
#include "AircraftTrace.h"
//保存所有飞行计划数据
class TotalAircraftTrace 
{
public:
	typedef stdext::hash_map<int,AircraftTrace*> hmFplTraces;

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

	void UpdateTracksType(int nRadarType);

	void GetTraces(hmFplTraces& traces);
	hmFplTraces& GetTraces(){return m_hmTraces;}
	void ClearTraces();
private:
	hmFplTraces m_hmTraces;
	AircraftTrace* m_pCurTraces;
	
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
	m_hmTraces[nTraceNo] = pTrace;
}

#endif // TOTALAIRCRAFTTRACE_H
