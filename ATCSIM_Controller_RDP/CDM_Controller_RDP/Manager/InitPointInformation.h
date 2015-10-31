#ifndef INITPOINTINFORMATION_H
#define INITPOINTINFORMATION_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: 
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/12/27
  【描  述】:  此文件定义了类CInitPointInformation，本类的作用是读取数据库
			   中的机场点的信息为路径规划做好准备
  【其  它】:   
**************************************************************************/
#include <QObject>
#include <QSqlQuery>
class CInitPointInformation : public QObject
{
	Q_OBJECT

public:
	CInitPointInformation();
	~CInitPointInformation();
	void Init();
//protected:
public:
	/*********************************************************
	*函数名：GetTaxiLineFromDB
	*函数功能：从数据库读取滑行道信息
	*变量：
	**********************************************************/
	void GetTaxiLineFromDB();
	/*********************************************************
	*函数名：GetFixPointFromDB
	*函数功能：从数据库读取固定点
	*变量：
	**********************************************************/
	void GetFixPointFromDB();
	/*********************************************************
	*函数名：GetRoadFixPointFromDB
	*函数功能：从数据库读取道路上的固定点信息
	*变量：
	**********************************************************/
	void GetRoadFixPointFromDB();
private:
	QSqlQuery& QueryDataFromDB(const QString& sqlStr);
private:
    QSqlQuery m_queryObj;
	
};
#endif // INITPOINTINFORMATION_H
