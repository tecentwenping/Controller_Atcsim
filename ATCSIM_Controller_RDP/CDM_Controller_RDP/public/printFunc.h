#ifndef PRINTFUNC_H
#define PRINTFUNC_H
#include "public/PublicStruct.h"
#include "PathPlaning/AircraftTrace.h"
#include <iostream>
#include <deque>
#include "wworldpoint.h"
void printTowerAicraftPacket(const PublicDataStruct::TowerAircraftPacketStruct& towerAircraft);
void printAircraftPoint(const AircraftTrace& aircraftTrace);
template<class T>
void printInformation(const T& information,void(*Func)(const T&))
{
	Func(information);
}
template<class T>
void PrintInfomation(const T& info){
	std::cout<<info<<std::endl;
}
template<class T>
void WriteToFile(const T& info){
    


}
void printTrace( int iFlightID,std::deque<WPointF>& Trace);
//{
//      
//	std::deque<WPointF>::iterator Iter=Trace.begin();
//	while(Iter++!=Trace.end()){
//
//		std::cout<<"iFlightID:"<<iFlightID<<":("<<(*Iter).rx()<<","<<(*Iter).ry()<<"),";
//
//	}
//	std::cout<<std::endl;
//
//
//}
#endif