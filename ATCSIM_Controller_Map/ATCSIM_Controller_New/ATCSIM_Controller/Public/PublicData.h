#ifndef PUBLICDATA_H
#define PUBLICDATA_H
#include <map>
#include "AircraftTrace.h"
namespace Controller_PublicData
{
     const int  RECVAIRCRAFTTRACEPORT = 10003;//接收航迹的UDP端口，和RDP发送航迹的UDP保持一致
}
class PublicData
{
private:
	 std::map<int,AircraftTrace> mapAircraftTrace;//存放航迹的映射表
public:
	 void _insert(std::pair<int,AircraftTrace>& vAircraftTrace)
	 {
		  mapAircraftTrace.insert(vAircraftTrace);
	 }
};
#endif