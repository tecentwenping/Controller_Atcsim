/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicspolylineitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsPolylineItem�������������WPolylineItemData
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_POLYLINE_ITEM_H_
#define _WGRAPHICS_POLYLINE_ITEM_H_

#include <vector>
#include "../wdllimport.h"
#include "wpen.h"
#include "wgraphicsitem.h"
#include "wworldpolyline.h"

/** 
 \brief                 ������WGraphicsPolylineItem�ĺ���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WPolylineItemData : public WItemData
{
public:
	explicit WPolylineItemData(int typ = 0, const WWorldPolylineF& p = WWorldPolylineF(), const WPen& pn = WPen())
		: WItemData(typ), polyline(p), pen(pn) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WPolylineItemData* copy() const { return new WPolylineItemData(*this); }

	WPen pen; //�������ߵĻ���
	WWorldPolylineF polyline; //����
};

/** 
 \brief                 ����ͼԪ�����๦�ܵ�ʵ���ַ���WGraphicsPolygonItem���ƣ�����׸��
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsPolylineItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsPolylineItem)

public:
	typedef WPolylineItemData data_type;

public:
	explicit WGraphicsPolylineItem(const WWorldPolylineF& p, const WPen& pn = WPen());
	explicit WGraphicsPolylineItem(data_type* d = 0);

	WWorldPolylineF polyline() const;
	const std::vector<WWorldPointF>& points() const;
	WPen pen() const;

	void setPen(const WPen& pen, bool update = false, bool opStack = false);
	void setPolyline(const WWorldPolylineF& p, bool update = false, bool opStack = false);
	void setPoints(const std::vector<WWorldPointF>& pts, bool update = false, bool opStack = false);
	bool setPoint(unsigned index, const WWorldPointF& pos, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsPolylineItem* copy() const;

	enum { Type = TYPE_POLYLINE_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	virtual void onContextMenu(Ws::ContextMenuFlag flag);

	virtual void translate(const WWorldPointF& offset);

private:
	int _select_flag;
	bool _dragging;
};

#endif