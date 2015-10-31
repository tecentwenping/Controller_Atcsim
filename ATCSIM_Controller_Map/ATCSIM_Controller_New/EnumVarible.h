#ifndef _ENUMVARIBLE_H
#define _ENUMVARIBLE_H

//�ɵ������ȵ�ͼԪ����
enum BRIGHTNESS_SUB_TYPE
{
	SUB_DEFAULT = 0,
	SUB_SYMBOL,
	SUB_LABEL,
	SUB_STRIP,
	SUB_MAP,
	SUB_TOOL,
	SUB_ROUTE,
	SUB_END
};

//���������С
enum LABEL_FONT_SIZE
{
	SIZE_SMALL = 0,
	SIZE_MIDDLE,
	SIZE_LARGE
};

//�״�����
enum ENUM_RADAR_TYPE
{
	TYPE_NORM = 0, //�ۺ��״�
	TYPE_MONO,     //���״�
	TYPE_BYPASS
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

//��������
enum AIRCRAFT_SYMBOL_TYPE
{
	SYMBOL_INVALID = -1,
	SYMBOL_COMBINED = 0,  //һ�����״��ںϺ���
	SYMBOL_PRIMARY,       //һ���״ﺽ��
	SYMBOL_SECONDARY,     //�����״ﺽ��
	SYMBOL_PLAN,          //�ƻ�����
	SYMBOL_COAST,         //���ƺ���
	SYMBOL_SPI,           //SPI�澯����
	SYMBOL_ADSB,		  //ADSB����
	SYMBOL_VEHICLE,       //��������
	SYMBOL_PIC_AIRCRAFT,  //������ͼƬ����
	SYMBOL_PIC_HELICOPTER,//ֱ����ͼƬ
	SYMBOL_PIC_VEHICLE,   //����ͼƬ����
};

//�澯����
enum WARNING_TYPE
{
	TYPE_EMG = 0,
	TYPE_RCF,
	TYPE_HIJ,
	TYPE_STCA,
	TYPE_MSAW,
	TYPE_CLAM,
	TYPE_DAIW,
	TYPE_SPI,
	TYPE_SC,
	TYPE_YAW,
	TYPE_RVSM
};

//��λ���ͣ���Ӣ��
enum UNIT_TYPE
{
	UNIT_METRIC = 0,//����
	UNIT_IMPERIAL,  //Ӣ��
	UNIT_END
};

enum ALARM_TYPE
{
	ALARM_BEGIN = 0,
	EMG = 0,
	HIJ,
	RCF,
	STCA,
	MSAW,
	CLAM,
	DAIW,
	SPI,
	RAM,
	TDAW,
	DUPE,
	ALARM_END
};

enum LABEL_TYPE
{
	CTRL_DEFAULT,
	OWN_CONTROLLED, //���ҹ���
	UN_CONTROLLED,	//δ����
	PREACTIVE,      //Ԥ����
	HAND_IN,        //�ƽ���
	HAND_OUT,       //�ƽ���
};//��������


enum RUNNING_STATUS
{
	RUNNING = 0,
	FROZEN,
	END
};

//�����ͼ�е������
enum ENUM_RANDOMPOINT_TYPE
{
	RPT_TRIANGLE = 0,
	RPT_CIRCLE,
	RPT_RECT,
};


#endif