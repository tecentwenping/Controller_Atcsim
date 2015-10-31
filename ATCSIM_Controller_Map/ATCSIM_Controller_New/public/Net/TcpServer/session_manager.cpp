#include "session_manager.h"


session_manager::session_manager()
{

}

session_manager::~session_manager()
{

}

session * session_manager::GetSession(int s_handle)
{
	//Ϊ�˶�ϯλ[type&id] || [id]��ͻ����������жϣ���Ϊ�������
	//֮���Ը�Ϊ��������Ϊm_session_list�Ǵ�β��������session��
	//����ͻ��Ӧ��ɾ���������session������Ӧ�÷�����ҡ�

	//std::vector<session *>::iterator it;
	//for(it = m_session_list.begin();it!=m_session_list.end();++it)

	std::vector<session *>::reverse_iterator it;
	for(it = m_session_list.rbegin();it!=m_session_list.rend();++it)
	{
		if((*it)->GetHandle() == s_handle)
			return *it;
	}

	return 0;
}

session * session_manager::GetOneInvalidSession()
{
	EnterLock();
	std::vector<session *>::iterator it;
	for(it = m_invalidsession_list.begin();it!=m_invalidsession_list.end();it++)
	{
		if(!(*it)->GetInvalidStatus())
		{
			session * psession = (*it);
			psession->SetInvalidStatus(true);
			m_invalidsession_list.erase(it);
			ExitLock();
			return psession;
		}
	}
	ExitLock();
	return 0;
}

void session_manager::AddSession(session * psession)
{
	m_session_list.push_back(psession);
}

void session_manager::AddInvalidSession( session * psession )
{
	EnterLock();
	m_invalidsession_list.push_back(psession);
	ExitLock();
}

session* session_manager::RemoveSession(int s_handle)
{
	//Ϊ�˶�ϯλ[type&id] || [id]��ͻ����������жϣ���Ϊ�������
	//֮���Ը�Ϊ��������Ϊm_session_list�Ǵ�β��������session��
	//����ͻ��Ӧ��ɾ���������session������Ӧ�÷�����ҡ�

	//std::vector<session *>::iterator it;	
	//for(it = m_session_list.begin();it!=m_session_list.end();++it)

	std::vector<session *>::reverse_iterator it;
	for(it = m_session_list.rbegin();it!=m_session_list.rend();++it)
	{
		if((*it)->GetHandle() == s_handle)
		{
			session * psession = (*it);
			//LOCK
			//m_session_list.erase(it);//erase()������reverse_iterator
			m_session_list.erase((++it).base());
			//UNLOCK
			return psession;
		}
	}
	return 0;
}

session * session_manager::GetSession(site_info& sinfo)
{
	//Ϊ�˶�ϯλ[type&id] || [id]��ͻ����������жϣ���Ϊ�������
	//֮���Ը�Ϊ��������Ϊm_session_list�Ǵ�β��������session��
	//����ͻ��Ӧ��ɾ���������session������Ӧ�÷�����ҡ�

	//std::vector<session *>::iterator it;
	//for(it = m_session_list.begin();it!=m_session_list.end();++it)

	std::vector<session *>::reverse_iterator it;
	for(it = m_session_list.rbegin();it!=m_session_list.rend();++it)
	{
		if((*it)->GetSiteInfo() == sinfo)
			return *it;
	}

	return 0;
}

int session_manager::GetSessionNum() const
{
	return m_session_list.size();
}