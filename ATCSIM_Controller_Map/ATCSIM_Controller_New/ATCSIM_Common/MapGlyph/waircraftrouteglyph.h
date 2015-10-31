#ifndef _WAircraftRouteGlyph_H_
#define _WAircraftRouteGlyph_H_

/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: waircraftrouteglyph.h
  ����  �ߡ�: @zcw
  ����  ����:1.0
  ��������ڡ�:2013/05/28
  ����  ����:  
    

  ����  ����:   
******************************************************************************/
#include <string>
#include <vector>
#include <wgraphicsarcitem.h>

enum DRAW_TYPE
{
	DT_LINETO,
	DT_ARCTO,
};

enum ARC_DIR
{
	AD_LEFT,
	AD_RIGHT,
};

class RouteData
{
	friend class WAircraftRouteGlyph;
public:
	RouteData() { m_drawType = DT_LINETO; }

	void SetRadius(double r);
	void SetRadius(double w, double h);
	void SetCenter(const WPointF& p);
	void SetArcDir(ARC_DIR arcDir);

	WPointF m_pos; //λ��
	std::string m_strHeight;  //�߶�
	std::string m_strName; //����
	DRAW_TYPE m_drawType; //����һ����Ļ����� ���һ������Ч

private:
	double m_width; // ��Բ�� 
	double m_height; // ��Բ��
	WPointF m_center; // �������Ŀ��Ƶ�λ��
	ARC_DIR m_arcDir; // ������ ����/���� ����˳ʱ��/��ʱ��
};

class WAircraftRouteItemData : public WItemData
{
public:
	WAircraftRouteItemData(){};
	
public:
	std::vector<RouteData> m_routeData;
	WPen m_pen;
};

class WAircraftRouteGlyph : public WGraphicsItem
{
	RTTI_DECL(WAircraftRouteGlyph)
public:
	typedef WAircraftRouteItemData data_type;

public:
	explicit WAircraftRouteGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual bool contain(const WWorldRectF& r) const;
	virtual WWorldRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};
#endif