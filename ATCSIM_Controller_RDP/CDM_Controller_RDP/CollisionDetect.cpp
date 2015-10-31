#include "CollisionDetect.h"

CollisionDetect::CollisionDetect()

{

}

CollisionDetect::~CollisionDetect()
{

}

void CollisionDetect::_SetSafeDistance( PublicDataStruct::Aircraft& aircraft )
{
    /*
	 告警层:L'=V*t+m*V*V/2(f1+f2+f3)
	 V:当前速度
	 t:反应时间，设定为5s
	 m:航空器质量
	 f1:刹车力，为质量的40%
	 f2:反推力，质量的40%
	 f3：空气阻力，为质量的10%
	 中小型飞机，反推力和空气阻力为0
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

void CollisionDetect::_CollisonDetect()
{


	


}
