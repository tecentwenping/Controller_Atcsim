#ifndef __W_Graphics_Layer_Filter_H__
#define __W_Graphics_Layer_Filter_H__

#include "../wdllimport.h"
#include "wworldrect.h"
#include "wgraphicslayer.h"
#include "wpainter.h"
#include "wgraphicsview.h"
/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicslayerfilter.h
  ����  �ߡ�: @zcw
  ����  ����:1.0
  ��������ڡ�:2013/09/14
  ����  ����:  
    

  ����  ����:   
******************************************************************************/
class WGraphicsLayer;
class WPainter;
class WGraphicsView;


class MAPAPI WGraphicsLayerFilter
{
public:
	bool operator()(WGraphicsLayer* layer, WPainter* painter, const WWorldRectF& rect, WGraphicsView* view);
};

bool WGraphicsLayerFilter::operator ()(WGraphicsLayer* layer, WPainter* painter, const WWorldRectF& rect, WGraphicsView* view)
{
	// �����л���
	return true;
}

#endif // __W_Graphics_Layer_Filter_H__