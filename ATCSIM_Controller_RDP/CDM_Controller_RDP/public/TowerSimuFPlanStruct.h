/************************************************************************/
/* Author: ���Ŀ�
   Time:2014.2.23
   Description:TowerSimuFPlanStruct.h�ļ���Ҫ��������̨ģ����з��мƻ��Լ�
   Ŀ��ƻ��Ľṹ��Ϣ��������Ŀ��ƻ�����мƻ���һ��һ�Ĺ�ϵ��StructConstParam.h
   �ļ��ж����FDO���мƻ��ṹFlightPlanStructҪ��AircraftPacketStruct�ṹ���ϣ�
   ׼ȷ��˵��Ҫ��FlightPlanStruct�ṹ��Ϣ���뵽AircraftPacketStruct�У���Ϊֻ��
   AircraftPacketStruct�Ľṹ��Ϣ���͵���ʾ�ն��Ժ󣬲�����ʾ����Ӧ�ĺ��ࡣ
*/
#ifndef _TOWERSIMUFPLANSTRUCT_H_
#define _TOWERSIMUFPLANSTRUCT_H_
#include <QObject>
#include <QString>
#include <vector>
#include <QMetaType>
using std::vector;

namespace TowerSimuSpace{

	const int	SENDFLIGHTPLANUDPPORT	= 10000;//���ͷ��мƻ���UDP�˿ں�
	const int	SENDPACKETUDPPORT		= 10001;//���ͱ��ĵ�UDP�˿ں�
	const int	SENDCOMMANDUDPPORT		= 9901; //���������UDP�˿ں�
	const int	RECVFLIGHTPLANIDPORT	= 9902; //���պ���ID��UDP�˿ں�
	const double Pi = 3.14159265358979323846;

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

	struct FlightPlanInfo
	{
		bool m_autoTakeof;
		int  m_arrRunway_id;
		int  m_depRunway_id;
		int  m_depGate_id;
		int  m_arrGate_id;
		int  m_vacateLine_id;
		int  m_inRunway_id;
		int  m_sector_id;
	};
	struct TowerObjectPlanStruct
	{
		ENUM_OBJ_TYPE   ObjType;						//����
		char			strSSrcode[64];					//�������мƻ��Ķ�����
		double			dLongtitude;					//���ֵľ��ȣ���λ�����ȣ�
		double			dLatitude;           			//���ֵ�γ�ȣ���λ�����ȣ�
		double 			dAltitude;						//��ʼ�߶ȣ���׼��ѹ�߶ȣ���λ���ף�
		double 			dHeading;						//��ͷ���򣨵�λ�����ȣ�
		double 			dIAS;							//��ʼ�ٶȣ����٣���λs����/�룩
		char			sAppearTime[64];		        //����ʱ�䣨��λ���룩
		char			strModelType[64];				//������
		char			strRegNum[64];		            //ע���
		bool 			bEngineStart;					//�����Ƿ���
	};
	//��·��ṹ
	struct TowerAirRoadStruct
	{
		char sBeacon[64];//����̨
		char sHeight[64];//�߶�
		char sSpeed[64];//�ٶ�
	};
	//���мƻ��ṹ
	struct TowerFlightPlanStruct
	{
		int				iFlightPlanId;					//���мƻ�id
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
	};
	//��̬�����ɻ���
	struct TowerAircraftPacketStruct
	{
		TowerObjectPlanStruct TowerobjFlight;	//Ŀ��ƻ� /* ����Ŀ��ƻ��ͷ��мƻ�һһ��Ӧ*/
		TowerFlightPlanStruct TowerplanFlight;	//���мƻ�

	};
   
	//���Ʒɻ��˶��������Ľṹ��Ϣ
	struct TowerControlFlightStruct
	{
		int		sFlightNo;
		char	sNetCommand[64];//���Ʒɻ��˶�ָ��
	};
	
}

Q_DECLARE_METATYPE(TowerSimuSpace::FlightPlanInfo);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerFlightPlanStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerAirRoadStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerObjectPlanStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerAircraftPacketStruct);
Q_DECLARE_METATYPE(TowerSimuSpace::TowerControlFlightStruct);
#endif