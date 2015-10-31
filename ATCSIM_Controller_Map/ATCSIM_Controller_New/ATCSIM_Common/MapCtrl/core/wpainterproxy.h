/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wpainterproxy.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WPainterProxy��
  ����  ����:   
******************************************************************************/
#ifndef _WPAINTER_PROXY_H_
#define _WPAINTER_PROXY_H_

#include "../wdllimport.h"

class WPainter;

//WPainterProxy is a helper class,
//it helps WPainter users to automatically save and restore paint objects
//it saves paint objects in ctor and restore them is detor
//the following example demonstrates basic usage of WPainterProxy
/*
void paintEvent(WPainter* painter)
{
	WPainterProxy proxy(painter); //WPainterProxy ctor, save paint objects in ctor
	painter->setPen(...); //pen has changed
	{
		WPainterProxy proxy_inner(painter); //save paint objects in ctor
		painter.setWorldTransform(...); //world transform has changed
	} //WPainterProxy detor, restore paint objects, that is, world transform has restored, now only pen has changed
	painter->setBrush(...); //brush has changed
} //WPainterProxy detor, restore paint objects, that is, nothing has changed
*/

/** 
 \brief                 ������ҪΪWPainter�Ĳ����ṩ����
\details   ������ڹ����ʱ���Զ�����WPainter��״̬��Ȼ����������ʱ���Զ��ָ�WPainter��״̬��
			WPainterʹ����һ�㶼��Ҫ��ʹ��֮ǰ����WPainter��״̬����WPainterʹ�����֮��ָ�WPainter��
			״̬������������ʱ����鷳�����״��󣬱����ڿ�ʼ��ʱ�򱣴�WPainter��״̬��Ȼ���WPainter����
			һϵ�еĲ�����ʹ����WPainter֮�������˻ָ�WPainter��ԭ����״̬������֮�������Ķ���ʹ��ͬһ��
			WPainter����ʱ����ֳ���ʾ�������������������WPainter���о���任û�м�ʱ�ָ�����Ϊ������
			Ϊ�˽��������ױ����������⣬��ʹ��WPainter֮ǰ����һ��WPainterProxy���󼴿ɡ�

 \author    ����
\date      2013/05/22
*/
class MAPAPI WPainterProxy
{
public:
	/**
	\brief      WPainterProxy
	\Access    public 
	\param  WPainter * painter
	\retval     
	\remark    ����WPainter��״̬ 
	*/
	explicit WPainterProxy(WPainter* painter);

	/**
	\brief      ~WPainterProxy
	\Access    public 
	\retval     
	\remark    �ָ�WPainter��״̬ 
	*/
	~WPainterProxy();

	/**
	\brief      painter
	\Access    public 
	\retval     WPainter*
	\remark    ��ȡWPainter���� 
	*/
	WPainter* painter() const;

private:
	WPainter* _painter;
};

#endif