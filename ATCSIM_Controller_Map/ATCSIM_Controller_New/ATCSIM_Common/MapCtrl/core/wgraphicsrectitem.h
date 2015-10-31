/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsrectitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsRectItem类及其核心数据类WRectItemData类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_RECT_ITEM_H_
#define _WGRAPHICS_RECT_ITEM_H_

#include "../wdllimport.h"
#include "wworldrect.h"
#include "wabstractgraphicsshapeitem.h"

class WMatrix;
class WGraphicsView;

/** 
 \brief                 此类是WGraphicsRectItem的核心数据类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WRectItemData : public WAbstractShapeItemData
{
public:
	explicit WRectItemData(int typ = 0, const WWorldRectF& r = WWorldRectF(), const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0) : WAbstractShapeItemData(typ, b, p), rect(r), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WRectItemData* copy() const { return new WRectItemData(*this); }

	WWorldRectF rect; //矩形区域
	double angle; //矩形区域旋转的角度
};

class MAPAPI WGraphicsRectItem : public WAbstractGraphicsShapeItem
{
	RTTI_DECL(WGraphicsRectItem)

public:
	typedef WRectItemData data_type;

public:
	explicit WGraphicsRectItem(const WWorldRectF& r, const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0);
	explicit WGraphicsRectItem(data_type* d = 0);

	WWorldRectF rect() const;
	double angle() const;

	void setRect(const WWorldRectF& rect, bool update = false, bool opStack = false);
	void setAngle(double ag, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	virtual void keyPressEvent(WKeyEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsRectItem* copy() const;

	enum { Type = TYPE_RECT_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      getCursorShape
	\Access    public 
	\param  int flag
	\retval     Ws::CursorShape
	\remark     根据选中状态获取光标的形状
	*/
	Ws::CursorShape getCursorShape(int flag);

	virtual void translate(const WWorldPointF& offset);

	/**
	\brief      updateCp
	\Access    public 
	\retval     void
	\remark     更新控制点信息
	*/
	void updateCp();

	/**
	\brief      getRotateMatrix
	\Access    public 
	\retval     WMatrix
	\remark     获取旋转矩阵
	*/
	WMatrix getRotateMatrix() const;

	/**
	\brief      getRotateMatrix_1
	\Access    public 
	\retval     WMatrix
	\remark     获取旋转矩阵的逆矩阵
	*/
	WMatrix getRotateMatrix_1() const;

protected:
	int _select_flag; //选中标识
	WWorldPointF _cp[8]; //control points
	WWorldPointF _rotate_pt; //旋转控制点
	bool _dragging; //矩形是否在拖动
};

#endif