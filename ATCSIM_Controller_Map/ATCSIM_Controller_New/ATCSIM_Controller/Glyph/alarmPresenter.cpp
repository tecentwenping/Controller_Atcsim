#include "alarmPresenter.h"
#include "wlabelformat.h"
#include "CLabelManager.h"
#include "AircraftalarmInfo.h"
#include "MapManager.h"
#include "waircraftglyph.h"
#include <boost/shared_ptr.hpp>
#include "Timer.h"
//#include "ControllerAcftInfo.h"
#include "wlabelformat.h"
//#include "CMainApp.h"


#define towstring boost::lexical_cast<std::wstring>

static const WSizeF EMPTY_SIZE;
static const std::wstring EMPTY_WSTR;
static const std::wstring CONST_HIJ(L"HIJ ");
static const std::wstring CONST_RAD(L"RAD ");
static const std::wstring CONST_EMG(L"EMG ");

static const std::wstring CONST_STCA(L"STCA ");
static const std::wstring CONST_DAIW(L"DAIW ");
static const std::wstring CONST_MSAW(L"MSAW ");

static const std::wstring CONST_PRE_STCA(L"PSTCA ");
static const std::wstring CONST_PRE_DAIW(L"PDAIW ");
static const std::wstring CONST_PRE_MSAW(L"PMSAW ");

static const std::wstring CONST_CLAM(L"CLAM ");
static const std::wstring CONST_RAM(L"RAM ");

static const std::wstring CONST_DUPE(L"DUPE ");
static const std::wstring CONST_RVSM(L"X ");

static const WColor RED(255, 0, 0);
static const WColor YELLOW(255, 255, 0);



AlarmPresenter::AlarmPresenter()
{
	//m_mAckAlarmInfo.clear();
	//m_mAlarm.clear();
	//m_mAircraftGlyph.clear();
	//m_mlastAlarmInfo.clear();
	//theApp::instance().GetTimerPtr()->addTimer(boost::bind(&AlarmPresenter::Coruscate, this), 1000);
	//m_bChangedAlarmColor = false;
	//m_vEmgAlarm.clear();
	//m_vComAlarm.clear();

	////�����ȼ��ߵ��ͽ��������͸澯��ӵ�vector�У�HJ > EM > CF��
	////�����Ժ��жϸ澯ʱ�Ӹߵ��ͽ����ж�
	//m_vEmgAlarm.push_back(std::make_pair(HJ_ALARM, L"HIJ "));
	//m_vEmgAlarm.push_back(std::make_pair(EM_ALARM, L"EMG "));
	//m_vEmgAlarm.push_back(std::make_pair(CF_ALARM, L"RAD "));

	////�����ȼ��ߵ��ͽ�һ�����͸澯��ӵ�vector�У�STCA > DAIW > MSAW > CLAM > RAM > DUPE��
	////�����Ժ��жϸ澯ʱ�Ӹߵ��ͽ����ж�
	//m_vComAlarm.push_back(std::make_pair(STCA_PREALARM, L"PSTCA "));
	//m_vComAlarm.push_back(std::make_pair(STCA_ALARM, L"STCA "));
	//m_vComAlarm.push_back(std::make_pair(DAIW_PREALARM, L"PDAIW "));
	//m_vComAlarm.push_back(std::make_pair(DAIW_ALARM, L"DAIW "));
	//m_vComAlarm.push_back(std::make_pair(MSAW_PREALARM, L"PMSAW "));
	//m_vComAlarm.push_back(std::make_pair(MSAW_ALARM, L"MSAW "));
	//m_vComAlarm.push_back(std::make_pair(CLAM_ALARM, L"CLAM "));
	//m_vComAlarm.push_back(std::make_pair(RAM_ALARM, L"RAM "));
	//m_vComAlarm.push_back(std::make_pair(DUPE_ALARM, L"DUPE "));
}

AlarmPresenter::~AlarmPresenter()
{
}

void AlarmPresenter::SetAckAlarmInfo(ControllerAcftInfo* acftInfo)
{
//	if (acftInfo->GetAlarmInfoPtr()->m_eAlarmFlag == 0)
//	{
//		return;
//	}
//
//	int iId = acftInfo->GetTrackNo();
//	WAircraftGlyph * traceGlyph = NULL;
//
//	//�Ƚ�����뵽ȷ���б��У�Ȼ��������˸�б����ҵ�
//	//��Ӧ�ķɻ��ɣ�,������б����Ƴ������趨��Ӧ�ɻ��ĸ澯��ɫ
//	//�����Ʊ߿���ɫΪ��ɫ,��ֹ�����߳�Ҳ�ڵ�������������������
//	m_alarmLock.lock();
//	m_mAckAlarmInfo[iId] = acftInfo->GetAlarmInfoPtr()->m_eAlarmFlag;
//	m_mAlarm.erase(iId);
//	BOOST_AUTO(iter, m_mAircraftGlyph.find(iId));
//	if (iter == m_mAircraftGlyph.end())
//	{
//		traceGlyph = NULL;
//	}
//	else
//	{
//		traceGlyph = iter->second;
//	}
//	m_alarmLock.unlock();
//
//	if (traceGlyph == NULL)
//	{
//		return;
//	}
//	//�ҵ���ӦͼԪ����澯�ֶκͱ߿��Ϊ��ɫ
//	WLabelFields& fields = *CLabelManager::Instance().GetFields(traceGlyph);
//	WLabelField* fd = 0;
//	fd = &fields[WLabelFields::emg];
//	WPen pen = fd->GetTextPen();
//	pen.setColor(YELLOW);
//	fd->SetTextPen(pen);
//	fd = &fields[WLabelFields::stca];
//	fd->SetTextPen(pen);
//	WAircraftGlyph::data_type& d = *traceGlyph->data();
//	d.m_penBounding = pen;
//
//	CLabelManager::Instance().LogicProcFormat(traceGlyph);
//
//	CLabelManager::Instance().UpdateLabel(traceGlyph);
//
//}
//
//
////���ڱ�������Ҫ��ʾ����澯��һ����HJ��EM��CF������澯��ʣ�µ�
////Ϊ��һ�ࣨһ��澯����ֻ��ʾÿһ��澯�г��ֵ����ȼ���ߵĸ澯��
////�����һ������û�������ͣ��������͵���ʾλ��Ҫ�Կո�ռ�ݣ�����
////Ϊ�˴��������ȡ��WLabelFields::emg�ֶα�ʾ�����澯��WLabelFields::stca�ֶ�
////��ʾһ��澯��ȷ���˵ĸ澯��Ԥ��������˸��ֻ�澯��˸
//void AlarmPresenter::ProcessAlarm(ControllerAcftInfo* acftInfo)
//{
//	if (!acftInfo)
//	{
//		return;
//	}
//	AircraftAlarmInfo& alarmInfo = *acftInfo->GetAlarmInfoPtr();
//	int acftID = acftInfo->GetTrackNo();
//
//	//�жϸ澯�Ƿ��и��£��еĻ��ͼ���
//	if (m_mlastAlarmInfo[acftID].first == alarmInfo.m_eAlarmFlag)
//	{
//		return;
//	}
//	m_mlastAlarmInfo[acftID].first = alarmInfo.m_eAlarmFlag;
//
//	//ȥ��ȷ�ϸ澯���Ѿ���ʧ��ȷ�ϸ澯
//	m_mAckAlarmInfo[acftID] = m_mAckAlarmInfo[acftID] & alarmInfo.m_eAlarmFlag;
//
//
//	std::wstring sEmgText; //��Ž����澯��ʾ����
//	std::wstring sComText; //���һ��澯��ʾ����
//	int emgAlarm;
//	int comAlarm;
//	bool bEqualLastEmgAlarm = false;  //����������ʾ�Ƿ����ϴ���ʾ��ͬ
//	bool bEqualLastComAlarm = false;  //һ��������ʾ�Ƿ����ϴ���ͬ
//
//	//�Ȼ�ȡ�����澯��ʾ����
//	CalculateDisPalyAlarm(alarmInfo.m_eAlarmFlag, emgAlarm, sEmgText, true);
//
//	//��ȡһ��澯��ʾ������
//	CalculateDisPalyAlarm(alarmInfo.m_eAlarmFlag, comAlarm, sComText, false);
//
//	WAircraftGlyph *traceGlyph = NULL;
//	m_alarmLock.lock();
//	BOOST_AUTO(iter, m_mAircraftGlyph.find(acftID));
//	if (iter == m_mAircraftGlyph.end())
//	{
//		traceGlyph = NULL;	
//	}
//	else
//	{
//		traceGlyph = iter->second;
//	}
//	m_alarmLock.unlock();
//
//	if (traceGlyph == NULL)
//	{
//		return;
//	}
//	WLabelFields& fields = *CLabelManager::Instance().GetFields(traceGlyph);
//	WLabelField* fd = 0;
//
//	//����ң֣ӣ͸澯
//	fd = &fields[WLabelFields::rvsm];
//	WPen pen = fd->GetTextPen();
//	if (alarmInfo.m_eAlarmFlag & RVSM_ALARM)
//	{
//		pen.setColor(RED);
//	}
//	else
//	{
//		pen.setColor(YELLOW);
//	}
//	fd->SetTextPen(pen);
//
//
//	//�����ʾ�������ϴ�һ���ͷ�����
//	if ((m_mlastAlarmInfo[acftID].second.m_iEmgAlarm == emgAlarm) 
//		&& (m_mlastAlarmInfo[acftID].second.m_iComAlarm == comAlarm))
//	{
//		return;
//	}
//
//	m_mlastAlarmInfo[acftID].second.m_iEmgAlarm = emgAlarm; 
//	m_mlastAlarmInfo[acftID].second.m_iComAlarm = comAlarm;
//
//	//ֻ����һ��澯�������澯����λ�þ��Կո�վλ
//	if ((sEmgText.length() == 0) && (sComText.length() != 0))
//	{
//		sEmgText = towstring("   ");
//	}
//
//
//	fd = &fields[WLabelFields::emg];
//	fd->SetText(sEmgText);
//	pen = fd->GetTextPen();
//	pen.setColor(YELLOW);
//
//	//�����ʾ�ĸ澯Ϊȷ���˵ĸ澯���Ͳ�������ӵ����ڴ��������˸���߼���
//	if ((emgAlarm & m_mAckAlarmInfo[acftID]) != 0 )
//	{
//		emgAlarm = int(NO_ALARM);
//		fd->SetTextPen(pen);
//	}
//
//	fd = &fields[WLabelFields::stca];
//	fd->SetText(sComText);
//
//	//�����ʾ��һ��澯��ȷ�ϻ�ΪԤ�����Ͳ�����������˸�б���
//	if ((comAlarm & m_mAckAlarmInfo[acftID]) || (comAlarm & (STCA_PREALARM | DAIW_PREALARM | MSAW_PREALARM)))
//	{
//		comAlarm = NO_ALARM;
//		fd->SetTextPen(pen);
//	}
//
//	//�Ƿ���ӱ߿���ɫ
//	bool bSetBoundingColor = false;
//	
//	//���û����Ҫ��˸�ĸ澯���ͣ��ͽ�������Ƴ�
//	if ((emgAlarm == 0) && (comAlarm == 0))
//	{
//		m_alarmLock.lock();
//		m_mAlarm.erase(acftID);
//		m_alarmLock.unlock();
//		bSetBoundingColor = true;
//	}
//	else
//	{
//		m_mAlarm[acftID].m_iEmgAlarm = emgAlarm;
//		m_mAlarm[acftID].m_iComAlarm = comAlarm;
//	}
//
//	//���ñ߿���ʾ�������߿���˸�������ñ߿����ɫΪ��ɫ
//	WAircraftGlyph::data_type& d = *traceGlyph->data();
//	if ((sEmgText.length() != 0) || (sComText.length() != 0))
//	{
//		d.m_bShowBounding = true;
//		if (bSetBoundingColor)
//		{
//			d.m_penBounding = pen;
//		}
//	}
//	else
//	{
//		d.m_bShowBounding = false;
//	}
//
//	CLabelManager::Instance().LogicProcFormat(traceGlyph);
//
//	CLabelManager::Instance().UpdateLabel(traceGlyph);
//}
//
////��˸���������ɶ�ʱ�����ã��ı���˸�ֶμ��߿����ɫ
//void AlarmPresenter::Coruscate()
//{
//	std::map<int, ST_ALARM> mAlarm;
//	std::map<int, WAircraftGlyph*> mAircraftGlyph;
//
//	m_alarmLock.lock();
//	mAlarm = m_mAlarm;
//	mAircraftGlyph = m_mAircraftGlyph;
//	m_alarmLock.unlock();
//
//	typedef BOOST_TYPEOF(*mAlarm.begin()) value_type;
//	
//	m_bChangedAlarmColor = !m_bChangedAlarmColor;
//	BOOST_FOREACH(const value_type& v, mAlarm)
//	{			
//		WAircraftGlyph *traceGlyph = NULL;
//		BOOST_AUTO(iter, mAircraftGlyph.find(v.first));
//		if (iter == mAircraftGlyph.end())
//		{
//			continue;	
//		}
//		traceGlyph = iter->second;
//		if (traceGlyph == NULL)
//		{
//			continue;
//		}
//		
//		WLabelFields& fields = *CLabelManager::Instance().GetFields(traceGlyph);
//		WLabelField* fd = 0;
//
//		fd =  &fields[WLabelFields::emg];
//		WPen pen = fd->GetTextPen();
//		//���û��ʵ���ɫ
//		m_bChangedAlarmColor ? pen.setColor(RED) : pen.setColor(YELLOW);
//
//		if (v.second.m_iEmgAlarm != 0)
//		{
//			fd =  &fields[WLabelFields::emg];
//			fd->SetTextPen(pen);
//		}
//		if (v.second.m_iComAlarm != 0)
//		{
//			fd = &fields[WLabelFields::stca];
//			fd->SetTextPen(pen);
//		}
//
//		WAircraftGlyph::data_type& d = *traceGlyph->data();
//		d.m_penBounding = pen;
//		CLabelManager::Instance().UpdateLabel(traceGlyph);	
//	}

}

/**
\brief     ClearLocalData
\Access    public 
\retval    void
\remark     
*/
void AlarmPresenter::ClearLocalData()
{
	/*m_mAckAlarmInfo.clear();
	m_mAircraftGlyph.clear();
	m_mAlarm.clear();
	m_mlastAlarmInfo.clear();*/
}

/**
\brief     AddAircraftGlyph
\Access    public 
\param    int iId
\param    WAircraftGlyph * gGlyph
\retval    void
\remark     
*/
void AlarmPresenter::AddAircraftGlyph(int iId, WAircraftGlyph* glyph)
{
	/*m_alarmLock.lock();
	m_mAircraftGlyph.insert(make_pair(iId, glyph));
	m_alarmLock.unlock();*/
}

void AlarmPresenter::CalculateDisPalyAlarm(int iAlarm, int &iDisAlarm, std::wstring &sDis, bool bEmg)
{
	/*std::vector<std::pair<int, std::wstring> >::iterator iterAlarm;
	std::vector<std::pair<int, std::wstring> >::iterator iterEnd;
	if (bEmg)
	{
		iterAlarm = m_vEmgAlarm.begin();
		iterEnd = m_vEmgAlarm.end();
	}
	else
	{
		iterAlarm = m_vComAlarm.begin();
		iterEnd = m_vComAlarm.end();
	}
	for (; iterAlarm != iterEnd; ++iterAlarm)
	{
		if (iterAlarm->first & iAlarm)
		{
			iDisAlarm = iterAlarm->first;
			sDis = iterAlarm->second;
			break;
		}
	}
	if (iterAlarm == iterEnd)
	{
		iDisAlarm = 0;
		sDis = EMPTY_WSTR;
	}*/
}

	