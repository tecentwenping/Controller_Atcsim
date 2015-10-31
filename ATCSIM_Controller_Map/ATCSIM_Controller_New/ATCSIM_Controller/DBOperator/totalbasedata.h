#ifndef TOTALBASEDATA_H
#define TOTALBASEDATA_H
#include <vector>
#include "airport_data_objs.h"
#include "airspace_data_objs.h"
class TotalBaseData 
{
public:
	TotalBaseData();
	~TotalBaseData();
public:
	void ClearBaseData();
	void SetBaseData(const AirportData& airportData);
	void SetBaseData(const std::vector<RunwayData>& vRunwayData);
	void SetBaseData(const std::vector<RoadData>& vRoadData);
	void SetBaseData(const std::vector<FixpointData>& vFixpointData);
	void SetBaseData(const std::vector<GateData>& vGateData);
	void SetBaseData(const std::vector<Tower>& vTowerData);
	void SetBaseData(const std::vector<AirportModel>& vAirportmodelData);
	void SetBaseData(const std::vector<AirportData>& vAirportData);
	void SetBaseData(const std::vector<Star>& vStarData);
	//�����
	void SetBaseData(const std::vector<Beacon>& vBeaconData);
	void SetBaseData(const std::vector<Sector>& vSectorData);
	void SetBaseData(const std::vector<RestrictArea>& vRestricAreaData);
	void SetBaseData(const std::vector<Course>& vCourseData);
	void SetBaseData(const std::vector<MsawArea>& vMsawAreaData);

	std::vector<AirportData>&		GetAirportDataVec();
    AirportData&					GetAirportData();
	std::vector<RunwayData> &		GetRunwayDataVec();
	std::vector<RoadData>&			GetRoadDataVec();
	std::vector<FixpointData>&		GetFixpointDataVec();
	bool							GetFixpointDataVec(int nID, FixpointData& fixpointdata);
	std::vector<GateData>&			GetGateDataVec();
	std::vector<Tower>&				GetTowerDataVec();
	std::vector<AirportModel>&		GetAirportDataModelVec();
	std::vector<Star>&				GetStarDataVec();
	std::vector<Beacon>&			GetBeaconVec();
	void							GetBeaconVec(int nID, Beacon &beacon);
	std::vector<Sector>&			GetSectorVec();
	std::vector<RestrictArea>&		GetRestrictAreaVec();
	std::vector<Course>&			GetCourseVec();
	std::vector<MsawArea>&			GetMsawAreaVec();
	void							GetCylinderVec(int nID, std::vector<Cylinder>& vCylinder);
	void							GetPointsData(int nID, std::vector<GlyphPt>& vGlyphPt);
	void							GetCylinderGlyphData(int nID, std::vector<CylinderGlyph> &vCylinderGlyph);
	int								GetGlyphPtIDFromSequence(int sequence, std::vector<CylinderGlyph> &vCylinderGlyph);
	void							GetGlyphPtData(int nID, GlyphPt &glyphPt);


	bool FindFixpointData(int nID, FixpointData& fixpointdata);
	bool FindRoadData(int nID, RoadData& roaddata);
 
private:
	AirportData					m_airportdata;
	std::vector<RunwayData>     m_vcRunWayData;      //�ܵ�
	std::vector<RoadData>       m_vcRoadData;        //���е�
	std::vector<FixpointData>   m_vcFixpointData;    //�̶���
	std::vector<GateData>       m_vcGateData;        //ͣ��λ
	std::vector<AirportData>    m_vAirportData;
	std::vector<Star>           m_vStar;
	std::vector<Tower>          m_vTower;
	std::vector<AirportModel>   m_vAirportModel;
	std::vector<Beacon>			m_vBeaconData;
	std::vector<Sector>			m_vSectorData;
	std::vector<RestrictArea>	m_vRestricAreaData;
	std::vector<Course>			m_vCourseData;
	std::vector<MsawArea>		m_vMsawAreaData;
	std::vector<Cylinder>		m_vecCylinder;//������Ϣ
	std::vector<CylinderGlyph>  m_vecCylinderGlyph;//�����������Ĺ�ϵ
	std::vector<GlyphPt>		m_vecGlyphPt;

};
#endif // TOTALBASEDATA_H
