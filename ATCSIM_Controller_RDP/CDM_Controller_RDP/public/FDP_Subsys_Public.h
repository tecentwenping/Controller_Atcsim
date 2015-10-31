/*********************************************************************
 * Copyright(c) Reserved, WiseSoft Corporation.
 *   FileName: fdp_subsys_public.h
 *     Author: huangyu
 *  $Revision: 52 $ 
 *       Date: 2004/05/28
 *Description: FDP�����ϵͳ[FDP, FDD, FDO, FDPTEL]�����ṹ����
 ********************************************************************/

#ifndef _FDP_SUBSYS_PUBLIC_H_
#define _FDP_SUBSYS_PUBLIC_H_

#include <time.h>

#include "simple_type_def.h"
#include "base_type_def.h"
#include "radp_type.h"

#pragma	pack(2)

// --------------------------------
// ö�����Ͷ��� [���ֽ��з�������]
// --------------------------------

//�ƻ����޸ĵ����ݵȼ�(0:û�иı� 1:���������ݸı� 2: ״̬�ı� 4:ʱ�䡢�ٶȡ��߶ȸı� 8:��·���ı�)
enum PLAN_CHANGE{CH_NONE=0, CH_DESCRIPTION=1, CH_STATUS=2, CH_TIMESPEED=4, CH_ROUTESTRING=8};

// �ƻ���״̬:δ��(�յ�PLN)����ֹ(�յ�FPL)��Ԥ����(Ԥ�����ʱ��ǰ��Сʱ)��Э�����ƽ������ơ���ɡ�ȡ��
enum PLAN_STATUS{FUTR=0, NACT=1, PREA=2, COOR=3, HAND=4, CONT=5, FIN=6, CNL=7};

// �ƻ���AIDC״̬:��ʼ̬��   ֪ͨ��		��ʼЭ����	��Э�̡�	�ƽ�    �����
enum AIDC_STATUS{AIDC_NONE=0, INFORM=1, NEGOTIATE=2, AGAIN=3, TRANSFER=4, FINISH=5};


//����״̬(0=ȷ�� 1=���� 2=���� 3=�ȴ� 4=���� 5=�ƽ� 6=��� 7=�ⲿ���� 8=���� 9=���мƻ�ģ��)
enum TRACK_TYPE{CH_CONFIRM=0, CH_ATTEMPT=1, CH_COAST=2, CH_WATI=3, CH_SUSP=4, CH_HAND=5, CH_FINAL=6, CH_EXTERN=7,CH_EMERG=8,CH_SIMU=9};

// �������ͣ�δ֪��       ������-��ۡ�		 ������-��ۡ�		  ������-���ۡ�	   ������-���ۡ� �����ػ�(�ɳ�����)
enum CPL_TYPE{ UNKNOWN=0, EXTERNAL_INBD,	 DOMES_INBD,		  EXTERNAL_OUTBD,  DOMES_OUTBD,	 BYPASS,
//					   ������-����������ۡ� ������-�����������ۡ�������-��������֮����С�	���������������ػ�(�ɳ�����)						 
						 EXTERNAL_ADP_INBD,	 EXTERNAL_ADP_OUTBD,  DOMESTIC,					DOMES_BYPASS, 	
//						��Խ������
						 OVERFLY };
//�뺽����Ե�״̬��û����ԡ���ʧ��ԡ�     �˹���ԡ�     �˹�ȥ��ԡ�    �Զ����	���Զ�ȥ���
enum PAIR_STATUS{NOTCOUPLE=0, LOSSCOUPLE, MANUALCOUPLE, DEMANUALCOUPLE, AUTOCOUPLE, DEAUTOCOUPLE};

//���мƻ���Դ: ���ر༭, �ظ��Է��мƻ�, ���мƻ���,	ģ����мƻ��������
enum PLAN_SOURCE{LPL=0,   RPL=1,			TELE=2,		STL=3   , TAG = 4};


//���ĵ��˹�����״̬:	ֵ��δ����, ֵ���Ѵ���
enum DUTYSTATUS {		DUTY_NO = 0, DUTY_DONE };

//���ĵ�ϵͳ����״̬ --    �ձ�״̬�� ���Ľ����� ���Ľ����ɹ����ձ���Ԥ�ƻ����ձ���Ԥ�ƻ��ɹ���������ȷ����, ��ǿ�ƺ���, AIDC������Ӧ�߼���
enum FINSTATUS{			RECVSTATUS=0,  RESOLVE_ERR, RESOLVE_SUCC, RDISPOSE_ERR, RDISPOSE_SUCC, DISPOSE_SUCC,    ERRMSG_IGNORE, AIDCLOGIC_ERR,
// 						  ����״̬:	    �鱨����     �鱨�ɹ���  	������Ԥ�ƻ���������Ԥ�ƻ��ɹ�, ���ͳɹ��� ����ʧ��
			 			SENDSTATUS = 20, COMPOSE_ERR, COMPOSE_SUCC, SDISPOSE_ERR,   SDISPOSE_SUCC, SEND_SUCC,	SEND_FAILURE,
};


// ��̬��·������
// NDB-�޷����ű�̨��VOR-ȫ���ű�̨��VORLOC-VOR�ͺ���̨��ϣ�DME-���̨��VORTAC-VOR��������ϣ�VORDME-ȫ���ű���̨��
// VORDMET-�����Ƶ�VOR/DME��������TACAN-������NONE-����һ��ر�㣬LOC-����̨��ʾλ̨��AIRPORT������ZA �ϰ���, TEMP ��γ�ȱ�ʾ�ĵ�, �������
enum RPS_TYPE { NONE=0, REPORT, NDB, VORDME, VOR, DME, NDBDME, AIRPORT, VORLOC, VORTAC, VORDMET, TACAN, LOC, ZA, TEMP, AIRSPACE, HANDOVER};
	
//��̬��·������: һ��㣬��ɻ�����������������㡢����㡢�������������佻�㡢�볡�㡢�����㣬���ȵ�, ���ӵ�
enum RPD_TYPE {RPD_GEN = 0, RPD_DEP = 1 , RPD_ARR = 2, RPD_BPN = 4, RPD_BPX = 8, RPD_SECP=16,
		RPD_SID = 32, RPD_STAR=64, RPD_CORRIDOR=128, RPD_AIRWAY=256, RPD_FTYP=512, RPD_KTYP=1024,
		RPD_JTYP=2048, RPD_CTYP=4096, RPD_ATYP=8192, RPD_SURVTYP = 16384};

//��·��λ�����ͣ������ڣ�  ���㣬 ����㣬 ������
enum RPP_TYPE { RPP_IN = 0, RPP_BPN, RPP_BPX, RPP_OUT};

// ���ش������Ĵ���
// ����ʱ�뽫˵���ʹ������,�Ա����
enum ACK_NO
{
	// 0
	SUCCESS=0,                              // �ɹ�
	PLAN_NOT_FOUND,                         // ��Ӧ�ļƻ�δ�ҵ�
	NOT_FOUND,                              // δ�ҵ�
	ACCESS_DENIED,                          // û����Ӧ��Ȩ��
	STATUS_DENIED,                          // ���мƻ�״̬������
	FIELD_DENIED,                           // �ֶβ������޸�
	FIELD_ERROR,                            // �ֶ����ݴ���
	NOT_CURRENT,                            // �����������ݲ������µ�
	ACK_ERROR,                              // ʧ��

	// 11
	ERR_PLAN_NOT_EXIST = 11,                // �ƻ�������
	ERR_TRACK_NOT_EXIST,                    // ����������
	ERR_MID_REPEAT,                         // MID�ظ�
	ERR_OPTYPE,                             // ����Ĳ�������
	ERR_TIMEZONE_MISMATCH,                  // FDP ��  FIEP  ʱ����һ��
	ERR_NOT_CURRENT,                        // �����������ݲ������µ�
	ERR_OUT_OF_RANGE,						// ֵ������Χ
	ERR_FIELD,								// �ƻ����ֶδ���
	ERR_ACCESS_DENIED,						// û����Ӧ��Ȩ��
	ERR_STATUS_DENIED,						// ���мƻ�״̬������

	// 21
	// �ƻ��ֶδ���
	ERR_FIELD_EMPTY    = 21,                // �ֶβ�����Ϊ��
	ERR_FILED_MODIFY_DENIED,                // �ֶβ������޸�
	ERR_FIELD_FORMAT,                       // �ֶθ�ʽ����
	ERR_FIELD_OUT_OF_RANGE,                 // �ֶε�ֵ������Χ
	ERR_FIELD_LENGTH_OVERFLOW,              // �ֶεĳ��ȳ���
	ERR_FIELD_NOT_CHANGE,                   // �ֶ�������ͬ�������޸�

	// 41
	// �ֶ������ݿ����Ҳ���
	ERR_POINT_NOT_EXIST = 41,               // �㲻����
	ERR_ACFT_NOT_EXIST,                     // ���Ͳ�����
	ERR_HEIGHT_NOT_EXIST,                   // �˸߶Ȳ㲻����
	ERR_FLYCOURSE_NOT_EXIST,                // ��Ŀ������
	ERR_TELE_ADDR_NOT_EXIST,                // �ձ���ַ������
	ERR_FLYTASK_NOT_EXIST,                  // ���񲻴���
	ERR_ROUTE,								// ���߽�������
	ERR_TRAJECTORY_CALC,					// �켣����
	ERR_ACFT_SPEED,							// ����ȱ�ٶ�
	ERR_ACFT_CLASS,							// ����ȱ����

	// 61
	ERR_RPL_ALREADY_COMMIT = 61,            // �Ѿ��ύ (RPL)
	ERR_RPL_NO_MISSION,                     // ����û�мƻ�
	ERR_RPL_ERROR,                          // RPL �д��󣬲������ɼƻ�
	ERR_RPL_EXTRACT,                        // RPL �ύ���󣬲������ɼƻ�
	ERR_RPL_INPROCESSING,                   // �����ύȫ�� RPL��������Ӧ����
	ERR_RPL_NOT_EXIST,                      // RPL �ƻ�������
	ERR_RPL_SUBMIT_MODIFIED,                // �û��ύ���޸Ĺ��Ĺ̶�RPL,
	ERR_CITYROUTE_ACFT_MISMATCH,			// ���а���Ժ���û�жԸû��Ϳ���

	// 81
	// ���̵�������·ʱ�Ĵ���
	ERR_ROUTEPOINT_NUMBER = 81,             // ��·����ų��磬��˳��ߵ�
	ERR_ROUTEPOINT_MISMATCH,                // ��·������ƺ���Ų�һ��

	// 101
	// �˹���Դ������
	ERR_PLAN_ALREADY_COUPLED = 101,         // �ƻ��Ѿ����
	ERR_TRACK_ALREADY_COUPLED,              // �����Ѿ����
	ERR_NOT_COUPLED,                        // Ҫ��ȥ���ʱ�������ͼƻ�û�����

	// 121
	// SSR ����������
	ERR_SSR_MISMATCH      = 121,            // �����ͼƻ��� SSR ��һ��
	ERR_SSR_NOT_EXIST,                      // SSR ���벻����, �����ڱ��ص���Դ
	ERR_SSR_REPEAT,                         // SSR �����ظ�
	ERR_SSR_ASSIGN,							// SSR �������

	ERR_CALLSIGN          = 141             // �ɻ���ʶ����
};


enum REQ_PLAN_TYPE
{
	SINGLE_PLAN = 0,			// ����cpl_id,����һ���ƻ�
	DYNAMIC_TODAY,				// ���ն�̬
	DYNAMIC_TOMORROW,			// ���ն�̬
	DYNAMIC_ALL,				// ���мƻ�
//	LIST_PREDYNAMIC,			// ׼��̬�б�
//	LIST_TPITPO_DELAY,			// TPI/TPO�����б�
//	LIST_PREDEP,				// ���Э���б�
//	LIST_PREARR,				// ���Э���б�
//	LIST_ACTIVE,				// �����б�
//	LIST_WAIT,					// �ȴ��б�
//	LIST_HOLD,					// �����б�
//	LIST_ARR,					// ��½˳���б�
//	LIST_WATCH					// ���ӵ��б�
	DYNAMIC_CHKSUM = 50			//fdpsub use only
};

// DATA_ID �ƻ��ֶ�ö������
enum DATA_ID
{
	CPL_ID=0, MID, DATE_EXE, TIME_CREATED, ACID, TYPE, RELA_TYPE, CPL_SOURCE, STATUS,
	
	FLY_CLASS, FLY_COURSE, FLY_TASK, IS_INTERNATIONAL, IS_VIP, FLY_RULE, EQUIPMENT,	UNIT,
	WATCH,	COMMANDER, PILOT, PILOT_POST, PSN_NUM,	TOTAL_SORTIE, REAL_SORTIE, TURBO, 
	AIRCRAFT_STR,	HOLD_POINT_TYPE, REGIST_NO,	METO_STR, CALLSIGN, COMM_STR, COMMENT,
	
	CPLTYPE, AP_DEP, AP_DEP_LAT, AP_DEP_LONG, STID, RWAY_DEP, TIME_DEP_PLAN, TIME_DEP_EST,	
	TIME_DEP_REAL, AP_ARR,	STAR, RWAY_ARR,	TIME_ARR_PLAN, TIME_ARR_EST, TIME_ARR_REAL,	AP_ALT,	
	
	CTRL_STATUS, CTRL_SEC, CTRL_OPS,	NEXT_SEC, NEXT_OPS,	CUR_SEC, 
		
	TRACK_NO, PAIRSTATUS, SSR_CODE,
	
	TAS, RFL, RFL2,	AFL, AFL2, CFL,	HOLD_POINT,	HOLD_HEIGHT, TIME_HOLD,	TIME_RESUME,
	SUSP_POINT,	TIME_SUSP, ROUTE_STR, ROUTE_STR_ALT,ROUTE_STR_ALT_FLAG,	EET_BP,	BPN, ETN, 
	BPX, ETX, CUR_POINT_NO, PR_POINT_NO, TOTAL_POINT_NO, ROUTE_POINTS,
	
	QUASI_STATUS, QUASI_INFO, PLAN_REL_NO, PLN_REL,	DEP_REL_NO,	DEP_REL, ARR_REL_NO, ARR_REL,

	BPN_HEIGHT, BPX_HEIGHT, SUSP_HEIGHT,

	PRESTATUS, TIME_STATUS_CHANGED, IS_MAN_STATUS, PLAN_CHANGE_FLAG, NEED_RTCD, AP_DEP_HEIGHT
};


enum RVSM_STATUS{
	RVSM_RVA = 0, 					//��׼RVSM����
 	RVSM_RVN, 						//δ��׼RVSM����
 	RVSM_RVX, 						//����RVSM����
 	RVSM_RVU, 						//δ֪�Ƿ��׼RVSM����
 	RVSM_RVT 						//��������/���ϵ�Ӱ��ȡ��RVSM
};

// -------------------------------------------
// ϵͳ�ƻ������ķ��飬����ͷ�ṹ�����Ͷ���
// -------------------------------------------
//AIDC�����ƽ���λAIDC״̬[TAG_PLAN��֧��ͬһ���������������ƽ����]
struct TAG_AIDC_STATUS 
{
	char		ATCCode[10];		//���������ƽ���λ����
	AIDC_STATUS	AIDCStatus;			//AIDC�׶� 
	BYTE		ResStatus;			//��Ӧ״̬,��BITλ��ʾ,1Ϊ��Ӧ��,0Ϊ����Ӧ��:
									//0λ-Ӧ����Ӧ��1λ - ������Ӧ
	char		LastAIDCMsg[6];		//���һ��AIDC��������
	char		RSFlag;				//���һ��AIDC���ĵ��շ���־: r/R-�գ�s/S-��
	BYTE		IOFlag;				//�ƽ���/�ƽ�����־��1 - �Ӹù������Ʋ����ƽ��뱾���Ʋ���
									//					 2 - �ӱ����Ʋ����ƽ������ù������Ʋ���
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

//////////////////////////////////////////////////////////////////////////
//���мƻ� 
typedef struct TAG_PLAN
{      
	//�ƻ���־
    char        CurMID[29+1];		//�ƻ�ID:������[8]+�����[7/6]+��ɻ���[4]���������[4]
    //�ƻ�������Ϣ
    char    	CplDate[8+1+1];   	//�ƻ�ִ������(������[8])
	INT32  		UpdateTime;		    //����ʱ��
    PLAN_STATUS CplStatus;    		//�ƻ�״̬
	PLAN_SOURCE	CplSrc;      	    //�ƻ���Դ
	CPL_TYPE	CplType;	      	//��������
	//��������
	char		CallSign[8+1+1];  	//����		
	char		ASSR[5+1];        	//ASSR��	
	char		FlyRule[1+1];     	//���й���		
	char		FlyType[1+1];     	//����������;			                            
	short		AcftNum;           	//�ܴ�
	char		AcftType[4+1+1];  	//�ɻ�����      			
	short   	AcftClass;        	//�ɻ��������[1-A��,2-B��,3-C1��,4-C2��,5-C3��,6-C4��,7-D��,8-E��]
	char		Turbo[1+1];	      	//β��
	char		AcftRegst[12+1+1];	//�ɻ�ע���
	char    	SelSign[4+1+1];   	//ѡ��
	char		WirelessEp[30];		//���ߵ�ͨ���豸
	char		SurveilEp[30];		//�����豸
	char		SUP[40];	  		//�ƻ�������Ϣ
	char		OTHER[120];	    	//��ӦAFTN��18��������
	char		OP_DATA[10+1+1]; 	//�����ϵ�OP_DATA��Ϣ
	//��ɽ�����Ϣ
	char		ADDEP[4+1+1];	  	//��ɻ���
	char    	ETD[4+1+1];	      	//Ԥ�����ʱ��
	char    	ATD[4+1+1];	     	//ʵ�����ʱ��	
	char		ADARR[4+1+1];	  	//��ػ���
	char		ALTN1[4+1+1];	  	//��������1	                                
	char    	ALTN2[4+1+1];     	//��������2	                                
	char		EET[4+1+1];	      	//Ԥ�Ʒ���ʱ��
	char    	ETA[4+1+1];       	//Ԥ�Ƶ���ʱ��	                                
	char    	ATA[4+1+1];       	//ʵ�ʵ���ʱ��
    //������Ϣ
	char		CurSec[10+1];		//��ǰ��
	char   		CtrlSec[10+1];      //������
	char		AcpSec[10+1];		//�ƽ�������
	char    	NextSec[5][10+1];  	//��һ��
	//������Ϣ
	char		TAS[5+1];	      	//Ԥ��Ѳ���ٶ�
	char		RFL[5+1];	      	//Ԥ��Ѳ���߶Ȳ�
	char		PRL[5+1];	      	//����Ա������и߶�
	char		CFL[5+1];	     	//����Աָ�����и߶�
	char		RouteStr[420];    	//�ƻ���·��
	char		HoldPoint[15+1];  	//HOLD������
	int     	HoldMinute;       	//HOLDʱ��(����)
	char		HoldTime[4+1+1];  	//�뿪HOLD��ʱ��
	char		BPN[15+1];	     	//����
	char		ETN[4+1+1];	     	//���ʱ��
	char		BPX[15+1];	     	//�����
	char		ETX[4+1+1];	     	//����ʱ��
    char	    XFL[5+1];	      	//Э���ƽ�(���ӵ�)�߶�
    char		GATE[4+1+1];     	//ͣ��λ	
	char		ARWY[10+1];	      	//�볡�ܵ�	
	char		DRWY[10+1];	      	//�볡�ܵ�
	char		SID[15+1];	      	//��׼�볡����	
	char		STAR[15+1];	      	//��׼��������
	char 		GlobalInfo[10+2];   //ȫ����Ϣ[���ӽ��̵�ʹ��]
	BYTE		OtherStatus;		//�ƻ�����״̬,��BITλ��ʾ,1ΪTRUE,0ΪFALSE: 
									// 0λ-�ƻ���FPL��;1 - DLA; 2 - ALN; 3 - RTN
	//�����Ϣ
	WORD			TrackNo;		    //TRACK_NO,��ص�ϵͳ�״ﺽ����,û�����ʱ��Ϊ0xffff;
	WORD			TrackIndexAdsb;	    //TRACK_INDEX_ADSB,��ص�ϵͳADSB������,û�����ʱ��Ϊ0xffff;
    PAIR_STATUS		PairStatus;         //���״̬
	//�澯��Ϣ
	short			AlarmYAWType;       // ֵΪ0 - δ�澯; 0λΪ1 - ��ֱƫ���� 1λΪ1 - ����ƫ�� ; 
										// 2λΪ1 - ��δ��׼RVSM����Ŀ���CFLֵ�����ԽRVSM����ĸ澯	
	//AIDC��Ϣ
	TAG_AIDC_STATUS	AIDCStatus[2];		//AIDC�׶�
	//RVSM״̬
	RVSM_STATUS 	rvsmStatus;    
	//��·����Ϣ
	short			PntSum;        		//��·������
	short			PntPassed;        	//�ѹ���·���[�� 0 ����, -1��ʾδ����]
	TAG_STRIP_POINT	STRIP_POINT[15];
	short			s_FlightID;			//��¼����ID
}TAG_PLAN_STRIP;


// -------------------------------------------
//	�ƻ����Ϊ��̬/��̬������
// -------------------------------------------
struct TAG_STC_PLAN		/**��̬�ƻ�**/
{
	//�ƻ���־
    char        CurMID[29+1];
    //�ƻ�������Ϣ
    char    	CplDate[8+1+1];   	//�ƻ�ִ������
	PLAN_SOURCE	CplSrc;      	    //�ƻ���Դ
	CPL_TYPE	CplType;	      	//���мƻ�����
	//��������
	char		CallSign[8+1+1];  	//����		
	char		ASSR[5+1];        	//ASSR��	
	char		FlyRule[1+1];     	//���й���		
	char		FlyType[1+1];     	//����������;			                            
	short		AcftNum;           	//�ܴ�
	char		AcftType[4+1+1];  	//�ɻ�����      			
	short   	AcftClass;        	//�ɻ��������� 0 - A; 1 - B; 2 - C; 3 - C1; 4 - C2; 5 - C3...
	char		Turbo[1+1];	      	//β��
	char		AcftRegst[12+1+1];	//�ɻ�ע���
	char    	SelSign[4+1+1];   	//ѡ��
	char		WirelessEp[30];		//���ߵ�ͨ���豸 
	char		SurveilEp[30];		//�����豸
	char		SUP[40];	  		//�ƻ�������Ϣ
	char		OTHER[120];    		//��ӦAFTN��18��������
	char		OP_DATA[10+1+1]; 	//�����ϵ�OP_DATA��Ϣ
	//��ɽ�����Ϣ
	char		ADDEP[4+1+1];	  	//��ɻ���
	char    	ETD[4+1+1];	      	//Ԥ�����ʱ��
	char		ADARR[4+1+1];	  	//��ػ���
	char		ALTN1[4+1+1];	  	//��������1	                                
	char    	ALTN2[4+1+1];     	//��������2	                                
	char		EET[4+1+1];	      	//Ԥ�Ʒ���ʱ��
	char    	ETA[4+1+1];       	//Ԥ�Ƶ���ʱ��	                                
	//������Ϣ
	char		TAS[5+1];	      	//Ԥ��Ѳ���ٶ�
	char		RFL[5+1];	      	//Ԥ��Ѳ���߶Ȳ�
	char		RouteStr[420];    	//�ƻ���·��   
	char		BPN[15+1];	     	//����
	char		ETN[4+1+1];	     	//���ʱ��
	char		BPX[15+1];	     	//�����
	char		ETX[4+1+1];	     	//����ʱ��
    char	    XFL[5+1];	      	//Э���ƽ�(���ӵ�)�߶�
    char		GATE[4+1+1];     	//ͣ��λ	
	char		ARWY[10+1];	      	//�볡�ܵ�	
	char		DRWY[10+1];	      	//�볡�ܵ�
	char		SID[15+1];	      	//��׼�볡����	
	char		STAR[15+1];	      	//��׼��������
	char 		GlobalInfo[10+2];   //ȫ����Ϣ
};

struct TAG_DYN_PLAN		/**��̬�ƻ�**/
{
	//�ƻ���־
	char        CurMID[29+1];
    //�ƻ�������Ϣ
 	INT32  		UpdateTime;		    //����ʱ��
	PLAN_STATUS CplStatus;    		//�ƻ�״̬
 	//��ɽ�����Ϣ
	char    	ATD[4+1+1];	     	//ʵ�����ʱ��	
	char    	ATA[4+1+1];       	//ʵ�ʵ���ʱ��
   //������Ϣ
	char		CurSec[10+1];		//��ǰ��
	char   		CtrlSec[10+1];      //������
	char		AcpSec[10+1];		//�ƽ�������
	char    	NextSec[5][10+1];  	//��һ��
	//������Ϣ
	char		PRL[5+1];	      	//����Ա������и߶�	
	char		CFL[5+1];	     	//����Աָ�����и߶�                         	                                
	char		HoldPoint[15+1];  	//HOLD������
	int     	HoldMinute;       	//HOLDʱ��(����)
	char		HoldTime[4+1+1];  	//�뿪HOLD��ʱ��
	//�����Ϣ
	WORD		TrackNo;		    //TRACK_NO,��ص�ϵͳ������,û�����ʱ��Ϊ-1;
    PAIR_STATUS PairStatus;         //���״̬
	//�澯��Ϣ
	short		AlarmYAWType;       // ֵΪ0 - δ�澯; 0λΪ1 - ��ֱƫ���� 1λΪ1 - ����ƫ�� 	
									// 2λΪ1 - ��δ��׼RVSM����Ŀ���CFLֵ�����ԽRVSM����ĸ澯	
	short		PntSum;        		//��·������
	short		PntPassed;        	//�ѹ���·���[�� 0 ����, -1��ʾδ����]
	TAG_STRIP_POINT	STRIP_POINT[15];
};


// -------------------------------------------
//	�ƻ�������Ϣ��[�ַ���RDP��OUTTELL��ؽ���]
// -------------------------------------------
struct TAG_PLAN_BASE_INFO
{
	//�ƻ���־
    char        CurMID[29+1];		//�ƻ�ID:������[8]+�����[7/6]+��ɻ���[4]���������[4]
    //�ƻ�������Ϣ
    char    	CplDate[8+1+1];   	//�ƻ�ִ������(������[8])
    PLAN_STATUS CplStatus;    		//�ƻ�״̬
	CPL_TYPE	CplType;	      	//��������
	//��������
	char		CallSign[8+1+1];  	//����		
	char		ASSR[5+1];        	//ASSR��	
	char		FlyRule[1+1];     	//���й���		
	char		FlyType[1+1];     	//����������;			                            
	char		AcftType[4+1+1];  	//�ɻ�����      			
	char		AcftRegst[12+1+1];	//�ɻ�ע���
	char		WirelessEp[30];		//���ߵ�ͨ���豸 
	char		SurveilEp[30];		//�����豸
	//��ɽ�����Ϣ
	char		ADDEP[4+1+1];	  	//��ɻ���
	char		ADARR[4+1+1];	  	//��ػ���
	//������Ϣ
	char		CFL[5+1];	     	//����Աָ�����и߶�                         	                                
	//�����Ϣ
	WORD			TrackNo;		    //TRACK_NO,��ص�ϵͳ������,û�����ʱ��Ϊ0xffff;
	WORD			TrackIndexAdsb;	    //TRACK_INDEX_ADSB,��ص�ϵͳADSB������,û�����ʱ��Ϊ0xffff;
    PAIR_STATUS		PairStatus;         //���״̬
	//RVSM״̬
	RVSM_STATUS 	rvsmStatus;   
	//���״��ں���Ϣ
	WORD		LocalRadarTrack[MAX_FUSION_RADAR_NUM];	//�����ںϵĵ��״�ĺ����� ��Ч��TrackNo=0xffff
	 	
};

//���ռƻ�
struct TAG_TODAYPLAN
{
    int 	ID;
    char	PlanDate[10]; 					//�ƻ�ִ������
    char 	FlyRule[2];						//���й���
    char 	FlyType[2];						//��������
    char 	FlySubType[30];					//��������������д
	char	RVSM[2];						//�Ƿ����RVSM����
    char 	CallSign[10];	 				//�����
    char  	MID[30];						//���мƻ�MID����FDP������Ψһʶ���
    char 	Aircraftype[10];				//����
    char    Turbo[2];						//β��
    char 	PlaneRegCode[10]; 				//ע���
    char 	Equipment[60];	 				//�����豸
    char	SSR[6];							//Ӧ�������
    char	Addep[5]; 						//��ɻ���
    char	Adarr[5]; 						//��ػ���
    char	TAS[6]; 						//Ԥ��Ѳ���ٶ�
    char	RFL[6]; 						//Ԥ��Ѳ���߶Ȳ�
    char	ETD[5]; 						//Ԥ�����ʱ��
    char	TELETD[5]; 						//����Ԥ�����ʱ��
    char	ATD[5];							//ʵ�����ʱ��
    char	ETA[5]; 						//Ԥ�ƽ���ʱ��
    char	TELETA[5]; 						//����Ԥ�����ʱ��
    char	ATA[5]; 						//ʵ�ʽ���ʱ��
    char	EET[5]; 						//Ԥ�Ʒ���ʱ��
    char	ADALTN1[5]; 					//��������1
    char	ADALTN2[5]; 					//��������2
    char	Route[256]; 					//�ƻ���·��
    char	PlanStatus[10];	 					//״̬
    char	Remark[256];					//��ע
	char	Abnormality[32];				//������ԭ��
	char 	Airline[32];					//ִ�к��չ�˾
};

//���ı�ͷ�ṹTAG_TELE_HEADER
struct TAG_TELE_HEADER
{
	char    teleid[30];					//  ���ı�ʶ[��FinIDһ��]
	char	rsflag;						//	����/���ͱ�־: R/S
	char	linecode[6];				//	��/�����籨��·��
	char	serialno[6];				//	��ˮ��
	char	rank[4];					//	�籨�ȼ�
	char	rcvtime[8];					//	�ձ�ʱ��
	char	rcvaddr[370];				//	AFTN��ַ(28X8)��SITA��ַ(32X7)����ַ���ÿո����
	char	sndtime[8];					//	����ʱ��
	char	sndaddr[10];				//	������ַ
	char	msgtype[10];				//  ��������(AFTN,WEATHER,SITA,BUREAU,OTHER��AIDC)
	char	typestr[26];				//	AFTN/SITA�������ͣ��������Ϊ��һ������
	UCHAR   typechar;					// 
};

//����3 ���� -- �籨���
struct TAG_TELE_GR3
{	
	char	tele_type[3+1];				//�籨����
	char	tele_no[12+1+1];			//�籨���� �����һ���ֽ���Ϊ�˴ճ�ż���ֽ�,��ͬ.
	char	ref_data[12+1+1];			//�ο�����
};

//����5	���� -- �������˵��
struct TAG_TELE_GR5
{
	char	danger_class[8+1+1];		//Σ�յȼ�ALERFA(�澯) INCERFA(����) DETRESFA(����)
	char	tele_sign[8+1+1];			//�籨ǩ���� ��������+��λ����+���Ŵ���
	char	G5C[120+1+1];				//�������˵�����ģ������ݶ�120
};

//����7 ����-- ��������־��SSRģʽ�ͱ���
struct TAG_TELE_GR7
{	
	char	aircraft_id [8+1+1];		//�ɻ���ʶ
	char 	ssr_mode[1+1];				//SSRģʽ
	char	ssr_code[4+1+1];			//SSR����
};

//����8 ���� -- ���й�������
struct TAG_TELE_GR8
{	
	char	fly_rule[1+1];				//���й���
	char	fly_type[1+1];				//��������
};

//����9���� -- ��������Ŀ�����ͺ�β���ȼ�
struct TAG_TELE_GR9
{
	char 	aircraft_num[2+1+1];	    //��������Ŀ
	char 	aircraft_type[4+1+1];       //����������
	char	tail_stream[1+1];			//β���ȼ�
};

//����10���� -- �����豸
struct TAG_TELE_GR10
{	
	char	equipmenta[30];				//���ߵ�ͨ���豸
	char	equipmentb[30];				//�����豸
};

//����13���� -- ��ɻ�����ʱ��
struct TAG_TELE_GR13
{
	char	dep_airport[4+1+1];			//��ɻ���
	char	dep_time[4+1+1];			//Ԥ�ƻ�ʵ�����ʱ��
};

//����14���� -- Ԥ�Ʒ�Խ�߽�����
struct TAG_TELE_GR14
{
	char	location[30+1+1];			//λ�õ�
	char	est_fly_time[4+1+1];		//Ԥ�Ʒ�Խʱ��
	char	est_fly_height[5+5+1+1];	//Ԥ�Ʒ�Խ�߶Ȳ� ���������Խ���ݼ���Խ����
} ;

//����15���� -- ��·
struct TAG_TELE_GR15
{
	char	speed[5+1];					//Ѳ���ٶ�
	char	height[5+1];				//Ѳ���߶Ȳ�
	char	route[400+1+1];				//����, ���������ʽ�е�һ���ո��ַ�
};

//����16���� -- Ŀ�Ļ�����Ԥ�ƾ�����ʱ�䡢��������
struct TAG_TELE_GR16
{
	char	dest_airport[4+1+1];		//Ŀ�Ļ���
	char	est_flight_time[4+1+1];	    //Ԥ�Ʒ�����ʱ��,����һ���ո�
	char	standby_airport[4+1+4+1];	//��������
};

//����17���� -- ��ػ�����ʱ��
struct TAG_TELE_GR17
{
	char	landing_airport[4+1+1];		//��ػ���
	char	landing_time[4+1+1];		//ʵ�����ʱ��
	char	airport_name[32+1+1];	    //����ػ�����ʹ��ZZZZʱ����˴������Ӣ��ȫ��
};

//����18���� -- �����鱨
struct TAG_TELE_GR18
{
	char	EET[20+1+1];				//EET/�ۼƵ�Ԥ�ƾ�����ʱ�䣬����һ���ո���������
	char	RIF[300+1+1];				//RIF/�����򱸽�ʱ���º�·������������
	char	REG[32+1+1];				//������ע���־
	char	SEL[10+1+1];				//SEL/ѡ����б��룬����9
	char	OPR[32+1+1];				//OPR/Ӫ���ˣ�����17
	char	STS[64+1+1];				//STS/�������������ʱ������Ҫ��д
	char	TYP[64+1+1];				//TYP/�ɻ����������ͣ���G9ab��ȫʱ��д
	char	PER[64+1+1];				//PER/���涨��д��������������
	char	COM[32+1+1];				//COM/����ͨѶ�豸
	char	DAT[10+1+1];				//�������������йص���Ҫ����
	char 	NAV[64+1+1]; 				//NAV/ �뵼���豸�йص���Ҫ����
	char	DEP[32+1+1];				//DEP/��ɻ���ȫ�ƣ�G13aΪZZZZʱ��д��
	char	DEST[32+1+1];				//DEST/Ŀ�Ļ���ȫ�ƣ�G16aΪZZZZʱ��д��
	char	ALTN[2*32+1+1]; 		//ALTN/Ŀ�ĵر���������Ӣ��ȫ��
	char	RALT[2*32+1+1];   	//��·��������Ӣ��ȫ��
	
	char	PBN[32+1+1];				//���򵼺���/�����赼�����ܵ�����
	char	SUR[32+1+1];				//10a ��δע���ļ�����;������
	char	DOF[10+1+1];				//�������������6 λ����ʾ��YYMMDD��YY ��ʾ�꣬MM ��ʾ�£�DD ��ʾ�գ�
	char	CODE[10+1+1];				//���йؿ��н�ͨ���񵱾�Ҫ��ĺ�������ַ (��6 λ16 �����ַ�����ĸ������ʽ��ʾ)
	char	DLE[32+1+1];				//��·�����ȴ�������ƻ���������ĺ�·��Ҫ�㣬�����ʱ�֣�Сʱ���ӣ�4 λ����ʾ���󳤶ȡ�
	char	ORGN[32+1+1];				//����޷�����ʶ����мƻ������ˣ������йؿ��н�ͨ���񵱾�Ҫ��ķ����˵�8 ��ĸAFTN��ַ�������������ϸ�ڡ�
	char	TALT[32+1+1];				//��Doc 7910 ���ļ����������롷�Ĺ涨������ɱ��������Ĺ�������֯���ִ��롣
	
	char	RMK[400+1+1];				//RMK/���ﱸע
};

//����19���� - �����鱨 19,20,21�ṹ���ֶ���Ӧ��籨��ʽ����ͳһ
struct TAG_TELE_GR19
{
	char	E[4+1+1];					//E/ ���4λ���ֱ�ʾȼ�ϳ���ʱ�䣬����һ���ո�
	char	P[3+1];						//P/ ���1~3λ���ֱ�ʾ������������һ���ո��������ơ�
	char	R[6+1+1];					//R/ ���1-3���ַ�����ʾ����ͨ���豸
	char	S[6+1+1];					//S/ ���1-4���ַ�����ʾ�����豸����
	char	J[6+1+1];					//J/ ���1-4���ַ�����ʾ���������
	char	D[32+1+1];					//D/ �����������Ŀ����ʾ��Ƥͧ���
	char	A[64+1+1];					//A/ �����������Ŀ����ʾ�ɻ���ɫ�ͱ�־���
	char	N[64+1+1];					//N/ ��������ִ���˵���������ؾ����豸�����ñ�ע	
	char	C[32+1+1];					//C/ �����������
};

//����20���� -- ��Ѱ�;�Ԯ�澯�鱨
struct TAG_TELE_GR20
{
	char	A[32+1+1];					//Ӫ���˴��ţ�����һ���ո�,��������
	char	B[20+1+1];					//���һ��˫����ϵ�ĵ�λ
	char	C[4+1+1]; 					//���һ��˫����ϵʱ��
	char	D[20+1+1];					//���һ����ϵ����/����Ƶ��
	char	E[34+1+1];					//��󱨸�λ�ü���Խλ�õ��ʱ��
	char	F[64+1+1]; 					//ȷ�������֪λ�õķ���������������
	char	G[64+1+1];					//���浥λ��ȡ���ж�������������
	char	H[64+1+1];					//�����й�����
};

//����21 -- ���ߵ�ʧЧ�鱨
struct TAG_TELE_GR21
{	
	char	A[4+1+1];					// ���һ��˫����ϵʱ��, ����һ���ո�,��������
	char	B[20+1+1]; 					// ���һ����ϵ����/����Ƶ��
	char	C[30+1+1];					// ��󱨵�λ�ã�λ�õ�
	char	D[4+1+1];					// ��󱨸�λ�õ�ʱ��
	char	E[64+1+1];					// �д�ͨ������
	char	F[64+1+1];		    		// ��Ҫ˵��
};

//����22���� [�䳤�ṹ�����水������������ж�Ӧ�ķ���ṹ]
struct TAG_TELE_GR22
{
	char	revise_data[300];			//22��������[��Ҫ�����鱨]
	int		revise_sum;					//�޶��ķ�������
	int		revise_groupno[16];			//�����
//	TAG_TELE_GR3~22 [];
};

//�漰TAG_GROUP�ṹ�������[��:TAG_FDPTEL_AFTNGROUP]���ڱ���22�䳤����Ϊ�䳤�����
struct TAG_GROUP
{	
	char				fly_fcast_date[8];  //����Ԥ�����ڣ�ֻ����PLN��COR��ABS��,SITA���౨��
	TAG_TELE_GR3    	G3;					//G3����	
	TAG_TELE_GR5		G5;					//G5����	
	TAG_TELE_GR7		G7;					//G7����	
	TAG_TELE_GR8		G8;					//G8����
	TAG_TELE_GR9		G9;					//G9����
	TAG_TELE_GR10		G10;				//G10����
	TAG_TELE_GR13		G13;				//G13����
	TAG_TELE_GR14		G14;				//G14����
	TAG_TELE_GR15		G15;				//G15����
	TAG_TELE_GR16		G16;				//G16����
	TAG_TELE_GR17		G17;				//G17����
	TAG_TELE_GR18		G18;				//G18����
	TAG_TELE_GR19		G19;				//G19����
	TAG_TELE_GR20		G20;				//G20����
	TAG_TELE_GR21		G21;				//G21����
	TAG_TELE_GR22		G22;				//G22����
};

//SITA�������ṹ
//���𽵶κ����������
struct TAG_SITA_MUTIDEPARR
{
	char				ADDEP[6];			//��ɻ���[4����,��"ZUUU"]
	char				ETD[6];				//Ԥ�����ʱ��
};
struct TAG_SITA_GROUP
{
	char				FlightDate[10];		//�ƻ�ִ�����ڣ�4λ����[MMDD]
	char				CallSign[128];		//�����[AFTN���ĺ���Ÿ�ʽ,��"CCA4181"]
											//�ຽ���ÿո���[����ǹ淶�����д��ڶຽ������]
	char				RegstNo[8];			//�ɻ�ע���
	char				TaskPro[8];			//��������[PLN��ʹ��]
	char				ADDEP[6];			//��ɻ���[4����,��"ZUUU"]
	char				ADARR[6];			//�������[4����,��"ZBAA"]
	char				ETD[6];				//Ԥ�����ʱ��
	char				ETA[6];				//Ԥ�ƽ���ʱ��
	char				ATD[6];				//ʵ�����ʱ��
	char				ATA[6];				//ʵ�ʽ���ʱ��
	TAG_SITA_MUTIDEPARR mutiDepArr[4];		//���𽵶κ����������[��������PLNʹ��]
	char				PutDownTime[6];		//���ֵ�ʱ��
	char				PutOnTime[6];		//���ֵ�ʱ��
	char				NextRptTime[6];		//�´�ͨ��ʱ��[��������ʹ��]
	char				DLReason[64];		//����ԭ��[�������\���󡢳�������ʹ��]
	unsigned short		DLTime;				//���������[�������ʹ��]
	unsigned short		NumofAircrew;		//��������
	char				Weahter[10];		//������׼
	char				SupInfo[128];		//SI������Ϣ
};

#ifdef AIX
#pragma	pack(pop)
#else
#pragma	pack()
#endif

#endif
