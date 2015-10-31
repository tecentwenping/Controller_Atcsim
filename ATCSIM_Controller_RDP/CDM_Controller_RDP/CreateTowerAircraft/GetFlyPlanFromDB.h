#ifndef CGetFlyPlanFromDB_H
#define CGetFlyPlanFromDB_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CGetFlyPlanFromDB
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/24
  ����  ����:  ���ļ�������CGetFlyPlanFromDB�࣬�������ڴ����ݿ��ж�ȡ���мƻ�
  ����  ����:   
**************************************************************************/

#include <QObject>
#include <QSqlQuery>
#include <vector>
#include "DBOperator/DataBaseAccess.h"
#include "DBOperator/MyReflect.h"
#include "public/PublicStruct.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QTimer>
class SFlyPlanFromDB;
class CSendFlyPlanToRDP;
typedef boost::shared_ptr<CSendFlyPlanToRDP> sendFlyPlanPtr;
typedef std::vector<PublicDataStruct::SFlyPlanFromDB> VecFlyPlan;
class CGetFlyPlanFromDB : public QObject
{
	Q_OBJECT

public:
	CGetFlyPlanFromDB();
	~CGetFlyPlanFromDB();
protected:
	/*********************************************************
	*��������ReadFlyPlanFromDB
	*�������ܣ������ݿ��ж�ȡ���мƻ����洢��m_vecFlyPlan��
	*������
	**********************************************************/
	bool		ReadFlyPlanFromDB();
	bool		InitData();//��ʼ������
	private slots:
		void   slot_ReadFlyPlanFromDB();
private:
	QSqlQuery		m_FlyPlanQuery;
	VecFlyPlan		m_vecFlyPlan;
	sendFlyPlanPtr	m_pSendFlyPlan;
	std::vector<QString> m_vecCurrentFlyPlan;
	QTimer * pTimer;
};

#endif // CGetFlyPlanFromDB_H
