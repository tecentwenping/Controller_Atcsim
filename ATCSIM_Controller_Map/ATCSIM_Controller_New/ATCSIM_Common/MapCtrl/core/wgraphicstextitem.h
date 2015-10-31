/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicstextitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫʵ����WGraphicsTextItem�༰���Ӧ��������WTextItemData
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_TEXT_ITEM_H_
#define _WGRAPHICS_TEXT_ITEM_H_

#include <string>
#include "../wdllimport.h"
#include "wpen.h"
#include "wfont.h"
#include "wgraphicsitem.h"

class WMatrix;

/** 
 \brief                 WGraphicsTextItem�ĺ���������
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WTextItemData : public WItemData
{
public:
	explicit WTextItemData(int typ = 0, const WWorldPointF& p = WWorldPointF(), const std::string& t = std::string(), 
		const WFont& f = WFont(), const WPen& pn = WPen(), double ag = 0.0) 
		: WItemData(typ), pos(p), text(t), font(f), pen(pn), angle(ag) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WTextItemData* copy() const { return new WTextItemData(*this); }

	WWorldPointF pos; //�ı���λ��
	std::string text; //�ı���Ϣ
	WFont font; //�ı������� 
	WPen pen; //�����ı����õĻ���
	double angle; //�ı�����ת�Ƕ�
};

/** 
 \brief                 �ı�ͼԪ
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsTextItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsTextItem)

public:
	typedef WTextItemData data_type;

public:
	explicit WGraphicsTextItem(const WWorldPointF& pos, const std::string& text = std::string(), 
		const WFont& font = WFont(), const WPen& pen = WPen(), double angle = 0.0);
	explicit WGraphicsTextItem(data_type* d = 0);

	WWorldPointF pos() const;
	std::string text() const;
	WFont font() const;
	WPen pen() const;
	double angle() const;

	//���º����ĵڶ�����update��Ϊ�Ƿ��������³����ĺ��壬��������opStack��Ϊ�Ƿ񽫲�����ջ�ĺ���
	void setPos(const WWorldPointF& p, bool update =false, bool opStack = false);
	void setText(const std::string& t, bool update = false, bool opStack = false);
	void setFont(const WFont& f, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);
	void setAngle(double angle, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	enum { Type = TYPE_TEXT_ITEM };
	virtual int type() const;

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsTextItem* copy() const;

	virtual void translate(const WWorldPointF& offset);

private:
	/**
	\brief      updateBoundRect
	\Access    private 
	\retval     void
	\remark     �����ı��ı߽����
	*/
	void updateBoundRect();

	/**
	\brief      getRotateMatrix
	\Access    private 
	\retval     WMatrix
	\remark     ��ȡ��ת����
	*/
	WMatrix getRotateMatrix() const;

	/**
	\brief      getRotateMatrix_1
	\Access    private 
	\retval     WMatrix
	\remark     ��ȡ��ת����������
	*/
	WMatrix getRotateMatrix_1() const;

private:
	int _select_flag; //�ı���ѡ�б�ʶ
	WWorldRectF _bound_rect; //�ı��ı߽����
	WWorldPointF _rotate_pt; //�ı�����ת���Ƶ�
	double _fx; //���ڿ����ı��ķ���
	double _fy; //���ڿ����ı��ķ���
	bool _dragging; //�ı��Ƿ����϶�
};

#endif