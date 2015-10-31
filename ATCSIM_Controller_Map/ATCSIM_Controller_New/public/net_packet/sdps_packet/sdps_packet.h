#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
#include "BaseTypeDefine/PublicTypeDefine.h"
#include "Serialization/wserialize.h"


//! 监视数据处理系统（Surveillance Data Processing System）航迹
struct SDPSTrack 
{
    SDPSTrack::SDPSTrack(){}

    int iTrackID;                            ///< 航迹ID
    ENUM_TRACKTYPE TrackType;                ///< 航迹类型
    int iICAOAddr;                           ///< 航空器ICAO地址
    double dLongitude;                       ///< 航空器经度
    double dLatitude;                        ///< 航空器纬度
    int iAltitude;		                     ///< 高度 m
    ENUM_AltitudeType AltitudeType;          ///< 高度类型
    double dGS;			                     ///< GS km/h
    double dTrackAngle;			             ///< 航迹朝向
    std::string strSSR;                      ///< 二次雷达码
    std::string strCallSign;                 ///< 航空器呼号
    std::vector<std::string> vecSensors;     ///< 检测到该航迹的传感器名称数组, 当用于单监视航迹时，该字段无用
    bool bSPIFlag;                           ///< SPI标志
    int Emergency;                           ///< 特殊情况类型
	ENUM_OBJ_TYPE ObjType;                   ///< 目标类型
    double dROCD;                            ///< 上升下降率，上升为正，下降为负，平飞为0


	//串行化
    template<typename Archive>
    Archive& serialize(Archive& ar,const unsigned int version)
    {
        return ar & iTrackID & TrackType & iICAOAddr & dLongitude & dLatitude & iAltitude &
            AltitudeType & dGS & dTrackAngle & strSSR & strCallSign & vecSensors & bSPIFlag & Emergency & ObjType & dROCD;
    }
};

////! 监视数据处理系统航迹包（综合雷达包）
//class SDPSTrackPacket : public CSerial_Base
//{
//    PKT_DECLARE_DYNCREATE(SDPSTrackPacket);
//
//public:
//    std::vector<SDPSTrack> m_vtrace;         ///< 航迹结构数组
//    
//private:
//    SERIALIZE_PACKET(m_vtrace)
//};
//
////! 监视数据处理系统航迹包（单监视航迹包）
//class MonoSDPSTrackPacket : public CSerial_Base
//{
//    PKT_DECLARE_DYNCREATE(MonoSDPSTrackPacket);
//
//public:
//    std::vector<SDPSTrack> m_vtrace;         ///< 航迹结构数组
//    std::string m_strSensorName;             ///< 该航迹数组对应的传感器名称
//
//private:
//    SERIALIZE_PACKET(m_vtrace & m_strSensorName)
//};


