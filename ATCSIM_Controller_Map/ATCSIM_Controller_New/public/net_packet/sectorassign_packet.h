#ifndef _SECTORASSIGN_PACKET_H_
#define _SECTORASSIGN_PACKET_H_

#include "serial_base.h"
#include <string>
#include <vector>
using namespace std;

#include "Serialization/wserialize.h"

struct ST_SectorAssign
{
	std::string m_strPos;
	std::vector<std::string> m_strSectorName;
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, ST_SectorAssign& ud, const unsigned int version)
{
	return	ar & ud.m_strPos & ud.m_strSectorName;
}

class SectorAssignPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorAssignPacket);

public:
	std::vector<ST_SectorAssign> m_vSectorAssign;
private:
	SERIALIZE_PACKET(m_vSectorAssign);
};


#endif