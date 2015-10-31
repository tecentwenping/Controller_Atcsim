#ifndef CSendFlyPlanToRDP_H
#define CSendFlyPlanToRDP_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CSendFlyPlanToRDP
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/25
  【描  述】:  此文件定义了类CSendFlyPlanToRDP，该类的作用是发送飞行计划到RDP
  【其  它】:   
**************************************************************************/

#include <QObject>
#include <QUdpSocket>
#include <vector>

class CSendFlyPlanToRDP : public QObject
{
	Q_OBJECT

public:
	CSendFlyPlanToRDP();
	~CSendFlyPlanToRDP();
	private slots:
		void slot_SendFlyPlanToRDP();
		void slot_StartSendFlyPlanToRDP();
private:
	QUdpSocket *m_UdpSendFlyPlanToRDPSocket;//向RDP发送飞行计划的UDP套接字
	static const int SENDFLYPLANPORT = 9903; //发送飞行计划UDP端口，发送的目的地是RDP
	int m_iCount;
	
};

#endif // CSendFlyPlanToRDP_H
