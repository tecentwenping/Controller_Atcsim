#ifndef GETDATAFROMDB_H
#define GETDATAFROMDB_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: GetDataFromDB
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/11/12
  ����  ����:  ������Ҫ�����Ǵ����ݿ��ж�ȡ�ļ�����ת���ļ���TotalBaseData
  ����  ����:   
**************************************************************************/

#include <vector>
#include <map>
#include <QSqlQuery>
#include "airport_dbaccess.h"
#include "./boost/shared_ptr.hpp"
class TotalBaseData;
class AckAirportDataPacket;
class AckAirspaceDataPacket;
//������
class AirportData;
class RunwayData;
class RoadData;
class RoadFixpointData;
class FixpointData;
class GateData;
class Tower;
class AirportModel;
class Star;
//�����
class Beacon;
class Sector;
class RestrictArea;
class Course;
class MsawArea;
class RoutePt;
class PointPosition;

class GetDataFromDB
{


public:
	GetDataFromDB();
	~GetDataFromDB();
	/*********************************************************
	*��������QueryDataFromDB
	*�������ܣ��ṩ���ⲿ�ĺ������������˽�к���������ѯ���ݿ��
	���Ľ�����д洢������е��洢�������TotalBaseData��Ķ���m_pDatabase��
	��ѯ����Ѿ��̶������ǳ��ڰ汾
	*������
	**********************************************************/
	 void QueryDataFromDB();
	 /*********************************************************
	 *��������GetTotalBaseData
	 *�������ܣ���ȡ�����ݿ��ѯ������
	 *������
	 **********************************************************/
	 TotalBaseData * GetTotalBaseData();
protected:
	/*********************************************************
	*��������OnBaseDataPacket
	*�������ܣ�ת����Ϣ�ĺ���
	*������const AckAirportDataPacket* rParama�������ݰ�
	**********************************************************/
	void OnBaseDataPacket(const AckAirportDataPacket* rParama);
	/*********************************************************
	*��������OnBaseDataPacket
	*�������ܣ�ת����Ϣ�ĺ���
	*������const AckAirportDataPacket* rParama�������ݰ�
	**********************************************************/
	void OnBaseDataPacket(const AckAirspaceDataPacket* rParama);
protected:
	/*********************************************************
	*��������SetBaseData
	*�������ܣ�����е�ת�����ݰ��ĺ������ṩ�˲�ͬ�İ汾
	*������const AirportData& airportData��������
	**********************************************************/
	void SetBaseData(const AirportData& airportData);
	void SetBaseData(const std::vector<RunwayData>& vRunwayData);
	void SetBaseData(const std::vector<RoadData>& vRoadData);
	void SetBaseData(const std::vector<FixpointData>& vFixpointData);
	void SetBaseData(const std::vector<GateData>& vGateData);
	void SetBaseData(const std::vector<Tower>& vTowerData);
	void SetBaseData(const std::vector<AirportModel>& vAirportmodelData);
	void SetBaseData(const std::vector<AirportData>& vAirportData);
	void SetBaseData(const std::vector<Star>& vStarData);
	void SetBaseData(const std::vector<Beacon>& vBeaconData);
	void SetBaseData(const std::vector<Sector>& vGateData);
	void SetBaseData(const std::vector<RestrictArea>& vTowerData);
	void SetBaseData(const std::vector<Course>& vAirportmodelData);
	void SetBaseData(const std::vector<MsawArea>& vAirportData);
protected:
	/*********************************************************
	*��������GetSomething()
	*�������ܣ������ݿ�������
	*������
	**********************************************************/
	void GetAirportData();//�����ݿ��ѯ��������
	void GetRunWayData();//�����ݿ��ѯ�ܵ�����
	void GetRoadData();//��·����
	void GetFixpointData();//�̶�������
	void GetGateData();//ͣ��λ��Ϣ
	void GetTowerData();//��̨��Ϣ
	void GetAirportModelData();//����ģ������
	void GetStarData();//�볡����
	void GetBeaconData();//
	void GetSectorData();//��������
	void GetRestricAreaData();//
	void GetCourseData();
	void GetMsawAreaData();//

protected:
	/*********************************************************
	*��������GetAirPortDataFromDB
	*�������ܣ���ȡ��������
	*������
	**********************************************************/
	void GetAirPortDataFromDB();
	/*********************************************************
	*��������GetAirPortDataFromDB
	*�������ܣ���ȡ��������
	*������
	**********************************************************/
	void GetAirSpaceDataFromDB();

	
private:
	AirPort_DBAccess *m_pDBAccessObj;/*���ݿ���ʶ���*/
	TotalBaseData    * m_pDataBase;/*�洢�����ݿ��ȡ�����ݣ��԰�����ʽ�洢*/
	AckAirportDataPacket  *m_AckAirportDataPacket;
	AckAirspaceDataPacket *m_AckAirspaceDataPacket;//�����洢���ݽṹ
	std::multimap<int,boost::shared_ptr<RoadFixpointData> > m_mFixpointOnRoadData;//��ŵ�·����ʱ���ӳ���
	std::multimap<int,boost::shared_ptr<RoutePt> > m_mRoutePtData;//���Route��ӳ���
	std::multimap<int,boost::shared_ptr<PointPosition> > m_mPointPosition;//��ŵ�λ�õ�ӳ���
};
#endif // GETDATAFROMDB_H
