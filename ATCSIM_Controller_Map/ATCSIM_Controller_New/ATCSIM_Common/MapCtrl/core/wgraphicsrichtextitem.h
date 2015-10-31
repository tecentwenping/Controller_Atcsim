/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsrichtextitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsRichTextItem�������������WRichTextItemData
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_RICH_TEXT_ITEM_H_
#define _WGRAPHICS_RICH_TEXT_ITEM_H_

#include <string>
#include "../wdllimport.h"
#include "wgraphicsitem.h"

class WMatrix;

/** 
 \brief                 ���ı�ͼԪWGraphicsRichTextItem�ĺ���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WRichTextItemData : public WItemData
{
public:
	explicit WRichTextItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const std::string& t = std::string(), double ag = 0.0) 
		: WItemData(typ), pos(p), text(t), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WRichTextItemData* copy() const { return new WRichTextItemData(*this); }

	WWorldPointF pos; //���ı�λ��
	std::string text; //���ı����ı�����������css��ʽŶ
	double angle; //���ı�����ת�Ƕ�
};

/** 
 \brief                 ���ı�ͼԪ�������ʵ���ַ���WGraphicsTextItemһ�£�����׸��
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsRichTextItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsRichTextItem)

public:
	typedef WRichTextItemData data_type;

public:
	explicit WGraphicsRichTextItem(const WWorldPointF& p, const std::string& t = std::string(), double ag = 0.0);
	explicit WGraphicsRichTextItem(data_type* d = 0);

	WWorldPointF pos() const;
	std::string text() const;
	double angle() const;

	void setPos(const WWorldPointF& p, bool update =false, bool opStack = false);
	void setText(const std::string& t, bool update = false, bool opStack = false);
	void setAngle(double angle, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	enum { Type = TYPE_RICH_TEXT_ITEM };
	virtual int type() const;

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsRichTextItem* copy() const;

	virtual void translate(const WWorldPointF& offset);

private:
	void updateBoundSize();
	void updateBoundRect();
	WMatrix getRotateMatrix() const;
	WMatrix getRotateMatrix_1() const;

private:
	int _select_flag;
	WWorldRectF _bound_rect;
	WWorldSizeF _bound_size;
	WWorldPointF _rotate_pt;
	bool _dragging;
};

#endif