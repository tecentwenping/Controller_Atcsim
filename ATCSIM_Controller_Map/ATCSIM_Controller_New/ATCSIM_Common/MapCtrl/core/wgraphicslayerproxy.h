/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicslayerproxy.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsLayerProxy类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_LAYER_PROXY_H_
#define _WGRAPHICS_LAYER_PROXY_H_

#include "../wdllimport.h"
#include "wworldrect.h"
#include <boost/function.hpp>

class WPainter;
class WGraphicsView;
class WGraphicsLayer;

/** 
 \brief                 此类主要用来支持在不同的视图中图层以不同方式显示的问题
\details   你可以定制图层的着色函数render，这样之后视图将以这种方式绘制图层
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsLayerProxy
{
public:
	typedef boost::function<bool (WGraphicsLayer*, WPainter*, const WWorldRectF&, WGraphicsView*)> LayerProxyObj;

	WGraphicsLayerProxy();
	WGraphicsLayerProxy(const LayerProxyObj& obj);
	
	bool proxy(WGraphicsLayer* layer, WPainter* painter, const WWorldRectF& rect, WGraphicsView* view);

private:
	LayerProxyObj m_proxyObj;
};


#endif