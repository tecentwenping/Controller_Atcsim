/********************************************************************
��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾	
���ļ�����:  tlsetting_packet.h
����  �ߡ�:  @yyg
����  ����:  1.0
��������ڡ�:2013/07/01	
����  ����:  ��Աϯλ���ù��ɸ߶Ȳ�İ�

����  ����:   
*********************************************************************/

#ifndef _TLSETTING_PACKET_H
#define _TLSETTING_PACKET_H

#include "serial_base.h"
#include "Serialization/wserialize.h"

class TLSettingPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TLSettingPacket);
public:
	int m_nAirportID;  //����ID
	double m_dTL;     //���ɸ߶�
	double m_dTIL;    //���ɼв�
	double m_dTHL;    //���ɸ߶Ȳ�
private:
	SERIALIZE_PACKET( m_nAirportID & m_dTL & m_dTIL & m_dTHL);
};

#endif
