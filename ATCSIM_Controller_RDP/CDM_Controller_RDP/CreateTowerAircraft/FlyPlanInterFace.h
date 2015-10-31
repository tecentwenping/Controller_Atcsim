#ifndef CFlyPlanInterFace_H
#define CFlyPlanInterFace_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CFlyPlanInterFace
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/25
  【描  述】:  此文件定义了类CFlyPlanInterFace，是关于飞行计划一系列操作的接口封装
  【其  它】:   
**************************************************************************/

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QThread>
#include <QObject>
class CGetFlyPlanFromDB;
class CSendFlyPlanToRDP;
typedef boost::shared_ptr<CGetFlyPlanFromDB> CGetFlyPlanFromDBPtr;
typedef boost::shared_ptr<CSendFlyPlanToRDP> CSendFlyPlanToRDPPtr;

class CFlyPlanInterFace : public QObject
{
	Q_OBJECT

public:
	CFlyPlanInterFace();
	~CFlyPlanInterFace();
private:
	void    myInitGetFlyPlanFunc();//初始化获取飞行计划的函数
private:
	CGetFlyPlanFromDBPtr  m_pGetFlyPlanFromDB;
	CSendFlyPlanToRDPPtr  m_pSendFlyPlanToRDP;
	
};

#endif // CFlyPlanInterFace_H
