/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsarcitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件包含了类WArcItemData和类WGraphicsArcItem
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_ARC_ITEM_H_
#define _WGRAPHICS_ARC_ITEM_H_

#include "../wdllimport.h"
#include "wpen.h"
#include "wworldrect.h"
#include "wgraphicsitem.h"

/** 
 \brief                 WGraphicsArcItem的数据类
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WArcItemData : public WItemData
{
public:
	explicit WArcItemData(int typ = 0, const WWorldRectF& r = WWorldRectF(), double s = 0.0, 
		double e = 359.99, const WPen& p = WPen()) : WItemData(typ), rect(r), startAngle(s), endAngle(e), pen(p) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WArcItemData* copy() const { return new WArcItemData(*this); }

	WWorldRectF rect; //弧线对应的矩形区域
	double startAngle; //起始角度
	double endAngle; //终止角度
	WPen pen; //画笔
};

/** 
 \brief                 此类代表场景中的弧线图元
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WGraphicsArcItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsArcItem)

public:
	typedef WArcItemData data_type;

public:
	/**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  const WWorldRectF & r
	\param  double s
	\param  double e
	\param  const WPen & p
	\retval     
	\remark    常规构造函数 
	*/
	explicit WGraphicsArcItem(const WWorldRectF& r, double s = 0.0, 
		double e = 359.99, const WPen& p = WPen());

	/**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  data_type * d
				d可以为0，此时类内部会动态创建一份数据
				如果d不为0，则数据是外部创建的（请保证数据是用new创建的，请不要将栈上创建的数据传进来），
				则d对象现在属于图元管理了，生命周期由图元负责，图元会在适当的时候删除
				（请不要在外部将d删除）
	\retval     
	\remark    以核心数据进行构造 
	*/
	explicit WGraphicsArcItem(data_type* d = 0);

	WWorldRectF rect() const;
	double startAngle() const;
	double endAngle() const;
	WPen pen() const;

	/**
	\brief      setRect
	\Access    public 
	\param  const WWorldRectF & rect
	\param  bool update 场景是否立即更新（以后此类设置属性的函数的此参数含义不变，不再赘述）
	\param  bool opStack 此操作是否支持撤消操作（以后此类设置属性的函数的此参数含义不变，不再赘述）
	\retval     void
	\remark     
	*/
	void setRect(const WWorldRectF& rect, bool update = false, bool opStack = false);
	void setAngle(double startAngle, double endAngle, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsArcItem* copy() const;

	enum { Type = TYPE_ARC_ITEM };
	virtual int type() const;

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
	int _select_flag; //当前选中弧线哪一部分的标识
	WWorldPointF _cp[6]; //control points 弧线的控制点
	bool _dragging; //弧线是否在拖动
};

#endif