#ifndef _TIMER_H
#define _TIMER_H

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
using namespace boost;
//millsec
class timer
{
public:
	typedef boost::function<void()> func_type;
	typedef std::pair<func_type, int> task_type;
	typedef std::vector<task_type> task_funcs;
public:
	timer():m_bStart(false)
	{}
	~timer()
	{
		m_bStart = false;
	}
public:
	void addTimer(func_type func, int millsec)
	{
		if (m_bStart)
		{
			m_threads.create_thread(boost::bind(&timer::exec, this, func, millsec));
		}
		else
		{
			m_funcs.push_back(std::make_pair(func, millsec));
		}
	}

	//·Ç×èÈû
	void startTimer()
	{
		BOOST_FOREACH(task_funcs::reference x, m_funcs)
		{
			m_bStart = true;
			m_threads.create_thread(boost::bind(&timer::exec, this, x.first, x.second));
		}
	}

	//×èÈû
	void runTimer()
	{
		startTimer();
		m_threads.join_all();
	}

	//¹Ø±Õtimer
	void killTimer()
	{
		m_bStart = false;
		boost::this_thread::sleep(boost::posix_time::millisec(500));
		m_threads.interrupt_all();
	}
private:
	void exec(func_type func, int millsec)
	{
		for (;;)
		{
			func();
			boost::this_thread::sleep(boost::posix_time::millisec(millsec));
		}
	}
private:
	task_funcs m_funcs;
	boost::thread_group m_threads;
	bool  m_bStart;
};

#endif