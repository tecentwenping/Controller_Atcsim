#include "ControllerAcftInfo.h"
#include "AircraftInfo.h"
#include <boost/foreach.hpp>
#include "Manager/DataManager.h"
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
void ControllerAcftInfo::UpdateStaticFpl( const PublicDataStruct::ST_FDP_FLIGHTPLAN_STATIC& info )
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
void ControllerAcftInfo::UpdateDynamicFpl( const PublicDataStruct::ST_FDP_FLIGHTPLAN_DYNAMIC& info )
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

// std::vector<PublicDataStruct::TAG_STRIP_POINT>& ControllerAcftInfo::GetAcftRoute()
// {
// 	//return m_DynamicFpl.stripPoints;
// }

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
	return m_DynamicFpl.PairStatus ==  PublicDataStruct::AUTOCOUPLE || m_DynamicFpl.PairStatus == PublicDataStruct::MANUALCOUPLE;
}


/**
\brief     IsADEPInFDRG
\Access    public 
\retval    bool
\remark     
*/
bool ControllerAcftInfo::IsADEPInFDRG()
{
	PublicDataStruct::CPL_TYPE cplType = m_StaticFpl.CplType;

	return(cplType == PublicDataStruct::EXTERNAL_OUTBD || \
		   cplType == PublicDataStruct::DOMES_OUTBD  ||\
		   cplType == PublicDataStruct::BYPASS ||\
		   cplType == PublicDataStruct::EXTERNAL_ADP_OUTBD ||\
		   cplType == PublicDataStruct::DOMESTIC ||\
		   cplType == PublicDataStruct::DOMES_BYPASS ||\
		   cplType == PublicDataStruct::DOMES_INBD);
}
/**
\brief     GetPlanStatus
\Access    public 
\retval    PLAN_STATUS
\remark     
*/
PublicDataStruct::PLAN_STATUS ControllerAcftInfo::GetPlanStatus()
{
	return m_DynamicFpl.CplStatus;
}


/**
\brief     GetHmiStat
\Access    public 
\retval    HMI_STAT
\remark     
*/
PublicDataStruct::HMI_STAT ControllerAcftInfo::GetHmiStat()
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
PublicDataStruct::HMI_STAT ControllerAcftInfo::ComputeHMIState()
{
	PublicDataStruct::CPL_TYPE    nFplType    = m_StaticFpl.CplType;
	PublicDataStruct::PLAN_STATUS nPlanStatus = m_DynamicFpl.CplStatus;
	PublicDataStruct::HMI_STAT  nHmiStat;
	switch(nPlanStatus)
	{
	case PublicDataStruct::FUTR:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		return nHmiStat;
	case PublicDataStruct::NACT:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		return nHmiStat;
	case PublicDataStruct::FIN:
		nHmiStat = PublicDataStruct::HMI_NONE;
		return nHmiStat;
	case PublicDataStruct::CNL:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		return nHmiStat;
	}
	bool bNextSecInPos = false;   //下一个扇区是否归本席位管制
	bool bTwrSec       = false;   //本席位管制的扇区手否有TWR扇区
	bool bCurSecInPos  = false;   //当前扇区是否归本席位管制
	bool bCtrlSecInPos = false;   //控制扇区是否归本席位管制
	bool bAcpSecInPos  = false;   //移交接受扇区扇区是否归本席位管制

	//改变HMI状态判断方法，基于全部基于扇区关系判断

	vstrings vSelfCtrlSector;
	//theData::instance().GetBaseCDataManager()->GetSectorData()

	//theData::instance().GetBaseCDataManager()->GetSelfSectors(vSelfCtrlSector);
	
	//根据雷达模拟机中扇区进行计算
	if (!vSelfCtrlSector.empty())
	{
		//2.判读下一个扇区是否归本席位管制
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
			//当前扇区归本席位管制
			if (m_DynamicFpl.CurSec == value)
			{
				bCurSecInPos = true;
			}
			//控制扇归本席位管制
			if (m_DynamicFpl.CtrlSec == value)
			{
				bCtrlSecInPos = true;
			}
			//移交接受扇归本席位管制
			if (m_DynamicFpl.AcpSec == value)
			{
				bAcpSecInPos = true;
			}

			//判断本席位管制的飞机是否有TWR类型
			//SEC_TYPE type = CCDataManager::Instance()->GetBaseCDataManager()->GetSectorTypeBySecName(iter->c_str());
// 			if (TWR == type)
// 			{
// 				bTwrSec = true;
// 			}
		}
	}

	//修改判断逻辑 
	switch(nPlanStatus)
	{
	case PublicDataStruct::FUTR:	
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		break;
	case PublicDataStruct::NACT:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		break;
	case PublicDataStruct::PREA:
		if(bNextSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_PREA;	
		}
		else if((nFplType == PublicDataStruct::EXTERNAL_OUTBD || nFplType == PublicDataStruct::DOMES_OUTBD ) && bTwrSec)
		{
			nHmiStat = PublicDataStruct::HMI_PREA;	
		}
		else
		{
			nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		}
		break;
	case PublicDataStruct::COOR:
		if(bNextSecInPos)			   
		{
			nHmiStat = PublicDataStruct::HMI_ANNOUNCE;	
		}
		else
		{
			nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		}
		break;

	case PublicDataStruct::CONT:
		if(bCtrlSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_JURI;
		}
		else if(bNextSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_ANNOUNCE;
		}	
		else		
		{
			nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		}
		break;
	case PublicDataStruct::HAND:
		if(bCtrlSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_HND_OUT;
		}
		else if(bAcpSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_HND_IN;
		}
		else if(bNextSecInPos)
		{
			nHmiStat = PublicDataStruct::HMI_ANNOUNCE;
		}
		else
		{
			nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		}
		break;
	case PublicDataStruct::FIN:
		nHmiStat = PublicDataStruct::HMI_NONE;
		break;
	case PublicDataStruct::CNL:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
		break;
	default:
		nHmiStat = PublicDataStruct::HMI_UNCONCERN;
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













