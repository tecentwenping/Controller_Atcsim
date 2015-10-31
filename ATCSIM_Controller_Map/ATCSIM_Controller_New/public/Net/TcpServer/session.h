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
	static const int  buffer_size=64*1024/*8024*/;//��������С
	//static int  static_id ;//��1��ʼ�����������ָ�session��ID

 	ip::tcp::socket m_socket;
	char m_tmp_buffer [buffer_size];//���ջ�����

	data_stack  m_InData;
	int m_handle;
	bool m_bInvalid;
	data_buffer m_packet_buffer;
	std::deque<data_buffer> m_bufqueue;
	TcpServer * m_pserver;
	int m_id;//��session��ID��
	site_info  m_site_info;
	bool m_bConflict;//��session��Ӧϯλ�Ƿ�������ϯλ��ͻ��true��ͻ��false����ͻ��
};
