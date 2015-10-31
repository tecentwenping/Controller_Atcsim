#pragma once
#include <string>

#define SITE_ALL						1

//发送到主题，根据包来决定
#define SITE_TOPIC						2
 
#define SITE_MAC						3

#define SITE_MAC_MONITOR				4

#define SITE_CONTROLLER					5

#define SITE_ATG						6

#define SITE_PILOT						7

#define SITE_GATE						8

#define SITE_CENTER						9

#define SITE_DATASERVER					10

#define SITE_EXER_DESIGNER				11

#define SITE_MEMCACHESERVER				12

#define SITE_SUPERVISOR					13

#define SITE_VIS						14

#define SITE_SWITCHSERVER				15

inline std::string GetSiteName(int site_type)
{
	switch (site_type)
	{
	case SITE_ALL:						return "SITE_ALL";
	case SITE_TOPIC:					return "SITE_TOPIC";
	case SITE_MAC:						return "SITE_MAC";
	case SITE_MAC_MONITOR:				return "SITE_MAC_MONITOR";
	case SITE_CONTROLLER:				return "SITE_CONTROLLER";
	case SITE_ATG:						return "SITE_ATG";
	case SITE_PILOT:					return "SITE_PILOT";
	case SITE_GATE:						return "SITE_GATE";
	case SITE_CENTER:					return "SITE_CENTER";
	case SITE_DATASERVER:				return "SITE_DATASERVER";
	case SITE_EXER_DESIGNER:			return "SITE_EXER_DESIGNER";
	case SITE_MEMCACHESERVER:			return "SITE_MEMCACHESERVER";
	case SITE_SUPERVISOR:				return "SITE_SUPERVISOR";
	case SITE_VIS:						return "SITE_VIS";
	case SITE_SWITCHSERVER:				return "SITE_SWITCHSERVER";
	default:							return "-";
	}
}