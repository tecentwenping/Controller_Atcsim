/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wrttimacro.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ������WItemInfo WItemRegHelper�ṹ����ȫ�ֺ��������м�����
					���ļ���Ҫ���ͼԪ�Ķ�̬ʶ�𣬶�̬�����ȹ���
  ����  ����:   
******************************************************************************/
#ifndef _WRTTI_MACRO_H_
#define _WRTTI_MACRO_H_

#include <boost/type_traits.hpp>
#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief                 ͼԪ��̬���������е�һ�����
\details   
 \author    ����
\date      2013/05/29
*/
struct MAPAPI WItemInfo
{
	const char* name; //ͼԪ����
	WGraphicsItem* (*create)(); //������ͼԪ�ĺ���ָ��
	const WItemInfo* next; //�˽�����һ�����
	static const WItemInfo* begin; //��̬��Ա��������ָ�������ͷ���
};

/** 
 \brief                 �����ǰ����࣬�����õ���Ҫ���乹�캯�������ڽ�һ�������ӵ�ͼԪ����������
\details   
 \author    ����
\date      2013/05/29
*/
struct MAPAPI WItemRegHelper
{
	explicit WItemRegHelper(WItemInfo* info);
};

template<class item_type, bool abstract_class>
struct WCreateHelper;

template<class item_type>
struct WCreateHelper<item_type, false>
{
	item_type* operator()()
	{
		return new item_type(new item_type::data_type);
	}
};

//����ǳ������򷵻�0
template<class item_type>
struct WCreateHelper<item_type, true>
{
	item_type* operator()()
	{
		return 0;
	}
};

/**
\brief      create_helper
\Access    public 
\retval     WGraphicsItem*
\remark     ����ͼԪ�ĺ���ָ��
*/
template<class item_type>
WGraphicsItem* create_helper()
{
	return WCreateHelper<item_type, boost::is_abstract<item_type>::value>()();
}

//�������ͼԪ֧�ֶ�̬�������ܣ��뽫�˺���ӵ������������壩��
#define RTTI_DECL(class_name)\
public:\
	static WItemInfo class##class_name;\
	virtual const WItemInfo* classinfo() const;\

//�������ͼԪ֧�ֶ�̬�������ܣ��뽫�˺���ӵ����ʵ���ļ���
#define RTTI_IMPL(class_name)\
	WItemInfo class_name::class##class_name = {#class_name, &create_helper<class_name>};\
	static WItemRegHelper _register_##class_name(&class_name::class##class_name);\
	const WItemInfo* class_name::classinfo() const { return &class_name::class##class_name; }\

#endif