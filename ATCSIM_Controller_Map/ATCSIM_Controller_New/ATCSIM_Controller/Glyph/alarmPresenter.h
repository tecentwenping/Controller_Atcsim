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

	//���������洴��һ���ɻ�ͼԪ����ӵ�map��
	//���ڴ���澯�߼�ʱ��ȡ��Ӧ��ͼԪ
	void AddAircraftGlyph(int iId, WAircraftGlyph* glyph);

private:
	//��������澯��һ��澯��ʾ����
	void CalculateDisPalyAlarm(int iAlarm, int &iDisAlarm, std::wstring &sDis, bool bEmg);
private:
	struct ST_ALARM
	{
		int m_iEmgAlarm;  //��Ž����澯����
		int m_iComAlarm;  //���һ��澯����
		ST_ALARM()
		{
			m_iEmgAlarm = 0;
			m_iComAlarm = 0;
		}
	};
private:
	std::map<int, int> m_mAckAlarmInfo;  //��ŷɻ�ID��澯��intֵ
	std::map<int, ST_ALARM> m_mAlarm;    //���ڴ����Ҫ��˸����ķɻ�ID�͸澯����
	std::map<int, WAircraftGlyph*> m_mAircraftGlyph;
	std::map<int, std::pair<int, ST_ALARM> > m_mlastAlarmInfo;//����ϴθ澯��ID��澯ֵ����ʾ�澯���͵Ķ�Ӧ��ϵ
	std::vector<std::pair<int, std::wstring> > m_vEmgAlarm; //��Ž����澯�������Ӧ����ʾ���ݶ�
	std::vector<std::pair<int, std::wstring> > m_vComAlarm; //���һ�����͸澯�������Ӧ����ʾ����
	boost::shared_mutex         m_alarmLock;
	bool m_bChangedAlarmColor;
};

#endif