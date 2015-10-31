/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicspointitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsPointItem��������Ӧ��������WPointItemData
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_POINT_ITEM_H
#define _WGRAPHICS_POINT_ITEM_H

#include "../wdllimport.h"
#include "wpen.h"
#include "wgraphicsitem.h"
#include "wworldpolygon.h"

class WPainter;

/** 
 \brief                 WGraphicsPointItem��ĺ���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WPointItemData : public WItemData
{
public:
	explicit WPointItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const WPen& pn = WPen()) : WItemData(typ), pos(p), pen(pn) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WPointItemData* copy() const { return new WPointItemData(*this); }

	WWorldPointF pos; //���λ��
	WPen pen; //���Ƶ�Ļ���
};

/** 
 \brief                 ��ͼԪ
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsPointItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsPointItem)

public:
	typedef WPointItemData data_type;

public:
	explicit WGraphicsPointItem(const WWorldPointF& p, const WPen& pn = WPen());
	explicit WGraphicsPointItem(data_type* d = 0);

	WWorldPointF pos() const;
	WPen pen() const;

	void setPos(const WWorldPointF& pos, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsPointItem* copy() const;

	enum { Type = TYPE_POINT_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	virtual void translate(const WWorldPointF& offset);

private:
	void updateCp();

private:
	int _select_flag; //ѡ�б�ʶ
	WWorldPolygonF _cp; //���Ӧ�������ε�������
	bool _dragging; //�Ƿ����϶�
};


#endif