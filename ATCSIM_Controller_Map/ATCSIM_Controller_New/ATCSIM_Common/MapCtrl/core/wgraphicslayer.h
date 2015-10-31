/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicslayer.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsLayer��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_LAYER_H_
#define _WGRAPHICS_LAYER_H_

#include <set>
#include <vector>
#include "../wdllimport.h"
#include "wpen.h"
#include "wbrush.h"
#include "wworldline.h"
#include "wworldrect.h"
#include "wworldpolyline.h"
#include "wworldpolygon.h"

class WPainter;
class WGraphicsItem;
class WGraphicsView;
class WGraphicsScene;
class WGraphicsArcItem;
class WGraphicsLineItem;
class WGraphicsTextItem;
class WGraphicsRectItem;
class WGraphicsPointItem;
class WGraphicsEllipseItem;
class WGraphicsPolylineItem;
class WGraphicsPolygonItem;
class WGraphicsRichTextItem;

/** 
 \brief                 ������Ҫʵ�ֳ����е�ͼ�������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsLayer //������ͼ�����
{
public:
	friend class WGraphicsScene;

	explicit WGraphicsLayer(WGraphicsScene* scene, int layer = 0);
	~WGraphicsLayer();

	/**
	\brief      layer
	\Access    public 
	\retval     int
	\remark     ͼ���id
	*/
	int layer() const;

	/**
	\brief      visible
	\Access    public 
	\retval     bool
	\remark    ͼ���Ƿ���ӣ�����������������������ͼԪ�������� 
	*/
	bool visible() const;

	/**
	\brief      editable
	\Access    public 
	\retval     bool
	\remark     ͼ���Ƿ�ɱ༭
	*/
	bool editable() const;

	/**
	\brief      scene
	\Access    public 
	\retval     WGraphicsScene*
	\remark     ͼ�����еĳ���
	*/
	WGraphicsScene* scene() const;
	
	void setLayer(int layer); //����ͼ��id
	void setVisible(bool visible); //����ͼ���Ƿ����
	void setEditable(bool editable); //����ͼ���Ƿ�ɱ༭

	//ͼ��������ͼԪ
	WGraphicsLineItem* addLine(const WWorldLineF& line, const WPen& pen = WPen(), bool updating = false);
	WGraphicsRectItem* addRect(const WWorldRectF& rect, double angle = 0.0, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsEllipseItem* addEllipse(const WWorldRectF& rect, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsPolygonItem* addPolygon(const WWorldPolygonF& polygon, const WPen& pen = WPen(), const WBrush& brush = WBrush(), bool updating = false);
	WGraphicsPolylineItem* addPolyline(const WWorldPolylineF& polyline, const WPen& pen = WPen(), bool updating = false);
	WGraphicsArcItem* addArc(const WWorldRectF& rect, double startAngle, double endAngle, const WPen& pen = WPen(), bool updating = false);
	WGraphicsTextItem* addText(const WWorldPointF& pos, const std::string& text, bool updating = false);
	WGraphicsRichTextItem* addRichText(const WWorldPointF& pos, const std::string& text, bool updating = false);
	WGraphicsPointItem* addPoint(const WWorldPointF& pos, const WPen& pen = WPen(), bool updating = false);

	//ͼ�����Ƿ����ĳ��ͼԪ
	bool hasItem(WGraphicsItem* item) const;
	//ͼ��������ͼԪ����
	std::vector<WGraphicsItem*> items() const;
	//��ͼ��������ָ��ͼԪ��ͼ�㽫�������ɾ��ͼԪ
	WGraphicsItem* addItem(WGraphicsItem* item, bool updating = false);
	//��ͼ��������ָ��ͼԪ�ĸ���
	WGraphicsItem* addItem(const WGraphicsItem& item, bool updating = false);
	//��ͼ����ɾ��ָ��ͼԪ
	bool removeItem(WGraphicsItem* item, bool updating = false, bool opStack = false);
	//��ͼ����ɾ������ͼԪ
	void removeAllItems(bool updating = false);
	//��Ⱦͼ��
	void render(WPainter* painter, const WWorldRectF& rect, WGraphicsView* view) const;
	//�ָ�ɾ����ͼԪ
	void recoverItem(WGraphicsItem* item, bool updating = false);
	
private:
	//��ջ���վ
	void clearGarbage();

	template<class Item>
	Item* addItemPrivate(Item* item, bool updating);

private:
	int _layer; //ͼ��ID
	bool _visible; //ͼ���Ƿ����
	bool _editable; //ͼ���Ƿ�ɱ༭
	WGraphicsScene* _scene; //ͼ�����ڳ���
	std::set<WGraphicsItem*> _items; //ͼ���������ͼԪ
	std::set<WGraphicsItem*> _items_garbage; //ͼ���б�ɾ����ͼԪ�����ڳ�������
};

struct WLayerCmp //ͼ��Ƚϲ����º�������
{
	bool operator()(const WGraphicsLayer* lhs, const WGraphicsLayer* rhs) const
	{
		return lhs->layer() < rhs->layer();
	}
};

#endif