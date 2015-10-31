#include "wlogappender.h"
#include <ctime>

WLogAppender::WLogAppender() : m_dispatcher(0)
{
}

WLogAppender::~WLogAppender() 
{
	delete m_dispatcher;
}

void WLogAppender::ResetDispatcher()
{
	delete m_dispatcher;
	m_dispatcher = 0;
}

WLogAppender::_Myt& WLogAppender::operator<<(_Myt& (*pfn)(_Myt&))
{
#ifdef _USE_LOG
	return (*pfn)(*this);
#else
	pfn; //wipe out compile warning : unreferenced parameter
	return *this;
#endif
}

void WLogAppender::Flush() 
{
	if (m_dispatcher)
	{
		(*m_dispatcher)(m_oss.str());
	}
	m_oss.str("");
}

std::ostream& WLogAppender::GetStream()
{
	return m_oss;
}

namespace std
{
	WLogAppender& flush(WLogAppender& appender)
	{
		appender.Flush();
		return appender;
	}

	WLogAppender& ends(WLogAppender& appender)
	{
		appender << '\0';
		return appender;
	}

	WLogAppender& endl(WLogAppender& appender)
	{
		appender << '\n';
		appender.Flush();
		return appender;
	}

	WLogAppender& time(WLogAppender& appender)
	{
		time_t curr = time(0);
		tm t;
		localtime_s(&t, &curr);

		std::ostream& os = appender.GetStream();
		os.fill('0');
		appender << '[';
		os.width(2);
		appender << t.tm_hour << ':';
		os.width(2);
		appender << t.tm_min << ':';
		os.width(2);
		appender << t.tm_sec << ']';

		return appender;
	}

	WLogAppender& timeplus(WLogAppender& appender)
	{
		time_t curr = time(0);
		tm t;
		localtime_s(&t, &curr);

		std::ostream& os = appender.GetStream();
		os.fill('0');
		appender << '[';
		os.width(2);
		appender << t.tm_hour << ':';
		os.width(2);
		appender << t.tm_min << ':';
		os.width(2);
		appender << t.tm_sec << '.';
		os.width(3);
		appender << clock() % CLOCKS_PER_SEC << ']';

		return appender;
	}
}