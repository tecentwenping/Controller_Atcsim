#include "NetDataDispenser.h"
#include "Interface/theApp.h"
#include "PathPlaning/AircraftTrace.h"
#include "Manager/DataManager.h"
#include "PathPlaning/TotalAircraftTrace.h"
#include "Manager/NetManager.h"
#include "Net/NetProcess.h"
#include "Manager/DataManager.h"
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <QTime>
#include <algorithm>
const double PI=3.1415926;
NetDataDispenser::NetDataDispenser():m_bInitDataSucess(false)
{  
	//分发器加载的时候，会首先先读一次数据，看是否有航迹
	if(InitData())
	{
		m_bInitDataSucess = true;//读取到了数据
	}
}
NetDataDispenser::~NetDataDispenser()
{

}
void NetDataDispenser::DispenserTraceToClient()
{ 
	//如果并且读到数据，则直接返回，等待下一次调用
     if(! m_bInitDataSucess)
	 {
		 return;
	 }
	 //对场面航空器做标记，标记AircraftTrace.m_aircraftInfo.bStop属性，该属性用于表面当前航空器运动还是停止
	 //如果bStop属性为true，那本轮扫描跳过该条航迹，不给其发送位置坐标，如果为false，则继续让其运动
	 _CollectionDetect();
	 _DisPenserTraceToClient();
}
bool NetDataDispenser::InitData()
{
	//获得最新的航迹信息
	theApp::instance().GetDataManagerPtr()->GetTotalAircraftTracePtr()->GetTraces(m_hmTrace);
	//theApp::instance().GetDataManagerPtr()->GetTotalAircraftTracePtr()->GetAircraftTracePoint(m_hmTracePoint);
    theApp::instance().GetDataManagerPtr()->GetTotalAircraftTracePtr()->GetAircraftTracePoint1(m_hmTracePoint);
	if(m_hmTrace.empty()||m_hmTracePoint.empty())
	{
		return false;
	}
	return true;
}
void NetDataDispenser::UpdateAircraftTrace(AircraftTrace* pTrace )
{
	//新加入的航迹计数等于0，也即下次更所有航迹信息时，这个新航迹会从第一个点开始移动
	 boost::shared_mutex tmpMutex;
	 tmpMutex.lock();
	 m_mpTracePointCount.insert(std::make_pair(pTrace,0));
	 tmpMutex.unlock();
	//重置一下航迹表和存放航迹点的容器，保持当前最新的数据
	 m_bInitDataSucess = InitData();
}

void NetDataDispenser::AircraftTraceToDispenser()
{  
	QTime currentTime;
	MapTowerAircraftPacket& mTowerAircraftPacket=theData::instance().GetMapTowerAircraftPacket();
	hmFplTraces::iterator traceIter = m_hmTrace.begin();
	while(traceIter!=m_hmTrace.end()){
		int traceID=traceIter->first;//飞行计划ID
		MapTowerAircraftPacket::iterator Iter=mTowerAircraftPacket.find(traceID);
		//下面的代码主要功能是筛选需要发送航迹的traceID,具体实现是：
		//获得当前的时间，和飞行计划的时间进行比较，如果和当前时间一致，
		//那么就把需要发送航迹的traceID放到一个容器中，分发函数回去读取
		//这个容器的ID，将航迹更新到显示界面
		if(Iter!= mTowerAircraftPacket.end()){
			PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct=(*Iter).second.TowerplanFlight;
			int planType=towerFlightPlanStruct.iFlyPlanType;
			std::string planTime="";
			if(0==planType){//离港航班
				  planTime=towerFlightPlanStruct.sDepartureTime;
				//strcpy(planTime.c_str(),towerFlightPlanStruct.sDepartureTime);
			}else{//进港航班
				planTime=towerFlightPlanStruct.sArrivalTime;
				//strcpy(planTime.c_str(),towerFlightPlanStruct.sArrivalTime);
			}
			currentTime=QTime::currentTime();
			int currentHour=currentTime.hour();//获取当前小时
			int currentMin=currentTime.minute();//获取当前分钟
			std::string hourStr,minStr,timeStr;
			CTools::ConvertInt2String(currentHour,hourStr);
			CTools::ConvertInt2String(currentMin,minStr);
			timeStr=hourStr+minStr;
			if(strcmp(planTime.c_str(),timeStr.c_str())==0)
				m_aircrftTraceToDispenserVec.push_back(traceID);
		}
	}
}



void NetDataDispenser::_CollectionDetect()
{
   AircraftTraceToDispenser();//获取在场的飞行器

   if(m_aircrftTraceToDispenserVec.empty()){
	   return;
   }
   //循环场面航空器，确定两个航空器之间的关系，也即前后两个点，如果两个
   //航空器之间有冲突，则要采取停等策略
   for(unsigned int i=0;i!=m_aircrftTraceToDispenserVec.size()-1;++i){
	   unsigned int j=1+1;
	   //计算角度
	   int iAngle1=CompuAngle(m_aircrftTraceToDispenserVec[i]);
	   while(j++!=m_aircrftTraceToDispenserVec.size()){
		   int iAngle2=CompuAngle(m_aircrftTraceToDispenserVec[j]);
		   if(iAngle1-iAngle2>PI/2)
			   continue;
           //计算两个航空器的距离，确定是否是在冲突范围内，并根据其在场面的先后关系，确定停等策略
		  _CollisionDectect_Aux(m_aircrftTraceToDispenserVec[i],m_aircrftTraceToDispenserVec[j]);
	   }
   }
}

int NetDataDispenser::CompuAngle( int iTraceID )
{
	//计算角度，角度不超过PI/2的才认为两个航空器方向大体一致
	int iAngle=0;
    hmFplTracePoint::iterator Iter1=m_hmTracePoint.find(iTraceID);
	if(Iter1!=m_hmTracePoint.end()){

		std::deque<WPointF> deqTracePoint=Iter1->second;
		hmFplTraces fplTraces;
		theData::instance().GetAircraftTrace(fplTraces);
		hmFplTraces::iterator Iter2=fplTraces.find(iTraceID);
		if(Iter2!=fplTraces.end()){

			std::vector< boost::shared_ptr<WPointF> > HistoryPos=Iter2->second->m_vHistoryPos;
			
			double dCurX=Iter2->second->m_fAbsX;
			double dCurY=Iter2->second->m_fAbsY;

			double dHistoryX=0.0,dHistoryY=0.0;
			if(!HistoryPos.empty()){
				
				dHistoryX=Iter2->second->m_vHistoryPos.back().get()->rx();
				dHistoryY=Iter2->second->m_vHistoryPos.back().get()->ry();
			}

			double dTempx=dCurX-dHistoryX;
			double dTempy=dCurY-dHistoryY;

			double root=sqrt(dTempx*dTempx+dTempy*dTempy);

			//预计线角度更新
			iAngle = (int)(asin(-dTempx/root)*(180/M_PI));

			if (dTempy > 0)
			{
				iAngle = 180 - iAngle;
			}
			iAngle = (iAngle+360)%360;
		}
	}
	return iAngle;

}

void  NetDataDispenser::_CollisionDectect_Aux( int iTraceID1,int iTraceID2 )
{
   //判定两个航空器是否在冲突范围之内
   //固定其中一个点，找出另一个点的下一个坐标，计算机距离
	hmFplTraces fplTraces;
	theData::instance().GetAircraftTrace(fplTraces);
	hmFplTraces::iterator AircraftTrace1=fplTraces.find(iTraceID1);
	hmFplTraces::iterator AircraftTrace2=fplTraces.find(iTraceID2);
    
	double currentDistance=0.0,newDistance=0.0;
	if(AircraftTrace1!=fplTraces.end()&&AircraftTrace2!=fplTraces.end()){

		double dCurx1=AircraftTrace1->second->m_fAbsX;
		double dCury1=AircraftTrace1->second->m_fAbsY;

		double dCurx2=AircraftTrace2->second->m_fAbsX;
		double dCury2=AircraftTrace2->second->m_fAbsY;

		currentDistance=CTools::DistancePoint2Point(WPointF(dCurx1,dCury1),WPointF(dCurx2,dCury2));

		hmFplTracePoint::iterator Iter1=m_hmTracePoint.find(iTraceID1);
		if(Iter1!=m_hmTracePoint.end()){
			std::deque<WPointF> deqTracePoint=Iter1->second;
			WPointF wNextPos=deqTracePoint.front();
			double dNextX=wNextPos.rx();
			double dNextY=wNextPos.ry();

			newDistance=CTools::DistancePoint2Point(WPointF(dNextX,dNextY),WPointF(dCurx2,dCury2));

			PublicDataStruct::Aircraft& aircraftInfo1=AircraftTrace1->second->m_aircraftInfo;
			PublicDataStruct::Aircraft& aircraftInfo2=AircraftTrace2->second->m_aircraftInfo;
			
           
			//距离缩小了,说明两个航空器在不断的缩进，Aircraft1在后，Aircraft2在前
			if(newDistance<currentDistance){
				if(currentDistance<aircraftInfo2.dSafeDistance){
					  aircraftInfo1.bStop=true;//冲突距离以内，后面的飞行器停等
					 // m_aircrftTraceToDispenserVec[iTraceID1]=-1;
					  m_aircraftStopVec.push_back(iTraceID1);
					  
				}
			}else{//距离变大了，这时Aircraft1在前，Aircraft2在后,保护层距离
				if(currentDistance<aircraftInfo1.dSafeDistance){
					aircraftInfo2.bStop=true;//冲突距离以内，后面的飞行器停等
					//m_aircrftTraceToDispenserVec[iTraceID2]=-1;
					m_aircraftStopVec.push_back(iTraceID2);

				}//if
			}//else
		}
	}
}
void NetDataDispenser::_DisPenserTraceToClient()
{
	if(!m_aircrftTraceToDispenserVec.empty()){

		std::vector<int>::iterator Iter=m_aircrftTraceToDispenserVec.begin();
		while(Iter++!=m_aircrftTraceToDispenserVec.end()){

			std::vector<int>::iterator isFind=std::find(m_aircraftStopVec.begin(),m_aircraftStopVec.end(),*Iter);
			if(isFind==m_aircraftStopVec.end())//需要停等
			    continue;
			std::deque<WPointF> TracePoint;
			theData::instance().GetAircraftTracePoint1(*Iter,TracePoint);
			WPointF postion=TracePoint.front();
			hmFplTraces::iterator traceIter=m_hmTrace.find(*Iter);
			if(traceIter!=m_hmTrace.end()){

				AircraftTrace* pTrace=traceIter->second;

				pTrace->m_fAbsX=postion.rx();
				pTrace->m_fAbsY=postion.ry();
				pTrace->m_nHistoryNum++;//历史轨迹点
				pTrace->m_vHistoryPos.push_back(boost::make_shared<WPointF>(postion.rx(), postion.ry()));
				theApp::instance().GetNetManagerPtr()->GetNetProcessPtr()->SendAircraftTrace(*pTrace);
				TracePoint.pop_front();//删除队头	
			}//if

		}//while
		
	}//if
	m_aircraftStopVec.clear();
}

