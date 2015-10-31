/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wpainter.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WPainter�ӿ�
  ����  ����:   
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
 \brief                 ������Ҫ�������豸��������Ҫʵ�ֵ�һЩ�ӿ�
\details   
 \author    ����
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
	\remark    ��ȡ���ʵĽӿ� 
	*/
	virtual WPen pen() const = 0;

	/**
	\brief      brush
	\Access    virtual public 
	\retval     WBrush
	\remark    ��ȡ��ˢ�Ľӿ� 
	*/
	virtual WBrush brush() const = 0;

	/**
	\brief      font
	\Access    virtual public 
	\retval     WFont
	\remark    ��ȡ����Ľӿ� 
	*/
	virtual WFont font() const = 0;

	/**
	\brief      worldTransform
	\Access    virtual public 
	\retval     WMatrix
	\remark    ��ȡ����ת������Ľӿ� 
	*/
	virtual WMatrix worldTransform() const = 0;

	/**
	\brief      device
	\Access    virtual public 
	\retval     WGraphicsView*
	\remark    ��ȡ�豸��Ӧ����ͼ�ӿ� 
	*/
	virtual WGraphicsView* device() const = 0;

	/**
	\brief      setPen
	\Access    virtual public 
	\param  const WPen & pen
	\retval     void
	\remark     ���û��ʵĽӿ�
	*/
	virtual void setPen(const WPen& pen) = 0;

	/**
	\brief      setBrush
	\Access    virtual public 
	\param  const WBrush & brush
	\retval     void
	\remark    ���û�ˢ�Ľӿ� 
	*/
	virtual void setBrush(const WBrush& brush) = 0;

	/**
	\brief      setFont
	\Access    virtual public 
	\param  const WFont & font
	\retval     void
	\remark    ��������Ľӿ� 
	*/
	virtual void setFont(const WFont& font) = 0;

	/**
	\brief      setWorldTransform
	\Access    virtual public 
	\param  const WMatrix & matrix
	\param  bool combine
	\retval     void
	\remark    �����豸������ת������ 
	*/
	virtual void setWorldTransform(const WMatrix& matrix, bool combine = false) = 0;

	/**
	\brief      backgroundMode
	\Access    virtual public 
	\retval     Ws::BGMode
	\remark    ����ģʽ�Ļ�ȡ�ӿ� 
	*/
	virtual Ws::BGMode backgroundMode() const = 0;

	/**
	\brief      setBackgroundMode
	\Access    virtual public 
	\param  Ws::BGMode mode
	\retval     void
	\remark   ����ģʽ�����ýӿ� 
	*/
	virtual void setBackgroundMode(Ws::BGMode mode) = 0;

	/**
	\brief      save
	\Access    virtual public 
	\retval     void
	\remark    �����豸������ 
	*/
	virtual void save() = 0;

	/**
	\brief      restore
	\Access    virtual public 
	\retval     void
	\remark    �ָ��豸������ 
	*/
	virtual void restore() = 0;

	/**
	\brief      drawRect
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark    ���ƾ��νӿ� 
	*/
	virtual void drawRect(const WWorldRectF& rect) = 0;

	/**
	\brief      drawLine
	\Access    virtual public 
	\param  const WWorldLineF & line
	\retval     void
	\remark    ����ֱ�߽ӿ� 
	*/
	virtual void drawLine(const WWorldLineF& line) = 0;

	/**
	\brief      drawPolygon
	\Access    virtual public 
	\param  const WWorldPolygonF & polygon
	\retval     void
	\remark    ���ƶ���νӿڣ�!!!��ȷ����������ٰ��������㣬�����Ǳպϵģ�����������Ը��� 
	*/
	virtual void drawPolygon(const WWorldPolygonF& polygon) = 0;

	/**
	\brief      drawEllipse
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark    ������Բ�ӿ� 
	*/
	virtual void drawEllipse(const WWorldRectF& rect) = 0;

	/**
	\brief      drawEllipse
	\Access    virtual public 
	\param  const WWorldPoint & center��Բ���ĵ�
	\param  double rx ��Բ���뾶
	\param  double ry ��Բ�̰뾶
	\retval     void
	\remark    ������Բ�ӿ� 
	*/
	virtual void drawEllipse(const WWorldPoint& center, double rx, double ry) = 0;

	/**
	\brief      drawArc
	\Access    virtual public 
	\param  const WWorldRectF & rectȷ����Բ�ľ���
	\param  double startAngle��Բ����ʼ�Ƕȣ�startAngle / 16Ϊ��ʵ�Ƕȣ�ʵ����1�ȱ��ֳ���16�ݣ�
	\param  double spanAngle��Բ���յ�Ƕȣ�endAngle / 16Ϊ��ʵ�Ƕȣ�ͬ�ϣ�
	\retval     void
    \remark    ���ƻ��ߵĽӿ� 
	*/
	virtual void drawArc(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawChord
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\param  double startAngle
	\param  double spanAngle
	\retval     void
	\remark    ���ƹ��νӿڣ���������ͬ��drawArc�� 
	*/
	virtual void drawChord(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawPie
	\Access    virtual public 
	\param  const WWorldRectF & rect
	\param  double startAngle
	\param  double spanAngle
	\retval     void
	\remark    ���Ʊ�״�ӿڣ���������ͬ��drawArc�� 
	*/
	virtual void drawPie(const WWorldRectF& rect, double startAngle, double spanAngle) = 0;

	/**
	\brief      drawPolyline
	\Access    virtual public 
	\param  const WWorldPolylineF & polyline
	\retval     void
	\remark    �������߽ӿ� 
	*/
	virtual void drawPolyline(const WWorldPolylineF& polyline) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldPointF & pos �����ı�����ʼλ��
	\param  const std::string & text �ı�
	\retval     void
	\remark    �����ı��ӿ� 
	*/
	virtual void drawText(const WWorldPointF& pos, const std::string& text) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldPointF & pos �����ı�����ʼλ��
	\param  const std::wstring & text ���ı�
	\retval     void
	\remark    �����ı��ӿ� 
	*/
	virtual void drawText(const WWorldPointF& pos, const std::wstring& text) = 0;

	/**
	\brief      drawText
	\Access    virtual public 
	\param  const WWorldRectF & r�ı��ı߽��������
	\param  int flags �����ı���ѡ���μ�Ws::AlignmentFlag��Ws::TextFlag
						flags��������������ö�����͵���������
	\param  const std::string & text �ı�
	\param[OUT]  WWorldRectF * boundingRect �����ı���ʵ�ʱ߽���Σ�Ĭ��Ϊ0
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
	\remark    ����������������ȫ��ͬ��ֻ����������ı�Ϊ���ı� 
	*/
	virtual void drawText(const WWorldRectF& r, int flags, const std::wstring& text, WWorldRectF* boundingRect = 0) = 0;

	/**
	\brief      drawStaticText
	\Access    virtual public 
	\param  const WWorldPointF & pos
	\param  const std::string & text
	\retval     void
	\remark    ��Ҫ���ڻ��Ƹ��ı� 
	*/
	virtual void drawStaticText(const WWorldPointF& pos, const std::string& text) = 0;

	/**
	\brief      drawPixmap
	\Access    virtual public 
	\param  const WWorldPointF & p
	\param  const WPixmap & pixmap
	\retval     void
	\remark    �ڸ��������ͼƬ�ӿ� 
	*/
	virtual void drawPixmap(const WWorldPointF& p, const WPixmap& pixmap) = 0;

	/**
	\brief      drawPixmap
	\Access    virtual public 
	\param  const WWorldRectF & r
	\param  const WPixmap & pixmap
	\retval     void
	\remark    �ڸ����������ڻ���ͼƬ�ӿ� 
	*/
	virtual void drawPixmap(const WWorldRectF& r, const WPixmap& pixmap) = 0;

	/**
	\brief      deviceSize
	\Access    virtual public 
	\retval     WWorldSizeF
	\remark    ��ȡ�豸�Ķ�Ӧ��ͼ��С 
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