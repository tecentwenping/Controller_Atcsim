#include "ControllerGetAirPortData.h"
#include "getdatafromdb.h"
#include "totalbasedata.h"
ControllerGetAirPortData::ControllerGetAirPortData()
{
	/*if(! m_pGetDataFromDB)
	{
		m_pGetDataFromDB = boost::make_shared<GetDataFromDB>();
		QueryAirPortData();
	}
	*/
	m_pGetDataFromDB = new GetDataFromDB;
	QueryAirPortData();
}

ControllerGetAirPortData::~ControllerGetAirPortData()
{

}

void ControllerGetAirPortData::QueryAirPortData()
{
   m_pGetDataFromDB->QueryDataFromDB();
}

TotalBaseData* ControllerGetAirPortData::GetAirPortData()
{
   return m_pGetDataFromDB->GetTotalBaseData();
}
