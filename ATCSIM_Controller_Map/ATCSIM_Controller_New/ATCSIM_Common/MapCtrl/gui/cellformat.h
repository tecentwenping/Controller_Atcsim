/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: cellformat.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  !!!!!!!!!!! ���ļ��еĺ����Ѿ�������������
  ����  ����:   
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