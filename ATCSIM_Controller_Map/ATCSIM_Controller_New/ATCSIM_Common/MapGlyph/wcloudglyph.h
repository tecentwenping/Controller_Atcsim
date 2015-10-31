/********************************************************************
��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾	
���ļ�����:  wcloudglyph.h
����  �ߡ�:  @yyg
����  ����:  1.0
��������ڡ�:2013/06/25	
����  ����:  

����  ����:   
*********************************************************************/
#ifndef WCLOUDGLYPH_H
#define WCLOUDGLYPH_H

#include "core/wgraphicsitem.h"
#include "core/wgraphicspolygonitem.h"

class WCloudGlyph;

class WCloudGlyphItemData :public WPolygonItemData
{
public:
	WCloudGlyphItemData();
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WColor m_color;
};

class WCloudGlyph :public WGraphicsPolygonItem
{
	RTTI_DECL(WCloudGlyph)

public:
	typedef WCloudGlyphItemData data_type;

public:
	explicit WCloudGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //ͼԪ�ı߽�����

	data_type* data(); //ͼԪ��������
	const data_type* data() const;
};
#endif