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

void NetDataDispenser::_SetSafeDistance( PublicDataStruct::Aircraft& aircraft )
{
	 /*
	 �澯��:L'=V*t+m*V*V/2(f1+f2+f3)
	 V:��ǰ�ٶ�
	 t:��Ӧʱ�䣬�趨Ϊ5s
	 m:����������
	 f1:ɲ������Ϊ������40%
	 f2:��������������40%
	 f3������������Ϊ������10%
	 ��С�ͷɻ����������Ϳ�������Ϊ0
	*/
	double dSpd=aircraft.dCurTaxSpd;
	double dTime=PublicDataStruct::RESPONSETIME;
	double dMass=aircraft.dMass;
	double F1=aircraft.dMass*0.4;
	double F2=0.0,F3=0.0;
	if(aircraft.sWake=="H"){
		F2=aircraft.dMass*0.4;
		F3=aircraft.dMass*0.1;
	}
	double dAlarmDistance=dSpd*dTime+(dMass*dSpd*dSpd)/(F1+F2+F3)*0.5;

	aircraft.dAlarmDistance=dAlarmDistance;
	aircraft.dBaseDistance=aircraft.dLength;
	aircraft.dSafeDistance=aircraft.dAlarmDistance+aircraft.dBaseDistance;

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
			double dCurX=Iter2->second->m_fAbsX;
			double dCurY=Iter2->second->m_fAbsY;

			WPointF wNextPos=deqTracePoint.front();
			double dNextX=wNextPos.rx();
			double dNextY=wNextPos.ry();

			double dTempx=dCurX-dNextX;
			double dTempy=dCurY-dNextY;

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
				
				std::string wake1=aircraftInfo1.sWake;
				std::string wake2=aircraftInfo2.sWake;
				int wakedistance=_CompuWakeDistance(wake1,wake2);
				aircraftInfo2.dProtectDistance=wakedistance;
				aircraftInfo2.dSafeDistance+=wakedistance;

				if(currentDistance<aircraftInfo2.dSafeDistance){
					  aircraftInfo1.bStop=true;//��ͻ�������ڣ�����ķ�����ͣ��
					  m_aircrftTraceToDispenserVec[iTraceID1]=-1;
					  
				}
			}else{//�������ˣ���ʱAircraft1��ǰ��Aircraft2�ں�,���������
				std::string wake1=aircraftInfo2.sWake;
				std::string wake2=aircraftInfo1.sWake;
				int wakedistance=_CompuWakeDistance(wake1,wake2);
				aircraftInfo1.dProtectDistance=wakedistance;
				aircraftInfo1.dSafeDistance+=wakedistance;

				if(currentDistance<aircraftInfo1.dSafeDistance){

					aircraftInfo2.bStop=true;//��ͻ�������ڣ�����ķ�����ͣ��
					m_aircrftTraceToDispenserVec[iTraceID2]=-1;

				}
					

			}
		}
	}
}

int NetDataDispenser::_CompuWakeDistance( std::string wake1,std::string wake2 )
{
	std::string str=wake1+wake2;
    int wakeDistance=0;
	if(str=="HH")  wakeDistance=PublicDataStruct::HH1;
	else if(str=="HM") wakeDistance=PublicDataStruct::HM1;
	else if(str=="HS") wakeDistance=PublicDataStruct::HS1;
	else if(str=="MH") wakeDistance=PublicDataStruct::MH1;
	else if(str=="MM")wakeDistance=PublicDataStruct::MM1;
	else if(str=="MS")wakeDistance=PublicDataStruct::MS1;
	else if(str=="SH")wakeDistance=PublicDataStruct::SH1;
	else if(str=="SM")wakeDistance=PublicDataStruct::SM1;
	else if(str=="SS")wakeDistance=PublicDataStruct::SS1;

	return wakeDistance;
}

void NetDataDispenser::_DisPenserTraceToClient()
{
	if(!m_aircrftTraceToDispenserVec.empty()){

		std::vector<int>::iterator Iter=m_aircrftTraceToDispenserVec.begin();

		
		while(Iter++!=m_aircrftTraceToDispenserVec.end()){
            
			if(-1==*Iter)//����Ҫ����λ�ø���
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
				//������ľ��������ų���״��ĸı����ģ����Է����꺽������Ҫ�������������ȥ��
				pTrace->m_aircraftInfo.dSafeDistance -=pTrace->m_aircraftInfo.dProtectDistance;
				TracePoint.pop_front();//ɾ����ͷ	
			}//if

		}//while
		
	}//if
	m_aircrftTraceToDispenserVec.clear();

}

