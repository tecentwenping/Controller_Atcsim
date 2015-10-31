/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wworldpolygon.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WWorldPolygonT模板类，及其相关的全局函数
  【其  它】:   
******************************************************************************/
#ifndef _WWORLD_POLYGON_H_
#define _WWORLD_POLYGON_H_

#include <utility>
#include <vector>
#include "wglobal.h"
#include "wworldrect.h"

/** 
 \brief                 此类主要实现多边形的功能
 \details    类的第一模板参数T为数据类型，第二参数Ax为对象内存分配器，默认为std::allocator
				!!!!! 多边形一般至少有三个点，并且第一个点和最后一个点相等，
				如果构造多边形时或者在修改内部数据时违背这一基本准则，造成运行的异常行为后果自负
 \author    陈龙
\date      2013/05/22
*/
template<class T, class Ax = std::allocator<WWorldPointT<T> > >
class WWorldPolygonT : public std::vector<WWorldPointT<T>, Ax>
{
public:
	WWorldPolygonT();
	explicit WWorldPolygonT(int size);
	explicit WWorldPolygonT(const std::vector<WWorldPointT<T>, Ax>& points);
	explicit WWorldPolygonT(const WWorldRectT<T>& rect);
	WWorldPolygonT(int size, const WWorldPointT<T>& p);

	WWorldPolygonT<T, Ax>& operator=(const std::vector<WWorldPointT<T>, Ax>& points);

	/**
	\brief      boundingRect
	\Access    public 
	\retval     WWorldRectT<T>
	\remark    多边形的最小边界矩形区域 
	*/
	WWorldRectT<T> boundingRect() const;

	/**
	\brief      containsPoint
	\Access    public 
	\param  const WWorldPointT<T> & point
	\retval     bool
	\remark    判断某一点是否在多边形区域内，如果是则返回true，反之为false 
	*/
	bool containsPoint(const WWorldPointT<T>& point) const;

	/**
	\brief      isClosed
	\Access    public 
	\retval     bool
	\remark    判断多边形是否是闭合的，如果是闭合的返回true，反之为false
					（如果不是闭合的，则多边形是非法的，将会导致运行时的不确定性） 
	*/
	bool isClosed() const;

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     void
	\remark    将多边形平移若干单位（本身发生改变） 
	*/
	void translate(const WWorldPointT<T>& offset);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     WWorldPolygonT<T, Ax>
	\remark    将多边形平移若干单位，并返回平移后的结果（本身不发生改变） 
	*/
	WWorldPolygonT<T, Ax> translated(const WWorldPointT<T>& offset) const;
};

template<class T, class Ax>
WWorldPolygonT<T, Ax>::WWorldPolygonT()
{
}

template<class T, class Ax>
WWorldPolygonT<T, Ax>::WWorldPolygonT(int size) : std::vector<WWorldPointT<T>, Ax>(size)
{
}

template<class T, class Ax>
WWorldPolygonT<T, Ax>::WWorldPolygonT(const std::vector<WWorldPointT<T>, Ax>& points) : std::vector<WWorldPointT<T>, Ax>(points)
{
}

template<class T, class Ax>
WWorldPolygonT<T, Ax>::WWorldPolygonT(const WWorldRectT<T>& rect) : std::vector<WWorldPointT<T>, Ax>(5)
{
	at(0) = rect.topLeft();
	at(1) = rect.topRight();
	at(2) = rect.bottomRight();
	at(3) = rect.bottomLeft();
	at(4) = rect.topLeft();
}

template<class T, class Ax>
WWorldPolygonT<T, Ax>::WWorldPolygonT(int size, const WWorldPointT<T>& p) : std::vector<WWorldPointT<T>, Ax>(size, p)
{
}

template<class T, class Ax>
WWorldRectT<T> WWorldPolygonT<T, Ax>::boundingRect() const
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

/**
\brief      ws_polygon_isect_line_world
\Access    public static 
\param  const WWorldPointT<T> & p1
\param  const WWorldPointT<T> & p2
\param  const WWorldPointT<T> & pos
\param  int * winding
\retval     void
\remark    此函数主要用于辅助WWorldPolygon::containPoint函数完成相应的功能 
*/
template<class T>
static void ws_polygon_isect_line_world(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2, 
								  const WWorldPointT<T>& pos, int* winding)
{
	T x1 = p1.x();
	T y1 = p1.y();
	T x2 = p2.x();
	T y2 = p2.y();
	T y = pos.y();

	int dir = 1;
	if (numeric_equal(y1, y2))
	{
		return;
	}
	else if (y2 < y1)
	{
		dir = -1;
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y >= y1 && y < y2)
	{
		double x = x1 + static_cast<double>(x2-x1) / (y2 - y1) * (y - y1);
		if (x <= pos.x())
		{
			(*winding) += dir;
		}
	}
}

template<class T, class Ax>
bool WWorldPolygonT<T, Ax>::containsPoint(const WWorldPointT<T>& point) const
{
	if (empty())
		return false;

	int winding_number = 0;
	unsigned sz = size();
	for (unsigned i=0; i<sz-1; ++i)
	{
		ws_polygon_isect_line_world(at(i), at(i+1), point, &winding_number);
	}

	return winding_number & 1;
}

template<class T, class Ax>
bool WWorldPolygonT<T, Ax>::isClosed() const
{
	return *begin() == *rbegin();
}

template<class T, class Ax>
void WWorldPolygonT<T, Ax>::translate(const WWorldPointT<T>& offset)
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
WWorldPolygonT<T, Ax> WWorldPolygonT<T, Ax>::translated(const WWorldPointT<T>& offset) const
{
	WWorldPolygonT<T, Ax> copy(*this);
	copy.translate(offset);
	return copy;
}

template<class T, class Ax>
WWorldPolygonT<T, Ax>& WWorldPolygonT<T, Ax>::operator=(const std::vector<WWorldPointT<T>, Ax>& points)
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
\param  const WWorldPolygonT<T
\param  Ax> & lhs
\param  const WWorldPolygonT<T
\param  Ax> & rhs
\retval     bool
\remark    判断两个多边形是否相等，即是否是每一个点都是相等的 
*/
template<class T, class Ax>
inline bool operator==(const WWorldPolygonT<T, Ax>& lhs, const WWorldPolygonT<T, Ax>& rhs)
{
	return static_cast<const std::vector<WWorldPointT<T>, Ax>&>(lhs) == static_cast<const std::vector<WWorldPointT<T>, Ax>&>(rhs);
}

template<class T, class Ax>
inline bool operator==(const WWorldPolygonT<T, Ax>& lhs, const std::vector<WWorldPointT<T>, Ax>& rhs)
{
	return static_cast<const std::vector<WWorldPointT<T>, Ax>&>(lhs) == rhs;
}

template<class T, class Ax>
inline bool operator==(const std::vector<WWorldPointT<T>, Ax>& lhs, const WWorldPolygonT<T, Ax>& rhs)
{
	return lhs == static_cast<const std::vector<WWorldPointT<T>, Ax>&>(rhs);
}

typedef WWorldPolygonT<int> WWorldPolygon;
typedef WWorldPolygonT<double> WWorldPolygonF;
typedef WWorldPolygonF WPolygonF;
typedef WWorldPolygon WPolygon;

#endif