#pragma once
#include "serial_base.h"
#include <string>
#include <vector>
//#include "Global_Struct.h"
#include "DataObj/dataobjs.h"
#include "BaseTypeDefine/PublicTypeDefine.h"
#include "Serialization/wserialize.h"
#include "DataObj/trainplan_data_objs.h"


#define MESSAGE_SIZE_LEN				(30 * 1024)
#define MAX_VALUE_WS 600000000 //���������ֵ
#define MIN_VALUE -600000000//������С����ֵ


struct Trace 
{
	Trace::Trace(){}
	Trace::Trace(int arg_attitude, int arg_gas, int arg_ias, float arg_heading,
		float arg_fAbsX, float arg_fAbsY, unsigned char arg_byAtt,
		int arg_ID, int arg_PlanID, std::string arg_szName,std::string arg_strSSR,bool arg_bHide) :
	attitude(arg_attitude),
	gas(arg_gas),
	ias(arg_ias),
	heading(arg_heading),
	fAbsX(arg_fAbsX),
	fAbsY(arg_fAbsY),
	byAtt(arg_byAtt),
	ID(arg_ID),
	PlanID(arg_PlanID),
	szName(arg_szName),
	strSSR(arg_strSSR),
	bHide(arg_bHide)
	{

	}
	int attitude;		//�߶�		Unit : m
	int gas;			//GAS		Unit : km/h
	int ias;			//IAS		Unit : km/h
	float heading;		//����		Unit : centigrade
	float fAbsX;		//����λ��x	Unit : km. Absolute position of aircraft.
	float fAbsY;		//����λ��y	Unit : km. Absolute position of aircraft.
	unsigned char byAtt;//��̬attitude��: cruising , 1: climb ; 2: decent
	int ID;//�Ի�����objID��sdd�Ǻ�����;
	int PlanID;//�Ի����Ƿ��мƻ�ID
	std::string szName;
	std::string strSSR;
	bool bHide; //�Ƿ�����
	ENUM_STATE_TYPE	eStateType;	//�ɻ�״̬��׹�١���������ȴ����ȵȴ������С���ɡ��ڿ��С������
	bool bRVSM; //��ǰ�ɻ��Ƿ�߱�RVSM������
	double dCDR; //���������ʣ������½���
	ENUM_OBJ_TYPE m_type;
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & attitude & gas & ias & heading 
			& fAbsX & fAbsY & byAtt 
			& ID & PlanID &szName & strSSR &bHide & eStateType & bRVSM & dCDR & m_type;
	}
};

class TracePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TracePacket);

public:
	Trace m_trce;
private:
	SERIALIZE_PACKET(m_trce)
};

//��������
class TimePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TimePacket);
public:
	int hour;
	int minute;
	int second;
	int msec;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();
	SERIALIZE_PACKET(hour & minute & second & msec)
};

class CTestPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CTestPacket);

public:
	std::string  m_msg;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

struct ST_ObjID
{
	int iObjID;
	std::string strName;
};

class InitPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitPacket);

public:
	int  m_AircraftNum;
	std::vector <ST_ObjID> m_vObjIDs;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class TraceArrayPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TraceArrayPacket);

public:
	int hour;
	int minute;
	int second;
	int msec;
	std::vector<Trace> m_vTrace;
private:
	SERIALIZE_PACKET(hour & minute & second & msec & m_vTrace)
};

//��ȡlua�ű����ӷɻ�ʱ����client����ʾ�������ݰ���������������
class ProAddPlanePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ProAddPlanePacket);
public:
	//int m_FlyPlanNum;
	std::vector <FlyPlanData> m_vFlyPlans;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

class TrainPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TrainPlanPacket);

public:
	int PlaneinAirNum;
	int PlaneonGroundNum;
	int Frequency;

private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum Command
{
	INVALID = 0,
	CIRCLE_CMD = 1,
	DIRECTLY_CMD = 2,
	TAX_LEFT_CMD = 3,
	TAX_RIGHT_CMD = 4,
};

class CommandPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CommandPacket);

public:
	Command cmd;
	int id;//�ɻ�ID
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum SysCommand
{
	START_PLAN = 1,
	END_PLAN = 2,
	READY_PLAN = 3,
};

class SysCommandPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SysCommandPacket);

public:
	SysCommand cmd;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

enum SysStatus
{
	START_STATUS = 1,
	END_STATUS= 2,
	PAUSE_STATUS = 3,
};

enum OperatorMemcache
{
	CACHE_UPDATE = 1,
	CACHE_FETCH= 2,
	CACHE_DELETE = 3,
};

class SysStatusPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SysStatusPacket);

public:
	int GroupID;
	SysStatus Status;
	OperatorMemcache OpCache;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

// class ExServerIPPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(ExServerIPPacket);
// 
// public:
// 	std::string ip;
// 	short port;
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

// class DataServiceIPPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(DataServiceIPPacket);
// 
// public:
// 	std::string ip;
// 	short port;
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

class MemcacheServiceIPPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MemcacheServiceIPPacket);

public:
	std::string ip;
	short port;
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

// class GroupDisConnectPacket : public CSerial_Base
// {
// 	PKT_DECLARE_DYNCREATE(GroupDisConnectPacket);
// 
// public:
// 
// private:
// 	virtual void ReadFromBuffer(const char* pBuffer);
// 	virtual void WriteToBuffer(char* pBuffer);
// 	virtual int GetBufferSize();
// };

//! �˶�Ŀ����Ϣ(��SDD����)
struct MovingObjTrack
{ 
	int iID;                            ///< Ŀ��ID
	int PlanID;                         ///< ���мƻ�ID
	ENUM_TRACKTYPE TrackType;           ///< ��������
	int iICAOAddress;                   ///< ������ICAO��ַ
	int iSurveilEquip;                  ///< �����������豸
	std::string strRegisterCode;        ///< ������ע���  
	std::string strCallSign;            ///< ����������
	std::string strSSRCode;             ///< �����״���
	double dLongitude;                  ///< ����������
	double dLatitude;                   ///< ������γ��
	int iAltitude;                      ///< �������߶�m
	ENUM_AltitudeType AltitudeType;     ///< �������߶�����
	double dIAS;                        ///< ������IAS km/h
	double dTAS;                        ///< ������TAS km/h
	double dGAS;                        ///< ������GAS km/h
	double dHeading;                    ///< ��������ͷ����
	double dTrackAngle;                 ///< ��������������
	int iVerticalState;                 ///< ��������ֱ״̬��������ƽ�ɡ��½�
	double dVerticalRate;               ///< �����½��ʣ�Ϊ��ֵ
	double dRollAngle;                  ///< �����������
	int iDesAltitude;                   ///< ������Ŀ�ĸ߶�
	ENUM_AltitudeType DesAltitudeType;  ///< ������Ŀ�ĸ߶�����
	double dDesHeading;                 ///< ���ú�����Ŀ�ĳ���
	bool bSPIFlag;                      ///< ���ú�����SPI��־
	int EmergencyType;                  ///< ���ú����������������
	bool bHide;                         ///< �Ƿ�����
	bool bRVSM;                         ///< ��ǰ�ɻ��Ƿ�߱�RVSM����
	ENUM_STATE_TYPE eStateType;         ///< �ɻ�״̬��׹�١���������ȴ����ȵȴ������С���ɡ��ڿ��С������
	ENUM_OBJ_TYPE ObjType;              ///< Ŀ������
    double dQNEAlt;                     ///< ��ǰQNE�߶ȣ����⽫QNH/QFE�߶�ת��QNE�߶�

	//����� shenjk
	double dROC; ///< Ŀ��������
	double	dROD;	///< Ŀ���½���
	double	dMaxROC;///< ���������
	double	dMaxROD; ///< ����½���
	std::string	strRespMode;///< Ӧ���ģʽ��mode��
	double	dTurnRate	; ///< ת����
	double	dDestIas; ///< Ŀ���ٶȣ����٣�
	double	dMaxIas; ///< ����ٶ�
	double	dCurMach; ///<��ǰ�����
	double	dDestMach; ///<	 Ŀ�������   
	std::vector<std::string> vRouteName; ///<   ���к�·
	int iCurRouteIndex; ///< ��ǰ��·���
	double	dDSSpd; ///<	V1�ٶ�
	std::vector<std::string>	vCmdList; ///<       ִ�������б�   
	int	 iCurCmdIndex; ///<   ��ǰ�������        
	
	MovingObjTrack()
	{
		 iID = -1;                            ///< Ŀ��ID
		 PlanID = -1;                         ///< ���мƻ�ID
		//ENUM_TRACKTYPE TrackType;           ///< ��������
		 iICAOAddress = -1;                   ///< ������ICAO��ַ
		 iSurveilEquip = -1;                  ///< �����������豸
		//std::string strRegisterCode;        ///< ������ע���  
		//std::string strCallSign;            ///< ����������
		//std::string strSSRCode;             ///< �����״���
		 dLongitude = -1.0;                  ///< ����������
		 dLatitude = -1.0;                   ///< ������γ��
		 iAltitude = -1;                      ///< �������߶�m
		//ENUM_AltitudeType AltitudeType;     ///< �������߶�����
		 dIAS = -1.0;                        ///< ������IAS km/h
		 dTAS = -1.0;                        ///< ������TAS km/h
		 dGAS = -1.0;                        ///< ������GAS km/h
		 dHeading = -1.0;                    ///< ��������ͷ����
		 dTrackAngle = -1.0;                 ///< ��������������
		 iVerticalState = -1;                 ///< ��������ֱ״̬��������ƽ�ɡ��½�
		 dVerticalRate = -1.0;               ///< �����½��ʣ�Ϊ��ֵ
		 dRollAngle = -1.0;                  ///< �����������
		 iDesAltitude = -1;                   ///< ������Ŀ�ĸ߶�
		//ENUM_AltitudeType DesAltitudeType;  ///< ������Ŀ�ĸ߶�����
		 dDesHeading = -1.0;                 ///< ���ú�����Ŀ�ĳ���
		 //bSPIFlag = false;                      ///< ���ú�����SPI��־
		 EmergencyType = -1;                  ///< ���ú����������������
		//bool bHide;                         ///< �Ƿ�����
		//bool bRVSM;                         ///< ��ǰ�ɻ��Ƿ�߱�RVSM����
		//ENUM_STATE_TYPE eStateType;         ///< �ɻ�״̬��׹�١���������ȴ����ȵȴ������С���ɡ��ڿ��С������
		//ENUM_OBJ_TYPE ObjType;              ///< Ŀ������
		 dQNEAlt = -1.0;                     ///< ��ǰQNE�߶ȣ����⽫QNH/QFE�߶�ת��QNE�߶�

		//����� shenjk
		 dROC = -1.0;	///< Ŀ��������
		 dROD = -1.0;	///< Ŀ���½���
		 dMaxROC = -1.0;	///< ���������
		 dMaxROD = -1.0; ///< ����½���
		//ENUM_SURVEILANCEEQUIPMENT	eRespMode;	///< Ӧ���ģʽ��mode��
		dTurnRate	 = -1.0; ///< ת����
		dDestIas = -1.0; ///< Ŀ���ٶȣ����٣�
		dMaxIas = -1.0; ///< ����ٶ�
		dCurMach = -1.0; ///<��ǰ�����
		dDestMach = -1.0; ///<	 Ŀ�������   
	    vRouteName.clear(); ///<   ���к�·
	    iCurRouteIndex = -1; ///< ��ǰ��·���
		dDSSpd = -1.0; ///<	V1�ٶ�
		vCmdList.clear(); ///<       ִ�������б�   
    	 iCurCmdIndex = -1; ///<   ��ǰ�������        

	}

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iID & PlanID & TrackType & iICAOAddress & iSurveilEquip & strRegisterCode &
			strCallSign & strSSRCode & dLongitude & dLatitude & iAltitude  &
			AltitudeType& dIAS & dTAS & dGAS & dHeading &
			dTrackAngle & iVerticalState & dVerticalRate & dRollAngle & iDesAltitude  &
			DesAltitudeType& dDesHeading & bSPIFlag &
			EmergencyType & bHide & bRVSM &eStateType & ObjType & dQNEAlt & dROC & dROD & dMaxROC & dMaxROD & strRespMode
			& dTurnRate & dDestIas & dMaxIas & dCurMach & dDestMach & vRouteName & iCurRouteIndex &dDSSpd & vCmdList & iCurCmdIndex;
	}
};

//! �˶�Ŀ����Ϣ��(��SDD������)
class MovingObjPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MovingObjPacket);

public:
	std::vector<MovingObjTrack> m_vTrace;

private:
	SERIALIZE_PACKET(m_vTrace);
};

//�����嶯̬������(ֻ�����˶�����Ч���壬����ţ�����������)
class MoveSpelEffectCreatePacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(MoveSpelEffectCreatePacket);
public:
	SpecialEffectObjPlan effectPlan;        //��Ч����ƻ�
private:
	SERIALIZE_PACKET(effectPlan);
};

//��Ч�˶����崴���ظ���
class MoveSpelEffectCreateAckPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectCreateAckPacket);
public:
	int		m_ObjID;    //id���
	ENUM_OBJ_TYPE	m_eObjType;       //��Ч��������
	string		m_strName;            //��Ч��������
private:
	SERIALIZE_PACKET(m_ObjID & m_eObjType & m_strName)
};

//�˶���Ч����ɾ����
class MoveSpelEffectDeletePacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectDeletePacket);
public:
	int		m_ObjID;      //id���
private:
	SERIALIZE_PACKET(m_ObjID)
};

//��Ч�˶����崴���ظ���ɾ����,�����Ӿ�
class MoveSpelEffectOperatorPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MoveSpelEffectOperatorPacket);
public:
	ENUM_OBJ_TYPE	 m_eObjType;     //����
	int		 m_iObjID;         //id
	string	 m_sName;           //����
	int		 m_iPerformanceID;	//����ID(�ɻ�ʹ��)
	string	 m_sComSign;		  //���չ�˾��(�ɻ�ʹ��)
	bool             m_bIsDelete;      //�Ƿ�ɾ��
	double         m_dPosX;          //λ����
	double         m_dPosY;
	double         m_dPosZ;
	double 		   m_dHdg;                  //����
	double 		   m_dPith;             //����
	double 		   m_dRoll;                //���
private:
	SERIALIZE_PACKET(m_eObjType&m_iObjID&m_sName&m_iPerformanceID&m_sComSign&m_bIsDelete&m_dPosX&m_dPosY&m_dPosZ&m_dHdg&m_dPith&m_dRoll)
};

//��̬�����˶������ѯ��
class ReqTmpObjPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(ReqTmpObjPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};

//��̬�������мƻ���
class DynamicCreateFlightPlanPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateFlightPlanPacket);
public:
	int iFlightPlanId;                //���мƻ�id
	string  sSSRCode;                   /*  ������ */
	bool  bRVSM;			               /* �Ƿ�߱�RVSM����*/
	int	iFlyPlanType;	               /* ���мƻ�����,0���ۣ�1��� */
	string sSectorName;            //����������
	string sCompany;		               /* ���չ�˾ */
	string sCallSign;		           /* ���ţ����չ�˾+���ֱ��룩*/
	string sDepDromeName;		           /* ��ɻ��� */
	string sArrDromeName;       		       /* ������� */
	string sAlternateDrome;	           /* ������ */
	int iCruiseLvl;		               /* Ѳ���߶�(��׼��ѹ�߶ȣ���λ����) */
	int	iCruiseSpd;		               /* Ѳ���ٶ�(���ٻ�����գ����ٵ�λ����/��) */
	string sArrRunway;		           /* �����ܵ� */
	string sDepRunway;                  /* ����ܵ�*/
	string sWeight;		               /* ���� */
	string sDepGate;		               /* �볡��ͣ��λ */
	string sArrGate;		               /* ������ͣ��λ */
	string sVacateLine;		           /* ����� */
	string sInRunwayLine;               /* ����� */
	string sDepartureTime;		           /* Ԥ�����ʱ��*/
	string sArrivalTime;		           /* Ԥ�Ƶ���ʱ��*/
	string  sSidName;                     /*�볡��������*/
	vector<string> vRoutePt;	      /* ��·�� ,��·���ʽ:xxx/kxxmxx,����xxx��ʾ����̨����xx��ʾ�߶ȣ���10��Ϊ��λ��xx��ʾ���٣���λkm/h */
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iFlightPlanId & sSSRCode & bRVSM & iFlyPlanType &sSectorName& sCompany & sCallSign & sDepDromeName &
			sArrDromeName & sAlternateDrome & iCruiseLvl & iCruiseSpd & sArrRunway  &
			sDepRunway& sWeight & sDepGate & sArrGate & sVacateLine &
			sInRunwayLine & sDepartureTime & sArrivalTime  & sSidName  &
			vRoutePt;
	}
private:
	SERIALIZE_PACKET(iFlightPlanId & sSSRCode&bRVSM&iFlyPlanType&sSectorName&sCompany&sCallSign&sDepDromeName&sArrDromeName&sAlternateDrome&iCruiseLvl&iCruiseSpd&sArrRunway&sDepRunway
		&sWeight&sDepGate&sArrGate&sVacateLine&sInRunwayLine&sDepartureTime&sArrivalTime&sSidName&vRoutePt)
};

//��̬����Ŀ��ƻ���
class DynamicCreateFlightObjPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateFlightObjPacket);
public:
	ENUM_OBJ_TYPE   ObjType;              //����
	string strSSrcode;               //�������мƵĶ�����
	double	dLongtitude;		        //���ֵľ��ȣ���λ�����ȣ�
	double	dLatitude;           	    //���ֵ�γ�ȣ���λ�����ȣ�
	double 	dAltitude;		            //��ʼ�߶ȣ���׼��ѹ�߶ȣ���λ���ף�
	double 	dHeading;		            //��ͷ���򣨵�λ�����ȣ�
	double 	dIAS;			            //��ʼ�ٶȣ����٣���λs����/�룩
	string sAppearTime;		        //����ʱ�䣨��λ���룩
	string strModelType;	        //������
	string	strRegNum;		            //ע���
	bool 	bEngineStart;		        //�����Ƿ���
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjType & strSSrcode & dLongtitude & dLatitude & dAltitude & dHeading &
			dIAS & sAppearTime & strModelType & strRegNum & bEngineStart;
	}
private:
	SERIALIZE_PACKET(ObjType&strSSrcode&dLongtitude&dLatitude&dAltitude&dHeading&dIAS&sAppearTime&strModelType&strRegNum&bEngineStart)
};

//��̬�����ɻ���
class DynamicCreateAircraftPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateAircraftPacket);
public:
	DynamicCreateFlightObjPacket ObjFlight;        //Ŀ��ƻ�
	vector<DynamicCreateFlightPlanPacket> PlanFlight;         //�����ķ��мƻ�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & ObjFlight & PlanFlight;
	}
private:
	SERIALIZE_PACKET(ObjFlight&PlanFlight)
};

//��̬�����ɻ��ظ���
class DynamicCreateAircraftAckPacket:public CSerial_Base
{
    PKT_DECLARE_DYNCREATE(DynamicCreateAircraftAckPacket);
public:
	vector<DynamicCreateFlightPlanPacket> PlanFlight;         //���мƻ�
	int iObjId;            //Ŀ��ƻ�id
	bool bOk;      //�������
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & PlanFlight &iObjId& bOk;
	}
private:
	SERIALIZE_PACKET(PlanFlight&iObjId&bOk)
};

//��ѯ��̬�����ɻ���
class QueryDynamicCreateAircraftPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(QueryDynamicCreateAircraftPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};


struct ParkInfo
{
	int m_iParkBayID; //!< ͣ��λID

	int m_iCurUseObjID; //!<��ǰʹ��ͣ��λ�ɻ�ID
	std::string m_sCurUseObjCallsign; //!<��ǰʹ��ͣ��λ�ɻ�����

	int m_iPlanUseObjID;//!< �ƻ�ʹ�õ�ǰͣ��λ�ɻ�ID
	std::string m_sPlanUseObjICallsign; //!<�ƻ�ʹ��ͣ��λ�ɻ�����
	std::string m_iCurUsePlaneType; //!<ͣ��λʵ��ʹ�÷ɻ�����
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iParkBayID & m_iCurUseObjID & m_sCurUseObjCallsign & m_iPlanUseObjID
			& m_sPlanUseObjICallsign & m_iCurUsePlaneType ;
	}
};
//ͣ��λ��Ϣ���°�
class ParkingBayInfoACKPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ParkingBayInfoACKPacket);
public:
	std::vector<ParkInfo> m_vParkInfo;

private:
	SERIALIZE_PACKET(m_vParkInfo);
};

//����ͣ��λ��Ϣ
class AssignParkingBayPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AssignParkingBayPacket);
public:
	int m_iParkBayID; //!< ͣ��λID
	
	int m_iAssignObjID; //!<׼�������ͣ��λ�ɻ�ID
private:
	SERIALIZE_PACKET(m_iParkBayID&m_iAssignObjID);
};
//ͣ��λ����ظ���
class AssignParkingBayACKPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AssignParkingBayACKPacket);
public:
	bool m_bOK;               //�Ƿ����ʧ��
	std::string m_sAckMsg;//�������ʧ�ܣ��ظ�ʧ��ԭ��
private:
	SERIALIZE_PACKET(m_bOK&m_sAckMsg);
};


//ͣ��λ��ѯ���°�
class ReqTmpParkingBayPacket:public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ReqTmpParkingBayPacket);
private:
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
};