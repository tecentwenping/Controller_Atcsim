/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicslayer.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsLayer类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_LAYER_H_
#define _WGRAPHICS_LAYER_H_

#include <set>
#include <vector>
#include "../wdllimport.h"
#include "wpen.h"
#include "wbrush.h"
#include "wworldline.h"
#include "wworldrect.h"
#include "wworldpolyline.h"
#include "wworldpolygon.h"

class WPainter;
class WGraphicsItem;
class WGraphicsView;
class WGraphicsScene;
class WGraphicsArcItem;
class WGraphicsLineItem;
class WGraphicsTextItem;
class WGraphicsRectItem;
class WGraphicsPointItem;
class WGraphicsEllipseItem;
class WGraphicsPolylineItem;
class WGraphicsPolygonItem;
class WGraphicsRichTextItem;

/** 
 \brief                 此类主要实现场景中的图层管理功能
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsLayer //场景中图层概念
{
public:
	friend class WGraphicsScene;

	explicit WGraphicsLayer(WGraphicsScene* scene, int layer = 0);
	~WGraphicsLayer();

	/**
	\brief      layer
	\Access    public 
	\retval     int
	\remark     图层的id
	*/
	int layer() const;

	/**
	\brief      visible
	\Access    public 
	\retval     bool
	\remark    图层是否可视，如果不可视则它管理的所有图元都不可视 
	*/
	bool visible() const;

	/**
	\brief      editable
	\Access    public 
	\retval     bool
	\remark     图层是否可编辑
	*/
	bool editable() const;

	/**
	\brief      scene
	\Access    public 
	\retval     WGraphicsScene*
	\remark     图层所有的场景
	*/
	WGraphicsScene* scene() const;
	
	void setLayer(int layer); //设置图层id
	void setVisible(bool visible); //设置图层是否可视
	void setEditable(bool editable); //设置图层是否可编辑

	//图层中增加图元
	WGraphicsLineItem* addLine(const WWorldLineF& line, const WPen& pen = WPen(), bool updating = false);
	WGraphicsRectItem* addRect(const WWorldRectF& rect, double angle = 0.0, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsEllipseItem* addEllipse(const WWorldRectF& rect, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsPolygonItem* addPolygon(const WWorldPolygonF& polygon, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsPolylineItem* addPolyline(const WWorldPolylineF& polyline, const WPen& pen = WPen(), bool updating = false);
	WGraphicsArcItem* addArc(const WWorldRectF& rect, double startAngle, double endAngle, const WPen& pen = WPen(), bool updating = false);
	WGraphicsTextItem* addText(const WWorldPointF& pos, const std::string& text, bool updating = false);
	WGraphicsRichTextItem* addRichText(const WWorldPointF& pos, const std::string& text, bool updating = false);
	WGraphicsPointItem* addPoint(const WWorldPointF& pos, const WPen& pen = WPen(), bool updating = false);

	//图层中是否包含某个图元
	bool hasItem(WGraphicsItem* item) const;
	//图层中现有图元集合
	std::vector<WGraphicsItem*> items() const;
	//在图层中增加指定图元，图层将负责管理，删除图元
	WGraphicsItem* addItem(WGraphicsItem* item, bool updating = false);
	//在图层中增加指定图元的副本
	WGraphicsItem* addItem(const WGraphicsItem& item, bool updating = false);
	//在图层中删除指定图元
	bool removeItem(WGraphicsItem* item, bool updating = false, bool opStack = false);
	//在图层中删除所有图元
	void removeAllItems(bool updating = false);
	//渲染图层
	void render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view) const;
	//恢复删除的图元
	void recoverItem(WGraphicsItem* item, bool updating = false);
	
private:
	//清空回收站
	void clearGarbage();

	template<class Item>
	Item* addItemPrivate(Item* item, bool updating);

private:
	int _layer; //图层ID
	bool _visible; //图层是否可视
	bool _editable; //图层是否可编辑
	WGraphicsScene* _scene; //图层所在场景
	std::set<WGraphicsItem*> _items; //图层所管理的图元
	std::set<WGraphicsItem*> _items_garbage; //图层中被删除的图元，用于撤消操作
};

struct WLayerCmp //图层比较操作仿函数对象
{
	bool operator()(const WGraphicsLayer* lhs, const WGraphicsLayer* rhs) const
	{
		return lhs->layer() < rhs->layer();
	}
};

#endif