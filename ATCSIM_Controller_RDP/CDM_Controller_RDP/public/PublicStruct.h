/*********************************************************************
 * Copyright(c) Reserved, WiseSoft Corporation.
 *   FileName: CDM_GlobalVariable.h
 *     Author: ����ƽ
 *       Date: 2014/08/31
 *Description: �������õ��Ĺ����ṹ����
 ********************************************************************/
#ifndef CDM_GLOBALVARIABLE_H
#define CDM_GLOBALVARIABLE_H
#include <QMetaType>
#include <QString>
#include<vector>
#include <string>
#define M_PI       3.14159265358979323846
namespace PublicDataStruct
{
	const int   BUFFERSZE=4096;
	const int	SENDFLIGHTPLANUDPPORT	= 10000;//���ͷ��мƻ���UDP�˿ں�
	const int	RECVFLIGHTPLANIDPORT	= 9902; //���պ���ID��UDP�˿ں�
	const int	SENDCOMMANDUDPPORT		= 9901; //���������UDP�˿ں�
	const int	RECVFLYPLANPORT			= 9903; //���շ��мƻ���UDP�˿ڣ�����CDMϵͳ����CDM����һ��
	const int   SENDAIRCRAFTTRACEPORT	= 13000;//���ͺ�����UDP�˿�
	// �ƻ���״̬:δ��(�յ�PLN)����ֹ(�յ�FPL)��Ԥ����(Ԥ�����ʱ��ǰ��Сʱ)��Э�����ƽ������ơ���ɡ�ȡ��
	enum PLAN_STATUS{FUTR=0, NACT=1, PREA=2, COOR=3, HAND=4, CONT=5, FIN=6, CNL=7};
	//��վ¥��Ϣ
	enum PLAN_TERMINATE{T1_TERMINATE=0,T2_TERMINATE};
	//Ŀ�����ͣ�����ΪOT_PLAN
	enum ENUM_OBJ_TYPE 
	{
		OT_OBJ_NONE = 0,			//δ֪����
		OT_PLANE,					//���÷ɻ�(��ֱ������)
		OT_HELICOPTER,				//ֱ����
		OT_VEHICLE,					//����
		OT_ENV,              
		OT_BIRD,					//��
		OT_CATTLE,					//ţ
		OT_DOG,						//��
		OT_BALLOON,					//����
		OT_SERVICE_CAR = 120,		//������
	};
	//���мƻ�����
	enum ENUM_PLAN_TYPE
	{
		
		CDM_ARR_PLAN=0,			//�����ƻ�
		CDM_DEP_PLAN,			//�볡�ƻ�
	};
	//! ��������
	enum ENUM_TRACKTYPE
	{
		TRACKTYPE_INVALID,
		TRACKTYPE_INAIR,
		TRACKTYPE_ONGROUND,
	};
	//! �߶�����
	enum ENUM_AltitudeType
	{
		ALTTYPE_INVALID,
		ALTTYPE_QNE,    //��ѹ
		ALTTYPE_QFE,    //��ѹ�߶�
		ALTTYPE_QNH,   //��ѹ�߶�
	};


	// �˶�Ŀ��״̬���Ͷ���
	enum ENUM_STATE_TYPE
	{
		STATE_NONE=0,             //δ����״̬
		STAT_COOL_WAIT = 1,       //��ȴ�(�ر�����)
		STAT_START_UP = 2,          //������״̬
		STAT_CLOSE_DOWN = 3,      //������״̬
		STAT_WARM_WAIT = 4,        //�ȵȴ�(������)
		STAT_TAXING = 5,              //���滬��״̬
		STAT_LAUNCHING = 6,       //���״̬
		STAT_LANDING = 7,            //����״̬
		STAT_HOLD = 9,                  //��������״̬
		STAT_SPECIAL_OPER = 11,         //��������״̬
		STAT_IN_AIR = 13,                  //���з���״̬
		STAT_SID=14,         //��׼��۳���
		STAT_STAR=15,     //��׼���۳���
		STAT_CRASHED=16,   //ײ��
		STAT_HELI_TDF = 17, //ֱ�������ط�
		STAT_HELI_XT = 18,  //ֱ������ͣ
		STAT_HELI_MOVE = 19,//ֱ�����ƶ�
		STAT_CAR_SERVICE = 20,//������
		STAT_AIRKINEMATIC = 21,//׹��
		STAT_SIMPLE_TOWER,         //����̨״̬
	};
	//�״��ź�����
	enum RADAR_SIGNAL_TYPE
	{
		SIGNAL_NONE = 0, //δ��ɨ�赽
		SIGNAL_PRIMARY,  //һ���״��ź�
		SIGNAL_SECONDARY,//�����״��ź�
		SIGNAL_ADSB,	 //ADSB�״��źţ����޸������
		SIGNAL_COMBINED  //һ�����״��ں��ź�
	};
	enum HMI_STAT
	{
		HMI_NONE = 0,
		HMI_UNCONCERN,
		HMI_PREA,
		HMI_HND_IN,
		HMI_ANNOUNCE,
		HMI_HND_OUT,
		HMI_JURI,
	};
	//���мƻ���Դ
	enum PLAN_SOURCE
	{
		LPL = 0, //���ر༭ 
		RPL,	 //�ظ��Է��мƻ�		
		TELE,	 //���мƻ��� 	
		STL,     //ģ����мƻ�
		TAG      //�����
	};
	// �������ͣ�δ֪��       ������-��ۡ�		 ������-��ۡ�		  ������-���ۡ�	   ������-���ۡ� �����ػ�(�ɳ�����)
	enum CPL_TYPE{ UNKNOWN=0, EXTERNAL_INBD,	 DOMES_INBD,		  EXTERNAL_OUTBD,  DOMES_OUTBD,	 BYPASS,
		//					   ������-����������ۡ� ������-�����������ۡ�������-��������֮����С�	���������������ػ�(�ɳ�����)						 
		EXTERNAL_ADP_INBD,	 EXTERNAL_ADP_OUTBD,  DOMESTIC,					DOMES_BYPASS, 	
		//						��Խ������
		OVERFLY };
	//�뺽����Ե�״̬��û����ԡ���ʧ��ԡ�     �˹���ԡ�     �˹�ȥ��ԡ�    �Զ����	���Զ�ȥ���
	enum PAIR_STATUS{NOTCOUPLE=0, LOSSCOUPLE, MANUALCOUPLE, DEMANUALCOUPLE, AUTOCOUPLE, DEAUTOCOUPLE};
	enum RVSM_STATUS{
		RVSM_RVA = 0, 					//��׼RVSM����
		RVSM_RVN, 						//δ��׼RVSM����
		RVSM_RVX, 						//����RVSM����
		RVSM_RVU, 						//δ֪�Ƿ��׼RVSM����
		RVSM_RVT 						//��������/���ϵ�Ӱ��ȡ��RVSM
	};

	//��·��λ�����ͣ������ڣ�  ���㣬 ����㣬 ������
	enum RPP_TYPE { RPP_IN = 0, RPP_BPN, RPP_BPX, RPP_OUT};
	class FplListItemInfo
	{
	public:
		int m_nAcftID;
		std::string m_strMid;        //Ψһ��ʶ��
		int         m_nRowID;        //���������Ϣ��ʾ���к�

		std::string m_strType;
		std::string m_strACID;       //����
		std::string m_strSSR;        //������
		std::string m_strPSource;    //�ƻ���Դ
		std::string m_strPState;     //�ƻ�״̬
		std::string m_strHMIState;   //�˻�����״̬
		std::string m_strCouple;
		std::string m_strRadarID;
		std::string m_strTrackID;
		std::string m_strFplType;
		std::string m_strADDep;
		std::string m_strEtd;
		std::string m_strAtd;
		std::string m_strAddArr;
		std::string m_strETA;
		std::string m_strATA;
		std::string m_strCtrlSec;
		std::string m_strCurSec;
		std::string m_strAcpSec;
		std::string m_strNextSec;
		std::string m_strBPN;
		std::string m_strETN;
		std::string m_strBPX;
		std::string m_strETX;
	};

	//���мƻ���̬����
	struct ST_FDP_FLIGHTPLAN_STATIC
	{
		std::string curMID;         //�ƻ�ID:������[8]+�����[7/6]+��ɻ���[4]���������[4]

		//�ƻ�������Ϣ
		std::string CplDate;        //�ƻ�ִ������(������[8])
		PLAN_SOURCE	CplSrc;      	//�ƻ���Դ
		CPL_TYPE	CplType;	    //���мƻ�����

		//��������
		std::string CallSign;  	    //����
		std::string	ASSR;        	//ASSR��
		std::string FlyRule;     	//���й���
		std::string FlyType;     	//����������;
		short AcftNum;              //�ܴ�
		std::string AcftType;  	    //�ɻ�����
		short AcftClass;        	//�ɻ��������� 0 - A; 1 - B; 2 - C; 3 - C1; 4 - C2; 5 - C3...
		std::string Turbo;	      	//β��
		std::string AcftRegst;	    //�ɻ�ע���
		std::string SelSign;   	    //ѡ��
		std::string WirelessEp;		//���ߵ�ͨ���豸
		std::string SurveilEp;		//�����豸
		std::string SUP;	  		//�ƻ�������Ϣ
		std::string OTHER;    		//��ӦAFTN��18��������
		std::string OP_DATA; 	    //�����ϵ�OP_DATA��Ϣ

		//��ɽ�����Ϣ
		std::string ADDEP;	  	    //��ɻ���
		std::string ETD;	      	//Ԥ�����ʱ��
		std::string ADARR;	  	    //��ػ���
		std::string ALTN1;	  	    //��������1
		std::string ALTN2;     	    //��������2
		std::string EET;	      	//Ԥ�Ʒ���ʱ��
		std::string ETA;       	    //Ԥ�Ƶ���ʱ��
		//������Ϣ
		std::string TAS;	      	//Ԥ��Ѳ���ٶ�
		std::string RFL;	      	//Ԥ��Ѳ���߶Ȳ�
		std::string RouteStr;    	//�ƻ���·��
		std::string	BPN;            //����
		std::string	ETN;            //���ʱ��
		std::string	BPX;            //�����
		std::string	ETX;	     	//����ʱ��
		std::string GATE;     	    //ͣ��λ
		std::string ARWY;	      	//�볡�ܵ�	
		std::string DRWY;	      	//�볡�ܵ�
		std::string SID;	      	//��׼�볡����	
		std::string STAR;	      	//��׼��������
		std::string GlobalInfo;     //ȫ����Ϣ
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar, const unsigned int version)
		{
			return ar & curMID & CplDate & CplSrc & CplType & CallSign 
				& ASSR & FlyRule & FlyType & AcftNum & AcftType & AcftClass & Turbo 
				& AcftRegst & SelSign & WirelessEp & SurveilEp & SUP & OTHER 
				& OP_DATA & ADDEP & ETD & ADARR & ALTN1 & ALTN2 & EET & ETA
				& TAS & RFL & RouteStr & BPN & ETN &BPX & ETX & GATE & ARWY 
				& DRWY & SID & STAR & GlobalInfo; 
		}
	};
	//���̵���·��
	struct TAG_STRIP_POINT
	{
		char		Code[15+1];			//��·������
		RPP_TYPE	Type;				//��·��λ������ �������жϵ�Ϊ�����ڻ�������
		char		ETOP[4+2];			//����ʱ�䣨Ԥ��˵�ʱ��/ʵ�ʹ���ʱ�䣺���ݹ�������жϣ�
		char		PCL[4+2];			//����߶ȣ�Ԥ����ɸ߶ȣ�
		int			Speed;				//�ٶ�
		double		Longitude;          //����
		double		Lat;                //γ��
	};

	//���мƻ���̬����
	struct ST_FDP_FLIGHTPLAN_DYNAMIC
	{
		//�ƻ���־
		std::string CurMID;
		//�ƻ�������Ϣ
		time_t UpdateTime;              //����ʱ��
		PLAN_STATUS CplStatus;    		//�ƻ�״̬
		//��ɽ�����Ϣ
		std::string ATD;	     	    //ʵ�����ʱ��
		std::string ATA;       	        //ʵ�ʵ���ʱ��
		//������Ϣ
		std::string CurSec;		//��ǰ��
		std::string CtrlSec;    //������
		std::string AcpSec;		//�ƽ�������
		std::vector<std::string>	NextSecs;  	//��N��
		//������Ϣ
		std::string PRL;	      	    //����Ա������и߶�
		std::string CFL;	     	    //����Աָ�����и߶�
		std::string RouteStr;    	    //��·��
		std::string HoldPoint;  	    //HOLD������
		int HoldMinute;       	        //HOLDʱ��(����)
		std::string HoldTime;  	        //�뿪HOLD��ʱ��
		//�����Ϣ
		int TrackNo;		            //TRACK_NO,��ص�ϵͳ������,û�����ʱ��Ϊ-1
		PAIR_STATUS PairStatus;         //���״̬

		RVSM_STATUS rvsmStatus;     //RVSM״̬

		int pointSum;        		    //��·������
		int pointPassed;        	    //�ѹ���·���[�� 0 ����, -1��ʾδ����]
		//std::vector<TAG_STRIP_POINT> stripPoints;
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar & CurMID & UpdateTime & CplStatus & ATD & ATA & CurSec 
				& CtrlSec & AcpSec & NextSecs & PRL & CFL & RouteStr & HoldPoint
				& HoldMinute & HoldTime & TrackNo & PairStatus & rvsmStatus & pointSum 
				& pointPassed ; 
		}
	};

	//���мƻ� 
	struct ST_FDP_FLIGHTPLAN
	{
		ST_FDP_FLIGHTPLAN_STATIC staticFlightPlan;
		ST_FDP_FLIGHTPLAN_DYNAMIC dynamicFlightPlan;
	public:
		template<typename Archive>
		Archive& serialize(Archive& ar, const unsigned int version)
		{
			return ar & staticFlightPlan & dynamicFlightPlan; 
		}
	};

	//��·��ṹ
	struct TowerAirRoadStruct
	{
		char sBeacon[64];//����̨
		char sHeight[64];//�߶�
		char sSpeed[64];//�ٶ�
		TowerAirRoadStruct()
		{
			strcpy(sBeacon,"");
			strcpy(sHeight,"");
			strcpy(sSpeed,"");
		}
		TowerAirRoadStruct(const TowerAirRoadStruct& rhs)
		{
			strcpy(this->sBeacon,rhs.sBeacon);
			strcpy(this->sHeight,rhs.sHeight);
			strcpy(this->sSpeed,rhs.sSpeed);
		}
	};
	//���мƻ��ṹ
	struct TowerFlightPlanStruct
	{
		int				iFlightPlanId;					//���мƻ�id����RDPָ��
		char			sFlightNum[64];                     //���мƻ������
		char			sSSRCode[64];					/*  ������ */
		bool			bRVSM;							/* �Ƿ�߱�RVSM����*/
		int				iFlyPlanType;					/* ���мƻ�����,0���ۣ�1��� */
		char			sSectorName[64];				//����������
		char			sCompany[64];		            /* ���չ�˾ */
		char			sCallSign[64];					/* ���ţ����չ�˾+���ֱ��룩*/
		char			sDepDromeName[64];		        /* ��ɻ��� */
		char			sArrDromeName[64];       		/* ������� */
		char			sAlternateDrome[64];	        /* ������ */
		int				iCruiseLvl;						/* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
		int				iCruiseSpd;						/* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
		char			sArrRunway[64];					/* �����ܵ� */
		char			sDepRunway[64];                 /* ����ܵ�*/
		char			sWeight[64];		            /* ���� */
		char			sDepGate[64];		            /* �볡��ͣ��λ */
		char			sArrGate[64];		            /* ������ͣ��λ */
		char			sVacateLine[64];		        /* ����� */
		char			sInRunwayLine[64];              /* ����� */
		char			sDepartureTime[64];				/* Ԥ�����ʱ��*/
		char			sArrivalTime[64];		        /* Ԥ�Ƶ���ʱ��*/
		char			sSidName[64];                   /*�볡��������*/
		TowerAirRoadStruct	sAirRoadPoint;


		std::string toString(){

			char* buf=new char[BUFFERSZE];
			memset(buf,0,BUFFERSZE);
			sprintf(buf,"TowerFlightPlanStruct:[FlightPlanId:%d;FlightNum:%s;SSRCode:%s;RVSM:%d;FlyPlanType:%d;SectorName:%s;Company:%s;CallSign:%s;\
DepDromeName:%d;ArrDromeName:%d;AlternateDrome:%s;CruiseLvl:%d;CruiseSpd:%d;ArrRunway:%s;DepRunway:%s;Weight:%s;DepGate:%s;\
ArrGate:%s;VacateLine:%s;InRunwayLine:%d;DepartureTime:%s;ArrivalTime:%s;SidName:%s]",iFlightPlanId,sFlightNum,sSSRCode,bRVSM,iFlyPlanType,sSectorName,sCompany,sCallSign,
sDepDromeName,sArrDromeName,sAlternateDrome,iCruiseLvl,iCruiseSpd,sArrRunway,sDepRunway,sWeight,sDepGate,sArrGate,sVacateLine,sInRunwayLine,sDepartureTime,
sArrivalTime,sSidName);

			return buf;

		}
        
	
	};
	//Ŀ��ƻ�
	struct TowerObjectPlanStruct
	{
		ENUM_OBJ_TYPE   ObjType;						//����
		char			strSSrcode[64];					//�������мƻ��Ķ����룬�ͷ��мƻ���SSR����һ��
		double			dLongtitude;					//���ֵľ��ȣ���λ�����ȣ�
		double			dLatitude;           			//���ֵ�γ�ȣ���λ�����ȣ�
		double 			dAltitude;						//��ʼ�߶ȣ���׼��ѹ�߶ȣ���λ���ף�
		double 			dHeading;						//��ͷ���򣨵�λ�����ȣ�
		double 			dIAS;							//��ʼ�ٶȣ����٣���λs����/�룩
		char			sAppearTime[64];		        //����ʱ�䣨��λ���룩
		char			strModelType[64];				//������
		char			strRegNum[64];		            //ע���
		bool 			bEngineStart;					//�����Ƿ���

		std::string  toString(){

		char* buf=new char[BUFFERSZE];
	    memset(buf,0,BUFFERSZE);

		
	   sprintf(buf,"TowerObjectPlanStruct:[ObjType:%d;SSR:%s;Longtitude:%L;Latitude:%L;Altitude:%L;Heading:%L;IAS:%L;AppearTime:%s;ModelType:%d;RegNum:%d;EngineStart:%s;]"
		      ,static_cast<int>(ObjType),strSSrcode,dLongtitude,dLatitude,dAltitude,dHeading,dIAS,sAppearTime,strModelType,strRegNum,bEngineStart);
		return buf;

	}
	};
	//��̬�����ɻ���
	struct TowerAircraftPacketStruct
	{
		TowerObjectPlanStruct TowerobjFlight;	//Ŀ��ƻ� /* ����Ŀ��ƻ��ͷ��мƻ�һһ��Ӧ*/
		TowerFlightPlanStruct TowerplanFlight;	//���мƻ�
		std::string toString(){

			return TowerobjFlight.toString()+TowerplanFlight.toString();
		}
	};
	//ͣ��λ��Ϣ
	struct GateInformationStruct
	{
		QString     sGateName;//ͣ��λ��
		double		dLongtitude;//ͣ��λ���ȣ���λ�����ȣ�
		double		dLatitude; //ͣ��λγ�ȣ���λ�����ȣ�
		char	    sArrRunway[64];	/* �����ܵ� */
		char		sDepRunway[64];  /* ����ܵ�*/
		char		sDepGate[64];	/* �볡��ͣ��λ */
		char		sArrGate[64];	/* ������ͣ��λ */
		char		sVacateLine[64];/* ����� */
		char		sInRunwayLine[64];/* ����� */
	};
	////�����ݿ��ȡ������
	struct FlyPlanFromDBStruct
	{
		std::string			sFlyPlanNum;				 /*�����*/
		std::string		    sSSRCode;					 /*  ������ */
		bool			    bRVSM;					     /* �Ƿ�߱�RVSM����*/
		int				    iFlyPlanType;				/* ���мƻ�����,0���ۣ�1��� */
		std::string			sSectorName;				//����������
		std::string			sDepDromeName;		        /* ��ɻ��� */
		std::string			sArrDromeName;       		/* ������� */
		std::string			sAlternateDrome;	        /* ������ */
		int				    iCruiseLvl;					/* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
		int				    iCruiseSpd;					/* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
		std::string			sArrRunway;					/* �����ܵ� */
		std::string			sDepRunway;                 /* ����ܵ�*/
		std::string			sWeight;		            /* ���� */
		std::string			sDepartureTime;				/* Ԥ�����ʱ��*/
		std::string			sArrivalTime;		        /* Ԥ�Ƶ���ʱ��*/
		std::string         sADepTime;//ʵ�����ʱ��
		std::string         sAArrTime;//ʵ�ʵ���ʱ��
		std::string         sRegNum;                   /*�ɻ�ע���*/
		std::string         sModlType;				   /*������*/
		bool                bIsPlanFinished;          //�üƻ��Ƿ����
		FlyPlanFromDBStruct()
		{
		   bIsPlanFinished=false;
		}
	};

	//���Ʒɻ��˶��������Ľṹ��Ϣ
	struct ControlFlightStruct
	{
		int     sFlightNo;
		char	sNetCommand[64];//���Ʒɻ��˶�ָ��
	};
	//���ļ���ȡ�ķ��мƻ�����������ݽṹ
    struct FlyPlanStruct
	{
		
		QString	sSSRCode;/*  ������ */
		bool	bRVSM;	/* �Ƿ�߱�RVSM����*/
		int		iFlyPlanType;/* ���мƻ�����,0���ۣ�1��� */
		QString	sSectorName;//����������
		QString sPlane_ID;//�ɻ���ID(��Ϊ��ӵĲ��֣���Ϊ������������Ź���һ�ܷɻ������)
		QString sFly_ID;//�����
		QString sPlaneType;//�ɻ�����
		QString sDEPAp;//��ɻ���
		QString sARRAp;//��ػ���
		QString sAlterAp;//������
		QString sDEPTime;//���ʱ��
		QString sARRTime;//����ʱ��
		int		iCruiseLvl;	/* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
		int		iCruiseSpd;/* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
		QString	sArrRunway;	/* �����ܵ� */
		QString	sDepRunway;   /* ����ܵ�*/
		QString	sWeight;	/* ���� */
		QString sRegNum;   /*�ɻ�ע���*/
		QString sModlType;	 /*������*/
		QString sTeriminal;//��վ¥
		bool    bIsPlanFinished; //�üƻ��Ƿ����
		FlyPlanStruct()
		{
			iFlyPlanType=0;
		}
		
	};
	//RDP���ĳ����͸�Displayģ������ݰ����������Ƿɻ���ǰ��λ����Ϣ
	struct RDP_Display_Struct
	{
		int			 iPlanID;         //���мƻ�ID�������RDPStruct��iPlanID����һ��
		double		 dLongtitude;  //�ɻ���ǰ�ľ���
		double		 dLatitude;    //�ɻ���ǰ��γ�� 
		/*�ɻ�������Ϣ*/                                                                   
		std::string	 sSSRCode;	/*  ������*/                                   
		std::string  sPlanNum;    //�����                                          
		double 		 dIAS;		//�ٶȣ����٣���λs����/�룩               
		double 		 dAltitude;	//�߶ȣ���׼��ѹ�߶ȣ���λ���ף�            
		char		 strModelType[64];	//������    
	};
	class TaxiLine
	{
		int				m_iRoadId;		 //��·ID
		std::string		m_sRoadName;	 //��·����
		int				m_iFixPointID;	 //�̶���ID
		std::string		m_sFixPointName; //�̶�������
		double			m_dFixPoint_x;	 //�̶����x����
		double			m_dFixPoint_y;	 //�̶����y����
	public:
		void			SetRoadID(const int iRoadId) { m_iFixPointID = iRoadId;}
		void			SetRoadName(const std::string& sRoadName) {m_sRoadName = sRoadName;}
		void			SetFixPointID(const int iFixPointId) {m_iFixPointID = iFixPointId;}
		void			SetFixPointName(const std::string& sFixPointName) { m_sFixPointName = sFixPointName;}
		void			SetFixPoint_X(const double& dFixPoint_X)  {m_dFixPoint_x = dFixPoint_X;}
		void			SetFixPoiint_Y(const double& dFixPoint_Y) {m_dFixPoint_y = dFixPoint_Y;}
		int				GetRoadID(){return m_iRoadId;}
		std::string&	GetRoadName(){return m_sRoadName;}
		int				GetFixPointID(){return m_iFixPointID;}
		std::string&	GetFixPointName(){return m_sFixPointName;}
		double			GetFixPoint_X(){return m_dFixPoint_x;}
		double			GetFixPoint_Y(){return m_dFixPoint_y;}
       };
	/**************************************************************************
	   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
	  ����  ����: AircraftTrace
	  ����  �ߡ�: ����ƽ
	  ����  ����:1.0
	  ��������ڡ�:2014/12/28
	  ����  ����:  ���ļ���������AircraftTrace��������RDP����Displayģ��ĺ�����
	  ����  ����:   
	**************************************************************************/
	class AircraftPos

	{
		double			m_dLongtitude;  //�ɻ���ǰ�ľ���                                           
		double			m_dLatitude;    //�ɻ���ǰ��γ�� 
	public:
		AircraftPos(){}
		AircraftPos(const AircraftPos& rhs)
		{
			m_dLongtitude = rhs.m_dLongtitude;
			m_dLatitude = rhs.m_dLatitude;
		}
		void SetLongtitude(const double& dLongtitude){ m_dLongtitude = dLongtitude;}
		void SetLatitude(const double& dLatitude){m_dLatitude = dLatitude;}
		const double& GetLongtitude(){return m_dLongtitude;}
		const double& GetLatitude(){return m_dLatitude;}
	};
	class AircraftTrace
	{
		int				m_iPlanID;				//���мƻ�ID�������TowerAircraftPacketStruct��iPlanID����һ��                                                                                                                     
		std::string	    m_sSSRCode;	           /*  ������*/                                   
		std::string     m_sPlanNum ;           //�����
		double 		    m_dIAS;		          //�ٶȣ����٣���λs����/�룩               
		double 			m_dAltitude;	     //�߶ȣ���׼��ѹ�߶ȣ���λ���ף�            
		char			m_strModelType[64];	 //������ 
		std::vector<AircraftPos> m_vecTracePoint;//��ŷɻ����к����������
	public:
		void				SetPlanID(const int iPlanID){ m_iPlanID = iPlanID;}
		void				SetSSRCode(const std::string& sSSRCode){m_sSSRCode = sSSRCode;}
		void				SetPlanNum(const std::string& sPlanNum){m_sPlanNum = sPlanNum;}
		void				SetIAS(const double& dIAS){m_dIAS = dIAS;}
		void				SetAltitude(const double& dAltitude){ m_dAltitude = dAltitude;}
		void				SetModeType(const char* strModeType){strcpy(const_cast<char*>(strModeType),m_strModelType);}
		void				SetVecAircraftTrace(std::vector<AircraftPos>& vecTracePoint){ m_vecTracePoint = vecTracePoint;}
		const int			GetPlanID(){return m_iPlanID;}
		const std::string&  GetSSRCode(){return m_sSSRCode;}
		const std::string&  GetPlanNum(){return m_sPlanNum;}
		const double		GetIAS(){return m_dIAS;}
		const double		GetAltitude(){return m_dAltitude;}
		const char*			GetModeType(){return m_strModelType;}
		const std::vector<AircraftPos>& GetVecTracePoint(){return m_vecTracePoint;}
	};
	class FixPoint
	{
		int					m_iFixpointId;		//�̶���ID
		std::string			m_sFixpointName;	//�̶�������
		double				m_dFixpoint_X;		//X����
		double				m_dFixpoint_Y;		//Y����
		double				m_dFixpoint_Z;		//Z����
	public:
		void				SetFixPointID(const int iFixpointId){m_iFixpointId = iFixpointId;}
		void				SetFixPointName(const std::string& sFixPointName){m_sFixpointName = sFixPointName;}
		void				SetFixPointX(const double& dFixpoint_X){m_dFixpoint_X = dFixpoint_X;}
		void				SetFixPointY(const double& dFixpoint_Y){m_dFixpoint_Y = dFixpoint_Y;}
		void				SetFixPointZ(const double& dFixPoint_Z){m_dFixpoint_Z = dFixPoint_Z;}
		const int			GetFixPointID(){return m_iFixpointId;}
		const std::string&  GetFixPointName(){return m_sFixpointName;}
		const double&		GetFixPointX(){return m_dFixpoint_X;}
		const double&		GetFixPointY(){return m_dFixpoint_Y;}
		const double&		GetFixPointZ(){return m_dFixpoint_Z;}
	};
	struct SDPSTrack 
	{
		SDPSTrack::SDPSTrack(){}

		int									iTrackID;               ///< ����ID
		PublicDataStruct::ENUM_TRACKTYPE	TrackType;          ///< ��������
		int									iICAOAddr;             ///< ������ICAO��ַ
		double								dLongitude;         ///< ����������
		double								dLatitude;            ///< ������γ��
		int									iAltitude;		    ///< �߶� m
		PublicDataStruct::ENUM_AltitudeType	AltitudeType;       ///< �߶�����
		double								dGS;			  ///< GS km/h
		double								dTrackAngle;	 ///< ��������
		std::string							strSSR;          ///< �����״���
		std::string							strCallSign;    ///< ����������
		std::vector<std::string>			vecSensors;     ///< ��⵽�ú����Ĵ�������������, �����ڵ����Ӻ���ʱ�����ֶ�����
		bool								bSPIFlag;       ///< SPI��־
		int									Emergency;      ///< �����������
		PublicDataStruct::ENUM_OBJ_TYPE		ObjType;        ///< Ŀ������
		double								dROCD;          ///< �����½��ʣ�����Ϊ�����½�Ϊ����ƽ��Ϊ0

		//���л�
		template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar & iTrackID & TrackType & iICAOAddr & dLongitude & dLatitude & iAltitude &
				AltitudeType & dGS & dTrackAngle & strSSR & strCallSign & vecSensors & bSPIFlag & Emergency & ObjType & dROCD;
		}
	};
	//add by ����ƽ
	//�����ݿ��ȡ�ķ��мƻ�����
	struct SFlyPlanFromDB
	{
		std::string			sFlyPlanNum;				 /*�����*/
		std::string		    sSSRCode;					 /*  ������ */
		bool			    bRVSM;					     /* �Ƿ�߱�RVSM����*/
		int				    iFlyPlanType;				/* ���мƻ�����,0���ۣ�1��� */
		std::string			sSectorName;				//����������
		std::string			sDepDromeName;		        /* ��ɻ��� */
		std::string			sArrDromeName;       		/* ������� */
		std::string			sAlternateDrome;	        /* ������ */
		int				    iCruiseLvl;					/* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
		int				    iCruiseSpd;					/* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
		std::string			sArrRunway;					/* �����ܵ� */
		std::string			sDepRunway;                 /* ����ܵ�*/
		std::string			sWeight;		            /* ���� */
		std::string			sDepartureTime;				/* Ԥ�����ʱ��*/
		std::string			sArrivalTime;		        /* Ԥ�Ƶ���ʱ��*/
		std::string         sADepTime;                  //ʵ�����ʱ��
		std::string         sAArrTime;                  //ʵ�ʵ���ʱ��
		std::string         sRegNum;                   /*�ɻ�ע���*/
		std::string         sModlType;				   /*������*/
		bool                bIsPlanFinished;           //�üƻ��Ƿ����
		SFlyPlanFromDB()
		{
			bIsPlanFinished=false;
			bRVSM=true;//Ĭ������£�����RVSM����
			sAlternateDrome="ZUUU";//Ĭ�������ΪZUUU
			sModlType="B001";
			sWeight="M";
			sSSRCode="A1234";
		}
		std::string toString(){

			char* buf=new char[BUFFERSZE];
			memset(buf,0,BUFFERSZE);
			sprintf(buf,"SFlyPlanFromDB:[FlyPlanNum:%s;SSR:%s;RVSM:%d;FlyPlanType:%d;SectorName:%s;DepDromeName:%s;ArrDromeName:%s;AlternateDrome:%s;\
CruiseLvl:%d;CruiseSpd:%d;ArrRunway:%s;DepRunway:%s;Weight:%s;DepartureTime:%s;ArrivalTime:%s;ADepTime:%s;AArrTime:%s;\
RegNum:%s;ModlType:%s;IsPlanFinished:%d]",sFlyPlanNum.c_str(),sSSRCode.c_str(),bRVSM,iFlyPlanType,sSectorName.c_str(),sDepDromeName.c_str(),sArrDromeName.c_str(),
sAlternateDrome.c_str(),iCruiseLvl,iCruiseSpd,sArrRunway.c_str(),sDepRunway.c_str(),sWeight.c_str(),sDepartureTime.c_str(),sArrivalTime.c_str(),sADepTime.c_str(),
sAArrTime.c_str(),sRegNum.c_str(),sModlType.c_str(),bIsPlanFinished);

			return buf;
   
		}
	};
	//////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	//add by 2015.10.30
	const double BRAKE_FACTOR=0.6; //ɲ��������
	const double REVERSE_FACTOR=0.4;//����������
	const double AIRFRICTION_FACTOR=0.15; //������������
	const int RESPONSETIME=5;//��Ӧʱ��=������Ա��Ӧʱ��+��ʻԱ��Ӧʱ��+��Ϣ����ʱ�䣬��λ��
	

	//enum AIRCRAFT_TYPE{S=0,H=1,M=2};
	enum WAKE_INTERVAL{//β����������õ���FAAβ����׼
		//H�������ͻ���M�������ͻ���S����С�ͻ�
		//˫�����������϶������ͻ������ͻ�
		//β����׼ֻ�к������ڿ��е������ã����ڵ��滬��ʱ���򲻲��ô��ױ�׼
		HH=7400,HM=9260,HS=11110,MH=5560,MM=5560,MS=7400,SH=5560,SM=5560,SS=5560
	};
	enum TAX_INTERVAL{//���滬��β��������˹涨Ϊ����ʵ���趨ֵ�������Ǳ�׼�ο�
		HH1=700,HM1=900,HS1=1100,MH1=600,MM1=600,MS1=700,SH1=600,SM1=600,SS1=600
	};
	enum TAX_SPEED{
		HIGHEST_SPD=29,  //��߻���ʱ��29km/h
		NORMAL_SPD=24,   //��������ʱ��
		TURN_SPD=15,    //ת�们��ʱ��
		STOP_SPD=5		//����ͣ��ƺ�ĳ�ʼ����ʱ��
	};
	//enum AIRCRAFT_MASS{
	//	//�������������趨Ϊ�������������λΪǧ�ˣ���Ҫ�ǳɶ�˫�����õ�һЩ�ɻ�����
	//	B737=58604,		B733=52550,		B736=58604,		B738=66361,		B739=66361,		B763=136078,
	//	B764=158800,	B772=201800,	B773=237680,	B741=265300,	B742=285700,	B743=260320,
	//	B744=285764,	B783=158757,	B788=165561,	B789=185519,	B762=123377,	A342=275000,
	//	A343=192000,	A345=243000,	A346=256000,	A358=182500,	A359=202500,	A312=123500,
	//	A313=124000,	A318=56000,		A319=61000,		A320=63000,		A321=71500,		A332=180000,
	//	A333=185000,
	//};

	//enum AIRCRAFT_LENGTH{//��������λ����
	//	B737=32.18,	B733=32.18,	B736=31.42,	B738=38.02,	B739=40.67,	B763=55,
	//	B764=61.4,	B772=62.94,	B773=73.08,	B741=68.6,	B742=68.6,	B743=68.6,
	//	B744=68.6,	B783=55.9,	B788=55.9,	B789=62,	B762=48.51,	A342=59.42,
	//	A343=63.69,	A345=66.03,	A346=73.46,	A358=60.5,	A359=65.2,	A312=45.89,
	//	A313=45.89,	A318=31.45,	A319=33.84,	A320=37.57,	A321=44.5,	A332=58.37,
	//	A333=63.69
	//};
	//enum AIRCRAFT_WINGSPAN{//��չ����λ����
	//	B737=34.3,	B733=28.9,	B736=34.31,	B738=34.3,	B739=34.3,	B763=47.57,
	//	B764=51.82,	B772=60.9,	B773=60.9,	B741=60.93,	B742=60.93,	B743=60.93,
	//	B744=60.93,	B783=60,	B788=60,	B789=60,	B762=47.57,	A342=60.3,
	//	A343=60.3,	A345=60.3,	A346=60.3,	A358=61.1,	A359=61.1,	A312=43.89,
	//	A313=43.89,	A318=34.09,	A319=34.09,	A320=34.09,	A321=34.09,	A332=60.3,
	//	A333=60.3
	//};
	//enum AIRCRAFT_WAKE{//β����׼��H--���ͻ���M--���ͻ���S--���ͻ�
	//	M=0,H=1,
	//	B737=M,	B733=M,	B736=M,	B738=M,	B739=M,	B763=H,
	//	B764=H,	B772=H,	B773=H,	B741=H,	B742=H,	B743=H,
	//	B744=H,	B783=H,	B788=H,	B789=H,	B762=H,	A342=H,
	//	A343=H,	A345=H,	A346=H,	A358=H,	A359=H,	A312=H,
	//	A313=H,	A318=M,	A319=M,	A320=M,	A321=M,	A332=H,
	//	A333=H
	//};
	struct Aircraft{
		int  iTraceID;
		std::string sFlightNum;//����ţ�Ψһʶ��һ�ܺ�����
		std::string sWake;//β������
		std::string sType;//������
		double dLength;//������
		double dWingSpan;//��չ
		double dMass;//����
		double dCurTaxSpd;//��ǰ�����ٶ�
		double dBaseDistance;//������
		double dProtectDistance;//������
		double dAlarmDistance;//�澯��
		//double dX;//x����
		//double dY;//y����
		//double dAngle;//�Ƕ�
		double dSafeDistance;//������+������+�澯��
		bool   bStop;
		Aircraft(){
			bStop=false;
			if(sWake=="H")
				dProtectDistance=HS1;
			else if(sWake=="M")
				dProtectDistance=MS1;
			else if(sWake=="S")
				dProtectDistance=SS1;
			dSafeDistance+=dProtectDistance;
		}
	};
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	//===============================================================================
	/*
	*���µ����ݽṹ�������ڻ�����ײ�������ݽṹ��
	*��ײ��⣺�����ݿ��ж�ȡ�ڳ���������λ�ã����ͣ��ؼ��ߴ繹����㣻
	           ��ȡ�������ڲ�ͬ��������ʱ�İ�ȫ���๹�챣���㣻
	           ���ݺ��������ٶȣ����ܲ���ʵ�ָ澯��
	ÿ��һ��ʱ�䣬�жϺ�����֮��ĸ澯���Ƿ��н�����
	*/
	//β�����

	
}
Q_DECLARE_METATYPE(PublicDataStruct::ControlFlightStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerFlightPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerAirRoadStruct);
Q_DECLARE_METATYPE(PublicDataStruct::TowerObjectPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::GateInformationStruct);
Q_DECLARE_METATYPE(PublicDataStruct::FlyPlanStruct);
Q_DECLARE_METATYPE(PublicDataStruct::PLAN_TERMINATE);
#endif