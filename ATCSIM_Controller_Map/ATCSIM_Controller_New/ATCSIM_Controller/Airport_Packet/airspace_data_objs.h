//���ļ��ж��������صĶ����࣬�������¶���
//����̨ Beacon
//����   Sector
//��·   Course
//��·�ϵĵ���̨   CourseBeacon

#ifndef _H_AIRSPACE_DATA_OBJS_H
#define _H_AIRSPACE_DATA_OBJS_H
#include <string>
#include "DataObj.h"
#include "assistance_data_objs.h"
#include <boost/boost/shared_ptr.hpp>
#include <boost/boost/make_shared.hpp>


/*---------------����̨-------------*/
class Beacon : public DataObj
{
public:
	Beacon(void);
	~Beacon(void);

	int GetId();
	std::string GetDisplayLabel();

	//Set����
	void SetBeaconID(int iBeaconID);
	void SetBeaconCode(std::string strCode);
	void SetBeaconName(std::string strBeaconName);
	void SetLongitude(double dLongitude);
	void SetLatitude(double dLatitude);
	void SetHeight(double dHeight);
	void SetType(int iType);
	void SetIconID(int iIconID);
	void SetIsStdReport(bool bIsStdReport);

	//Get����
	int GetBeaconID();
	std::string GetBeaconCode();
	std::string GetBeaconName();
	double GetLongitude();
	double GetLatitude();
	double GetHeight();
	int GetType();
	int GetIconID();
	bool GetIsStdReport();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iBeaconID & m_strBeaconCode & m_strBeaconName & m_dLongitude & m_dLatitude & m_dHeight & m_iType & m_iIconID & m_bIsStdReport;
	}

private:
	int m_iBeaconID;			/*����̨ID*/
	std::string m_strBeaconCode;
	std::string m_strBeaconName;	/*����̨����������*/
	double m_dLongitude;                 /*����̨����*/
	double m_dLatitude;                 /*����̨γ��*/
	double m_dHeight;             /*  ����̨�߶ȣ��ף�*/
	int m_iType;				/*���� 0x0 = �����ͣ���������е�һ���� �����������һ���㣬0x1 = NDB�޷����ű�̨��0x2 = DME���̨��0x4 = VORȫ���ű�̨ */
	int m_iIconID;			/*��ʶ,��ͼ����ʾ������ͼ��,����ICON�� null*/
	bool m_bIsStdReport;		/*�Ƿ�Ϊ��׼�����(0 = ��1 = ��)not null default 0*/

};


/*!
\brief  ���Ӵ��������ͣ��״����ͣ�
\details  
\author DXQ
\date 2013/6/19
*/
enum ENUM_SURVEILLANCE_SENSOR_TYPE
{
	SENSOR_NULL = 0x00,		//��Ч������
	SENSOR_PSR = 0x01,		//һ���״�
	SENSOR_SSR = 0x02,		//�����״�
	SENSOR_ADSB = 0x04,		//ADS-B
};


/*!
\brief  ���Ӵ��������״
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


	//��������ֵ����
	SurveillanceSensor(const SurveillanceSensor &sensor);
	SurveillanceSensor& operator=(const SurveillanceSensor& sensor);


//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSensorId & m_strSensorName & m_eSensorType & m_dLongitude & m_dLatitude 
			& m_dAltitude & m_iPeriod & m_iRange & m_dElevationAngle & m_dDepressionAngle;
	}

public:
	int m_iSensorId;							//������ID
	std::string m_strSensorName;				//����������
	ENUM_SURVEILLANCE_SENSOR_TYPE m_eSensorType;//����������
	double m_dLongitude;						//����������
	double m_dLatitude;							//������γ��
	double m_dAltitude;							//�������߶�
	int m_iPeriod;								//������ɨ�����ڣ�����Ϊ��λ��
	int m_iRange;								//������ɨ�跶Χ���Թ���Ϊ��λ��
	double m_dElevationAngle;					//�״���ӭ��
	double m_dDepressionAngle;					//�״���ӭ��
};

/*--------------------����-------------------*/
class Sector : public DataObj
{
public:
	Sector(void);
	~Sector(void);

	int GetId();
	std::string GetDisplayLabel();

	//��������ֵ����
	Sector(const Sector &sector);
	Sector& operator=(const Sector& sector);


	//Set ����
	void SetSectorID(int iSectorID);
	void SetSectorName(std::string strSectorName);
	void SetSectorFrequency(double dFrequency);


	//Get����
	int GetSectorID();
	std::string GetSectorName();
	double GetSectorFrequency();


	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSectorID & m_strSectorName & m_dFrequency;
	}


private:
	int m_iSectorID;			    /*��������ID*/
	std::string m_strSectorName;	/*��������*/
	double m_dFrequency;            /*����Ƶ��*/

};

/*!
\brief  �������ֿ��е�������������
\details  
\author GQ
\date 2013/5/29
*/
enum POINT_OWNER_TYPE
{
	POT_STCA_AREA = 0,			// ��ͻ�澯��
	POT_MSAW_AREA= 1,			// �����������
	POT_RESTRICT_AREA = 2,     // ��������������Σ����
	POT_RADARROBE = 3,			//�״����ä��
	POT_QNH_AREA =4,				//QNH����, QNH(Ӣ��ȫ��: query normal height, ������ѹ)
	POT_INHIBITORY_AREA = 5	//�澯������
};

/*!
\brief  ���λ��
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
	void SetSequence(int iSeq); //Ϊ������designer��ģ��������
	int GetSequence();			   //Ϊ������designer��ģ��������
	int m_iPointPositionID;       //���ID
	std::string m_strPointPositionName; //�������
	int m_iSequence; //������
	POINT_OWNER_TYPE m_enumOwnerType; //�������� 0��ͻ�澯����1�����������2��������������Σ������3�״����ä��
	int m_iOwnerID;	//����ID
	double m_dLongtitude; //����
	double m_dLatitude;   //γ��
	double m_dHeight;     //�߶�
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iPointPositionID & m_strPointPositionName &m_iSequence &  m_enumOwnerType & m_iOwnerID & m_dLongtitude & m_dLatitude
			& m_dHeight;
	}
};

/*!
\brief  ��ͻ�澯��������
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
\brief  ��ͻ�澯��
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
	std::string	m_strStcaAreaName;  //��ͻ�澯������
	int     m_iLineStyle;  //��ʾ����ı�������
	int     m_iColor;   //��ʾ����ɫ
	double  m_dLowestAlt;//��͸߶�
	double  m_dHighestAlt;//��߸߶�
	STCA_AREA_TYPE		m_itype;//��ͻ�澯������
	double  m_dHorizontalAlarmRange;//ˮƽ�澯����
	double  m_dVerticalAlarmRange;//��ֱ�澯����
	double  m_dConverseTime;  //����ʱ��
	double  m_dSuitableTime;  //˳��ʱ��
	double  m_dCrossTime;     //����ʱ��
	double  m_dFinalSideDis;  //�л�ͬ������ɻ��ĺ���澯����
	double  m_dFinalEndDis;   //�л�ͬһ������ɻ�������澯����
	std::vector<boost::shared_ptr<PointPosition> > m_vStcaAreaPoint;//����ɵ�����
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iStcaAreaID & m_strStcaAreaName & m_iLineStyle & m_iColor & m_dLowestAlt &m_dHighestAlt & m_itype & m_dHorizontalAlarmRange
			&m_dVerticalAlarmRange & m_dConverseTime & m_dSuitableTime & m_dCrossTime & m_dFinalSideDis
			& m_dFinalEndDis & m_vStcaAreaPoint;
	}
};


/*!
\brief  ����������������ڵ͸߸澯
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

	int m_iMsawAreaID; //�����������ID
	std::string m_strMsawAreaName;  //���������������
	int     m_iLineStyle;  //��ʾ����߽������
	int    m_iColor;    //��ʾ����߽����ɫ
	double m_dHeight;//��͸߶�
	std::vector<boost::shared_ptr<PointPosition> > m_vMsawAreaPoint;//����ɵ�����

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iMsawAreaID & m_strMsawAreaName & m_iLineStyle & m_iColor  & m_dHeight  &m_vMsawAreaPoint;
	}
};




/*!
\brief  ����RestrictArea��������������������Σ�����������ø�ö�������������⼸������
\details  
\author GQ
\date 2013/5/29
*/
enum AREA_TYPE
{
	AT_RESTRICT = 0,        // ������
	AT_FORBID = 1,			// ����
	AT_DANGER = 2,          // Σ����
	AT_MILITARY,            // military area
	AT_RVSM                 // RVSM area

};

/*!
\brief  ���������ǽ�������Σ����
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
	int m_iRestrictAreaID; //������ID
	std::string m_strRestrictAreaName; //����������
	AREA_TYPE m_enumAreaType;  //�������� 0�������� 1�ǽ��� 2��Σ����
	bool m_bIsUsed; //��ѵ���У��Ƿ�ʹ��
	double  m_dLowestAlt;//��͸߶�
	double  m_dHighestAlt;//��߸߶�
	double  m_dStartTime;//����ʱ��εĿ�ʼʱ��(��λ����)
	double  m_dEndTime;//����ʱ��εĽ���ʱ��(��λ����)
	int    m_iLineStyle;
	int    m_iColor;
	std::vector<boost::shared_ptr<PointPosition> > m_vRestrictAreaPoint;//����ɵ�����
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRestrictAreaID & m_strRestrictAreaName & m_enumAreaType & m_bIsUsed  & m_dLowestAlt
			&m_dHighestAlt & m_dStartTime & m_dEndTime  & m_iLineStyle & m_iColor & m_vRestrictAreaPoint;
	}
};


/*!
\brief  QNH����
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
	int m_iQnhAreaID;						//qnh����ID
	std::string m_strQnhAreaName;	//qnh����
	bool m_bIsUsed;				//��ѵ���У��Ƿ�ʹ��
	double  m_dLowestAlt;		//��͸߶�
	double  m_dHighestAlt;		//��߸߶�
	double  m_dQnhValue;		//qnhֵ
	int    m_iLineStyle;
	int    m_iColor;
	std::vector<boost::shared_ptr<PointPosition> > m_vQnhAreaPoint; //���qnh����ĵ�
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iQnhAreaID & m_strQnhAreaName &  m_bIsUsed  & m_dLowestAlt
			& m_dHighestAlt & m_dQnhValue & m_iLineStyle & m_iColor & m_vQnhAreaPoint;
	}
};

/*!
\brief  �澯������
\details  
\author ZJ
\date 2013/7/16
*/
enum INHIBITORY_AREA_TYPE
{
	IAT_STCA_AREA_TYPE = 0,     //��ͻ�澯������
	IAT_MSAW_AREA_TYPE = 1  //�͸߸澯������
};

class InhibitoryArea : public DataObj
{
public:
	InhibitoryArea();
	~InhibitoryArea();

	//��������ֵ����
	InhibitoryArea(const InhibitoryArea &inhibitoryArea);
	InhibitoryArea& operator=(const InhibitoryArea& inhibitoryArea);

	//boost���л�
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
	double  m_dLowestAlt;//��͸߶�
	double  m_dHighestAlt;//��߸߶�
	std::vector<boost::shared_ptr<PointPosition> > m_vInhibitoryAreaPoint;//����ɵ����� 
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

	//��������ֵ����
	ATS(const ATS &ATS);
	ATS& operator=(const ATS& ATS);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iATSId & m_strATSName & m_vecRoutePt;
	}

public:
	int m_iATSId;		              /* ATSID */
	std::string m_strATSName;	      /* ATS����*/
	std::vector<RoutePt> m_vecRoutePt;     /* ATS�����ĺ�·�� */
};


/*!
\brief  �״����ä��������
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

	//��������ֵ����
	Radarrobe(const Radarrobe &radarrobe);
	Radarrobe& operator=(const Radarrobe& radarrobe);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRadarrobeId & m_iAirspaceId & m_strRadarrobeName & m_dHeight & m_vRadarrobePoint;
	}

public:
	int m_iRadarrobeId;		                /* �״�ä��ID */
	int m_iAirspaceId;						/* ��������ID */
	std::string m_strRadarrobeName;	        /* �״�ä������*/
	double m_dHeight;						/* �״����ä���߶�(��λ����)*/
	std::vector<boost::shared_ptr<PointPosition> > m_vRadarrobePoint; //����ɵ�����
};

/*!
\brief  �̶���·������
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

	//��������ֵ����
	Course(const Course &course);
	Course& operator=(const Course& course);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCourseId & m_iAirspaceId & m_strCourseName & m_bDoubleLine & m_dWidth & m_vecRoutePt;
	}

public:
	int m_iCourseId;				/* ��·ID */
	std::string m_strCourseName;	/* ��·����*/
	int m_iAirspaceId;				/*��������ID*/
	bool m_bDoubleLine;				/*��·�Ƿ���˫��*/
	double m_dWidth;				/*˫�ߺ�·���(��λ��ǧ��)*/
	std::vector<boost::shared_ptr<RoutePt> > m_vecRoutePt;   /* ��·�����ĺ�·�� */
};
#endif //_H_AIRSPACE_DATA_OBJS_H


