#ifndef _GLOBALMAPS_PACKET_H_
#define _GLOBALMAPS_PACKET_H_

#include "serial_base.h"
#include <string>
#include "public/site_info.h"
using namespace std;

#include "Serialization/wserialize.h"

enum OperateType
{
	OPERATE_TYPE_SYNC = 0,	//同步全局地图数据操作
	OPERATE_TYPE_DELETE		//删除全局地图数据操作
};

class GlobalMapsPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(GlobalMapsPacket);

public:
	site_info  m_site_info; 
	string m_str;
	OperateType m_operateType;
private:
	SERIALIZE_PACKET(m_site_info & m_str & m_operateType);
};


#endif /*_GLOBALMAPS_PACKET_H_*/