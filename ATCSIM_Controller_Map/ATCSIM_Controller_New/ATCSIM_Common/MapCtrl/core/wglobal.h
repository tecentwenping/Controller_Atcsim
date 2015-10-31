/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wglobal.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  此文件一些功能性的全局函数
  【其  它】:   
******************************************************************************/
#ifndef _WGLOBAL_H_
#define _WGLOBAL_H_

#include <limits>
#include <cmath>
#include "../wdllimport.h"

#define NS_GLOBAL_BEGIN namespace Ws {
#define NS_GLOBAL_END }

/**
\brief      bit
\Access    public 
\param  int i
\retval     int MAPAPI
\remark    返回一个数的二进制 
*/
int MAPAPI bit(int i);

/**
\brief      wFuzzyCompare
\Access    public 
\param  float f1
\param  float f2
\retval     bool  相等为true，反之为false 
\remark    判断两个float是否相等
*/
inline bool wFuzzyCompare(float f1, float f2)
{
	static const float epsilon = std::numeric_limits<float>::epsilon();
	return -epsilon <= (f2 - f1)  && (f2 - f1) <= epsilon;
}

/**
\brief      wFuzzyCompare
\Access    public 
\param  double d1
\param  double d2
\retval     bool 相等为true，反之为false
\remark     判断两个double是否相等
*/
inline bool wFuzzyCompare(double d1, double d2)
{
	static const double epsilon = std::numeric_limits<double>::epsilon();
	return -epsilon <= (d2 - d1) && (d2 - d1) <= epsilon;
}

/**
\brief      wRound
\Access    public 
\param  double d
\retval     int
\remark    浮点数的四舍五入功能 
*/
inline int wRound(double d)
{ 
	return d >= 0.0 ? int(d + 0.5) : int(d - int(d-1) + 0.5) + int(d-1); 
}

/**
\brief      wCompare
\Access    public 
\param  double d1
\param  double d2
\retval     bool 相等返回true，反之为false
\remark    比较两个double是否相等，模板参数为比较的精度，也就是小数点后面多少位 
*/
template<int precision>
inline bool wCompare(double d1, double d2)
{
	static const double epsilon = pow(10.0, static_cast<double>(precision));
	return fabs(d1 - d2) <= epsilon;
}

/**
\brief      wMin
\Access    public 
\param  const T & a
\param  const T & b
\retval     const T&
\remark    返回两个数的最小值 
*/
template <typename T>
inline const T& wMin(const T &a, const T &b) 
{ 
	return a < b ? a : b;
}

/**
\brief      wMin
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\retval     const T&
\remark    返回三个数的最小值 
*/
template<class T>
inline const T& wMin(const T& t1, const T& t2, const T& t3)
{
	return wMin(t1, wMin(t2, t3));
}

/**
\brief      wMin
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\retval     const T&
\remark    返回四个数的最小值 
*/
template<class T>
inline const T& wMin(const T& t1, const T& t2, const T& t3, const T& t4)
{
	return wMin(t1, wMin(t2, t3, t4));
}

/**
\brief      wMin
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\param  const T & t5
\retval     const T&
\remark    返回五个数的最小值 
*/
template<class T>
inline const T& wMin(const T& t1, const T& t2, const T& t3, const T& t4, const T& t5)
{
	return wMin(t1, wMin(t2, t3, t4, t5));
}

/**
\brief      wMin
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\param  const T & t5
\param  const T & t6
\retval     const T&
\remark 返回六个数的最小值    
*/
template<class T>
inline const T& wMin(const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6)
{
	return wMin(t1, wMin(t2, t3, t4, t5, t6));
}

/**
\brief      wMax
\Access    public 
\param  const T & a
\param  const T & b
\retval     const T &
\remark    返回两个数的最大值 
*/
template <typename T>
inline const T &wMax(const T &a, const T &b) 
{ 
	return a > b ? a : b;
}

/**
\brief      wMax
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\retval     const T&
\remark    返回三个数的最大值 
*/
template<class T>
inline const T& wMax(const T& t1, const T& t2, const T& t3)
{
	return wMax(t1, wMax(t2, t3));
}

/**
\brief      wMax
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\retval     const T&
\remark    返回四个数的最大值 
*/
template<class T>
inline const T& wMax(const T& t1, const T& t2, const T& t3, const T& t4)
{
	return wMax(t1, wMax(t2, t3, t4));
}

/**
\brief      wMax
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\param  const T & t5
\retval     const T&
\remark    返回五个数的最大值 
*/
template<class T>
inline const T& wMax(const T& t1, const T& t2, const T& t3, const T& t4, const T& t5)
{
	return wMax(t1, wMax(t2, t3, t4, t5));
}

/**
\brief      wMax
\Access    public 
\param  const T & t1
\param  const T & t2
\param  const T & t3
\param  const T & t4
\param  const T & t5
\param  const T & t6
\retval     const T&
\remark   返回六个数的最大值  
*/
template<class T>
inline const T& wMax(const T& t1, const T& t2, const T& t3, const T& t4, const T& t5, const T& t6)
{
	return wMax(t1, wMax(t2, t3, t4, t5, t6));
}

/**
\brief      wBound
\Access    public 
\param  const T & min
\param  const T & val
\param  const T & max
\retval     const T &
\remark 对val进行修正，确保返回值在min和max之间
			 如果val > max 返回max
			 如果val < min 返回min
			 其它返回val
*/
template <typename T>
inline const T &wBound(const T &min, const T &val, const T &max)
{ 
	return wMax(min, wMin(max, val));
}

/**
\brief      numeric_equal
\Access    public 
\param  T lhs
\param  T rhs
\retval     bool
\remark    比较两个数是否相等，相等返回true，反之false 
*/
template<class T>
inline bool numeric_equal(T lhs, T rhs)
{
	static const T epsilon = std::numeric_limits<T>::epsilon();
	return -epsilon <= (lhs - rhs) && (lhs - rhs) <= epsilon;
}

/**
\brief      array_size
\Access    public 
\param  const T 
\param  & 
\param  [N]
\retval     size_t
\remark    返回数组的大小 
*/
template<class T, size_t N>
inline size_t array_size(const T (&)[N])
{
	return N;
}

/**
\brief      in_range
\Access    public 
\param  const T & start
\param  const T & end
\param  const T & t
\retval     bool
\remark    判断某个数t是否在[start, end]范围内，是则返回true，反之false 
*/
template<class T>
inline bool in_range(const T& start, const T& end, const T& t)
{
	return (start <= t && t <= end) || (end <= t && t <= start);
}

/**
\brief      approximate_integer
\Access    public 
\param  double d
\retval     int
\remark     返回浮点数的四舍五入值
*/
inline int approximate_integer(double d)
{
	return static_cast<int>(d + 0.5);
}

/**
\brief      approximate_integer
\Access    public 
\param  float f
\retval     int
\remark     返回浮点数的四舍五入值
*/
inline int approximate_integer(float f)
{
	return static_cast<int>(f + 0.5f);
}

/**
\brief      fillbit
\Access    public 
\param  int i
\param  int index
\param  bool on
\retval     int
\remark    给一个整数i的二进制形式的i第index位设置为on 
*/
inline int fillbit(int i, int index, bool on)
{
	return on ? (i | (1 << index)) : (i & ~(1 << index));
}

/**
\brief      getbit
\Access    public 
\param  int i
\param  int index
\retval     bool
\remark    获取一个整数i的二进制形式的第index位 
*/
inline bool getbit(int i, int index)
{
	return (i >> index) & 1;
}

/**
\brief      normalized_angle
\Access    public 
\param  double angle
\retval     double
\remark    将一个角度正规化，即是将角度控制在[0, 360)之间 
*/
inline double normalized_angle(double angle)
{
	return fmod((fmod(angle, 360.0) + 360.0), 360.0);
}

/**
\brief     COLOR 
\Access    public 
\param  int
\param  int
\param  int
\retval    int 
\remark  用rgb三个整数构造一个代表颜色的整数 
*/
#define COLOR(r, g, b) ((((unsigned int)(unsigned char)r) << 16) | (((unsigned int)(unsigned char)g) << 8) | ((((unsigned int)(unsigned char)r))))
 
#endif