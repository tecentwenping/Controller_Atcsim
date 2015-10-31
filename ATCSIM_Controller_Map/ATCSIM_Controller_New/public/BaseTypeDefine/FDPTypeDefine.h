#ifndef _FDP_TYPE_DEFINE_HEADER
#define _FDP_TYPE_DEFINE_HEADER

#include <string>
#include <vector>

//�ɻ����
enum ACFT_CLASS_TYPE
{
    ACFT_UNKNOWN = 0,
    ACFT_A, 
    ACFT_B, 
    ACFT_C1, 
    ACFT_C2, 
    ACFT_C3, 
    ACFT_C4, 
    ACFT_D, 
    ACFT_E
};

//���мƻ����
enum PLAN_CLASS
{
    PLAN_CLS_NORMAL = 0,
    PLAN_CLS_TAG
};

//�ƻ����޸ĵ����ݵȼ�
enum PLAN_CHANGE
{
    CH_NONE = 0,        //û�иı�
    CH_DESCRIPTION = 1, //���������ݸı�
    CH_STATUS = 2,      //״̬�ı�
    CH_TIMESPEED = 4,   //ʱ�䡢�ٶȡ��߶ȸı�
    CH_ROUTESTRING = 8, //��·���ı�
    CH_CREATE = 16,     //�ƻ�����
    CH_DELETE = 32      //�ƻ�ɾ��
};

//�ƻ���״̬
enum PLAN_STATUS
{
    FUTR = 0, //δ��(�յ�PLN)
    NACT,     //��ֹ(�յ�FPL)
    PREA,     //Ԥ����(Ԥ�����ʱ��ǰ��Сʱ)
    COOR,     //Э��
    HAND,     //�ƽ�
    CONT,     //����
    FIN,      //���
    CNL       //ȡ��
};

//�뺽����Ե�״̬
enum PAIR_STATUS
{
    NOTCOUPLE = 0,  //û�����
    LOSSCOUPLE,     //��ʧ���
    MANUALCOUPLE,   //�˹����
    DEMANUALCOUPLE, //�˹�ȥ���
    AUTOCOUPLE,     //�Զ����
    DEAUTOCOUPLE    //�Զ�ȥ���
};

// ��������
enum CPL_TYPE
{ 
    UNKNOWN=0,      //δ֪
    EXTERNAL_INBD,	//������-���
    DOMES_INBD,     //������-���
    EXTERNAL_OUTBD, //������-����
    DOMES_OUTBD,    //������-����
    BYPASS,         //�����ػ�(�ɳ�����)						 

    EXTERNAL_ADP_INBD,  //������-�����������
    EXTERNAL_ADP_OUTBD, //������-��������֮�����
    DOMESTIC,           //���������������ػ�(�ɳ�����)	
    DOMES_BYPASS,

    OVERFLY             //��Խ������
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

enum RVSM_STATUS
{
    RVSM_RVA = 0,   //��׼RVSM����
    RVSM_RVN,       //δ��׼RVSM����
    RVSM_RVX,       //����RVSM����
    RVSM_RVU,       //δ֪�Ƿ��׼RVSM����
    RVSM_RVT        //��������/���ϵ�Ӱ��ȡ��RVSM
};

//��·��λ������
enum RPP_TYPE
{
    RPP_IN = 0, //������
    RPP_BPN,    //����
    RPP_BPX,    //�����
    RPP_OUT     //������
};

//���̵���·��
struct TAG_STRIP_POINT
{
    std::string Code;      //��·������
    RPP_TYPE	Type;	   //��·��λ������ �������жϵ�Ϊ�����ڻ�������
    std::string ETOP;      //����ʱ�䣨Ԥ��˵�ʱ��/ʵ�ʹ���ʱ�䣺���ݹ�������жϣ�
    std::string PCL;       //����߶ȣ�Ԥ����ɸ߶ȣ�
    int         Speed;     //�ٶ�
    double      Longitude; //����
    double      Lat;       //γ��

public:
    template<typename Archive>
    Archive& serialize(Archive& ar, const unsigned int version)
    {
        return ar & Code & Type & ETOP & PCL & Speed & Longitude & Lat; 
    }
};

//�����ƽ�������
enum ENUM_HANDOVER_TYPE
{
    HANDOVER_NONE = 0,     //δ֪
    HANDOVER_START,        //�����ƽ�
    HANDOVER_CANCEL,       //ȡ���ƽ�
    HANDOVER_ACCEPTE,      //�����ƽ�
    HANDOVER_REFUSE,       //�ܾ��ƽ�
    HANDOVER_RELEASE,      //�ͷſ���
    HANDOVER_FORCE,        //ǿ�ƽӹ�
}; 

enum ENUM_FLIGHTPLAN_OPERRTYPE
{
    FLIGHTPLAN_ADD = 0,    //���ӷ��мƻ�
    FLIGHTPLAN_MODIFY      //�޸ķ��мƻ�
};

//�ȴ�����
enum ENUM_HOLD_TYPE
{
    HOLD_START = 0,     //��ʼ�ȴ�
    HOLD_END            //�����ȴ�
};

//�ֶ����/ȥ���
enum ENUM_COUPLE_INFO
{
    COUPLE = 0,     //���
    DECOUPLE        //ȥ���
};

//����Ʋ���
enum ENUM_TAG_TYPE
{
    TAG_ADD = 0,   //����
    TAG_DELETE,    //ɾ��
    TAG_MODIFY     //�޸�
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
    std::vector<TAG_STRIP_POINT> stripPoints;
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & CurMID & UpdateTime & CplStatus & ATD & ATA & CurSec 
            & CtrlSec & AcpSec & NextSecs & PRL & CFL & RouteStr & HoldPoint
			& HoldMinute & HoldTime & TrackNo & PairStatus & rvsmStatus & pointSum 
            & pointPassed & stripPoints; 
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

#endif //_FDP_TYPE_DEFINE_HEADER