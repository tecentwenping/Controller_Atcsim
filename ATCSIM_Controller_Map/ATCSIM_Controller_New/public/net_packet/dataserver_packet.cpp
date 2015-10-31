#include "dataserver_packet.h"
#include <memory.h>
#define MAX_VALUE_WS 600000000 //定义最大极限值


/*------------------------发包------------------------ */
//发包：初始化包
PKT_IMPLEMENT_DYNCREATE(InitializePacket);
void InitializePacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_site_info.site_type,sizeof(int));
	pTemp += sizeof(int);
	memcpy(pTemp, &m_site_info.site_id, sizeof(int));
	pTemp += sizeof(unsigned);
	memcpy(pTemp, &m_site_info.topic_pub, sizeof(unsigned));
	pTemp += sizeof(unsigned);
	memcpy(pTemp, &m_site_info.topic_sub, sizeof(unsigned));
	pTemp += sizeof(unsigned);
}

void InitializePacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_site_info.site_type, pTemp, sizeof(int));
	pTemp += sizeof(int);
	memcpy(&m_site_info.site_id, pTemp, sizeof(int));
	pTemp += sizeof(unsigned);
	memcpy(&m_site_info.topic_pub, pTemp, sizeof(unsigned));
	pTemp += sizeof(unsigned);
	memcpy(&m_site_info.topic_sub, pTemp, sizeof(unsigned));
	pTemp += sizeof(unsigned);
}

int InitializePacket::GetBufferSize()
{
	return sizeof(int) + sizeof(int) + sizeof(unsigned) + sizeof(unsigned);
}

//发包：获得单条/全部记录的包，根据名字
PKT_IMPLEMENT_DYNCREATE(KeyDataPacket);
void KeyDataPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&m_DataKey,sizeof(DataKey));
	pTemp += sizeof(DataKey);
}

void KeyDataPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_DataKey,pTemp,sizeof(DataKey));
	pTemp += sizeof(DataKey);
}

int KeyDataPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(DataKey);	

	return size;
}

//发包：获得单条/全部记录的包，根据ID
PKT_IMPLEMENT_DYNCREATE(KeyDataIDPacket);
void KeyDataIDPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&m_DataKeyID,sizeof(DataKeyID));
	pTemp += sizeof(DataKeyID);
}

void KeyDataIDPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_DataKeyID,pTemp,sizeof(DataKeyID));
	pTemp += sizeof(DataKeyID);
}

int KeyDataIDPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(DataKeyID);	

	return size;
}

////发包：机型信息编辑包
//PKT_IMPLEMENT_DYNCREATE(AircraftDataEditPacket);
//void AircraftDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer;
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(pTemp,&m_AircraftData.m_iAircraftID,sizeof(m_AircraftData.m_iAircraftID));
//	pTemp += sizeof(m_AircraftData.m_iAircraftID);
//	memcpy(pTemp,m_AircraftData.m_szAircraftName.c_str(),m_AircraftData.m_szAircraftName.size()+1);
//	pTemp += m_AircraftData.m_szAircraftName.size()+1;
//	memcpy(pTemp,&m_AircraftData.m_dIAS,sizeof(m_AircraftData.m_dIAS));
//	pTemp += sizeof(m_AircraftData.m_dIAS);
//	memcpy(pTemp,&m_AircraftData.m_dAcceleration,sizeof(m_AircraftData.m_dAcceleration));
//	pTemp += sizeof(m_AircraftData.m_dAcceleration);
//	memcpy(pTemp,&m_AircraftData.m_dDeceleration,sizeof(m_AircraftData.m_dDeceleration));
//	pTemp += sizeof(m_AircraftData.m_dDeceleration);
//}
//
//void AircraftDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(&m_AircraftData.m_iAircraftID,pTemp,sizeof(m_AircraftData.m_iAircraftID));
//	pTemp += sizeof(m_AircraftData.m_iAircraftID);
//	m_AircraftData.m_szAircraftName.assign(pTemp);
//	pTemp += m_AircraftData.m_szAircraftName.size()+1;
//	memcpy(&m_AircraftData.m_dIAS,pTemp,sizeof(m_AircraftData.m_dIAS));
//	pTemp += sizeof(m_AircraftData.m_dIAS);
//	memcpy(&m_AircraftData.m_dAcceleration,pTemp,sizeof(m_AircraftData.m_dAcceleration));
//	pTemp += sizeof(m_AircraftData.m_dAcceleration);
//	memcpy(&m_AircraftData.m_dDeceleration,pTemp,sizeof(m_AircraftData.m_dDeceleration));
//	pTemp += sizeof(m_AircraftData.m_dDeceleration);
//}
//
//int AircraftDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += sizeof(m_AircraftData.m_iAircraftID);
//	size += m_AircraftData.m_szAircraftName.size()+1;
//	size += sizeof(m_AircraftData.m_dIAS);
//	size += sizeof(m_AircraftData.m_dAcceleration);
//	size += sizeof(m_AircraftData.m_dDeceleration);
//	return size;	
//}
//

////发包：训练计划信息编辑包
//PKT_IMPLEMENT_DYNCREATE(TrainPlanDataEditPacket);
//void TrainPlanDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer ;
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(pTemp,&m_TrainPlanData.m_iTrainPlanID,sizeof(m_TrainPlanData.m_iTrainPlanID));
//	pTemp+=sizeof(m_TrainPlanData.m_iTrainPlanID);
//	memcpy(pTemp,m_TrainPlanData.m_szTrainPlanName.c_str(),m_TrainPlanData.m_szTrainPlanName.size()+1);
//	pTemp+=m_TrainPlanData.m_szTrainPlanName.size()+1;
//}
//
//void TrainPlanDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(&m_TrainPlanData.m_iTrainPlanID,pTemp,sizeof(m_TrainPlanData.m_iTrainPlanID));
//	pTemp += sizeof(m_TrainPlanData.m_iTrainPlanID);
//	m_TrainPlanData.m_szTrainPlanName.assign(pTemp);
//	pTemp += m_TrainPlanData.m_szTrainPlanName.size()+1;
//}
//
//int TrainPlanDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += sizeof(m_TrainPlanData.m_iTrainPlanID);
//	size += m_TrainPlanData.m_szTrainPlanName.size()+1;
//
//	return size;	
//}
//
////发包：飞机计划信息编辑包
//PKT_IMPLEMENT_DYNCREATE(FlyPlanDataEditPacket);
//void FlyPlanDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer;
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(pTemp,&m_FlyPlanData.m_iTrainPlanID,sizeof(m_FlyPlanData.m_iTrainPlanID));
//	pTemp += sizeof(m_FlyPlanData.m_iTrainPlanID);
//	memcpy(pTemp,&m_FlyPlanData.m_iFlyPlanID,sizeof(m_FlyPlanData.m_iFlyPlanID));
//	pTemp += sizeof(m_FlyPlanData.m_iFlyPlanID);
//	memcpy(pTemp,m_FlyPlanData.m_szFlyPlanName.c_str(),m_FlyPlanData.m_szFlyPlanName.size()+1);
//	pTemp += m_FlyPlanData.m_szFlyPlanName.size()+1;
//	memcpy(pTemp,m_FlyPlanData.m_szSignName.c_str(),m_FlyPlanData.m_szSignName.size()+1);
//	pTemp += m_FlyPlanData.m_szSignName.size()+1;
//	memcpy(pTemp,&m_FlyPlanData.m_dX,sizeof(m_FlyPlanData.m_dX));
//	pTemp += sizeof(m_FlyPlanData.m_dX);
//	memcpy(pTemp,&m_FlyPlanData.m_dY,sizeof(m_FlyPlanData.m_dY));
//	pTemp += sizeof(m_FlyPlanData.m_dY);
//	memcpy(pTemp,&m_FlyPlanData.m_dZ,sizeof(m_FlyPlanData.m_dZ));
//	pTemp += sizeof(m_FlyPlanData.m_dZ);
//	memcpy(pTemp,&m_FlyPlanData.m_dHeading,sizeof(m_FlyPlanData.m_dHeading));
//	pTemp += sizeof(m_FlyPlanData.m_dHeading);
//	memcpy(pTemp,&m_FlyPlanData.m_dSpeed,sizeof(m_FlyPlanData.m_dSpeed));
//	pTemp += sizeof(m_FlyPlanData.m_dSpeed);
//	memcpy(pTemp,&m_FlyPlanData.m_iAircraftID,sizeof(m_FlyPlanData.m_iAircraftID));
//	pTemp += sizeof(m_FlyPlanData.m_iAircraftID);
//}
//
//void FlyPlanDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(&m_FlyPlanData.m_iTrainPlanID,pTemp,sizeof(m_FlyPlanData.m_iTrainPlanID));
//	pTemp += sizeof(m_FlyPlanData.m_iTrainPlanID);
//	memcpy(&m_FlyPlanData.m_iFlyPlanID,pTemp,sizeof(m_FlyPlanData.m_iFlyPlanID));
//	pTemp += sizeof(m_FlyPlanData.m_iFlyPlanID);
//	m_FlyPlanData.m_szFlyPlanName.assign(pTemp);
//	pTemp += m_FlyPlanData.m_szFlyPlanName.size()+1;
//	m_FlyPlanData.m_szSignName.assign(pTemp);
//	pTemp += m_FlyPlanData.m_szSignName.size()+1;
//	memcpy(&m_FlyPlanData.m_dX,pTemp,sizeof(m_FlyPlanData.m_dX));
//	pTemp += sizeof(m_FlyPlanData.m_dX);
//	memcpy(&m_FlyPlanData.m_dY,pTemp,sizeof(m_FlyPlanData.m_dY));
//	pTemp += sizeof(m_FlyPlanData.m_dY);
//	memcpy(&m_FlyPlanData.m_dZ,pTemp,sizeof(m_FlyPlanData.m_dZ));
//	pTemp += sizeof(m_FlyPlanData.m_dZ);
//	memcpy(&m_FlyPlanData.m_dHeading,pTemp,sizeof(m_FlyPlanData.m_dHeading));
//	pTemp += sizeof(m_FlyPlanData.m_dHeading);
//	memcpy(&m_FlyPlanData.m_dSpeed,pTemp,sizeof(m_FlyPlanData.m_dSpeed));
//	pTemp += sizeof(m_FlyPlanData.m_dSpeed);
//	memcpy(&m_FlyPlanData.m_iAircraftID,pTemp,sizeof(m_FlyPlanData.m_iAircraftID));
//	pTemp += sizeof(m_FlyPlanData.m_iAircraftID);
//}
//
//int FlyPlanDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += sizeof(m_FlyPlanData.m_iTrainPlanID);
//	size += sizeof(m_FlyPlanData.m_iFlyPlanID);
//	size += m_FlyPlanData.m_szFlyPlanName.size()+1;
//	size += m_FlyPlanData.m_szSignName.size()+1;
//	size += sizeof(m_FlyPlanData.m_dX);
//	size += sizeof(m_FlyPlanData.m_dY);
//	size += sizeof(m_FlyPlanData.m_dZ);
//	size += sizeof(m_FlyPlanData.m_dHeading);
//	size += sizeof(m_FlyPlanData.m_dSpeed);
//	size += sizeof(m_FlyPlanData.m_iAircraftID);
//	return size;	
//}


/*-----------------------回复包----------------------*/

//回复包：数据库席位初始化化回复包
PKT_IMPLEMENT_DYNCREATE(AckInitializePacket_Exer);
void AckInitializePacket_Exer::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	int num_trainplan = m_vecAllTrainPlanName.size();
	memcpy(pTemp,&num_trainplan,sizeof(num_trainplan));
	pTemp += sizeof(num_trainplan);
	if(num_trainplan>0&&num_trainplan<MAX_VALUE_WS)
	{
		for (int i=0; i<num_trainplan; i++)
		{
			std::string name = m_vecAllTrainPlanName.at(i);
			memcpy(pTemp,name.c_str(),name.size()+1);
			pTemp += name.size()+1;
		}
	}

	int num_aircraft = m_vecAllAircraftName.size();
	memcpy(pTemp,&num_aircraft,sizeof(num_aircraft));
	pTemp += sizeof(num_aircraft);
	if(num_aircraft>0&&num_aircraft<MAX_VALUE_WS)
	{
		for (int i=0; i<num_aircraft; i++)
		{
			std::string name = m_vecAllAircraftName.at(i);
			memcpy(pTemp,name.c_str(),name.size()+1);
			pTemp += name.size()+1;
		}
	}
}

void AckInitializePacket_Exer::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	int num_trainplan;
	memcpy(&num_trainplan, pTemp, sizeof(num_trainplan));
	pTemp += sizeof(num_trainplan);
	if(num_trainplan>0&&num_trainplan<MAX_VALUE_WS)
	{
		for (int i=0; i<num_trainplan; i++)
		{
			std::string name ;
			name.assign(pTemp);
			pTemp += name.size()+1;
			m_vecAllTrainPlanName.push_back(name);
		}
	}

	int num_aircraft;
	memcpy(&num_aircraft, pTemp, sizeof(num_aircraft));
	pTemp += sizeof(num_aircraft);
	if(num_aircraft>0&&num_aircraft<MAX_VALUE_WS)
	{
		for (int i=0; i<num_aircraft; i++)
		{
			std::string name ;
			name.assign(pTemp);
			pTemp += name.size()+1;
			m_vecAllAircraftName.push_back(name);
		}
	}
}

int AckInitializePacket_Exer::GetBufferSize()
{
	int size = 0;
	int num_trainplan = m_vecAllTrainPlanName.size();
	size += sizeof(num_trainplan);
	if(num_trainplan>0&&num_trainplan<MAX_VALUE_WS)
	{
		for (int i=0; i<num_trainplan; i++)
		{
			std::string name = m_vecAllTrainPlanName.at(i);
			size += name.size() + 1;
		}
	}

	int num_aircraft = m_vecAllAircraftName.size();
	size += sizeof(num_aircraft);
	if(num_aircraft>0&&num_aircraft<MAX_VALUE_WS)
	{
		for (int i=0; i<num_aircraft; i++)
		{
			std::string name = m_vecAllAircraftName.at(i);
			size += name.size() + 1;
		}
	}
	return size;
}



//回复包：单条机型信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_SingleAircraft);
void AckKeyDataPacket_SingleAircraft::WriteToBuffer(char* pBuffer)
{
	int iOffSize = 0;
	m_AircraftData.WriteToBuffer(pBuffer,iOffSize);
}

void AckKeyDataPacket_SingleAircraft::ReadFromBuffer(const char* pBuffer)
{
	int iOffSize = 0;
	m_AircraftData.ReadFromBuffer(pBuffer, iOffSize);
}

int AckKeyDataPacket_SingleAircraft::GetBufferSize()
{
	return (m_AircraftData.GetBufferSize());	
}

//回复包：全部机型信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_AllAircraft);
void AckKeyDataPacket_AllAircraft::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	int num = m_vAircraftData.size();
	memcpy(pTemp,&num,sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			AircraftData aircraft = m_vAircraftData.at(i);
			memcpy(pTemp,&aircraft.m_iAircraftID,sizeof(aircraft.m_iAircraftID));
			pTemp += sizeof(aircraft.m_iAircraftID);
			memcpy(pTemp,aircraft.m_szAircraftName.c_str(),aircraft.m_szAircraftName.size()+1);
			pTemp += aircraft.m_szAircraftName.size()+1;
			memcpy(pTemp,&aircraft.m_dIAS,sizeof(aircraft.m_dIAS));
			pTemp += sizeof(aircraft.m_dIAS);
			memcpy(pTemp,&aircraft.m_dAcceleration,sizeof(aircraft.m_dAcceleration));
			pTemp += sizeof(aircraft.m_dAcceleration);
			memcpy(pTemp,&aircraft.m_dDeceleration,sizeof(aircraft.m_dDeceleration));
			pTemp += sizeof(aircraft.m_dDeceleration);
		}
	}
}

void AckKeyDataPacket_AllAircraft::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			AircraftData aircraft;
			memcpy(&aircraft.m_iAircraftID,pTemp,sizeof(aircraft.m_iAircraftID));
			pTemp += sizeof(aircraft.m_iAircraftID);
			aircraft.m_szAircraftName.assign(pTemp);
			pTemp += aircraft.m_szAircraftName.size()+1;
			memcpy(&aircraft.m_dIAS,pTemp,sizeof(aircraft.m_dIAS));
			pTemp += sizeof(aircraft.m_dIAS);
			memcpy(&aircraft.m_dAcceleration,pTemp,sizeof(aircraft.m_dAcceleration));
			pTemp += sizeof(aircraft.m_dAcceleration);
			memcpy(&aircraft.m_dDeceleration,pTemp,sizeof(aircraft.m_dDeceleration));
			pTemp += sizeof(aircraft.m_dDeceleration);

			m_vAircraftData.push_back(aircraft);
		}
	}
}

int AckKeyDataPacket_AllAircraft::GetBufferSize()
{
	int size = 0;
	int num = m_vAircraftData.size();
	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			AircraftData aircraft = m_vAircraftData.at(i);
			size += sizeof(aircraft.m_iAircraftID);
			size += aircraft.m_szAircraftName.size()+1;
			size += sizeof(aircraft.m_dIAS);
			size += sizeof(aircraft.m_dAcceleration);
			size += sizeof(aircraft.m_dDeceleration);
		}
	}
	return size;	
}


//回复包：单条训练计划信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_SingleTrainPlan);
void AckKeyDataPacket_SingleTrainPlan::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&m_TrainPlanData.m_iTrainPlanID,sizeof(m_TrainPlanData.m_iTrainPlanID));
	pTemp+=sizeof(m_TrainPlanData.m_iTrainPlanID);
	memcpy(pTemp,m_TrainPlanData.m_szTrainPlanName.c_str(),m_TrainPlanData.m_szTrainPlanName.size()+1);
	pTemp+=m_TrainPlanData.m_szTrainPlanName.size()+1;
}

void AckKeyDataPacket_SingleTrainPlan::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_TrainPlanData.m_iTrainPlanID,pTemp,sizeof(m_TrainPlanData.m_iTrainPlanID));
	pTemp += sizeof(m_TrainPlanData.m_iTrainPlanID);
	m_TrainPlanData.m_szTrainPlanName.assign(pTemp);
	pTemp += m_TrainPlanData.m_szTrainPlanName.size()+1;
}

int AckKeyDataPacket_SingleTrainPlan::GetBufferSize()
{
	int size = 0;
	size += sizeof(m_TrainPlanData.m_iTrainPlanID);
	size += m_TrainPlanData.m_szTrainPlanName.size()+1;

	return size;	
}

//回复包：全部训练计划信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_AllTrainPlan);
void AckKeyDataPacket_AllTrainPlan::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	int num = m_vTrainPlanData.size();
	memcpy(pTemp,&num,sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			TrainPlanData TrainPlanData = m_vTrainPlanData.at(i);
			memcpy(pTemp,&TrainPlanData.m_iTrainPlanID,sizeof(TrainPlanData.m_iTrainPlanID));
			pTemp+=sizeof(TrainPlanData.m_iTrainPlanID);
			memcpy(pTemp,TrainPlanData.m_szTrainPlanName.c_str(),TrainPlanData.m_szTrainPlanName.size()+1);
			pTemp+=TrainPlanData.m_szTrainPlanName.size()+1;
		}
	}
}

void AckKeyDataPacket_AllTrainPlan::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			TrainPlanData TrainPlanData;
			memcpy(&TrainPlanData.m_iTrainPlanID,pTemp,sizeof(TrainPlanData.m_iTrainPlanID));
			pTemp += sizeof(TrainPlanData.m_iTrainPlanID);
			TrainPlanData.m_szTrainPlanName.assign(pTemp);
			pTemp += TrainPlanData.m_szTrainPlanName.size()+1;
	
			m_vTrainPlanData.push_back(TrainPlanData);
		}
	}
}

int AckKeyDataPacket_AllTrainPlan::GetBufferSize()
{
	int size = 0;
	int num = m_vTrainPlanData.size();
	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
	{
		for (int i=0; i<num; i++)
		{
			TrainPlanData TrainPlanData = m_vTrainPlanData.at(i);
			size += sizeof(TrainPlanData.m_iTrainPlanID);
			size += TrainPlanData.m_szTrainPlanName.size()+1;
		}
	}
	return size;	
}

//回复包：单条飞行计划信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_SingleFlyPlan);
void AckKeyDataPacket_SingleFlyPlan::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer;
	memcpy(pTemp,&m_FlyPlanData.m_iTrainPlanID,sizeof(m_FlyPlanData.m_iTrainPlanID));
	pTemp += sizeof(m_FlyPlanData.m_iTrainPlanID);
	memcpy(pTemp,&m_FlyPlanData.m_iFlyPlanID,sizeof(m_FlyPlanData.m_iFlyPlanID));
	pTemp += sizeof(m_FlyPlanData.m_iFlyPlanID);
	memcpy(pTemp,m_FlyPlanData.m_szFlyPlanName.c_str(),m_FlyPlanData.m_szFlyPlanName.size()+1);
	pTemp += m_FlyPlanData.m_szFlyPlanName.size()+1;
	memcpy(pTemp,m_FlyPlanData.m_szSignName.c_str(),m_FlyPlanData.m_szSignName.size()+1);
	pTemp += m_FlyPlanData.m_szSignName.size()+1;
	memcpy(pTemp,&m_FlyPlanData.m_dX,sizeof(m_FlyPlanData.m_dX));
	pTemp += sizeof(m_FlyPlanData.m_dX);
	memcpy(pTemp,&m_FlyPlanData.m_dY,sizeof(m_FlyPlanData.m_dY));
	pTemp += sizeof(m_FlyPlanData.m_dY);
	memcpy(pTemp,&m_FlyPlanData.m_dZ,sizeof(m_FlyPlanData.m_dZ));
	pTemp += sizeof(m_FlyPlanData.m_dZ);
	memcpy(pTemp,&m_FlyPlanData.m_dHeading,sizeof(m_FlyPlanData.m_dHeading));
	pTemp += sizeof(m_FlyPlanData.m_dHeading);
	memcpy(pTemp,&m_FlyPlanData.m_dSpeed,sizeof(m_FlyPlanData.m_dSpeed));
	pTemp += sizeof(m_FlyPlanData.m_dSpeed);
	memcpy(pTemp,&m_FlyPlanData.m_iAircraftID,sizeof(m_FlyPlanData.m_iAircraftID));
	pTemp += sizeof(m_FlyPlanData.m_iAircraftID);
}

void AckKeyDataPacket_SingleFlyPlan::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&m_FlyPlanData.m_iTrainPlanID,pTemp,sizeof(m_FlyPlanData.m_iTrainPlanID));
	pTemp += sizeof(m_FlyPlanData.m_iTrainPlanID);
	memcpy(&m_FlyPlanData.m_iFlyPlanID,pTemp,sizeof(m_FlyPlanData.m_iFlyPlanID));
	pTemp += sizeof(m_FlyPlanData.m_iFlyPlanID);
	m_FlyPlanData.m_szFlyPlanName.assign(pTemp);
	pTemp += m_FlyPlanData.m_szFlyPlanName.size()+1;
	m_FlyPlanData.m_szSignName.assign(pTemp);
	pTemp += m_FlyPlanData.m_szSignName.size()+1;
	memcpy(&m_FlyPlanData.m_dX,pTemp,sizeof(m_FlyPlanData.m_dX));
	pTemp += sizeof(m_FlyPlanData.m_dX);
	memcpy(&m_FlyPlanData.m_dY,pTemp,sizeof(m_FlyPlanData.m_dY));
	pTemp += sizeof(m_FlyPlanData.m_dY);
	memcpy(&m_FlyPlanData.m_dZ,pTemp,sizeof(m_FlyPlanData.m_dZ));
	pTemp += sizeof(m_FlyPlanData.m_dZ);
	memcpy(&m_FlyPlanData.m_dHeading,pTemp,sizeof(m_FlyPlanData.m_dHeading));
	pTemp += sizeof(m_FlyPlanData.m_dHeading);
	memcpy(&m_FlyPlanData.m_dSpeed,pTemp,sizeof(m_FlyPlanData.m_dSpeed));
	pTemp += sizeof(m_FlyPlanData.m_dSpeed);
	memcpy(&m_FlyPlanData.m_iAircraftID,pTemp,sizeof(m_FlyPlanData.m_iAircraftID));
	pTemp += sizeof(m_FlyPlanData.m_iAircraftID);
}

int AckKeyDataPacket_SingleFlyPlan::GetBufferSize()
{
	int size = 0;
	size += sizeof(m_FlyPlanData.m_iTrainPlanID);
	size += sizeof(m_FlyPlanData.m_iFlyPlanID);
	size += m_FlyPlanData.m_szFlyPlanName.size()+1;
	size += m_FlyPlanData.m_szSignName.size()+1;
	size += sizeof(m_FlyPlanData.m_dX);
	size += sizeof(m_FlyPlanData.m_dY);
	size += sizeof(m_FlyPlanData.m_dZ);
	size += sizeof(m_FlyPlanData.m_dHeading);
	size += sizeof(m_FlyPlanData.m_dSpeed);
	size += sizeof(m_FlyPlanData.m_iAircraftID);
	return size;	
}

//回复包：全部飞行计划信息
PKT_IMPLEMENT_DYNCREATE(AckKeyDataPacket_AllFlyPlan);
void AckKeyDataPacket_AllFlyPlan::WriteToBuffer(char* pBuffer)
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

void AckKeyDataPacket_AllFlyPlan::ReadFromBuffer(const char* pBuffer)
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

int AckKeyDataPacket_AllFlyPlan::GetBufferSize()
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

////回复包：回复编辑包
//PKT_IMPLEMENT_DYNCREATE(AckDataEditPacket);
//void AckDataEditPacket::WriteToBuffer(char* pBuffer)
//{
//	char* pTemp = pBuffer ;
//	memcpy(pTemp,&m_edit_type,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(pTemp,&m_bSuccessed,sizeof(m_bSuccessed));
//	pTemp+=sizeof(m_bSuccessed);
//	
//}
//
//void AckDataEditPacket::ReadFromBuffer(const char* pBuffer)
//{
//	const char* pTemp = pBuffer;
//	memcpy(&m_edit_type,pTemp,sizeof(m_edit_type));
//	pTemp += sizeof(m_edit_type);
//	memcpy(&m_bSuccessed,pTemp,sizeof(m_bSuccessed));
//	pTemp += sizeof(m_bSuccessed);
//
//}
//
//int AckDataEditPacket::GetBufferSize()
//{
//	int size = 0;
//	size += sizeof(m_edit_type);
//	size += sizeof(m_bSuccessed);
//
//	return size;	
//}
