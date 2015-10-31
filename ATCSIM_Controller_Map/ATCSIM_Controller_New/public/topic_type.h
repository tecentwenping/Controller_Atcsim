#pragma once
//航迹服务
#define ATG									0x1
//地面航迹服务（已废弃）
#define GND									0x2
//训练计划初始化服务
#define EXERPLAN							0x4
//碰撞检测服务
#define COLLIDE								0x8
//环境数据服务
#define ENVIRONMENT							0x10
//训练计划控制服务
#define EPLANCTRL							0x20
//航空器控制命令服务（改变航向、速度、高度等）
#define CMD									0x40
//训练计划初始化服务(发向视景)
#define EXERPLAN_VIS						0x80
//接入席位连接确服务
#define SwitchCheckIn						0x100
//数据服务席位连接确认服务
#define DataServiceCheckIn					0x200
//数据请求服务
#define DATAREQ								0x400
//心跳包服务
#define TIME								0x800
//客户端席位重连接时，数据服务席位将基础数据点对点发送给重连入的客户端
#define PeerToPeer						    0x1000
//全局地图数据服务
#define GlobalMapsSync						0x2000
//告警服务
#define ALARM								0x4000
//Hold服务
#define FPL_OPERATE							0x8000
//Fdp飞行计划初始化
#define FDP_FLIGHTPLAN                      0x10000
//区域控制信息服务
#define REGION_CTRL							0x20000
//扇区移交服务
#define SectorAssignService					0x40000
//环境控制服务
#define ENVCTRLSERVICE                      0x80000
//动态创建物体/删除服务
#define MotionalObjService					0x100000
//SDPS航迹服务
#define SDPSService                         0x200000
//监视传感器状态服务
#define SurvSensorsStatService				0x400000
//动态创建物体服务回复
#define ACKMotionalObjService					0x800000
//动态创建物体查询服务
#define MotionalObjQueryService					0x1000000
//机长告警服务
#define PILOTALARM	                            0x2000000 
//停机位查询服务
#define ParkingBayQueryService					 0x4000000
//停机位回复服务
#define ParkingBayACKService				 0x8000000

#define LIGHTCTRLSERVER                      0x10000000
#define LIGHTCTRLSERVERTOVIS                 0x20000000
//机长广播服务（现在主要用于机长席位移交,-->ATG -->Pilot)
#define PilotBroadcastService				 0x40000000 

inline std::string GetTopicName(int topic_type)
{
	switch (topic_type)
	{
	case ATG:					return "ATG";
	case GND:					return "GND";
	case EXERPLAN:				return "EXERPLAN";
	case COLLIDE:				return "COLLIDE";
	case ENVIRONMENT:			return "ENVIRONMENT";
	case EPLANCTRL:				return "EPLANCTRL";
	case CMD:					return "CMD";
	case EXERPLAN_VIS:			return "EXERPLAN_VIS";
	case SwitchCheckIn:			return "SwitchCheckIn";
	case DataServiceCheckIn:	return "DataServiceCheckIn";
	case DATAREQ:				return "DATAREQ";
	case TIME:					return "TIME";
	case PeerToPeer:			return "PeerToPeer";
	case GlobalMapsSync:		return "GlobalMapsSync";
	case ALARM:					return "ALARM";
	case FPL_OPERATE:			return "FPL_OPERATE";
	case FDP_FLIGHTPLAN:		return "FDP_FLIGHTPLAN";
	case REGION_CTRL:			return "REGION_CTRL";
	case SectorAssignService:	return "SectorAssignService";
	case ENVCTRLSERVICE:        return "ENVCTRLSERVICE";
	case MotionalObjService:    return "MotionalObjService";
    case SDPSService:           return "SDPSService";
	case ACKMotionalObjService:           return "ACKMotionalObjService";
	case MotionalObjQueryService:           return "MotionalObjQueryService";
	case PILOTALARM:					return "PILOTALARM";
	case ParkingBayQueryService:    return "ParkingBayQueryService";
	case ParkingBayACKService:	return "ParkingBayACKService";
	case LIGHTCTRLSERVER:       return "LIGHTCTRLSERVER";
	case LIGHTCTRLSERVERTOVIS:  return "LIGHTCTRLSERVERTOVIS";
	case PilotBroadcastService: return "PilotBroadcastService";
	default:					return "-";
	}
}