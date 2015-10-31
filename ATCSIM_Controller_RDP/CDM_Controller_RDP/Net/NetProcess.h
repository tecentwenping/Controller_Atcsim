#ifndef NETPROCESS_H
#define NETPROCESS_H

/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: NetProcess
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/01
  【描  述】:  此文件定义了类NetProcess，该类的作用处理网络包
  【其  它】:   
**************************************************************************/
#include <QUdpSocket>
#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class AircraftTrace;
class NetProcess:public QObject
{
	Q_OBJECT
public:

public:
	NetProcess();
	~NetProcess();
	QUdpSocket& GetSendTraceUdpSocket(){return *m_pUdpSendTraceSocket;}
	/*********************************************************
	*函数名：SendSingleTrace
	*函数功能：向显示界面发送航迹
	*变量：
	**********************************************************/
	void SendAircraftTrace(const AircraftTrace& vAircraftTrace);

private:
	QUdpSocket *m_pUdpSendTraceSocket;//发送航迹到显示界面的Socket
};

#endif // NETPROCESS_H
