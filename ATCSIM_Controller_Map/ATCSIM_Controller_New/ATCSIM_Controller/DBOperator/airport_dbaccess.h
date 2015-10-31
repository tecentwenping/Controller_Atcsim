#ifndef AIRPORT_DBACCESS_H
#define AIRPORT_DBACCESS_H
///*********************************************************************///
//@类名：AirPort_DBAccess
//@Author:陈文平                                                          
//@Time:2014-11-10                                                        
//@Descirption:数据库访问类，提供数据库访问支持                                                           
////*********************************************************************//
#include <QObject>
#include <QSqlDatabase>
#include <map>
#include <vector>
class AirPort_DBAccess : public QObject
{
	Q_OBJECT

public:
	/**************************************************************************
	*函数名：OpenDB
	*函数功能：打开数据库，返回bool变量，false表示没打开，true表示打开
	**************************************************************************/
	 bool OpenDB();
	/**************************************************************************
	*函数名：CloseDB
	*函数功能：关闭数据库
	*变量：
	**************************************************************************/
   	 void CloseDB();
	AirPort_DBAccess();
	/*********************************************************
	*函数名：SQLQuery
	*函数功能：从数据库查询数据
	*变量：
	**********************************************************/
	QSqlQuery SQLQuery(const QString& aSqlStr);

private:
	static QSqlDatabase m_db;//数据库访问对象
};

#endif // AIRPORT_DBACCESS_H
