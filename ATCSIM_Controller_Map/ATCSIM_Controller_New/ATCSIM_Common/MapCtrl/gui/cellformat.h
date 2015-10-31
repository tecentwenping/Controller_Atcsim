/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: cellformat.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  !!!!!!!!!!! 此文件中的函数已经废弃，请勿保用
  【其  它】:   
******************************************************************************/
#ifndef _CELL_FORMAT_H_
#define _CELL_FORMAT_H_

#include "../core/wworldpoint.h"

class QString;
class WGraphicsItem;
class WGraphicsArcItem;
class WGraphicsLineItem;
class WGraphicsTextItem;
class WGraphicsRectItem;
class WGraphicsPointItem;
class WGraphicsEllipseItem;
class WGraphicsPolylineItem;
class WGraphicsPolygonItem;
class WGraphicsRichTextItem;

QString cell_format(const WWorldPointF& point);
QString cell_format(const WGraphicsItem& item);
QString cell_format(const WGraphicsArcItem& item);
QString cell_format(const WGraphicsLineItem& item);
QString cell_format(const WGraphicsTextItem& item);
QString cell_format(const WGraphicsRectItem& item);
QString cell_format(const WGraphicsPointItem& item);
QString cell_format(const WGraphicsEllipseItem& item);
QString cell_format(const WGraphicsPolylineItem& item);
QString cell_format(const WGraphicsPolygonItem& item);
QString cell_format(const WGraphicsRichTextItem& item);

#endif