#include "airport_dbaccess.h"
#include <QString>
#include <QSqlQuery>
#include <vector>
#include <assert.h>
#include <QVariant>
#include <utility>
QSqlDatabase AirPort_DBAccess::m_db;
//std::multimap<int,MapPoint> AirPort_DBAccess::m_pointMap;
AirPort_DBAccess::AirPort_DBAccess()
{
	//打开数据库
	QString dsn=QString::fromLocal8Bit("DRIVER={SQL SERVER};SERVER=192.168.0.65;DATABASE=shuangliu_ATCSIM");
	m_db = QSqlDatabase::addDatabase("QODBC"); 
	m_db.setHostName("192.168.0.65");
	m_db.setDatabaseName(dsn);  
	m_db.setUserName("sa");  
	m_db.setPassword("123456");
}
bool AirPort_DBAccess::OpenDB()
{
	return (m_db.open());
}

void AirPort_DBAccess::CloseDB()
{
     m_db.close();
}
QSqlQuery AirPort_DBAccess::SQLQuery( const QString& aSqlStr )
{
	QSqlQuery m_query(m_db);
	m_query.exec(aSqlStr);
	return m_query;
}
