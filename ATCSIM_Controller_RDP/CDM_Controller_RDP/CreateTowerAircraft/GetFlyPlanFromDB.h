#ifndef CGetFlyPlanFromDB_H
#define CGetFlyPlanFromDB_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CGetFlyPlanFromDB
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/24
  【描  述】:  此文件定义了CGetFlyPlanFromDB类，该类用于从数据库中读取飞行计划
  【其  它】:   
**************************************************************************/

#include <QObject>
#include <QSqlQuery>
#include <vector>
#include "DBOperator/DataBaseAccess.h"
#include "DBOperator/MyReflect.h"
#include "public/PublicStruct.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QTimer>
class SFlyPlanFromDB;
class CSendFlyPlanToRDP;
typedef boost::shared_ptr<CSendFlyPlanToRDP> sendFlyPlanPtr;
typedef std::vector<PublicDataStruct::SFlyPlanFromDB> VecFlyPlan;
class CGetFlyPlanFromDB : public QObject
{
	Q_OBJECT

public:
	CGetFlyPlanFromDB();
	~CGetFlyPlanFromDB();
protected:
	/*********************************************************
	*函数名：ReadFlyPlanFromDB
	*函数功能：从数据库中读取飞行计划，存储在m_vecFlyPlan中
	*变量：
	**********************************************************/
	bool		ReadFlyPlanFromDB();
	bool		InitData();//初始化数据
	private slots:
		void   slot_ReadFlyPlanFromDB();
private:
	QSqlQuery		m_FlyPlanQuery;
	VecFlyPlan		m_vecFlyPlan;
	sendFlyPlanPtr	m_pSendFlyPlan;
	std::vector<QString> m_vecCurrentFlyPlan;
	QTimer * pTimer;
};

#endif // CGetFlyPlanFromDB_H
