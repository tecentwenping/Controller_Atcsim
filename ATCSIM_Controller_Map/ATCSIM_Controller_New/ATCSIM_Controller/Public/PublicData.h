#ifndef PUBLICDATA_H
#define PUBLICDATA_H
#include <map>
#include "AircraftTrace.h"
namespace Controller_PublicData
{
     const int  RECVAIRCRAFTTRACEPORT = 10003;//���պ�����UDP�˿ڣ���RDP���ͺ�����UDP����һ��
}
class PublicData
{
private:
	 std::map<int,AircraftTrace> mapAircraftTrace;//��ź�����ӳ���
public:
	 void _insert(std::pair<int,AircraftTrace>& vAircraftTrace)
	 {
		  mapAircraftTrace.insert(vAircraftTrace);
	 }
};
#endif