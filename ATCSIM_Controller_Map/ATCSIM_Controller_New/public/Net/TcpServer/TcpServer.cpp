#include "TcpServer.h"
#include <string>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "public/utility.h"
#include "public/net_packet/serial_base.h"
#include "public/log.h"
#include "session.h"

TcpServer::TcpServer(short port,/*server_notify * pserver_notify,*/ServerPacketProcessor * pPacket_processor)
    :m_acceptor(m_io_service,ip::tcp::endpoint(ip::tcp::v4(),port)),
	/* m_pserver_notify(pserver_notify),*/m_send_thread_stop(false),m_packet_processor(pPacket_processor),
	 m_pDataQueue(new data_queue<data_buffer>(40))
{
	Accept();
	m_server_thread = boost::make_shared<boost::thread>(ServerThreadFun,this);
	m_send_thread   = boost::make_shared<boost::thread>(SendThreadFun,this);
}

void TcpServer::SendThreadFun(TcpServer * pserver)
{
	
	while(!pserver->m_send_thread_stop)
	{
		data_buffer tmpbuf;
		pserver->m_pDataQueue->read(&tmpbuf);
		site_info site = utility::get_buffer_siteinfo(tmpbuf);
		//pserver->m_session_manager.EnterLock();
		session *psession = pserver->m_session_manager.GetSession(site);
		if(psession != 0&& psession->GetInvalidStatus())
		{			
			//psession->write(tmpbuf.get_buffer_pt(),tmpbuf.get_buffer_len());
			psession->write(tmpbuf);
			if (psession->Conflict())
			{//处理冲突席位的连接
				psession->SetSiteInfo(site_info());//重置席位信息
			}
		}
		//pserver->m_session_manager.ExitLock();
	}
}

void TcpServer::ServerThreadFun(TcpServer * pserver)
{
	pserver->Run();
	//LOG("TcpServer exit");
}

TcpServer::~TcpServer(void)
{
}

void TcpServer::Accept()
{
	//重新连接的时候检测老的连接是否存在；
	//session * new_session =new session(m_io_service,this);
	session * new_session = m_session_manager.GetOneInvalidSession();
	if (0 == new_session)
	{
		new_session =new session(m_io_service,this);
	}
	m_acceptor.async_accept(new_session->socket(),
		                   boost::bind(&TcpServer::HandleAccept,this,new_session,placeholders::error)
						   );
}

void TcpServer::Run()
{
	m_io_service.run();
}

void TcpServer::HandleAccept(session * new_session,const boost::system::error_code& error)
{
	if(!error)
	{
		m_session_manager.AddSession(new_session);
		new_session->start();
	}
	else
	{
		//delete new_session;
		m_session_manager.AddInvalidSession(new_session);
	}
	Accept();
}

bool TcpServer::SendPacket(site_info& target,CSerial_Base & pPacket)
{
	data_buffer tmpbuf;
	if(utility::encode_buffer(target,pPacket,tmpbuf))
	{
		m_pDataQueue->write(tmpbuf);	
		return true;
	}
	else
	{
		return false;
	}
}

bool TcpServer::SendPacket(CSerial_Base & pPacket)
{
	m_session_manager.EnterLock();
	site_info target;
	if(m_session_manager.GetSessionList().size() <1)
	{
		m_session_manager.ExitLock();
		return false;
	}

	const std::vector<session *> vSession = m_session_manager.GetSessionList();
	std::vector<session *>::const_iterator it = vSession.begin();
	for(;it!=vSession.end();++it)
	{
		target = (*it)->GetSiteInfo();
		data_buffer tmpbuf;
		if(utility::encode_buffer(target,pPacket,tmpbuf))
		{
			m_pDataQueue->write(tmpbuf);	
			//DataQueue.push_back(tmpbuf);
		}

	}
	m_session_manager.ExitLock();
	return true;
}

void TcpServer::SessionReadFailure(session *psession,const boost::system::error_code& error)
{
	//m_session_manager.EnterLock();
	session *del_session = m_session_manager.RemoveSession(psession->GetHandle());
	if (del_session != 0)
	{	
		site_info SiteInfo = psession->GetSiteInfo();
	//delete del_session;
	//m_session_manager.ExitLock();
	del_session->ResetSession();
	m_packet_processor->SiteDisconnect(SiteInfo);
	m_session_manager.AddInvalidSession(del_session);
	}
}

void TcpServer::SessionWriteFailure(session *psession,const boost::system::error_code& error)
{
	//m_session_manager.EnterLock();
	session *del_session = m_session_manager.RemoveSession(psession->GetHandle());
	if (del_session != 0)
	{
		site_info SiteInfo = psession->GetSiteInfo();
	//delete del_session;
	//m_session_manager.ExitLock();
		del_session->ResetSession();
		m_packet_processor->SiteDisconnect(SiteInfo);
		m_session_manager.AddInvalidSession(del_session);
	}
}

void TcpServer::ReceivePacket(data_buffer & packet)
{
	m_packet_processor->PacketProcess(packet);
}

void TcpServer::SiteCheckin(site_info& target)
{
	m_packet_processor->SiteCheckin(target);
}

int TcpServer::GetClientNum() const
{
	return m_session_manager.GetSessionNum();
}