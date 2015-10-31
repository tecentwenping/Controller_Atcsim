#ifndef _CMD_LINE_MANAGER_H_
#define _CMD_LINE_MANAGER_H_

#include "public/singleton.h"

struct SiteCmdInfo;

class CmdLineManager : public WSingleton<CmdLineManager>
{
	DECLARE_SINGLETON(CmdLineManager)

public:
	bool ParseArgs(int argc, char* argv[], SiteCmdInfo &info);
};

#endif /*_CMD_LINE_MANAGER_H_*/