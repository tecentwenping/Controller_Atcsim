#ifndef _AIRCRAFTTRACE_H__
#define _AIRCRAFTTRACE_H__
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: ControllerAcftTrack
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/01/03
  ����  ����:  ���ļ���������ControllerAcftTrack�������Ǻ������࣬���к���
               ����Ӹ���̳�
  ����  ����:   
**************************************************************************/
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QDataStream>
#include "wworldpoint.h"
#include "PublicStruct.h"
using namespace boost;
class AircraftInfo;
//������Ϊ��������Ļ���

// ����˵��
// 2013-9-22
// ������Ϊ�˺�������Ļ��࣬�����е�������Ϣ��û����Ƶúܺ�
// ��Ϊ����Ա��������������Ϣֻ��Թ���Ա���ã�������ϢҲֻ��Ի�������
// ���Ը�������ڲ�ͣ���������ݵ�ʱ���Ӧ�ÿ��Ƿֿ���
// ������֯��ʱ�򲢲�һ����Ҫȥ����һ�����ݣ������������ֵط���Ҫdynamic_cast��ʱ���ϵĻ���
// ������������ã�������forѭ���зǼ�ӵ�dynamic_castת�������µ�Ч��
// �ⲿ��Ӧ����Ϊһ���Ż���
// ControllerAircraftTrace, PilotAircraftTrace

#include "public/ControllerAcftInfo.h"
#include "public/PublicStruct.h"
class AircraftTrace
{
	friend QDataStream& operator<<(QDataStream&,const AircraftTrace&);
	friend QDataStream& operator>>(QDataStream&,AircraftTrace&);
public:
	typedef boost::shared_ptr<WPointF> PointPtr;

public:
	AircraftTrace();
	virtual ~AircraftTrace();
public:
	void ComputeMapXY();
	void ComputPRLPos();
	void ComputPRLPos(int iTraceID);
	void SetPRLTime(const float fTime);
	void SetHistoryNum(const int nHistoryNum);
	void GetSSRCode(int &iSSR) const;
public:
	//process common data from trace packet
	int								    m_nTraceID;
	PublicDataStruct::ENUM_TRACKTYPE	m_euTrackType;          ///< ��������
    int									m_nICAOAddress;         ///< ������ICAO��ַ
	std::string							m_strName;
	std::string							m_strSSR;
	double								m_dLongitude;           ///< ����������
	double								m_dLatitude;            ///< ������γ��
	int									m_nAttitude;		       ///< �߶�		Unit : m
	PublicDataStruct::ENUM_AltitudeType	m_euAltitudeType;    ///< �������߶�����
	int									m_nDesAltitude;			///< ������Ŀ�ĸ߶�
	PublicDataStruct::ENUM_AltitudeType	m_euDesAltitudeType;	///< ������Ŀ�ĸ߶�����
	double								m_dGAS;                 ///< ������GAS km/h
	double								m_dHeading;             ///< ��������ͷ����
	double								m_dTrackAngle;          ///< ��������������
	PublicDataStruct::ENUM_OBJ_TYPE		m_euObjType;             ///< Ŀ������
	int									m_euEmergencyType;  ///< ���ú����������������
	//////////////////////////////////////////////////////////////////////////
	bool								m_bHide;              ///< �Ƿ�����
	float								m_fAbsX;		    //����λ��x	Unit : km. Absolute position of aircraft.
	float								m_fAbsY;		    //����λ��y	Unit : km. Absolute position of aircraft.
	unsigned char						m_byAtt;			//��̬attitude��0: cruising , 1: climb ; 2: decent
	PublicDataStruct::ENUM_STATE_TYPE	eStateType;			//�ɻ�״̬��׹�١���������ȴ����ȵȴ������С���ɡ��ڿ��С������
	float								m_fPRLTime;          //������Ԥ���ߵ�ָʾʱ��(��λ������)
	int									m_nHistoryNum;        //������β�������(Ŀǰ��ʱ���ã�
	WPointF								m_wPRLPos;           //��������Ԥ����PRL���յ�
	PublicDataStruct::RADAR_SIGNAL_TYPE	m_eCurSignalType;
	bool								m_bShowLabel;
	int									m_iCount; //�����������ڱ�����˸(�磺�����յ���������ʱ����˸�ĸ�����)
	static double						PI;
	PublicDataStruct::Aircraft          m_aircraftInfo;//�ɻ��Ļ���������id������ţ�β�����𣬻�����������ɶ�����չ����������ȫ����

	std::vector<PointPtr>				m_vHistoryPos;
};
inline QDataStream& operator<<(QDataStream& out,const AircraftTrace& aircraftTrace)
{ 
	QString strName(QString::fromStdString(aircraftTrace.m_strName));
	QString strSSR(QString::fromStdString(aircraftTrace.m_strSSR));
	out<<aircraftTrace.m_nTraceID<<aircraftTrace.m_euTrackType<<aircraftTrace.m_nICAOAddress
	   <<strName<<strSSR<<aircraftTrace.m_dLongitude<<aircraftTrace.m_dLatitude<<aircraftTrace.m_nAttitude
	   <<aircraftTrace.m_euAltitudeType<<aircraftTrace.m_nDesAltitude<<aircraftTrace.m_euDesAltitudeType
	   <<aircraftTrace.m_dGAS<<aircraftTrace.m_dHeading<<aircraftTrace.m_dTrackAngle<<aircraftTrace.m_euObjType
	   <<aircraftTrace.m_euEmergencyType<<aircraftTrace.m_bHide<<aircraftTrace.m_fAbsX<<aircraftTrace.m_fAbsY
	   <<aircraftTrace.m_byAtt<<aircraftTrace.eStateType<<aircraftTrace.m_fPRLTime<<aircraftTrace.m_nHistoryNum
	   <<aircraftTrace.m_wPRLPos.x()<<aircraftTrace.m_wPRLPos.y()<<aircraftTrace.m_eCurSignalType
	   <<aircraftTrace.m_bShowLabel<<aircraftTrace.m_iCount;  
	return out;
}
inline QDataStream& operator>>(QDataStream& in,AircraftTrace& aircraftTrace)
{
	int				nTraceID;         
	int				nICAOAddress;         
	QString			strName;
	QString			strSSR;
	double			dLongitude;          
	double			dLatitude;            
	int				nAttitude;		       
	int				nDesAltitude;			
	double			dGAS;            
	double			dHeading;             
	double			dTrackAngle;           
	int				euEmergencyType;  
	bool			bHide;              
	float			fAbsX;		    
	float			fAbsY;		   
	unsigned char	byAtt;					
	float			fPRLTime;          
	int				nHistoryNum;                
	bool			bShowLabel;
	int				iCount; 
	int TrackType;
	int AltitudeType;
	int DesAltitudeType;
	int ObjType;
	int StateType;
	int CursingnalType;
	double PRLPosX;
	double PRLPosY;
	in>>nTraceID>>TrackType>>nICAOAddress>>strName>>strSSR>>dLongitude>>dLatitude
	  >>nAttitude>>AltitudeType>>nDesAltitude>>DesAltitudeType>>dGAS>>dHeading
	  >>dTrackAngle>>ObjType>>euEmergencyType>>bHide>>fAbsX>>fAbsY>>byAtt>>StateType
	  >>fPRLTime>>nHistoryNum>>PRLPosX>>PRLPosY>>CursingnalType>>bShowLabel>>iCount;
	WPointF	wPRLPos(PRLPosX,PRLPosY); 
	aircraftTrace.m_nTraceID = nTraceID;
	aircraftTrace.m_euTrackType = (PublicDataStruct::ENUM_TRACKTYPE)TrackType;
	aircraftTrace.m_nICAOAddress = nICAOAddress;
	aircraftTrace.m_strName = strName.toStdString();
	aircraftTrace.m_strSSR = strSSR.toStdString();
	aircraftTrace.m_dLongitude = dLongitude;
	aircraftTrace.m_dLatitude = dLatitude;
	aircraftTrace.m_nAttitude = nAttitude;
	aircraftTrace.m_euAltitudeType = (PublicDataStruct::ENUM_AltitudeType)AltitudeType;
	aircraftTrace.m_nDesAltitude = nDesAltitude;
	aircraftTrace.m_euDesAltitudeType = (PublicDataStruct::ENUM_AltitudeType)DesAltitudeType;
	aircraftTrace.m_dGAS = dGAS;
	aircraftTrace.m_dHeading = dHeading;
	aircraftTrace.m_dTrackAngle  = dTrackAngle;
	aircraftTrace.m_euObjType = (PublicDataStruct::ENUM_OBJ_TYPE)ObjType;
	aircraftTrace.m_euEmergencyType = euEmergencyType;
	aircraftTrace.m_bHide = bHide;
	aircraftTrace.m_fAbsX = fAbsX;
	aircraftTrace.m_fAbsY = fAbsY;
	aircraftTrace.m_byAtt = byAtt;
	aircraftTrace.eStateType = (PublicDataStruct::ENUM_STATE_TYPE)StateType;
	aircraftTrace.m_fPRLTime = fPRLTime;
	aircraftTrace.m_nHistoryNum = nHistoryNum;
	aircraftTrace.m_wPRLPos = wPRLPos;
	aircraftTrace.m_eCurSignalType = (PublicDataStruct::RADAR_SIGNAL_TYPE)CursingnalType;
	aircraftTrace.m_bShowLabel = bShowLabel;
	return in;
}
#endif	//_AIRCRAFTTRACE_H__