#pragma once

#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "public/data_queue.hpp"
#include "session_manager.h"
#include "public/Net/PackProcessorBase/PacketProcessor.h"
using namespace boost::asio;
using namespace boost;

class session;
class CSerial_Base;
class PacketProcessor;

class TcpServer
{
public:
	TcpServer(short port/*,server_notify * pserver_notify*/,ServerPacketProcessor * pPacket_processor);
	~TcpServer(void);

public:
	bool SendPacket(site_info& target,CSerial_Base& pPacket);
	bool SendPacket(CSerial_Base& pPacket);
	void ReceivePacket(data_buffer & packet);
	void SiteCheckin(site_info& target);
	int GetClientNum() const;//获取连接session数量

	session_manager* GetSessionManager()
	{
		return &m_session_manager;
	}


protected:
	void HandleAccept(session * new_session,
		const boost::system::error_code& error);

private:
	void SessionReadFailure(session *psession,const boost::system::error_code& error);
	void SessionWriteFailure(session *psession,const boost::system::error_code& error);

private:
	static void ServerThreadFun(TcpServer * pserver);
	static void SendThreadFun(TcpServer * pserver);
	void Run();
	void Accept();
	friend session;

private:
	asio::io_service m_io_service;
	ip::tcp::acceptor  m_acceptor;
	session_manager m_session_manager;
	boost::shared_ptr<boost::thread> m_server_thread;
	boost::shared_ptr<boost::thread> m_send_thread;
	//server_notify * m_pserver_notify;
	ServerPacketProcessor *m_packet_processor;
	boost::shared_ptr<data_queue<data_buffer>> m_pDataQueue;
	bool m_send_thread_stop;
	//std::vector<data_buffer> DataQueue;
	boost::mutex m;
};
