#include "printFunc.h"
void printTowerAicraftPacket(const PublicDataStruct::TowerAircraftPacketStruct& towerAircraft)
{
	std::cout<<"--------------------------<TowerAircraftPacket>--------------------------"<<std::endl;
	std::cout<<"create a toweraircraftpacket successfully,the system will use this toweraircraft to generate aircrafttrace,the fllow information is:"<<std::endl;
	std::cout<<"---ID: "<<towerAircraft.TowerplanFlight.iFlightPlanId<<std::endl;
	std::cout<<"---FlightNum:"<<towerAircraft.TowerplanFlight.sFlightNum<<std::endl;
	std::cout<<"---SSRCode:"<<towerAircraft.TowerplanFlight.sSSRCode<<std::endl;
	std::cout<<"---"<<towerAircraft.TowerplanFlight.sDepDromeName<<"-->"<<towerAircraft.TowerplanFlight.sArrDromeName
		<<"  "<<towerAircraft.TowerplanFlight.sAlternateDrome<<"  "<<towerAircraft.TowerplanFlight.sDepartureTime
		<<"  "<<towerAircraft.TowerplanFlight.sArrivalTime<<std::endl;
}
void printAircraftPoint(const AircraftTrace& aircraftTrace)
{
	std::cout<<"--------------------------<AircraftTrace>--------------------------"<<std::endl;
	std::cout<<"Send a aircraftTrace to the display model,this trace indicate a aircraft's current absolutly position in the display,the fllow information is: "<<std::endl;
	std::cout<<"---TraceID: "<<aircraftTrace.m_nTraceID<<std::endl;
	std::cout<<"---SSRCode:"<<aircraftTrace.m_strSSR<<std::endl;
	std::cout<<"---CurrentPos(x,y):"<<aircraftTrace.m_fAbsX<<"  "<<aircraftTrace.m_fAbsY<<std::endl;
}

void printTrace( int iFlightID,std::deque<WPointF>& Trace )
{
		std::deque<WPointF>::iterator Iter=Trace.begin();
		while(Iter++!=Trace.end()){
	
			std::cout<<"iFlightID:"<<iFlightID<<":("<<(*Iter).rx()<<","<<(*Iter).ry()<<"),";
	
		}
		std::cout<<std::endl;
}


