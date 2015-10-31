#ifndef CPathPlanning_H
#define CPathPlanning_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: 
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/23
  【描  述】:  此文件定义了类CDM_PathPlaning类，该类的主要作用是规划机场飞机从
               起点到终点的路径，并组成一个路径串，再经过网络模块将这些路径数据
			   发送到显示界面，显示界面进行相应的显示
  【其  它】:   
**************************************************************************/

#include <QObject>
#include <vector>
#include <QTimer>
#include "PublicStruct.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/shared_mutex.hpp>
class AircraftTrace;
class ControllerPresenter;
class NetProcess;
class ControllerAircraftTrace;
//////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<AircraftTrace> AircraftTracePtr;
typedef boost::shared_ptr<ControllerPresenter> ControllerPresenterPtr;
typedef boost::shared_ptr<NetProcess> NetProcessPtr;
typedef boost::shared_ptr<ControllerAircraftTrace> ControllerAircraftTracePtr;
class CPathPlanning : public QObject
{
	Q_OBJECT
public:
	typedef PublicDataStruct::SDPSTrack track_type;
public:
	CPathPlanning();
	~CPathPlanning();
     void PathPlaning();
protected:
	/*********************************************************
	*函数名：GetAircraftBaseInformation
	*函数功能：获取计划的基本信息
	*变量：towAircraftPacket
	**********************************************************/
	void GetPlanBaseInformation(const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket);
private:
	/*********************************************************
	*函数名：GetSourceAndDest
	*函数功能：得到路径规划的起点和终点，数据来源于TowerAircraftPacket
	*变量：towAircraftPacket飞机包
	**********************************************************/
	void GetSourceAndDest(const PublicDataStruct::TowerAircraftPacketStruct& towAircraftPacket);
	/**************************************************************************
	*函数名：SettAircraftTraceDefaulValue
	*函数功能：认为的设定一些航迹默认值，该函数主要是测试阶段使用
	*变量：
	**************************************************************************/
	void SettAircraftTraceDefaulValue(AircraftTrace& vAircraftTrace);
private slots:
	/*********************************************************
	*函数名：PathPlaningStart
	*函数功能：开始路径规划
	*变量：
	**********************************************************/
	void slot_StartPathPlaning(int iFlightID);
signals:
	void sig_ReTranslateTowerAircraftPacket(int iFlightID);
private:
	double					m_dInitLongtitude; //飞机出现的初始经度
	double					m_dInitLatitude;   //飞机出现的初始纬度
	std::string				m_DepGate;			//离场停机位
	std::string				m_ArrGate;			//进场停机位
	double					m_dSpeed;//速度
	double					m_dFinishTime;//滑到指定位置的固定时间
	double					m_dInternalTime;//更新航迹的时间间隔
	track_type				m_Track;
	ControllerPresenterPtr	m_pControllerPressenter;
	AircraftTracePtr		m_pAircraftTrace;
	NetProcessPtr			m_pSendAircraftTrace;
	PublicDataStruct::AircraftTrace m_aircraftTrace;
	boost::shared_mutex     m_traceCheckLocker;  //保存航迹更新和航迹检测修改的锁
	//////////////////////////////////////////////////////////////////////////
	int iCount;//用于标示发送哪一个航迹点
	QTimer					m_Timer;
	bool					m_isFinished;	
};

#endif // CPathPlanning_H
