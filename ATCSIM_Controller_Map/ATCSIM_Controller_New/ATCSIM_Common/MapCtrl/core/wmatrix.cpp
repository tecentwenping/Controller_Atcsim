#include <cmath>
#include "../wdllexport.h"
#include "wmatrix.h"

#define MAPDOUBLE(x, y, nx, ny)\
{\
	double fx = x;\
	double fy = y;\
	nx = _m11*fx + _m21*fy + _dx;\
	ny = _m12*fx + _m22*fy + _dy;\
}\
\

#define MAPINT(x, y, nx, ny)\
{\
	double fx = x;\
	double fy = y;\
	nx = wRound(_m11*fx + _m21*fy + _dx);\
	ny = wRound(_m12*fx + _m22*fy + _dy);\
}\
\

WMatrix::WMatrix()
: _m11(1.)
, _m12(0.)
, _m21(0.)
, _m22(1.)
, _dx(0.)
, _dy(0.)
{
}

WMatrix::WMatrix(double m11, double m12, double m21, double m22, double dx, double dy)
: _m11(m11)
, _m12(m12)
, _m21(m21)
, _m22(m22)
, _dx(dx)
, _dy(dy)
{
}

WMatrix::WMatrix(const WMatrix& matrix)
: _m11(matrix._m11)
, _m12(matrix._m12)
, _m21(matrix._m21)
, _m22(matrix._m22)
, _dx(matrix._dx)
, _dy(matrix._dy)
{
}

void WMatrix::setMatrix(double m11, double m12, double m21, double m22, double dx, double dy)
{
	_m11 = m11;
	_m12 = m12;
	_m21 = m21;
	_m22 = m22;
	_dx  = dx;
	_dy  = dy;
}

void WMatrix::map(double x, double y, double *tx, double* ty) const
{
	MAPDOUBLE(x, y, *tx, *ty);
}

void WMatrix::map(int x, int y, int* tx, int* ty) const
{
	MAPINT(x, y, *tx, *ty);
}

WWorldRect WMatrix::mapRect(const WWorldRect& rect) const
{
	WWorldRect result;
	if (_m12 == 0.0F && _m21 == 0.0F) 
	{
		int x = wRound(_m11*rect.x() + _dx);
		int y = wRound(_m22*rect.y() + _dy);
		int w = wRound(_m11*rect.width());
		int h = wRound(_m22*rect.height());
		result = WWorldRect(x, y, w, h).normalized();
	} 
	else 
	{
		double x0, y0;
		double x, y;
		MAPDOUBLE(rect.left(), rect.top(), x0, y0);
		double xmin = x0;
		double ymin = y0;
		double xmax = x0;
		double ymax = y0;
		MAPDOUBLE(rect.right() + 1, rect.top(), x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		MAPDOUBLE(rect.right() + 1, rect.bottom() + 1, x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		MAPDOUBLE(rect.left(), rect.bottom() + 1, x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		result = WWorldRect(wRound(xmin), wRound(ymin), wRound(xmax)-wRound(xmin), wRound(ymax)-wRound(ymin));
	}
	return result;
}

WWorldRectF WMatrix::mapRect(const WWorldRectF& rect) const
{
	WWorldRectF result;
	if (_m12 == 0.0F && _m21 == 0.0F) 
	{
		double x = _m11*rect.x() + _dx;
		double y = _m22*rect.y() + _dy;
		double w = _m11*rect.width();
		double h = _m22*rect.height();
		result = WWorldRectF(x, y, w, h).normalized();
	} 
	else 
	{
		double x0, y0;
		double x, y;
		MAPDOUBLE(rect.x(), rect.y(), x0, y0);
		double xmin = x0;
		double ymin = y0;
		double xmax = x0;
		double ymax = y0;
		MAPDOUBLE(rect.x() + rect.width(), rect.y(), x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		MAPDOUBLE(rect.x() + rect.width(), rect.y() + rect.height(), x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		MAPDOUBLE(rect.x(), rect.y() + rect.height(), x, y);
		xmin = wMin(xmin, x);
		ymin = wMin(ymin, y);
		xmax = wMax(xmax, x);
		ymax = wMax(ymax, y);
		result = WWorldRectF(xmin, ymin, xmax-xmin, ymax - ymin);
	}
	return result;
}

WWorldPoint WMatrix::map(const WWorldPoint& p) const
{
	double fx = p.x();
	double fy = p.y();
	return WWorldPoint(wRound(_m11*fx + _m21*fy + _dx), wRound(_m12*fx + _m22*fy + _dy));
}

WWorldPointF WMatrix::map(const WWorldPointF& point) const
{
	double fx = point.x();
	double fy = point.y();
	return WWorldPointF(_m11*fx + _m21*fy + _dx, _m12*fx + _m22*fy + _dy);
}

WWorldLineF WMatrix::map(const WWorldLineF& line) const
{
	return WWorldLineF(map(line.p1()), map(line.p2()));
}

WWorldLine WMatrix::map(const WWorldLine& line) const
{
	return WWorldLine(map(line.p1()), map(line.p2()));
}

WWorldPolygon WMatrix::map(const WWorldPolygon& a) const
{
	int size = a.size();
	int i;
	WWorldPolygon p(size);
	const WWorldPoint* da = &a[0];
	WWorldPoint* dp = &p[0];
	for(i = 0; i < size; ++i) 
	{
		MAPINT(da[i].x(), da[i].y(), dp[i].rx(), dp[i].ry());
	}
	return p;
}

WWorldPolygonF WMatrix::map(const WWorldPolygonF& a) const
{
	int size = a.size();
	int i;
	WWorldPolygonF p(size);
	const WWorldPointF* da = &a[0];
	WWorldPointF* dp = &p[0];
	for(i = 0; i < size; ++i)
	{
		MAPDOUBLE(da[i].x(), da[i].y(), dp[i].rx(), dp[i].ry());
	}
	return p;
}

WWorldPolygon WMatrix::mapToPolygon(const WWorldRect& rect) const
{
	WWorldPolygon a(4);
	double x[4], y[4];
	if (_m12 == 0.0F && _m21 == 0.0F) 
	{
		x[0] = _m11*rect.x() + _dx;
		y[0] = _m22*rect.y() + _dy;
		double w = _m11*rect.width();
		double h = _m22*rect.height();
		if (w < 0) 
		{
			w = -w;
			x[0] -= w;
		}
		if (h < 0) 
		{
			h = -h;
			y[0] -= h;
		}
		x[1] = x[0]+w;
		x[2] = x[1];
		x[3] = x[0];
		y[1] = y[0];
		y[2] = y[0]+h;
		y[3] = y[2];
	} 
	else 
	{
		double right = rect.x() + rect.width();
		double bottom = rect.y() + rect.height();
		MAPDOUBLE(rect.x(), rect.y(), x[0], y[0]);
		MAPDOUBLE(right, rect.y(), x[1], y[1]);
		MAPDOUBLE(right, bottom, x[2], y[2]);
		MAPDOUBLE(rect.x(), bottom, x[3], y[3]);
	}

	for (int i=0; i<4; ++i)
	{
		a[i].setX(wRound(x[i]));
		a[i].setY(wRound(y[i]));
	}
	
	return a;
}

void WMatrix::reset()
{
	_m11 = _m22 = 1.0;
	_m12 = _m21 = _dx = _dy = 0.0;
}

WMatrix& WMatrix::translate(double dx, double dy)
{
	_dx += dx*_m11 + dy*_m21;
	_dy += dy*_m22 + dx*_m12;
	return *this;
}

WMatrix& WMatrix::translate(const WWorldPointF& p)
{
	return translate(p.x(), p.y());
}

WMatrix& WMatrix::scale(double sx, double sy)
{
	_m11 *= sx;
	_m12 *= sx;
	_m21 *= sy;
	_m22 *= sy;
	return *this;
}

WMatrix& WMatrix::shear(double sh, double sv)
{
	double tm11 = sv*_m21;
	double tm12 = sv*_m22;
	double tm21 = sh*_m11;
	double tm22 = sh*_m12;
	_m11 += tm11;
	_m12 += tm12;
	_m21 += tm21;
	_m22 += tm22;
	return *this;
}

const double deg2rad = double(0.017453292519943295769);        // pi/180

WMatrix& WMatrix::rotate(double a)
{
	double sina = 0;
	double cosa = 0;
	if (a == 90. || a == -270.)
		sina = 1.;
	else if (a == 270. || a == -90.)
		sina = -1.;
	else if (a == 180.)
		cosa = -1.;
	else
	{
		double b = deg2rad*a;                        // convert to radians
		sina = sin(b);
		cosa = cos(b);
	}
	double tm11 = cosa*_m11 + sina*_m21;
	double tm12 = cosa*_m12 + sina*_m22;
	double tm21 = -sina*_m11 + cosa*_m21;
	double tm22 = -sina*_m12 + cosa*_m22;
	_m11 = tm11; _m12 = tm12;
	_m21 = tm21; _m22 = tm22;
	return *this;
}

WMatrix WMatrix::inverted(bool* invertible) const
{
	double dtr = determinant();
	if (dtr == 0.0) 
	{
		if (invertible)
			*invertible = false;                // singular matrix
		return WMatrix();
	}
	else 
	{                                        // invertible matrix
		if (invertible)
			*invertible = true;
		double dinv = 1.0/dtr;
		return WMatrix((_m22*dinv),  (-_m12*dinv), (-_m21*dinv), (_m11*dinv), ((_m21*_dy - _m22*_dx)*dinv), ((_m12*_dx - _m11*_dy)*dinv));
	}
}

bool WMatrix::operator==(const WMatrix& m) const
{
	return fuzzyCompare(m);
}

bool WMatrix::operator!=(const WMatrix& m) const
{
	return !(*this == m);
}

WMatrix& WMatrix::operator*=(const WMatrix& m)
{
	double tm11 = _m11*m._m11 + _m12*m._m21;
	double tm12 = _m11*m._m12 + _m12*m._m22;
	double tm21 = _m21*m._m11 + _m22*m._m21;
	double tm22 = _m21*m._m12 + _m22*m._m22;

	double tdx  = _dx*m._m11  + _dy*m._m21 + m._dx;
	double tdy =  _dx*m._m12  + _dy*m._m22 + m._dy;

	_m11 = tm11; _m12 = tm12;
	_m21 = tm21; _m22 = tm22;
	_dx = tdx; _dy = tdy;
	return *this;
}

WMatrix WMatrix::operator*(const WMatrix& m) const
{
	double tm11 = _m11*m._m11 + _m12*m._m21;
	double tm12 = _m11*m._m12 + _m12*m._m22;
	double tm21 = _m21*m._m11 + _m22*m._m21;
	double tm22 = _m21*m._m12 + _m22*m._m22;

	double tdx  = _dx*m._m11  + _dy*m._m21 + m._dx;
	double tdy =  _dx*m._m12  + _dy*m._m22 + m._dy;
	return WMatrix(tm11, tm12, tm21, tm22, tdx, tdy);
}

WMatrix &WMatrix::operator=(const WMatrix &matrix)
{
	_m11 = matrix._m11;
	_m12 = matrix._m12;
	_m21 = matrix._m21;
	_m22 = matrix._m22;
	_dx  = matrix._dx;
	_dy  = matrix._dy;
	return *this;
}

bool WMatrix::isInvertible() const 
{ 
	return wFuzzyCompare(determinant(), 0.0); 
}

double WMatrix::determinant() const 
{ 
	return _m11*_m22 - _m12*_m21; 
}

bool WMatrix::fuzzyCompare(const WMatrix& other) const
{
	return wFuzzyCompare(_m11, other._m11)
		&& wFuzzyCompare(_m12, other._m12)
		&& wFuzzyCompare(_m21, other._m21)
		&& wFuzzyCompare(_m22, other._m22)
		&& wFuzzyCompare(_dx, other._dx)
		&& wFuzzyCompare(_dy, other._dy);
}

WWorldPoint operator*(const WWorldPoint& p, const WMatrix& m)
{ 
	return m.map(p); 
}

WWorldPointF operator*(const WWorldPointF& p, const WMatrix& m)
{ 
	return m.map(p); 
}

WWorldLineF operator*(const WWorldLineF& l, const WMatrix& m)
{ 
	return m.map(l); 
}

WWorldLine operator*(const WWorldLine& l, const WMatrix& m)
{ 
	return m.map(l); 
}

WWorldPolygon operator*(const WWorldPolygon& a, const WMatrix& m)
{ 
	return m.map(a);
}

WWorldPolygonF operator *(const WWorldPolygonF &a, const WMatrix &m)
{ 
	return m.map(a); 
}

bool WMatrix::isIdentity() const
{
	return wFuzzyCompare(_m11, 1.0)
		&& wFuzzyCompare(_m22, 1.0)
		&& wFuzzyCompare(_m12, 0.0)
		&& wFuzzyCompare(_m21, 0.0)
		&& wFuzzyCompare(_dx, 0.0)
		&& wFuzzyCompare(_dy, 0.0);
}

bool wFuzzyCompare(const WMatrix& m1, const WMatrix& m2)
{
	return wFuzzyCompare(m1.m11(), m2.m11())
		&& wFuzzyCompare(m1.m12(), m2.m12())
		&& wFuzzyCompare(m1.m21(), m2.m21())
		&& wFuzzyCompare(m1.m22(), m2.m22())
		&& wFuzzyCompare(m1.dx(), m2.dx())
		&& wFuzzyCompare(m1.dy(), m2.dy());
}

double WMatrix::m11() const 
{ 
	return _m11; 
}

double WMatrix::m12() const 
{ 
	return _m12; 
}

double WMatrix::m21() const
{
	return _m21; 
}

double WMatrix::m22() const 
{ 
	return _m22; 
}

double WMatrix::dx() const 
{
	return _dx; 
}

double WMatrix::dy() const 
{
	return _dy; 
}