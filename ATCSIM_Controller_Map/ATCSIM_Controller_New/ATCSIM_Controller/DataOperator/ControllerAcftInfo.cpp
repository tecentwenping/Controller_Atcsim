#include "ControllerAcftInfo.h"
#include "AircraftInfo.h"
#include <boost/foreach.hpp>
/**
\brief     ControllerAcftInfo
\Access    public 
\retval    
\remark     
*/
ControllerAcftInfo::ControllerAcftInfo()
:m_AcftType(ACFT_NORMAL)
{

}

ControllerAcftInfo::ControllerAcftInfo( const ControllerAcftInfo& rhs )
{
     m_DynamicFpl = rhs.m_DynamicFpl;
	 m_StaticFpl  = rhs.m_StaticFpl;
	 m_hmiStat	  = rhs.m_hmiStat;
	 m_AcftType	  = rhs.m_AcftType;
}


/**
\brief     ~ControllerAcftInfo
\Access    public 
\retval    
\remark     
*/
ControllerAcftInfo::~ControllerAcftInfo()
{

}


/**
\brief     UpdateStaticFpl
\Access    public 
\param     const ST_FDP_FLIGHTPLAN_STATIC & info
\retval    void
\remark     
*/
void ControllerAcftInfo::UpdateStaticFpl( const ST_FDP_FLIGHTPLAN_STATIC& info )
{
	m_StaticFpl = info;
}


/**
\brief     UpdateDynamicFpl
\Access    public 
\param     const ST_FDP_FLIGHTPLAN_DYNAMIC & info
\retval    void
\remark     
*/
void ControllerAcftInfo::UpdateDynamicFpl( const ST_FDP_FLIGHTPLAN_DYNAMIC& info )
{
	m_DynamicFpl = info;
	m_hmiStat = ComputeHMIState();
}


int ControllerAcftInfo::GetTrackNo()
{
	return m_DynamicFpl.TrackNo;
}


std::string& ControllerAcftInfo::GetMid()
{
	return m_StaticFpl.curMID;
}

std::string& ControllerAcftInfo::GetArrRunwayName()
{

	return m_StaticFpl.ARWY;
}

std::vector<TAG_STRIP_POINT>& ControllerAcftInfo::GetAcftRoute()
{
	return m_DynamicFpl.stripPoints;
}

/**
\brief     GetCallsignName
\Access    public 
\retval    std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetCallsignName()
{
	return m_StaticFpl.CallSign;
}

/**
\brief     GetTurbo
\Access    virtual public 
\retval    std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetTurbo()
{
	return m_StaticFpl.Turbo;
}

/**
\brief     GetArrAerodrome
\Access    virtual public 
\retval    std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetArrAerodrome()
{
	return m_StaticFpl.ADARR;
}

/**
\brief     GetAcftType
\Access    virtual public 
\retval    std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetAcftType()
{
	return m_StaticFpl.AcftType;
}


/**
\brief     GetCoupleFlag
\Access    public 
\retval    bool
\remark     
*/
bool ControllerAcftInfo::GetCoupleFlag()
{
	return m_DynamicFpl.PairStatus ==  AUTOCOUPLE || m_DynamicFpl.PairStatus == MANUALCOUPLE;
}


/**
\brief     IsADEPInFDRG
\Access    public 
\retval    bool
\remark     
*/
bool ControllerAcftInfo::IsADEPInFDRG()
{
	CPL_TYPE cplType = m_StaticFpl.CplType;

	return(cplType == EXTERNAL_OUTBD || \
		   cplType == DOMES_OUTBD  ||\
		   cplType == BYPASS ||\
		   cplType == EXTERNAL_ADP_OUTBD ||\
		   cplType == DOMESTIC ||\
		   cplType == DOMES_BYPASS ||\
		   cplType == DOMES_INBD);
}
/**
\brief     GetPlanStatus
\Access    public 
\retval    PLAN_STATUS
\remark     
*/
PLAN_STATUS ControllerAcftInfo::GetPlanStatus()
{
	return m_DynamicFpl.CplStatus;
}


/**
\brief     GetHmiStat
\Access    public 
\retval    HMI_STAT
\remark     
*/
HMI_STAT ControllerAcftInfo::GetHmiStat()
{
	return m_hmiStat;
}


/**
\brief     GetHoldPlanFlag
\Access    public 
\retval    bool
\remark     
*/
bool ControllerAcftInfo::GetHoldPlanFlag()
{
	return !m_DynamicFpl.HoldPoint.empty();
}

/**
\brief     GetAcftPlanType
\Access    public 
\retval    ACFTTYPE
\remark     
*/
ACFTTYPE ControllerAcftInfo::GetAcftPlanType()
{
	return m_AcftType;
}

/**
\brief     GetAtdEmptyFlag
\Access    public 
\retval    bool
\remark     
*/
bool ControllerAcftInfo::GetAtdEmptyFlag()
{
	return m_DynamicFpl.ATD.empty();
}

/**
\brief     ComputeHMIState
\Access    private 
\retval    HMI_STAT
\remark     
*/
HMI_STAT ControllerAcftInfo::ComputeHMIState()
{
	CPL_TYPE    nFplType    = m_StaticFpl.CplType;
	PLAN_STATUS nPlanStatus = m_DynamicFpl.CplStatus;
	HMI_STAT  nHmiStat;
	switch(nPlanStatus)
	{
	case FUTR:
		nHmiStat = HMI_UNCONCERN;
		return nHmiStat;
	case NACT:
		nHmiStat = HMI_UNCONCERN;
		return nHmiStat;
	case FIN:
		nHmiStat = HMI_NONE;
		return nHmiStat;
	case CNL:
		nHmiStat = HMI_UNCONCERN;
		return nHmiStat;
	}
	bool bNextSecInPos = false;   //��һ�������Ƿ�鱾ϯλ����
	bool bTwrSec       = false;   //��ϯλ���Ƶ������ַ���TWR����
	bool bCurSecInPos  = false;   //��ǰ�����Ƿ�鱾ϯλ����
	bool bCtrlSecInPos = false;   //���������Ƿ�鱾ϯλ����
	bool bAcpSecInPos  = false;   //�ƽ��������������Ƿ�鱾ϯλ����

	//�ı�HMI״̬�жϷ���������ȫ������������ϵ�ж�

	vstrings vSelfCtrlSector;
	//theData::instance().GetBaseDataManager()->GetSectorData()

	//theData::instance().GetBaseDataManager()->GetSelfSectors(vSelfCtrlSector);
	
	//�����״�ģ������������м���
	if (!vSelfCtrlSector.empty())
	{
		//2.�ж���һ�������Ƿ�鱾ϯλ����
		BOOST_FOREACH(vstrings::value_type& value, m_DynamicFpl.NextSecs)
		{
			bool bFlag = IsSectorInCtrlSector(value, vSelfCtrlSector);
			if (bFlag)
			{
				bNextSecInPos = true;
				break;
			}
		}

		BOOST_FOREACH(vstrings::value_type& value, vSelfCtrlSector)
		{
			//��ǰ�����鱾ϯλ����
			if (m_DynamicFpl.CurSec == value)
			{
				bCurSecInPos = true;
			}
			//�����ȹ鱾ϯλ����
			if (m_DynamicFpl.CtrlSec == value)
			{
				bCtrlSecInPos = true;
			}
			//�ƽ������ȹ鱾ϯλ����
			if (m_DynamicFpl.AcpSec == value)
			{
				bAcpSecInPos = true;
			}

			//�жϱ�ϯλ���Ƶķɻ��Ƿ���TWR����
			//SEC_TYPE type = CDataManager::Instance()->GetBaseDataManager()->GetSectorTypeBySecName(iter->c_str());
// 			if (TWR == type)
// 			{
// 				bTwrSec = true;
// 			}
		}
	}

	//�޸��ж��߼� 
	switch(nPlanStatus)
	{
	case FUTR:	
		nHmiStat = HMI_UNCONCERN;
		break;
	case NACT:
		nHmiStat = HMI_UNCONCERN;
		break;
	case PREA:
		if(bNextSecInPos)
		{
			nHmiStat = HMI_PREA;	
		}
		else if((nFplType == EXTERNAL_OUTBD || nFplType == DOMES_OUTBD ) && bTwrSec)
		{
			nHmiStat = HMI_PREA;	
		}
		else
		{
			nHmiStat = HMI_UNCONCERN;
		}
		break;
	case COOR:
		if(bNextSecInPos)			   
		{
			nHmiStat = HMI_ANNOUNCE;	
		}
		else
		{
			nHmiStat = HMI_UNCONCERN;
		}
		break;

	case CONT:
		if(bCtrlSecInPos)
		{
			nHmiStat = HMI_JURI;
		}
		else if(bNextSecInPos)
		{
			nHmiStat = HMI_ANNOUNCE;
		}	
		else		
		{
			nHmiStat = HMI_UNCONCERN;
		}
		break;
	case HAND:
		if(bCtrlSecInPos)
		{
			nHmiStat = HMI_HND_OUT;
		}
		else if(bAcpSecInPos)
		{
			nHmiStat = HMI_HND_IN;
		}
		else if(bNextSecInPos)
		{
			nHmiStat = HMI_ANNOUNCE;
		}
		else
		{
			nHmiStat = HMI_UNCONCERN;
		}
		break;
	case FIN:
		nHmiStat = HMI_NONE;
		break;
	case CNL:
		nHmiStat = HMI_UNCONCERN;
		break;
	default:
		nHmiStat = HMI_UNCONCERN;
		break;			
	}
	return nHmiStat;
}

/**
\brief     IsSectorInCtrlSector
\Access    private 
\param     const std::string & sec
\param     const vstrings & vSec
\retval    bool
\remark     
*/
bool ControllerAcftInfo::IsSectorInCtrlSector( const std::string& sec, const vstrings& vSec )
{
	BOOST_FOREACH(const vstrings::value_type& value, vSec)
	{
		if (value == sec)
		{
			return true;
		}
	}
	return false;
}

/**
\brief      GetSSRCode
\Access     public 
\retval     std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetSSRCode()
{
	return m_StaticFpl.ASSR;
}

void ControllerAcftInfo::UpdateHMIState()
{
	m_hmiStat = ComputeHMIState();
}

/**
\brief      GetSectorName
\Access    public 
\retval     std::string&
\remark     
*/
std::string& ControllerAcftInfo::GetSectorName()
{
	return m_DynamicFpl.CurSec;
}













