#ifndef INITPOINTINFORMATION_H
#define INITPOINTINFORMATION_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: 
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/27
  ����  ����:  ���ļ���������CInitPointInformation������������Ƕ�ȡ���ݿ�
			   �еĻ��������ϢΪ·���滮����׼��
  ����  ����:   
**************************************************************************/
#include <QObject>
#include <QSqlQuery>
class CInitPointInformation : public QObject
{
	Q_OBJECT

public:
	CInitPointInformation();
	~CInitPointInformation();
	void Init();
//protected:
public:
	/*********************************************************
	*��������GetTaxiLineFromDB
	*�������ܣ������ݿ��ȡ���е���Ϣ
	*������
	**********************************************************/
	void GetTaxiLineFromDB();
	/*********************************************************
	*��������GetFixPointFromDB
	*�������ܣ������ݿ��ȡ�̶���
	*������
	**********************************************************/
	void GetFixPointFromDB();
	/*********************************************************
	*��������GetRoadFixPointFromDB
	*�������ܣ������ݿ��ȡ��·�ϵĹ̶�����Ϣ
	*������
	**********************************************************/
	void GetRoadFixPointFromDB();
private:
	QSqlQuery& QueryDataFromDB(const QString& sqlStr);
private:
    QSqlQuery m_queryObj;
	
};
#endif // INITPOINTINFORMATION_H
