/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicslineitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsLineItem������������WLineItemData��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_LINE_ITEM_H
#define _WGRAPHICS_LINE_ITEM_H

#include "../wdllimport.h"
#include "wpen.h"
#include "wworldline.h"
#include "wgraphicsitem.h"

class WPainter;

/** 
 \brief                 WGraphicsLineItem��ĺ�������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WLineItemData : public WItemData
{
public:
	explicit WLineItemData(int typ = 0, const WWorldLineF& l = WWorldLineF(), const WPen& p = WPen()) : WItemData(typ), line(l), pen(p) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WLineItemData* copy() const { return new WLineItemData(*this); }

	WWorldLineF line; //ֱ��
	WPen pen; //����
};

/** 
 \brief                 ֱ��ͼԪ��
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsLineItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsLineItem)

public:
	typedef WLineItemData data_type;

public:
	explicit WGraphicsLineItem(const WWorldLineF& l, const WPen& p = WPen());
	explicit WGraphicsLineItem(data_type* d = 0);

	WWorldLineF line() const;
	WPen pen() const;

	void setLine(const WWorldLineF& line, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	virtual void keyPressEvent(WKeyEvent* event);

	data_type* data();
	const data_type* data() const;

	void showArraw(bool show = true, bool update = false);
	bool isArrawShow() const;

	virtual WGraphicsLineItem* copy() const;

	enum { Type = TYPE_LINE_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	virtual void translate(const WWorldPointF& offset);

private:
	int _select_flag; //ѡ�б�ʶ
	bool _show_arraw; //�Ƿ���ʾֱ�ߣ�ʸ�����ļ�ͷ
	bool _dragging; //ֱ���Ƿ����϶�
};

#endif