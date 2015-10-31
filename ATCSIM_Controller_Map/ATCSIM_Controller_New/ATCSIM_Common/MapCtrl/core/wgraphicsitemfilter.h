#ifndef _WGRAPHICS_ITEM_FILTER_H_
#define _WGRAPHICS_ITEM_FILTER_H_

#include "../wdllimport.h"
#include "wgraphicsitem.h"
#include "wpainter.h"
#include "wgraphicsview.h"
/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsitemfilter.h
  【作  者】: @zcw
  【版  本】:1.0
  【完成日期】:2013/05/20
  【描  述】:  图元过滤器  
    

  【其  它】: 
******************************************************************************/
class WGraphicsItem;
class WPainter;
class WGraphicsView;

/** 
 \brief	对view添加了WGraphicsItemFilter, 则该view将不显示该Item	
 \details   
 \author    @zcw
 \date      2013/05/20
*/

class MAPAPI WGraphicsItemFilter
{
public:
	bool operator()(WGraphicsItem* item, WPainter* painter, const WWorldRectF& rct, WGraphicsView* view)
	{
		// 不进行该图元绘制
		return true;
	}
};

#endif // _WGRAPHICS_ITEM_FILTER_H_