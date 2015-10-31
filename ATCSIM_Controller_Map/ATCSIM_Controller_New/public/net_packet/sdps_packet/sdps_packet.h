#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
#include "BaseTypeDefine/PublicTypeDefine.h"
#include "Serialization/wserialize.h"


//! �������ݴ���ϵͳ��Surveillance Data Processing System������
struct SDPSTrack 
{
    SDPSTrack::SDPSTrack(){}

    int iTrackID;                            ///< ����ID
    ENUM_TRACKTYPE TrackType;                ///< ��������
    int iICAOAddr;                           ///< ������ICAO��ַ
    double dLongitude;                       ///< ����������
    double dLatitude;                        ///< ������γ��
    int iAltitude;		                     ///< �߶� m
    ENUM_AltitudeType AltitudeType;          ///< �߶�����
    double dGS;			                     ///< GS km/h
    double dTrackAngle;			             ///< ��������
    std::string strSSR;                      ///< �����״���
    std::string strCallSign;                 ///< ����������
    std::vector<std::string> vecSensors;     ///< ��⵽�ú����Ĵ�������������, �����ڵ����Ӻ���ʱ�����ֶ�����
    bool bSPIFlag;                           ///< SPI��־
    int Emergency;                           ///< �����������
	ENUM_OBJ_TYPE ObjType;                   ///< Ŀ������
    double dROCD;                            ///< �����½��ʣ�����Ϊ�����½�Ϊ����ƽ��Ϊ0


	//���л�
    template<typename Archive>
    Archive& serialize(Archive& ar,const unsigned int version)
    {
        return ar & iTrackID & TrackType & iICAOAddr & dLongitude & dLatitude & iAltitude &
            AltitudeType & dGS & dTrackAngle & strSSR & strCallSign & vecSensors & bSPIFlag & Emergency & ObjType & dROCD;
    }
};

////! �������ݴ���ϵͳ���������ۺ��״����
//class SDPSTrackPacket : public CSerial_Base
//{
//    PKT_DECLARE_DYNCREATE(SDPSTrackPacket);
//
//public:
//    std::vector<SDPSTrack> m_vtrace;         ///< �����ṹ����
//    
//private:
//    SERIALIZE_PACKET(m_vtrace)
//};
//
////! �������ݴ���ϵͳ�������������Ӻ�������
//class MonoSDPSTrackPacket : public CSerial_Base
//{
//    PKT_DECLARE_DYNCREATE(MonoSDPSTrackPacket);
//
//public:
//    std::vector<SDPSTrack> m_vtrace;         ///< �����ṹ����
//    std::string m_strSensorName;             ///< �ú��������Ӧ�Ĵ���������
//
//private:
//    SERIALIZE_PACKET(m_vtrace & m_strSensorName)
//};


