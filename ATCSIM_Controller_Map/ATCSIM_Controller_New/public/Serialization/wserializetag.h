/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wserializetag.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ��ÿ�����͵ı�ǩ�󶨵Ĺ��ܣ�
					Ҳ����ÿһ�����Ͷ�Ӧһ����ǩ��
					һ����ǩ���Զ�Ӧ��������
  ����  ����:   
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
 \brief                 �˺���Ҫʵ��Ϊ����������һ����ǩtag_seq_container
\details   
 \author    ����
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
 \brief                 �˺���Ҫʵ���ж�ĳһ�������Ƿ���ĳһ���ض��ĳ�Ա����
\details  �˺������л�һ���Զ��������ʱ���õ������һ������serialize��Ա��������ϵͳ��
			��������Ա�������������û��serialize��Ա����������ȫ�ֵ�serialize��غ�����
			ϵͳ�ͻ��Զ��ĵ��ô�ȫ�ֺ���������ֻҪ��������һ��ϵͳ���ܺܺõ�ʶ��			
 \author    ����
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
 \brief                 ����ĳ�������Ƿ���serialize��Ա����
\details   has_member_called_serialize<T>::value����T�����Ƿ���serialize��Ա����
 \author    ����
\date      2013/05/23
*/
DEFINE_HAS_MEMBER_CALLED(serialize)

/** 
 \brief                 ����δ֪���������
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_none = 0x0;

/** 
 \brief                 POD���ͱ�ǩ
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_pod = 0x1;

/** 
\brief                 �Զ������ͣ����������г�Ա����serialize�����ͱ�ǩ
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_has_inner_impl = 0x2;

/** 
 \brief        ��������������������������        
 \details   ����std::vector��std::deque��std::list
 \author    ����
\date      2013/05/23
*/
static const size_t tag_seq_container = 0x4;

/** 
 \brief                 �ַ������ͱ�ǩ
 \details	�����������͵��ַ���std::basic_string<_Elem, _Traits, _Ax>��
				�����������std::string, std::wstring�ȣ�
				��ʵstring�ڸ����Ͽ��Ժ���������tag_seq_container��һ�࣬
				������ȡ������ȫ�ǳ�������Ч��������
 \author    ����
\date      2013/05/23
*/
static const size_t tag_string = 0x5;

/** 
 \brief                 �������ͱ�ǩ
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_array = 0x6;

/** 
 \brief                 ��������set����Ͳ������������ͱ�ǩ������std::set��QSet
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_set = 0x7;

/** 
 \brief                 ��������map����Ͳ����ı�ǩ������std::map, QMap
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_map = 0x8;

/** 
 \brief                 std::pair���ͽӿ�
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_pair = 0x9;

/** 
 \brief                 �Զ������ͣ��������ⲿ���serializeȫ�ֺ����ı�ǩ
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_has_outer_impl = 0xa;

/** 
 \brief                 �ɽ��������ͱ�ǩ
\details   ����ָ�룬������
 \author    ����
\date      2013/05/23
*/
static const size_t tag_dereferencable = 0xb;

/** 
 \brief                 ����ָ�����ͱ�ǩ
\details   
 \author    ����
\date      2013/05/23
*/
static const size_t tag_smart_pointer = 0xc;

/** 
 \brief                 ���½���ǩӳ������Ӧ������
\details  ��Ҫͨ��ģ���ػ���ƫ�ػ�ʵ�� 
 \author    ����
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



//���ڻ������Ϳ��ܲ�������Զ���Ĵ��л���������Ϊ���Զ��崮�л���������
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