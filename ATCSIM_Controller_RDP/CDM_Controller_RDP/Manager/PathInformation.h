#ifndef CInitPathInformation_H
#define CInitPathInformation_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CInitPathInformation
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/22
  ����  ����:  ���ļ���������CInitPathInformation,����������Ǵӱ����ļ���ȡ
               �������õ�·����Ϣ��
  ����  ����:  ����·�����ֹ�ָ���ģ��汾1.0����Ϊ��̬�̶�   
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
