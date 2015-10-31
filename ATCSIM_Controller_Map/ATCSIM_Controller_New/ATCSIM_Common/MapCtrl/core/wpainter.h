/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wpainter.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WPainter接口
  【其  它】:   
******************************************************************************/
#ifndef _WPAINTER_H_
#define _WPAINTER_H_

#include <string>
#include "../wdllimport.h"
#include "wpen.h"
#include "wfont.h"
#include "wbrush.h"
#include "wmatrix.h"
#include "wenums.h"
#include "wworldline.h"
#include "wworldsize.h"
#include "wworldrect.h"
#include "wworldpolyline.h"
#include "wworldpolygon.h"

class WPixmap;
class WGraphicsView;

/** 
 \brief                 此类主要定义了设备上下文需要实现的一些接口
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WPainter
{
public:
	virtual ~WPainter() {}

	/**
	\brief      pen
	\Access    virtual public 
	\retval     WPen
	\remark    获取画笔的接口 
	*/
	virtual WPen pen() const = 0;

	/**
	\brief      brush
	\Access    virtual public 
	\retval     WBrush
	\remark    获取画刷的接口 
	*/
	virtual WBrush brush() const = 0;

	/**
	\brief      font
	\Access    virtual public 
	\retval     WFont
	\remark    获取字体的接口 
	*/
	virtual WFont font() const = 0;

	/**
	\brief      worldTransform
	\Access    virtual public 
	\retval     WMatrix
	\remark    获取坐标转换矩阵的接口 
	*/
	virtual WMatrix worldTransform() const = 0;

	/**
	\brief      device
	\Access    virtual public 
	\retval     WGraphicsView*
	\remark    获取设备对应的视图接口 
	*/
	virtual WGraphicsView* device() const = 0;

	/**
	\brief      setPen
	\Access    virtual public 
	\param  const WPen & pen
	\retval     void
	\remark     设置画笔的接口
	*/
	virtual void setPen(const WPen& pen) = 0;

	/**
	\brief      setBrush
	\Access    virtual public 
	\param  const WBrush & brush
	\retval     void
	\remark    设置画刷的接口 
	*/
	virtual void setBrush(const WBrush& brush) = 0;

	/**
	\brief      setFont
	\Access    virtual public 
	\param  const WFont & font
	\retval     void
	\remark    设置字体的接口 
	*/
	virtual void setFont(const WFont& font) = 0;

	/**
	\brief      setWorldTransform
	\Access    virtual public 
	\param  const WMatrix & matrix
	\param  bool combine
	\retval     void
	\remark    设置设备的坐标转换矩阵 
	*/
	virtual void setWorldTransform(const WMatrix& matrix, bool combine = false) = 0;

	/**
	\brief      backgroundMode
	\Access    virtual public 
	\retval     Ws::BGMode
	\remark    背景模式的获取接口 
	*/
	virtual Ws::BGMode backgroundMode() const = 0;

	/**
	\brief      setBackgroundMode
	\Access    virtual public 
	\param  Ws::BGMode mode
	\retval     void
	\remark   背景模式的设置接口 
	*/
	virtual void setBackgroundMode(Ws::BGMode mode) = 0;

	/**
	\brief      save
	\Access    virtual public 
	\retval     void
	\remark    保存设备上下文 
	*/
	virtual void save() = 0;

	/**
	\brief      restore
	\Access    virtual public 
	\retval     void
	\remark    恢复设备上下文 
	*/
	virtual void restore() = 0;

	/**
	\brief      drawRect
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark    绘制矩形接口 
	*/
	virtual void drawRect(const WWorldRectF& rect) = 0;

	/**
	\brief      drawLine
	\Access    virtual public 
	\param  const WWorldLineF & line
	\retval     void
	\remark    绘制直线接口 
	*/
	virtual void drawLine(const WWorldLineF& line) = 0;

	/**
	\brief      drawPolygon
	\Access    virtual public 
	\param  const WWorldPolygonF & polygon
	\retval     void
	\remark    绘制多边形接口（!!!请确保多边形至少包含三个点，并且是闭合的，否则出错后果自负） 
	*/
	virtual void drawPolygon(const WWorldPolygonF& polygon) = 0;

	/**
	\brief      drawEllipse
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark    绘制椭圆接口 
	*/
	virtual void drawEllipse(const WWorldRectF& rect) = 0;

	/**
	\brief      drawEllipse
	\Access    virtual public 
	\param  const WWorldPoint & center椭圆中心点
	\param  double rx 椭圆长半径
	\param  double ry 椭圆短半径
	\retval     void
	\remark    绘制椭圆接口 
	*/
	virtual void drawEllipse(const WWorldPoint& center, double rx, double ry) = 0;

	/**
	\brief      drawArc
	\Access    virtual public 
	\param  const WWorldRectF & rect确定椭圆的矩形
	\param  double startAngle椭圆的起始角度（startAngle / 16为真实角度，实际上1度被分成了16份）
	\param  double spanAngle椭圆的终点角度（endAngle / 16为真实角度，同上）
	\retval     void
    \remark    绘制弧线的接口 
	*/
	virtual void drawArc(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawChord
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\param  double startAngle
	\param  double spanAngle
	\retval     void
	\remark    绘制弓形接口（参数含义同上drawArc） 
	*/
	virtual void drawChord(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawPie
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\param  double startAngle
	\param  double spanAngle
	\retval     void
	\remark    绘制饼状接口（参数含义同上drawArc） 
	*/
	virtual void drawPie(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawPolyline
	\Access    virtual public 
	\param  const WWorldPolylineF & polyline
	\retval     void
	\remark    绘制折线接口 
	*/
	virtual void drawPolyline(const WWorldPolylineF& polyline) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldPointF & pos 绘制文本的起始位置
	\param  const std::string & text 文本
	\retval     void
	\remark    绘制文本接口 
	*/
	virtual void drawText(const WWorldPointF& pos, const std::string& text) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldPointF & pos 绘制文本的起始位置
	\param  const std::wstring & text 宽文本
	\retval     void
	\remark    绘制文本接口 
	*/
	virtual void drawText(const WWorldPointF& pos, const std::wstring& text) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldRectF & r文本的边界矩形区域
	\param  int flags 绘制文本的选项，请参见Ws::AlignmentFlag和Ws::TextFlag
						flags可以是上述两个枚举类型的任意个组合
	\param  const std::string & text 文本
	\param[OUT]  WWorldRectF * boundingRect 绘制文本的实际边界矩形，默认为0
	\retval     void
	\remark     
	*/
	virtual void drawText(const WWorldRectF& r, int flags, const std::string& text, WWorldRectF* boundingRect = 0) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldRectF & r
	\param  int flags
	\param  const std::wstring & text
	\param  WWorldRectF * boundingRect
	\retval     void
	\remark    参数含义和上面的完全相同，只不过这里的文本为宽文本 
	*/
	virtual void drawText(const WWorldRectF& r, int flags, const std::wstring& text, WWorldRectF* boundingRect = 0) = 0;

	/**
	\brief      drawStaticText
	\Access    virtual public 
	\param  const WWorldPointF & pos
	\param  const std::string & text
	\retval     void
	\remark    主要用于绘制富文本 
	*/
	virtual void drawStaticText(const WWorldPointF& pos, const std::string& text) = 0;

	/**
	\brief      drawPixmap
	\Access    virtual public 
	\param  const WWorldPointF & p
	\param  const WPixmap & pixmap
	\retval     void
	\remark    在给定点绘制图片接口 
	*/
	virtual void drawPixmap(const WWorldPointF& p, const WPixmap& pixmap) = 0;

	/**
	\brief      drawPixmap
	\Access    virtual public 
	\param  const WWorldRectF & r
	\param  const WPixmap & pixmap
	\retval     void
	\remark    在给定的区域内绘制图片接口 
	*/
	virtual void drawPixmap(const WWorldRectF& r, const WPixmap& pixmap) = 0;

	/**
	\brief      deviceSize
	\Access    virtual public 
	\retval     WWorldSizeF
	\remark    获取设备的对应视图大小 
	*/
	virtual WWorldSizeF deviceSize() = 0;

	//virtual const WBrush& background() const = 0;
	
	//virtual KRect boundingRect(const KRect& rect, int flags, const std::string& text) = 0;
	//virtual const WBrush& brush() const = 0;
	
	virtual void drawPoint(const WWorldPointF& point) = 0;
	//virtual void drawPolygon(const KPolygon& polygon) = 0;
	//virtual void drawPolyline(const KPolygon& polygon) = 0;
	
	
	/**
	\brief      setRenderHint
	\Access    public 
	\param  RenderHint hint
	\param  bool on
	\retval     void
	\remark     
	*/
	virtual void setRenderHint ( Ws::RenderHint hint, bool on = true ) = 0;
};

#endif