/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wworldpolygon.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WWorldPolygonTģ���࣬������ص�ȫ�ֺ���
  ����  ����:   
******************************************************************************/
#ifndef _WWORLD_POLYGON_H_
#define _WWORLD_POLYGON_H_

#include <utility>
#include <vector>
#include "wglobal.h"
#include "wworldrect.h"

/** 
 \brief                 ������Ҫʵ�ֶ���εĹ���
 \details    ��ĵ�һģ�����TΪ�������ͣ��ڶ�����AxΪ�����ڴ��������Ĭ��Ϊstd::allocator
				!!!!! �����һ�������������㣬���ҵ�һ��������һ������ȣ�
				�����������ʱ�������޸��ڲ�����ʱΥ����һ����׼��������е��쳣��Ϊ����Ը�
 \author    ����
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
	\remark    ����ε���С�߽�������� 
	*/
	WWorldRectT<T> boundingRect() const;

	/**
	\brief      containsPoint
	\Access    public 
	\param  const WWorldPointT<T> & point
	\retval     bool
	\remark    �ж�ĳһ���Ƿ��ڶ���������ڣ�������򷵻�true����֮Ϊfalse 
	*/
	bool containsPoint(const WWorldPointT<T>& point) const;

	/**
	\brief      isClosed
	\Access    public 
	\retval     bool
	\remark    �ж϶�����Ƿ��Ǳպϵģ�����Ǳպϵķ���true����֮Ϊfalse
					��������Ǳպϵģ��������ǷǷ��ģ����ᵼ������ʱ�Ĳ�ȷ���ԣ� 
	*/
	bool isClosed() const;

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     void
	\remark    �������ƽ�����ɵ�λ���������ı䣩 
	*/
	void translate(const WWorldPointT<T>& offset);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     WWorldPolygonT<T, Ax>
	\remark    �������ƽ�����ɵ�λ��������ƽ�ƺ�Ľ�������������ı䣩 
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
\remark    �˺�����Ҫ���ڸ���WWorldPolygon::containPoint���������Ӧ�Ĺ��� 
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
\remark    �ж�����������Ƿ���ȣ����Ƿ���ÿһ���㶼����ȵ� 
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