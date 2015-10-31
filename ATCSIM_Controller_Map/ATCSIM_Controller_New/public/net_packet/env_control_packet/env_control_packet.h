
/******************************************************************************
版权所有 (C), 2000 - 2013, 四川川大智胜软件股份有限公司

【文件名】: env_control_packet.h
【作  者】: JZH
【版  本】:

【完成日期】:2013/6/5

【描  述】: 用于存放环境变化相关的包的头文件

******************************************************************************/
#pragma once
#include "DataObj/dataobjs.h"
#include "net_packet/serial_base.h"

/*! 
\brief     灯光组开关包
\details   本包主要用于控制灯光组开关。
\author    JZH
\date      2013-06-04
*/
class LightGroupControlPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightGroupControlPacket);
public:
	int m_iLightGroupID;				//!<灯光组ID
	int m_iLightLevel;	//!<灯光的级别，0 = 关闭，1 = 1级，依次类推，最高5级
	SERIALIZE_PACKET(m_iLightGroupID & m_iLightLevel)
};