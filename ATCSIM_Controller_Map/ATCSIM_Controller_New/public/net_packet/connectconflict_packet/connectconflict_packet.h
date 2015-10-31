 /******************************************************************************
   ��Ȩ����(C), 2013���Ĵ�������ʤ����ɷ����޹�˾

  ���� �� ����:   connectconflict_packet.h
  ����    �ߡ�:   lijin
  ����    ����:   1.0
  ��������ڡ�:   2013/06/19
  ����    ����:   �������ӳ�ͻ��
  ����    ����: 
******************************************************************************/

#ifndef _CONNECTCONFLICT_PACKET_H_
#define _CONNECTCONFLICT_PACKET_H_

#include "serial_base.h"
#include <string>
#include "public/site_info.h"
using namespace std;

#include "Serialization/wserialize.h"

enum ENUM_CONNECT_CONFLICT_TYPE
{
	CONFLICT_DEFALUT = 0,
	CONFLICT_SITE_ID,		//ϯλid�ظ���ϯλtype��ͬ��
	CONFLICT_SITE_TYPE_ID,	//ϯλtype��id���ظ�
};

/** 
 \brief    �������ӳ�ͻ��
\details   
 \author   lijin
\date      2013/06/19
*/
class ConnectConflictPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ConnectConflictPacket);

public:
	site_info  m_site_info; 
	ENUM_CONNECT_CONFLICT_TYPE m_enumConflictType;
private:
	SERIALIZE_PACKET(m_site_info & m_enumConflictType);
};


#endif