/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsellipseitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/28
  ����  ����:  ���ļ���Ҫ����WGraphicsEllipseItem
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_ELLIPSE_ITEM_H_
#define _WGRAPHICS_ELLIPSE_ITEM_H_

#include "../wdllimport.h"
#include "wgraphicsrectitem.h"

/** 
 \brief                 ��ԲͼԪ
\details   
 \author    ����
\date      2013/05/28
*/
class MAPAPI WGraphicsEllipseItem : public WGraphicsRectItem
{
	RTTI_DECL(WGraphicsEllipseItem)

public:
	explicit WGraphicsEllipseItem(const WWorldRectF& r, const WBrush& b = WBrush(), 
		const WPen& p = WPen(), double ag = 0.0);
	explicit WGraphicsEllipseItem(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual bool contains(const WWorldPointF& point) const;

	enum { Type = TYPE_ELLIPSE_ITEM };
	virtual int type() const;

	virtual WGraphicsEllipseItem* copy() const;

	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const;
};

#endif