/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wuncopyable.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WUncopyable��
  ����  ����:   
******************************************************************************/
#ifndef _WUNCOPYABLE_H_
#define _WUNCOPYABLE_H_

#include "../wdllimport.h"

/** 
 \brief          ����Ҫ��������Ĳ����Կ��������⣬������һ�����࣬
					���в�֧�ֶ��󿽱�����������̳м���
\details   
 \author    ����
\date      2013/05/22
*/
class MAPAPI WUncopable
{
public:
	WUncopable() {}

private:
	/**
	\brief      WUncopable
	\Access    private 
	\param  const WUncopable &
	\retval     
	\remark    ��ֹ�������� 
	*/
	WUncopable(const WUncopable&);

	/**
	\brief      operator=
	\Access    private 
	\param  const WUncopable &
	\retval     WUncopable&
	\remark    ��ֹ��ֵ���� 
	*/
	WUncopable& operator=(const WUncopable&);
};

#endif