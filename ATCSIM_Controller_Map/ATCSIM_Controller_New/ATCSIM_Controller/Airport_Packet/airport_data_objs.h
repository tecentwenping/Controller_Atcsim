//���ļ��ж��������صĶ����࣬�������¶���
//����         AirportData
//�̶���       FixpointData
//��·�̶���   RoadFixpointData
//��·         RoadData
//ͣ��λ       GataData
//�ܵ������   InRunwayLineData
//�ܵ������   VacateLineData
//�ܵ�         RunwayData
//��̨         Tower
//ģ��         AirportModel
//�볡����     Sid
//��������     Star
//��           Macro
//����         MacroGroup
//�ȴ����� Hold


#ifndef _H_AIRPORT_DATA_OBJS_H
#define _H_AIRPORT_DATA_OBJS_H

#include <string>
#include <vector>
#include "dataObj.h"
#include "assistance_data_objs.h"
#include "./boost/boost/shared_ptr.hpp"
#include "./boost/boost/make_shared.hpp"
using namespace boost;


/*-----------------����--------------*/
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

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iAirspaceID & m_szAirportName & m_szAirportCode 
			& m_dCenterPointLongitude & m_dCenterPointLatitude & m_dElevation 
			& m_dMegaticDiff & m_iMainRunway & m_iDefaultEnvID & m_dHeading;
	}


private:
	int m_iAirportID;					/* ����ID */
	int m_iAirspaceID;				/* ���������ID */
	std::string m_szAirportName;		/* ��������(����������˵�����磺�����׶�����) */
	std::string m_szAirportCode;
	double m_dCenterPointLongitude;	/* �������ĵ㾭��(��λ������) */
	double m_dCenterPointLatitude;	/* �������ĵ�γ��(��λ������) */
	double m_dElevation;				/* ������ߣ���λ���ף� */
	double m_dMegaticDiff;			/* �Ų�ǣ���λ�����ȣ�*/
	int m_iMainRunway;				/* ���������ܵ�ID */
	int m_iDefaultEnvID;				/* ����Ĭ�ϵĻ��������� */
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

/*-----------------�̶���--------------*/
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

	//boost���л�
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
	int m_iFixpointID;		/*�̶���ID*/
	int m_iIconID	;		/*�̶���ͼ��*/
	std::string m_szFixpointName;	/*�̶�������*/
	int m_iAirportID;			/*�����Ļ���ID*/
	int m_iFixpointType;				/*�̶�������, ����
										0x1	���е��㡢
										0x2	���е����㡢
										0x4	���е��㡢
										0x8	���е����㡢
										0x10	ͣ��λ�㡢
										0x20	���е���ͣ��λ�Ľ��㡢
										0x40	���е��복�е��Ľ��㡢
										0x80	�ȴ��㡢
										0x100	�����еĵ�
										0x200	���ɹ��������ĵ㡢
										0x400	���ɱ������ĵ�
										�Լ�һ�����������õ��ʾ��Ŀ�ꡣ*/
	double m_dX;				/*�̶���ľ��ȣ���λ�����ȣ�not null default 0*/
	double m_dY;				/*�̶����γ�ȣ���λ�����ȣ�not null default 0*/
	double m_dZ;				/*�̶���߶ȣ���λ���ף�not null default 0*/
	bool m_bWaitingPoint;
};


/*-----------------��·�ϵĹ̶���--------------*/
class RoadFixpointData : public DataObj
{
public:
	RoadFixpointData(void);
	~RoadFixpointData(void);
	//�õ��̶�������
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
	int m_iRoadID;			/*��·ID*/
	int m_iSequence;			/*�̶������� not null*/
	int m_iFixpointID;			/*�̶���*/
};

/*-----------------��·--------------*/
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
	int m_iRoadID;			/*��·ID*/
	int m_iAirportID;		/*����ID*/
	std::string m_szRoadName;		/*��·����*/
	int m_iRoadType;				/*��·����
									0x1	���е���
									0x2 ������
									0x4 ͣ��λ
									not null default 1*/
	double m_dWidth;				/*��·���(��λ����) not null default 20*/
	int m_iMaxAircraft;		/*��·����ͨ���������� ���û���ID */
	std::vector<boost::shared_ptr<RoadFixpointData> > m_vRoadFixpoints;	/*���ɵ�·�ĵ�*/

};

//����·�ߵ�����
enum ENUM_FORM_ROUTE_TYPE
{
	ROUTE_FIXPOINT_TYPE = 1,	 //�̶�������
	ROUTE_ROAD_TYPE =2			 //���е�����
};

/*---------------·���ϵĹ̶�����ߵ�·----------*/
class RouteFixpointRoad : public DataObj
{
public:
	RouteFixpointRoad(void);
	~RouteFixpointRoad(void);

	//�õ��̶�������
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
	int m_iRouteID;			/*·��ID��·�ߵĹ���ԭ�򣺿�ʼ�ͽ�β�����ǵ㣬��·֮������е����ӣ����� �C ��· �C �� �C ��· �C �㣿 û���cx2013-06-02*/
	int m_iSequence;		/*���not null default 0 */
	int m_iFactorType;		/*���ɸ�·�ߵ�Ԫ���ǹ̶��㻹�ǵ�·��1 = �㣬2 = ��· not null default 1 */
	int m_iFactorID;		/*�̶�����·��ID not null default 0 */
};

/*-----------------·��--------------*/
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
	int m_iRouteID;			/*·��ID*/
	int m_iAirportID;		/*����ID*/
	std::string m_szRouteName;		/*·������*/
	int m_iType;				/*·���ʺϸ�ʲô����ʹ�ã�1�ɻ���2���� */
	double m_dLength;	/*·�ߵĳ��ȣ���λ��ǧ�ף�not null default 0 */
	double m_dWidth;	/*·�ߵĿ��*/
	double m_dWaitX;		/*�ȴ���X����*/
	double m_dWaitY;		/*�ȴ���Y����*/
	
	std::vector<boost::shared_ptr<RouteFixpointRoad> > m_vRouteFixpointRoad;	/*����·�ߵĹ̶�����ߵ�·*/

};

/*-----------------ͣ��λ--------------*/
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


//boost���л�
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
	int m_iGateID;			/*ͣ��λID*/	
	int m_iAirportID;		/*����ID*/
	std::string m_szGateDataName;		/*ͣ��λ����not null*/
	int m_iRoadID;			/*���road ��road_id ��Ӧ����·��ID��ͣ��λ�Ĺ����ڵ�·�С�not null default 1*/
	int m_iInGateDataFixpointID;	/*����ͣ��λ�Ĺ̶���ID not null default 0 */
	int m_iGateFixpointID;		/*ͣ��λ�Ĺ̶���ID not null default 0 */
	double m_dLength;			/*ͣ��λ�ĳ��ȣ���λ��ǧ�ף�not null default 0 */
	int m_iMaxAircraftID;		/*ͣ��λ����ͣ���������� ���û���ID */
	int m_iInternationalType;	/*�������ͣ�1���ڣ�2���ʣ�3�����ڹ���not null default 1  */
	int m_iBelongedCompanyID;			/*ͣ��λ�����ĸ����չ�˾��0��ʾ�������κκ��չ�˾not null default 0 */
	int m_iStartPosition;		/*�Ƴ�����λ�ã����ݲ�ͬ�ܵ��в�ͬ���Ƴ�����λ�ã���֪��Ӧ�����ó�ĳһ�̶��㻹��ʲônot null default 1 */
	bool m_bIsDirectTax;		/*�Ƿ�����ֱ�ӻ��� false��������true������ not null default false */
	int m_iRoutineInLine;		/*�����ͣ��λ·�ߣ�ֻ������һ��,��������ö��������Ը�Ϊ�ַ����ֶΣ����á�XXX,XX,XXXX���ķ�ʽ���棩��
								���ۺ������ӵغ��Զ����룬��ָ�����������ƺ�󵽸û�ͣ��λ����Ļ���·�� not null default 0 */
	int m_iRoutineOutLine;	/*�����ͣ��λ·�ߣ��ӹ涨��λ�û�����ָ����������ڣ��Լ��Ӹ���������ܵ�ͷ�ĳ��滬��·�� not null default 0 */
	int m_iRoutineToRunway;	/*�������ܵ�·��not null default 0  */

};


/*-----------------�ܵ������--------------*/
class InRunwayLineData : public DataObj
{
public:
	InRunwayLineData(void);
	~InRunwayLineData(void);

	//��������ֵ����
	InRunwayLineData(const InRunwayLineData& inRunwayLine);
	InRunwayLineData& operator=(const InRunwayLineData& inRunwayLine);


	int GetId();
	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<InRunwayLineData> spInRunwayLineData);

	//Set����
	void SetInRunwayLineID(int iID);
	void SetInRunwayLineName(std::string szName);
	void SetRunwayID(int iRunwayID);
	void SetAirportID(int iAirportID);
	void SetSequence(int iSequence);
	void SetRoadID(int iRoadID);
	void SetInPointID(int iInPointID);
	void SetStartPointID(int iStartPointID);
	void SetWaitingPointID(int iWaitingPointID);

	//Get����
	int GetInRunwayLineID();
	std::string GetInRunwayLineName();
	int GetRunwayID();
	int GetAirportID();
	int GetSequence();
	int GetRoadID();
	int GetInPointID();
	int GetStartPointID();
	int GetWaitingPointID();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();


//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iInRunwayLineID & m_iRunwayID & m_iAirportID & m_szInRunwayLineName & m_iSequence 
			& m_iRoadID & m_iInPointID & m_iStartPointID & m_iWaitingPointID; 
	}

public:
	int m_iInRunwayLineID;     /* �����ID ������ĵ�·IDһ��*/
	int m_iRunwayID;			/* �ܵ�ID */
	int m_iAirportID;           /* ����ID*/
	std::string m_szInRunwayLineName; /* ������� */
	int m_iSequence;			/*��������*/
	int m_iRoadID;			    /* ��·ID */
	int m_iInPointID;			/* �����ID */
	int m_iStartPointID;		/* ��ʼ��ID */
	int m_iWaitingPointID;	    /* �ȴ���ID */
};

/*-----------------�ܵ������--------------*/
class VacateLineData :public DataObj
{
public:
	VacateLineData(void);
	~VacateLineData(void);

	//��������ֵ����
	VacateLineData(const VacateLineData& vacateline);
	VacateLineData& operator=(const VacateLineData& vacateline);

	int GetId();
	std::string GetDisplayLabel();

	//Set����
	void SetVacateLineID(int iVacateLineID);
	void SetAirportID(int iAirportID);
	void SetVacateLineName(std::string szName);
	void SetSequence(int iSequence);
	void SetRunwayID(int iRunwayID);
	void SetRoadID(int iRoadID);
	void SetStartPointID(int iStartPointID);
	void SetWaitingPointID(int iWaitingPointID);


	//Get����
	int GetVacateLineID();
	int GetAirportID();
	std::string GetVacateLineName();
	int GetSequence();
	int GetRunwayID();
	int GetRoadID();
	int GetStartPointID();
	int GetWaitingPointID();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iVacateLineID & m_iAirportID & m_szVacateLineName & m_iSequence 
			& m_iRunwayID & m_iRoadID & m_iStartPointID & m_iWaitingPointID; 
	}

public:
	int m_iVacateLineID;       /*�����ID*/
	int m_iAirportID;        /*  ����ID*/
	std::string m_szVacateLineName; /*���������*/
	int m_iSequence;			/*��������*/
	int m_iRunwayID;			/* �ܵ�ID */
	int m_iRoadID;			    /* ��·ID */
	int m_iStartPointID;		/* ��ʼ��ID */
	int m_iWaitingPointID;	    /* �ȴ���ID */
};

/*-----------------�ܵ�--------------*/
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

	//Set����
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

	//Get����

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

//boost���л�
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
	int m_iRunwayID;			/*�ܵ�ID*/
	int m_iAirportID;		/*�ܵ����������Ļ���ID*/
	std::string m_szRunwayName;	/*�ܵ�������*/
	double m_dCenterPointLongitude;	/*�������ĵ㾭��(��λ������)*/
	double m_dCenterPointLatitude;	/*�������ĵ�γ��(��λ������)*/
	double m_dLength;			/*�ܵ�����(��λ����) not null default 0*/
	double m_dWidth;			/*���(��λ����) not null default 0*/
	double m_dHeading;		/*�ܵ�����(��λ������) not null default 0 */
	double m_dDryFrictionfactor;	/*���ܵ�Ħ��ϵ����ȡֵ��Χ0~1�� not null default 0 */
	double m_dDryFrictionfactor_start;	/*���ܵ���ʼ��Ħ��ϵ����ȡֵ��Χ0~1�� not null default 0 */
	double m_dDryFrictionfactor_mid;		/*���ܵ��м��Ħ��ϵ����ȡֵ��Χ0~1�� not null default 0 */
	double m_dDryFrictionfactor_end;		/*���ܵ�ĩβ��Ħ��ϵ����ȡֵ��Χ0~1�� not null default 0 */
	double m_dGradient;		/*�¶�(��λ������) not null default 0 */

	double m_dStartX;			/*�ܵ���ʼ��x����*/
	double m_dStartY;			/*�ܵ���ʼ��y����*/
	double m_dEndX;			/*�ܵ��յ�x����*/
	double m_dEndY;			/*�ܵ��յ�y����*/
	double m_dHeight;			/*�ܵ����θ߶�*/
	double m_dMegaticDiff;			/* �Ų�ǣ���λ�����ȣ�*/
	double m_dLandingPoint;   /*�ܵ�����㣨��ʵ�ʵ��ܵ���ڵ㣬����ܵ���ڵ����Ƶ������������Ż����������*/
	std::vector<boost::shared_ptr<VacateLineData> > m_vVacateLine;  //�ܵ��������
	std::vector<boost::shared_ptr<InRunwayLineData> > m_vInRunwayLine; //�ܵ��Ľ����
};


/*-----------------��̨--------------*/
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

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTowerID & m_iAirportID & m_iIconID & m_strTowerName 
			& m_dLongitude & m_dLatitude & m_dHeight & m_dHeading 
			& m_dPitch & m_dRoll; 
	}

public:
	int m_iTowerID;			/*��̨ID*/
	int m_iAirportID;		/*��̨���ڻ����Ļ���ID*/
	int m_iIconID;		/*��̨��ʾͼ��*/
	std::string m_strTowerName;	/*��̨����not null unique*/
	double m_dLongitude;		/*��̨�ľ��ȣ���λ�����ȣ�not null default 0*/
	double m_dLatitude;		/*��̨��γ�ȣ���λ�����ȣ�not null default 0*/
	double m_dHeight;			/*��̨�߶ȣ���λ���ף�not null default 0*/
	double m_dHeading;		/*�ӵ㳯�򣨵�λ�����ȣ�not null default 0*/
	double m_dPitch;			/*�ӵ㸩�ӽǶȣ���λ�����ȣ�not null default 0*/
	double m_dRoll;			/*�ӵ㷭ת�Ƕȣ���λ�����ȣ�not null default 0*/
};



/*---------����ģ��-----------------*/
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

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iModelID & m_iAirportID & m_strModelName & m_strModelFile; 
	}

public:
	int m_iModelID;					/*����ģ��ID*/
	int m_iAirportID;					/*ģ�����������Ļ���ID*/
	std::string m_strModelName;		/*ģ�����ƣ������ĸ������Լ��ꡢѩ��ҹ��not null unique*/
	std::string m_strModelFile;		/*ģ�Ͷ�Ӧ���ļ���not null*/
};


/*----------------�볡����-----------------*/
class Sid : public DataObj
{
public:
	Sid();
	~Sid();

	//
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//��������ֵ����
	Sid(const Sid &sid);
	Sid& operator=(const Sid& sid);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSidId & m_strSidName & m_iAirportID 
			& m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iSidId;		              /* �볡����ID */
	std::string m_strSidName;	      /* �볡��������*/
	int m_iAirportID;		          /* ����ID */
	int m_iRunwayID;	              /* �ܵ�ID */
	std::vector<RoutePt> m_vecRoutePt;     /* �볡��������ĺ�·�� */
};

/*----------------��������-----------------*/
class Star : public DataObj
{
public:
	Star();
	~Star();

	//
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	//��������ֵ����
	Star(const Star &star);
	Star& operator=(const Star& star);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStarId & m_strStarName & m_iAirportID 
			& m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iStarId;		              /* ��������ID */
	std::string m_strStarName;	      /* ������������*/
	int m_iAirportID;		          /* ����ID */
	int m_iRunwayID;	              /* �ܵ�ID */
	std::vector<RoutePt> m_vecRoutePt;     /* ������������ĺ�·�� */
};


/*!
\brief:  ����
\details: �����Ϣ 
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

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMacroID & m_iMacroGroupID & m_szMacroName 
			& m_szCmd & m_szRemark;
	}

public:	
	int m_iMacroID;				/*��ID*/
	int m_iMacroGroupID;		/*��������ID*/
	std::string m_szMacroName;	/*������ƣ���������ĺ�������not null unique*/
	std::string m_szCmd;		/*�������*/
	std::string m_szRemark;		/*����������*/
};

/*!
\brief:  ������
\details: �������Ϣ 
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

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMacroGroupID & m_iAirportID & m_szMacroGroupName 
			& m_szRemark;
	}

public:
	int m_iMacroGroupID;                 //����ID
	int m_iAirportID;					 //��������ID
	std::string m_szMacroGroupName;		 //��������
	std::string m_szRemark;				 //����������
};

enum STDAPCH_TURN_TYPE
{
	STT_LT = 0,	//��������
	STT_LR,		//��ֱ��
	STT_RT,		//��������
	STT_RR		//��ֱ��

};

enum HOLD_TURN_TYPE
{
	HTT_LT = 0,	//��ת��
	HTT_RT		//��ת��
};

enum AIRCRAFT_TYPE
{
	AT_A = 0,
	AT_B,
	AT_CD
};
/*!
\brief:  ����������
\details: �����������Ϣ 
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

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStdapchID & m_iAirportID & m_iBeaconID & m_szStdapchName 
			& m_iRunwayID & m_dInBoundHeading & m_iHighLevel 
			& m_iLowLevel & m_iOutBoundLegTime & m_eTurnType & m_eAircraftType;
	}

public:
	int m_iStdapchID;		/* ��������ID,������*/
	int m_iAirportID;		/*����ID not null default 0*/
	int m_iBeaconID;		/*����̨id*/
	std::string m_szStdapchName;	/* ������������varchar(50) */
	int m_iRunwayID;		/*��½�ܵ�id*/
	double m_dInBoundHeading;	/* ������OUTBOUND������float(8) default 0 */
	int m_iHighLevel;		/* �ɻ���һ�ι�̨�߶�(��λ����)int default 0 */
	int m_iLowLevel;		/* �ɻ��ڶ��ι�̨�߶�(��λ����)int default 0 */
	int m_iOutBoundLegTime;/* �ɻ�ֱ���η���ʱ�䣨��λ���룩int default 0 */
	STDAPCH_TURN_TYPE m_eTurnType;
	AIRCRAFT_TYPE m_eAircraftType;
};


/*!
\brief  �ȴ�������
\details  �ȴ��������Ϣ
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

	//boost���л�
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

	int m_iHoldID;			/*id ������ */
	std::string m_szHoldName;		/*�ȴ���������*/
	int m_iAirportID;		/*����ID not null default 0*/
	int m_iBeaconID;			/*����̨ID not null default 0*/
	HOLD_TURN_TYPE m_eTurnType;		/*ת������ 'left' 'right' not null */
	int m_iAltitudeLevel1;	/*��һ�߶Ȳ�ָ��(��λ����)*  not null default 0*/
	int m_iAltitudeLevel2;	/*�ڶ��߶Ȳ�ָ��(��λ����)  not null default 0*/
	double m_dHeading;		/*����(��λ����)  not null default 0*/
	int m_iHoldIasAL;		/*A�ͷɻ��ڵ͸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasAM;		/*A�ͷɻ����и߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasAH;		/*A�ͷɻ��ڸ߸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasBL;		/*B�ͷɻ��ڵ͸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasBM;		/*B�ͷɻ����и߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasBH;		/*B�ͷɻ��ڸ߸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasCDL;		/*CD�ͷɻ��ڵ͸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasCDM;		/*CD�ͷɻ����и߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iHoldIasCDH;		/*CD�ͷɻ��ڸ߸߶Ȳ��ias(��λ����)  not null default 0*/
	int m_iOutBoundLegTimeA;	/*A�ͷɻ��ɳ�ʱ��(��λ����)  not null default 0*/
	int m_iOutBoundLegTimeB;	/*B�ͷɻ��ɳ�ʱ��(��λ����)  not null default 0*/
	int m_iOutBoundLegTimeCD;	/*CD�ͷɻ��ɳ�ʱ��(��λ����)  not null default 0*/  

};


/*!
\brief  ���ɳ�����
\details  ���ɳ������Ϣ
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

	//��������ֵ����
	Miss(const Miss &miss);
	Miss& operator=(const Miss& miss);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMissID & m_iAirportID & m_szMissName 
			& m_iBeaconAltitude & m_iRunwayID & m_vecRoutePt;
	}

public:
	int m_iMissID;			/* ���ɳ���ID,������*/
	int m_iAirportID;		/*����ID not null default 0*/	
	std::string m_szMissName;		/* ���ɳ�������varchar(50) */
	int m_iBeaconAltitude;	/* �ɻ�����߶�int default 0 */
	int m_iRunwayID;		/*�ܵ�ID */
	std::vector<RoutePt> m_vecRoutePt;     /* ���ɳ�������ĺ�·�� */
};

//�Ƶ�����
enum ENUM_LIGHT_TYPE
{
	ELT_NOMAL	= 0,		//!<��ͨ�ĵ�
	ELT_GLIMMER,			//!<�ϰ���

};

  /*! 
\brief     �ƹ�����Ϣ
\details   �Ӿ�ʹ�õĵƹ�����Ϣ
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
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightGroupID & m_strLightGroupName & m_strLightGroupNodeName 
			& m_iAirportID & m_enumType & m_iLightCollectionID & m_iGlimmerRate & m_iGlimmerTime;
	}
public:
	int m_iLightGroupID;				//!<�ƹ���ID
	std::string m_strLightGroupName;	//!<�ƹ�������
	std::string m_strLightGroupNodeName;//!<�ƹ���ģ�͵Ľڵ�����
	int m_iAirportID;					//!<����ID
	ENUM_LIGHT_TYPE m_enumType;			//!<�ƹ����ͣ�0 = ��ͨ�ĵƣ�1 = �ϰ��ƣ�������˸�ĵƣ�
	int m_iLightCollectionID;		//!<�ƹ��������ƹ������ID
	int m_iGlimmerRate;		//!<�ϰ��Ƶ���˸Ƶ�ʣ�������ϰ��ƴ��ֶ���Ч
	int m_iGlimmerTime;		//!<�ϰ�������ʱ��ʱ��
};

  /*!
\brief     ��
\details   ��Ӧ�����ϵ�һ����
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
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightID & m_iLightGroupID & m_iAirportID 
			& m_iSequence & m_dX & m_dY & m_dZ & m_dRed & m_dGreen & m_dBlue
			& m_dHeading & m_dUpPitch & m_dDownPitch;
	}
public:
	int m_iLightID;			//!<�Ƶ�ID
	int m_iLightGroupID; //�����ƹ���ID
	int m_iAirportID;		//!<����ID
	int m_iSequence;		//�Ƶĵ���
	double m_dX;		//!<�Ƶ�X����
	double m_dY;		//!<�Ƶ�Y����
	double m_dZ;		//!<�Ƶ�Z����
	double m_dRed;		//!<�ƹ���ɫRedֵ��Ϊ0��1,��ʾ��ɫ����ɫ��Ȱٷֱ�
	double m_dGreen;		//!<�ƹ���ɫGreenֵ��Ϊ0��1,��ʾ��ɫ����ɫ��Ȱٷֱ�
	double m_dBlue;		//!<�ƹ���ɫBlueֵ��Ϊ0��1,��ʾ��ɫ����ɫ��Ȱٷֱ�
	double m_dHeading;	//!<ˮƽ������Կ����ƹ�ĽǶ�
	double m_dUpPitch;	//!<��ֱ������Կ����ƹ���ϽǶ�
	double m_dDownPitch;	//!<��ֱ������Կ����ƹ���½Ƕ�
};

/*!
\brief     �ƹ������
\details   N���ƹ������ϣ����ڿ��Ƹ���ƵĿ��ء��������õȲ�����
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
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightCollectionID & m_iAirportID & m_szLightCollectionName 
			& m_vLightGroups;
	}
public:
	int m_iLightCollectionID;		//!<�ƹ�����ϱ��
	int m_iAirportID;			//!<����ID
	std::string m_szLightCollectionName;	//!<�ƹ����������
	std::vector<boost::shared_ptr<LightGroup>> m_vLightGroups;	//!</�ƹ�������еĵƹ���
};

/*!
\brief  �ƹ��������Ӧ�ĵ�
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
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightGroupID & m_vLights;
	}
public:
	int m_iLightGroupID;		//!<�ƹ���ID
	std::vector<boost::shared_ptr<Light>> m_vLights;	//!<���ɵƹ���ĵ�
};

#endif