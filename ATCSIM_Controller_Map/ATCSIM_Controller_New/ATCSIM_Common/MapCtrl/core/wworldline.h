/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wworldline.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WWorldLineTģ����
  ����  ����:   
******************************************************************************/
#ifndef _WWORLD_LINE_H_
#define _WWORLD_LINE_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include "wglobal.h"
#include "wworldpoint.h"

/** 
 \brief                 ������ҪΪֱ�ߵĸ������
\details   
 \author    ����
\date      2013/05/22
*/
template<class T>
class WWorldLineT
{
public:
	WWorldLineT();
	WWorldLineT(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2);
	WWorldLineT(T x1, T y1, T x2, T y2);

	/**
	\brief      p1
	\Access    public 
	\retval     WWorldPointT<T>
	\remark    ����ֱ�ߵ���� 
	*/
	inline WWorldPointT<T> p1() const;

	/**
	\brief      p2
	\Access    public 
	\retval     WWorldPointT<T>
	\remark    ����ֱ�ߵ��յ� 
	*/
	inline WWorldPointT<T> p2() const;
	inline T x1 () const;
	inline T x2 () const;
	inline T y1 () const;
	inline T y2 () const;
	inline T dx () const;
	inline T dy () const;

	/**
	\brief      length
	\Access    public 
	\retval     T
	\remark    ����ֱ�ߵĳ��� 
	*/
	inline T	length () const;

	/**
	\brief      center
	\Access    public 
	\retval     WWorldPointT<T>
	\remark    ����ֱ�ߵ����ĵ� 
	*/
	inline WWorldPointT<T> center() const;

	/**
	\brief      setP1
	\Access    public 
	\param  const WWorldPointT<T> & p1
	\retval     void
	\remark    ����ֱ�ߵ���� 
	*/
	inline void setP1(const WWorldPointT<T>& p1);

	/**
	\brief      setP2
	\Access    public 
	\param  const WWorldPointT<T> & p2
	\retval     void
	\remark    ����ֱ�ߵ��յ� 
	*/
	inline void setP2(const WWorldPointT<T>& p2);

	/**
	\brief      setAngle
	\Access    public 
	\param  double angle
	\retval     void
	\remark    ����ֱ�ߵĽǶ� 
	*/
	inline void setAngle(double angle);

	/**
	\brief      setLength
	\Access    public 
	\param  T len
	\retval     void
	\remark    ����ֱ�ߵĳ��� 
	*/
	inline void setLength(T len);

	/**
	\brief      setLine
	\Access    public 
	\param  T x1
	\param  T y1
	\param  T x2
	\param  T y2
	\retval     void
	\remark    ����ֱ�� 
	*/
	inline void setLine(T x1, T y1, T x2, T y2);

	/**
	\brief      setPoints
	\Access    public 
	\param  const WWorldPointT<T> & p1
	\param  const WWorldPointT<T> & p2
	\retval     void
	\remark    ����ֱ�� 
	*/
	inline void setPoints(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2);

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     void
	\remark    ��ֱ��ƽ�� 
	*/
	inline void translate(const WWorldPointT<T>& offset);

	/**
	\brief      translate
	\Access    public 
	\param  T dx
	\param  T dy
	\retval     void
	\remark    ��ֱ��ƽ�� 
	*/
	inline void translate (T dx, T dy);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & offset
	\retval     WWorldLineT<T>
	\remark    ����ֱ��ƽ�ƺ�Ľ���������ı䣩 
	*/
	inline WWorldLineT<T> translated(const WWorldPointT<T>& offset) const;

	/**
	\brief      translated
	\Access    public 
	\param  T dx
	\param  T dy
	\retval     WWorldLineT<T>
	\remark    ����ֱ��ƽ�ƺ�Ľ���������ı䣩 
	*/
	inline WWorldLineT<T> translated(T dx, T dy) const;

	/**
	\brief      angle
	\Access    public 
	\retval     double
	\remark    ����ֱ�ߵĽǶ� 
	*/
	double angle() const;

	/**
	\brief      angleTo
	\Access    public 
	\param  const WWorldLineT & line
	\retval     double
	\remark    ��������ֱ�ߵļн� 
	*/
	double angleTo(const WWorldLineT& line) const;

	/**
	\brief      normalVector
	\Access    public 
	\retval     WWorldLineT<T>
	\remark    ����ֱ�߶�Ӧ�ĵ�λ���� 
	*/
	inline WWorldLineT<T> normalVector() const;

	/**
	\brief      pointAt
	\Access    public 
	\param  double t
	\retval     WWorldPointT<T>
	\remark    ����ֱ���ϵĵ㣬��ֱ��Ϊ(x1, y1, x2, y2)���򷵻صĵ�P(x, y)�������t�Ĳ�������Ϊ
					x = x1 + (x2 - x1) * t = (1 - t) * x1 + t * x2
					y = y1 + (y2 - y1) * t = (1 - t) * y1 +��* y2
					ͨ��������
					t�(-��, 0) P��ֱ�����
					t�[0, 1] P��ֱ����
					t�[1, ��) P��ֱ���ұ�
	*/
	inline WWorldPointT<T>	pointAt (double t) const;

	/**
	\brief      unitVector
	\Access    public 
	\retval     WWorldLineT<T>
	\remark    ��ֱ�߶�Ӧ�ĵ�λ���� 
	*/
	inline WWorldLineT<T> unitVector() const;

	inline bool	operator!=(const WWorldLineT<T>& line) const;
	inline bool	operator==(const WWorldLineT<T>& line) const;

private:
	WWorldPointT<T> _p1;
	WWorldPointT<T> _p2;
};

template<class T>
WWorldLineT<T>::WWorldLineT()
{
}

template<class T>
WWorldLineT<T>::WWorldLineT(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2) : _p1(p1), _p2(p2) 
{
}

template<class T>
WWorldLineT<T>::WWorldLineT (T x1, T y1, T x2, T y2) : _p1(x1, y1), _p2(x2, y2) 
{
}

template<class T>
inline WWorldPointT<T> WWorldLineT<T>::p1() const
{ 
	return _p1; 
}

template<class T>
inline WWorldPointT<T> WWorldLineT<T>::p2() const 
{ 
	return _p2; 
}

template<class T>
inline T	WWorldLineT<T>::x1() const 
{ 
	return _p1.x(); 
}

template<class T>
inline T	WWorldLineT<T>::x2() const 
{ 
	return _p2.x(); 
}

template<class T>
inline T	WWorldLineT<T>::y1() const 
{ 
	return _p1.y(); 
}

template<class T>
inline T	WWorldLineT<T>::y2() const 
{ 
	return _p2.y();
}

template<class T>
inline T	WWorldLineT<T>::dx() const 
{ 
	return _p2.x() - _p1.x(); 
}

template<class T>
inline T	WWorldLineT<T>::dy() const 
{ 
	return _p2.y() - _p1.y(); 
}

template<class T>
inline T	WWorldLineT<T>::length () const 
{ 
	return static_cast<T>(sqrt(static_cast<double>(dx() * dx() + dy() * dy()))); 
}

template<class T>
inline WWorldPointT<T> WWorldLineT<T>::center() const
{
	return (_p1 + _p2) / 2;
}

template<class T>
inline WWorldLineT<T> WWorldLineT<T>::normalVector() const 
{ 
	return WWorldLineT<T>(p1(), p1() + WWorldPointT<T>(dy(), -dx())); 
}

template<class T>
inline WWorldPointT<T>	WWorldLineT<T>::pointAt (double t) const 
{ 
	return WWorldPointT<T>(static_cast<T>(_p1.x()+dx()*t), static_cast<T>(_p1.y()+dy()*t)); 
}

template<class T>
double	WWorldLineT<T>::angle () const
{
	T dx = _p2.x() - _p1.x();
	T dy = _p2.y() - _p1.y();

	double theta = atan2(static_cast<double>(dy), static_cast<double>(dx)) * 180.0 / M_PI;
	double theta_normalized = theta < 0 ? theta + 360 : theta;

	return wFuzzyCompare(theta_normalized, 360.0) ? 0.0 : theta_normalized;
}

template<class T>
double WWorldLineT<T>::angleTo(const WWorldLineT& line) const
{
	double delta = line.angle() - angle();
	double delta_normalized = delta < 0 ? delta + 360 : delta;
	return wFuzzyCompare(delta_normalized, 360.0) ? 0 : delta_normalized;
}

template<class T>
inline void WWorldLineT<T>::setP1(const WWorldPointT<T>& p1)
{
	_p1 = p1;
}

template<class T>
inline void WWorldLineT<T>::setP2(const WWorldPointT<T>& p2)
{
	_p2 = p2;
}

template<class T>
inline bool	WWorldLineT<T>::operator!=(const WWorldLineT<T>& line) const
{
	return !(*this == line);
}

template<class T>
inline bool	WWorldLineT<T>::operator==(const WWorldLineT<T>& line) const
{
	return _p1 == line._p1 && _p2 == line._p2;
}

template<class T>
void WWorldLineT<T>::setAngle(double angle)
{
	double angleR = angle * M_PI / 180.0;
	double l = length();

	_p2.setX(static_cast<T>(_p1.x() + cos(angleR) * l));
	_p2.setY(static_cast<T>(_p1.y() + sin(angleR) * l));
}

template<class T>
inline WWorldLineT<T> WWorldLineT<T>::unitVector() const
{
	return WWorldLineT<T>(_p1, WWorldPointT<T>(_p1.x()+static_cast<T>(dx() / length()), _p1.y()+static_cast<T>(dy() / length())));
}

template<class T>
inline void WWorldLineT<T>::setLength(T len)
{
	double factor = static_cast<double>(len) / length();
	_p2.setXY(_p1.x() + static_cast<T>(dx() * factor), _p1.y() + static_cast<T>(dy() * factor));
}

template<class T>
inline void WWorldLineT<T>::setLine(T x1, T y1, T x2, T y2)
{
	_p1.setXY(x1, y1);
	_p2.setXY(x2, y2);
}

template<class T>
inline void WWorldLineT<T>::setPoints(const WWorldPointT<T>& p1, const WWorldPointT<T>& p2)
{
	_p1 = p1;
	_p2 = p2;
}

template<class T>
inline void WWorldLineT<T>::translate(const WWorldPointT<T>& offset)
{
	_p1 += offset;
	_p2 += offset;
}

template<class T>
inline void WWorldLineT<T>::translate (T dx, T dy)
{
	translate(WWorldPointT<T>(dx, dy));
}

template<class T>
inline WWorldLineT<T> WWorldLineT<T>::translated(const WWorldPointT<T>& offset) const
{
	return WWorldLineT<T>(_p1 + offset, _p2 + offset);
}

template<class T>
inline WWorldLineT<T> WWorldLineT<T>::translated(T dx, T dy) const
{
	return translated(WWorldPointT<T>(dx, dy));
}

typedef WWorldLineT<int> WWorldLine;
typedef WWorldLineT<double> WWorldLineF;
typedef WWorldLineF WLineF;

#endif