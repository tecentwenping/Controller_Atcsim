/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicslayerproxy.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsLayerProxy��
  ����  ����:   
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
 \brief                 ������Ҫ����֧���ڲ�ͬ����ͼ��ͼ���Բ�ͬ��ʽ��ʾ������
\details   ����Զ���ͼ�����ɫ����render������֮����ͼ�������ַ�ʽ����ͼ��
 \author    ����
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