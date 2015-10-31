/********************************************************************
版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司	
【文件名】:  tlsetting_packet.h
【作  者】:  @yyg
【版  本】:  1.0
【完成日期】:2013/07/01	
【描  述】:  教员席位设置过渡高度层的包

【其  它】:   
*********************************************************************/

#ifndef _TLSETTING_PACKET_H
#define _TLSETTING_PACKET_H

#include "serial_base.h"
#include "Serialization/wserialize.h"

class TLSettingPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TLSettingPacket);
public:
	int m_nAirportID;  //机场ID
	double m_dTL;     //过渡高度
	double m_dTIL;    //过渡夹层
	double m_dTHL;    //过渡高度层
private:
	SERIALIZE_PACKET( m_nAirportID & m_dTL & m_dTIL & m_dTHL);
};

#endif
