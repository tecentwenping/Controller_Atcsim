#ifndef CGLYPHCREATOR_H
#define CGLYPHCREATOR_H
#include <boost/shared_ptr.hpp>
#include "./boost/shared_ptr.hpp"
#include "wworldpoint.h"

#include <hash_map>
class CSimMap;
class Coordinate;
class WAircraftGlyph;
class AircraftTrace;
class WColor;
class CGlyphManager;
class TotalBaseData;
class GetDataFromDB;
class WLabelFields;
class AircraftInfo;
class CGlyphCreator
{ 
	typedef stdext::hash_map<int,AircraftTrace*> hmFplTraces;
	typedef boost::shared_ptr<WPoint> PointPtr;
	typedef boost::shared_ptr<Coordinate> CoordinatePtr;
	typedef boost::shared_ptr<CGlyphManager> GlyphManagerPtr;
	typedef boost::shared_ptr<CSimMap> SimMapPtr;
public:
	CGlyphCreator();
	CGlyphCreator(GlyphManagerPtr pGlyphManager,CoordinatePtr pCoordinate,SimMapPtr pSimMap);
	virtual ~CGlyphCreator();
public:
	void InitMapGlyph();
	void InitAirspaceGlyph();
	void UpdateMouseCoordinate(double x, double y);
	//初始化更新航迹目标
	//void InitTraceGlyph(int id, const boost::any& target,const boost::any& data);
	void UpdateLabel_AircraftInfo( WLabelFields& fields, AircraftInfo* pAcftInfo );
	void UpdateLabel_TraceInfo(WAircraftGlyph* aircraftGlyph, WLabelFields& fields,  AircraftTrace* pTraceInfo );
	void UpdateTelemeterLine(WAircraftGlyph* gly);
	//在场面添加飞机
	void InitSingleAircraftGlyph(AircraftTrace* pTrace);
	void UpdateSingleAircraftTrace(AircraftTrace* pTrace);
	void UpdateSingleAircraftPRLPos(std::string& strName,WPointF& point);
public:
    //添加经纬度显示
	void AddLongLatInfo(const WWorldPointF& pointF);
	//删除经纬度显示
	void DeleteLonLatInfo(const WWorldPointF& pointF);
	//删除全部的经纬度显示
	void DeleteAllLongLatInfos();
private:
	void InitCoordinate();
	void InitRunwayGlyph();
	void InitTaxinglineGlyph();
	void InitFixpointGlyph();
	void InitGateGlyph();
	void GetBaseDataFromDB();
	void InitSysInfoGlyph();
	void InitNAVPointGlyph();
	void InitSectorGlyph();
	void InitRestricAreaGlyph();
	void InitRouteGlyph();
	void InitMsawAreaGlyph();

	
	/*********************************************************
	*函数名：UpdateTrace
	*函数功能：更新航迹
	*变量：aircraftGlyph标识飞机,pTrace指定路线
	**********************************************************/
    void UpdateTrace(WAircraftGlyph* aircraftGlyph,AircraftTrace *pTrace);
	//void UpdateCurAircraft(const WLabelEventFeedback& pFeedback);

	//测试函数，在不连接网络的情况下初始化一些飞机
	void InitSomeAircraft();
public:
	template<class T>
	void SetAircraftTrace(int nTraceNo, T* pTrace);
	AircraftTrace* GetAircraftTrace(int nTraceNo);
	hmFplTraces GetTrace(){ return m_hmTraces;}
	void ClearTraces();
	void SetCurAircraftTrace(int iTraceID);

	


protected:
	SimMapPtr	    m_pSimMap;
	GlyphManagerPtr	m_pGlyphManager;
	CoordinatePtr	m_pCoordinate;
	TotalBaseData	*m_pDataBase;
	GetDataFromDB	*m_pGetDataFromDB;
private:
	hmFplTraces	m_hmTraces;
	AircraftTrace* m_pCurTraces;

	
};
template<class T>
void CGlyphCreator::SetAircraftTrace(int nTraceNo, T* pTrace)
{
	//m_hmTraces[nTraceNo] = pTrace;
	m_hmTraces.insert(std::make_pair(nTraceNo,pTrace));
}
#endif // CGLYPHCREATOR_H
