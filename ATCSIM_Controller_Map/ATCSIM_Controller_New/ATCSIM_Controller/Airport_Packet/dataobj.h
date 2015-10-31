#ifndef DATAOBJ_H
#define DATAOBJ_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: DataObj
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2014/11/12
  【描  述】:  此文件定义了数据对象基类，定义了一些通用方法和序列化数据的方法
  【其  它】:   
**************************************************************************/

#include <string>
#include <vector>

class DataObj
{
public:
	DataObj();
	virtual ~DataObj();
public:
	//通用的方法
	virtual  int GetId();
	virtual  int GetOwnerId();
	virtual  std::string GetDisplayLabel();
	virtual  std::string GetObjName();
	virtual  bool IsEqual(DataObj* dataobj);
	virtual  void Copy(DataObj* dataobj);
	//序列化方法
	virtual void ReadFromBuffer(const char* pBuffer,int iOffSize);
	virtual void WriteToBuffer(char *pBuffer,int iOffSize);
	virtual int GetBufferSize();

	
};

#endif // DATAOBJ_H
