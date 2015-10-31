
/******************************************************************************
��Ȩ���� (C), 2000 - 2013, �Ĵ�������ʤ����ɷ����޹�˾

���ļ�����: env_control_packet.h
����  �ߡ�: JZH
����  ����:

��������ڡ�:2013/6/5

����  ����: ���ڴ�Ż����仯��صİ���ͷ�ļ�

******************************************************************************/
#pragma once
#include "DataObj/dataobjs.h"
#include "net_packet/serial_base.h"

/*! 
\brief     �ƹ��鿪�ذ�
\details   ������Ҫ���ڿ��Ƶƹ��鿪�ء�
\author    JZH
\date      2013-06-04
*/
class LightGroupControlPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(LightGroupControlPacket);
public:
	int m_iLightGroupID;				//!<�ƹ���ID
	int m_iLightLevel;	//!<�ƹ�ļ���0 = �رգ�1 = 1�����������ƣ����5��
	SERIALIZE_PACKET(m_iLightGroupID & m_iLightLevel)
};