#ifndef _AIRPORT_PACKET_H
#define _AIRPORT_PACKET_H
#include "airport_data_objs.h"
#include "airspace_data_objs.h"
#include "assistance_data_objs.h"
//�ظ������������ݰ�
class AckAirportDataPacket
{
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

};
//�ظ������������ݰ�
class AckAirspaceDataPacket
{
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
};


#endif