#ifndef _WLOG_APPENDER_MANAGER_H_
#define _WLOG_APPENDER_MANAGER_H_

#include <boost/pool/detail/singleton.hpp>
#include "wlogappender.h"

class WLogAppenderManager
{
public:
	enum category //��־����
	{
		debug = 0,
		warning,
		critical,
		fatal,
		cg_end,
	};

	 //��ȡ��־��ʽ����
	WLogAppender* GetLogAppender(category cg);
	const WLogAppender* GetLogAppender(category cg) const;

private:
	WLogAppender m_appenders[cg_end]; //��ȡ��־��ʽ����
};

inline WLogAppenderManager& log_manager() { return boost::details::pool::singleton_default<WLogAppenderManager>::instance(); }
//���������������ڷ����ݵĻ�ȡ��־��ʽ����
inline WLogAppender& wDebug() { return *log_manager().GetLogAppender(WLogAppenderManager::debug); }
inline WLogAppender& wWarning() { return *log_manager().GetLogAppender(WLogAppenderManager::warning); }
inline WLogAppender& wCritical() { return *log_manager().GetLogAppender(WLogAppenderManager::critical); }
inline WLogAppender& wFatal() { return *log_manager().GetLogAppender(WLogAppenderManager::fatal); }

#define debug wDebug()
#define warning wWarning()
#define critical wCritical()
#define fatal wFatal()

#endif