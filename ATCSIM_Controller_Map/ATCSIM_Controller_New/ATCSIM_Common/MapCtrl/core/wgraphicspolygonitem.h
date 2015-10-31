
/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicspolygonitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsPolygonItem和其对应的数据类WPolygonItemData类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_POLYGON_ITEM_H_
#define _WGRAPHICS_POLYGON_ITEM_H_

#include "../wdllimport.h"
#include "wworldpolygon.h"
#include "wabstractgraphicsshapeitem.h"

/** 
 \brief                 此类是WGraphicsPolygon类的数据类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WPolygonItemData : public WAbstractShapeItemData
{
public:
	explicit WPolygonItemData(int typ = 0, const WWorldPolygonF& p = WWorldPolygonF(), const WBrush& b = WBrush(), const WPen& pn = WPen()) 
		: WAbstractShapeItemData(typ, b, pn), polygon(p) {}
	
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WPolygonItemData* copy() const { return new WPolygonItemData(*this); }

	WWorldPolygonF polygon; //多边形
};

/** 
 \brief                 多边形图元
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsPolygonItem : public WAbstractGraphicsShapeItem
{
	RTTI_DECL(WGraphicsPolygonItem)

public:
	typedef WPolygonItemData data_type;

public:
	explicit WGraphicsPolygonItem(const WWorldPolygonF& p, const WBrush& b = WBrush(), const WPen& pn = WPen());
	explicit WGraphicsPolygonItem(data_type* d = 0);
	
	//以下均是设置/获取多边形数据的接口
	WWorldPolygonF polygon() const;
	const std::vector<WWorldPointF>& points() const;
	void setPolygon(const WWorldPolygonF& polygon, bool update = false, bool opStack = false);
	void setPoints(const std::vector<WWorldPointF>& pts, bool update = false, bool opStack = false);
	bool setPoint(unsigned index, const WWorldPointF& pos, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsPolygonItem* copy() const;

	enum { Type = TYPE_POLYGON_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      onContextMenu
	\Access    virtual public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     响应右键菜单
	*/
	virtual void onContextMenu(Ws::ContextMenuFlag flag);

	virtual void translate(const WWorldPointF& offset);

private:
	/**
	\brief      updateCp
	\Access    private 
	\retval     void
	\remark     更新控制点
	*/
	void updateCp();

private:
	int _select_flag; //选中标识，低16位是选中位标识，高16位是选中控制点的id
	std::vector<WWorldPointF> _cp; //多边形被选中时产生的控制点
	bool _dragging; //多边形是否在拖动
};

#endif