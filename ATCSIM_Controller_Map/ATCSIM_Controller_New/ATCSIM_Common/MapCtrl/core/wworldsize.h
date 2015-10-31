/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wworldsize.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要实现了WWorldSizeT模板类，然后是WWorldSizeT类相关的全局函数，
					重新定义了WWorldSizeT<int> WWorldSizeT<double>
  【其  它】:   
******************************************************************************/
#ifndef _WWORLD_SIZE_H_
#define _WWORLD_SIZE_H_

#include <utility>
#include <xutility>
#include "wglobal.h"

/** 
 \brief                 此类主要用来表达大小概念
\details   
 \author    陈龙
\date      2013/05/22
*/
template<class T>
class WWorldSizeT
{
public:
	WWorldSizeT();
	WWorldSizeT(T w, T h);

	inline T width() const;
	inline T height() const;

	inline void setWidth(T w);
	inline void setHeight(T h);

	/**
	\brief      isValid
	\Access    public 
	\retval     bool
	\remark    大小是否为合法 
	*/
	inline bool isValid() const;

	/**
	\brief      isEmpty
	\Access    public 
	\retval     bool
	\remark    大小是否为空 
	*/
	inline bool isEmpty() const;

	/**
	\brief      transpose
	\Access    public 
	\retval     void
	\remark    交换大小的width和height 
	*/
	inline void transpose();

	/**
	\brief      boundedTo
	\Access    public 
	\param  const WWorldSizeT<T> & other
	\retval     WWorldSizeT<T>
	\remark    返回两个大小的交集 
	*/
	inline WWorldSizeT<T> boundedTo(const WWorldSizeT<T>& other) const;

	/**
	\brief      expandedTo
	\Access    public 
	\param  const WWorldSizeT<T> & other
	\retval     WWorldSizeT<T>
	\remark    返回两个大小的并集 
	*/
	inline WWorldSizeT<T> expandedTo(const WWorldSizeT<T>& other) const;

	inline WWorldSizeT<T> operator+=(const WWorldSizeT<T>& size);
	inline WWorldSizeT<T> operator-=(const WWorldSizeT<T>& size);
	inline WWorldSizeT<T> operator*=(double factor);
	inline WWorldSizeT<T> operator/=(double divisor);

private:
	T _w;
	T _h;
};

template<class T>
WWorldSizeT<T>::WWorldSizeT() : _w(T()), _h(T())
{
}

template<class T>
WWorldSizeT<T>::WWorldSizeT(T w, T h) : _w(w), _h(h)
{
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::boundedTo(const WWorldSizeT<T>& other) const
{
	return WWorldSizeT<T>(std::min(_w, other._w), std::min(_h, other._h));
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::expandedTo(const WWorldSizeT<T>& other) const
{
	return WWorldSizeT<T>(std::max(_w, other._w), std::max(_h, other._h));
}

template<class T>
inline T WWorldSizeT<T>::width() const
{
	return _w;
}

template<class T>
inline T WWorldSizeT<T>::height() const
{
	return _h;
}

template<class T>
inline void WWorldSizeT<T>::setWidth(T w)
{
	_w = w;
}

template<class T>
inline void WWorldSizeT<T>::setHeight(T h)
{
	_h = h;
}

template<class T>
inline bool WWorldSizeT<T>::isValid() const
{
	return _w >= T() && _h >= T();
}

template<class T>
inline bool WWorldSizeT<T>::isEmpty() const
{
	return _w <= T() || _h <= T();
}

template<class T>
inline void WWorldSizeT<T>::transpose()
{
	std::swap(_w, _h);
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::operator+=(const WWorldSizeT<T>& size)
{
	_w += size._w;
	_h += size._h;
	return *this;
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::operator-=(const WWorldSizeT<T>& size)
{
	_w -= size._w;
	_h -= size._h;
	return *this;
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::operator*=(double factor)
{
	_w = static_cast<T>(_w * factor);
	_h = static_cast<T>(_h * factor);
	return *this;
}

template<class T>
inline WWorldSizeT<T> WWorldSizeT<T>::operator/=(double divisor)
{
	_w = static_cast<T>(_w / divisor);
	_h = static_cast<T>(_h / divisor);
	return *this;
}

template<class T>
inline bool operator==(const WWorldSizeT<T>& lhs, const WWorldSizeT<T>& rhs)
{
	return numeric_equal(lhs.width(), rhs.width()) && numeric_equal(lhs.height(), rhs.height());
}

template<class T>
inline bool operator!=(const WWorldSizeT<T>& lhs, const WWorldSizeT<T>& rhs)
{
	return !(lhs == rhs);
}

template<class T>
inline const WWorldSizeT<T> operator*(const WWorldSizeT<T>& size, double factor)
{
	return WWorldSizeT<T>(size) *= factor;
}

template<class T>
inline const WWorldSizeT<T> operator*(double factor, const WWorldSizeT<T>& size)
{
	return size * factor;
}

template<class T>
inline const WWorldSizeT<T> operator+(const WWorldSizeT<T>& s1, const WWorldSizeT<T>& s2)
{
	return WWorldSizeT<T>(s1) += s2;
}

template<class T>
inline const WWorldSizeT<T> operator-(const WWorldSizeT<T>& s1, const WWorldSizeT<T>& s2)
{
	return WWorldSizeT<T>(s1) -= s2;
}

template<class T>
inline const WWorldSizeT<T> operator/(const WWorldSizeT<T>& size, double divisor)
{
	return WWorldSizeT<T>(size) /= divisor;
}

typedef WWorldSizeT<int> WWorldSize;
typedef WWorldSizeT<double> WWorldSizeF;
typedef WWorldSizeF WSizeF;
typedef WWorldSize WSize;

#endif