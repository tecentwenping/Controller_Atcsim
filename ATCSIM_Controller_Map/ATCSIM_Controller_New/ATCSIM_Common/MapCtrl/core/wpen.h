/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wpen.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WPen��
  ����  ����:   
******************************************************************************/
#ifndef _WPEN_H_	
#define _WPEN_H_

#include "../wdllimport.h"
#include "wcolor.h"
#include "wenums.h"

/** 
 \brief        ������Ҫ���GDI�еĻ����豸
				 ������Ҫ�����Σ���ɫ���������Ҫ�����	
\details   
 \author    ����
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
	\param  Ws::PenStyle ps ���ʵ�����
	\param  const WColor & color ���ʵ���ɫ
	\param  double width ���ʵĿ��
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
	\remark    �ж����������Ƿ���ȣ��������Ҫ����ȼ�Ϊ��� 
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