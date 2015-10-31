#include "FlyPlanInterFace.h"
#include "GetFlyPlanFromDB.h"
#include "SendFlyPlanToRDP.h"
CFlyPlanInterFace::CFlyPlanInterFace()
{
    myInitGetFlyPlanFunc();
}

CFlyPlanInterFace::~CFlyPlanInterFace()
{

}
void CFlyPlanInterFace::myInitGetFlyPlanFunc()
{
	if(! m_pGetFlyPlanFromDB)
	{
		m_pGetFlyPlanFromDB = boost::make_shared<CGetFlyPlanFromDB>();
		if(! m_pSendFlyPlanToRDP)
		{
			m_pSendFlyPlanToRDP = boost::make_shared<CSendFlyPlanToRDP>();
			connect(m_pGetFlyPlanFromDB.get(),SIGNAL(sig_StartSendFlyPlan()),m_pSendFlyPlanToRDP.get(),SLOT(slot_StartSendFlyPlanToRDP()));
		}
		m_pGetFlyPlanFromDB.get()->StartSendFlyPlan();
	}
}
