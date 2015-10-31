/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: witemshareprivate.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ�����˼���ȫ�ֺ�������Щ������Ҫ�����Ǹ���ͼԪ�����Ӧ�Ĺ���
  ����  ����:   
******************************************************************************/
#ifndef _WITEM_SHARE_PRIVATE_H_
#define _WITEM_SHARE_PRIVATE_H_

#include "../wdllimport.h"
#include "wworldline.h"
#include "wworldrect.h"

typedef const WWorldPointF& WPF;

/**
\brief      attachLine
\Access    public 
\param  const WWorldLineF & line
\param  double attachDistance
\param  const WWorldPointF & pos
\param  WWorldPointF * attachedPos
\retval     bool MAPAPI
\remark     �ж�һ����(pos)�Ƿ��ܹ�����һ��ֱ��(line)
				�ж��Ƿ������ı�׼�ǵ�(pos)��ֱ��(line)�ľ����Ƿ�С��һ����������ֵ(attachDistance)��
				����������ģ���������true�����ɺ�������attachedPos����ֱ���ϵ�������
*/
bool MAPAPI attachLine(const WWorldLineF& line, double attachDistance, const WWorldPointF& pos, WWorldPointF* attachedPos);

//���¼������صĺ������ڻ�ȡn(2, 3, 4, 5, 6)�����γɵ����ߵı߽��������
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5);
WWorldRectF MAPAPI boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5, WPF p6);

#endif