/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wcolor.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要完成WColor
  【其  它】:   
******************************************************************************/
#ifndef _WCOLOR_H_
#define _WCOLOR_H_

#include "../wdllimport.h"

typedef unsigned int WRgb; //颜色整数值

/** 
 \brief                 此类代表GDI中的颜色
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WColor
{
public:
	WColor();
	explicit WColor(WRgb color);

	/**
	\brief      WColor
	\Access    public 
	\param  int r
	\param  int g
	\param  int b
	\param  int a alpha透明度值
	\retval     
	\remark     
	*/
	WColor(int r, int g, int b, int a = 255);

	int red() const;
	int green() const;
	int blue() const;
	int alpha() const;

	/**
	\brief      rgb
	\Access    public 
	\retval     WRgb
	\remark    返回颜色的rgb数值，其中alpha被忽略 
	*/
	WRgb rgb() const; //0 r g b

	/**
	\brief      rgba
	\Access    public 
	\retval     WRgb
	\remark    返回argb数值 
	*/
	WRgb rgba() const; //a r g b

	/**
	\brief      colorref
	\Access    public 
	\retval     WRgb
	\remark    返回bgr数值（请注意不是rgb），其中alpha被忽略 
	*/
	WRgb colorref() const; // 0 b g r

	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);
	void setAlpha(int a);
	void setRgb(WRgb color);
	void setRgba(WRgb color);
	void setRgb(int r, int g, int b, int a = 255);

	/**
	\brief      darker
	\Access    public 
	\param  double factor
	\retval     WColor
	\remark    让颜色变深，即是设置alpha的数值 
	*/
	WColor darker(double factor) const;

	/**
	\brief      lighter
	\Access    public 
	\param  double factor
	\retval     WColor
	\remark    让颜色变浅，即是设置alpha的数值 
	*/
	WColor lighter(double factor) const;

	WColor opposite() const;

	bool equal(const WColor& other) const;

private:
	unsigned char _r;
	unsigned char _g;
	unsigned char _b;
	unsigned char _a;
};

inline bool operator==(const WColor& lhs, const WColor& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const WColor& lhs, const WColor& rhs)
{
	return !(lhs == rhs);
}

#endif