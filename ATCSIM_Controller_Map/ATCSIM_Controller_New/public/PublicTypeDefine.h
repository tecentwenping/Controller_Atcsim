#ifndef _STRUCT_DEFINE_HEADER
#define _STRUCT_DEFINE_HEADER
/******************************************
���ܣ����ļ�������ʹ�õĽṹ������
*******************************************/

#include <vector>
#include <string>
using namespace std;

//����ִ��ģʽ
enum ENUM_EXECUTE_MODE
{
	EXCUTE_NONE=0,       //δ֪
	EXCUTE_ATONCE=1,     //����
	EXCUTE_AFTER=2,      //���뵱ǰ�����,��ɾ��֮�������״̬
	EXCUTE_QUEUED=3,     //��ӵ�����β
};

// �˶�Ŀ��ķ��ࣨ�ɻ���������
enum ENUM_OBJ_TYPE 
{
	OT_OBJ_NONE=0,         //δ֪����
	OT_PLANE,					//���÷ɻ�(��ֱ������)
	OT_HELICOPTER,			//ֱ����
	OT_VEHICLE,					//����
	OT_ENV,              
	OT_BIRD,						//��
	OT_CATTLE,					//ţ
	OT_DOG,						//��
	OT_BALLOON,				//����
	OT_SERVICE_CAR = 120,      //������
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

//����ϯ��������Ӧ
struct ContrlSectorMap
{
	int iCotrlId;      //����ϯλ��
	vector<string>  vSector;     //���Ƶ�����
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCotrlId & vSector; 
	}
};

//����ϯ�������Ӧ
struct ContrlPilotMap
{
	string iCotrlId;      //����ϯλ��
    vector<int> vPilot;      //���ƻ���ϯλ��
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iCotrlId & vPilot; 
	}
};

//����ϯλ����ɻ���Ӧ
struct PilotPlaneMap
{
	int iPilotId;     //����ϯλ��
	vector<int> vPlane;     //���Ʒɻ�ID
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iPilotId & vPlane; 
	}
};

//������ɻ���Ӧ
struct SectorPlaneMap
{
	string Sector;     //����
	vector<int> vPlane;     //���Ʒɻ�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & Sector & vPlane; 
	}
};

/** 
 \brief		������              
 \details  
 \author    
 \date      2013-06-03
*/
enum EM_CLOUD_TYPE
{
	DEFAULT_YUN,  //Ĭ�ϵ���
	CENG_YUN,     //����
	JUAN_YUN,     //����
	DAN_JI_YUN,   //������
	NONG_JI_YUN,  //Ũ����
	JIYU_YUN,      //������
};

//! �߶�����
enum ENUM_AltitudeType
{
	ALTTYPE_INVALID,
	ALTTYPE_QNE,    //��ѹ
	ALTTYPE_QFE,    //��ѹ�߶�
	ALTTYPE_QNH,   //��ѹ�߶�
};

//! ��������
enum ENUM_TRACKTYPE
{
	TRACKTYPE_INVALID,
	TRACKTYPE_INAIR,
	TRACKTYPE_ONGROUND,
};

//! �����������
enum ENUM_EMERGENCYTYPE
{
	EMERGENCY_INVALID = 0x00000000,
	EMERGENCY_RF = 0x00000001,
	EMERGENCY_EM = 0x00000002,
	EMERGENCY_HJ = 0x00000004,
};

//����ṹ
struct stPoint
{
   double dLongtitude;      //����,��λ:����
   double dLatitude;         //γ��,��λ:����
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & dLongtitude & dLatitude; 
	}
};

//!��������
enum ENUM_REPORT_TYPE
{
	RQ_REPORT = 1,  ///<��������౨��
	SEARCH_REPORT = 2, ///<��ѯ�౨��
	STANDARD_REPORT = 3, ///<��׼��̨����
	LVL_REACH_REPORT = 4, ///<�߶ȵ��ﱨ��
	ESTABLISHED_REPORT = 5, ///<ä��������
	PROCEDURE_REPORT = 6, ///<���̱��棬����FPLLIST�еı���
};

//!��ѹ����
enum ENUM_QNH_TYPE
{
    TYPE_QNE,    //��׼��ѹ
    TYPE_QNH,    //������ѹ
    TYPE_QFE,    //��ѹ
};
#endif