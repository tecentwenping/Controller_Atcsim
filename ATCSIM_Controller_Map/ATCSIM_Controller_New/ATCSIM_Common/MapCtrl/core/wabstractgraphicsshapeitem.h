/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wabstractgraphicsshapeitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要实现WAbstractShapeItem和WAbstractShapeItemData类
  【其  它】:   
******************************************************************************/
#ifndef _WABSTRACT_GRAPHICS_SHAPE_ITEM_H_
#define _WABSTRACT_GRAPHICS_SHAPE_ITEM_H_

#include "../wdllimport.h"
#include "wpen.h"
#include "wbrush.h"
#include "wgraphicsitem.h"

/** 
 \brief                 WAbstractShapeItem的数据类，主要包含画笔WPen和画刷WBrush两个属性
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WAbstractShapeItemData : public WItemData
{
public:
	explicit WAbstractShapeItemData(int typ = 0, const WBrush& b = WBrush(), const WPen& p = WPen()) : WItemData(typ), brush(b), pen(p) {}
	
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WAbstractShapeItemData* copy() const { return new WAbstractShapeItemData(*this); }

	WBrush brush; //绘制填充区域的画刷
	WPen pen; //绘制填充区域的画笔
};

/** 
 \brief                 此类是一个基类，它为所有有形状的图元提供了抽象
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WAbstractGraphicsShapeItem : public WGraphicsItem
{
	RTTI_DECL(WAbstractGraphicsShapeItem)

public:
	typedef WAbstractShapeItemData data_type;

public:
	explicit WAbstractGraphicsShapeItem(const WBrush& brush, const WPen& pen = WPen());
	explicit WAbstractGraphicsShapeItem(data_type* d = 0);

	WBrush brush() const;
	WPen pen() const;

	/**
	\brief      setBrush
	\Access    public 
	\param  const WBrush & brush
	\param  bool update 是否立即进行一次刷新
	\param  bool opStack 是否将操作进栈
	\retval     void
	\remark     设置画刷
	*/
	void setBrush(const WBrush& brush, bool update = false, bool opStack = false);

	/**
	\brief      setPen
	\Access    public 
	\param  const WPen & pen
	\param  bool update
	\param  bool opStack
	\retval     void
	\remark    设置画笔，update和opStack参数和上面的含义一致 
	*/
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	data_type* data();
	const data_type* data() const;

	enum { Type = TYPE_SHAPE_ITEM };
	virtual int type() const;
};

#endif