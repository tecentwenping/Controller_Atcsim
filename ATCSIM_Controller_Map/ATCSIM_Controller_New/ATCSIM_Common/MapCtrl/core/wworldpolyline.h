/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wworldpolyline.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WWorldPolylineT模板类，及其相关全局函数
  【其  它】:   
******************************************************************************/
#ifndef _WWORLD_POLYLINE_H_
#define _WWORLD_POLYLINE_H_

#include <vector>
#include "wglobal.h"
#include "wworldrect.h"
#include "wworldpoint.h"

/** 
 \brief                 此类主要实现折线功能
 \details  第一模板参数T为数据类型，第二模板参数Ax为对象内存空间分配器，默认为std::allocator 
 \author    陈龙
\date      2013/05/22
*/
template<class T, class Ax = std::allocator<WWorldPointT<T> > >
class WWorldPolylineT : public std::vector<WWorldPointT<T>, Ax>
{
public:
	WWorldPolylineT();
	explicit WWorldPolylineT(int size);
	explicit WWorldPolylineT(const std::vector<WWorldPointT<T>, Ax>& points);
	WWorldPolylineT(int size, const WWorldPointT<T>& p);
	WWorldPolylineT(const WWorldPointT<T>* p, int size);

	WWorldPolylineT<T, Ax>& operator=(const std::vector<WWorldPointT<T>, Ax>& points);

	/**
	\brief      boundingRect
	\Access    public 
	\retval     WWorldRectT<T>
	\remark    返回此折线的最小边界矩形区域 
	*/
	WWorldRectT<T> boundingRect() const;

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     void
	\remark    将折线平移若干个单位（本身发生改变） 
	*/
	void translate(const WWorldPointT<T>& offset);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     WWorldPolylineT<T, Ax>
	\remark    将折线平移若干个单位，返回平移后的结果（本身不发生改变） 
	*/
	WWorldPolylineT<T, Ax> translated(const WWorldPointT<T>& offset) const;
};

template<class T, class Ax>
WWorldPolylineT<T, Ax>::WWorldPolylineT()
{
}

template<class T, class Ax>
WWorldPolylineT<T, Ax>::WWorldPolylineT(int size) : std::vector<WWorldPointT<T>, Ax>(size)
{
}

template<class T, class Ax>
WWorldPolylineT<T, Ax>::WWorldPolylineT(const std::vector<WWorldPointT<T>, Ax>& points) : std::vector<WWorldPointT<T>, Ax>(points)
{
}

template<class T, class Ax>
WWorldPolylineT<T, Ax>::WWorldPolylineT(int size, const WWorldPointT<T>& p) : std::vector<WWorldPointT<T> >(size, p)
{
}

template<class T, class Ax>
WWorldPolylineT<T, Ax>::WWorldPolylineT(const WWorldPointT<T>* p, int size) : std::vector<WWorldPointT<T> >(p, p+size)
{
}

template<class T, class Ax>
WWorldRectT<T> WWorldPolylineT<T, Ax>::boundingRect() const
{
	if (empty()) 
		return WWorldRectT<T>();

	const WWorldPointT<T>* p = &at(0);
	T xmin = p->x();
	T xmax = p->x();
	T ymin = p->y();
	T ymax = p->y();
	++p;

	int sz = size();
	for (int i=1; i<sz; ++i)
	{
		if (p->x() < xmin)
			xmin = p->x();
		else if (p->x() > xmax)
			xmax = p->x();

		if (p->y() < ymin)
			ymin = p->y();
		else if (p->y() > ymax)
			ymax = p->y();

		++p;
	}

	return WWorldRectT<T>(xmin, ymin, xmax-xmin, ymax-ymin);
}

template<class T, class Ax>
void WWorldPolylineT<T, Ax>::translate(const WWorldPointT<T>& offset)
{
	int sz = size();
	WWorldPointT<T>* p = &*begin();

	while (sz--)
	{
		*p += offset;
		++p;
	}
}

template<class T, class Ax>
WWorldPolylineT<T, Ax> WWorldPolylineT<T, Ax>::translated(const WWorldPointT<T>& offset) const
{
	WWorldPolylineT<T, Ax> copy(*this);
	copy.translate(offset);
	return copy;
}

template<class T, class Ax>
WWorldPolylineT<T, Ax>& WWorldPolylineT<T, Ax>::operator=(const std::vector<WWorldPointT<T>, Ax>& points)
{
	std::vector<WWorldPointT<T>, Ax>& base = *this;
	if (&base != &points)
	{
		base = points;
	}
	return *this;
}

/**
\brief      operator==
\Access    public 
\param  const WWorldPolylineT<T
\param  Ax> & lhs
\param  const WWorldPolylineT<T
\param  Ax> & rhs
\retval     bool
\remark    判断两条折线是否相等，即是每个点都是相等 
*/
template<class T, class Ax>
inline bool operator==(const WWorldPolylineT<T, Ax>& lhs, const WWorldPolylineT<T, Ax>& rhs)
{
	return static_cast<const std::vector<WWorldPointT<T>, Ax>&>(lhs) == static_cast<const std::vector<WWorldPointT<T>, Ax>&>(rhs);
}

template<class T, class Ax>
inline bool operator==(const WWorldPolylineT<T, Ax>& lhs, const std::vector<WWorldPointT<T>, Ax>& rhs)
{
	return static_cast<const std::vector<WWorldPointT<T> >&>(lhs) == rhs;
}

template<class T, class Ax>
inline bool operator==(const std::vector<WWorldPointT<T>, Ax>& lhs, const WWorldPolylineT<T, Ax>& rhs)
{
	return lhs == static_cast<const std::vector<WWorldPointT<T> >&>(rhs);
}

typedef WWorldPolylineT<int> WWorldPolyline;
typedef WWorldPolylineT<double> WWorldPolylineF;
typedef WWorldPolylineF WPolylineF;

#endif