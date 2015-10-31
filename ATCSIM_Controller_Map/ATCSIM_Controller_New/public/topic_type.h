#pragma once
//��������
#define ATG									0x1
//���溽�������ѷ�����
#define GND									0x2
//ѵ���ƻ���ʼ������
#define EXERPLAN							0x4
//��ײ������
#define COLLIDE								0x8
//�������ݷ���
#define ENVIRONMENT							0x10
//ѵ���ƻ����Ʒ���
#define EPLANCTRL							0x20
//����������������񣨸ı亽���ٶȡ��߶ȵȣ�
#define CMD									0x40
//ѵ���ƻ���ʼ������(�����Ӿ�)
#define EXERPLAN_VIS						0x80
//����ϯλ����ȷ����
#define SwitchCheckIn						0x100
//���ݷ���ϯλ����ȷ�Ϸ���
#define DataServiceCheckIn					0x200
//�����������
#define DATAREQ								0x400
//����������
#define TIME								0x800
//�ͻ���ϯλ������ʱ�����ݷ���ϯλ���������ݵ�Ե㷢�͸�������Ŀͻ���
#define PeerToPeer						    0x1000
//ȫ�ֵ�ͼ���ݷ���
#define GlobalMapsSync						0x2000
//�澯����
#define ALARM								0x4000
//Hold����
#define FPL_OPERATE							0x8000
//Fdp���мƻ���ʼ��
#define FDP_FLIGHTPLAN                      0x10000
//���������Ϣ����
#define REGION_CTRL							0x20000
//�����ƽ�����
#define SectorAssignService					0x40000
//�������Ʒ���
#define ENVCTRLSERVICE                      0x80000
//��̬��������/ɾ������
#define MotionalObjService					0x100000
//SDPS��������
#define SDPSService                         0x200000
//���Ӵ�����״̬����
#define SurvSensorsStatService				0x400000
//��̬�����������ظ�
#define ACKMotionalObjService					0x800000
//��̬���������ѯ����
#define MotionalObjQueryService					0x1000000
//�����澯����
#define PILOTALARM	                            0x2000000 
//ͣ��λ��ѯ����
#define ParkingBayQueryService					 0x4000000
//ͣ��λ�ظ�����
#define ParkingBayACKService				 0x8000000

#define LIGHTCTRLSERVER                      0x10000000
#define LIGHTCTRLSERVERTOVIS                 0x20000000
//�����㲥����������Ҫ���ڻ���ϯλ�ƽ�,-->ATG -->Pilot)
#define PilotBroadcastService				 0x40000000 

inline std::string GetTopicName(int topic_type)
{
	switch (topic_type)
	{
	case ATG:					return "ATG";
	case GND:					return "GND";
	case EXERPLAN:				return "EXERPLAN";
	case COLLIDE:				return "COLLIDE";
	case ENVIRONMENT:			return "ENVIRONMENT";
	case EPLANCTRL:				return "EPLANCTRL";
	case CMD:					return "CMD";
	case EXERPLAN_VIS:			return "EXERPLAN_VIS";
	case SwitchCheckIn:			return "SwitchCheckIn";
	case DataServiceCheckIn:	return "DataServiceCheckIn";
	case DATAREQ:				return "DATAREQ";
	case TIME:					return "TIME";
	case PeerToPeer:			return "PeerToPeer";
	case GlobalMapsSync:		return "GlobalMapsSync";
	case ALARM:					return "ALARM";
	case FPL_OPERATE:			return "FPL_OPERATE";
	case FDP_FLIGHTPLAN:		return "FDP_FLIGHTPLAN";
	case REGION_CTRL:			return "REGION_CTRL";
	case SectorAssignService:	return "SectorAssignService";
	case ENVCTRLSERVICE:        return "ENVCTRLSERVICE";
	case MotionalObjService:    return "MotionalObjService";
    case SDPSService:           return "SDPSService";
	case ACKMotionalObjService:           return "ACKMotionalObjService";
	case MotionalObjQueryService:           return "MotionalObjQueryService";
	case PILOTALARM:					return "PILOTALARM";
	case ParkingBayQueryService:    return "ParkingBayQueryService";
	case ParkingBayACKService:	return "ParkingBayACKService";
	case LIGHTCTRLSERVER:       return "LIGHTCTRLSERVER";
	case LIGHTCTRLSERVERTOVIS:  return "LIGHTCTRLSERVERTOVIS";
	case PilotBroadcastService: return "PilotBroadcastService";
	default:					return "-";
	}
}