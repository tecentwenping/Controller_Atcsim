/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wbrush.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫʵ��WBrush��
  ����  ����:   
******************************************************************************/
#ifndef _WBRUSH_H_
#define _WBRUSH_H_

#include "../wdllimport.h"
#include "wcolor.h"
#include "wenums.h"

/** 
 \brief                 ����ΪGDI�еĻ�ˢ
\details   WBrush����������Ԫ�أ���ʽ����ɫ
 \author    ����
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