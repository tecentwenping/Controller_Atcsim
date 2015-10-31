/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wbrush.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要实现WBrush类
  【其  它】:   
******************************************************************************/
#ifndef _WBRUSH_H_
#define _WBRUSH_H_

#include "../wdllimport.h"
#include "wcolor.h"
#include "wenums.h"

/** 
 \brief                 此类为GDI中的画刷
\details   WBrush有两个核心元素：样式和颜色
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WBrush
{
public:
	WBrush();
	explicit WBrush(Ws::BrushStyle style);
	explicit WBrush(const WColor& color, Ws::BrushStyle style = Ws::SolidPattern);

	Ws::BrushStyle style() const;
	WColor color() const;

	void setStyle(Ws::BrushStyle style);
	void setColor(const WColor& color);

	bool equal(const WBrush& other) const;

private:
	Ws::BrushStyle _style;
	WColor _color;
};

inline bool operator==(const WBrush& lhs, const WBrush& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const WBrush& lhs, const WBrush& rhs)
{
	return !(lhs == rhs);
}

#endif