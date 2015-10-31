#ifndef _HOLDLIST_PACKET_H_
#define _HOLDLIST_PACKET_H_

#include "serial_base.h"
#include <vector>
using namespace std;

#include "Serialization/wserialize.h"

#define SERIALIZE(body)\
	virtual void ReadFromBuffer(const char* pBuffer)\
{\
	WUnserializer(pBuffer) & body;\
}\
	virtual void WriteToBuffer(char* pBuffer)\
{\
	WSerializer(pBuffer) & body;\
}\
	virtual int GetBufferSize()\
{\
	return (WSizeHelper() & body).value();\
}

struct HoldInfo
{
	int		nAcftId;		//飞机ID
	bool    bHold;			//飞机是否被HOLD
	string	strHoldEndTime;	//Hold状态结束时间
	string	strHoldName;	//Hold名称
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, HoldInfo& ud, const unsigned int version)
{
	return	ar & ud.nAcftId & ud.bHold & ud.strHoldEndTime & ud.strHoldName;
}

class HoldListPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(HoldListPacket);

public:
	vector<HoldInfo> m_vHoldList;
private:
	SERIALIZE(m_vHoldList);
};


#endif /*_HOLDLIST_PACKET_H_*/