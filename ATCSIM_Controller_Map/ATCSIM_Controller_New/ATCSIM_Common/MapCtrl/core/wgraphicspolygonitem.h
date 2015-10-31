
/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicspolygonitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsPolygonItem�����Ӧ��������WPolygonItemData��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_POLYGON_ITEM_H_
#define _WGRAPHICS_POLYGON_ITEM_H_

#include "../wdllimport.h"
#include "wworldpolygon.h"
#include "wabstractgraphicsshapeitem.h"

/** 
 \brief                 ������WGraphicsPolygon���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WPolygonItemData : public WAbstractShapeItemData
{
public:
	explicit WPolygonItemData(int typ = 0, const WWorldPolygonF& p = WWorldPolygonF(), const WBrush& b = WBrush(), const WPen& pn = WPen()) 
		: WAbstractShapeItemData(typ, b, pn), polygon(p) {}
	
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WPolygonItemData* copy() const { return new WPolygonItemData(*this); }

	WWorldPolygonF polygon; //�����
};

/** 
 \brief                 �����ͼԪ
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsPolygonItem : public WAbstractGraphicsShapeItem
{
	RTTI_DECL(WGraphicsPolygonItem)

public:
	typedef WPolygonItemData data_type;

public:
	explicit WGraphicsPolygonItem(const WWorldPolygonF& p, const WBrush& b = WBrush(), const WPen& pn = WPen());
	explicit WGraphicsPolygonItem(data_type* d = 0);
	
	//���¾�������/��ȡ��������ݵĽӿ�
	WWorldPolygonF polygon() const;
	const std::vector<WWorldPointF>& points() const;
	void setPolygon(const WWorldPolygonF& polygon, bool update = false, bool opStack = false);
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

	virtual WGraphicsPolygonItem* copy() const;

	enum { Type = TYPE_POLYGON_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      onContextMenu
	\Access    virtual public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     ��Ӧ�Ҽ��˵�
	*/
	virtual void onContextMenu(Ws::ContextMenuFlag flag);

	virtual void translate(const WWorldPointF& offset);

private:
	/**
	\brief      updateCp
	\Access    private 
	\retval     void
	\remark     ���¿��Ƶ�
	*/
	void updateCp();

private:
	int _select_flag; //ѡ�б�ʶ����16λ��ѡ��λ��ʶ����16λ��ѡ�п��Ƶ��id
	std::vector<WWorldPointF> _cp; //����α�ѡ��ʱ�����Ŀ��Ƶ�
	bool _dragging; //������Ƿ����϶�
};

#endif