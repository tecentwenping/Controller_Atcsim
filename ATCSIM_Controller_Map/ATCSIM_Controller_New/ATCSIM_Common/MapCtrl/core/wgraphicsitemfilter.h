#ifndef _WGRAPHICS_ITEM_FILTER_H_
#define _WGRAPHICS_ITEM_FILTER_H_

#include "../wdllimport.h"
#include "wgraphicsitem.h"
#include "wpainter.h"
#include "wgraphicsview.h"
/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsitemfilter.h
  ����  �ߡ�: @zcw
  ����  ����:1.0
  ��������ڡ�:2013/05/20
  ����  ����:  ͼԪ������  
    

  ����  ����: 
******************************************************************************/
class WGraphicsItem;
class WPainter;
class WGraphicsView;

/** 
 \brief	��view�����WGraphicsItemFilter, ���view������ʾ��Item	
 \details   
 \author    @zcw
 \date      2013/05/20
*/

class MAPAPI WGraphicsItemFilter
{
public:
	bool operator()(WGraphicsItem* item, WPainter* painter, const WWorldRectF& rct, WGraphicsView* view)
	{
		// �����и�ͼԪ����
		return true;
	}
};

#endif // _WGRAPHICS_ITEM_FILTER_H_