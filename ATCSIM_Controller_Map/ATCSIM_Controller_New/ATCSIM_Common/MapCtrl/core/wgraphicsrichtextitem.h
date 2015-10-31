/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsrichtextitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsRichTextItem及其核心数据类WRichTextItemData
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_RICH_TEXT_ITEM_H_
#define _WGRAPHICS_RICH_TEXT_ITEM_H_

#include <string>
#include "../wdllimport.h"
#include "wgraphicsitem.h"

class WMatrix;

/** 
 \brief                 富文本图元WGraphicsRichTextItem的核心数据类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WRichTextItemData : public WItemData
{
public:
	explicit WRichTextItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const std::string& t = std::string(), double ag = 0.0) 
		: WItemData(typ), pos(p), text(t), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WRichTextItemData* copy() const { return new WRichTextItemData(*this); }

	WWorldPointF pos; //富文本位置
	std::string text; //富文本的文本，可以设置css样式哦
	double angle; //富文本的旋转角度
};

/** 
 \brief                 富文本图元，此类的实现手法和WGraphicsTextItem一致，不再赘述
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsRichTextItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsRichTextItem)

public:
	typedef WRichTextItemData data_type;

public:
	explicit WGraphicsRichTextItem(const WWorldPointF& p, const std::string& t = std::string(), double ag = 0.0);
	explicit WGraphicsRichTextItem(data_type* d = 0);

	WWorldPointF pos() const;
	std::string text() const;
	double angle() const;

	void setPos(const WWorldPointF& p, bool update =false, bool opStack = false);
	void setText(const std::string& t, bool update = false, bool opStack = false);
	void setAngle(double angle, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	enum { Type = TYPE_RICH_TEXT_ITEM };
	virtual int type() const;

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsRichTextItem* copy() const;

	virtual void translate(const WWorldPointF& offset);

private:
	void updateBoundSize();
	void updateBoundRect();
	WMatrix getRotateMatrix() const;
	WMatrix getRotateMatrix_1() const;

private:
	int _select_flag;
	WWorldRectF _bound_rect;
	WWorldSizeF _bound_size;
	WWorldPointF _rotate_pt;
	bool _dragging;
};

#endif