#ifndef CDataManager_H
#define CDataManager_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CDataManager
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/29
  ����  ����:  ���ļ���������CDataManager���������е�����
  ����  ����:   
**************************************************************************/
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pool/detail/singleton.hpp>
#include <map>
#include <QString>
#include <QStringList>
#include <vector>
#include <hash_map>
#include "public/PublicStruct.h"
#include "Manager/TaxiLineInformation.h"
#include "wworldpoint.h"
#include <deque>
using boost::details::pool::singleton_default;
class CFile;
class CInitPointInformation;
class CPublicData;
class TowerAircraftPacketStruct;
class TotalAircraftTrace;
class AircraftTrace;
class AircraftTraceNewVersion;
class CGateInformation;
///////////////////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<CFile>									FilePtr;//�ļ�������
typedef boost::shared_ptr<CInitPointInformation>					InitPointInformationPtr;
typedef boost::shared_ptr<CPublicData>	        					PublicDataPtr;
typedef boost::shared_ptr<TotalAircraftTrace>						TotalAircraftTracePtr;
typedef boost::shared_ptr<CTaxiLineInformation>						TaxiLineInformationPtr;
/////////////////////////////////////////////////////////////////////////////////////////////
typedef std::map<int,std::vector<WPointF> >							MapAircraftTrace;
typedef stdext::hash_map<int,AircraftTrace*>						hmFplTraces;				
typedef std::vector<QStringList>									VecGateInformation;
typedef std::multimap<QString,QString>								MapGateName;
typedef std::multimap<int,PublicDataStruct::TaxiLine>				MapTaxiLine;
typedef std::multimap<std::string,PublicDataStruct::FixPoint>		MapFixPoint;
typedef std::map<int,PublicDataStruct::TowerAircraftPacketStruct>	MapTowerAircraftPacket;
typedef std::multimap<QString,QStringList>								MapPath;
////////////////////////////////////////////////////////////////////////////////////////////
typedef stdext::hash_map<int,std::deque<WPointF> >					hmFplTracePoint;
class CDataManager
{

public:
	CDataManager();
	~CDataManager();
	void	  Init();
public:
	void					GetCenterCoordinate(double& dCenterLongtitude,double& dLatitude);//���û����������꣨Ĭ��Ϊ˫��������
	void					GetMapGateName(MapGateName& mapGateName);//��ȡͣ��λ����
	void					GetMapTaxiLine(MapTaxiLine& mapTaxiLine);//��ȡ���е�
	void					GetMapFixPoint(MapFixPoint& mapFixPoint);//��ȡ�̶���
	//void					GetMapTowerAircraftPacket(MapTowerAircraftPacket& mapTowerAircraft);//��ȡ�ɻ���
	//MapTowerAircraftPacket& GetMapTowerAircraftPacket();
	void					GetMapAirTrace(MapAircraftTrace& mapAircraftTrace);
	void					GetAircraftTrace(hmFplTraces& hmFplTrace);
	//TotalAircraftTrace*     GetTotalAircraftTracePtr();
	void					GetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	void					GetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					GetPathInformation(MapPath& mapPath,int flag);
	void					GetCurrentFlyPlan(std::vector<QString>& vecCurFlyPlan);
	//////////////////////////////////////////////////////////////////////////////////
	void					SetMapAirTrace(const MapAircraftTrace& mapAircraftTrace);
	void					SetPathInformation(const MapPath& mapPath,int flag);
	void					SetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	void					SetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					SetAircraftTrace(int iTraceno,AircraftTrace* aicraftTrace);
	void					SetMapFixPoint(const MapFixPoint& mpFixPoint);
	void					SetMapTaxLine(const MapTaxiLine& mpTaxLine);
	void					SetMapGateName(const MapGateName& mpGateName);
	void					SetMapTowerAircraftPacket(const MapTowerAircraftPacket& mpTowerAircraft);
	void					SetCurrentFlyPlan(const QString& singleFlyPlan);
	//===================================================================================
	void					SetAircraftTracePoint1(int traceID,const std::deque<WPointF>& dTrace);
	void					GetAircraftTracePoint1(int traceID, std::deque<WPointF>& dTrace);
    void					GetGateInformation_New(VecGateInformation& vecGateInformation);
	void					SetGateInformation_New(const VecGateInformation& vecGateInformation);
	VecGateInformation&     GetGateInformation_New();
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	CInitPointInformation*      GetInitPointInformationPtr();
	CPublicData*				GetPublicDataPtr();
	TotalAircraftTrace*         GetTotalAircrafTracePtr();
	CTaxiLineInformation*		GetTaxLineInfomationPtr();
	CFile*						GetGateInformationPtr();
private:
//	FilePtr					m_pInitGateInformation;//ͣ��λ��Ϣ
//	FilePtr					m_pInitPathInformation;//·����Ϣ
////	InitPointInformationPtr m_pInitPointInformaton;//�����Ϣ
//	CPublicDataPtr			m_pPublicData;//��������
//	TotalAircraftTracePtr	m_pTotalTrace;
//	TotalAircraftTrace      *m_pTotalTracePtr;
//	TaxiLineInformationPtr  m_pTaxLineInformation;

/////////////////////////////////////////////////////////////////////
private:
	FilePtr					m_pGateInformation;
	InitPointInformationPtr m_pInitPointInformaton;
	PublicDataPtr		    m_pPublicData;
	TotalAircraftTracePtr	m_pTotalAircraftTrace;
	TaxiLineInformationPtr  m_pTaxiLineInformation;
public:
	TotalAircraftTracePtr	GetTotalAircraftTracePtr_New();
};
//�������ݹ���������
typedef singleton_default<CDataManager> theData;
#endif // CDataManager_H
