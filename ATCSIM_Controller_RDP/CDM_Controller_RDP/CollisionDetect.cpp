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

void CollisionDetect::_CollisonDetect()
{


	


}
