/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wcolor.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫ���WColor
  ����  ����:   
******************************************************************************/
#ifndef _WCOLOR_H_
#define _WCOLOR_H_

#include "../wdllimport.h"

typedef unsigned int WRgb; //��ɫ����ֵ

/** 
 \brief                 �������GDI�е���ɫ
\details   
 \author    ����
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
	\param  int a alpha͸����ֵ
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
	\remark    ������ɫ��rgb��ֵ������alpha������ 
	*/
	WRgb rgb() const; //0 r g b

	/**
	\brief      rgba
	\Access    public 
	\retval     WRgb
	\remark    ����argb��ֵ 
	*/
	WRgb rgba() const; //a r g b

	/**
	\brief      colorref
	\Access    public 
	\retval     WRgb
	\remark    ����bgr��ֵ����ע�ⲻ��rgb��������alpha������ 
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
	\remark    ����ɫ�����������alpha����ֵ 
	*/
	WColor darker(double factor) const;

	/**
	\brief      lighter
	\Access    public 
	\param  double factor
	\retval     WColor
	\remark    ����ɫ��ǳ����������alpha����ֵ 
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