#ifndef _WLONGLAT_GLYPH_H_
#define _WLONGLAT_GLYPH_H_

#include "wgraphicsitem.h"

const int g_max_longlat_num = 5;
//��γ��
class WLongLatItemData : public WItemData
{
public:
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

public:
	WWorldPointF m_point;//��ĳ�������
	std::string m_strText;//��γ����Ϣ
	int m_index;//������
	WRectF m_rect;//��γ�ȵ���ʾ��Χ
};

class WLongLatGlyph : public WGraphicsItem
{
	RTTI_DECL(WLongLatGlyph)

public:
	typedef WLongLatItemData data_type;
	WMatrix m_mapToViewMatrix;

public:
	explicit WLongLatGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif