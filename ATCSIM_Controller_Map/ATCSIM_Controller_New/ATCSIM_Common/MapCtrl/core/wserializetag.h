#ifndef _WSERIALIZE_TAG_H_
#define _WSERIALIZE_TAG_H_

#include <set>
#include <list>
#include <map>
#include <vector>
#include <deque>
#include <xstring>
#include <boost/type_traits.hpp>

#include "wpen.h"
#include "wfont.h"
#include "wcolor.h"
#include "wbrush.h"
#include "wworldline.h"
#include "wworldsize.h"
#include "wworldrect.h"
#include "wworldpoint.h"
#include "wgraphicsitem.h"
#include "wworldpolyline.h"
#include "wworldpolygon.h"

#define TAG_TRAIT_SEQ_CONTAINER(typ)\
template<class _Ty, class _Ax>\
struct tag_trait<typ<_Ty, _Ax> >\
{\
static const size_t tag = tag_seq_container;\
};\

static const size_t tag_none = 0x0;
static const size_t tag_pod = 0x1;
static const size_t tag_has_impl = 0x2;
static const size_t tag_graphics_item = 0x3;
static const size_t tag_seq_container = 0x4;
static const size_t tag_string = 0x5;
static const size_t tag_array = 0x6;
static const size_t tag_set = 0x7;
static const size_t tag_map = 0x8;
static const size_t tag_pair = 0x9;

template<size_t N> struct serialize_tag {};

template<bool is_pod, bool is_array, bool is_graphics_item>
struct tag_trait_helper
{
	static const size_t tag = tag_has_impl;
};

template<>
struct tag_trait_helper<true, false, false>
{
	static const size_t tag = tag_pod;
};

template<>
struct tag_trait_helper<false, true, false>
{
	static const size_t tag = tag_array;
};

template<>
struct tag_trait_helper<false, false, true>
{
	static const size_t tag = tag_graphics_item;
};

template<class T> 
struct tag_trait
{
	static const size_t tag = tag_trait_helper<
		boost::is_pod<T>::value, 
		boost::is_array<T>::value, 
		boost::is_base_of<WItemData, T>::value
	>::tag;
};

TAG_TRAIT_SEQ_CONTAINER(std::vector)
TAG_TRAIT_SEQ_CONTAINER(std::list)
TAG_TRAIT_SEQ_CONTAINER(std::deque)
TAG_TRAIT_SEQ_CONTAINER(WWorldPolygonT)
TAG_TRAIT_SEQ_CONTAINER(WWorldPolylineT)

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

#endif