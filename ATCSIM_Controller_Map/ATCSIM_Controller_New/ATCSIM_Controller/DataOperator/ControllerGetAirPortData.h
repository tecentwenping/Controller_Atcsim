#ifndef CONTROLLERGETAIRPORTDATA_H
#define CONTROLLERGETAIRPORTDATA_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class TotalBaseData;
class GetDataFromDB;
typedef boost::shared_ptr<TotalBaseData> TotalBaseDataPtr;
typedef boost::shared_ptr<GetDataFromDB> GetDataFromDBPtr;
class ControllerGetAirPortData : public QObject
{
	Q_OBJECT

public:
	ControllerGetAirPortData();
	~ControllerGetAirPortData();
public:
	TotalBaseData*  GetAirPortData();
	void            QueryAirPortData();

private:
	TotalBaseDataPtr	m_pDataBase;
	GetDataFromDB*	m_pGetDataFromDB;
	
};

#endif // CONTROLLERGETAIRPORTDATA_H
