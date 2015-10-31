#ifndef _H_ACK_EDIT_PACKET
#define _H_ACK_EDIT_PACKET

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include <string>

//回复包：回复编辑包
class AckDataEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckDataEditPacket);
public:
	EDIT_TYPE m_edit_type;      //编辑类型（增、删、改）
	bool m_bSuccessed;          //成功与否
	std::string m_strErrorInfo; //错误信息
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_edit_type & m_bSuccessed &m_strErrorInfo);
};


class AckTestDataPacket :public  CSerial_Base
{
PKT_DECLARE_DYNCREATE(AckTestDataPacket) ;
public:
	std::string m_str;
private:
	SERIALIZE_PACKET(m_str) ;

};
#endif
