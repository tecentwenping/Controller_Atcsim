#ifndef _AIRPORT_PACKET_H
#define _AIRPORT_PACKET_H
#include "airport_data_objs.h"
#include "airspace_data_objs.h"
#include "assistance_data_objs.h"
//回复包：机场数据包
class AckAirportDataPacket
{
public:
	AirportData m_airportdata;
	std::vector<AirportData> m_vecAirport; //所有机场
	std::vector<RunwayData> m_vcRunWayData;//跑道
	std::vector<RoadData> m_vcRoadData;//滑行道
	std::vector<FixpointData> m_vcFixpointData;//固定点
	std::vector<Tower> m_vecTower;
	std::vector<AirportModel> m_vecAirportModel;
	std::vector<GateData> m_vecGate;//停机位
	std::vector<Sid> m_vecSid; //标准进场
	std::vector<Star> m_vecStar; //标准离场
	std::vector<Macro> m_vecMacro; //宏
	std::vector<MacroGroup> m_vecMacroGroup; //宏组
	std::vector<Stdapch> m_vecStdapch;//进近程序
	std::vector<Hold> m_vecHold; //等待程序
	std::vector<Miss> m_vecMiss; //复飞程序
	std::vector<LightGroup> m_vecLightGroup; //灯光组
	std::vector<Route> m_vecRoute; //路线
	std::vector<Light> m_vecLight;  //灯
	std::vector<LightCollection> m_vecLightCollection; //灯光组组合
	std::vector<LightGroupDetail> m_vecLightGroupDetail; //灯光组与其对应的灯

};
//回复包：空中数据包
class AckAirspaceDataPacket
{
public: 
	std::vector<Beacon> m_vecBeacon;				//导航台
	std::vector<SurveillanceSensor> m_vecSensor;	//监视传感器（雷达）
	std::vector<StcaArea> m_vecStcaArea;			//冲突告警区
	std::vector<MsawArea> m_vecMsawArea;			//最低引导扇区
	std::vector<RestrictArea> m_vecRestrictAera;    //限制区，禁区和危险区
	std::vector<ATS> m_vecATS;						//临时航路
	std::vector<Radarrobe> m_vecRadarrobe;			//雷达地理盲区
	std::vector<Course> m_vecCourse;				//固定航路
	std::vector<QnhArea> m_vecQnhArea;			//QNH区
	std::vector<InhibitoryArea> m_vecInhibitoryArea;	//告警抑制区

	//以下为扇区相关数据
	std::vector<Sector> m_vecSector;				//扇区
	std::vector<GlyphPt>  m_vecGlyphPt;
	std::vector<GlyphPtArcInfo> m_vecGlyphPtArcInfo;
	std::vector<Cylinder> m_vecCylinder;
	std::vector<CylinderGlyph> m_vecCylinderGlyph;
};


#endif