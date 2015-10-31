/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wworldpoint.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  此文件主要实现WWorldPointT模板类，及其相关的全局函数
  【其  它】:   
******************************************************************************/
#ifndef _WWORLD_POINT_H_
#define _WWORLD_POINT_H_

#include <cmath>
#include "wglobal.h"

/** 
 \brief                 此类主要实现坐标点的概念抽象
\details   
 \author    陈龙
\date      2013/05/22
*/
template<class T>
class WWorldPointT
{
public:
	WWorldPointT();
	WWorldPointT(T x, T y);

	inline T x() const;
	inline T y() const;

	inline T& rx();
	inline T& ry();

	inline void setX(T x);
	inline void setY(T y);
	inline void setXY(T x, T y);

	inline WWorldPointT& operator+=(const WWorldPointT& p);
	inline WWorldPointT& operator-=(const WWorldPointT& p);
	inline WWorldPointT& operator*=(double factor);
	inline WWorldPointT& operator/=(double divisor);

public:
	T _x;
	T _y;
};

template<class T>
WWorldPointT<T>::WWorldPointT() : _x(T()), _y(T()) 
{
}

template<class T>
WWorldPointT<T>::WWorldPointT(T x, T y) : _x(x), _y(y) 
{
}

template<class T>
inline T WWorldPointT<T>::x() const 
{ 
	return _x; 
}

template<class T>
inline T WWorldPointT<T>::y() const 
{ 
	return _y; 
}

template<class T>
inline T& WWorldPointT<T>::rx() 
{ 
	return _x; 
}

template<class T>
inline T& WWorldPointT<T>::ry() 
{ 
	return _y; 
}

template<class T>
inline void WWorldPointT<T>::setX(T x) 
{ 
	_x = x; 
}

template<class T>
inline void WWorldPointT<T>::setY(T y) 
{ 
	_y = y; 
}

template<class T>
inline void WWorldPointT<T>::setXY(T x, T y)
{
	_x = x;
	_y = y;
}

template<class T>
inline WWorldPointT<T>& WWorldPointT<T>::operator+=(const WWorldPointT& p)
{
	_x += p._x;
	_y += p._y;
	return *this;
}

template<class T>
inline WWorldPointT<T>& WWorldPointT<T>::operator-=(const WWorldPointT& p)
{
	_x -= p._x;
	_y -= p._y;
	return *this;
}

template<class T>
inline WWorldPointT<T>& WWorldPointT<T>::operator*=(double factor)
{
	_x = static_cast<T>(_x * factor);
	_y = static_cast<T>(_y * factor);
	return *this;
}

template<class T>
inline WWorldPointT<T>& WWorldPointT<T>::operator/=(double divisor)
{
	_x = static_cast<T>(_x / divisor);
	_y = static_cast<T>(_y / divisor);
	return *this;
}

template<class T>
inline bool operator==(const WWorldPointT<T>& lhs, const WWorldPointT<T>& rhs)
{
	return numeric_equal(lhs.x(), rhs.x()) && numeric_equal(lhs.y(), rhs.y());
}

template<class T>
inline bool operator!=(const WWorldPointT<T>& lhs, const WWorldPointT<T>& rhs)
{
	return !(lhs == rhs);
}

template<class T>
inline const WWorldPointT<T> operator+(const WWorldPointT<T>& lhs, const WWorldPointT<T>& rhs)
{
	return WWorldPointT<T>(lhs) += rhs;
}

template<class T>
inline const WWorldPointT<T> operator-(const WWorldPointT<T>& lhs, const WWorldPointT<T>& rhs)
{
	return WWorldPointT<T>(lhs) -= rhs;
}

template<class T>
inline const WWorldPointT<T> operator-(const WWorldPointT<T>& p)
{
	return WWorldPointT<T>(-p.x(), -p.y());
}

template<class T>
inline const WWorldPointT<T> operator*(const WWorldPointT<T>& p, double factor)
{
	return WWorldPointT<T>(p) *= factor;
}

template<class T>
inline const WWorldPointT<T> operator*(double factor, const WWorldPointT<T>& p)
{
	return p * factor;
}

template<class T>
inline const WWorldPointT<T> operator/(const WWorldPointT<T>& p, double divisor)
{
	return WWorldPointT<T>(p) /= divisor;
}

/**
\brief      distance
\Access    public 
\param  const WWorldPointT<T> & lhs
\param  const WWorldPointT<T> & rhs
\retval     double
\remark    计算两点之间直线的距离 
*/
template<class T>
inline double distance(const WWorldPointT<T>& lhs, const WWorldPointT<T>& rhs)
{
	T dx = rhs.x() - lhs.x();
	T dy = rhs.y() - lhs.y();
	return sqrt(static_cast<double>(dx * dx + dy * dy));
}

/**
\brief      triangleArea
\Access    public 
\param  const WWorldPointT<T> & p1
\param  const WWorldPointT<T> & p2
\param  const WWorldPointT<T> & p3
\retval     T
\remark    计算三角形的面积 
*/
template<class T>
T triangleArea(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2, const WWorldPointT<T>& p3)
{
	T x1 = p1.x();
	T x2 = p2.x();
	T x3 = p3.x();
	T y1 = p1.y();
	T y2 = p2.y();
	T y3 = p3.y();

	//					|x1, y1, 1|
	//S = 1/2*		|x2, y2, 1|
	//					|x3, y3, 1|
	T t = x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
	t /= 2;
	return t > 0 ? t : -t;
}

typedef WWorldPointT<int> WWorldPoint;
typedef WWorldPointT<double> WWorldPointF;
typedef WWorldPointF WPointF;
typedef WWorldPoint WPoint;

#endif