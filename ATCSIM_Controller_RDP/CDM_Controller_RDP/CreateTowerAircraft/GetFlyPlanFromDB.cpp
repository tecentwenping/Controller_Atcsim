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
			//启动定时器，每30s读取一次数据库，获得最新的飞行计划信息
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
			//查找查询出来的航班号是否已经存在，如果存在，则读取下一条记录
			std::vector<QString>::iterator Iter = find(m_vecCurrentFlyPlan.begin(),m_vecCurrentFlyPlan.end(),FlyPlanQuery.value(0).toString());
			if(Iter != m_vecCurrentFlyPlan.end())
				continue;
		}
		flyPlanFromDBStructTemp.sFlyPlanNum = FlyPlanQuery.value(0).toString();//航班号
		flyPlanFromDBStructTemp.sSSRCode = FlyPlanQuery.value(1).toString();//二次码
		int nRVSM = FlyPlanQuery.value(2).toInt();//是否具备RSVM能力，1表示有，0表示没有
		flyPlanFromDBStructTemp.iFlyPlanType = FlyPlanQuery.value(3).toInt();//飞行计划类型
		flyPlanFromDBStructTemp.sDepDromeName =  FlyPlanQuery.value(4).toString();//起飞机场
		flyPlanFromDBStructTemp.sArrDromeName = FlyPlanQuery.value(5).toString();//降落机场
		flyPlanFromDBStructTemp.sAlternateDrome = FlyPlanQuery.value(6).toString();//备降场
		flyPlanFromDBStructTemp.iCruiseLvl = FlyPlanQuery.value(7).toInt();//巡航高度
		flyPlanFromDBStructTemp.iCruiseSpd = FlyPlanQuery.value(8).toInt();//巡航速度
		flyPlanFromDBStructTemp.sArrRunway = FlyPlanQuery.value(9).toString();//降落跑道
		flyPlanFromDBStructTemp.sDepRunway = FlyPlanQuery.value(10).toString();//起飞跑道
		flyPlanFromDBStructTemp.sDepartureTime = FlyPlanQuery.value(11).toString();//预计起飞时间
		flyPlanFromDBStructTemp.sArrivalTime = FlyPlanQuery.value(12).toString();//预计达到时间
		flyPlanFromDBStructTemp.sADepTime = FlyPlanQuery.value(13).toString();//实际起飞时间
		flyPlanFromDBStructTemp.sAArrTime = FlyPlanQuery.value(14).toString();//实际降落时间
		flyPlanFromDBStructTemp.sModlType = FlyPlanQuery.value(15).toString();//机型名
		flyPlanFromDBStructTemp.sRegNum = FlyPlanQuery.value(16).toString();//注册号
		flyPlanFromDBStructTemp.sWeight = FlyPlanQuery.value(17).toString();//载重
		//还要做一些处理，没从数据库中读取到的数据则填写默认值
		if(nRVSM == 0)  
		{
			flyPlanFromDBStructTemp.bRVSM = false;
		}
		//存储飞行计划	
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
