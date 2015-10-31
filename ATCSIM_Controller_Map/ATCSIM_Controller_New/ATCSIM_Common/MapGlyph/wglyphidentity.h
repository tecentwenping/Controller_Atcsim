#ifndef _WGLYPHIDENTITY_H
#define _WGLYPHIDENTITY_H

#include <string>

//����ͼԪ�����ͣ��κ�һ��ͼԪ��������һ������
//ͼ���ö��ֵ������ͼ��ĸ߶�
typedef enum euGlyphType
{
	GLYPH_NONE = -1,
	// [ ��Ŀ��� ]
	GLYPH_AIRCRAFT,	 //������
	GLYPH_FRAME,	 //���ο�
	GLYPH_TELEMETER, //�����
	GLYPH_VEHICLE,   //����
	// [ ��Ŀ�긨���� ]
	GLYPH_LONGLAT,	//��γ����ʾ��
	GLYPH_TAXING,//��ͼ�򵥲�����̬������
	GLYPH_DYNAMIC_ROUTE,//������ķ��мƻ���·
	GLYPH_DRAG_AIRCRAFT,//�Ժ�ϲ�

	// [ �м䱣��ͼ�����ڶ�̬��ͼ id: 10-100]
	GLYPH_RESERVE = 10,
	

	GLYPH_RUNWAY = 101,    //�ܵ�
	GLYPH_NAVPOINT,  //����̨
	GLYPH_AIRNAVPOINT, //���ڿ��еĵ���̨
	GLYPH_AIRLINE,   //����
	GLYPH_ROUTE,     //���мƻ��ĺ�·
	GLYPH_LINKLINE,  //������
	GLYPH_TAXLINE,   //������
	GLYPH_GATE,      //ͣ��λ
	GLYPH_CORRIDOR,  //��������
	GLYPH_SECTOR,
	GLYPH_CONTROLLER,
	GLYPH_LANDFORM, //����
	GLYPH_WEATHER_ENV_AREA, //���󻷾�����
	GLYPH_MAINRING,		// �����뻷
	GLYPH_SECONDRING,	// 
	GLYPH_FROZEN,    //�����
	GLYPH_RING,      //���뻷
	GLYPH_AZIMUTH,   //��λ��
	GLYPH_SYSINFO,
	GLYPH_RESTRICTAREA, //����������
	GLYPH_MSAWAREA,     //�����������
	GLYPH_AIRSPACEROUTE,//���к�·
	GLYPH_CLOUD,
	GLYPH_BACKGROUND,// [ ������ ]

	GLYPH_END //!!! the end
}GlyphType;


//��ʶͼԪ����
class WGlyphIdentity
{
public:
	WGlyphIdentity(){};
	virtual ~WGlyphIdentity(){};
public:
	std::string strName;
	int  m_nLayerID;
	int  m_nTraceID;
};


//��ʶ�ɻ�ͼԪ
class WAcftGlyphIdentity:public WGlyphIdentity
{
public:
	WAcftGlyphIdentity(){};
	~WAcftGlyphIdentity(){};
public:
	int m_nSSR;
};


#endif