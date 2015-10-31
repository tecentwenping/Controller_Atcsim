#ifndef PRINTFUNC_H
#define PRINTFUNC_H
#include "public/PublicStruct.h"
#include "PathPlaning/AircraftTrace.h"
#include <iostream>
void printTowerAicraftPacket(const PublicDataStruct::TowerAircraftPacketStruct& towerAircraft);
void printAircraftTrace(const AircraftTrace& aircraftTrace);
template<class T>
void printInformation(const T& information,void(*Func)(const T&))
{
	Func(information);
}
#endif