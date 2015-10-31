/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wserializetag.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现每种类型的标签绑定的功能，
					也就是每一种类型对应一个标签，
					一个标签可以对应多种类型
  【其  它】:   
******************************************************************************/
#ifndef _WSERIALIZE_TAG_H_
#define _WSERIALIZE_TAG_H_

#include <set>
#include <list>
#include <map>
#include <vector>
#include <deque>
#include <xstring>
#include <memory>
#include <boost/type_traits.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

/** 
 \brief                 此宏主要实现为序列容器绑定一个标签tag_seq_container
\details   
 \author    陈龙
\date      2013/05/23
*/
#define TAG_TRAIT_SEQ_CONTAINER(typ)\
template<class _Ty, class _Ax>\
struct tag_trait<typ<_Ty, _Ax> >\
{\
static const size_t tag = tag_seq_container;\
};\

#define STATIC_CONSTANT(typ, value) static const typ value;

/** 
 \brief                 此宏主要实现判断某一个类中是否有某一个特定的成员函数
\details  此宏在序列化一个自定义的类型时会用到，如果一个类有serialize成员函数，此系统就
			会调用其成员函数，如果此类没有serialize成员函数，而有全局的serialize相关函数，
			系统就会自动的调用此全局函数，所以只要定义其中一个系统就能很好的识别			
 \author    陈龙
\date      2013/05/23
*/
#define DEFINE_HAS_MEMBER_CALLED(member_name)\
template<typename T, bool=boost::is_class<T>::value>\
struct has_member_called_##member_name\
{\
	STATIC_CONSTANT(bool, value=false);\
};\
\
template<typename T>\
struct has_member_called_##member_name<T,true>\
{\
	typedef char true_type;\
struct false_type { true_type dummy[2]; };\
	\
struct fallback { int member_name; };\
struct derived : T, fallback { derived(); };\
	\
	template<int fallback::*> struct tester;\
	\
	template<typename U>\
	static false_type has_member(tester<&U::member_name>*);\
	template<typename U>\
	static true_type has_member(...);\
	\
	STATIC_CONSTANT(bool, value=sizeof(has_member<derived>(0))==sizeof(true_type));\
};\

/** 
 \brief                 定义某个类型是否有serialize成员函数
\details   has_member_called_serialize<T>::value代表T类型是否有serialize成员函数
 \author    陈龙
\date      2013/05/23
*/
DEFINE_HAS_MEMBER_CALLED(serialize)

/** 
 \brief                 类型未知，编译错误
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_none = 0x0;

/** 
 \brief                 POD类型标签
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_pod = 0x1;

/** 
\brief                 自定义类型，并且有类有成员函数serialize的类型标签
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_has_inner_impl = 0x2;

/** 
 \brief        所有满足序列容器操作的容器        
 \details   比如std::vector，std::deque，std::list
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_seq_container = 0x4;

/** 
 \brief                 字符串类型标签
 \details	包括所有类型的字符串std::basic_string<_Elem, _Traits, _Ax>，
				比如最基本的std::string, std::wstring等，
				其实string在概念上可以和序列容器tag_seq_container是一类，
				单独抽取出来完全是出于运行效率增考虑
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_string = 0x5;

/** 
 \brief                 数组类型标签
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_array = 0x6;

/** 
 \brief                 所有满足set概念和操作的类型类型标签，比如std::set，QSet
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_set = 0x7;

/** 
 \brief                 所有满足map概念和操作的标签，比如std::map, QMap
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_map = 0x8;

/** 
 \brief                 std::pair类型接口
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_pair = 0x9;

/** 
 \brief                 自定义类型，并且有外部相关serialize全局函数的标签
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_has_outer_impl = 0xa;

/** 
 \brief                 可解引用类型标签
\details   比如指针，迭代器
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_dereferencable = 0xb;

/** 
 \brief                 智能指针类型标签
\details   
 \author    陈龙
\date      2013/05/23
*/
static const size_t tag_smart_pointer = 0xc;

/** 
 \brief                 以下将标签映射成相对应的类型
\details  主要通过模板特化和偏特化实现 
 \author    陈龙
\date      2013/05/23
*/
template<size_t N> struct serialize_tag {};

template<class T, bool is_pod, bool is_array, bool is_class>
struct tag_trait_helper
{
	static const size_t tag = tag_none;
};

template<class T, bool is_pod, bool is_class>
struct tag_trait_helper<T, is_pod, true, is_class>
{
	static const size_t tag = tag_array;
};

template<class T>
struct tag_trait_helper<T, true, false, false>
{
	static const size_t tag = tag_pod;
};

template<class T, bool is_pod>
struct tag_trait_helper<T, is_pod, false, true>
{
	static const size_t tag = (has_member_called_serialize<T>::value ? tag_has_inner_impl : tag_has_outer_impl);
};



//对于基本类型可能不会调用自定义的串行化方法，改为以自定义串行化方法优先
template<class T> 
struct tag_trait
{
	static const size_t tag = tag_trait_helper<T,
		boost::is_pod<T>::value, 
		boost::is_array<T>::value,
		boost::is_class<T>::value
	>::tag;
};


TAG_TRAIT_SEQ_CONTAINER(std::vector)
TAG_TRAIT_SEQ_CONTAINER(std::list)
TAG_TRAIT_SEQ_CONTAINER(std::deque)

template<class _Elem, class _Traits, class _Ax>
struct tag_trait<std::basic_string<_Elem, _Traits, _Ax> >
{
	static const size_t tag = tag_string;
};

template<class _Kty, class _Pr, class _Alloc>
struct tag_trait<std::set<_Kty, _Pr, _Alloc> >
{
	static const size_t tag = tag_set;
};

template<class _Kty, class _Pr, class _Alloc>
struct tag_trait<std::multiset<_Kty, _Pr, _Alloc> >
{
	static const size_t tag = tag_set;
};

template<class _Kty, class _Ty, class _Pr, class _Alloc>
struct tag_trait<std::map<_Kty, _Ty, _Pr, _Alloc> >
{
	static const size_t tag = tag_map;
};

template<class _Kty, class _Ty, class _Pr, class _Alloc>
struct tag_trait<std::multimap<_Kty, _Ty, _Pr, _Alloc> >
{
	static const size_t tag = tag_map;
};

template<class _Ty1, class _Ty2>
struct tag_trait<std::pair<_Ty1, _Ty2> >
{
	static const size_t tag = tag_pair;
};

template<class T>
struct tag_trait<std::auto_ptr<T> >
{
	static const size_t tag = tag_smart_pointer;
};

template<class T>
struct tag_trait<boost::shared_ptr<T> >
{
	static const size_t tag = tag_smart_pointer;
};

template<class T>
struct tag_trait<boost::scoped_ptr<T> >
{
	static const size_t tag = tag_smart_pointer;
};

template<class T>
struct tag_trait<T*>
{
	static const size_t tag = tag_dereferencable;
};

template<class T>
struct tag_trait<const T*>
{
	static const size_t tag = tag_dereferencable;
};

#endif