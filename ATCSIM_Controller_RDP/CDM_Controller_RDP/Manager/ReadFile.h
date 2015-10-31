#ifndef CFile_H
#define CFile_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CFile
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/22
  ����  ����:  ���ļ���������CFile,�����������ļ������Ļ���
  ����  ����:   
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
	*��������GetInfoFromFile
	*��������:��txt�ļ��ж�ȡ�ļ���Ϣ
	*������qFileName�Ǵ�����ļ���,qStringList�Ǵ洢��Ϣ����
	**************************************************************************/
    virtual void GetInfoFromFile(const QString &qFileName,QStringList &qStringList);
    /**************************************************************************
    *��������GetInfoFromFile
    *�������ܣ�GetInfoFromFile���ذ汾
	(����/���)����Ϣ�����һ�����ݽṹ
	*������qFileName��ȡ�ļ��ļ�����sFlag��־���ǻ�������㣬�̶��Ļ�λ�й̶���
	����㣻VecGateInformation�Ǵ洢ͣ��λ��Ϣ��ӳ���
    **************************************************************************/
	 void GetInfoFromFile(const QString &qFileName,std::vector<QStringList>& VecGateInformation);

	 void GetInfoFromFile(const QString& qFileName,std::map<QString,QStringList>& vMap);

};

#endif // CFile_H
