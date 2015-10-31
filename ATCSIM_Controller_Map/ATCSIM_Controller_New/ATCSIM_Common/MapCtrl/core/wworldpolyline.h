/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wworldpolyline.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WWorldPolylineTģ���࣬�������ȫ�ֺ���
  ����  ����:   
******************************************************************************/
#ifndef _WWORLD_POLYLINE_H_
#define _WWORLD_POLYLINE_H_

#include <vector>
#include "wglobal.h"
#include "wworldrect.h"
#include "wworldpoint.h"

/** 
 \brief                 ������Ҫʵ�����߹���
 \details  ��һģ�����TΪ�������ͣ��ڶ�ģ�����AxΪ�����ڴ�ռ��������Ĭ��Ϊstd::allocator 
 \author    ����
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
	\remark    ���ش����ߵ���С�߽�������� 
	*/
	WWorldRectT<T> boundingRect() const;

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     void
	\remark    ������ƽ�����ɸ���λ���������ı䣩 
	*/
	void translate(const WWorldPointT<T>& offset);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     WWorldPolylineT<T, Ax>
	\remark    ������ƽ�����ɸ���λ������ƽ�ƺ�Ľ�������������ı䣩 
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
\remark    �ж����������Ƿ���ȣ�����ÿ���㶼����� 
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