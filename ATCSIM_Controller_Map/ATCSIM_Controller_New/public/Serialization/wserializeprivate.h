/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wserializeprivate.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件是序列化内部实现文件，
					除了扩展外一般不会用到此文件，
					wserialize.h文件中提供了更加简便的接口
  【其  它】:   
******************************************************************************/
#ifndef _WSERIALIZE_PRIVATE_H_
#define _WSERIALIZE_PRIVATE_H_

#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/range/as_array.hpp>
#include "wserializetag.h"

 //declarations : user interface
/**
\brief      serialize
\Access    public 
\param  char * buf 序列化缓冲区指针位置
\param  const T & t 进行序列化操作的对象
\retval     char* 返回序列化后缓冲区新的位置
				= 输入buf指针位置 + 对象序列化所需空间大小，
				返回此值有利于序列化操作的连续性
\remark     这是serialize系列函数的总接口，
				这个总接口根据类型绑定的标签，再将实际的任务分发给具体的实现者
*/
template<class T> inline char* serialize(char* buf, const T& t);

/**
\brief      unserialize
\Access    public 
\param  const char * buf
\param  T & t
\retval     const char*
\remark    反序列化操作，参数含义和上面的函数类似，只不过是从缓冲区中读取数据 
*/
template<class T> inline const char* unserialize(const char* buf, T& t);

/**
\brief      serialize_size
\Access    public 
\param  const T & t
\retval     size_t
\remark    计算某个对象序列化所占用的缓冲区大小 
*/
template<class T> inline size_t serialize_size(const T& t);

//declarations : internal implements
/** 
 \brief                 以下根据实际的类型（概念）实现实际的序列化操作
\details   
 \author    陈龙
\date      2013/05/23
*/
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_pod>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_has_inner_impl>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_has_outer_impl>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_seq_container>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_string>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_array>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_set>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_map>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_pair>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_dereferencable>);
template<class T> inline char* serialize(char* buf, const T& t, serialize_tag<tag_smart_pointer>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_pod>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_inner_impl>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_outer_impl>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_seq_container>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_string>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_array>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_set>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_map>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_pair>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_dereferencable>);
template<class T> inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_smart_pointer>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_pod>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_has_inner_impl>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_has_outer_impl>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_seq_container>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_string>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_array>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_set>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_map>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_pair>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_dereferencable>);
template<class T> inline size_t serialize_size(const T& t, serialize_tag<tag_smart_pointer>);

template<class T>
inline char* serialize(char* buf, const T& t)
{
	return serialize(buf, t, serialize_tag<tag_trait<T>::tag>());
}

template<class T> 
inline const char* unserialize(const char* buf, T& t)
{
	return unserialize(buf, t, serialize_tag<tag_trait<T>::tag>());
}

template<class T>
inline size_t serialize_size(const T& t)
{
	return serialize_size(t, serialize_tag<tag_trait<T>::tag>());
}

template<class T>
inline char* serialize(char* buf, const T& t, serialize_tag<tag_pod>)
{
	*reinterpret_cast<T*>(buf) = t;
	return buf + sizeof(T);
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_pod>)
{
	t = *reinterpret_cast<const T*>(buf);
	//memcpy(&t, buf, sizeof(T));
	return buf + sizeof(T);
}

template<class T> 
inline size_t serialize_size(const T&, serialize_tag<tag_pod>)
{
	return sizeof(T);
}

template<class T>
inline char* serialize(char* buf, const T& t, serialize_tag<tag_has_inner_impl>)
{
	return const_cast<T&>(t).serialize(WSerializer(buf), 0).value();
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_inner_impl>)
{
	return t.serialize(WUnserializer(buf), 0).value();
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_has_inner_impl>)
{
	return const_cast<T&>(t).serialize(WSizeHelper(), 0).value();
}

template<class T>
inline char* serialize(char* buf, const T& t, serialize_tag<tag_has_outer_impl>)
{
	return serialize(WSerializer(buf), const_cast<T&>(t), 0).value();
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_outer_impl>)
{
	return serialize(WUnserializer(buf), t, 0).value();
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_has_outer_impl>)
{
	return serialize(WSizeHelper(), const_cast<T&>(t), 0).value();
}

template<class T>
char* serialize(char* buf, const T& t, serialize_tag<tag_seq_container>)
{
	typedef T::value_type value_type;

	buf = serialize(buf, t.size());
	BOOST_FOREACH(const value_type& v, t)
	{
		buf = serialize(buf, v);
	}
	return buf;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_seq_container>)
{
	typedef T::size_type size_type;
	typedef T::value_type value_type;

	size_type size = 0;
	buf = unserialize(buf, size);
	t.resize(size);
	BOOST_FOREACH(value_type& v, t)
	{
		buf = unserialize(buf, v);
	}
	return buf;
}

template<class T> 
size_t serialize_size(const T& t, serialize_tag<tag_seq_container>)
{
	typedef T::size_type size_type;
	typedef T::value_type value_type;

	size_t size = sizeof(size_type);
	BOOST_FOREACH(const value_type& v, t)
	{
		size += serialize_size(v);
	}
	return size;
}

template<class T>
char* serialize(char* buf, const T& t, serialize_tag<tag_string>)
{
	buf = serialize(buf, t.size());
	size_t string_bytes = t.size() * sizeof(T::value_type);
	memcpy(buf, t.c_str(), string_bytes);
	return buf + string_bytes;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_string>)
{
	T::size_type size = 0;
	buf = unserialize(buf, size);
	t.assign(reinterpret_cast<const T::value_type*>(buf), size);
	return buf + size * sizeof(T::value_type);
}

template<class T> 
size_t serialize_size(const T& t, serialize_tag<tag_string>)
{
	return sizeof(T::size_type) + t.size() * sizeof(T::value_type);
}

template<class T>
char* serialize(char* buf, const T& t, serialize_tag<tag_array>)
{
	typedef BOOST_TYPEOF(t[0]) element_type;

	BOOST_FOREACH(const element_type& v, boost::as_array(t))
	{
		buf = serialize(buf, v);
	}
	return buf;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_array>)
{
	typedef BOOST_TYPEOF(t[0]) element_type;

	BOOST_FOREACH(element_type& v, boost::as_array(t))
	{
		buf = unserialize(buf, v);
	}
	return buf;
}

template<class T> 
size_t serialize_size(const T& t, serialize_tag<tag_array>)
{
	typedef BOOST_TYPEOF(t[0]) element_type;

	size_t size = 0;
	BOOST_FOREACH(const element_type& v, boost::as_array(t))
	{
		size += serialize_size(v);
	}
	return size;
}

template<class T>
char* serialize(char* buf, const T& t, serialize_tag<tag_set>)
{
	typedef T::key_type key_type;

	buf = serialize(buf, t.size());
	BOOST_FOREACH(const key_type& v, t)
	{
		buf = serialize(buf, v);
	}
	return buf;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_set>)
{
	typedef T::size_type size_type;
	typedef T::key_type key_type;

	size_type size = 0;
	buf = unserialize(buf, size);

	t.clear();
	for (size_type i = 0; i < size; ++i)
	{
		key_type key;
		buf = unserialize(buf, key);
		t.insert(key);
	}
	return buf;
}

template<class T> 
size_t serialize_size(const T& t, serialize_tag<tag_set>)
{
	typedef T::key_type key_type;

	size_t size = serialize_size(t.size());
	BOOST_FOREACH(const key_type& v, t)
	{
		size += serialize_size(v);
	}
	return size;
}

template<class T>
char* serialize(char* buf, const T& t, serialize_tag<tag_map>)
{
	typedef T::value_type value_type;
	
	buf = serialize(buf, t.size());
	BOOST_FOREACH(const value_type& v, t)
	{
		buf = serialize(buf, v);
	}
	return buf;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_map>)
{
	typedef T::size_type size_type;
	typedef T::key_type key_type;
	typedef T::mapped_type mapped_type;

	size_type size = 0;
	buf = unserialize(buf, size);

	t.clear();
	for (size_type i = 0; i < size; ++i)
	{
		std::pair<key_type, mapped_type> v;
		buf = unserialize(buf, v);
		t.insert(v);
	}
	return buf;
}

template<class T> 
size_t serialize_size(const T& t, serialize_tag<tag_map>)
{
	typedef T::value_type value_type;

	size_t size = serialize_size(t.size());
	BOOST_FOREACH(const value_type& v, t)
	{
		size += serialize_size(v);
	}
	return size;
}

template<class T>
inline char* serialize(char* buf, const T& t, serialize_tag<tag_pair>)
{
	buf = serialize(buf, t.first);
	buf = serialize(buf, t.second);
	return buf;
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_pair>)
{
	buf = unserialize(buf, t.first);
	buf = unserialize(buf, t.second);
	return buf;
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_pair>)
{
	return serialize_size(t.first) + serialize_size(t.second);
}

template<class T> 
inline char* serialize(char* buf, const T& t, serialize_tag<tag_dereferencable>)
{
	return serialize(buf, *t);
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_dereferencable>)
{
	return unserialize(buf, *t);
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_dereferencable>)
{
	return serialize_size(*t);
}

template<class T> 
inline char* serialize(char* buf, const T& t, serialize_tag<tag_smart_pointer>)
{
	return serialize(buf, *t);
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_smart_pointer>)
{
	t.~T();
	new (&t) T(new typename T::element_type);
	return unserialize(buf, *t);
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_smart_pointer>)
{
	return serialize_size(*t);
}

#endif