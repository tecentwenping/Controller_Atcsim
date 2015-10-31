#include "AircraftAlarmInfo.h"
#include "alarm_packet.h"
#include "EnumVarible.h"

AircraftAlarmInfo::AircraftAlarmInfo():m_eAlarmFlag(0),
// SPI(no_warn), HJ(no_warn), CF(no_warn), EM(no_warn),
// STCA(no_warn), MSAW(no_warn), DAIW(no_warn), CLAM(no_warn),
// RAM(no_warn), rvsmAlarm(no_warn),
STCAAlertTime(-1), MSAWAlertTime(-1), DAIWAlertTime(-1), RVSMAlertTime(-1)
{

}


AircraftAlarmInfo::~AircraftAlarmInfo()
{

}


/**
\brief     UpdateAlarmInfo
\Access    public 
\param     const AlarmInfo & alarmInfo
\retval    void
\remark     
*/
void AircraftAlarmInfo::UpdateAlarmInfo( const AlarmInfo& alarmInfo )
{
	m_eAlarmFlag = 0;
	(alarmInfo.AlarmFlag & ALARM_SPI) ? (m_eAlarmFlag |= SPI_ALARM): m_eAlarmFlag;
	(alarmInfo.AlarmFlag & ALARM_HJ)  ? (m_eAlarmFlag |= HJ_ALARM) : m_eAlarmFlag;
	(alarmInfo.AlarmFlag & ALARM_CF)  ? (m_eAlarmFlag |= CF_ALARM) : m_eAlarmFlag;
	(alarmInfo.AlarmFlag & ALARM_EM)  ? (m_eAlarmFlag |= EM_ALARM) : m_eAlarmFlag;

	const int nPreWarnTime = 120; //seconds

	(((alarmInfo.AlarmFlag & ALARM_STCA) && (0 == alarmInfo.STCAAlertTime)) ? (m_eAlarmFlag |= STCA_ALARM) :\
		    (alarmInfo.STCAAlertTime > 0 && alarmInfo.STCAAlertTime <= nPreWarnTime ?(m_eAlarmFlag |= STCA_PREALARM) : m_eAlarmFlag));

	(((alarmInfo.AlarmFlag & ALARM_MSAW) && (0 == alarmInfo.MSAWAlertTime)) ? (m_eAlarmFlag |= MSAW_ALARM) :\
		    (alarmInfo.MSAWAlertTime > 0 && alarmInfo.MSAWAlertTime <= nPreWarnTime ? (m_eAlarmFlag |= MSAW_PREALARM) : m_eAlarmFlag));

	(((alarmInfo.AlarmFlag & ALARM_DAIW) && (0 == alarmInfo.DAIWAlertTime)) ? (m_eAlarmFlag |= DAIW_ALARM) :\
		    (alarmInfo.DAIWAlertTime > 0 && alarmInfo.DAIWAlertTime <= nPreWarnTime ? (m_eAlarmFlag |= DAIW_PREALARM) : m_eAlarmFlag));

	(alarmInfo.AlarmFlag & ALARM_RVSM)  ? (m_eAlarmFlag |= RVSM_ALARM): m_eAlarmFlag;

	(alarmInfo.AlarmFlag & ALARM_CLAM) ? (m_eAlarmFlag |= CLAM_ALARM) : m_eAlarmFlag;

	(alarmInfo.AlarmFlag & ALARM_RAM) ? (m_eAlarmFlag |= RAM_ALARM) : m_eAlarmFlag;

	
}


/**
\brief     AlarmStrings
\Access    public 
\param     std::vector<std::string> & vStrings
\retval    void
\remark    after compute the alarminfo, get the alarm strings;
*/
void AircraftAlarmInfo::AlarmStrings( std::vector<std::string>& vStrings )
{
	vStrings.clear();

	(m_eAlarmFlag & SPI_ALARM) ? vStrings.push_back("SPI") : vStrings;
	(m_eAlarmFlag & HJ_ALARM) ? vStrings.push_back("HIJ") : vStrings;
	(m_eAlarmFlag & CF_ALARM) ? vStrings.push_back("CF")  : vStrings;
	(m_eAlarmFlag & EM_ALARM) ? vStrings.push_back("EMG") : vStrings;
	(m_eAlarmFlag & CLAM_ALARM) ? vStrings.push_back("CLAM"): vStrings;
	(m_eAlarmFlag & RAM_ALARM) ? vStrings.push_back("RAM") : vStrings;

	(m_eAlarmFlag & STCA_ALARM) ? vStrings.push_back("STCA") : (m_eAlarmFlag & STCA_PREALARM ? vStrings.push_back("PSTCA"): vStrings);
	(m_eAlarmFlag & MSAW_ALARM) ? vStrings.push_back("MSAW") : (m_eAlarmFlag & MSAW_PREALARM ? vStrings.push_back("PMSAW"): vStrings);
	(m_eAlarmFlag & DAIW_ALARM) ? vStrings.push_back("DAIW") : (m_eAlarmFlag & DAIW_ALARM ? vStrings.push_back("PDAIW"): vStrings);
}

/**
\brief      GetIsAlarmOrWarnning
\Access    public 
\retval     bool
\remark     
*/
bool AircraftAlarmInfo::GetIsAlarmOrWarnning()
{
	return m_eAlarmFlag != 0;
}

/**
\brief      UpdateSTCAAlarmInfo
\Access     public 
\param      const AlarmInfo & alarmInfo
\retval     void
\remark     
*/
void AircraftAlarmInfo::UpdateSTCAAlarmInfo(const AlarmInfo& alarmInfo)
{
	const int nPreWarnTime = 120; //seconds

	//先将STCA告警和预警位置为0
	m_eAlarmFlag &= (~(STCA_ALARM | STCA_PREALARM));

	(((alarmInfo.AlarmFlag & ALARM_STCA) && (0 == alarmInfo.STCAAlertTime)) ? (m_eAlarmFlag |= STCA_ALARM) :\
		(alarmInfo.STCAAlertTime > 0 && alarmInfo.STCAAlertTime <= nPreWarnTime ? (m_eAlarmFlag |= STCA_PREALARM) : m_eAlarmFlag));

	
}