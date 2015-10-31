#include "CmdLineManager.h"
#include <iostream>
#include <boost/regex.hpp>
#include "public_struct.h"
#include "getopt.h"

using namespace std;
using namespace boost;

bool CmdLineManager::ParseArgs(int argc, char* argv[], SiteCmdInfo &info)
{
	//exact match : -a 127.0.0.1 -p 20000 -s 5 -i 10 -l 20101
	if (argc < 2)
		return false;

	regex reg_ip("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");	//ip匹配正则表达式
	regex reg_port("\\d{3,5}");									//port匹配正则表达式
	regex reg_site_type("[1-9]\\d*|[0]");						//site_type匹配正则表达式，非负整数
	regex reg_site_id("[1-9]\\d*|[0]");							//site_id匹配正则表达式，非负整数
	cmatch what;

	//命令行参数判断
	int c;
	extern char *optarg;
	extern int optind;
	char *address = 0;
	char *port = 0;
	char *site_type = 0;
	char *site_id = 0;
	char *listen_port = 0;
	int errflg = 0;

	while ((c = getopt(argc, argv, "a:p:s:i:l:")) != -1)
	{
		switch (c) 
		{
		case 'a':
			if (regex_match(optarg, what, reg_ip))
			{
				address = optarg;
				//strcpy_s(info.server_ip, address);
				info.server_ip = make_pair(true, address);
			}
			else
			{
				errflg++;
			}
			break;
		case 'p':
			if (regex_match(optarg, what, reg_port))
			{
				port = optarg;
				info.server_port = make_pair(true, atoi(port));
			}
			else
			{
				errflg++;
			}
			break;
		case 's':
			if (regex_match(optarg, what, reg_site_type))
			{
				site_type = optarg;
				info.site_type = make_pair(true, atoi(site_type));
			}
			else
			{
				errflg++;
			}
			break;
		case 'i':
			if (regex_match(optarg, what, reg_site_id))
			{
				site_id = optarg;
				info.site_id = make_pair(true, atoi(site_id));
			}
			else
			{
				errflg++;
			}
			break;
		case 'l':
			if (regex_match(optarg, what, reg_port))
			{
				listen_port = optarg;
				info.listen_port = make_pair(true, atoi(listen_port));
			}
			else
			{
				errflg++;
			}
			break;
		case '?':
			errflg++;
		}
	}

	if (errflg) 
	{
		cout << "usage: cmd [-a|-b] [-o<file>] files..." << endl;
		return false;
	}

	for ( ; optind < argc; optind++)
	{
		cout << argv[optind] << endl;
	}

	return true;
}