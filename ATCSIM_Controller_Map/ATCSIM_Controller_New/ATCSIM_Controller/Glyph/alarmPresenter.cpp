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

	////按优先级高到低将紧急类型告警添加到vector中（HJ > EM > CF）
	////便于以后判断告警时从高到低进行判断
	//m_vEmgAlarm.push_back(std::make_pair(HJ_ALARM, L"HIJ "));
	//m_vEmgAlarm.push_back(std::make_pair(EM_ALARM, L"EMG "));
	//m_vEmgAlarm.push_back(std::make_pair(CF_ALARM, L"RAD "));

	////按优先级高到低将一般类型告警添加到vector中（STCA > DAIW > MSAW > CLAM > RAM > DUPE）
	////便于以后判断告警时从高到低进行判断
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
//	//先将其加入到确认列表中，然后再在闪烁列表中找到
//	//对应的飞机ＩＤ,将其从列表中移除，并设定对应飞机的告警颜色
//	//及标牌边框颜色为黄色,防止其他线程也在调用这两个容器，加锁
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
//	//找到对应图元将其告警字段和边框改为黄色
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
////现在标牌上主要显示两类告警，一类是HJ，EM，CF紧急类告警，剩下的
////为另一类（一般告警），只显示每一类告警中出现的优先级最高的告警，
////如果有一般类型没紧急类型，紧急类型的显示位置要以空格占据，所以
////为了处理方便从中取出WLabelFields::emg字段表示紧急告警，WLabelFields::stca字段
////表示一般告警，确认了的告警或预警它不闪烁，只告警闪烁
//void AlarmPresenter::ProcessAlarm(ControllerAcftInfo* acftInfo)
//{
//	if (!acftInfo)
//	{
//		return;
//	}
//	AircraftAlarmInfo& alarmInfo = *acftInfo->GetAlarmInfoPtr();
//	int acftID = acftInfo->GetTrackNo();
//
//	//判断告警是否有更新，有的话就继续
//	if (m_mlastAlarmInfo[acftID].first == alarmInfo.m_eAlarmFlag)
//	{
//		return;
//	}
//	m_mlastAlarmInfo[acftID].first = alarmInfo.m_eAlarmFlag;
//
//	//去掉确认告警中已经消失的确认告警
//	m_mAckAlarmInfo[acftID] = m_mAckAlarmInfo[acftID] & alarmInfo.m_eAlarmFlag;
//
//
//	std::wstring sEmgText; //存放紧急告警显示内容
//	std::wstring sComText; //存放一般告警显示内容
//	int emgAlarm;
//	int comAlarm;
//	bool bEqualLastEmgAlarm = false;  //紧急类型显示是否与上次显示相同
//	bool bEqualLastComAlarm = false;  //一般类型显示是否与上次相同
//
//	//先获取紧急告警显示内容
//	CalculateDisPalyAlarm(alarmInfo.m_eAlarmFlag, emgAlarm, sEmgText, true);
//
//	//获取一般告警显示的内容
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
//	//处理ＲＶＳＭ告警
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
//	//如果显示内容与上次一样就返回来
//	if ((m_mlastAlarmInfo[acftID].second.m_iEmgAlarm == emgAlarm) 
//		&& (m_mlastAlarmInfo[acftID].second.m_iComAlarm == comAlarm))
//	{
//		return;
//	}
//
//	m_mlastAlarmInfo[acftID].second.m_iEmgAlarm = emgAlarm; 
//	m_mlastAlarmInfo[acftID].second.m_iComAlarm = comAlarm;
//
//	//只存在一般告警，紧急告警类型位置就以空格站位
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
//	//如果显示的告警为确认了的告警，就不把它添加到用于处理标牌闪烁的逻辑中
//	if ((emgAlarm & m_mAckAlarmInfo[acftID]) != 0 )
//	{
//		emgAlarm = int(NO_ALARM);
//		fd->SetTextPen(pen);
//	}
//
//	fd = &fields[WLabelFields::stca];
//	fd->SetText(sComText);
//
//	//如果显示的一般告警已确认或为预警，就不把它加入闪烁列表中
//	if ((comAlarm & m_mAckAlarmInfo[acftID]) || (comAlarm & (STCA_PREALARM | DAIW_PREALARM | MSAW_PREALARM)))
//	{
//		comAlarm = NO_ALARM;
//		fd->SetTextPen(pen);
//	}
//
//	//是否添加边框颜色
//	bool bSetBoundingColor = false;
//	
//	//如果没有需要闪烁的告警类型，就将其从中移除
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
//	//设置边框显示与否，如果边框不闪烁，则设置边框的颜色为黄色
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
////闪烁处理函数，由定时器调用，改变闪烁字段及边框的颜色
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
//		//设置画笔的颜色
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

	