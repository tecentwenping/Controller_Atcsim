//���ļ��ж���ѵ���ƻ���صĶ����࣬�������¶���
//ѵ���ƻ�                TrainPlan
//ѵ���ƻ�_���мƻ�       TPFlyPlan
//ѵ���ƻ�                TrainPlanData ��demo4�ṹ�����Ժ�ɾ����
//���мƻ�                FlyPlanData    ��demo4�ṹ�����Ժ�ɾ����

#ifndef _H_TRAINPLAN_DATA_OBJS_H
#define _H_TRAINPLAN_DATA_OBJS_H
#include "DataObj.h"
#include "assistance_data_objs.h"
#include "public\BaseTypeDefine\PublicTypeDefine.h"

class TrainPlan : public DataObj
{
public:
	TrainPlan();
	~TrainPlan();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	TrainPlan(const TrainPlan &trainPlan);
	TrainPlan& operator=(const TrainPlan& trainPlan);

    //boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_strTrainPlanName & m_iAirportID 
			& m_iAirportModelID & m_iEnvironmentID & m_strDate & m_iStartTime & m_bUnion 
			& m_iControllerNum & m_mapControllerSector & m_vObjPlan & m_vCloudPlan & m_vSmokePlan & m_vVehiclePlan & m_vSpecialEffectObjPlan
			 & m_vEnvPlan;
	}

public:
	int m_iTrainPlanID;							  /* ѵ���ƻ�ID */
	std::string m_strTrainPlanName;	      /* ѵ���ƻ�����*/
	int m_iAirportID;								  /* ����ID */
	int m_iAirportModelID;						  /* ����ģ��ID */
	int m_iEnvironmentID;						  /* ��������ID */
	std::string m_strDate;						  /* ѵ������*/
	int m_iStartTime;								  /* ѵ����ʼʱ�� ��0�㿪ʼ������� */     
	bool m_bUnion;								  /* �Ƿ�����ѵ��*/
	int m_iControllerNum;                        /* ��Ҫ�Ĺ���ϯλ��*/
	std::map<int, std::vector<int> >  m_mapControllerSector;   /* ����ϯλ�������Ķ�Ӧ��ϵ*/
	vector<int> m_vObjPlan;						//Ŀ��ƻ�������Ŀ��ƻ�ID
	vector<int> m_vCloudPlan;					//�Ƽƻ�
	vector<int> m_vSmokePlan;					//�̼ƻ�
	vector<int> m_vVehiclePlan;					//�����ƻ�
	vector<int> m_vSpecialEffectObjPlan;  //��Ч�˶�����ƻ�
	vector<int> m_vEnvPlan;//���������ƻ�
};

/*----------------ѵ���ƻ�-���мƻ�----------------------*/
class TPFlyPlan : public DataObj
{
public:
	TPFlyPlan();
	~TPFlyPlan();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	TPFlyPlan(const TPFlyPlan &flyPlan);
	TPFlyPlan& operator=(const TPFlyPlan& flyPlan);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlyPlanID & m_iObjPlanID &m_strFlyPlanName 
			& m_strSSRCode & m_iSectorID & m_iControllerID & m_iPilotID & m_bAutoTakeoff 
			& m_bRVSM & m_iFlyPlanType & m_iCompanyID & m_strCallSign 
			& m_iDepDromeID & m_iArrDromeID & m_iAlternateDromeID 
			& m_dFuelTime & m_dCruiseLvl & m_dCruiseSpd & m_iArrRunwayID 
			& m_iDepRunwayID & m_iWeight & m_iDepGateID & m_iArrGateID 
			& m_iVacateLineID & m_iInRunwayLineID & m_iDepartureTime 
			& m_iArrivalTime & m_strRemark & m_vecRoutePt;
	}

public:
	int m_iFlyPlanID;                    /* ���мƻ�ID */
	string m_strFlyPlanName;             /* ���мƻ����� */
	string m_strSSRCode;                 /*  ������ */
	int m_iObjPlanID;				  /* ���мƻ�Ŀ��ID*/
	int m_iSectorID;                   //������������
	int m_iControllerID;                 /* ��������ԱϯλID */
	int m_iPilotID;                      /* ��������ϯλID */
	bool m_bAutoTakeoff;		         /* �Ƿ��Զ����*/
	bool m_bRVSM;			             /* �Ƿ�߱�RVSM����*/

	//�����Ƿ��мƻ�ģ���е����ݣ���ѵ���ƻ��п����޸�
	int	m_iFlyPlanType;	                 /* ���мƻ����� 0 ���ۣ�1 ��� ��2 ��Ծ*/
	int	m_iCompanyID;		             /* ���չ�˾ */
	string 	m_strCallSign;		         /* ���ţ����չ�˾+���ֱ��룩*/
	int	m_iDepDromeID;		             /* ��ɻ��� */
	int	m_iArrDromeID;       		     /* ������� */
	int	m_iAlternateDromeID;	         /* ������ */
	int m_dFuelTime;		             /* ȼ��ʱ��(��λ����) */
	int m_dCruiseLvl;		             /* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
	int	m_dCruiseSpd;		             /* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
	int	m_iArrRunwayID;		             /* �����ܵ� */
	int m_iDepRunwayID;                  /* ����ܵ�*/
	int	m_iWeight;		                 /* ���� */
	int	m_iDepGateID;		             /* �볡��ͣ��λ */
	int	m_iArrGateID;		             /* ������ͣ��λ */
	int m_iVacateLineID;		         /* �����ID */
	int m_iInRunwayLineID;               /* �����ID */
	int m_iDepartureTime;		         /* Ԥ�����ʱ�䣨��λ���룩*/
	int m_iArrivalTime;		             /* Ԥ�Ƶ���ʱ�䣨��λ���룩*/
	string m_strRemark;		             /* ��ע��Ϣ */
	vector<boost::shared_ptr<RoutePt> > m_vecRoutePt;	     /* ��·�� */

};

//�ɻ�Ŀ��ƻ�
class ObjPlan : public DataObj
{
public:
	ObjPlan();
	~ObjPlan();
	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();
	//��������ֵ����
	ObjPlan(const ObjPlan &objPlan);
	ObjPlan& operator=(const ObjPlan& objPlan);
	//boost���л�
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iObjPlanID &m_iTrainPlanID & m_strRegNum & m_strSSRCode 
			& m_iAppearTime & m_iAircraftTypeID & m_dLongtitude 
			& m_dLatitude & m_dAltitude & m_dHeading & m_dIAS 
			& m_strCmd & m_bEngineStart &m_vFlyPlan;
	}

	int     m_iObjPlanID;		//���мƻ�ID��һ���ɻ�ȫ�̿ɹ���������мƻ�����ͬһʱ��ֻ�ܹ���һ������һ��һ�Ĺ�ϵ��
	int m_iTrainPlanID;             /* ѵ���ƻ�ID */
	string	m_strRegNum;		//ע���
	string 	m_strSSRCode;		//������xx
	int   	m_iAppearTime;		//�ɻ�����ʱ�䣨��λ���룩
	int	m_iAircraftTypeID;	//����
	double	m_dLongtitude;		//�ɻ����ֵľ��ȣ���λ�����ȣ�
	double	m_dLatitude;           	//�ɻ����ֵ�γ�ȣ���λ�����ȣ�
	double 	m_dAltitude;		//�ɻ��ĳ�ʼ�߶ȣ���׼��ѹ�߶ȣ���λ���ף�
	double 	m_dHeading;		//��ͷ���򣨵�λ�����ȣ�
	double 	m_dIAS;			//��ʼ�ٶȣ����٣���λ����/�룩
	string  m_strCmd;			//�������
	bool 	m_bEngineStart;		//�����Ƿ���
	vector<int> m_vFlyPlan;     //һ��Ŀ��ƻ��µķ��мƻ�

};

/*-----------------ѵ���ƻ�------------*/
class TrainPlanData : public DataObj
{
public:
	int m_iTrainPlanID;		        /* ѵ���ƻ�ID */
	std::string m_szTrainPlanName;  /* ѵ���ƻ���*/

	TrainPlanData();
	~TrainPlanData();

	//��������ֵ����
	TrainPlanData(const TrainPlanData &trainPlanData);
	TrainPlanData& operator=(const TrainPlanData& train_plan_data);
	bool operator==(DataObj *dataobj);


	int GetId();
	std::string GetDisplayLabel();

	bool IsEqual(DataObj *dataobj);
	void Copy(DataObj *dataobj);


	//Set����


	//Get����



	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_szTrainPlanName;
	}
};


/*----------------�����ƻ�-----------------*/
class VehiclePlan  : public DataObj
{
public:
	VehiclePlan();
	~VehiclePlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	VehiclePlan(const VehiclePlan & vehiclePlan);
	VehiclePlan& operator=(const VehiclePlan & vehiclePlan);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar &m_iTrainPlanID	& m_iVehiclePlanId & m_strVehiclePlanName & m_strCallsign               
			& m_iVehicleId & m_iSectorId & m_eVehiclePlanType & m_eBelongedType        			
			& m_iBelongedId & m_iAppearTime & m_dLongitude & m_dLatitude				
			& m_dHeading& m_dSpeed &m_bEngineStart & m_strCmd & m_strRemark ;
	}


public:
	int    m_iTrainPlanID		; //ѵ���ƻ�ID
	int 	m_iVehiclePlanId     ; //�����ƻ�ID
	string 	m_strVehiclePlanName   ; //�����ƻ�����
	string 	m_strCallsign              ; //�����ƻ�����
	int	m_iVehicleId             ; //��������ID
	int	m_iSectorId				; //����ID
	int	m_eVehiclePlanType		; //�����ƻ�����0 = ���ڳ�����1= ���⳵��
	int	m_eBelongedType			; //���ƻ���ʹ�õĳ����������ͣ���ʾ��������ʾ���չ�˾
	int	m_iBelongedId			; //������������iBelongedType ȷ��������λ��Ϊ0 ��ʾ����ID��1��ʾ���չ�˾ID
	int	m_iAppearTime			; //����ʱ��
	double	m_dLongitude				; //����
	double	m_dLatitude				; //γ��
	double	m_dHeading				; //����
	double	m_dSpeed					; //�ٶ�
	bool	m_bEngineStart			; //�����Ƿ�����
	string	m_strCmd					; //����
	string	m_strRemark                ; //��ע
};

class FlyPlanData : public DataObj
{
public:
	int m_iTrainPlanID;		    /* ѵ���ƻ�ID */
	int m_iFlyPlanID;			/* ���мƻ�ID, �ǴӸ÷��мƻ��и��ƹ����ļƻ� ����������п��ܺ�ԭ����ֵ��һ�� */
	std::string m_szFlyPlanName;
	std::string m_szSignName;
	double m_dX;                    /* �ɻ����ֵ�λ�� X���� Ĭ��0 ʹ�þ�γ��*/
	double m_dY;					/* Y���� Ĭ��0 ʹ�þ�γ��*/
	double m_dZ;					/* Z���� Ĭ��0 ʹ�þ�γ��*/
	double m_dHeading;			    /* ��ͷ���� Ĭ��0 */
	double m_dSpeed;				/* ��ʼ�ٶ�*/
	int m_iAircraftID;			    /* ����*/

	FlyPlanData();
	~FlyPlanData();
	FlyPlanData(const FlyPlanData &flyPlanInfo);
	FlyPlanData& operator=(const FlyPlanData& flyPlanInfo);

	int GetId();
	int GetOwnerId();
	std::string GetDisplayLabel();

	bool IsEqual(DataObj *dataobj);
	void Copy(DataObj *dataobj);


	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iFlyPlanID & m_szFlyPlanName & m_szSignName 
			& m_dX & m_dY & m_dZ & m_dHeading & m_dSpeed & m_iAircraftID; 
	}
};



/*----------------ѵ���ƻ�-���мƻ��������ͻ��ˣ�----------------------*/
/*! 
\brief     FPL��Ϣ�ṹ�壨��TPFlyPlan��Ӧ��
\details   �ṩ������װ���FPL���ݣ�����ֱ���ṩ���ݱ��е�����
\author    lijin
\date      2013-05-28
*/
class FplInfo : public DataObj
{
public:
	FplInfo();
	~FplInfo();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	FplInfo(const FplInfo & flyPlan);
	FplInfo& operator=(const FplInfo & flyPlan);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlyPlanID & m_strFlyPlanName 
			& m_strSSRCode & m_strSector & m_iControllerID & m_iPilotID & m_bAutoTakeoff 
			& m_bRVSM & m_iFlyPlanType & m_strCompanyName & m_strCallSign 
			& m_strDepDrome & m_strArrDrome & m_strAlternateDrome 
			& m_nFuelTime & m_nCruiseLvl & m_nCruiseSpd & m_strArrRunwayName 
			& m_strDepRunwayName & m_iWeight & m_strDepGateName & m_strArrGateName 
			& m_strVacateLineName & m_strInRunwayLineName & m_tDepartureTime 
			& m_tArrivalTime & m_strRemark & m_vecRoutePtNames;
	}

public:
	int		m_iFlyPlanID;                 /* ���мƻ�ID */
	string	m_strFlyPlanName;             /* ���мƻ����� */
	string	m_strSSRCode;                 /*  ������ */
	string	m_strSector;                  //������������
	int		m_iControllerID;              /* ��������ԱϯλID */
	int		m_iPilotID;                   /* ��������ϯλID */
	bool	m_bAutoTakeoff;				  /* �Ƿ��Զ����*/
	bool	m_bRVSM;					  /* �Ƿ�߱�RVSM����*/

	//�����Ƿ��мƻ�ģ���е����ݣ���ѵ���ƻ��п����޸�
	int		m_iFlyPlanType;	              /* ���мƻ����� */
	string  m_strCompanyName;			  /* ���չ�˾ */
	string 	m_strCallSign;		          /* ���ţ����չ�˾+���ֱ��룩*/
	string  m_strDepDrome;		          /* ��ɻ��� */
	string  m_strArrDrome;       		  /* ������� */
	string  m_strAlternateDrome;	      /* ������ */

	int     m_nFuelTime;		          /* ȼ��ʱ��(��λ����) */
	int     m_nCruiseLvl;		          /* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
	int		m_nCruiseSpd;		          /* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
	string  m_strArrRunwayName;		      /* �����ܵ� */
	string  m_strDepRunwayName;           /* ����ܵ�*/
	int		m_iWeight;					  /* ���� */
	string  m_strDepGateName;		      /* �볡��ͣ��λ */
	string  m_strArrGateName;		      /* ������ͣ��λ */

	string  m_strVacateLineName;		  /* ����� */
	string  m_strInRunwayLineName;          /* ����� */
	time_t  m_tDepartureTime;		      /* Ԥ�����ʱ�䣨��λ���룩*/
	time_t  m_tArrivalTime;		          /* Ԥ�Ƶ���ʱ�䣨��λ���룩*/
	string	m_strRemark;		          /* ��ע��Ϣ */
	vector<std::string> m_vecRoutePtNames;/* ��·������ */
};

/*! 
\brief     �Ƶ�����
\details   
\author    JZH
\date      2013-06-04
*/
enum ENUM_CLOUD_TYPE
{
	ECT_DEFAULT_YUN = 0,  //Ĭ�ϵ���
	ECT_CENG_YUN,     //����
	ECT_JUAN_YUN,     //����
	ECT_DAN_JI_YUN,   //������
	ECT_NONG_JI_YUN,  //Ũ����
	ECT_JIYU_YUN,      //������
};

/*! 
\brief     �Ƽƻ�
\details   ѵ���ƻ��а������Ƽƻ�
\author   JZH
\date      2013-06-04
*/
class CloudPlan: public DataObj
{
public:
	CloudPlan();
	~CloudPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCloudID & m_strCloudName & m_eCloudType & m_iTrainPlanID 
			& m_dLongitude & m_dLatitude & m_dZ & m_dSize; 
	}
public:

	int m_iCloudID;		//!<��ID
	std::string m_strCloudName;  //!< ������
	ENUM_CLOUD_TYPE m_eCloudType;	//!<������
	int m_iTrainPlanID;	//!<ѵ���ƻ�ID
	double m_dLongitude;//!<���ŵľ���
	double m_dLatitude;	//!<��ͼ��γ��
	double m_dZ;		//!<��ͼ�߶�
	double m_dSize;		//!<��ͼֱ����С
};

/*! 
\brief     �̵�����
\details   
\author    JZH
\date      2013-06-04
*/
enum SMOKE_TYPE
{
	EST_JIEGAN = 0,	//!<�ո���
};

/*! 
\brief     �̼ƻ�
\details   ѵ���ƻ��а������̼ƻ�
\author    JZH
\date      2013-06-04
*/
class SmokePlan: public DataObj
{
public:
	SmokePlan();
	~SmokePlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iSmokeID & m_strSmokeName & m_eSmokeType & m_iTrainPlanID 
			& m_dLongitude & m_dLatitude & m_dZ & m_dSize; 
	}	
public:

	int m_iSmokeID;		//!<��ID
	std::string m_strSmokeName; //!< ������
	SMOKE_TYPE m_eSmokeType;	//!<������
	int m_iTrainPlanID;	//!<ѵ���ƻ�ID
	double m_dLongitude;//!<�̵ľ���
	double m_dLatitude;	//!<�̵�γ��
	double m_dZ;		//!<�̵ĸ߶�
	double m_dSize;		//!<�̵�ֱ����С
};

/*! 
\brief     �������
\details   
\author    JZH
\date      2013-06-04
*/
enum FOG_TYPE
{
	EFT_NONE = 0,	//!<����
	EFT_PINGLIU,	//!<ƽ����
	EFT_FUSHE		//!<������
};



/*! 
\brief     ��Ч�˶�����ƻ�
\details  
\author	   ZY
\date      2013-06-24
\modifer   DXQ 2013-06-24
*/
class SpecialEffectObjPlan : public DataObj
{
public:
	SpecialEffectObjPlan();
	~SpecialEffectObjPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	SpecialEffectObjPlan(const SpecialEffectObjPlan & effectObjPlan);
	SpecialEffectObjPlan& operator=(const SpecialEffectObjPlan & effectObjPlan);

public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iObjPlanId & m_eObjType & m_strName 
			& m_dLongitude & m_dLatitude & m_dAltitude & m_dSpeed & m_vecRoute & m_bLoop; 
	}

public:
	int m_iTrainPlanID;				//ѵ���ƻ�ID
	int m_iObjPlanId;				//��Ч����id
	ENUM_OBJ_TYPE m_eObjType;		//��Ч�����������
	string m_strName;				//��Ч��������
	double	m_dLongitude;			//���ȣ���λ�����ȣ�
	double	m_dLatitude;			//γ��
	double 	m_dAltitude;			//��ʼ�߶ȣ���λ���ף�
	double	m_dSpeed;				//�ٶ�(��λ:km/h) 
	vector<stPoint> m_vecRoute;		//�˶�·����(��γ��ָ��)
	bool m_bLoop;					//·���Ƿ�ѭ��
};

/*!
\brief  ��Ч�˶����徭���Ĺ켣��
\details  
\author CX
\date 2013/06/29
*/
class RoutePointPosition : public DataObj
{
public:
	RoutePointPosition();
	~RoutePointPosition();
	virtual int GetOwnerId();
	void SetSequence(int iSeq);  //Ϊ������designer��ģ��������
	int GetSequence();			   //Ϊ������designer��ģ��������

	int m_iSequence;		//������
	int m_iOwnerID;		//��������Ч�˶�����ƻ���ID
	stPoint m_stPosion;  //���λ��
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iOwnerID & m_iSequence & m_stPosion;
	}
};


/*! 
\brief     �����Ӷ������
\details   
\author    DXQ
\date      2013-06-25
*/
enum ENUM_ENV_OBJ_TYPE 
{
	ENV_OBJ_NONE = -1,				//δ֪����
	ENV_OBJ_RAIN,					//��
	ENV_OBJ_SNOW,					//ѩ
	ENV_OBJ_VISIBILITY,				//�ܼ���
	ENV_OBJ_TEMPERATURE,			//�¶�
	ENV_OBJ_DEWPOINT,				//¶��
	ENV_OBJ_DUST,					//��
	ENV_OBJ_RISENDUST,					//��ɳ
	ENV_OBJ_QNH,					//��ѹ
	ENV_OBJ_HAZE,					//��
	ENV_OBJ_FOG,					//��
	ENV_OBJ_LIGHTINGT,				//����
	ENV_OBJ_WIND,					//��
	ENV_OBJ_QFE,					//��ѹ
	ENV_OBJ_SMOKE,					//��
	ENV_OBJ_SPECIALEFFECTOBJ,		//��Ч�˶�����

};



/*! 
\brief     �����Ӷ�����ĳһʱ����ڵļƻ�
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvObjectPhasePlan : public DataObj
{
public:
	EnvObjectPhasePlan();
	~EnvObjectPhasePlan();

	//��������ֵ����
	EnvObjectPhasePlan(const EnvObjectPhasePlan & envObjectPhasePlan);
	EnvObjectPhasePlan& operator=(const EnvObjectPhasePlan & envObjectPhasePlan);

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_dTimePoint & m_iLevel & m_bPhasePlanOn & m_dWindSpeed & m_dWindDirection 
			& m_dLightingDirection & m_dLightingRadious & m_dQFE & m_dSmokeDensity & m_dTemprature& m_dQNH & m_dRVR & m_dDewPoint; 
	}

public:
	double m_dTimePoint;			//��Կ�ʼʱ���ʱ�����
	int m_iLevel;					//�ȼ�,EnvObjectPlan�����е�m_eEnvObjectTypeȡֵ����ʱ����ֵ������
									//ENV_OBJ_RAIN,					//��
									//ENV_OBJ_SNOW,					//ѩ
									//ENV_OBJ_DEWPOINT,				//¶��
									//ENV_OBJ_DUST,					//��
									//ENV_OBJ_RISENDUST,		//��ɳ
									//ENV_OBJ_QNH,					//��ѹ
									//ENV_OBJ_HAZE,					//��
									//ENV_OBJ_FOG,					//��
									//ENV_OBJ_LIGHTINGT,			//����
	bool m_bPhasePlanOn;			//��ʱ����ڵļƻ��Ƿ���á�EnvObjectPlan�����е�m_eEnvObjectTypeȡֵ����ʱ����ֵ������
									/*	
									ENV_OBJ_DUST,					//��
									ENV_OBJ_RISENDUST,					//��ɳ
									ENV_OBJ_HAZE,					//��
									ENV_OBJ_FOG,					//��
									ENV_OBJ_LIGHTINGT,				//����
									ENV_OBJ_SMOKE,					//��*/
									
	double m_dWindSpeed;			//���٣�EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_WINDʱ����ֵ������
	double m_dWindDirection;		//����EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_WINDʱ����ֵ������
	double m_dLightingDirection;	//�����λ��EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_LIGHTINGTʱ����ֵ������
	double m_dLightingRadious;		//������룬EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_LIGHTINGTʱ����ֵ������
	double m_dQFE;					//��ѹ��EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_QFEʱ����ֵ������
	double m_dSmokeDensity;			//�̵��ܶȣ�EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_SMOKEʱ����ֵ������
	double m_dTemprature;			//�¶�ֵ��EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_TEMPERATUREʱ����ֵ������
	double m_dQNH;						//��ѹֵ��EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_QNHʱ����ֵ������
	double m_dRVR;						//�ܼ���,EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_VISIBILITYʱ����ֵ������
	double m_dDewPoint;				//¶�㣬EnvObjectPlan�����е�m_eEnvObjectTypeΪENV_OBJ_DEWPOINTʱ����ֵ������
};


/*! 
\brief     �����Ӷ���ƻ�
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvObjectPlan : public DataObj
{
public:
	EnvObjectPlan();
	~EnvObjectPlan();

	//��������ֵ����
	EnvObjectPlan(const EnvObjectPlan & envObjectPlan);
	EnvObjectPlan& operator=(const EnvObjectPlan & envObjectPlan);

	int GetId();
	int GetOwnerId();

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iEnvPlanID & m_iEnvObjectPlanID & m_eEnvObjectType & m_dStartTime 
			& m_dEndTime & m_vecEnvObjectPhasePlan; 
	}

public:
	int m_iEnvPlanID;					//�����ƻ�ID
	int m_iEnvObjectPlanID;				//�����Ӷ���ƻ�ID
	ENUM_ENV_OBJ_TYPE m_eEnvObjectType;//�����Ӷ������ȡֵ���£�
										/*	ENV_OBJ_RAIN,				//��
										ENV_OBJ_SNOW,					//ѩ
										ENV_OBJ_VISIBILITY,				//�ܼ���
										ENV_OBJ_TEMPERATURE,			//�¶�
										ENV_OBJ_DEWPOINT,				//¶��
										ENV_OBJ_DUST,					//��
										ENV_OBJ_RISENDUST,					//��ɳ
										ENV_OBJ_QNH,					//��ѹ
										ENV_OBJ_HAZE,					//��
										ENV_OBJ_FOG,					//��
										ENV_OBJ_LIGHTINGT,				//����
										ENV_OBJ_WIND,					//��
										ENV_OBJ_QFE,					//��ѹ
										ENV_OBJ_SMOKE,					//��*/

	double m_dStartTime;				//�ƻ���ʼʱ��
	double m_dEndTime;					//�ƻ�����ʱ��
	std::vector<EnvObjectPhasePlan> m_vecEnvObjectPhasePlan;	//��ͬʱ�̵Ļ����Ӷ���ƻ�vector
};


/*! 
\brief     �����Ӷ���ƻ������ܵ������ƻ�
\details   
\author    DXQ
\date      2013-06-25
*/
class RunwayEnvPlan : public DataObj
{
public:
	RunwayEnvPlan();
	~RunwayEnvPlan();

	//��������ֵ����
	RunwayEnvPlan(const RunwayEnvPlan & runwayEnvPlan);
	RunwayEnvPlan& operator=(const RunwayEnvPlan & runwayEnvPlan);

//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iEnvPlanID & m_iRunwayID & m_dTemperatureRatio 
			& m_dDewpointRatio & m_dWindSpdRatio & m_dWindDirRatio & m_dQNHRatio & m_dQFERatio; 
	}

public:
	int m_iAirportID;				/* ����ID*/
	int m_iEnvPlanID;				/* �����ƻ�ID*/
	int m_iRunwayID;				/* �ܵ�ID */ 

	double m_dTemperatureRatio;		/* �¶�ƫ�����Ĭ��1*/
	double m_dDewpointRatio;		/* ¶��ƫ�����Ĭ��1*/
	double m_dWindSpdRatio;			/* ���ٱ仯ƫ���Ĭ��1*/
	double m_dWindDirRatio;			/* ����ƫ��Ĭ��0*/
	double m_dQNHRatio;				/* ������ѹƫ�����Ĭ��1*/		
	double m_dQFERatio;				/* ��ѹƫ�����Ĭ��1*/
};


/*! 
\brief     �����ƻ�
\details   
\author    DXQ
\date      2013-06-25
*/
class EnvPlan : public DataObj
{
public:
	EnvPlan();
	~EnvPlan();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//��������ֵ����
	EnvPlan(const EnvPlan & envPlan);
	EnvPlan& operator=(const EnvPlan & envPlan);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iTrainPlanID & m_iEnvPlanID & m_strEnvPlanName & m_RainPlan 
			& m_SnowPlan & m_RVRPlan & m_TempraturePlan & m_DewPointPlan & m_DustPlan & m_RisenDustPlan & m_QNHPlan & m_HazePlan
			& m_FogPlan & m_LightingPlan & m_WindPlan & m_QFEPlan & m_SmokePlan & m_RunwayEnvPlan & m_SpecialEffectObjPlan; 
	}

public:
	int m_iTrainPlanID;					//ѵ���ƻ�ID
	int m_iEnvPlanID;					//�����ƻ�ID
	std::string m_strEnvPlanName;		//�����ƻ�����
	RunwayEnvPlan m_RunwayEnvPlan;		//�����Ӷ���ƻ������ܵ������ƻ�
	EnvObjectPlan m_RainPlan;			//�����Ӷ���ƻ�������ƻ�
	EnvObjectPlan m_SnowPlan;			//�����Ӷ���ƻ�����ѩ�ƻ�
	EnvObjectPlan m_RVRPlan;			//�����Ӷ���ƻ������ܼ��ȼƻ�
	EnvObjectPlan m_TempraturePlan;		//�����Ӷ���ƻ������¶ȼƻ�
	EnvObjectPlan m_DewPointPlan;		//�����Ӷ���ƻ�����¶��ƻ�
	EnvObjectPlan m_DustPlan;			//�����Ӷ���ƻ��������ƻ�
	EnvObjectPlan m_RisenDustPlan;			//�����Ӷ���ƻ�������ɳ�ƻ�
	EnvObjectPlan m_QNHPlan;			//�����Ӷ���ƻ�������ѹ�ƻ�
	EnvObjectPlan m_HazePlan;			//�����Ӷ���ƻ��������ƻ�
	EnvObjectPlan m_FogPlan;			//�����Ӷ���ƻ�������ƻ�
	EnvObjectPlan m_LightingPlan;		//�����Ӷ���ƻ���������ƻ�
	EnvObjectPlan m_WindPlan;			//�����Ӷ���ƻ�������ƻ�
	EnvObjectPlan m_QFEPlan;			//�����Ӷ���ƻ�������ѹ�ƻ�
	EnvObjectPlan m_SmokePlan;			//�����Ӷ���ƻ������̼ƻ�
	EnvObjectPlan m_SpecialEffectObjPlan; //�����Ӷ���ƻ�������Ч�˶�����ƻ�
};


/*! 
\brief     ��������
\details   
\author    JZH
\date      2013-06-04
*/
class EnvData: public DataObj
{
public:
	EnvData();
	~EnvData();

	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iRainLevel & m_iSnowLevel & m_enumFogType & m_dVis 
			& m_dSunRiseTime & m_dSunSetTime & m_strTerrainName & m_dTerrainPosX & m_dTerrainPosY & m_dTerrainPosZ
			& m_iVaneX & m_iVaneY & m_iDogVaneX & m_iDogVaneY; 
	}	
public:

	int m_iRainLevel;		//!<��������1~3����0��������
	int m_iSnowLevel;		//!<ѩ������1~3����0������ѩ
	FOG_TYPE m_enumFogType;	//!<0 = ����1 = ƽ����2=������ Ĭ��0
	double m_dVis;			//!<�ܼ���

	double m_dSunRiseTime;	//!<�ճ�ʱ��
	double m_dSunSetTime;	//!<����ʱ��

	std::string m_strTerrainName;	//!<��������
	double  m_dTerrainPosX;	//!<��������
	double  m_dTerrainPosY;	//!<��������
	double  m_dTerrainPosZ;	//!<��������
	int m_iVaneX;		//!<
	int m_iVaneY;		//!<
	int m_iDogVaneX;	//!<
	int m_iDogVaneY;	//!<
};




/*!
\brief  Ŀ��ƻ����ͣ������Ӿ���
\details  
\author DXQ
\date 2013/6/19
*/
enum ENUM_PLAN_TYPE
{
	PLAN_TYPE_AIRCRAFT = 0,	//Ŀ��ƻ�
	PLAN_TYPE_VEHICLE,		//�����ƻ�
};


/*! 
\brief     Ŀ��ƻ���Ϊ�Ӿ�ʹ�ã�
\details   ��Ϊ�Ӿ���Ҫ��Ŀ��ƻ������ݲ��࣬Ϊ�˼���������Ĵ�С����д���ࡣ
\author    JZH
\date      2013-06-04
\modifer   DXQ 2013-06-19
*/
class ObjPlanForVis: public DataObj
{
public:
	ObjPlanForVis();
	~ObjPlanForVis();

	int GetId();
	string GetDisplayLabel();
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_eObjPlanType & m_iObjPlanID & m_iObjID & m_strCallSign & m_strCompanyName; 
	}	
public:
	ENUM_PLAN_TYPE	m_eObjPlanType;	//�ƻ�����
	int	m_iObjPlanID;				//m_eObjPlanType ΪPLAN_TYPE_AIRCRAFTʱ�������Ӿ�Ҫ������Ŀ��ƻ�ID����Ӧѵ���ƻ��е�Ŀ��ƻ���ID
									//m_eObjPlanType ΪPLAN_TYPE_VEHICLEʱ�� �����Ӿ�Ҫ�����ĳ����ƻ�ID����Ӧѵ���ƻ��еĳ����ƻ���ID
	int m_iObjID;					//m_eObjPlanType ΪPLAN_TYPE_AIRCRAFTʱ���������ID����ʾ�����ֻ��ͣ�����AircraftForVis�е�m_iAircraftID
									//m_eObjPlanType ΪPLAN_TYPE_VEHICLEʱ,  ������ID����ʾ�����ֳ���������VehicleForVis�е�m_iVehicleID
	std::string	m_strCallSign;		//m_eObjPlanType ΪPLAN_TYPE_AIRCRAFTʱ�����Ŀ��ƻ����˶�����мƻ����Ǵ˴������һ�����мƻ��ĺ���
									//m_eObjPlanType ΪPLAN_TYPE_VEHICLEʱ,	 �����ƻ�����
	std::string	m_strCompanyName;	//m_eObjPlanType ΪPLAN_TYPE_AIRCRAFTʱ��������˾���ƣ����Ŀ��ƻ����˶�����мƻ����Ǵ˴������һ�����мƻ���������˾����
									//m_eObjPlanType ΪPLAN_TYPE_VEHICLEʱ�� ֵû������
};

/*!
\brief     �ƹ�ƻ�
\details   ������ĳ��ѵ���ƻ��еĵƹ⿪�������
\author    JZH
\date      2013-06-25
*/
class LightPlan: public DataObj
{
public:
	LightPlan();
	~LightPlan();
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLightPlanID & m_iTrainPlanID & m_szLightPlanName & m_iLightCollectionID & m_iLightLevel;
	}
public:
	int m_iLightPlanID;	//!<�ƹ�ƻ���ID
	int m_iTrainPlanID;	//!<ѵ���ƻ�ID
	std::string m_szLightPlanName;	//!<�ƹ�ƻ�����
	int m_iLightCollectionID;	//!<�ƹ������ID
	int m_iLightLevel;	//!<�ƹ�ȼ���0��5,0Ϊ�رգ�
};

#endif