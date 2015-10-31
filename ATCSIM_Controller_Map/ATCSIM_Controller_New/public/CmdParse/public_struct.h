#pragma once
#include <cstring>
#include <string>
#include <map>
using namespace std;

struct SiteCmdInfo
{
	SiteCmdInfo()
	{
		server_ip	= make_pair(false, "");
		server_port = make_pair(false, 0);
		site_type	= make_pair(false, 0);
		site_id		= make_pair(false, 0);
		listen_port = make_pair(false, 0);
	}
	pair<bool, string> server_ip;
	pair<bool, int> server_port;
	pair<bool, unsigned> site_type;
	pair<bool, unsigned> site_id;
	pair<bool, int> listen_port;
};