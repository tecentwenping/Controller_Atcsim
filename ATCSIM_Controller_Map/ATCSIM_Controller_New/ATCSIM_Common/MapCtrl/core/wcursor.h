/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wcursor.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ��WCursor
  ����  ����:   
******************************************************************************/
#ifndef _WCURSOR_H_
#define _WCURSOR_H_

#include "../wdllimport.h"
#include "wenums.h"

/** 
 \brief                 ������Ҫʵ��GDI�еĹ��
\details  Ŀǰֻ֧��ֻ֧��������Ĺ�꣬��֧���Զ���ͼƬ�Ĺ�� 
 \author    ����
\date      2013/05/23
*/
class MAPAPI WCursor
{
public:
	explicit WCursor(Ws::CursorShape shape = Ws::ArrowCursor);

	Ws::CursorShape shape() const;
	void setShape(Ws::CursorShape shape);

private:
	Ws::CursorShape _shape;
};

#endif