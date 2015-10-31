#include "tcpclient.h"
#include "public/data_buffer.h"
#include "public/sim_net_def.h"
#include "public/utility.h"
#include "public/site_type.h"
#include "public/net_packet/checkin_packet.h"
#include "public/utility.h"
#include "public/log.h"
#include <boost/make_shared.hpp>

#pragma warning(disable:4100)

void TcpClient::TcpClientThreadProc(TcpClient * pclient)
{
	pclient->m_ios.run();
}

TcpClient::TcpClient(std::string server_ip,int port,site_info sinfo):m_ep(ip::address::from_string(server_ip),port),
													   m_sock(new ip::tcp::socket(m_ios)),
													   m_site_info(sinfo),m_PacketProcessor(0),m_bIsClosed(false)
													   
{
	//Connect();
	//work_thread = boost::make_shared<boost::thread>(TcpClient::TcpClientThreadProc,this);
}

TcpClient::~TcpClient()
{
	//boost::posix_time::millisec(1000);
	utility::wait_time(1000);
	work_thread->interrupt();
}

void TcpClient::Disconnect()
{
	m_ios.stop();
	m_sock->close();
	m_bIsClosed = true;
	work_thread->interrupt();
	m_PacketProcessor->ClientConnect(false);
	m_PacketProcessor->ClientConnect(m_site_info, false);
}

void TcpClient::SockClose()
{
	m_sock->close();
}

void TcpClient::Connect()
{
	m_sock->async_connect(m_ep,bind(&TcpClient::ConnectHandler,this,placeholders::error,m_sock));
	work_thread = boost::make_shared<boost::thread>(TcpClient::TcpClientThreadProc,this);
}

void TcpClient::CheckIn()
{
	CCheckInPacket checkin_packet;
	checkin_packet.m_site_info = m_site_info;
	data_buffer tmpbuffer;

	if (utility::encode_buffer(m_site_info,checkin_packet,tmpbuffer))
	{
		write(tmpbuffer);
	}
}

void TcpClient::SendPacket(/*site_info target,*/CSerial_Base & packet)
{
	data_buffer tmpbuffer;
	if (utility::encode_buffer(m_site_info,packet,tmpbuffer))
	{
		write(tmpbuffer);
	}
}

void TcpClient::SendPacket(site_info target,CSerial_Base & packet)
{
	data_buffer tmpbuffer;
	if (utility::encode_buffer(target,packet,tmpbuffer))
	{
		write(tmpbuffer);
	}
}

bool TcpClient::ConnectionDisable(const system::error_code& ec)
{
	if(ec == error::connection_aborted ||
	   ec ==error::connection_refused  || 
	   ec ==error::connection_reset)
	{
		return true;
	}
	else
		return false;
}

void TcpClient::ConnectHandler(const system::error_code& ec,sock_pt sock)
{
	if(ec)
	{	
		PrintError(ec);
		if(ConnectionDisable(ec))
		{
			//m_PacketProcessor->ClientConnect(false);
			if (NULL != m_PacketProcessor)
			{
				m_PacketProcessor->ClientConnect(false);
				m_PacketProcessor->ClientConnect(m_site_info, false);
			}
			utility::wait_time(1000);
			Connect();
		}
	}
	else
	{
		//m_PacketProcessor->ClientConnect(true);
		if (NULL != m_PacketProcessor)
		{
			m_PacketProcessor->ClientConnect(true);
			m_PacketProcessor->ClientConnect(m_site_info, true);
		}
		CheckIn();
		read(m_rev_data,max_data_buffer);
	}
}

void TcpClient::read(char *buf,int len)
{
	m_sock->async_read_some(boost::asio::buffer(buf,len),
		boost::bind(&TcpClient::ReadHandler,this,placeholders::error,
		placeholders::bytes_transferred));
}

void TcpClient::ReadHandler(const system::error_code& ec,size_t bytes_transferred)
{
	
	if(ec)
	{
		PrintError(ec);
		if(ConnectionDisable(ec))
		{
			SockClose();
			utility::wait_time(1000);
			Connect();
		}
		return ;
	}	

	else
	{
		size_t len = bytes_transferred;
		len = m_InData.Append(m_rev_data,len);
		while( m_InData.GetPacket(m_packet_buffer))
		{
			if (!m_bIsClosed&&m_PacketProcessor)
			{
				m_PacketProcessor->PacketProcess(m_packet_buffer);
			}
		}
	}
	read(m_rev_data,max_data_buffer);		
}

void TcpClient::WriteHandler(const system::error_code& ec)
{
	if(ec)
	{

	}
	else
	{
		m_bufqueue.pop_front();
		if (!m_bufqueue.empty())
		{
			boost::asio::async_write(*m_sock,
				boost::asio::buffer(m_bufqueue.front().get_buffer_pt(),
				m_bufqueue.front().get_buffer_len()),
				boost::bind(&TcpClient::WriteHandler, this,
				boost::asio::placeholders::error));
		}
	}
}

void TcpClient::write(data_buffer pbuffer)
{

// 	m_sock->async_write_some(boost::asio::buffer(pbuffer->get_buffer_pt(),pbuffer->get_buffer_len()),
// 		boost::bind(&TcpClient::WriteHandler,this,placeholders::error));
	if (!m_bIsClosed)
	{	
		m_ios.post(boost::bind(&TcpClient::DoWrite, this, pbuffer));
	}
}

void TcpClient::DoWrite(data_buffer buf)
{
	bool write_in_progress = !m_bufqueue.empty();
	m_bufqueue.push_back(buf);
	if (!write_in_progress)
	{
		boost::asio::async_write(*m_sock,
			boost::asio::buffer(m_bufqueue.front().get_buffer_pt(),
			m_bufqueue.front().get_buffer_len()),
			boost::bind(&TcpClient::WriteHandler, this,
			boost::asio::placeholders::error));
	}
}

void TcpClient::SetSiteInfo(const site_info& site)
{
	m_site_info = site;
}

site_info TcpClient::GetSiteInfo() const
{
	return m_site_info;
}

void TcpClient::PrintError(const system::error_code& ec)
{
	int error_code = ec.value();
	switch(error_code)
	{
	case error::access_denied: 
		std::cout<<"error::access_denied"<<std::endl;
		break;

	case error::address_family_not_supported: 
		std::cout<<"error::address_family_not_supported"<<std::endl;
		break;

	case error::address_in_use: 
		std::cout<<"error::address_in_use"<<std::endl;
		break;

	case error::already_connected:
		std::cout<<"error::already_connected "<<std::endl;
		break;

	case error::already_started:  
		std::cout<<"error::already_started "<<std::endl;
		break;

	case error::broken_pipe:  
		std::cout<<"error::broken_pipe "<<std::endl;
		break;

	case error::connection_aborted:   
		std::cout<<"error::connection_aborted  "<<std::endl;
		break;


	case error::connection_refused:   
		std::cout<<"error::connection_refused  "<<std::endl;
		break;

	case error::connection_reset:   
		std::cout<<"error::connection_reset  "<<std::endl;
		break;


	case error::bad_descriptor:  
		std::cout<<"error::bad_descriptor  "<<std::endl;
		break;



	case error::fault:   
		std::cout<<"error::fault  "<<std::endl;
		break;

	case error::host_unreachable:   
		std::cout<<"error::host_unreachable  "<<std::endl;
		break;

	case error::in_progress:   
		std::cout<<"error::in_progress  "<<std::endl;
		break;


	case error::interrupted:   
		std::cout<<"error::interrupted  "<<std::endl;
		break;

	case error::invalid_argument:   
		std::cout<<"error::invalid_argument  "<<std::endl;
		break;


	case error::message_size:   
		std::cout<<"error::message_size  "<<std::endl;
		break;

	case error::name_too_long:   
		std::cout<<"error::name_too_long  "<<std::endl;
		break;

	case error::network_down:   
		std::cout<<"error::network_down  "<<std::endl;
		break;

	case error::network_reset:   
		std::cout<<"error::network_reset  "<<std::endl;
		break;

	case error::network_unreachable:   
		std::cout<<"error::network_unreachable  "<<std::endl;
		break;

	case error::no_descriptors:   
		std::cout<<"error::no_descriptors  "<<std::endl;
		break;

	case error::no_buffer_space:   
		std::cout<<"error::no_buffer_space  "<<std::endl;
		break;

	case error::no_memory:   
		std::cout<<"error::no_memory  "<<std::endl;
		break;

	case error::no_permission:   
		std::cout<<"error::no_permission  "<<std::endl;
		break;

	case error::no_protocol_option:   
		std::cout<<"error::no_protocol_option  "<<std::endl;
		break;
	case error::not_connected:   
		std::cout<<"error::not_connected  "<<std::endl;
		break;
	case error::not_socket:   
		std::cout<<"error::not_socket  "<<std::endl;
		break;

	case error::operation_aborted:   
		std::cout<<"error::operation_aborted  "<<std::endl;
		break;

	case error::operation_not_supported:   
		std::cout<<"error::operation_not_supported  "<<std::endl;
		break;

	case error::shut_down:   
		std::cout<<"error::shut_down  "<<std::endl;
		break;

	case error::timed_out:   
		std::cout<<"error::timed_out  "<<std::endl;
		break;

	case error::try_again:   
		std::cout<<"error::try_again  "<<std::endl;
		break;

	case error::would_block:   
		std::cout<<"error::would_block  "<<std::endl;
		break;
	default:
		std::cout<<"unkonw  "<<std::endl;
		break;
	}
}