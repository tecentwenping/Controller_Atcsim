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
///////////////////////////////////////////////////////////////////////////////////////////
typedef boost::shared_ptr<CFile>									FilePtr;//�ļ�������
typedef boost::shared_ptr<CInitPointInformation>					InitPointInformationPtr;
typedef boost::shared_ptr<CPublicData>	        					CPublicDataPtr;
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
	//void					GetGateInformation_T1(VecGateInformation& vecGateInformation);//��ȡT1��վ¥ͣ��λ��Ϣ
	//void					GetGateInformation_T2(VecGateInformation& vecGateInformation);//��ȡT2��վ¥ͣ��λ��Ϣ
	//VecGateInformation&		GetGateInformation_T1();
	//VecGateInformation&     GetGateInformation_T2();
	void					GetMapGateName(MapGateName& mapGateName);//��ȡͣ��λ����
	void					GetMapTaxiLine(MapTaxiLine& mapTaxiLine);//��ȡ���е�
	void					GetMapFixPoint(MapFixPoint& mapFixPoint);//��ȡ�̶���
	void					GetMapTowerAircraftPacket(MapTowerAircraftPacket& mapTowerAircraft);//��ȡ�ɻ���
	MapTowerAircraftPacket& GetMapTowerAircraftPacket();
	void					GetMapAirTrace(MapAircraftTrace& mapAircraftTrace);
	//void					GetTracePoint(int iTraceno,std::vector<WPointF>& vecTracePoint);
	void					GetAircraftTrace(hmFplTraces& hmFplTrace);
	TotalAircraftTrace*     GetTotalAircraftTracePtr();
	void					GetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	void					GetPathPoint(int iFlyID,QStringList& vecPathPoint);
	void					GetPathInformation(MapPath& mapPath,int flag);
	void					GetCurrentFlyPlan(std::vector<QString>& vecCurFlyPlan);
	//////////////////////////////////////////////////////////////////////////////////
	void					SetMapAirTrace(const MapAircraftTrace& mapAircraftTrace);
	//void					SetTracePoint(int iTraceno,const std::vector<WPointF>& vecTracePoint);
	void					SetPathInformation(const MapPath& mapPath,int flag);
	void					SetFlyPlan(std::vector<PublicDataStruct::SFlyPlanFromDB>& vecFlyPlan);
	//void					SetGateInformation(const VecGateInformation& vecGateInformation,int flag);
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
private:
	FilePtr					m_pInitGateInformation;//ͣ��λ��Ϣ
	FilePtr					m_pInitPathInformation;//·����Ϣ
	InitPointInformationPtr m_pInitPointInformaton;//�����Ϣ
	CPublicDataPtr			m_pPublicData;//��������
	TotalAircraftTracePtr	m_pTotalTrace;
	TotalAircraftTrace      *m_pTotalTracePtr;
	TaxiLineInformationPtr  m_pTaxLineInformation;
public:
	TotalAircraftTracePtr	GetTotalAircraftTracePtr_New();
};
//�������ݹ���������
typedef singleton_default<CDataManager> theData;
#endif // CDataManager_H
