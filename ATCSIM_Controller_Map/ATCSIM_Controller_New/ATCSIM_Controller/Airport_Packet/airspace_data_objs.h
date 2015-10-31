//此文件中定义空域相关的对象类，包括以下对象：
//导航台 Beacon
//扇区   Sector
//航路   Course
//航路上的导航台   CourseBeacon

#ifndef _H_AIRSPACE_DATA_OBJS_H
#define _H_AIRSPACE_DATA_OBJS_H
#include <string>
#include "DataObj.h"
#include "assistance_data_objs.h"
#include <boost/boost/shared_ptr.hpp>
#include <boost/boost/make_shared.hpp>


/*---------------导航台-------------*/
class Beacon : public DataObj
{
public:
	Beacon(void);
	~Beacon(void);

	int GetId();
	std::string GetDisplayLabel();

	//Set方法
	void SetBeaconID(int iBeaconID);
	void SetBeaconCode(std::string strCode);
	void SetBeaconName(std::string strBeaconName);
	void SetLongitude(double dLongitude);
	void SetLatitude(double dLatitude);
	void SetHeight(double dHeight);
	void SetType(int iType);
	void SetIconID(int iIconID);
	void SetIsStdReport(bool bIsStdReport);

	//Get方法
	int GetBeaconID();
	std::string GetBeaconCode();
	std::string GetBeaconName();
	double GetLongitude();
	double GetLatitude();
	double GetHeight();
	int GetType();
	int GetIconID();
	bool GetIsStdReport();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iBeaconID & m_strBeaconCode & m_strBeaconName & m_dLongitude & m_dLatitude & m_dHeight & m_iType & m_iIconID & m_bIsStdReport;
	}

private:
	int m_iBeaconID;			/*导航台ID*/
	std::string m_strBeaconCode;
	std::string m_strBeaconName;	/*导航台的中文名称*/
	double m_dLongitude;                 /*导航台经度*/
	double m_dLatitude;                 /*导航台纬度*/
	double m_dHeight;             /*  导航台高度（米）*/
	int m_iType;				/*类型 0x0 = 无类型，仅代表空中的一个点 ，仅代表空中一个点，0x1 = NDB无方向信标台，0x2 = DME测距台，0x4 = VOR全向信标台 */
	int m_iIconID;			/*标识,地图能显示出来的图案,引用ICON表 null*/
	bool m_bIsStdReport;		/*是否为标准报告点(0 = 否，1 = 是)not null default 0*/

};


/*!
\brief  监视传感器类型（雷达类型）
\details  
\author DXQ
\date 2013/6/19
*/
enum ENUM_SURVEILLANCE_SENSOR_TYPE
{
	SENSOR_NULL = 0x00,		//无效传感器
	SENSOR_PSR = 0x01,		//一次雷达
	SENSOR_SSR = 0x02,		//二次雷达
	SENSOR_ADSB = 0x04,		//ADS-B
};


/*!
\brief  监视传感器（雷达）
\details  
\author DXQ
\date 2013/6/19
*/
class SurveillanceSensor : public DataObj
{

public:
	SurveillanceSensor(void);
	~SurveillanceSensor(void);

	int GetId();
	std::string GetDisplayLabel();


	//拷贝、赋值函数
	SurveillanceSensor(const SurveillanceSensor &sensor);
	SurveillanceSensor& operator=(const SurveillanceSensor& sensor);


//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSensorId & m_strSensorName & m_eSensorType & m_dLongitude & m_dLatitude 
			& m_dAltitude & m_iPeriod & m_iRange & m_dElevationAngle & m_dDepressionAngle;
	}

public:
	int m_iSensorId;							//传感器ID
	std::string m_strSensorName;				//传感器名称
	ENUM_SURVEILLANCE_SENSOR_TYPE m_eSensorType;//传感器类型
	double m_dLongitude;						//传感器经度
	double m_dLatitude;							//传感器纬度
	double m_dAltitude;							//传感器高度
	int m_iPeriod;								//传感器扫描周期（以秒为单位）
	int m_iRange;								//传感器扫描范围（以公里为单位）
	double m_dElevationAngle;					//雷达上迎角
	double m_dDepressionAngle;					//雷达下迎角
};

/*--------------------扇区-------------------*/
class Sector : public DataObj
{
public:
	Sector(void);
	~Sector(void);

	int GetId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Sector(const Sector &sector);
	Sector& operator=(const Sector& sector);


	//Set 方法
	void SetSectorID(int iSectorID);
	void SetSectorName(std::string strSectorName);
	void SetSectorFrequency(double dFrequency);


	//Get方法
	int GetSectorID();
	std::string GetSectorName();
	double GetSectorFrequency();


	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSectorID & m_strSectorName & m_dFrequency;
	}


private:
	int m_iSectorID;			    /*管制扇区ID*/
	std::string m_strSectorName;	/*扇区名称*/
	double m_dFrequency;            /*扇区频率*/

};

/*!
\brief  用于区分空中点所属区域类型
\details  
\author GQ
\date 2013/5/29
*/
enum POINT_OWNER_TYPE
{
	POT_STCA_AREA = 0,			// 冲突告警区
	POT_MSAW_AREA= 1,			// 最低引导扇区
	POT_RESTRICT_AREA = 2,     // 限制区（禁区，危险区
	POT_RADARROBE = 3,			//雷达地理盲区
	POT_QNH_AREA =4,				//QNH区域, QNH(英文全称: query normal height, 修正海压)
	POT_INHIBITORY_AREA = 5	//告警抑制区
};

/*!
\brief  点的位置
\details  
\author GQ
\date 2013/5/29
*/
class PointPosition : public DataObj
{
public:
	PointPosition();
	~PointPosition();
	virtual int GetId();
	virtual int GetOwnerId();
	virtual std::string GetDisplayLabel();
	void SetSequence(int iSeq); //为了用于designer的模版类增加
	int GetSequence();			   //为了用于designer的模版类增加
	int m_iPointPositionID;       //点的ID
	std::string m_strPointPositionName; //点的名称
	int m_iSequence; //点的序号
	POINT_OWNER_TYPE m_enumOwnerType; //所属类型 0冲突告警区，1最低引导扇区2限制区（禁区，危险区）3雷达地理盲区
	int m_iOwnerID;	//所属ID
	double m_dLongtitude; //经度
	double m_dLatitude;   //纬度
	double m_dHeight;     //高度
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iPointPositionID & m_strPointPositionName &m_iSequence &  m_enumOwnerType & m_iOwnerID & m_dLongtitude & m_dLatitude
			& m_dHeight;
	}
};

/*!
\brief  冲突告警区的类型
\details  
\author YY
\date 2013/6/8
*/
enum STCA_AREA_TYPE
{
	ACC_LOW = 0,    
	ACC_RVSM,       
	APP,            
	TWR,            
	FINAL,          
	NTZ  ,
	DEFAULT       
};

/*!
\brief  冲突告警区
\details  
\author GQ
\date 2013/5/29
*/
class StcaArea : public DataObj
{
public:
	StcaArea();
	~StcaArea();
	int GetId();
	std::string GetDisplayLabel();
	int m_iStcaAreaID;
	std::string	m_strStcaAreaName;  //冲突告警区名称
	int     m_iLineStyle;  //显示区域的边线线型
	int     m_iColor;   //显示的颜色
	double  m_dLowestAlt;//最低高度
	double  m_dHighestAlt;//最高高度
	STCA_AREA_TYPE		m_itype;//冲突告警区类型
	double  m_dHorizontalAlarmRange;//水平告警距离
	double  m_dVerticalAlarmRange;//垂直告警距离
	double  m_dConverseTime;  //逆向时间
	double  m_dSuitableTime;  //顺向时间
	double  m_dCrossTime;     //交叉时间
	double  m_dFinalSideDis;  //切获不同航向道飞机的横向告警距离
	double  m_dFinalEndDis;   //切获同一航向道飞机的纵向告警距离
	std::vector<boost::shared_ptr<PointPosition> > m_vStcaAreaPoint;//点组成的区域
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStcaAreaID & m_strStcaAreaName & m_iLineStyle & m_iColor & m_dLowestAlt &m_dHighestAlt & m_itype & m_dHorizontalAlarmRange
			&m_dVerticalAlarmRange & m_dConverseTime & m_dSuitableTime & m_dCrossTime & m_dFinalSideDis
			& m_dFinalEndDis & m_vStcaAreaPoint;
	}
};


/*!
\brief  最低引导扇区，用于低高告警
\details  
\author GQ
\date 2013/5/29
*/
class MsawArea : public DataObj
{
public:
	MsawArea();
	~MsawArea();
	int GetId();
	std::string GetDisplayLabel();

	int m_iMsawAreaID; //最低引导扇区ID
	std::string m_strMsawAreaName;  //最低引导扇区名称
	int     m_iLineStyle;  //显示区域边界的线型
	int    m_iColor;    //显示区域边界的颜色
	double m_dHeight;//最低高度
	std::vector<boost::shared_ptr<PointPosition> > m_vMsawAreaPoint;//点组成的区域

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMsawAreaID & m_strMsawAreaName & m_iLineStyle & m_iColor  & m_dHeight  &m_vMsawAreaPoint;
	}
};




/*!
\brief  由于RestrictArea可用于限制区，禁区和危险区，所以用该枚举类型来区分这几个区域
\details  
\author GQ
\date 2013/5/29
*/
enum AREA_TYPE
{
	AT_RESTRICT = 0,        // 限制区
	AT_FORBID = 1,			// 禁区
	AT_DANGER = 2,          // 危险区
	AT_MILITARY,            // military area
	AT_RVSM                 // RVSM area

};

/*!
\brief  限制区或是禁区或是危险区
\details  
\author GQ
\date 2013/5/29
*/
class RestrictArea : public DataObj
{
public:

	RestrictArea();
	~RestrictArea();
	int GetId();
	std::string GetDisplayLabel();
	int m_iRestrictAreaID; //限制区ID
	std::string m_strRestrictAreaName; //限制区名称
	AREA_TYPE m_enumAreaType;  //区域类型 0是限制区 1是禁区 2是危险区
	bool m_bIsUsed; //在训练中，是否被使用
	double  m_dLowestAlt;//最低高度
	double  m_dHighestAlt;//最高高度
	double  m_dStartTime;//激活时间段的开始时间(单位：秒)
	double  m_dEndTime;//激活时间段的结束时间(单位：秒)
	int    m_iLineStyle;
	int    m_iColor;
	std::vector<boost::shared_ptr<PointPosition> > m_vRestrictAreaPoint;//点组成的区域
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRestrictAreaID & m_strRestrictAreaName & m_enumAreaType & m_bIsUsed  & m_dLowestAlt
			&m_dHighestAlt & m_dStartTime & m_dEndTime  & m_iLineStyle & m_iColor & m_vRestrictAreaPoint;
	}
};


/*!
\brief  QNH区域
\details  
\author CX
\date 2013/07/10
*/
class QnhArea : public DataObj
{
public:

	QnhArea();
	~QnhArea();
	int GetId();
	std::string GetDisplayLabel();
	int m_iQnhAreaID;						//qnh区域ID
	std::string m_strQnhAreaName;	//qnh名称
	bool m_bIsUsed;				//在训练中，是否被使用
	double  m_dLowestAlt;		//最低高度
	double  m_dHighestAlt;		//最高高度
	double  m_dQnhValue;		//qnh值
	int    m_iLineStyle;
	int    m_iColor;
	std::vector<boost::shared_ptr<PointPosition> > m_vQnhAreaPoint; //组成qnh区域的点
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iQnhAreaID & m_strQnhAreaName &  m_bIsUsed  & m_dLowestAlt
			& m_dHighestAlt & m_dQnhValue & m_iLineStyle & m_iColor & m_vQnhAreaPoint;
	}
};

/*!
\brief  告警抑制区
\details  
\author ZJ
\date 2013/7/16
*/
enum INHIBITORY_AREA_TYPE
{
	IAT_STCA_AREA_TYPE = 0,     //冲突告警抑制区
	IAT_MSAW_AREA_TYPE = 1  //低高告警抑制区
};

class InhibitoryArea : public DataObj
{
public:
	InhibitoryArea();
	~InhibitoryArea();

	//拷贝、赋值函数
	InhibitoryArea(const InhibitoryArea &inhibitoryArea);
	InhibitoryArea& operator=(const InhibitoryArea& inhibitoryArea);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iInhibitoryAreaID & m_strInhibitoryAreaName & m_enumType & m_dLowestAlt & m_dHighestAlt & m_vInhibitoryAreaPoint;
	}

	int GetId();
	std::string GetDisplayLabel();
	int  m_iInhibitoryAreaID;
	std::string m_strInhibitoryAreaName;
	INHIBITORY_AREA_TYPE  m_enumType;  
	double  m_dLowestAlt;//最低高度
	double  m_dHighestAlt;//最高高度
	std::vector<boost::shared_ptr<PointPosition> > m_vInhibitoryAreaPoint;//点组成的区域 
};

/*----------------ATS-----------------*/
class ATS : public DataObj
{
public:
	ATS();
	~ATS();

	//
	int GetId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	ATS(const ATS &ATS);
	ATS& operator=(const ATS& ATS);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iATSId & m_strATSName & m_vecRoutePt;
	}

public:
	int m_iATSId;		              /* ATSID */
	std::string m_strATSName;	      /* ATS名称*/
	std::vector<RoutePt> m_vecRoutePt;     /* ATS包括的航路点 */
};


/*!
\brief  雷达地理盲区数据类
\details  
\author JZH
\date 2013/5/28
*/
class Radarrobe : public DataObj
{
public:
	Radarrobe();
	~Radarrobe();

	//
	int GetId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Radarrobe(const Radarrobe &radarrobe);
	Radarrobe& operator=(const Radarrobe& radarrobe);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRadarrobeId & m_iAirspaceId & m_strRadarrobeName & m_dHeight & m_vRadarrobePoint;
	}

public:
	int m_iRadarrobeId;		                /* 雷达盲区ID */
	int m_iAirspaceId;						/* 所属空域ID */
	std::string m_strRadarrobeName;	        /* 雷达盲区名称*/
	double m_dHeight;						/* 雷达地理盲区高度(单位：米)*/
	std::vector<boost::shared_ptr<PointPosition> > m_vRadarrobePoint; //点组成的区域
};

/*!
\brief  固定航路数据类
\details  
\author JZH
\date 2013/6/3
*/
class Course : public DataObj
{
public:
	Course();
	~Course();

	//
	int GetId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Course(const Course &course);
	Course& operator=(const Course& course);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCourseId & m_iAirspaceId & m_strCourseName & m_bDoubleLine & m_dWidth & m_vecRoutePt;
	}

public:
	int m_iCourseId;				/* 航路ID */
	std::string m_strCourseName;	/* 航路名称*/
	int m_iAirspaceId;				/*所属空域ID*/
	bool m_bDoubleLine;				/*航路是否是双线*/
	double m_dWidth;				/*双线航路宽度(单位：千米)*/
	std::vector<boost::shared_ptr<RoutePt> > m_vecRoutePt;   /* 航路包括的航路点 */
};
#endif //_H_AIRSPACE_DATA_OBJS_H


