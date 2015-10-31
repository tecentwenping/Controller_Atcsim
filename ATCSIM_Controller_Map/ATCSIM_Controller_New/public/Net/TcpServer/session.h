#pragma once

#include <vector>
#include <queue>
#include <boost/asio.hpp>
#include "public/data_stack.h"
#include "public/data_buffer.h"
#include "public/data_queue.hpp"
#include "public/site_info.h"

using namespace boost::asio;

class TcpServer;
class session
{
public:
	 session(io_service& io_service,TcpServer * pserver);
	~session(void);

public:
	ip::tcp::socket& socket();
	int GetHandle();
	void SetInvalidStatus(bool bInvalid);
	bool GetInvalidStatus();
	void start();
	void read(char * buf,size_t num);
	void write(data_buffer buf);
	void SetSiteInfo(site_info & sinfo);
	site_info GetSiteInfo();
	void ResetSession();
	TcpServer *GetTcpServer() const
	{
		return m_pserver;
	}
	bool Conflict()
	{
		return m_bConflict;
	}

private:
	void HandleRead(const boost::system::error_code& error,
		size_t bytes_transferred);
	void DoWrite(data_buffer buf);
	void HandleWrite(const boost::system::error_code& error);

	void HandleCheckin(char * pbuf,int len);
	void close();

private:
	static const int  buffer_size=64*1024/*8024*/;//缓冲区大小
	//static int  static_id ;//从1开始自增，以区分各session的ID

 	ip::tcp::socket m_socket;
	char m_tmp_buffer [buffer_size];//接收缓冲区

	data_stack  m_InData;
	int m_handle;
	bool m_bInvalid;
	data_buffer m_packet_buffer;
	std::deque<data_buffer> m_bufqueue;
	TcpServer * m_pserver;
	int m_id;//本session的ID号
	site_info  m_site_info;
	bool m_bConflict;//此session对应席位是否与其他席位冲突（true冲突，false不冲突）
};
