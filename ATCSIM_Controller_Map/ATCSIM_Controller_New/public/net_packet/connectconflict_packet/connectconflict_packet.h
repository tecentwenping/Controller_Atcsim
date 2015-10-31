 /******************************************************************************
   版权所有(C), 2013，四川川大智胜软件股份有限公司

  【文 件 名】:   connectconflict_packet.h
  【作    者】:   lijin
  【版    本】:   1.0
  【完成日期】:   2013/06/19
  【描    述】:   网络连接冲突包
  【其    它】: 
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
	CONFLICT_SITE_ID,		//席位id重复（席位type不同）
	CONFLICT_SITE_TYPE_ID,	//席位type，id均重复
};

/** 
 \brief    网络连接冲突包
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