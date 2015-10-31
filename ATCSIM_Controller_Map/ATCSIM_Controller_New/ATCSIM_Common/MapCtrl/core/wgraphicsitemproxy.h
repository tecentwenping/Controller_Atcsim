/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsitemproxy.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsItemProxy��
  ����  ����:   
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
 \brief                 ������Ҫ����֧��ͬһͼԪ�ڲ�ͬ��ͼ���Բ�ͬ�ķ�ʽ��ʾ�Ĺ���
\details   �����ͨ������ͼԪ��paint������ʵ�֣����ƺ���ͼ�ڻ��ƴ�ͼԪ�ͻ�ʹ�ô˶��Ƶĺ���
 \author    ����
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