#ifndef ALARMPRESENTER_H
#define ALARMPRESENTER_H

#include <map>
#include <vector>
#include <boost/thread/shared_mutex.hpp>
class ControllerAcftInfo;
class WAircraftGlyph;
//#define towstring boost::lexical_cast<std::wstring>
class AlarmPresenter
{
public:
	AlarmPresenter();
	~AlarmPresenter();
public:
	void SetAckAlarmInfo(ControllerAcftInfo* acftInfo);
	void ProcessAlarm(ControllerAcftInfo* acftInfo);
	void Coruscate();
	void ClearLocalData();

	//用于在外面创建一个飞机图元后，添加到map中
	//便于处理告警逻辑时获取对应的图元
	void AddAircraftGlyph(int iId, WAircraftGlyph* glyph);

private:
	//计算紧急告警或一般告警显示内容
	void CalculateDisPalyAlarm(int iAlarm, int &iDisAlarm, std::wstring &sDis, bool bEmg);
private:
	struct ST_ALARM
	{
		int m_iEmgAlarm;  //存放紧急告警类型
		int m_iComAlarm;  //存放一般告警类型
		ST_ALARM()
		{
			m_iEmgAlarm = 0;
			m_iComAlarm = 0;
		}
	};
private:
	std::map<int, int> m_mAckAlarmInfo;  //存放飞机ID与告警的int值
	std::map<int, ST_ALARM> m_mAlarm;    //用于存放需要闪烁处理的飞机ID和告警类型
	std::map<int, WAircraftGlyph*> m_mAircraftGlyph;
	std::map<int, std::pair<int, ST_ALARM> > m_mlastAlarmInfo;//存放上次告警的ID与告警值及显示告警类型的对应关系
	std::vector<std::pair<int, std::wstring> > m_vEmgAlarm; //存放紧急告警类型与对应的显示内容对
	std::vector<std::pair<int, std::wstring> > m_vComAlarm; //存放一般类型告警类型与对应的显示内容
	boost::shared_mutex         m_alarmLock;
	bool m_bChangedAlarmColor;
};

#endif