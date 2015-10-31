#pragma once
#include "public/site_info.h"
#include "public/net_packet/serial_base.h"
#include "public/data_buffer.h"
class ServerPacketProcessor
{
public:
	virtual ~ServerPacketProcessor(){};
	virtual void PacketProcess(data_buffer & packet)=0;
	virtual void SiteCheckin(site_info& site)    =0;
	virtual void SiteCheckin(CSerial_Base * packet)    =0;
	virtual void SiteDisconnect(site_info& site) =0;
};

class ClientPacketProcessor
{
public:
	virtual ~ClientPacketProcessor(){};
	virtual void PacketProcess(data_buffer & packet)=0;
	virtual void ClientConnect(bool bConnect)=0;
	virtual void ClientConnect(site_info site, bool bConnect)=0;
};
