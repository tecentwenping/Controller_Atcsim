#include "ReadFile.h"
#include <assert.h>
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QDateTime>
#include <QSettings>
#include <QFile>
#include <vector>
#include <utility>
#include <QTextStream>
#include <QTimer>
#include <QDebug>
#include "DBOperator/DataBase.h"
#include "Mutex.h"
#include "Manager/DataManager.h"
CFile::CFile()
{
}

CFile::~CFile()
{

}
void CFile::GetInfoFromFile( const QString &qFileName,QStringList &qStringList )
{
	
	QFile file(qFileName);//读取文件对象
	assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
	QTextStream textStream(&file);
	QString qStrData = textStream.readAll();//全部读取
	qStringList = qStrData.split("\n", QString::SkipEmptyParts);//以换行符分割,放入链表中
	file.close();
     
}
void CFile::GetInfoFromFile( const QString &qFileName,std::vector<QStringList>& VecGateInformation )
{
	QFile file(qFileName);//读取文件对象
	assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
	QTextStream textStream(&file);
	QString qStrData = textStream.readAll();//全部读取
	QStringList qStringList = qStrData.split("\n", QString::SkipEmptyParts);//以换行符分割
	QStringList qTempStringList;
	CQMutex qMutex;
	for(int i=0;i!=qStringList.size();++i)
	{
		qMutex.MyLock();
		qTempStringList = qStringList.at(i).split(",",QString::SkipEmptyParts);//停机位信息
		VecGateInformation.push_back(qTempStringList);
		qMutex.MyUnlock();
	}
}

void CFile::ReadGateInformation()
{

}
void CFile::GetInfoFromFile(const QString& qFileName,std::map<QString,QStringList>& vMap)
{
	QFile file(qFileName);//读取文件对象
	assert(file.open(QIODevice::ReadOnly | QIODevice::Text));
	QTextStream textStream(&file);
	QString qStrData = textStream.readAll();//全部读取
	QStringList qStringList = qStrData.split("\n", QString::SkipEmptyParts);//以换行符分割
	QStringList qTempStringList;
	CQMutex qMutex;
	for(int i=0;i!=qStringList.size();++i)
	{
		qMutex.MyLock();
		qTempStringList = qStringList.at(i).split(",",QString::SkipEmptyParts);//停机位信息
		vMap.insert(std::make_pair(qTempStringList.at(0),qTempStringList));
		qMutex.MyUnlock();
	}
}

