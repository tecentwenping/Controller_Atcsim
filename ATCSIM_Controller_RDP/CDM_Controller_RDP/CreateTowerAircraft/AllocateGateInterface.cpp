#include "AllocateGateInterface.h"
#include "InitGateInformation.h"
#include "PublicStruct.h"
#include <iostream>
AllocateGatePInterface::AllocateGatePInterface()
{
	std::cout<<"³ÌÐòÆô¶¯ÖÐ......"<<std::endl;
	initial();
}

AllocateGatePInterface::~AllocateGatePInterface()
{
}
void AllocateGatePInterface::initial()
{
	qRegisterMetaType<CDM_DataStruct::FlyPlanStruct>("CDM_DataStruct::FlyPlanStruct");
	qRegisterMetaType<CDM_DataStruct::PLAN_TERMINATE>("CDM_DataStruct::PLAN_TERMINATE");
	if(!m_pAllocateGatePosObj)
	{
		m_pAllocateGatePosObj = boost::make_shared<CDM_InitGateInformation>();
	}
}
