/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wworldrect.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫʵ����ģ����WWorldRectT����WWorldRectT����ص�ȫ�ֺ���
  ����  ����:   
******************************************************************************/
#ifndef _WWORLD_RECT_H_
#define _WWORLD_RECT_H_

#include "wglobal.h"
#include "wworldsize.h"
#include "wworldpoint.h"

/** 
 \brief                 ������Ҫ���ڱ���������ĸ���
\details   !!!!!!! ��Ϊ�Ժ��õ��Ķ�����������ϵͳ���ʾ��ε���㲢��������ͨ����Ϊ��top-left����bottom-left
 \author    ����
\date      2013/05/22
*/
template<class T>
class WWorldRectT
{
public:
	WWorldRectT();
	WWorldRectT(const WWorldPointT<T>& bottomLeft, const WWorldSizeT<T>& size);
	WWorldRectT(const WWorldPointT<T>& bottomLeft, const WWorldPointT<T>& topRight);
	WWorldRectT(T x, T y, T width, T height);

	inline void setRect(T x, T y, T width, T height);

	inline bool isEmpty() const;

	inline T top() const;
	inline T left() const;
	inline T bottom() const;
	inline T right() const;

	inline T x() const;
	inline T y() const;
	inline T width() const;
	inline T height() const;

	inline WWorldPointT<T> topLeft() const;
	inline WWorldPointT<T> topRight() const;
	inline WWorldPointT<T> bottomLeft() const;
	inline WWorldPointT<T> bottomRight() const;

	/**
	\brief      center
	\Access    public 
	\retval     WWorldPointT<T>
	\remark    ���ؾ��ε����ĵ����� 
	*/
	inline WWorldPointT<T> center() const;

	/**
	\brief      adjust
	\Access    public 
	\param  T dx1
	\param  T dy1
	\param  T dx2
	\param  T dy2
	\retval     void
	\remark    ΢�����δ�С�������ǰ��������Ϊ(x1, y1, x2, y2)��
					��ô������Ϊ(x1 + dx1, y1 + dy1, x2 + dx2, y2 + dy2)
	*/
	inline void adjust(T dx1, T dy1, T dx2, T dy2);
	
	/**
	\brief      adjusted
	\Access    public 
	\param  T dx1
	\param  T dy1
	\param  T dx2
	\param  T dy2
	\retval     WWorldRectT<T>
	\remark    ���������䣬 ����һ�����Σ�Ȼ��ͬ�ϵ��������ص�����ľ���
	*/
	inline WWorldRectT<T> adjusted(T dx1, T dy1, T dx2, T dy2) const;

	/**
	\brief      contains
	\Access    public 
	\param  const WWorldPointT<T> & p
	\retval     bool
	\remark    �ж�ĳһ���Ƿ��ھ��������ڣ�����Ƿ���true����֮false 
	*/
	inline bool contains(const WWorldPointT<T>& p) const;

	/**
	\brief      contains
	\Access    public 
	\param  T x
	\param  T y
	\retval     bool
	\remark    ͬ�� 
	*/
	inline bool contains(T x, T y) const;

	/**
	\brief      contains
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     bool
	\remark    �ж���һ������r�Ƿ�������ľ��η�Χ�ڣ�����Ƿ���true����֮false 
	*/
	inline bool contains(const WWorldRectT<T>& r) const;

	/**
	\brief      intersects
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     bool
	\remark    �ж���һ������r�Ƿ������ľ��η�Χ�н��棬����Ƿ���true����֮false 
	*/
	inline bool intersects(const WWorldRectT<T>& r) const;

	/**
	\brief      normalized
	\Access    public 
	\retval     WWorldRectT<T>
	\remark    ���������滯�����������滯����Σ�ԭ���β���
					���滯���������Ǿ��ε�width��height���Ϸ�(Ϊ����)����
	*/
	inline WWorldRectT<T> normalized() const;

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointT<T> & p
	\retval     void
	\remark    ������ƽ�����ɵ�λ 
	*/
	inline void translate(const WWorldPointT<T>& p);

	/**
	\brief      translated
	\Access    public 
	\param  const WWorldPointT<T> & p
	\retval     WWorldRectT<T>
	\remark    ����ƽ�ƺ�ľ��Σ����������ı䣩 
	*/
	inline WWorldRectT<T> translated(const WWorldPointT<T>& p) const;

	/**
	\brief      operator|
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     WWorldRectT<T>
	\remark    ���ؾ��β������Ľ�������������ı䣩 
	*/
	inline WWorldRectT<T> operator|(const WWorldRectT<T>& r) const;

	/**
	\brief      operator|=
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     WWorldRectT<T>&
	\remark    ���ؾ��β������Ľ�����������ı䣩 
	*/
	inline WWorldRectT<T>& operator|=(const WWorldRectT<T>& r);

	/**
	\brief      operator&
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     WWorldRectT<T>
	\remark    ���ؾ��ν������Ľ�������������ı䣩 
	*/
	inline WWorldRectT<T> operator&(const WWorldRectT<T>& r) const;

	/**
	\brief      operator&=
	\Access    public 
	\param  const WWorldRectT<T> & r
	\retval     WWorldRectT<T>&
	\remark    ���ؾ��ν������Ľ�����������ı䣩 
	*/
	inline WWorldRectT<T>& operator&=(const WWorldRectT<T>& r);
	/*
	QRectF	intersected ( const QRectF & rectangle ) const
	bool	intersects ( const QRectF & rectangle ) const
	bool	isEmpty () const
	bool	isNull () const
	bool	isValid () const

	void	moveBottom ( qreal y )
	void	moveBottomLeft ( const QPointF & position )
	void	moveBottomRight ( const QPointF & position )
	void	moveCenter ( const QPointF & position )
	void	moveLeft ( qreal x )
	void	moveRight ( qreal x )
	void	moveTo ( qreal x, qreal y )
	void	moveTo ( const QPointF & position )
	void	moveTop ( qreal y )
	void	moveTopLeft ( const QPointF & position )
	void	moveTopRight ( const QPointF & position )
	QRectF	normalized () const

	void	setBottom ( qreal y )
	void	setBottomLeft ( const QPointF & position )
	void	setBottomRight ( const QPointF & position )
	void	setCoords ( qreal x1, qreal y1, qreal x2, qreal y2 )
	void	setHeight ( qreal height )
	void	setLeft ( qreal x )
	void	setRect ( qreal x, qreal y, qreal width, qreal height )
	void	setRight ( qreal x )
	void	setSize ( const QSizeF & size )
	void	setTop ( qreal y )
	void	setTopLeft ( const QPointF & position )
	void	setTopRight ( const QPointF & position )
	void	setWidth ( qreal width )
	void	setX ( qreal x )
	void	setY ( qreal y )
	QSizeF	size () const

	QRectF	united ( const QRectF & rectangle ) const
	*/

private:
	T _x;
	T _y;
	T _w;
	T _h;
};

template<class T>
WWorldRectT<T>::WWorldRectT() : _x(T()), _y(T()), _w(T()), _h(T())
{
}

template<class T>
WWorldRectT<T>::WWorldRectT(const WWorldPointT<T>& bottomLeft, const WWorldSizeT<T>& size)
: _x(bottomLeft.x()), _y(bottomLeft.y()), _w(size.width()), _h(size.height())
{
}

template<class T>
WWorldRectT<T>::WWorldRectT(const WWorldPointT<T>& bottomLeft, const WWorldPointT<T>& topRight) : _x(bottomLeft.x()), _y(bottomLeft.y()),
_w(topRight.x() - bottomLeft.x()), _h(topRight.y() - bottomLeft.y())
{
}

template<class T>
WWorldRectT<T>::WWorldRectT(T x, T y, T width, T height)
: _x(x), _y(y), _w(width), _h(height)
{
}

template<class T>
inline void WWorldRectT<T>::setRect(T x, T y, T width, T height)
{
	_x = x;
	_y = y;
	_w = width;
	_h = height;
}

template<class T>
inline bool WWorldRectT<T>::isEmpty() const
{
	return numeric_equal(_w, T()) || numeric_equal(_h, T());
}

template<class T>
inline void WWorldRectT<T>::adjust(T dx1, T dy1, T dx2, T dy2)
{
	_x += dx1;
	_y += dy1;
	_w += dx2 - dx1;
	_h += dy2 - dy1;
}

template<class T>
inline WWorldRectT<T> WWorldRectT<T>::adjusted(T dx1, T dy1, T dx2, T dy2) const
{
	return WWorldRectT<T>(_x+dx1, _y+dy1, _w+dx2-dx1, _h+dy2-dy1);
}

template<class T>
inline T WWorldRectT<T>::top() const
{
	return _y + _h;
}

template<class T>
inline T WWorldRectT<T>::left() const
{
	return _x;
}

template<class T>
inline T WWorldRectT<T>::bottom() const
{
	return _y;
}

template<class T>
inline T WWorldRectT<T>::right() const
{
	return _x + _w;
}

template<class T>
inline T WWorldRectT<T>::x() const
{
	return _x;
}

template<class T>
inline T WWorldRectT<T>::y() const
{
	return _y;
}

template<class T>
inline T WWorldRectT<T>::width() const
{
	return _w;
}

template<class T>
inline T WWorldRectT<T>::height() const
{
	return _h;
}

template<class T>
inline WWorldPointT<T> WWorldRectT<T>::topLeft() const
{
	return WWorldPointT<T>(_x, _y + _h);
}

template<class T>
inline WWorldPointT<T> WWorldRectT<T>::topRight() const
{
	return WWorldPointT<T>(_x + _w, _y + _h);
}

template<class T>
WWorldPointT<T> WWorldRectT<T>::bottomLeft() const
{
	return WWorldPointT<T>(_x, _y);
}

template<class T>
inline WWorldPointT<T> WWorldRectT<T>::bottomRight() const
{
	return WWorldPointT<T>(_x + _w, _y);
}

template<class T>
inline WWorldPointT<T> WWorldRectT<T>::center() const
{
	return WWorldPointT<T>(_x + _w / 2, _y + _h / 2);
}

template<class T>
inline bool WWorldRectT<T>::contains(const WWorldPointT<T>& p) const
{
	return contains(p.x(), p.y());
}

template<class T>
inline bool WWorldRectT<T>::contains(T x, T y) const
{
	WWorldRectT<T> r = normalized();
	return r._x<=x && x<=r._x+r._w && r._y<=y && y<=r._y+_h;
}

template<class T>
inline bool WWorldRectT<T>::contains(const WWorldRectT<T>& r) const
{
	WWorldRectT<T> r1 = normalized();
	WWorldRectT<T> r2 = r.normalized();

	return r1._x <= r2._x && r2._x+r2._w <= r1._x+r1._w
		&& r1._y <= r2._y && r2._y+r2._h <= r1._y+r1._h;
}

template<class T>
bool WWorldRectT<T>::intersects(const WWorldRectT<T>& r) const
{
	WWorldRectT<T> r1 = normalized();
	WWorldRectT<T> r2 = r.normalized();

	double left = wMax(r1.left(), r2.left());
	double right = wMin(r1.right(), r2.right());
	double bottom = wMax(r1.bottom(), r2.bottom());
	double top = wMin(r1.top(), r2.top());

	return left < right && bottom < top;
}

template<class T>
inline WWorldRectT<T> WWorldRectT<T>::normalized() const
{
	WWorldRectT<T> r(*this);

	if (_w < 0)
	{
		r._x += _w;
		r._w = -_w;
	}

	if (_h < 0)
	{
		r._y += _h;
		r._h = -_h;
	}

	return r;
}

template<class T>
inline void WWorldRectT<T>::translate(const WWorldPointT<T>& p)
{
	_x += p.x();
	_y += p.y();
}

template<class T>
inline WWorldRectT<T> WWorldRectT<T>::translated(const WWorldPointT<T>& p) const
{
	WWorldRectT<T> rect(*this);
	rect.translate(p);
	return rect;
}

template<class T>
inline bool operator==(const WWorldRectT<T>& lhs, const WWorldRectT<T>& rhs)
{
	return numeric_equal(lhs.left(), rhs.left()) 
		&& numeric_equal(lhs.bottom(), rhs.bottom())
		&& numeric_equal(lhs.width(), rhs.width())
		&& numeric_equal(lhs.height(), rhs.height());
}

template<class T>
inline bool operator!=(const WWorldRectT<T>& lhs, const WWorldRectT<T>& rhs)
{
	return !(lhs == rhs);
}

template<class T>
WWorldRectT<T> WWorldRectT<T>::operator|(const WWorldRectT<T>& r) const
{
	WWorldRectT<T> r1 = normalized();
	WWorldRectT<T> r2 = r.normalized();

	double left = wMin(r1.left(), r2.left());
	double right = wMax(r1.right(), r2.right());
	double bottom = wMin(r1.bottom(), r2.bottom());
	double top = wMax(r1.top(), r2.top());
	
	return WWorldRectT<T>(left, bottom, right - left, top - bottom);
}

template<class T>
inline WWorldRectT<T>& WWorldRectT<T>::operator|=(const WWorldRectT<T>& r)
{
	return *this = *this | r;
}

template<class T>
WWorldRectT<T> WWorldRectT<T>::operator&(const WWorldRectT<T>& r) const
{
	WWorldRectT<T> r1 = normalized();
	WWorldRectT<T> r2 = r.normalized();

	double left = wMax(r1.left(), r2.left());
	double right = wMin(r1.right(), r2.right());
	double bottom = wMax(r1.bottom(), r2.bottom());
	double top = wMin(r1.top(), r2.top());

	return (left < right && bottom < top) ? WWorldRectT<T>(left, bottom, right - left, top - bottom) : WWorldRectT<T>();
}

template<class T>
inline WWorldRectT<T>& WWorldRectT<T>::operator&=(const WWorldRectT<T>& r)
{
	return *this = *this & r;
}

typedef WWorldRectT<int> WWorldRect;
typedef WWorldRectT<double> WWorldRectF;
typedef WWorldRectF WRectF;
typedef WWorldRect WRect;

#endif