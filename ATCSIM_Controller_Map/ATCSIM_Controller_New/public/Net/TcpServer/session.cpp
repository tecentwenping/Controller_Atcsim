#include "session.h"
#include <boost/bind.hpp>
#include "public/net_packet/serial_base.h"
#include "public/utility.h"
#include "public/Net/TcpServer/TcpServer.h"
//#include "public/net_packet/test_packet.h"
#include "public/net_packet/checkin_packet.h"
#include "public/net_packet/connectconflict_packet/connectconflict_packet.h"

//int session::static_id =1;
//int session::static_id =0;//连进来的席位id从0开始递增

session::session(io_service& io_service,TcpServer * pserver)
:m_socket(io_service),m_pserver(pserver),m_bConflict(false),m_bInvalid(true)
{
	//m_id = static_id;
	//static_id++;
	m_id = 0;/*2013.3.4不再采用自动分配方式,采用site_info.site_id*/
}

session::~session(void)
{
	close();
}

int session::GetHandle()
{
	return m_id;
	//return m_site_info.site_id;
}

ip::tcp::socket& session::socket()
{
	return m_socket;
}

void session::start()
{
	read(m_tmp_buffer,buffer_size);//
}

void session::read(char * buf,size_t num)
{
	m_socket.async_read_some(boost::asio::buffer(buf,num),
		boost::bind(&session::HandleRead,this,placeholders::error,
		placeholders::bytes_transferred));
}

void session::write(data_buffer buf)
{
// 	m_socket.async_write_some(boost::asio::buffer(buf,num),
// 		boost::bind(&session::HandleWrite,this,placeholders::error));
	m_pserver->m_io_service.post(boost::bind(&session::DoWrite, this, buf));
}
void session::DoWrite(data_buffer buf)
{
	bool write_in_progress = !m_bufqueue.empty();
	m_bufqueue.push_back(buf);
	if (!write_in_progress)
	{
		boost::asio::async_write(m_socket,
			boost::asio::buffer(m_bufqueue.front().get_buffer_pt(),
				m_bufqueue.front().get_buffer_len()),
			boost::bind(&session::HandleWrite, this,
				boost::asio::placeholders::error));
	}
}
void session::close()
{
	m_socket.close();
}

void session::HandleCheckin(char * pbuf,int len)
{
	CSerial_Base* pkt = CPacketFactory::CreatePacketFromBuffer(pbuf + sizeof(int) + sizeof(site_info));
	if (pkt && strcmp(pkt->GetPacketClassInfo()->m_lpszPacketName,"CCheckInPacket") == 0 )
	{
		CCheckInPacket* chk = (CCheckInPacket*)pkt;

		//判断连接是否冲突
		session* ses_type_id_conflict = this->GetTcpServer()->GetSessionManager()->GetSession(chk->m_site_info);//返回不为空表示type与id均相同，即为冲突。
		session* ses_only_id_conflict = this->GetTcpServer()->GetSessionManager()->GetSession(chk->m_site_info.site_id);//返回不为空表示id相同，即为冲突。

		//设置本session的site_info，发送线程SendThreadFun在发送数据时要用到（其他地方也要用）
		m_site_info = chk->m_site_info;//此句必须放在上面两句之后，否则在判断时会将自身也算在内

        if (ses_type_id_conflict != NULL || ses_only_id_conflict != NULL)
        {
			//给客户端回复一条冲突信息//释放掉这个连接
			ConnectConflictPacket cft_pkt;
			cft_pkt.m_site_info = (ses_type_id_conflict != NULL ?  ses_type_id_conflict->m_site_info : ses_only_id_conflict->m_site_info);
			cft_pkt.m_enumConflictType = (ses_type_id_conflict != NULL ?  CONFLICT_SITE_TYPE_ID : CONFLICT_SITE_ID);
			m_pserver->SendPacket(m_site_info, cft_pkt);
			m_bConflict = true;//设置冲突标记（发送冲突包后将席位信息重置，否则在冲突席位退出后，会影响被冲突席位，切记！！）
        }
		else
		{
			m_id = chk->m_site_info.site_id;
			m_pserver->SiteCheckin(m_site_info);
			chk->m_site_info = m_site_info;//更新site_id后的site_info?
			m_pserver->SendPacket(m_site_info, *pkt);//回发CheckIn信息
		}	
	}
}

void session::HandleRead(const boost::system::error_code& error,
				 size_t bytes_transferred)
{
	if(!error)
	{	
		size_t len = bytes_transferred;
		
		if( m_site_info.site_type  == INVALID_SITE_TYPE 
			&& m_site_info.site_id == INVALID_SITE_ID)
		{
		    HandleCheckin(m_tmp_buffer,len);
		}
		else		
		{
			//处理其他包
 			len = m_InData.Append(m_tmp_buffer,len);
  			while( m_InData.GetPacket(m_packet_buffer))
   			{
				m_pserver->ReceivePacket(m_packet_buffer);
			}
			
		}
		read(m_tmp_buffer,buffer_size);
	}
	else
	{
		//close();
		m_pserver->SessionReadFailure(this,error);
	}
}

void session::HandleWrite(const boost::system::error_code& error)
{
	if(error)
	{
		//close();
		//m_pserver->SessionWriteFailure(this,error);
	}
	else
	{
		m_bufqueue.pop_front();
		if (!m_bufqueue.empty())
		{
			boost::asio::async_write(m_socket,
				boost::asio::buffer(m_bufqueue.front().get_buffer_pt(),
				m_bufqueue.front().get_buffer_len()),
				boost::bind(&session::HandleWrite, this,
				boost::asio::placeholders::error));
		}
	}

}

void session::SetSiteInfo(site_info & sinfo)
{
	m_site_info = sinfo;
}

site_info session::GetSiteInfo()
{
	return m_site_info;
}

void session::SetInvalidStatus(bool bInvalid)
{
	m_bInvalid = bInvalid;
}

void session::ResetSession()
{
	m_handle = 0;
	m_site_info.site_id = INVALID_SITE_ID;
	m_site_info.site_type = INVALID_SITE_TYPE;
	m_bufqueue.clear();
	m_InData.Reset();
}

bool session::GetInvalidStatus()
{
	return m_bInvalid;
}