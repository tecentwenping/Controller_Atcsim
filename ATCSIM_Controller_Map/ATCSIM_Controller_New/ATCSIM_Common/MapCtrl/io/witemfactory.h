/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: witemfactory.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ������WItemFactory��
  ����  ����:   
******************************************************************************/
#ifndef _WITEM_FACTORY_H_
#define _WITEM_FACTORY_H_

#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief       ������Ҫʵ���˽�ͼԪ���л������������У����ڶ��������ж�̬����ͼԪ����
\details   
 \author    ����
\date      2013/05/31
*/
class MAPAPI WItemFactory
{
public:
	/**
	\brief      serialize
	\Access    public static 
	\param  char * buf
	\param  const WGraphicsItem & item
	\retval     char*
	\remark     ��ͼԪ���л�������������
	*/
	static char* serialize(char* buf, const WGraphicsItem& item);
	
	/**
	\brief      serialize_size
	\Access    public static 
	\param  const WGraphicsItem & item
	\retval     size_t
	\remark     ����ͼԪ���л����������������軺������С
	*/
	static size_t serialize_size(const WGraphicsItem& item);

	/**
	\brief      create
	\Access    public static 
	\param  const char * buf
	\param  WGraphicsItem * * item
	\retval     const char* ͼԪ�����󻺳����ĵ�ǰָ��λ��
	\remark     �����뻺����buf�д���ͼԪ����*item���أ��������ʧ��item���䣩
	*/
	static const char* create(const char* buf, WGraphicsItem** item);
};

#endif