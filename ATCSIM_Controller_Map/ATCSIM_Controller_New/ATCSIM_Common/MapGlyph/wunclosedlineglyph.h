#ifndef _WUNCLOSEDLINEGLYPH_H
#define _WUNCLOSEDLINEGLYPH_H

#include "core/wgraphicsitem.h"
#include "core/wgraphicspolylineitem.h"

class WUnclosedLineItemData : public WPolylineItemData
{
public:
	WUnclosedLineItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	void SetLineStyle(Ws::PenStyle style);//����ģ������Ч��

public:
	WColor m_color;
	std::string m_sName;
};

class WUnclosedLineGlyph : public WGraphicsPolylineItem
{
	RTTI_DECL(WUnclosedLineGlyph)

public:
	typedef WUnclosedLineItemData data_type;

public:
	explicit WUnclosedLineGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //ͼԪ�ı߽�����

	data_type* data(); //ͼԪ��������
	const data_type* data() const;
};



#endif