/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wqtpainter.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WQtPainter类
  【其  它】:   
******************************************************************************/
#ifndef _WQT_PAINTER_H_
#define _WQT_PAINTER_H_

#include <QPainter>
#include "../core/wpainter.h"

class WGraphicsView;
class WMapWidget;

/** 
 \brief                 此类主要基于Qt的绘图API实现WPainter接口
\details		此类主要完成WPainter类定义所有的虚接口（每个接口的含义请参考WPainter类），
				是WPainter的一种实现方式，
				它主要依靠QPainter类的功能，可以将此类看作QPainter类的代理
 \author    陈龙
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