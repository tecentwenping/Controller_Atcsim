#include "wlogappendermanager.h"

WLogAppender* WLogAppenderManager::GetLogAppender(category cg)
{
	return m_appenders + cg;
}

const WLogAppender* WLogAppenderManager::GetLogAppender(category cg) const
{
	return m_appenders + cg;
}