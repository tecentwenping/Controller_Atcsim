#ifndef _WAircraftRouteGlyph_H_
#define _WAircraftRouteGlyph_H_

/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: waircraftrouteglyph.h
  【作  者】: @zcw
  【版  本】:1.0
  【完成日期】:2013/05/28
  【描  述】:  
    

  【其  它】:   
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

	WPointF m_pos; //位置
	std::string m_strHeight;  //高度
	std::string m_strName; //名称
	DRAW_TYPE m_drawType; //到下一个点的画法， 最后一个点无效

private:
	double m_width; // 非圆弧 
	double m_height; // 非圆弧
	WPointF m_center; // 弧的中心控制点位置
	ARC_DIR m_arcDir; // 弧方向 向左/向右 或者顺时针/逆时针
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