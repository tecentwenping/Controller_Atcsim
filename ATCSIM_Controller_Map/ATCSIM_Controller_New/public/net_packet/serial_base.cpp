#include "serial_base.h"
#include "string.h"



CPacket_Info* CPacket_Info::pFirstPacketClass = 0 ;
static char szCSerial_Base[] = "CSerial_Base" ;
struct CPacket_Info CSerial_Base::classCSerial_Base = {szCSerial_Base,0};
static CPacket_Class_Init _init_CSerial_Base(&CSerial_Base::classCSerial_Base);


CSerial_Base::CSerial_Base()
{

}

CSerial_Base::~CSerial_Base()
{

}
int CSerial_Base::Serialize(char *pBuffer)
{
	if (pBuffer == 0)
		return 0 ;
	//写入类名
	const char* lpszPacketName = GetPacketClassInfo()->m_lpszPacketName ;
	int len = strlen(lpszPacketName)+ 1;
	memcpy(pBuffer,lpszPacketName,len);
	WriteToBuffer(pBuffer+len);

	return GetSize();
}
int CSerial_Base::UnSerialize(const char* pBuffer )
{
	if (pBuffer == 0)
		return 0 ;
	//读出类名
	int len = strlen((char*)pBuffer) + 1 ;
	//根据类名判断能否逆串行化
	if (strcmp(pBuffer,GetPacketClassInfo()->m_lpszPacketName) !=0)
		return 0 ;
	ReadFromBuffer(pBuffer+len);
	return GetSize();	
}
int CSerial_Base::GetSize()
{
	int len = strlen(GetPacketClassInfo()->m_lpszPacketName) + 1;
	len += GetBufferSize();
	return len ;
}


CPacket_Info* CSerial_Base::GetPacketClassInfo() const
{
	return &CSerial_Base::classCSerial_Base ;
}
CPacketFactory::CPacketFactory()
{
}
CPacketFactory::~CPacketFactory()
{
}
CSerial_Base* CPacketFactory::CreatePacketFromBuffer(const char* pBuffer)
{
	CPacket_Info* p;
	CSerial_Base* pPacket = 0;
	char* szPacketName = 0 ;
	int len = strlen((const char*)pBuffer);
	szPacketName = new char[len+1];

	if(szPacketName == 0)
		return 0 ;
	memset(szPacketName,0,len+1);
	memcpy(szPacketName,pBuffer,len) ;
	for(p = CPacket_Info::pFirstPacketClass ; p != 0 ; p = p->m_pNextPacketClass)
	{

		if (!strcmp(p->m_lpszPacketName,szPacketName))
		{

			if (p->m_pfnCreatePacket)
			{
				pPacket = (CSerial_Base*)p->m_pfnCreatePacket() ;
				if (pPacket)
				{
					pPacket->UnSerialize(pBuffer);
					break;
				}
			}
		}
	}
	delete[] szPacketName ;
	return pPacket ;	
}