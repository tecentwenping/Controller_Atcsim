#ifndef NetDataDispenser_H
#define NetDataDispenser_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: NetDataDispenser
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/15
  【描  述】:  此文件定义了类NetDataDispenser，网络分发器，该类负责分发所有的网络包
               该类会循环扫描接入RDP的显示终端，依次分发当前最新的航迹点信息
			   1.获取在场航空器
			   2，冲突检测
			   3，发送命令
  【其  它】:   
**************************************************************************/
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QList>
#include <hash_map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <deque>
#include "wworldpoint.h"
#include "public/PublicStruct.h"
#include "Tools.h"
class AircraftTrace;
typedef boost::shared_ptr<AircraftTrace>			AircraftTracePtr;
typedef stdext::hash_map<int,AircraftTrace*>		hmFplTraces;
//typedef stdext::hash_map<int,std::vector<WPointF> > hmFplTracePoint;
typedef stdext::hash_map<int,std::deque<WPointF> > hmFplTracePoint;
class NetDataDispenser:public QObject
{
	Q_OBJECT

public:
	NetDataDispenser();
	~NetDataDispenser();
	 bool InitData();
	 void UpdateAircraftTrace(AircraftTrace* pTrace);
public:
	 void DispenserTraceToClient();
private:
	/**************************************************************************
	*函数名：AircraftTraceToDispenser
	*函数功能：查找那些在当前时间应该发送航迹的航班集合
	*变量：传入的参数可以唯一识别一条航迹
	**************************************************************************/
	void AircraftTraceToDispenser();
	/**************************************************************************
	*函数名：_SetSafeDistance
	*函数功能：传入一个航空器，算出其告警层和基础层的和，保护层需要根据尾流来确定
	*变量：
	**************************************************************************/
	void _SetSafeDistance(PublicDataStruct::Aircraft& aircraft);
    /**************************************************************************
    *函数名：_CollectionDetect
    *函数功能：冲突检测
    *变量：
    **************************************************************************/
	void _CollectionDetect();
	/**************************************************************************
	*函数名：CompuAngle
	*函数功能：根据TraceID计算出航空器的角度
	*变量：
	**************************************************************************/
	int CompuAngle(int iTraceID);
	/**************************************************************************
	*函数名：_CollisionDectect_Aux
	*函数功能：检测两个航空器之间的距离
	*变量：返回值是后点的ID
	**************************************************************************/
	void  _CollisionDectect_Aux(int iTraceID1,int iTraceID2);
	
	/**************************************************************************
	*函数名：_DisPenserTraceToClient
	*函数功能：执行分发任务的具体函数
	*变量：
	**************************************************************************/
	void _DisPenserTraceToClient();

private:
	bool							m_bInitDataSucess;
	std::map<AircraftTrace*,int>	m_mpTracePointCount;//航迹点计数器，用于标识当前某一个航迹应该所在的坐标位置
	hmFplTraces						m_hmTrace;
	hmFplTracePoint					m_hmTracePoint;
	QTimer							*m_pTimer;
	//========================================================================
	std::vector<int>				m_aircrftTraceToDispenserVec;
	std::vector<int>				m_aircraftTraceVec;
	std::vector<int>				m_aircraftStopVec;//需要停等的航空器的ID
	
};

#endif // NetDataDispenser_H
