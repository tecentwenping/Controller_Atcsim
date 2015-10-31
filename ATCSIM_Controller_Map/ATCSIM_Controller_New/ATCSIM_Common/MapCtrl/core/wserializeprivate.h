#ifndef _WSERIALIZE_PRIVATE_H_
#define _WSERIALIZE_PRIVATE_H_

#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include "wserializetag.h"
#include "wserializeimpl.h"

 //declarations : user interface
template<class T> char* serialize(char* buf, const T& t);
template<class T> const char* unserialize(const char* buf, T& t);
template<class T> size_t serialize_size(const T& t);

//declarations : internal implements
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_pod>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_has_impl>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_graphics_item>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_seq_container>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_string>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_array>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_set>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_map>);
template<class T> char* serialize(char* buf, const T& t, serialize_tag<tag_pair>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_pod>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_impl>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_graphics_item>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_seq_container>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_string>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_array>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_set>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_map>);
template<class T> const char* unserialize(const char* buf, T& t, serialize_tag<tag_pair>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_pod>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_has_impl>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_graphics_item>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_seq_container>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_string>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_array>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_set>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_map>);
template<class T> size_t serialize_size(const T& t, serialize_tag<tag_pair>);

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
	return buf + sizeof(T);
}

template<class T> 
inline size_t serialize_size(const T&, serialize_tag<tag_pod>)
{
	return sizeof(T);
}

template<class T>
inline char* serialize(char* buf, const T& t, serialize_tag<tag_has_impl>)
{
	return serialize_impl(buf, t);
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_has_impl>)
{
	return unserialize_impl(buf, t);
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_has_impl>)
{
	return serialize_size_impl(t);
}

template<class T> 
inline char* serialize(char* buf, const T& t, serialize_tag<tag_graphics_item>)
{
	return t.serialize(buf);
}

template<class T> 
inline const char* unserialize(const char* buf, T& t, serialize_tag<tag_graphics_item>)
{
	return t.unserialize(buf);
}

template<class T> 
inline size_t serialize_size(const T& t, serialize_tag<tag_graphics_item>)
{
	return t.serialize_size();
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
	t.resize(size);
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

	BOOST_FOREACH(const element_type& v, t)
	{
		buf = serialize(buf, v);
	}
	return buf;
}

template<class T> 
const char* unserialize(const char* buf, T& t, serialize_tag<tag_array>)
{
	typedef BOOST_TYPEOF(t[0]) element_type;

	BOOST_FOREACH(element_type& v, t)
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
	BOOST_FOREACH(const element_type& v, t)
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

#endif