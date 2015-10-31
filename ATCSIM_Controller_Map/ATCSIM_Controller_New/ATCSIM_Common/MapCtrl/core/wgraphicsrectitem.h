/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsrectitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsRectItem�༰�����������WRectItemData��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_RECT_ITEM_H_
#define _WGRAPHICS_RECT_ITEM_H_

#include "../wdllimport.h"
#include "wworldrect.h"
#include "wabstractgraphicsshapeitem.h"

class WMatrix;
class WGraphicsView;

/** 
 \brief                 ������WGraphicsRectItem�ĺ���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WRectItemData : public WAbstractShapeItemData
{
public:
	explicit WRectItemData(int typ = 0, const WWorldRectF& r = WWorldRectF(), const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0) : WAbstractShapeItemData(typ, b, p), rect(r), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WRectItemData* copy() const { return new WRectItemData(*this); }

	WWorldRectF rect; //��������
	double angle; //����������ת�ĽǶ�
};

class MAPAPI WGraphicsRectItem : public WAbstractGraphicsShapeItem
{
	RTTI_DECL(WGraphicsRectItem)

public:
	typedef WRectItemData data_type;

public:
	explicit WGraphicsRectItem(const WWorldRectF& r, const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0);
	explicit WGraphicsRectItem(data_type* d = 0);

	WWorldRectF rect() const;
	double angle() const;

	void setRect(const WWorldRectF& rect, bool update = false, bool opStack = false);
	void setAngle(double ag, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	virtual void keyPressEvent(WKeyEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsRectItem* copy() const;

	enum { Type = TYPE_RECT_ITEM };
	virtual int type() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;

	/**
	\brief      getCursorShape
	\Access    public 
	\param  int flag
	\retval     Ws::CursorShape
	\remark     ����ѡ��״̬��ȡ������״
	*/
	Ws::CursorShape getCursorShape(int flag);

	virtual void translate(const WWorldPointF& offset);

	/**
	\brief      updateCp
	\Access    public 
	\retval     void
	\remark     ���¿��Ƶ���Ϣ
	*/
	void updateCp();

	/**
	\brief      getRotateMatrix
	\Access    public 
	\retval     WMatrix
	\remark     ��ȡ��ת����
	*/
	WMatrix getRotateMatrix() const;

	/**
	\brief      getRotateMatrix_1
	\Access    public 
	\retval     WMatrix
	\remark     ��ȡ��ת����������
	*/
	WMatrix getRotateMatrix_1() const;

protected:
	int _select_flag; //ѡ�б�ʶ
	WWorldPointF _cp[8]; //control points
	WWorldPointF _rotate_pt; //��ת���Ƶ�
	bool _dragging; //�����Ƿ����϶�
};

#endif