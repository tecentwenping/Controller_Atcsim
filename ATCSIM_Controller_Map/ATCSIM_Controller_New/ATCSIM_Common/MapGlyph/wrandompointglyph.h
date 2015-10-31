/******************************************************************************
��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
���ļ�����: wrandompointglyph.h
����  �ߡ�: �����
����  ����:1.0
��������ڡ�:2013/10/9
����  ����:  ���ļ���Ҫ���������ͼ��Ļ���
����  ����:   
******************************************************************************/

#ifndef _WRANDOMPOINTGLYPH_H
#define _WRANDOMPOINTGLYPH_H

#include "wpen.h"
#include "wgraphicsitem.h"
#include "wbrush.h"
#include "EnumVarible.h"
#define TYPE_RANDOM_POINT_ITEM 11


class WRandomPointItemData : public WItemData
{
public:
	WRandomPointItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	ENUM_RANDOMPOINT_TYPE m_eRandomPointType;
	WPointF m_pos;
	WPen m_pen;
	WBrush m_brush;
};

class WRandomPointGlyph : public WGraphicsItem
{
	RTTI_DECL(WRandomPointGlyph)

public:
	typedef WRandomPointItemData data_type;

	enum { Type = TYPE_RANDOM_POINT_ITEM };
	virtual int type() const;

public:
	explicit WRandomPointGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //ͼԪ�ı߽�����

	data_type* data(); //ͼԪ��������
	const data_type* data() const;
};
#endif