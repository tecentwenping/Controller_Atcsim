//此文件中定义机场相关的对象类，包括以下对象：
//机场         AirportData
//固定点       FixpointData
//道路固定点   RoadFixpointData
//道路         RoadData
//停机位       GataData
//跑道进入道   InRunwayLineData
//跑道脱离道   VacateLineData
//跑道         RunwayData
//塔台         Tower
//模型         AirportModel
//离场程序     Sid
//进场程序     Star
//宏           Macro
//宏组         MacroGroup
//等待程序 Hold


#ifndef _H_AIRPORT_DATA_OBJS_H
#define _H_AIRPORT_DATA_OBJS_H

#include <string>
#include <vector>
#include "dataObj.h"
#include "assistance_data_objs.h"
#include "./boost/boost/shared_ptr.hpp"
#include "./boost/boost/make_shared.hpp"
using namespace boost;


/*-----------------机场--------------*/
class AirportData : public DataObj
{
public:
	AirportData(void);
	~AirportData(void);
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<AirportData> spAirport);

	void SetAirportID(int iAirportID);
	void SetAirspaceID(int iAirspaceID);
	void SetAirportName(std::string szAirportName);
	void SetAirportCode(std::string szCode);
	void SetCenterPointLongitude(double dCenterPointLongitude);
	void SetCenterPointLatitude(double dCenterPointLatitude);
	void SetElevation(double dElevation);
	void SetMegaticDiff(double dMegaticDiff);
	void SetMainRunway(int iMainRunway);
	void SetDefaultEnvID(int iDefaultEnvID);
	void SetHeading(double dHeading);


	int GetAirportID();
	int GetAirspaceID();
	std::string GetAirportName();
	std::string GetAirportCode();
	double GetCenterPointLongitude();
	double GetCenterPointLatitude();
	double GetElevation();
	double GetMegaticDiff();
	int GetMainRunway();
	int GetDefaultEnvID();
	double GetHeading();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iAirspaceID & m_szAirportName & m_szAirportCode 
			& m_dCenterPointLongitude & m_dCenterPointLatitude & m_dElevation 
			& m_dMegaticDiff & m_iMainRunway & m_iDefaultEnvID & m_dHeading;
	}


private:
	int m_iAirportID;					/* 机场ID */
	int m_iAirspaceID;				/* 空域管制区ID */
	std::string m_szAirportName;		/* 机场名称(机场的文字说明，如：北京首都机场) */
	std::string m_szAirportCode;
	double m_dCenterPointLongitude;	/* 机场中心点经度(单位：弧度) */
	double m_dCenterPointLatitude;	/* 机场中心点纬度(单位：弧度) */
	double m_dElevation;				/* 机场标高（单位：米） */
	double m_dMegaticDiff;			/* 磁差角（单位：弧度）*/
	int m_iMainRunway;				/* 机场的主跑道ID */
	int m_iDefaultEnvID;				/* 机场默认的环境主键码 */
	double m_dHeading;
public:
	AirportData& operator=(const AirportData& rhs)
	{
		this->m_iAirportID=rhs.m_iAirportID;
		this->m_iAirspaceID=rhs.m_iAirspaceID;
		this->m_szAirportName=rhs.m_szAirportName;
		this->m_szAirportCode=rhs.m_szAirportCode;
		this->m_dCenterPointLongitude=rhs.m_dCenterPointLongitude;
		this->m_dCenterPointLatitude=rhs.m_dCenterPointLatitude;
		this->m_dElevation=rhs.m_dElevation;
		this->m_dMegaticDiff=rhs.m_dMegaticDiff;
		this->m_iMainRunway=rhs.m_iMainRunway;
		this->m_iDefaultEnvID=rhs.m_iDefaultEnvID;
		this->m_dHeading=rhs.m_dHeading;
		return *this;

	}

};

/*-----------------固定点--------------*/
class FixpointData : public DataObj
{
public:

	FixpointData();
	~FixpointData();

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<FixpointData> spFixpoint);

	void SetFixpointID(int iFixpointID);
	void SetIconID(int iIConID);
	void SetFixpointName(std::string szFixpointName);
	void SetAirportID(int iAirportID);
	void SetFixpointType(int iFixpointType);
	void SetX(double dX);
	void SetY(double dY);
	void SetZ(double dZ);
	void SetIsWaitingPoint(bool bWaitingPoint);

	int GetFixpointID();
	int GetIconID();
	std::string GetFixpointName();
	int GetAirportID();
	int GetFixpointType();
	double GetX();
	double GetY();
	double GetZ();
	bool GetIsWaitingPoint();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFixpointID & m_iIconID & m_szFixpointName & m_iAirportID 
			& m_iFixpointType & m_dX & m_dY 
			& m_dZ & m_bWaitingPoint;
	}

public:
	enum
	{
		FXP_TYPE_TAXPOINT = 0x1,
		FXP_TYPE_TAXCROSSPOINT = 0x2,
		FXP_TYPE_VEHICLEROADPOINT = 0x4,
		FXP_TYPE_VEHICLEROADCROSSPOINT = 0x8,
		FXP_TYPE_GATEPOINT = 0x10,
		FXP_TYPE_TAXGATECROSSPOINT = 0x20,
		FXP_TYPE_TAXVEHICLECROSSPOINT = 0x40,
		FXP_TYPE_WAITINGPOINT = 0x80,
		FXP_TYPE_AIRSPACEPOINT = 0x100,
		FXP_TYPE_SECTORPOINT = 0x200,
		FXP_TYPE_WARNINGZONEPOINT = 0x400
	};

public:
	int m_iFixpointID;		/*固定点ID*/
	int m_iIconID	;		/*固定点图标*/
	std::string m_szFixpointName;	/*固定点名称*/
	int m_iAirportID;			/*所属的机场ID*/
	int m_iFixpointType;				/*固定点类型, 包括
										0x1	滑行道点、
										0x2	滑行道交点、
										0x4	车行道点、
										0x8	车行道交点、
										0x10	停机位点、
										0x20	滑行道与停机位的交点、
										0x40	滑行道与车行道的交点、
										0x80	等待点、
										0x100	空域中的点
										0x200	构成管制扇区的点、
										0x400	构成报警区的点
										以及一切其他可以用点表示的目标。*/
	double m_dX;				/*固定点的经度（单位：弧度）not null default 0*/
	double m_dY;				/*固定点的纬度（单位：弧度）not null default 0*/
	double m_dZ;				/*固定点高度（单位：米）not null default 0*/
	bool m_bWaitingPoint;
};


/*-----------------道路上的固定点--------------*/
class RoadFixpointData : public DataObj
{
public:
	RoadFixpointData(void);
	~RoadFixpointData(void);
	//得到固定点的序号
	int GetId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<RoadFixpointData> spRoadFixpoint);
	void SetRoadID(int iRoadID);
	void SetSequence(int iSeq);
	void SetFixpointID(int iFixpointID);

	int GetRoadID();
	int GetSequence();
	int GetFixpointID();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();


public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRoadID & m_iSequence & m_iFixpointID;
	}


private:
	int m_iRoadID;			/*道路ID*/
	int m_iSequence;			/*固定点的序号 not null*/
	int m_iFixpointID;			/*固定点*/
};

/*-----------------道路--------------*/
class RoadData : public DataObj
{
public:
	RoadData(void);
	RoadData(const RoadData &roadFixpointData);
	RoadData& operator=(const RoadData& roadFixpointData);

	~RoadData(void);

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<RoadData> spRoad);

	void SetRoadID(int iRoadID);
	void SetAirportID(int iAirportID);
	void SetRoadName(std::string szRoadName);
	void SetRoadType(int iRoadType);
	void SetWidth(double dRoadWidth);
	void SetMaxAircraft(int iMaxAirCraft);

	int GetRoadID();
	int GetAirportID();
	std::string GetRoadName();
	int GetRoadType();
	double GetRoadWidth();
	int GetMaxAircraft();
	
	void  SetFixpoints(std::vector<boost::shared_ptr<RoadFixpointData> >& vData);
	std::vector<boost::shared_ptr<RoadFixpointData> >& GetFixpoints();
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRoadID & m_iAirportID & m_szRoadName 
			& m_iRoadType & m_dWidth & m_iMaxAircraft & m_vRoadFixpoints;
	}


public:
	int m_iRoadID;			/*道路ID*/
	int m_iAirportID;		/*机场ID*/
	std::string m_szRoadName;		/*道路名称*/
	int m_iRoadType;				/*道路类型
									0x1	滑行道、
									0x2 车道、
									0x4 停机位
									not null default 1*/
	double m_dWidth;				/*道路宽度(单位：米) not null default 20*/
	int m_iMaxAircraft;		/*道路允许通过的最大机型 引用机型ID */
	std::vector<boost::shared_ptr<RoadFixpointData> > m_vRoadFixpoints;	/*构成道路的点*/

};

//构成路线的类型
enum ENUM_FORM_ROUTE_TYPE
{
	ROUTE_FIXPOINT_TYPE = 1,	 //固定点类型
	ROUTE_ROAD_TYPE =2			 //滑行道类型
};

/*---------------路线上的固定点或者道路----------*/
class RouteFixpointRoad : public DataObj
{
public:
	RouteFixpointRoad(void);
	~RouteFixpointRoad(void);

	//得到固定点的序号
	int GetId();
	int GetSequence();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<RouteFixpointRoad> spRoadFixpoint);
// 	void SetRoadID(int iRoadID);
 	void SetSequence(int iSeq);
// 	void SetFixpointID(int iFixpointID);
// 
// 	int GetRoadID();
// 	int GetSequence();
// 	int GetFixpointID();
// 
// 	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
// 	void WriteToBuffer(char* pBuffer, int &iOffSize);
// 	int GetBufferSize();


public:
	template<typename Archive>
	Archive& serialize(Archive& ar, const unsigned int version)
	{
		return ar & m_iRouteID & m_iSequence & m_iFactorType & m_iFactorID;
	}


public:
	int m_iRouteID;			/*路线ID，路线的构成原则：开始和结尾必须是点，道路之间必须有点连接，即点 – 道路 – 点 – 道路 – 点？ 没理解cx2013-06-02*/
	int m_iSequence;		/*序号not null default 0 */
	int m_iFactorType;		/*构成该路线的元素是固定点还是道路，1 = 点，2 = 道路 not null default 1 */
	int m_iFactorID;		/*固定点或道路的ID not null default 0 */
};

/*-----------------路线--------------*/
class Route : public DataObj
{
public:
	Route(void);
	Route(const Route &routeFixpointRoadData);
	Route& operator=(const Route& routeFixpointRoadData);

	~Route(void);

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<Route> spRoad);

public:
	template<typename Archive>
	Archive& serialize(Archive& ar, const unsigned int version)
	{
		return ar & m_iRouteID & m_iAirportID & m_szRouteName 
			& m_iType & m_dLength & m_dWidth & m_dWaitX & m_dWaitY & m_vRouteFixpointRoad;
	}


public:
	int m_iRouteID;			/*路线ID*/
	int m_iAirportID;		/*机场ID*/
	std::string m_szRouteName;		/*路线名称*/
	int m_iType;				/*路线适合给什么对象使用，1飞机，2车辆 */
	double m_dLength;	/*路线的长度（单位：千米）not null default 0 */
	double m_dWidth;	/*路线的宽度*/
	double m_dWaitX;		/*等待点X坐标*/
	double m_dWaitY;		/*等待点Y坐标*/
	
	std::vector<boost::shared_ptr<RouteFixpointRoad> > m_vRouteFixpointRoad;	/*构成路线的固定点或者道路*/

};

/*-----------------停机位--------------*/
class GateData : public DataObj
{
public:
	GateData(void);
	~GateData(void);

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	void SetGateID(int iGateID);
	void SetAirportID(int iAirportID);
	void SetGateName(std::string szName);
	void SetRoadID(int iRoadID);
	void SetInGateDataFixpointID(int iInGateDataFixpointID);
	void SetGateFixpointID(int iGateFixpointID);
	void SetLength(double dLength);
	void SetMaxAircraftID(int iMaxAircraftID);
	void SetInternationalType(int iInternationalType);
	void SetBelongedCompanyID(int iBelongedCompanyID);
	void SetStartPosition(int iStartPosition);
	void SetIsDirectTax(bool bIsDirectTax);
	void SetRoutineInLine(int iRoutineInLine);
	void SetRoutinOutLine(int iRoutineOutLine);
	void SetRoutinToRunway(int iRoutineToRunway);

	int GetGateID();
	int GetAirportID();
	std::string GetGateName();
	int GetRoadID();
	int GetInGateDataFixpointID();
	int GetGateFixpointID();
	double GetLength();
	int GetMaxAircraftID();
	int GetInternationalType();
	int GetBelongedCompanyID();
	int GetStartPosition();
	bool GetIsDirectTax();
	int GetRoutineInLine();
	int GetRoutinOutLine();
	int GetRoutinToRunway();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();


//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iGateID & m_iAirportID & m_szGateDataName & m_iRoadID 
			& m_iInGateDataFixpointID & m_iGateFixpointID & m_dLength 
			& m_iMaxAircraftID & m_iInternationalType & m_iBelongedCompanyID 
			& m_iStartPosition & m_bIsDirectTax & m_iRoutineInLine 
			& m_iRoutineOutLine & m_iRoutineToRunway;
	}

public:
	int m_iGateID;			/*停机位ID*/	
	int m_iAirportID;		/*机场ID*/
	std::string m_szGateDataName;		/*停机位名称not null*/
	int m_iRoadID;			/*与表road 中road_id 对应，道路的ID，停机位的构成在道路中。not null default 1*/
	int m_iInGateDataFixpointID;	/*进入停机位的固定点ID not null default 0 */
	int m_iGateFixpointID;		/*停机位的固定点ID not null default 0 */
	double m_dLength;			/*停机位的长度（单位：千米）not null default 0 */
	int m_iMaxAircraftID;		/*停机位允许停靠的最大机型 引用机型ID */
	int m_iInternationalType;	/*航班类型，1国内，2国际，3，国内国际not null default 1  */
	int m_iBelongedCompanyID;			/*停机位属于哪个航空公司，0表示不属于任何航空公司not null default 0 */
	int m_iStartPosition;		/*推出开车位置，根据不同跑道有不同的推出开车位置，不知道应该设置成某一固定点还是什么not null default 1 */
	bool m_bIsDirectTax;		/*是否允许直接滑出 false：不允许，true：允许 not null default false */
	int m_iRoutineInLine;		/*常规进停机位路线（只能设置一条,如果能设置多条，可以改为字符型字段，采用“XXX,XX,XXXX”的方式保存）。
								进港航空器接地后自动脱离，从指定联络道进机坪后到该机停机位常规的滑行路线 not null default 0 */
	int m_iRoutineOutLine;	/*常规出停机位路线，从规定的位置滑出到指定的联络道口，以及从该联络道到跑道头的常规滑行路线 not null default 0 */
	int m_iRoutineToRunway;	/*常规上跑道路线not null default 0  */

};


/*-----------------跑道进入道--------------*/
class InRunwayLineData : public DataObj
{
public:
	InRunwayLineData(void);
	~InRunwayLineData(void);

	//拷贝、赋值函数
	InRunwayLineData(const InRunwayLineData& inRunwayLine);
	InRunwayLineData& operator=(const InRunwayLineData& inRunwayLine);


	int GetId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<InRunwayLineData> spInRunwayLineData);

	//Set方法
	void SetInRunwayLineID(int iID);
	void SetInRunwayLineName(std::string szName);
	void SetRunwayID(int iRunwayID);
	void SetAirportID(int iAirportID);
	void SetSequence(int iSequence);
	void SetRoadID(int iRoadID);
	void SetInPointID(int iInPointID);
	void SetStartPointID(int iStartPointID);
	void SetWaitingPointID(int iWaitingPointID);

	//Get方法
	int GetInRunwayLineID();
	std::string GetInRunwayLineName();
	int GetRunwayID();
	int GetAirportID();
	int GetSequence();
	int GetRoadID();
	int GetInPointID();
	int GetStartPointID();
	int GetWaitingPointID();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();


//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iInRunwayLineID & m_iRunwayID & m_iAirportID & m_szInRunwayLineName & m_iSequence 
			& m_iRoadID & m_iInPointID & m_iStartPointID & m_iWaitingPointID; 
	}

public:
	int m_iInRunwayLineID;     /* 进入道ID 与关联的道路ID一样*/
	int m_iRunwayID;			/* 跑道ID */
	int m_iAirportID;           /* 机场ID*/
	std::string m_szInRunwayLineName; /* 进入道名 */
	int m_iSequence;			/*进入道序号*/
	int m_iRoadID;			    /* 道路ID */
	int m_iInPointID;			/* 进入点ID */
	int m_iStartPointID;		/* 开始点ID */
	int m_iWaitingPointID;	    /* 等待点ID */
};

/*-----------------跑道脱离道--------------*/
class VacateLineData :public DataObj
{
public:
	VacateLineData(void);
	~VacateLineData(void);

	//拷贝、赋值函数
	VacateLineData(const VacateLineData& vacateline);
	VacateLineData& operator=(const VacateLineData& vacateline);

	int GetId();
	std::string GetDisplayLabel();

	//Set方法
	void SetVacateLineID(int iVacateLineID);
	void SetAirportID(int iAirportID);
	void SetVacateLineName(std::string szName);
	void SetSequence(int iSequence);
	void SetRunwayID(int iRunwayID);
	void SetRoadID(int iRoadID);
	void SetStartPointID(int iStartPointID);
	void SetWaitingPointID(int iWaitingPointID);


	//Get方法
	int GetVacateLineID();
	int GetAirportID();
	std::string GetVacateLineName();
	int GetSequence();
	int GetRunwayID();
	int GetRoadID();
	int GetStartPointID();
	int GetWaitingPointID();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iVacateLineID & m_iAirportID & m_szVacateLineName & m_iSequence 
			& m_iRunwayID & m_iRoadID & m_iStartPointID & m_iWaitingPointID; 
	}

public:
	int m_iVacateLineID;       /*脱离道ID*/
	int m_iAirportID;        /*  机场ID*/
	std::string m_szVacateLineName; /*脱离道名称*/
	int m_iSequence;			/*脱离道序号*/
	int m_iRunwayID;			/* 跑道ID */
	int m_iRoadID;			    /* 道路ID */
	int m_iStartPointID;		/* 开始点ID */
	int m_iWaitingPointID;	    /* 等待点ID */
};

/*-----------------跑道--------------*/
class RunwayData : public DataObj
{
public:
	RunwayData();
	~RunwayData();
	RunwayData& operator=(const RunwayData& runway);
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<RunwayData> spRunway);

	//Set方法
	void SetRunWayID(int iRunwayID);
	void SetAirportID(int iAirportID);
	void SetRunwayName(std::string szRunwayName);
	void SetWidth(double dWidth);
	void SetCenterPointLongitude(double CenterPointLongitude);
	void SetCenterPointLatitude(double dCenterPointLatituded);
	void SetLength(double dLength);
	void SetHeading(double dHeading);
	void SetDryFrictionfactor(double dDryFrictionfactor);
	void SetDryFrictionfactor_start(double dDryFrictionfactor_start);
	void SetDryFrictionfactor_mid(double dDryFrictionfactor_mid);
	void SetDryFrictionfactor_end(double dDryFrictionfactor_end);
	void SetGradient(double dGradient);
	void SetStartX(double dStartX);
	void SetStartY(double dStartY);
	void SetEndX(double dEndX);
	void SetEndY(double dEndY);
	void SetHeight(double dHeight);
	void SetMegaticDiff(double dGradient);
	void SetLandingPoint(double dLandingPoint);
	void SetInRunwayLines(std::vector<boost::shared_ptr<InRunwayLineData> >& vInRunwayLine);
	void SetVacateLines(std::vector<boost::shared_ptr<VacateLineData> >& vVacateLine);

	//Get方法

	int GetRunWayID();
	int GetAirportID();
	std::string GetRunwayName();
	double GetWidth();
	double GetCenterPointLongitude();
	double GetCenterPointLatitude();
	double GetLength();
	double GetHeading();
	double GetDryFrictionfactor();
	double GetDryFrictionfactor_start();
	double GetDryFrictionfactor_mid();
	double GetDryFrictionfactor_end();
	double GetGradient();
	double GetStartX();
	double GetStartY();
	double GetEndX();
	double GetEndY();
	double GetHeight();
	double GetMegaticDiff();
	double GetLandingPoint();
	std::vector<boost::shared_ptr<InRunwayLineData> >& GetInRunwayLines();
	std::vector<boost::shared_ptr<VacateLineData> >& GetVacateLines();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRunwayID & m_iAirportID & m_szRunwayName & m_dCenterPointLongitude 
			& m_dCenterPointLatitude & m_dLength & m_dWidth & m_dHeading 
			& m_dDryFrictionfactor & m_dDryFrictionfactor_start & m_dDryFrictionfactor_mid 
			& m_dDryFrictionfactor_end & m_dGradient & m_dStartX & m_dStartY 
			& m_dEndX & m_dEndY & m_dHeight & m_dMegaticDiff & m_dLandingPoint 
			& m_vVacateLine & m_vInRunwayLine; 
	}

public:
	int m_iRunwayID;			/*跑道ID*/
	int m_iAirportID;		/*跑道所属机场的机场ID*/
	std::string m_szRunwayName;	/*跑道的名称*/
	double m_dCenterPointLongitude;	/*机场中心点经度(单位：弧度)*/
	double m_dCenterPointLatitude;	/*机场中心点纬度(单位：弧度)*/
	double m_dLength;			/*跑道长度(单位：米) not null default 0*/
	double m_dWidth;			/*宽度(单位：米) not null default 0*/
	double m_dHeading;		/*跑道朝向(单位：弧度) not null default 0 */
	double m_dDryFrictionfactor;	/*干跑道摩擦系数（取值范围0~1） not null default 0 */
	double m_dDryFrictionfactor_start;	/*干跑道起始段摩擦系数（取值范围0~1） not null default 0 */
	double m_dDryFrictionfactor_mid;		/*干跑道中间段摩擦系数（取值范围0~1） not null default 0 */
	double m_dDryFrictionfactor_end;		/*干跑道末尾段摩擦系数（取值范围0~1） not null default 0 */
	double m_dGradient;		/*坡度(单位：弧度) not null default 0 */

	double m_dStartX;			/*跑道起始点x坐标*/
	double m_dStartY;			/*跑道起始点y坐标*/
	double m_dEndX;			/*跑道终点x坐标*/
	double m_dEndY;			/*跑道终点y坐标*/
	double m_dHeight;			/*跑道海拔高度*/
	double m_dMegaticDiff;			/* 磁差角（单位：弧度）*/
	double m_dLandingPoint;   /*跑道降落点（即实际的跑道入口点，针对跑道入口点内移的情况，比如澳门机场的情况）*/
	std::vector<boost::shared_ptr<VacateLineData> > m_vVacateLine;  //跑道的脱离道
	std::vector<boost::shared_ptr<InRunwayLineData> > m_vInRunwayLine; //跑道的进入道
};


/*-----------------塔台--------------*/
class Tower: public DataObj
{
public:
	Tower(void);
	~Tower(void);
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	void SetTowerID(int iTowerID);
	void SetAirportID(int iAirportID);
	void SetIconID(int iIconID);
	void SetTowerName(std::string strTowerName);
	void SetLongitude(double dLongitude);
	void SetLatitude(double dLatitude);
	void SetHeight(double dHeight);
	void SetHeading(double dHeading);
	void SetPitch(double dPitch);
	void SetRoll(double dRoll);

	int GetTowerID();
	int GetAirportID();
	int GetIconID();
	std::string GetTowerName();
	double GetLongitude();
	double GetLatitude();
	double GetHeight();
	double GetHeading();
	double GetPitch();
	double GetRoll();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTowerID & m_iAirportID & m_iIconID & m_strTowerName 
			& m_dLongitude & m_dLatitude & m_dHeight & m_dHeading 
			& m_dPitch & m_dRoll; 
	}

public:
	int m_iTowerID;			/*塔台ID*/
	int m_iAirportID;		/*塔台所在机场的机场ID*/
	int m_iIconID;		/*塔台显示图标*/
	std::string m_strTowerName;	/*塔台名称not null unique*/
	double m_dLongitude;		/*塔台的经度（单位：弧度）not null default 0*/
	double m_dLatitude;		/*塔台的纬度（单位：弧度）not null default 0*/
	double m_dHeight;			/*塔台高度（单位：米）not null default 0*/
	double m_dHeading;		/*视点朝向（单位：弧度）not null default 0*/
	double m_dPitch;			/*视点俯视角度（单位：弧度）not null default 0*/
	double m_dRoll;			/*视点翻转角度（单位：弧度）not null default 0*/
};



/*---------机场模型-----------------*/
class AirportModel : public DataObj
{
public:
	AirportModel(void);
	~AirportModel(void);
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	void SetModelID(int iModelID);
	void SetAirportID(int iAirportID);
	void SetModelName(std::string strModelName);
	void SetModelFile(std::string strModelFile);

	int GetModelID();
	int GetAirportID();
	std::string GetModelName();
	std::string GetModelFile();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iModelID & m_iAirportID & m_strModelName & m_strModelFile; 
	}

public:
	int m_iModelID;					/*机场模型ID*/
	int m_iAirportID;					/*模型所属机场的机场ID*/
	std::string m_strModelName;		/*模型名称（包括四个季节以及雨、雪、夜晚）not null unique*/
	std::string m_strModelFile;		/*模型对应的文件名not null*/
};


/*----------------离场程序-----------------*/
class Sid : public DataObj
{
public:
	Sid();
	~Sid();

	//
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Sid(const Sid &sid);
	Sid& operator=(const Sid& sid);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSidId & m_strSidName & m_iAirportID 
			& m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iSidId;		              /* 离场程序ID */
	std::string m_strSidName;	      /* 离场程序名称*/
	int m_iAirportID;		          /* 机场ID */
	int m_iRunwayID;	              /* 跑道ID */
	std::vector<RoutePt> m_vecRoutePt;     /* 离场程序包括的航路点 */
};

/*----------------进场程序-----------------*/
class Star : public DataObj
{
public:
	Star();
	~Star();

	//
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Star(const Star &star);
	Star& operator=(const Star& star);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStarId & m_strStarName & m_iAirportID 
			& m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iStarId;		              /* 进场程序ID */
	std::string m_strStarName;	      /* 进场程序名称*/
	int m_iAirportID;		          /* 机场ID */
	int m_iRunwayID;	              /* 跑道ID */
	std::vector<RoutePt> m_vecRoutePt;     /* 进场程序包括的航路点 */
};


/*!
\brief:  宏类
\details: 宏的信息 
\author:JZH
\date:2013/5/7
*/
class Macro : public DataObj
{
public:
	Macro();
	~Macro();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMacroID & m_iMacroGroupID & m_szMacroName 
			& m_szCmd & m_szRemark;
	}

public:	
	int m_iMacroID;				/*宏ID*/
	int m_iMacroGroupID;		/*所属宏组ID*/
	std::string m_szMacroName;	/*宏的名称：机长输入的宏命令名not null unique*/
	std::string m_szCmd;		/*宏命令定义*/
	std::string m_szRemark;		/*描述性语言*/
};

/*!
\brief:  宏组类
\details: 宏组的信息 
\author:JZH
\date:2013/5/7
*/
class MacroGroup : public DataObj
{
public:
	MacroGroup();
	~MacroGroup();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMacroGroupID & m_iAirportID & m_szMacroGroupName 
			& m_szRemark;
	}

public:
	int m_iMacroGroupID;                 //宏组ID
	int m_iAirportID;					 //所属机场ID
	std::string m_szMacroGroupName;		 //宏组名称
	std::string m_szRemark;				 //描述性语言
};

enum STDAPCH_TURN_TYPE
{
	STT_LT = 0,	//左修正角
	STT_LR,		//左直角
	STT_RT,		//右修正角
	STT_RR		//右直角

};

enum HOLD_TURN_TYPE
{
	HTT_LT = 0,	//左转弯
	HTT_RT		//右转弯
};

enum AIRCRAFT_TYPE
{
	AT_A = 0,
	AT_B,
	AT_CD
};
/*!
\brief:  进近程序类
\details: 进近程序的信息 
\author:ZJ
\date:2013/5/22
*/
class Stdapch : public DataObj
{
public:
	Stdapch();
	~Stdapch();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStdapchID & m_iAirportID & m_iBeaconID & m_szStdapchName 
			& m_iRunwayID & m_dInBoundHeading & m_iHighLevel 
			& m_iLowLevel & m_iOutBoundLegTime & m_eTurnType & m_eAircraftType;
	}

public:
	int m_iStdapchID;		/* 进近程序ID,主键码*/
	int m_iAirportID;		/*机场ID not null default 0*/
	int m_iBeaconID;		/*导航台id*/
	std::string m_szStdapchName;	/* 进近程序名称varchar(50) */
	int m_iRunwayID;		/*着陆跑道id*/
	double m_dInBoundHeading;	/* 出航（OUTBOUND）航向float(8) default 0 */
	int m_iHighLevel;		/* 飞机第一次过台高度(单位：米)int default 0 */
	int m_iLowLevel;		/* 飞机第二次过台高度(单位：米)int default 0 */
	int m_iOutBoundLegTime;/* 飞机直航段飞行时间（单位：秒）int default 0 */
	STDAPCH_TURN_TYPE m_eTurnType;
	AIRCRAFT_TYPE m_eAircraftType;
};


/*!
\brief  等待程序类
\details  等待程序的信息
\author JZH
\date 2013/5/21
*/
class Hold : public DataObj
{
public:
	Hold();
	~Hold();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iHoldID & m_szHoldName & m_iAirportID & m_iBeaconID & m_eTurnType & m_iAltitudeLevel1
			& m_iAltitudeLevel2 & m_dHeading & m_iHoldIasAL & m_iHoldIasAM & m_iHoldIasAH & m_iHoldIasBL
			& m_iHoldIasBM & m_iHoldIasBH & m_iHoldIasCDL & m_iHoldIasCDM & m_iHoldIasCDH & m_iOutBoundLegTimeA
			& m_iOutBoundLegTimeB & m_iOutBoundLegTimeCD;
	}

public:

	int m_iHoldID;			/*id 主键码 */
	std::string m_szHoldName;		/*等待程序名称*/
	int m_iAirportID;		/*机场ID not null default 0*/
	int m_iBeaconID;			/*导航台ID not null default 0*/
	HOLD_TURN_TYPE m_eTurnType;		/*转弯类型 'left' 'right' not null */
	int m_iAltitudeLevel1;	/*第一高度层分割点(单位：米)*  not null default 0*/
	int m_iAltitudeLevel2;	/*第二高度层分割点(单位：米)  not null default 0*/
	double m_dHeading;		/*航向(单位：度)  not null default 0*/
	int m_iHoldIasAL;		/*A型飞机在低高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasAM;		/*A型飞机在中高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasAH;		/*A型飞机在高高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasBL;		/*B型飞机在低高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasBM;		/*B型飞机在中高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasBH;		/*B型飞机在高高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasCDL;		/*CD型飞机在低高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasCDM;		/*CD型飞机在中高度层的ias(单位：米)  not null default 0*/
	int m_iHoldIasCDH;		/*CD型飞机在高高度层的ias(单位：米)  not null default 0*/
	int m_iOutBoundLegTimeA;	/*A型飞机飞出时间(单位：秒)  not null default 0*/
	int m_iOutBoundLegTimeB;	/*B型飞机飞出时间(单位：秒)  not null default 0*/
	int m_iOutBoundLegTimeCD;	/*CD型飞机飞出时间(单位：秒)  not null default 0*/  

};


/*!
\brief  复飞程序类
\details  复飞程序的信息
\author JZH
\date 2013/5/23
*/
class Miss : public DataObj
{
public:
	Miss();
	~Miss();

	//
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//拷贝、赋值函数
	Miss(const Miss &miss);
	Miss& operator=(const Miss& miss);

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMissID & m_iAirportID & m_szMissName 
			& m_iBeaconAltitude & m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iMissID;			/* 复飞程序ID,主键码*/
	int m_iAirportID;		/*机场ID not null default 0*/	
	std::string m_szMissName;		/* 复飞程序名称varchar(50) */
	int m_iBeaconAltitude;	/* 飞机过点高度int default 0 */
	int m_iRunwayID;		/*跑道ID */
	std::vector<RoutePt> m_vecRoutePt;     /* 复飞程序包括的航路点 */
};

//灯的类型
enum ENUM_LIGHT_TYPE
{
	ELT_NOMAL	= 0,		//!<普通的灯
	ELT_GLIMMER,			//!<障碍灯

};

  /*! 
\brief     灯光组信息
\details   视景使用的灯光组信息
\author    JZH
\date      2013-06-04
*/
class LightGroup : public DataObj
{
public:
	LightGroup();
	~LightGroup();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightGroupID & m_strLightGroupName & m_strLightGroupNodeName 
			& m_iAirportID & m_enumType & m_iLightCollectionID & m_iGlimmerRate & m_iGlimmerTime;
	}
public:
	int m_iLightGroupID;				//!<灯光组ID
	std::string m_strLightGroupName;	//!<灯光组名称
	std::string m_strLightGroupNodeName;//!<灯光组模型的节点名称
	int m_iAirportID;					//!<机场ID
	ENUM_LIGHT_TYPE m_enumType;			//!<灯光类型，0 = 普通的灯，1 = 障碍灯（可以闪烁的灯）
	int m_iLightCollectionID;		//!<灯光组所属灯光组组合ID
	int m_iGlimmerRate;		//!<障碍灯的闪烁频率，如果是障碍灯此字段有效
	int m_iGlimmerTime;		//!<障碍灯亮起时的时长
};

  /*!
\brief     灯
\details   对应物理上的一个灯
\author    JZH
\date      2013-06-25
*/
class Light : public DataObj
{
public:
	Light();
	~Light();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightID & m_iLightGroupID & m_iAirportID 
			& m_iSequence & m_dX & m_dY & m_dZ & m_dRed & m_dGreen & m_dBlue
			& m_dHeading & m_dUpPitch & m_dDownPitch;
	}
public:
	int m_iLightID;			//!<灯的ID
	int m_iLightGroupID; //所属灯光组ID
	int m_iAirportID;		//!<机场ID
	int m_iSequence;		//灯的点序
	double m_dX;		//!<灯的X坐标
	double m_dY;		//!<灯的Y坐标
	double m_dZ;		//!<灯的Z坐标
	double m_dRed;		//!<灯光颜色Red值，为0到1,表示红色的颜色深度百分比
	double m_dGreen;		//!<灯光颜色Green值，为0到1,表示绿色的颜色深度百分比
	double m_dBlue;		//!<灯光颜色Blue值，为0到1,表示绿色的颜色深度百分比
	double m_dHeading;	//!<水平方向可以看见灯光的角度
	double m_dUpPitch;	//!<垂直方向可以看见灯光的上角度
	double m_dDownPitch;	//!<垂直方向可以看见灯光的下角度
};

/*!
\brief     灯光组组合
\details   N个灯光组的组合，便于控制更多灯的开关、亮度设置等操作。
\author    JZH
\date      2013-06-25
*/
class LightCollection : public DataObj
{
public:
	LightCollection();
	~LightCollection();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightCollectionID & m_iAirportID & m_szLightCollectionName 
			& m_vLightGroups;
	}
public:
	int m_iLightCollectionID;		//!<灯光组组合编号
	int m_iAirportID;			//!<机场ID
	std::string m_szLightCollectionName;	//!<灯光组组合名称
	std::vector<boost::shared_ptr<LightGroup>> m_vLightGroups;	//!</灯光组组合中的灯光组
};

/*!
\brief  灯光组与其对应的灯
\details  
\author JZH
\date 2013/6/26
*/
class LightGroupDetail  : public DataObj
{
public:
	LightGroupDetail();
	~LightGroupDetail();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightGroupID & m_vLights;
	}
public:
	int m_iLightGroupID;		//!<灯光组ID
	std::vector<boost::shared_ptr<Light>> m_vLights;	//!<构成灯光组的灯
};

#endif