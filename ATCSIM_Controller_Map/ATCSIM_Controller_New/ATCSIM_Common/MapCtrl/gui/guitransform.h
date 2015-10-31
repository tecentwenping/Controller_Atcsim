/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: guitransform.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件定义了一些全局函数实现Qt和此库中的GUI设备，资源等的转换
  【其  它】:   
******************************************************************************/
#ifndef _GUI_TRANSFORM_H_
#define _GUI_TRANSFORM_H_

#include <QPen>
#include <QFont>
#include <QColor>
#include <QLineF>
#include <QRectF>
#include <QBrush>
#include <QPointF>
#include <QCursor>
#include <QPixmap>
#include <QTransform>

#include "../wdllimport.h"
#include "../core/wpen.h"
#include "../core/wfont.h"
#include "../core/wbrush.h"
#include "../core/wcursor.h"
#include "../core/wmatrix.h"
#include "../core/wenums.h"
#include "../core/wpixmap.h"
#include "../core/wworldline.h"
#include "../core/wworldsize.h"
#include "../core/wworldrect.h"

//以下这些函数功能单一，参数和返回值明确，就免注释了
//只是矩形rect的转换函数涉及到坐标系转换的问题，请谨慎处理

QCursor MAPAPI transform(const WCursor& cursor);
QPen MAPAPI transform(const WPen& pen);
QBrush MAPAPI transform(const WBrush& brush);
QFont MAPAPI transform(const WFont& font);
QTransform MAPAPI transform(const WMatrix& matrix);
QPointF MAPAPI transform(const WWorldPointF& point);
QPoint MAPAPI transform(const WWorldPoint& point);
QRectF MAPAPI transform(const WWorldRectF& rect);
QLineF MAPAPI transform(const WWorldLineF& line);
QColor MAPAPI transform(const WColor& color);
QPixmap MAPAPI transform(const WPixmap& pixmap);
QSizeF MAPAPI transform(const WWorldSizeF& size);

WCursor MAPAPI transform(const QCursor& cursor);
WPen MAPAPI transform(const QPen& pen);
WBrush MAPAPI transform(const QBrush& brush);
WFont MAPAPI transform(const QFont& font);
WMatrix MAPAPI transform(const QTransform& matrix);
WWorldPointF MAPAPI transform(const QPointF& point);
WWorldPoint MAPAPI transform(const QPoint& point);
WWorldRectF MAPAPI transform(const QRectF& rect);
WWorldLineF MAPAPI transform(const QLineF& line);
WColor MAPAPI transform(const QColor& color);
WPixmap MAPAPI transform(const QPixmap& pixmap);
WWorldSizeF MAPAPI transform(const QSizeF& size);

#endif