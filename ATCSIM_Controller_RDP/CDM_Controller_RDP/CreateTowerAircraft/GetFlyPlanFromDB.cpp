#include <assert.h>
#include "GetFlyPlanFromDB.h"
#include "DBOperator/DataBase.h"
#include "SendFlyPlanToRDP.h"
#include "Interface/theApp.h"
#include "Manager/DataManager.h"
#include <boost/thread/shared_mutex.hpp>
CGetFlyPlanFromDB::CGetFlyPlanFromDB()
{
	
	qDebug()<<"Start DataBase thread sucessfully.....";
	bool isOpen = DataBaseAccessObj::GetInstance()->OpenDB();
	assert(isOpen);
		if(InitData())
		{
			qDebug()<<"Read FlyPlan sucessfully....";
			//������ʱ����ÿ30s��ȡһ�����ݿ⣬������µķ��мƻ���Ϣ
		}
	pTimer = new QTimer(this);
	connect(pTimer,SIGNAL(timeout()),this,SLOT(slot_ReadFlyPlanFromDB()),Qt::DirectConnection);
	pTimer->start(30000);
}
CGetFlyPlanFromDB::~CGetFlyPlanFromDB()
{
	DataBaseAccessObj::GetInstance()->func_closeConnection();
}
bool CGetFlyPlanFromDB::ReadFlyPlanFromDB()
{
	m_vecFlyPlan.clear();
	m_vecCurrentFlyPlan.clear();
	QString qStr="select PLAN_ACARS_FLIGHTNUMBER,PLAN_ACARS_SSR,PLAN_ACARS_RVSMSTATUS,PLAN_ACARS_TASKNATURE,PLAN_ACARS_ADDDEP,\
				 PLAN_ACARS_DES,PLAN_ACARS_ALTN1,PLAN_ACARS_RFL,PLAN_ACARS_TAS,PLAN_ACARS_ARWY,\
				 PLAN_ACARS_RUNWAY,PLAN_ACARS_ETD,PLAN_ACARS_ETA,PLAN_ACARS_ATD,PLAN_ACARS_ATA,\
				 PLAN_ACARS_ACFTTYPE,PLAN_ACARS_ACFTREGEST,PLAN_ACARS_TURBO from ATCSIM_PLAN_ACARS";
	QSqlQuery FlyPlanQuery = DataBaseAccessObj::GetInstance()->func_SqlDatabaseQuery(qStr);
	PublicDataStruct::SFlyPlanFromDB flyPlanFromDBStructTemp;
	while (FlyPlanQuery.next())
	{
		theData::instance().GetPublicDataPtr()->GetCurrentFlyPlan(m_vecCurrentFlyPlan);
		if(!m_vecCurrentFlyPlan.empty())
		{
			//���Ҳ�ѯ�����ĺ�����Ƿ��Ѿ����ڣ�������ڣ����ȡ��һ����¼
			std::vector<QString>::iterator Iter = find(m_vecCurrentFlyPlan.begin(),m_vecCurrentFlyPlan.end(),FlyPlanQuery.value(0).toString());
			if(Iter != m_vecCurrentFlyPlan.end())
				continue;
		}
		flyPlanFromDBStructTemp.sFlyPlanNum = FlyPlanQuery.value(0).toString();//�����
		flyPlanFromDBStructTemp.sSSRCode = FlyPlanQuery.value(1).toString();//������
		int nRVSM = FlyPlanQuery.value(2).toInt();//�Ƿ�߱�RSVM������1��ʾ�У�0��ʾû��
		flyPlanFromDBStructTemp.iFlyPlanType = FlyPlanQuery.value(3).toInt();//���мƻ�����
		flyPlanFromDBStructTemp.sDepDromeName =  FlyPlanQuery.value(4).toString();//��ɻ���
		flyPlanFromDBStructTemp.sArrDromeName = FlyPlanQuery.value(5).toString();//�������
		flyPlanFromDBStructTemp.sAlternateDrome = FlyPlanQuery.value(6).toString();//������
		flyPlanFromDBStructTemp.iCruiseLvl = FlyPlanQuery.value(7).toInt();//Ѳ���߶�
		flyPlanFromDBStructTemp.iCruiseSpd = FlyPlanQuery.value(8).toInt();//Ѳ���ٶ�
		flyPlanFromDBStructTemp.sArrRunway = FlyPlanQuery.value(9).toString();//�����ܵ�
		flyPlanFromDBStructTemp.sDepRunway = FlyPlanQuery.value(10).toString();//����ܵ�
		flyPlanFromDBStructTemp.sDepartureTime = FlyPlanQuery.value(11).toString();//Ԥ�����ʱ��
		flyPlanFromDBStructTemp.sArrivalTime = FlyPlanQuery.value(12).toString();//Ԥ�ƴﵽʱ��
		flyPlanFromDBStructTemp.sADepTime = FlyPlanQuery.value(13).toString();//ʵ�����ʱ��
		flyPlanFromDBStructTemp.sAArrTime = FlyPlanQuery.value(14).toString();//ʵ�ʽ���ʱ��
		flyPlanFromDBStructTemp.sModlType = FlyPlanQuery.value(15).toString();//������
		flyPlanFromDBStructTemp.sRegNum = FlyPlanQuery.value(16).toString();//ע���
		flyPlanFromDBStructTemp.sWeight = FlyPlanQuery.value(17).toString();//����
		//��Ҫ��һЩ����û�����ݿ��ж�ȡ������������дĬ��ֵ
		if(nRVSM == 0)  
		{
			flyPlanFromDBStructTemp.bRVSM = false;
		}
		//�洢���мƻ�	
		m_vecFlyPlan.push_back(flyPlanFromDBStructTemp);
		theData::instance().GetPublicDataPtr()->SetCurrentFlyPlan(FlyPlanQuery.value(0).toString());
	}
	//DataBaseAccessObj::GetInstance()->func_closeConnection();
	if(!m_vecFlyPlan.empty())
	{
		boost::shared_mutex sMutex;
		sMutex.lock();
		theData::instance().GetPublicDataPtr()->SetVecFlyPlanFromDB(m_vecFlyPlan);
		sMutex.unlock();
		return true;
	}
	return false;
}
 bool CGetFlyPlanFromDB::InitData()
 {
	  return ReadFlyPlanFromDB();
 }

 void CGetFlyPlanFromDB::slot_ReadFlyPlanFromDB()
 {
	 ReadFlyPlanFromDB();
 }
