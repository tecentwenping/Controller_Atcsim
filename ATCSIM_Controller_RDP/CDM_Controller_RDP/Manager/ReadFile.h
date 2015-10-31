#ifndef CFile_H
#define CFile_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CFile
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/22
  【描  述】:  此文件定义了类CFile,该类是所有文件操作的基类
  【其  它】:   
**************************************************************************/
#include <vector>
#include <QStringList>
#include <QString>
#include <map>
#include "PublicData.h"
class CFile
{

public:
	CFile();
	virtual ~CFile();
public:
	virtual void ReadInformationFromFile();
protected:
	/**************************************************************************
	*函数名：GetInfoFromFile
	*函数功能:从txt文件中读取文件信息
	*变量：qFileName是传入的文件名,qStringList是存储信息容器
	**************************************************************************/
    virtual void GetInfoFromFile(const QString &qFileName,QStringList &qStringList);
    /**************************************************************************
    *函数名：GetInfoFromFile
    *函数功能：GetInfoFromFile重载版本
	(进港/离港)等信息，组成一个数据结构
	*变量：qFileName读取文件文件名，sFlag标志的是机场进入点，固定的机位有固定的
	进入点；VecGateInformation是存储停机位信息的映射表
    **************************************************************************/
	 void GetInfoFromFile(const QString &qFileName,std::vector<QStringList>& VecGateInformation);

	 void GetInfoFromFile(const QString& qFileName,std::map<QString,QStringList>& vMap);

};

#endif // CFile_H
