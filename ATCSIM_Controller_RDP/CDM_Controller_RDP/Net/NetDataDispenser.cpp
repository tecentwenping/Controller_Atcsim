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
	//�ַ������ص�ʱ�򣬻������ȶ�һ�����ݣ����Ƿ��к���
	if(InitData())
	{
		m_bInitDataSucess = true;//��ȡ��������
	}
}
NetDataDispenser::~NetDataDispenser()
{

}
void NetDataDispenser::DispenserTraceToClient()
{ 
	//������Ҷ������ݣ���ֱ�ӷ��أ��ȴ���һ�ε���
     if(! m_bInitDataSucess)
	 {
		 return;
	 }
	 //�Գ��溽��������ǣ����AircraftTrace.m_aircraftInfo.bStop���ԣ����������ڱ��浱ǰ�������˶�����ֹͣ
	 //���bStop����Ϊtrue���Ǳ���ɨ���������������������䷢��λ�����꣬���Ϊfalse������������˶�
	 _CollectionDetect();
	 _DisPenserTraceToClient();
}
bool NetDataDispenser::InitData()
{
	//������µĺ�����Ϣ
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
	//�¼���ĺ�����������0��Ҳ���´θ����к�����Ϣʱ������º�����ӵ�һ���㿪ʼ�ƶ�
	 boost::shared_mutex tmpMutex;
	 tmpMutex.lock();
	 m_mpTracePointCount.insert(std::make_pair(pTrace,0));
	 tmpMutex.unlock();
	//����һ�º�����ʹ�ź���������������ֵ�ǰ���µ�����
	 m_bInitDataSucess = InitData();
}

void NetDataDispenser::AircraftTraceToDispenser()
{  
	QTime currentTime;
	MapTowerAircraftPacket& mTowerAircraftPacket=theData::instance().GetMapTowerAircraftPacket();
	hmFplTraces::iterator traceIter = m_hmTrace.begin();
	while(traceIter!=m_hmTrace.end()){
		int traceID=traceIter->first;//���мƻ�ID
		MapTowerAircraftPacket::iterator Iter=mTowerAircraftPacket.find(traceID);
		//����Ĵ�����Ҫ������ɸѡ��Ҫ���ͺ�����traceID,����ʵ���ǣ�
		//��õ�ǰ��ʱ�䣬�ͷ��мƻ���ʱ����бȽϣ�����͵�ǰʱ��һ�£�
		//��ô�Ͱ���Ҫ���ͺ�����traceID�ŵ�һ�������У��ַ�������ȥ��ȡ
		//���������ID�����������µ���ʾ����
		if(Iter!= mTowerAircraftPacket.end()){
			PublicDataStruct::TowerFlightPlanStruct& towerFlightPlanStruct=(*Iter).second.TowerplanFlight;
			int planType=towerFlightPlanStruct.iFlyPlanType;
			std::string planTime="";
			if(0==planType){//��ۺ���
				  planTime=towerFlightPlanStruct.sDepartureTime;
				//strcpy(planTime.c_str(),towerFlightPlanStruct.sDepartureTime);
			}else{//���ۺ���
				planTime=towerFlightPlanStruct.sArrivalTime;
				//strcpy(planTime.c_str(),towerFlightPlanStruct.sArrivalTime);
			}
			currentTime=QTime::currentTime();
			int currentHour=currentTime.hour();//��ȡ��ǰСʱ
			int currentMin=currentTime.minute();//��ȡ��ǰ����
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
   AircraftTraceToDispenser();//��ȡ�ڳ��ķ�����

   if(m_aircrftTraceToDispenserVec.empty()){
	   return;
   }
   //ѭ�����溽������ȷ������������֮��Ĺ�ϵ��Ҳ��ǰ�������㣬�������
   //������֮���г�ͻ����Ҫ��ȡͣ�Ȳ���
   for(unsigned int i=0;i!=m_aircrftTraceToDispenserVec.size()-1;++i){
	   unsigned int j=1+1;
	   //����Ƕ�
	   int iAngle1=CompuAngle(m_aircrftTraceToDispenserVec[i]);
	   while(j++!=m_aircrftTraceToDispenserVec.size()){
		   int iAngle2=CompuAngle(m_aircrftTraceToDispenserVec[j]);
		   if(iAngle1-iAngle2>PI/2)
			   continue;
           //���������������ľ��룬ȷ���Ƿ����ڳ�ͻ��Χ�ڣ����������ڳ�����Ⱥ��ϵ��ȷ��ͣ�Ȳ���
		  _CollisionDectect_Aux(m_aircrftTraceToDispenserVec[i],m_aircrftTraceToDispenserVec[j]);
	   }
   }
}

int NetDataDispenser::CompuAngle( int iTraceID )
{
	//����Ƕȣ��ǶȲ�����PI/2�Ĳ���Ϊ�����������������һ��
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

			//Ԥ���߽Ƕȸ���
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
   //�ж������������Ƿ��ڳ�ͻ��Χ֮��
   //�̶�����һ���㣬�ҳ���һ�������һ�����꣬���������
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
			
           
			//������С��,˵�������������ڲ��ϵ�������Aircraft1�ں�Aircraft2��ǰ
			if(newDistance<currentDistance){
				if(currentDistance<aircraftInfo2.dSafeDistance){
					  aircraftInfo1.bStop=true;//��ͻ�������ڣ�����ķ�����ͣ��
					 // m_aircrftTraceToDispenserVec[iTraceID1]=-1;
					  m_aircraftStopVec.push_back(iTraceID1);
					  
				}
			}else{//�������ˣ���ʱAircraft1��ǰ��Aircraft2�ں�,���������
				if(currentDistance<aircraftInfo1.dSafeDistance){
					aircraftInfo2.bStop=true;//��ͻ�������ڣ�����ķ�����ͣ��
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
			if(isFind==m_aircraftStopVec.end())//��Ҫͣ��
			    continue;
			std::deque<WPointF> TracePoint;
			theData::instance().GetAircraftTracePoint1(*Iter,TracePoint);
			WPointF postion=TracePoint.front();
			hmFplTraces::iterator traceIter=m_hmTrace.find(*Iter);
			if(traceIter!=m_hmTrace.end()){

				AircraftTrace* pTrace=traceIter->second;

				pTrace->m_fAbsX=postion.rx();
				pTrace->m_fAbsY=postion.ry();
				pTrace->m_nHistoryNum++;//��ʷ�켣��
				pTrace->m_vHistoryPos.push_back(boost::make_shared<WPointF>(postion.rx(), postion.ry()));
				theApp::instance().GetNetManagerPtr()->GetNetProcessPtr()->SendAircraftTrace(*pTrace);
				TracePoint.pop_front();//ɾ����ͷ	
			}//if

		}//while
		
	}//if
	m_aircraftStopVec.clear();
}

