/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wqtpainter.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WQtPainter��
  ����  ����:   
******************************************************************************/
#ifndef _WQT_PAINTER_H_
#define _WQT_PAINTER_H_

#include <QPainter>
#include "../core/wpainter.h"

class WGraphicsView;
class WMapWidget;

/** 
 \brief                 ������Ҫ����Qt�Ļ�ͼAPIʵ��WPainter�ӿ�
\details		������Ҫ���WPainter�ඨ�����е���ӿڣ�ÿ���ӿڵĺ�����ο�WPainter�ࣩ��
				��WPainter��һ��ʵ�ַ�ʽ��
				����Ҫ����QPainter��Ĺ��ܣ����Խ����࿴��QPainter��Ĵ���
 \author    ����
\date      2013/05/22
*/
class WQtPainter : public WPainter
{
public:
	explicit WQtPainter(WMapWidget* w, QPainter* dc = 0);

	void setDc(QPainter* dc);
	QPainter* dc();

	virtual WGraphicsView* device() const;

	virtual WPen pen() const;
	virtual WBrush brush() const;
	virtual WFont font() const;
	virtual WMatrix worldTransform() const;

	virtual void setPen(const WPen& pen);
	virtual void setBrush(const WBrush& brush);
	virtual void setFont(const WFont& font);
	virtual void setWorldTransform(const WMatrix& matrix, bool combine = false);

	virtual void save();
	virtual void restore();

	virtual Ws::BGMode backgroundMode() const;
	virtual void setBackgroundMode(Ws::BGMode mode);

	virtual void drawLine(const WWorldLineF& line);
	virtual void drawRect(const WWorldRectF& rect);
	virtual void drawPolygon(const WWorldPolygonF& polygon);
	virtual void drawEllipse(const WWorldRectF& rect);
	virtual void drawEllipse(const WWorldPoint& center, double rx, double ry);
	virtual void drawArc(const WWorldRectF& rect, double startAngle, double spanAngle);
	virtual void drawChord(const WWorldRectF& rect, double startAngle, double spanAngle);
	virtual void drawPie(const WWorldRectF& rect, double startAngle, double spanAngle);
	virtual void drawPolyline(const WWorldPolylineF& polyline);
	virtual void drawText(const WWorldPointF& pos, const std::string& text);
	virtual void drawText(const WWorldPointF& pos, const std::wstring& text);
	virtual void drawText(const WWorldRectF& r, int flags, const std::string& text, WWorldRectF* boundingRect = 0);
	virtual void drawText(const WWorldRectF& r, int flags, const std::wstring& text, WWorldRectF* boundingRect = 0);
	virtual void drawStaticText(const WWorldPointF& pos, const std::string& text);
	virtual void drawPixmap(const WWorldPointF& p, const WPixmap& pixmap);
	virtual void drawPixmap(const WWorldRectF& r, const WPixmap& pixmap);
	virtual void drawPoint(const WWorldPointF& point);
	virtual WWorldSizeF deviceSize();
	virtual void setRenderHint(Ws::RenderHint hint, bool on = true);
private:
	QPainter* _dc;
	WMapWidget* _w;
};

#endif