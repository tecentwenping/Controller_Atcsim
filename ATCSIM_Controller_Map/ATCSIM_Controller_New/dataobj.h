#ifndef DATAOBJ_H
#define DATAOBJ_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: DataObj
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/11/12
  ����  ����:  ���ļ����������ݶ�����࣬������һЩͨ�÷��������л����ݵķ���
  ����  ����:   
**************************************************************************/

#include <string>
#include <vector>

class DataObj
{
public:
	DataObj();
	virtual ~DataObj();
public:
	//ͨ�õķ���
	virtual  int GetId();
	virtual  int GetOwnerId();
	virtual  std::string GetDisplayLabel();
	virtual  std::string GetObjName();
	virtual  bool IsEqual(DataObj* dataobj);
	virtual  void Copy(DataObj* dataobj);
	//���л�����
	virtual void ReadFromBuffer(const char* pBuffer,int iOffSize);
	virtual void WriteToBuffer(char *pBuffer,int iOffSize);
	virtual int GetBufferSize();

	
};

#endif // DATAOBJ_H
