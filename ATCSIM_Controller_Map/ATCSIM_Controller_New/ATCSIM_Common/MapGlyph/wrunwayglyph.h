#ifndef _WRUNWAY_GLYPH_H_
#define _WRUNWAY_GLYPH_H_

#include "core/wgraphicsrectitem.h"
#include "wworldline.h"

class WRunwayItemData : public WItemData
{
public:
	WRunwayItemData();

public:
	static const size_t GENERIC_SCALE_COUNT = 2;
	static const size_t DETAIL_SCALE_COUNT = 5;
	static const bool SHOW_PROLONG = true;

public:
	WPen m_pen;
	double m_dProlongLength; //�ӳ��߳���
	size_t m_genericScaleCount; //�ӳ��ߴ�̶ȸ���
	size_t m_detailScaleCount; //�ӳ���С�̶ȸ���
	bool m_bShowProlong; //�Ƿ���ʾ�ӳ���
	WPointF m_pointStart; // ����
	WLineF m_line; // ��㵽�յ�
	WSizeF m_size; // ������
	double m_angle; // �Ƕ�
};

class WRunwayGlyph : public WGraphicsItem
{
	RTTI_DECL(WRunwayGlyph)

public:
	typedef WRunwayItemData data_type;

public:
	explicit WRunwayGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const; //ͼԪ�ı߽�����

	data_type* data(); //ͼԪ��������
	const data_type* data() const;
};

#endif