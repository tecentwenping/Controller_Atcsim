#include "DataLayerPacket.h"
#include <memory.h>
#define MAX_VALUE_WS 600000000 //定义最大极限值

PKT_IMPLEMENT_DYNCREATE(TrainPlanDataPacket);

void TrainPlanDataPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_iTrainPlanID,sizeof(m_iTrainPlanID));
	pTemp+=sizeof(m_iTrainPlanID);
	memcpy(pTemp,m_szTrainPlanName.c_str(),m_szTrainPlanName.size()+1);
	//pTemp+=m_szTrainPlanName.size()+1;

	/*int num = m_vFlyPlanData.size();
	memcpy(pTemp,&num,sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan = m_vFlyPlanData.at(i);
			memcpy(pTemp,&flyplan.m_iTrainPlanID,sizeof(flyplan.m_iTrainPlanID));
			pTemp += sizeof(flyplan.m_iTrainPlanID);
			memcpy(pTemp,&flyplan.m_iFlyPlanID,sizeof(flyplan.m_iFlyPlanID));
			pTemp += sizeof(flyplan.m_iFlyPlanID);
			memcpy(pTemp,flyplan.m_szFlyPlanName.c_str(),flyplan.m_szFlyPlanName.size()+1);
			pTemp += flyplan.m_szFlyPlanName.size()+1;
			memcpy(pTemp,flyplan.m_szSignName.c_str(),flyplan.m_szSignName.size()+1);
			pTemp += flyplan.m_szSignName.size()+1;
			memcpy(pTemp,&flyplan.m_dX,sizeof(flyplan.m_dX));
			pTemp += sizeof(flyplan.m_dX);
			memcpy(pTemp,&flyplan.m_dY,sizeof(flyplan.m_dY));
			pTemp += sizeof(flyplan.m_dY);
			memcpy(pTemp,&flyplan.m_dZ,sizeof(flyplan.m_dZ));
			pTemp += sizeof(flyplan.m_dZ);
			memcpy(pTemp,&flyplan.m_dHeading,sizeof(flyplan.m_dHeading));
			pTemp += sizeof(flyplan.m_dHeading);
			memcpy(pTemp,&flyplan.m_dSpeed,sizeof(flyplan.m_dSpeed));
			pTemp += sizeof(flyplan.m_dSpeed);
			memcpy(pTemp,&flyplan.m_iAircraftID,sizeof(flyplan.m_iAircraftID));
			pTemp += sizeof(flyplan.m_iAircraftID);
		}
	}*/
}

void TrainPlanDataPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iTrainPlanID,pTemp,sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);
	m_szTrainPlanName.assign(pTemp);
	//pTemp += m_szTrainPlanName.size()+1;

	/*int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan ;
			memcpy(&flyplan.m_iTrainPlanID,pTemp,sizeof(flyplan.m_iTrainPlanID));
			pTemp += sizeof(flyplan.m_iTrainPlanID);
			memcpy(&flyplan.m_iFlyPlanID,pTemp,sizeof(flyplan.m_iFlyPlanID));
			pTemp += sizeof(flyplan.m_iFlyPlanID);
			flyplan.m_szFlyPlanName.assign(pTemp);
			pTemp += flyplan.m_szFlyPlanName.size()+1;
			flyplan.m_szSignName.assign(pTemp);
			pTemp += flyplan.m_szSignName.size()+1;
			memcpy(&flyplan.m_dX,pTemp,sizeof(flyplan.m_dX));
			pTemp += sizeof(flyplan.m_dX);
			memcpy(&flyplan.m_dY,pTemp,sizeof(flyplan.m_dY));
			pTemp += sizeof(flyplan.m_dY);
			memcpy(&flyplan.m_dZ,pTemp,sizeof(flyplan.m_dZ));
			pTemp += sizeof(flyplan.m_dZ);
			memcpy(&flyplan.m_dHeading,pTemp,sizeof(flyplan.m_dHeading));
			pTemp += sizeof(flyplan.m_dHeading);
			memcpy(&flyplan.m_dSpeed,pTemp,sizeof(flyplan.m_dSpeed));
			pTemp += sizeof(flyplan.m_dSpeed);
			memcpy(&flyplan.m_iAircraftID,pTemp,sizeof(flyplan.m_iAircraftID));
			pTemp += sizeof(flyplan.m_iAircraftID);

			m_vFlyPlanData.push_back(flyplan);
		}
	}*/
}

int TrainPlanDataPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(m_iTrainPlanID);
	size += m_szTrainPlanName.size()+1;	
	/*int num = m_vFlyPlanData.size();
	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan = m_vFlyPlanData.at(i);
			size += sizeof(flyplan.m_iTrainPlanID);
			size += sizeof(flyplan.m_iFlyPlanID);
			size += flyplan.m_szFlyPlanName.size()+1;
			size += flyplan.m_szSignName.size()+1;
			size += sizeof(flyplan.m_dX);
			size += sizeof(flyplan.m_dY);
			size += sizeof(flyplan.m_dZ);
			size += sizeof(flyplan.m_dHeading);
			size += sizeof(flyplan.m_dSpeed);
			size += sizeof(flyplan.m_iAircraftID);
		}
	}*/
	return size;
}
PKT_IMPLEMENT_DYNCREATE(FlyPlanDataPacket);
void FlyPlanDataPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&m_iTrainPlanID,sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);
	memcpy(pTemp,&m_iFlyPlanID,sizeof(m_iFlyPlanID));
	pTemp += sizeof(m_iFlyPlanID);
	memcpy(pTemp,m_szFlyPlanName.c_str(),m_szFlyPlanName.size()+1);
	pTemp += m_szFlyPlanName.size()+1;
	memcpy(pTemp,m_szSignName.c_str(),m_szSignName.size()+1);
	pTemp += m_szSignName.size()+1;
	memcpy(pTemp,&m_dX,sizeof(m_dX));
	pTemp += sizeof(m_dX);
	memcpy(pTemp,&m_dY,sizeof(m_dY));
	pTemp += sizeof(m_dY);
	memcpy(pTemp,&m_dZ,sizeof(m_dZ));
	pTemp += sizeof(m_dZ);
	memcpy(pTemp,&m_dHeading,sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);
	memcpy(pTemp,&m_dSpeed,sizeof(m_dSpeed));
	pTemp += sizeof(m_dSpeed);
	memcpy(pTemp,&m_iAircraftID,sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);
}
void FlyPlanDataPacket::ReadFromBuffer(const char* pBuffer)
{
    const char* pTemp = pBuffer;
	memcpy(&m_iTrainPlanID,pTemp,sizeof(m_iTrainPlanID));
	pTemp += sizeof(m_iTrainPlanID);
	memcpy(&m_iFlyPlanID,pTemp,sizeof(m_iFlyPlanID));
	pTemp += sizeof(m_iFlyPlanID);
	m_szFlyPlanName.assign(pTemp);
	pTemp += m_szFlyPlanName.size()+1;
	m_szSignName.assign(pTemp);
	pTemp += m_szSignName.size()+1;
	memcpy(&m_dX,pTemp,sizeof(m_dX));
	pTemp += sizeof(m_dX);
	memcpy(&m_dY,pTemp,sizeof(m_dY));
	pTemp += sizeof(m_dY);
	memcpy(&m_dZ,pTemp,sizeof(m_dZ));
	pTemp += sizeof(m_dZ);
	memcpy(&m_dHeading,pTemp,sizeof(m_dHeading));
	pTemp += sizeof(m_dHeading);
	memcpy(&m_dSpeed,pTemp,sizeof(m_dSpeed));
	pTemp += sizeof(m_dSpeed);
	memcpy(&m_iAircraftID,pTemp,sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);
}
int FlyPlanDataPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(m_iTrainPlanID);
	size += sizeof(m_iFlyPlanID);
	size += m_szFlyPlanName.size()+1;
	size += m_szSignName.size()+1;
    size += sizeof(m_dX);
	size += sizeof(m_dY);
	size += sizeof(m_dZ);
	size += sizeof(m_dHeading);
	size += sizeof(m_dSpeed);
	size += sizeof(m_iAircraftID);
	return size;
}

PKT_IMPLEMENT_DYNCREATE(ALLFlyPlanDataPacket);
void ALLFlyPlanDataPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	int num = m_vFlyPlanData.size();
	memcpy(pTemp,&num,sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan = m_vFlyPlanData.at(i);
			memcpy(pTemp,&flyplan.m_iTrainPlanID,sizeof(flyplan.m_iTrainPlanID));
			pTemp += sizeof(flyplan.m_iTrainPlanID);
			memcpy(pTemp,&flyplan.m_iFlyPlanID,sizeof(flyplan.m_iFlyPlanID));
			pTemp += sizeof(flyplan.m_iFlyPlanID);
			memcpy(pTemp,flyplan.m_szFlyPlanName.c_str(),flyplan.m_szFlyPlanName.size()+1);
			pTemp += flyplan.m_szFlyPlanName.size()+1;
			memcpy(pTemp,flyplan.m_szSignName.c_str(),flyplan.m_szSignName.size()+1);
			pTemp += flyplan.m_szSignName.size()+1;
			memcpy(pTemp,&flyplan.m_dX,sizeof(flyplan.m_dX));
			pTemp += sizeof(flyplan.m_dX);
			memcpy(pTemp,&flyplan.m_dY,sizeof(flyplan.m_dY));
			pTemp += sizeof(flyplan.m_dY);
			memcpy(pTemp,&flyplan.m_dZ,sizeof(flyplan.m_dZ));
			pTemp += sizeof(flyplan.m_dZ);
			memcpy(pTemp,&flyplan.m_dHeading,sizeof(flyplan.m_dHeading));
			pTemp += sizeof(flyplan.m_dHeading);
			memcpy(pTemp,&flyplan.m_dSpeed,sizeof(flyplan.m_dSpeed));
			pTemp += sizeof(flyplan.m_dSpeed);
			memcpy(pTemp,&flyplan.m_iAircraftID,sizeof(flyplan.m_iAircraftID));
			pTemp += sizeof(flyplan.m_iAircraftID);
		}
	}
}
void ALLFlyPlanDataPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan ;
			memcpy(&flyplan.m_iTrainPlanID,pTemp,sizeof(flyplan.m_iTrainPlanID));
			pTemp += sizeof(flyplan.m_iTrainPlanID);
			memcpy(&flyplan.m_iFlyPlanID,pTemp,sizeof(flyplan.m_iFlyPlanID));
			pTemp += sizeof(flyplan.m_iFlyPlanID);
			flyplan.m_szFlyPlanName.assign(pTemp);
			pTemp += flyplan.m_szFlyPlanName.size()+1;
			flyplan.m_szSignName.assign(pTemp);
			pTemp += flyplan.m_szSignName.size()+1;
			memcpy(&flyplan.m_dX,pTemp,sizeof(flyplan.m_dX));
			pTemp += sizeof(flyplan.m_dX);
			memcpy(&flyplan.m_dY,pTemp,sizeof(flyplan.m_dY));
			pTemp += sizeof(flyplan.m_dY);
			memcpy(&flyplan.m_dZ,pTemp,sizeof(flyplan.m_dZ));
			pTemp += sizeof(flyplan.m_dZ);
			memcpy(&flyplan.m_dHeading,pTemp,sizeof(flyplan.m_dHeading));
			pTemp += sizeof(flyplan.m_dHeading);
			memcpy(&flyplan.m_dSpeed,pTemp,sizeof(flyplan.m_dSpeed));
			pTemp += sizeof(flyplan.m_dSpeed);
			memcpy(&flyplan.m_iAircraftID,pTemp,sizeof(flyplan.m_iAircraftID));
			pTemp += sizeof(flyplan.m_iAircraftID);

			m_vFlyPlanData.push_back(flyplan);
		}
	}
}
int ALLFlyPlanDataPacket::GetBufferSize()
{
	int size = 0;
	int num = m_vFlyPlanData.size();
	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			FlyPlanData flyplan = m_vFlyPlanData.at(i);
			size += sizeof(flyplan.m_iTrainPlanID);
			size += sizeof(flyplan.m_iFlyPlanID);
			size += flyplan.m_szFlyPlanName.size()+1;
			size += flyplan.m_szSignName.size()+1;
			size += sizeof(flyplan.m_dX);
			size += sizeof(flyplan.m_dY);
			size += sizeof(flyplan.m_dZ);
			size += sizeof(flyplan.m_dHeading);
			size += sizeof(flyplan.m_dSpeed);
			size += sizeof(flyplan.m_iAircraftID);
		}
	}
	return size;
}

PKT_IMPLEMENT_DYNCREATE(AircraftDataPacket);
void AircraftDataPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&m_iAircraftID,sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);
	memcpy(pTemp,m_szAircraftName.c_str(),m_szAircraftName.size()+1);
	pTemp += m_szAircraftName.size()+1;
	memcpy(pTemp,&m_dIAS,sizeof(m_dIAS));
	pTemp += sizeof(m_dIAS);
	memcpy(pTemp,&m_dAcceleration,sizeof(m_dAcceleration));
	pTemp += sizeof(m_dAcceleration);
	memcpy(pTemp,&m_dDeceleration,sizeof(m_dDeceleration));
	pTemp += sizeof(m_dDeceleration);


}
void AircraftDataPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_iAircraftID,pTemp,sizeof(m_iAircraftID));
	pTemp += sizeof(m_iAircraftID);
	m_szAircraftName.assign(pTemp);
	pTemp += m_szAircraftName.size()+1;
	memcpy(&m_dIAS,pTemp,sizeof(m_dIAS));
	pTemp += sizeof(m_dIAS);
	memcpy(&m_dAcceleration,pTemp,sizeof(m_dAcceleration));
	pTemp += sizeof(m_dAcceleration);
	memcpy(&m_dDeceleration,pTemp,sizeof(m_dDeceleration));
	pTemp += sizeof(m_dDeceleration);

}
int AircraftDataPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(m_iAircraftID);
	size += m_szAircraftName.size()+1;
	size += sizeof(m_dIAS);
	size += sizeof(m_dAcceleration);
	size += sizeof(m_dDeceleration);
	return size;
}