#ifndef _H_ACK_EDIT_PACKET
#define _H_ACK_EDIT_PACKET

#include "edit_type.h"
#include "net_packet/serial_base.h"
#include <string>

//�ظ������ظ��༭��
class AckDataEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckDataEditPacket);
public:
	EDIT_TYPE m_edit_type;      //�༭���ͣ�����ɾ���ģ�
	bool m_bSuccessed;          //�ɹ����
	std::string m_strErrorInfo; //������Ϣ
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
