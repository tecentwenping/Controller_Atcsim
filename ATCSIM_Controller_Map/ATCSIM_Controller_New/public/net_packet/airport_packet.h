#pragma once
#define MAX_VALUE_WS 600000000 //���������ֵ
#include "DataObj/dataobjs.h"
#include "net_packet/serial_base.h"

/*********************����*************************/
//����������Աϯλ��ʼ����
class InitializeClientPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitializeClientPacket);
public:
	int m_nAirportID;//����ID
private:
	SERIALIZE_PACKET(m_nAirportID)
};

//��������ʼ������ֻ���»������ݣ�
class AirportDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportDataPacket);
public:
	int m_nAirportID;//����ID
private:
	SERIALIZE_PACKET(m_nAirportID)
};


/**********************�ظ���**************************/

//�ظ������������ݰ�
class AckAirportDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAirportDataPacket);
public:
	AirportData m_airportdata;
	std::vector<AirportData> m_vecAirport; //���л���
	std::vector<RunwayData> m_vcRunWayData;//�ܵ�
	std::vector<RoadData> m_vcRoadData;//���е�
	std::vector<FixpointData> m_vcFixpointData;//�̶���
	std::vector<Tower> m_vecTower;
	std::vector<AirportModel> m_vecAirportModel;
	std::vector<GateData> m_vecGate;//ͣ��λ
	std::vector<Sid> m_vecSid; //��׼����
	std::vector<Star> m_vecStar; //��׼�볡
	std::vector<Macro> m_vecMacro; //��
	std::vector<MacroGroup> m_vecMacroGroup; //����
	std::vector<Stdapch> m_vecStdapch;//��������
	std::vector<Hold> m_vecHold; //�ȴ�����
	std::vector<Miss> m_vecMiss; //���ɳ���

	std::vector<LightGroup> m_vecLightGroup; //�ƹ���
	std::vector<Route> m_vecRoute; //·��
	std::vector<Light> m_vecLight;  //��
	std::vector<LightCollection> m_vecLightCollection; //�ƹ������
	std::vector<LightGroupDetail> m_vecLightGroupDetail; //�ƹ��������Ӧ�ĵ�

private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_airportdata & m_vecAirport & m_vcRunWayData & m_vcRoadData 
		& m_vcFixpointData & m_vecTower & m_vecAirportModel & m_vecGate & m_vecSid & m_vecStar 
		& m_vecMacro & m_vecMacroGroup & m_vecStdapch & m_vecHold & m_vecMiss & m_vecLightGroup & m_vecRoute
		& m_vecLight & m_vecLightCollection & m_vecLightGroupDetail);

};

//�ظ������������ݰ�
class AckAirspaceDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAirspaceDataPacket);
public: 
	std::vector<Beacon> m_vecBeacon;				//����̨
	std::vector<SurveillanceSensor> m_vecSensor;	//���Ӵ��������״
	std::vector<StcaArea> m_vecStcaArea;			//��ͻ�澯��
	std::vector<MsawArea> m_vecMsawArea;			//�����������
	std::vector<RestrictArea> m_vecRestrictAera;    //��������������Σ����
	std::vector<ATS> m_vecATS;						//��ʱ��·
	std::vector<Radarrobe> m_vecRadarrobe;			//�״����ä��
	std::vector<Course> m_vecCourse;				//�̶���·
	std::vector<QnhArea> m_vecQnhArea;			//QNH��
	std::vector<InhibitoryArea> m_vecInhibitoryArea;	//�澯������

	//����Ϊ�����������
	std::vector<Sector> m_vecSector;				//����
	std::vector<GlyphPt>  m_vecGlyphPt;
	std::vector<GlyphPtArcInfo> m_vecGlyphPtArcInfo;
	std::vector<Cylinder> m_vecCylinder;
	std::vector<CylinderGlyph> m_vecCylinderGlyph;


	//std::vector<ControlArea> m_vcControlAirspaceData;//������
	//std::vector<FinalControlArea> m_vcFinalControlAirspaceData;//�ն˹�����
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vecBeacon & m_vecSensor & m_vecStcaArea & m_vecMsawArea & m_vecRestrictAera & m_vecATS & m_vecRadarrobe & m_vecCourse & m_vecQnhArea & m_vecInhibitoryArea & m_vecSector & m_vecGlyphPt & m_vecGlyphPtArcInfo & m_vecCylinder & m_vecCylinderGlyph );

};

//�ظ������������ݰ�
class AckBaseDataPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckBaseDataPacket);
public: 
	std::vector<AircraftData> m_vcAircraftData;//��������
	std::vector<AircraftPerformance> m_vAicraftPerData;
	std::vector<Vehicle> m_vcVehicleData;//��������
	std::vector<Company> m_vcCompanyData;//���չ�˾����
	std::vector<Flight> m_vcFlightData; //��������
	std::vector<AircraftModel> m_vcAircraftModel; //����ģ��
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vcAircraftData &m_vAicraftPerData &m_vcVehicleData &m_vcCompanyData &m_vcFlightData & m_vcAircraftModel)
};

//�ظ�����ѵ���ƻ��� ��ǰ�����ã���ɾ��
class AckExercisePacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckExercisePacket);
public: 
	std::vector<TrainPlan>		m_vecTrainPlan;//ѵ���ƻ�
	std::vector<ObjPlan>		m_vecObj;	//����Ŀ��ƻ�
	std::vector<TPFlyPlan>		m_vecFlyPlan;    //���мƻ�
	std::vector<VehiclePlan>	m_vecVehiclePlan ; //�����ƻ�
	std::vector<CloudPlan>      m_vecCloudPlan;   //�Ƽƻ�
	std::vector<SmokePlan>      m_vecSmokePlan;   //�̼ƻ�
	std::vector<SpecialEffectObjPlan> m_vecSpecialEffectObjPlan; //��Ч�˶�����ƻ�
	std::vector <EnvPlan> m_vecEnvPlan;//���������ƻ�
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();

	SERIALIZE_PACKET(m_vecTrainPlan & m_vecObj & m_vecFlyPlan & m_vecVehiclePlan & m_vecCloudPlan & m_vecSmokePlan & m_vecSpecialEffectObjPlan & m_vecEnvPlan);
};

//�ظ�������Աϯλѵ���ƻ�����ظ���
class AckAllTrainPlanNamePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllTrainPlanNamePacket);
public:
	std::vector<std::string> m_vAllTrainPlanName;
private:
	SERIALIZE_PACKET(m_vAllTrainPlanName)
};

//�ظ���������ѵ���ƻ��Լ���ط��мƻ���������ظ���
class AckSingleTrainPlanPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleTrainPlanPacket);
public:
	TrainPlan m_TrainPlan;
	std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<TPFlyPlan> m_vFlyPlan;
	std::vector<VehiclePlan> m_vVehiclePlan;
	std::vector<SpecialEffectObjPlan> m_vSpecialEffectObjPlan;
private:
	SERIALIZE_PACKET(m_TrainPlan & m_vAllObjPlan & m_vFlyPlan & m_vVehiclePlan & m_vSpecialEffectObjPlan)
};

//�ظ���������ѵ���ƻ��Լ���ط��мƻ���������ظ����������ͻ��ˣ�
class AckSingleTrainPlanPacket_S : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleTrainPlanPacket_S);
public:
	//TrainPlan m_TrainPlan;
	//std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<FplInfo> m_vFlyPlan;
private:
	SERIALIZE_PACKET(m_vFlyPlan)
};

//�ظ������Ӿ���ʼ����Ҫ�İ�
class VISInitPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(VISInitPacket);
public:
	//��������
	std::vector<LightGroup> m_vLightGroups;		//!<�ƹ�������
	std::vector<AircraftForVis> m_vAircrafts;	//!<��������
	std::vector<VehicleForVis> m_vVehicles;		//��������

	//��ѵ���ƻ���ص�����
	int m_iTrainPlanID;					//!<ѵ���ƻ�ID
	std::string m_strTrainPlanName;		//!<ѵ���ƻ�����
	std::string m_strDate;				//!<ѵ������
	int m_iStartTime;					//!<ѵ����ʼʱ�� ��0�㿪ʼ������� */

	int m_iAirportID;					//!<����ID
	std::string m_strAirportCode;		//!<����������
	std::string m_strAirportModelName;	//!<����ģ������
	double m_dAirportModelRotateAngle;	//!<����ģ����ת�Ƕ�
	double m_dCenterPointLongitude;		//!<�������ĵ㾭��(��λ������)
	double m_dCenterPointLatitude;		//!<�������ĵ�γ��(��λ������)

	std::vector<ObjPlanForVis> m_vObjPlans;	//!<Ŀ��ƻ�
	std::vector<CloudPlan> m_vCloud;		//!<��
	std::vector<SmokePlan> m_vSmoke;		//!<��
	EnvData m_envData;						//!<��������

	double m_dViewPointX;		//!<�ӵ㾭�ȣ��ӵ��ʼ��ʱ��ʹ�õ���TOWER�Ĳ���
	double m_dViewPointY;		//!<�ӵ�γ��
	double m_dViewPointZ;		//!<�ӵ�߶�
	double m_dViewPointHeading;	//!<�ӵ�ĳ���
	double m_dViewPointPitch;	//!<�ӵ������
	double m_dViewPointRoll;	//!<�ӵ�ˮƽ��ת
private:
	SERIALIZE_PACKET(m_vLightGroups & m_vAircrafts & m_vVehicles & m_iTrainPlanID & m_strTrainPlanName & m_strDate & m_iStartTime 
		& m_iAirportID & m_strAirportCode & m_strAirportModelName & m_dAirportModelRotateAngle & m_dCenterPointLongitude
		& m_dCenterPointLatitude & m_vObjPlans & m_vCloud & m_vSmoke & m_envData & m_dViewPointX & m_dViewPointY 
		& m_dViewPointZ & m_dViewPointHeading & m_dViewPointPitch & m_dViewPointRoll)
};


/*!
\brief:		���������л���ID��map�Եİ�
\details:	��Ҫ���ڽ�Աϯλϯλ��
			��Աϯλ���������͸ð��������л���ID�����֣��Թ�ѡ��ѵ���ƻ�ʹ�ã�
			DataServer�յ��ð���ظ�AckAirportPacket��
\author DXQ
\date 2013/6/13
*/
class AllAirportPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AllAirportPacket);
public:
	int m_iSiteType; //ϯλ����
private:
	SERIALIZE_PACKET(m_iSiteType)
};



/*!
\brief:		����ȫ������������ID��map�԰�
\details:	��Ҫ���ڽ�Աϯλ
\author DXQ
\date 2013/6/13
*/
class AckAllAirportPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllAirportPacket);
public:
	std::map<string, int> m_mapAirport;	//����������IDmap��
private:
	SERIALIZE_PACKET(m_mapAirport)
};


/*!
\brief:		������ĳһ��������ѵ���ƻ�ID�����ֵ�map�԰�
\details:	��Ҫ���ڽ�Աϯλ��
			��Աϯλ���л�������ʱ���ͣ��Թ�ѡ��ѵ���ƻ�ʹ�ã�
			DataServer�յ��ð���ظ�AckAllExercisePacket����
\author DXQ
\date 2013/6/13
*/
class AllExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AllExercisePacket);
public:
	int m_iAirportID;//����ID
private:
	SERIALIZE_PACKET(m_iAirportID)
};


/*!
\brief:		����ĳһ������ȫ��ѵ���ƻ�������ID��map�԰�
\details:	��Ҫ���ڽ�Աϯλ���Թ�ѡ��ѵ���ƻ�ʹ�á�
\author DXQ
\date 2013/6/13
*/
class AckAllExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckAllExercisePacket);
public:
	int m_nAirportID;						//����ID
	std::map<string, int> m_mapExercise;	//ѵ���ƻ����ֺ�IDmap��
private:
	SERIALIZE_PACKET(m_nAirportID & m_mapExercise)
};



/*!
\brief:		����ѵ���ƻ��Լ���ط��мƻ���������ظ���
\details:	��Ҫ���ں��ļ��㡣
\author DXQ
\date 2013/6/14
*/
class AckSingleExrecisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleExrecisePacket);
public:
	TrainPlan m_TrainPlan;
	std::vector<ObjPlan> m_vAllObjPlan;
	std::vector<TPFlyPlan> m_vAllFlyPlan;
	std::vector<VehiclePlan> m_vAllVehiclePlan;
	std::vector<EnvPlan> m_vecEnvPlan;
	std::vector<LightPlan> m_vecLightPlan;
private:
	SERIALIZE_PACKET(m_TrainPlan & m_vAllObjPlan & m_vAllFlyPlan & m_vAllVehiclePlan & m_vecEnvPlan & m_vecLightPlan)
};



/*!
\brief:		����ѵ���ƻ��������͸��ͻ���
\details:	��Ҫ���ڿͻ��ˡ�
\author DXQ
\date 2013/6/18
*/
class AckSingleExrecisePacket_S : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AckSingleExrecisePacket_S);
public:
	std::string m_strTrainPlanName;		//ѵ����
	std::string m_strAirportName;		//������
	int m_iStartTime;					//ѵ����ʼʱ��
	std::map<int, std::vector<std::string>> m_mapControllerSector;//����Ա������Ӧ��ϵ(δ���䵽�κι������Ĺ���ԱΪ-1)
	std::map<std::string, std::vector<int>> m_mapSectorFlight;//�����������¹��Ʒɻ���Ӧ��ϵ
private:
	SERIALIZE_PACKET(m_strTrainPlanName & m_strAirportName & m_iStartTime & m_mapControllerSector & m_mapSectorFlight)
};



/*!
\brief:		����ĳһ����ID��ѵ���ƻ�ID
\details:	��Ҫ���ڽ�Աϯλ��
			��Աϯλ��ѡ����ĳ�������е�ĳ��ѵ���ƻ��󣬵��׼��ʱ���͸ð���
			DataServer�յ��ð��󣬻ظ�һϵ�а���
			DataServer�ظ��İ����£�
								AckBaseDataPacket���������ݰ���
								AckAirportDataPacket���������ݰ���
								AckAirspaceDataPacket���������ݰ���
								AckSingleExrecisePacket������ѵ���ƻ�����
								AckSingleTrainPlanPacket_S���ͻ���ѵ���ƻ�����
								VISInitPacket���Ӿ���ʼ������

\author DXQ
\date 2013/6/13
*/
class InitExercisePacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InitExercisePacket);
public:
	int m_iAirportID;	//����ID
	int m_iTrainPlanID; //ѵ���ƻ�ID
private:
	SERIALIZE_PACKET(m_iAirportID & m_iTrainPlanID)
};



/*!
\brief:		�л�������
\details:	��Ҫ����Designerϯλ����ʼ��ʱ�Լ��л�����ʱʹ�ã�
			Designer��ʼ��ʱ�����͸ð���
			Designer�л�����ʱ�����͸ð�
			DataServer�յ��ð��󣬻ظ�һϵ�а���
			DataServer�ظ��İ����£�
									AckBaseDataPacket���������ݰ���
									AckAirportDataPacket���������ݰ���
									AckAirspaceDataPacket���������ݰ���
									AckExercisePacket��ѵ���ƻ�����
\author DXQ
\date 2013/6/17
*/
class AirportChangePacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(AirportChangePacket);
public:
	int m_iAirportID;				//����ID������ID<=0ʱ���ݻ������־���
	std::string m_strAirportName;	//������
private:
	SERIALIZE_PACKET(m_iAirportID & m_strAirportName)
};

/*!
\brief: ����ĳһ����ID��ѵ���ƻ�ID
\details: ��Ҫ���ڽ�Աϯλ��
��Աϯλ��ѡ����ĳ�������е�ĳ��ѵ���ƻ��󣬵��׼��ʱ���͸ð���
DataServer�յ��ð��󣬻ظ�һϵ�а���
DataServer�ظ��İ����£�
AckSingleTrainPlanPacket_S���ͻ���ѵ���ƻ�����
\author JZH
\date 2013/9/16
*/
class ExerciseInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ExerciseInfoPacket);
public:
	int m_iAirportID; //����ID
	int m_iTrainPlanID; //ѵ���ƻ�ID
private:
	SERIALIZE_PACKET(m_iAirportID & m_iTrainPlanID)
};