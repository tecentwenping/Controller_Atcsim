#include "test_packet.h"
#include <memory.h>


PKT_IMPLEMENT_DYNCREATE(CTestPacket);

void CTestPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,m_msg.c_str(),m_msg.length()+1);
	//memcpy(pTemp,&Message,sizeof(Message)+1);
}

void CTestPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	m_msg.assign(pTemp);
	//memcpy(&Message, pTemp, sizeof(Message)+1);
}

int CTestPacket::GetBufferSize()
{
	return m_msg.length()+1;
	//return sizeof(Message)+1;
}

PKT_IMPLEMENT_DYNCREATE(TracePacket);

PKT_IMPLEMENT_DYNCREATE(TimePacket);

PKT_IMPLEMENT_DYNCREATE(InitPacket);

void InitPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;

	memcpy(pTemp, &m_AircraftNum, sizeof(m_AircraftNum));
	pTemp += sizeof(m_AircraftNum);

	int num = m_vObjIDs.size();
	memcpy(pTemp, &num, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			ST_ObjID objID = m_vObjIDs.at(i);

			memcpy(pTemp, &objID.iObjID, sizeof(objID.iObjID));
			pTemp += sizeof(objID.iObjID);
			memcpy(pTemp, objID.strName.c_str(), objID.strName.size() + 1);
			pTemp += objID.strName.size() + 1;
		}
}

void InitPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;

	memcpy(&m_AircraftNum,pTemp,sizeof(m_AircraftNum));
	pTemp+=sizeof(m_AircraftNum);
	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			ST_ObjID objID;
			memcpy(&objID.iObjID, pTemp, sizeof(objID.iObjID));
			pTemp += sizeof(objID.iObjID);

			objID.strName.assign(pTemp);
			pTemp += objID.strName.size() + 1;

			m_vObjIDs.push_back(objID);
		}

}

int InitPacket::GetBufferSize()
{
	int size = 0;

	size += sizeof(m_AircraftNum);

	int num = m_vObjIDs.size();

	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			ST_ObjID objID;
			objID = m_vObjIDs.at(i);
			size += sizeof(objID.iObjID);
			size += objID.strName.size() + 1;
		}
		return size;
}

PKT_IMPLEMENT_DYNCREATE(TraceArrayPacket);

PKT_IMPLEMENT_DYNCREATE(ProAddPlanePacket);

void ProAddPlanePacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	/*memcpy(&m_FlyPlanNum,pTemp,sizeof(m_FlyPlanNum));
	pTemp+=sizeof(m_FlyPlanNum);*/
	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			 FlyPlanData flp;
			memcpy(&flp.m_iTrainPlanID, pTemp, sizeof(flp.m_iTrainPlanID));
			pTemp += sizeof(flp.m_iTrainPlanID);
			memcpy(&flp.m_iFlyPlanID, pTemp, sizeof(flp.m_iFlyPlanID));
			pTemp += sizeof(flp.m_iFlyPlanID);

			flp.m_szFlyPlanName.assign(pTemp);
            pTemp += flp.m_szFlyPlanName.size() + 1;
			flp.m_szSignName.assign(pTemp);
			pTemp += flp.m_szSignName.size() + 1;

			memcpy(&flp.m_dX,pTemp,sizeof(flp.m_dX));
			pTemp += sizeof(flp.m_dX);
			memcpy(&flp.m_dY,pTemp,sizeof(flp.m_dY));
			pTemp += sizeof(flp.m_dY);
			memcpy(&flp.m_dZ,pTemp,sizeof(flp.m_dZ));
			pTemp += sizeof(flp.m_dZ);

			memcpy(&flp.m_dHeading,pTemp,sizeof(flp.m_dHeading));
			pTemp += sizeof(flp.m_dHeading);
			memcpy(&flp.m_dSpeed,pTemp,sizeof(flp.m_dSpeed));
			pTemp += sizeof(flp.m_dSpeed);
			memcpy(&flp.m_iAircraftID,pTemp,sizeof(flp.m_iAircraftID));
			pTemp += sizeof(flp.m_iAircraftID);
            
			m_vFlyPlans.push_back(flp);
		}

}

void ProAddPlanePacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;

	/*memcpy(pTemp, &m_FlyPlanNum, sizeof(m_FlyPlanNum));
	pTemp += sizeof(m_FlyPlanNum);*/

	int num = m_vFlyPlans.size();
	memcpy(pTemp, &num, sizeof(num));
	pTemp += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			FlyPlanData flp = m_vFlyPlans.at(i);

			memcpy(pTemp, &flp.m_iTrainPlanID, sizeof(flp.m_iTrainPlanID));
			pTemp += sizeof(flp.m_iTrainPlanID);
			memcpy(pTemp, &flp.m_iFlyPlanID, sizeof(flp.m_iFlyPlanID));
			pTemp += sizeof(flp.m_iFlyPlanID);
			memcpy(pTemp,flp.m_szFlyPlanName.c_str(),flp.m_szFlyPlanName.size() + 1);
			pTemp += flp.m_szFlyPlanName.size() + 1;
			memcpy(pTemp,flp.m_szSignName.c_str(),flp.m_szSignName.size() + 1);
			pTemp += flp.m_szSignName.size() + 1;

			memcpy(pTemp, &flp.m_dX, sizeof(flp.m_dX));
			pTemp += sizeof(flp.m_dX);
			memcpy(pTemp, &flp.m_dY, sizeof(flp.m_dY));
			pTemp += sizeof(flp.m_dY);
			memcpy(pTemp, &flp.m_dZ, sizeof(flp.m_dZ));
			pTemp += sizeof(flp.m_dZ);

			memcpy(pTemp, &flp.m_dHeading, sizeof(flp.m_dHeading));
			pTemp += sizeof(flp.m_dHeading);
			memcpy(pTemp, &flp.m_dSpeed, sizeof(flp.m_dSpeed));
			pTemp += sizeof(flp.m_dSpeed);
			memcpy(pTemp, &flp.m_iAircraftID, sizeof(flp.m_iAircraftID));
			pTemp += sizeof(flp.m_iAircraftID);
		}
}

int ProAddPlanePacket::GetBufferSize()
{
	int size = 0;

	int num = m_vFlyPlans.size();

	size += sizeof(num);
	if(num>0&&num<MAX_VALUE_WS)
		for (int i=0; i<num; i++)
		{
			FlyPlanData flp;
			flp = m_vFlyPlans.at(i);
			size += sizeof(flp.m_iTrainPlanID);
			size += sizeof(flp.m_iFlyPlanID);
			size += flp.m_szFlyPlanName.size() + 1;
			size += flp.m_szSignName.size() + 1;

			size += sizeof(flp.m_dX);
            size += sizeof(flp.m_dY);
			size += sizeof(flp.m_dZ);
			size += sizeof(flp.m_dHeading);
			size += sizeof(flp.m_dSpeed);
			size += sizeof(flp.m_iAircraftID);
		}
		return size;
}
PKT_IMPLEMENT_DYNCREATE(TrainPlanPacket);

void TrainPlanPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&PlaneinAirNum,sizeof(PlaneinAirNum));
	pTemp+=sizeof(PlaneinAirNum);
	memcpy(pTemp,&PlaneonGroundNum,sizeof(PlaneonGroundNum));
	pTemp+=sizeof(PlaneonGroundNum);
	memcpy(pTemp,&Frequency,sizeof(Frequency));
	pTemp+=sizeof(Frequency);
}

void TrainPlanPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&PlaneinAirNum,pTemp,sizeof(PlaneinAirNum));
	pTemp += sizeof(PlaneinAirNum);
	memcpy(&PlaneonGroundNum,pTemp,sizeof(PlaneonGroundNum));
	pTemp += sizeof(PlaneonGroundNum);
	memcpy(&Frequency,pTemp,sizeof(Frequency));
	pTemp += sizeof(Frequency);
}

int TrainPlanPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(PlaneinAirNum);
	size += sizeof(PlaneonGroundNum);
	size += sizeof(Frequency);
		return size;
}

PKT_IMPLEMENT_DYNCREATE(CommandPacket);

void CommandPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
	pTemp += sizeof(cmd);
	memcpy(pTemp,&id,sizeof(id));
}

void CommandPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
	pTemp += sizeof(cmd);
	memcpy(&id, pTemp, sizeof(id));
}

int CommandPacket::GetBufferSize()
{
	int size = 0;
	size += sizeof(cmd);
	size += sizeof(id);
	return size;
}

PKT_IMPLEMENT_DYNCREATE(SysCommandPacket);

void SysCommandPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&cmd,sizeof(cmd));
}

void SysCommandPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&cmd, pTemp, sizeof(cmd));
}

int SysCommandPacket::GetBufferSize()
{
	return sizeof(cmd);
}

PKT_IMPLEMENT_DYNCREATE(SysStatusPacket);

void SysStatusPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,&GroupID,sizeof(GroupID));
	pTemp+=sizeof(GroupID);
	memcpy(pTemp,&Status,sizeof(Status));
	pTemp+=sizeof(Status);
	memcpy(pTemp,&OpCache,sizeof(OpCache));
}

void SysStatusPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	memcpy(&GroupID,pTemp,sizeof(GroupID));
	pTemp+=sizeof(GroupID);
	memcpy(&Status, pTemp, sizeof(Status));
	pTemp+=sizeof(Status);
	memcpy(&OpCache,pTemp,sizeof(OpCache));
}

int SysStatusPacket::GetBufferSize()
{
	return sizeof(Status)+sizeof(GroupID)+sizeof(OpCache);
}

// PKT_IMPLEMENT_DYNCREATE(ExServerIPPacket);
// 
// void ExServerIPPacket::WriteToBuffer(char* pBuffer)
// {
// 	char* pTemp = pBuffer ;
// 	memcpy(pTemp,ip.c_str(),ip.length()+1);
// 	pTemp +=ip.length()+1;
// 	memcpy(pTemp,&port,sizeof(port));
// 	pTemp += sizeof(port);
// }

// void ExServerIPPacket::ReadFromBuffer(const char* pBuffer)
// {
// 	const char* pTemp = pBuffer;
// 	ip.assign(pTemp);
// 	pTemp +=ip.length()+1;
// 	memcpy(&port,pTemp,sizeof(port));
// 	pTemp += sizeof(port);
// }
// 
// int ExServerIPPacket::GetBufferSize()
// {
// 	return ip.length()+1+sizeof(port);
// }

//PKT_IMPLEMENT_DYNCREATE(DataServiceIPPacket);

// void DataServiceIPPacket::WriteToBuffer(char* pBuffer)
// {
// 	char* pTemp = pBuffer ;
// 	memcpy(pTemp,ip.c_str(),ip.length()+1);
// 	pTemp +=ip.length()+1;
// 	memcpy(pTemp,&port,sizeof(port));
// 	pTemp += sizeof(port);
// }

// void DataServiceIPPacket::ReadFromBuffer(const char* pBuffer)
// {
// 	const char* pTemp = pBuffer;
// 	ip.assign(pTemp);
// 	pTemp +=ip.length()+1;
// 	memcpy(&port,pTemp,sizeof(port));
// 	pTemp += sizeof(port);
// }

// int DataServiceIPPacket::GetBufferSize()
// {
// 	return ip.length()+1+sizeof(port);
// }

//PKT_IMPLEMENT_DYNCREATE(GroupDisConnectPacket);

// void GroupDisConnectPacket::WriteToBuffer(char* pBuffer)
// {
// 	char* pTemp = pBuffer ;
// }

// void GroupDisConnectPacket::ReadFromBuffer(const char* pBuffer)
// {
// 	const char* pTemp = pBuffer;
// }

// int GroupDisConnectPacket::GetBufferSize()
// {
// 	return 0;
// }

PKT_IMPLEMENT_DYNCREATE(MemcacheServiceIPPacket);

void MemcacheServiceIPPacket::WriteToBuffer(char* pBuffer)
{
	char* pTemp = pBuffer ;
	memcpy(pTemp,ip.c_str(),ip.length()+1);
	pTemp +=ip.length()+1;
	memcpy(pTemp,&port,sizeof(port));
	pTemp += sizeof(port);
}

void MemcacheServiceIPPacket::ReadFromBuffer(const char* pBuffer)
{
	const char* pTemp = pBuffer;
	ip.assign(pTemp);
	pTemp +=ip.length()+1;
	memcpy(&port,pTemp,sizeof(port));
	pTemp += sizeof(port);
}

int MemcacheServiceIPPacket::GetBufferSize()
{
	return ip.length()+1+sizeof(port);
}

PKT_IMPLEMENT_DYNCREATE(MovingObjPacket);
PKT_IMPLEMENT_DYNCREATE(MoveSpelEffectCreatePacket);
PKT_IMPLEMENT_DYNCREATE(MoveSpelEffectCreateAckPacket);
PKT_IMPLEMENT_DYNCREATE(MoveSpelEffectDeletePacket);
PKT_IMPLEMENT_DYNCREATE(MoveSpelEffectOperatorPacket);
PKT_IMPLEMENT_DYNCREATE(ReqTmpObjPacket);

void ReqTmpObjPacket::ReadFromBuffer(const char* pBuffer)
{

}

void ReqTmpObjPacket::WriteToBuffer(char* pBuffer)
{

}

int ReqTmpObjPacket::GetBufferSize()
{
   return 0;
}

PKT_IMPLEMENT_DYNCREATE(DynamicCreateFlightPlanPacket);
PKT_IMPLEMENT_DYNCREATE(DynamicCreateFlightObjPacket);
PKT_IMPLEMENT_DYNCREATE(DynamicCreateAircraftPacket);
PKT_IMPLEMENT_DYNCREATE(DynamicCreateAircraftAckPacket);
PKT_IMPLEMENT_DYNCREATE(QueryDynamicCreateAircraftPacket);

void QueryDynamicCreateAircraftPacket::ReadFromBuffer(const char* pBuffer)
{

}

void QueryDynamicCreateAircraftPacket::WriteToBuffer(char* pBuffer)
{

}

int QueryDynamicCreateAircraftPacket::GetBufferSize()
{
	return 0;
}

PKT_IMPLEMENT_DYNCREATE(ParkingBayInfoACKPacket);
PKT_IMPLEMENT_DYNCREATE(AssignParkingBayPacket);
PKT_IMPLEMENT_DYNCREATE(ReqTmpParkingBayPacket);
PKT_IMPLEMENT_DYNCREATE(AssignParkingBayACKPacket);

void ReqTmpParkingBayPacket::ReadFromBuffer(const char* pBuffer)
{

}

void ReqTmpParkingBayPacket::WriteToBuffer(char* pBuffer)
{

}

int ReqTmpParkingBayPacket::GetBufferSize()
{
	return 0;
}