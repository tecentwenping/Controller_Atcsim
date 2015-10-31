#pragma once
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "public/data_stack.h"
#include "public/site_info.h"
#include "../PackProcessorBase/PacketProcessor.h"
#include <iostream>
using namespace boost::asio;
using namespace boost;

class data_buffer;
class CSerial_Base;

class TcpClient
{
	typedef shared_ptr<ip::tcp::socket> sock_pt;

public:
	void Connect();
	void Disconnect();

public:
	TcpClient(std::string server_ip,int port,site_info sinfo);
	~TcpClient();

	void SendPacket(CSerial_Base & packet);
	void SendPacket(site_info target,CSerial_Base & packet);

	void SetPacketProcessor(ClientPacketProcessor *_packet_processor)
	{
		m_PacketProcessor = _packet_processor;
	}

	void SetSiteInfo(const site_info& site);
	site_info GetSiteInfo() const;

protected:
	void read(char *buf,int len);

private:
	void ConnectHandler(const system::error_code& ec,sock_pt sock);
	bool ConnectionDisable(const system::error_code& ec);
	void ReadHandler(const system::error_code& ec,size_t bytes_transferred);
	void WriteHandler(const system::error_code& ec);
	void CheckIn();
	void SockClose();
	void write(data_buffer pbuffer);
	void DoWrite(data_buffer buf);
	void PrintError(const system::error_code& ec);
	static void TcpClientThreadProc(TcpClient * pclient);

private:
	io_service m_ios;
	ip::tcp::endpoint m_ep;
	const static  int max_data_buffer =64*1024;
	char m_rev_data[max_data_buffer];
	char m_send_data[max_data_buffer];
	sock_pt m_sock;
	ClientPacketProcessor *m_PacketProcessor;
	data_stack m_InData;
	data_buffer m_packet_buffer;
	std::deque<data_buffer> m_bufqueue;
	site_info m_site_info;
	boost::shared_ptr<boost::thread> work_thread;
	bool m_bIsClosed;
};