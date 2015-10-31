#pragma  once

#include "session.h"

//  #define DEF_MUTEX  boost::mutex m;
//  #define LOCK m.lock();
//  #define UNLOCK m.unlock();

class session_manager
{
public:
	session_manager();
	~session_manager();

public:
	session * GetSession(int  s_handle);
	session * GetOneInvalidSession();
	void      AddSession(session * psession);
	void	  AddInvalidSession(session * psession);
	session * RemoveSession(int s_handle);
	session * GetSession(site_info& sinfo); 
	int GetSessionNum() const;
	const std::vector<session *> GetSessionList() const
	{
		return m_session_list;
	}
	void EnterLock(){m.lock();}
	void ExitLock(){m.unlock();}

private:
	std::vector<session *> m_session_list;
	std::vector<session *> m_invalidsession_list;
	//DEF_MUTEX
	boost::mutex m;
};