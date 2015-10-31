#ifndef CInitPathInformation_H
#define CInitPathInformation_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CInitPathInformation
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/22
  【描  述】:  此文件定义了类CInitPathInformation,该类的作用是从本地文件读取
               离线配置的路径信息。
  【其  它】:  离线路径是手工指定的，版本1.0设置为静态固定   
**************************************************************************/

//#include <QObject>
#include "Manager/ReadFile.h"
class CInitPathInformation:public CFile
{
public:
	CInitPathInformation();
	~CInitPathInformation();
	void ReadInformationFromFile();
};
#endif // CInitPathInformation_H
