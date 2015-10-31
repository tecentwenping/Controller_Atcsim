/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicstextitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要实现了WGraphicsTextItem类及其对应的数据类WTextItemData
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_TEXT_ITEM_H_
#define _WGRAPHICS_TEXT_ITEM_H_

#include <string>
#include "../wdllimport.h"
#include "wpen.h"
#include "wfont.h"
#include "wgraphicsitem.h"

class WMatrix;

/** 
 \brief                 WGraphicsTextItem的核心数据类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WTextItemData : public WItemData
{
public:
	explicit WTextItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const std::string& t = std::string(), 
		const WFont& f = WFont(), const WPen& pn = WPen(), double ag = 0.0) 
		: WItemData(typ), pos(p), text(t), font(f), pen(pn), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WTextItemData* copy() const { return new WTextItemData(*this); }

	WWorldPointF pos; //文本的位置
	std::string text; //文本信息
	WFont font; //文本的字体 
	WPen pen; //绘制文本所用的画笔
	double angle; //文本的旋转角度
};

/** 
 \brief                 文本图元
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsTextItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsTextItem)

public:
	typedef WTextItemData data_type;

public:
	explicit WGraphicsTextItem(const WWorldPointF& pos, const std::string& text = std::string(), 
		const WFont& font = WFont(), const WPen& pen = WPen(), double angle = 0.0);
	explicit WGraphicsTextItem(data_type* d = 0);

	WWorldPointF pos() const;
	std::string text() const;
	WFont font() const;
	WPen pen() const;
	double angle() const;

	//以下函数的第二参数update均为是否立即更新场景的含义，第三参数opStack均为是否将操作进栈的含义
	void setPos(const WWorldPointF& p, bool update =false, bool opStack = false);
	void setText(const std::string& t, bool update = false, bool opStack = false);
	void setFont(const WFont& f, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);
	void setAngle(double angle, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	enum { Type = TYPE_TEXT_ITEM };
	virtual int type() const;

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsTextItem* copy() const;

	virtual void translate(const WWorldPointF& offset);

private:
	/**
	\brief      updateBoundRect
	\Access    private 
	\retval     void
	\remark     更新文本的边界矩形
	*/
	void updateBoundRect();

	/**
	\brief      getRotateMatrix
	\Access    private 
	\retval     WMatrix
	\remark     获取旋转矩阵
	*/
	WMatrix getRotateMatrix() const;

	/**
	\brief      getRotateMatrix_1
	\Access    private 
	\retval     WMatrix
	\remark     获取旋转矩阵的逆矩阵
	*/
	WMatrix getRotateMatrix_1() const;

private:
	int _select_flag; //文本的选中标识
	WWorldRectF _bound_rect; //文本的边界矩形
	WWorldPointF _rotate_pt; //文本的旋转控制点
	double _fx; //用于控制文本的放缩
	double _fy; //用于控制文本的放缩
	bool _dragging; //文本是否在拖动
};

#endif