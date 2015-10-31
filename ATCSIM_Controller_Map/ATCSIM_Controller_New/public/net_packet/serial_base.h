#pragma once

#include "wpackethandler.h"
#include "Serialization/wserialize.h"

#define SERIALIZE_PACKET(body)\
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


#define PKT_CALLBACK(class_name)\
virtual void callback(const WPacketHandlerBase* handler, const CSerial_Base& packet) const\
{\
	dynamic_cast<const WPacketHandler<class_name>*>(handler)->dispatch(dynamic_cast<const class_name&>(packet));\
}\

#define PKT_CLONE(class_name)\
virtual class_name* Clone() const { return new class_name(*this); }\

#define PKT_DECLARE_DYNAMIC(class_name) \
public: \
	static  CPacket_Info class##class_name;\
	virtual CPacket_Info* GetPacketClassInfo() const ;\
	static const char* GetPacketName() { return class##class_name.m_lpszPacketName;}\
	PKT_CALLBACK(class_name)\
	PKT_CLONE(class_name)\
\

#define PKT_RUNTIME_CLASS(class_name) (&class_name::class##class_name)


#define PKT_IMPLEMENT_RUNTIMECLASS(class_name,pfnNew) \
	static char _lpsz##class_name[] = #class_name; \
	CPacket_Info class_name::class##class_name = {_lpsz##class_name, pfnNew }; \
	static CPacket_Class_Init _init_##class_name(&class_name::class##class_name); \
	CPacket_Info* class_name::GetPacketClassInfo() const \
{ return &class_name::class##class_name; } 



#define PKT_DECLARE_DYNCREATE(class_name) \
	PKT_DECLARE_DYNAMIC(class_name) \
	static CSerial_Base* CreatePacket();

#define PKT_IMPLEMENT_DYNCREATE(class_name) \
	CSerial_Base* class_name::CreatePacket() \
{ return new class_name; } \
	PKT_IMPLEMENT_RUNTIMECLASS(class_name,class_name::CreatePacket)

class CSerial_Base;
struct CPacket_Info
{
	char* m_lpszPacketName;
	CSerial_Base* (* m_pfnCreatePacket)();
	static CPacket_Info* pFirstPacketClass ;
	CPacket_Info* m_pNextPacketClass ;
};
struct CPacket_Class_Init
{
	CPacket_Class_Init(CPacket_Info* pNewPacketClass)
	{
		pNewPacketClass->m_pNextPacketClass = CPacket_Info::pFirstPacketClass ;
		CPacket_Info::pFirstPacketClass = pNewPacketClass ;
	}

};
class CSerial_Base  
{
private:
	virtual void ReadFromBuffer(const char* pBuffer)=0;
	virtual void WriteToBuffer(char* pBufffer)=0;
	virtual int GetBufferSize(){return 0;};
public:
	static CPacket_Info classCSerial_Base ;
public:
	CSerial_Base();
	virtual ~CSerial_Base();
	virtual CPacket_Info* GetPacketClassInfo() const ;
	virtual CSerial_Base* Clone() const = 0;

	int Serialize(char *pBuffer) ; // 串行化的开始是包类型名;
	int UnSerialize(const char* pBuffer) ;//逆串行化
	int GetSize(); // 得到的是串行化以后Buffer的大小
	PKT_CALLBACK(CSerial_Base)
};

class CPacketFactory
{
public:
	static CSerial_Base* CreatePacketFromBuffer(const char* pBuffer);
	CPacketFactory();
	virtual ~CPacketFactory();

};