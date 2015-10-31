#ifndef _AIRCRAFTTRACE_H__
#define _AIRCRAFTTRACE_H__
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: ControllerAcftTrack
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/01/03
  【描  述】:  此文件定义了类ControllerAcftTrack，该类是航迹基类，所有航迹
               必须从该类继承
  【其  它】:   
**************************************************************************/
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QDataStream>
#include "wworldpoint.h"
#include "PublicStruct.h"
using namespace boost;
class AircraftInfo;
//该类作为航迹处理的基类

// 补充说明
// 2013-9-22
// 该类作为了航迹处理的基类，但其中的数据信息本没有设计得很好
// 作为管制员，机长，部分信息只针对管制员有用，部分信息也只针对机长有用
// 所以该类如果在不停的扩充内容的时候就应该考虑分开了
// 数据组织有时候并不一定需要去抽象一下数据，这样带来部分地方需要dynamic_cast的时间上的花费
// 并且如果处理不好，导致在for循环中非间接的dynamic_cast转换，导致低效率
// 这部分应该作为一个优化点
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
	PublicDataStruct::ENUM_TRACKTYPE	m_euTrackType;          ///< 航迹类型
    int									m_nICAOAddress;         ///< 航空器ICAO地址
	std::string							m_strName;
	std::string							m_strSSR;
	double								m_dLongitude;           ///< 航空器经度
	double								m_dLatitude;            ///< 航空器纬度
	int									m_nAttitude;		       ///< 高度		Unit : m
	PublicDataStruct::ENUM_AltitudeType	m_euAltitudeType;    ///< 航空器高度类型
	int									m_nDesAltitude;			///< 航空器目的高度
	PublicDataStruct::ENUM_AltitudeType	m_euDesAltitudeType;	///< 航空器目的高度类型
	double								m_dGAS;                 ///< 航空器GAS km/h
	double								m_dHeading;             ///< 航空器机头朝向
	double								m_dTrackAngle;          ///< 航空器航迹朝向
	PublicDataStruct::ENUM_OBJ_TYPE		m_euObjType;             ///< 目标类型
	int									m_euEmergencyType;  ///< 设置航空器紧急情况类型
	//////////////////////////////////////////////////////////////////////////
	bool								m_bHide;              ///< 是否隐藏
	float								m_fAbsX;		    //坐标位置x	Unit : km. Absolute position of aircraft.
	float								m_fAbsY;		    //坐标位置y	Unit : km. Absolute position of aircraft.
	unsigned char						m_byAtt;			//姿态attitude，0: cruising , 1: climb ; 2: decent
	PublicDataStruct::ENUM_STATE_TYPE	eStateType;			//飞机状态：坠毁、阻塞、冷等待、热等待、滑行、起飞、在空中、降落等
	float								m_fPRLTime;          //航空器预计线的指示时间(单位：分钟)
	int									m_nHistoryNum;        //航空器尾迹点个数(目前暂时无用）
	WPointF								m_wPRLPos;           //航空器的预计线PRL的终点
	PublicDataStruct::RADAR_SIGNAL_TYPE	m_eCurSignalType;
	bool								m_bShowLabel;
	int									m_iCount; //计数器，用于标牌闪烁(如：当接收到机长报告时，闪烁四个周期)
	static double						PI;
	PublicDataStruct::Aircraft          m_aircraftInfo;//飞机的基本参数，id，航班号，尾流级别，机型名，机身成都，翼展，质量，安全间距等

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