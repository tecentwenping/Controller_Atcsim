/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsitemproxy.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsItemProxy类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_ITEM_PROXY_H_
#define _WGRAPHICS_ITEM_PROXY_H_

#include "../wdllimport.h"
#include "wworldrect.h"
#include <boost/function.hpp>
class WPainter;
class WGraphicsItem;
class WGraphicsView;

/** 
 \brief                 此类主要用来支持同一图元在不同视图中以不同的方式显示的功能
\details   你可以通过定制图元的paint函数来实现，定制后视图在绘制此图元就会使用此定制的函数
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsItemProxy
{
public:
	
	typedef boost::function<bool (WGraphicsItem*, WPainter*, const WWorldRectF&, WGraphicsView*)> ItemProxyObj;


	WGraphicsItemProxy();
	WGraphicsItemProxy(const ItemProxyObj& obj);

	bool proxy(WGraphicsItem* item, WPainter* painter, const WWorldRectF& rct, WGraphicsView* view);

private:

	ItemProxyObj m_proxyObj;
};



#endif