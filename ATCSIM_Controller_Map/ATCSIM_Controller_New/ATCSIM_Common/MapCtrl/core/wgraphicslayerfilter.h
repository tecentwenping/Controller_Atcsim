#ifndef __W_Graphics_Layer_Filter_H__
#define __W_Graphics_Layer_Filter_H__

#include "../wdllimport.h"
#include "wworldrect.h"
#include "wgraphicslayer.h"
#include "wpainter.h"
#include "wgraphicsview.h"
/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicslayerfilter.h
  【作  者】: @zcw
  【版  本】:1.0
  【完成日期】:2013/09/14
  【描  述】:  
    

  【其  它】:   
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
	// 不进行绘制
	return true;
}

#endif // __W_Graphics_Layer_Filter_H__