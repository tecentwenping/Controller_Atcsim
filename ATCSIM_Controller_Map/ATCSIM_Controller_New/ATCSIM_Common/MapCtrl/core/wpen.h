/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wpen.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WPen类
  【其  它】:   
******************************************************************************/
#ifndef _WPEN_H_	
#define _WPEN_H_

#include "../wdllimport.h"
#include "wcolor.h"
#include "wenums.h"

/** 
 \brief        此类主要完成GDI中的画笔设备
				 画笔主要由线形，颜色，宽度三个要素组成	
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WPen
{
public:
	WPen();
	explicit WPen(Ws::PenStyle ps);
	explicit WPen(const WColor& color);
	explicit WPen(double width);
	/**
	\brief      WPen
	\Access    public 
	\param  Ws::PenStyle ps 画笔的线形
	\param  const WColor & color 画笔的颜色
	\param  double width 画笔的宽度
	\retval     
	\remark   
	*/
	WPen(Ws::PenStyle ps, const WColor& color, double width);

	Ws::PenStyle style() const;
	WColor color() const;
	double width() const;

	void setStyle(Ws::PenStyle ps);
	void setColor(const WColor& color);
	void setWidth(double width);

	/**
	\brief      equal
	\Access    public 
	\param  const WPen & other
	\retval     bool
	\remark    判断两个画笔是否相等，如果三个要素相等即为相等 
	*/
	bool equal(const WPen& other) const;

private:
	Ws::PenStyle _ps;
	WColor _color;
	double _width;
};

inline bool operator==(const WPen& lhs, const WPen& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const WPen& lhs, const WPen& rhs)
{
	return !(lhs == rhs);
}

#endif