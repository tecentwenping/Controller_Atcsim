/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsarcitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���������WArcItemData����WGraphicsArcItem
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_ARC_ITEM_H_
#define _WGRAPHICS_ARC_ITEM_H_

#include "../wdllimport.h"
#include "wpen.h"
#include "wworldrect.h"
#include "wgraphicsitem.h"

/** 
 \brief                 WGraphicsArcItem��������
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WArcItemData : public WItemData
{
public:
	explicit WArcItemData(int typ = 0, const WWorldRectF& r = WWorldRectF(), double s = 0.0, 
		double e = 359.99, const WPen& p = WPen()) : WItemData(typ), rect(r), startAngle(s), endAngle(e), pen(p) {}

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WArcItemData* copy() const { return new WArcItemData(*this); }

	WWorldRectF rect; //���߶�Ӧ�ľ�������
	double startAngle; //��ʼ�Ƕ�
	double endAngle; //��ֹ�Ƕ�
	WPen pen; //����
};

/** 
 \brief                 ����������еĻ���ͼԪ
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsArcItem : public WGraphicsItem
{
	RTTI_DECL(WGraphicsArcItem)

public:
	typedef WArcItemData data_type;

public:
	/**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  const WWorldRectF & r
	\param  double s
	\param  double e
	\param  const WPen & p
	\retval     
	\remark    ���湹�캯�� 
	*/
	explicit WGraphicsArcItem(const WWorldRectF& r, double s = 0.0, 
		double e = 359.99, const WPen& p = WPen());

	/**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  data_type * d
				d����Ϊ0����ʱ���ڲ��ᶯ̬����һ������
				���d��Ϊ0�����������ⲿ�����ģ��뱣֤��������new�����ģ��벻Ҫ��ջ�ϴ��������ݴ���������
				��d������������ͼԪ�����ˣ�����������ͼԪ����ͼԪ�����ʵ���ʱ��ɾ��
				���벻Ҫ���ⲿ��dɾ����
	\retval     
	\remark    �Ժ������ݽ��й��� 
	*/
	explicit WGraphicsArcItem(data_type* d = 0);

	WWorldRectF rect() const;
	double startAngle() const;
	double endAngle() const;
	WPen pen() const;

	/**
	\brief      setRect
	\Access    public 
	\param  const WWorldRectF & rect
	\param  bool update �����Ƿ��������£��Ժ�����������Եĺ����Ĵ˲������岻�䣬����׸����
	\param  bool opStack �˲����Ƿ�֧�ֳ����������Ժ�����������Եĺ����Ĵ˲������岻�䣬����׸����
	\retval     void
	\remark     
	*/
	void setRect(const WWorldRectF& rect, bool update = false, bool opStack = false);
	void setAngle(double startAngle, double endAngle, bool update = false, bool opStack = false);
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;
	virtual WWorldRectF boundingRect() const;

	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	virtual WGraphicsArcItem* copy() const;

	enum { Type = TYPE_ARC_ITEM };
	virtual int type() const;

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
	int _select_flag; //��ǰѡ�л�����һ���ֵı�ʶ
	WWorldPointF _cp[6]; //control points ���ߵĿ��Ƶ�
	bool _dragging; //�����Ƿ����϶�
};

#endif