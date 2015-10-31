#ifndef DATABASEBASECLASS_H
#define DATABASEBASECLASS_H
#ifdef CDM_OracleDatabaseAccessLIBDll  
#define CDM_OracleDatabaseAccessAPI _declspec(dllexport)  
#else  
#define CDM_OracleDatabaseAccessAPI  _declspec(dllimport)  
#endif 
#include <QtCore/qglobal.h>
#include <QSqlQuery>
#include <QDateTime>
#include <QString>
#include <QSettings>
#include <QSqlDriver>
#include <QSqlError>
#include <iostream>
#include <utility>
#include "myReflect.h"
// #ifdef   CDM_OracleDatabaseAccess_LIB
// # define CDM_OracleDatabaseAccess_EXPORT Q_DECL_EXPORT
// #else
// # define CDM_OracleDatabaseAccess_EXPORT Q_DECL_IMPORT
// #endif
class CDM_OracleDatabaseAccessAPI CDM_OracleDatabaseAccess
{
public:
	DECLARE_CLASS(CDM_OracleDatabaseAccess)
	QSqlDatabase m_db;//打开数据库
	QSqlQuery    *m_pQuery;
	QString		 m_currentSystemTime;
	bool		 m_isOpendb;
	bool         m_isQuerySuccess;
	QString		 m_DbDriver;

public:
	CDM_OracleDatabaseAccess(){m_pQuery=NULL;}
	~CDM_OracleDatabaseAccess(){
			if(NULL!=m_pQuery)
			{
				delete m_pQuery;
				m_pQuery=NULL;
	         }

	}
	static void* CreateInstance()
	{
		return new CDM_OracleDatabaseAccess();
	}
	const QString& func_getCurrentSystemTime();//获取当前系统时间
	void func_closeConnection();	
	void func_Init();
	QSqlQuery& func_SqlDatabaseQuery(const QString& sqlStr);//数据库操作
	bool func_SqlDatabaseQuery(const QSqlQuery*);
	bool OpenDB();//打开数据库
private:
	QSqlQuery    m_query;
};
#ifdef CDM_SQLDatabaseAccessLIBDll
#define CDM_SQLDatabaseAccessAPI _declspec(dllexport)
#else
#define CDM_SQLDatabaseAccessAPI _declspec(dllimport)
#endif
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlDriver>
#include <QSqlError>
#include <iostream>
#include "myReflect.h"
class CDM_SQLDatabaseAccessAPI CDM_SQLDatabaseAccess
{
	
	public:
	DECLARE_CLASS(CDM_SQLDatabaseAccess)
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
	/*********************************************************
	*函数名：SQLQuery
	*函数功能：从数据库查询数据
	*变量：
	**********************************************************/
	QSqlQuery& SQLQuery(const QString& aSqlStr);

	static void* CreateInstance()
	{
		return new CDM_SQLDatabaseAccess();
	}
	~CDM_SQLDatabaseAccess()
	{
		if(NULL != m_pSqlQuery)
		{
			delete m_pSqlQuery;
			m_pSqlQuery = NULL;
		}
	}
protected:
	void InitDBInformation();
private:
	QSqlDatabase m_SqlDBObj;//数据库访问对象
	bool         m_bIsOpenDB;//是否开启了数据库
	QSqlQuery*   m_pSqlQuery;
	QString		 m_DbDriver;


};
#ifdef CDM_classFactoryLIBDll  
#define CDM_classFactoryAPI _declspec(dllexport)  
#else  
#define CDM_classFactoryAPI  _declspec(dllimport)  
#endif 
class  CDM_classFactoryAPI CDM_classFactory
{
public:
   static void* CreateDatabaseInstance(QString );

};
//#ifdef DataBaseAccessInterfaceLIBDll
//#define DataBaseAccessInterfaceAPI _declspec(dllexport)
//#else
//#define DataBaseAccessInterfaceAPI _declspec(dllimport)
//#endif
//#include "myReflect.h"
//class DataBaseAccessInterfaceAPI DataBaseAccessInterface
//{
//public:
//	DECLARE_CLASS(DataBaseAccessInterface)
//	DataBaseAccessInterface(){
//		m_pOracleDBConnection = new CDM_OracleDatabaseAccess();
//		m_pSQLDBConnection = new CDM_SQLDatabaseAccess();
//	}
//	static CDM_OracleDatabaseAccess* GetInstance(){ return m_pOracleDBConnection; }
//		
//	static CDM_SQLDatabaseAccess*    GetSQLAccessInstance(){ return m_pSQLDBConnection;}
//protected:
//	static void* CreateInstance()
//	{
//		return new DataBaseAccessInterface();
//	}
//private:
//		static CDM_OracleDatabaseAccess *m_pOracleDBConnection;
//		static CDM_SQLDatabaseAccess    *m_pSQLDBConnection;
//	
//};
#endif