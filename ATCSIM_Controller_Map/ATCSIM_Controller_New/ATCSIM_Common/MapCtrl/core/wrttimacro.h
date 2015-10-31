/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wrttimacro.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含了WItemInfo WItemRegHelper结构，和全局函数，还有几个宏
					此文件主要完成图元的动态识别，动态创建等功能
  【其  它】:   
******************************************************************************/
#ifndef _WRTTI_MACRO_H_
#define _WRTTI_MACRO_H_

#include <boost/type_traits.hpp>
#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief                 图元动态创建链表中的一个结点
\details   
 \author    陈龙
\date      2013/05/29
*/
struct MAPAPI WItemInfo
{
	const char* name; //图元名称
	WGraphicsItem* (*create)(); //创建此图元的函数指针
	const WItemInfo* next; //此结点的下一个结点
	static const WItemInfo* begin; //静态成员，它总是指向链表的头结点
};

/** 
 \brief                 此类是帮助类，起作用的主要是其构造函数，用于将一个结点添加到图元创建链表中
\details   
 \author    陈龙
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

//如果是抽象类则返回0
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
\remark     创建图元的函数指针
*/
template<class item_type>
WGraphicsItem* create_helper()
{
	return WCreateHelper<item_type, boost::is_abstract<item_type>::value>()();
}

//如果想让图元支持动态创建功能，请将此宏添加到类声明（定义）中
#define RTTI_DECL(class_name)\
public:\
	static WItemInfo class##class_name;\
	virtual const WItemInfo* classinfo() const;\

//如果想让图元支持动态创建功能，请将此宏添加到类的实现文件中
#define RTTI_IMPL(class_name)\
	WItemInfo class_name::class##class_name = {#class_name, &create_helper<class_name>};\
	static WItemRegHelper _register_##class_name(&class_name::class##class_name);\
	const WItemInfo* class_name::classinfo() const { return &class_name::class##class_name; }\

#endif