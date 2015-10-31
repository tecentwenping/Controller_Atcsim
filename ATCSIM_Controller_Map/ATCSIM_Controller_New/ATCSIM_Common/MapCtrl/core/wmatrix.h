/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wmatrix.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WMatrix类
  【其  它】:   
******************************************************************************/
#ifndef _WMATRIX_H_
#define _WMATRIX_H_

#include "../wdllimport.h"
#include "wglobal.h"
#include "wworldline.h"
#include "wworldrect.h"
#include "wworldpolygon.h"

/** 
 \brief                 矩阵变换类
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WMatrix // 2D transform matrix
{
public:
	/**
	\brief      WMatrix
	\Access    public 
	\retval     
	\remark     默认是单位矩阵
	*/
	WMatrix();

	/**
	\brief      WMatrix
	\Access    public 
	\param  double m11
	\param  double m12
	\param  double m21
	\param  double m22
	\param  double dx
	\param  double dy
	\retval     
	\remark     设置矩阵的初值
	*/
	WMatrix(double m11, double m12, double m21, double m22, double dx, double dy);

	WMatrix(const WMatrix& matrix);

	/**
	\brief      setMatrix
	\Access    public 
	\param  double m11
	\param  double m12
	\param  double m21
	\param  double m22
	\param  double dx
	\param  double dy
	\retval     void
	\remark     重新设置矩阵的初值
	*/
	void setMatrix(double m11, double m12, double m21, double m22, double dx, double dy);

	double m11() const;
	double m12() const;
	double m21() const;
	double m22() const;
	double dx() const;
	double dy() const;

	/**
	\brief      map
	\Access    public 
	\param  int x
	\param  int y
	\param  int * tx
	\param  int * ty
	\retval     void
	\remark     将点(x, y)映射到点(*tx, *ty)
	*/
	void map(int x, int y, int* tx, int* ty) const;

	/**
	\brief      map
	\Access    public 
	\param  double x
	\param  double y
	\param  double * tx
	\param  double * ty
	\retval     void
	\remark     同上
	*/
	void map(double x, double y, double* tx, double* ty) const;

	/**
	\brief      mapRect
	\Access    public 
	\param  const WWorldRect & rect
	\retval     WWorldRect
	\remark    映射矩形 
	*/
	WWorldRect mapRect(const WWorldRect& rect) const;

	/**
	\brief      mapRect
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     WWorldRectF
	\remark     同上
	*/
	WWorldRectF mapRect(const WWorldRectF& rect) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPoint & p
	\retval     WWorldPoint
	\remark     映射点
	*/
	WWorldPoint map(const WWorldPoint& p) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     同上
	*/
	WWorldPointF map(const WWorldPointF& p) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldLine & l
	\retval     WWorldLine
	\remark     映射直线
	*/
	WWorldLine map(const WWorldLine& l) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldLineF & l
	\retval     WWorldLineF
	\remark     同上
	*/
	WWorldLineF map(const WWorldLineF& l) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPolygonF & a
	\retval     WWorldPolygonF
	\remark     映射多边形
	*/
	WWorldPolygonF map(const WWorldPolygonF& a) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPolygon & a
	\retval     WWorldPolygon
	\remark     同上
	*/
	WWorldPolygon map(const WWorldPolygon& a) const;

	/**
	\brief      mapToPolygon
	\Access    public 
	\param  const WWorldRect & r
	\retval     WWorldPolygon
	\remark     将矩形映射成多边形
	*/
	WWorldPolygon mapToPolygon(const WWorldRect& r) const;

	/**
	\brief      reset
	\Access    public 
	\retval     void
	\remark     将矩阵重置
	*/
	void reset();

	/**
	\brief      isIdentity
	\Access    public 
	\retval     bool
	\remark     是否是单位矩阵
	*/
	bool isIdentity() const;

	/**
	\brief      translate
	\Access    public 
	\param  double dx
	\param  double dy
	\retval     WMatrix&
	\remark     矩阵偏移操作
	*/
	WMatrix& translate(double dx, double dy);

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WMatrix&
	\remark     同上
	*/
	WMatrix& translate(const WWorldPointF& p);

	/**
	\brief      scale
	\Access    public 
	\param  double sx
	\param  double sy
	\retval     WMatrix&
	\remark     矩阵放缩操作
	*/
	WMatrix& scale(double sx, double sy);

	/**
	\brief      shear
	\Access    public 
	\param  double sh
	\param  double sv
	\retval     WMatrix&
	\remark     矩阵斜切操作
	*/
	WMatrix& shear(double sh, double sv);

	/**
	\brief      rotate
	\Access    public 
	\param  double a
	\retval     WMatrix&
	\remark     矩阵旋转
	*/
	WMatrix& rotate(double a);

	/**
	\brief      isInvertible
	\Access    public 
	\retval     bool
	\remark     矩阵是否可逆
	*/
	bool isInvertible() const;

	/**
	\brief      determinant
	\Access    public 
	\retval     double
	\remark     矩阵对应的行列式的值
	*/
	double determinant() const;

	/**
	\brief      inverted
	\Access    public 
	\param  bool * invertible
	\retval     WMatrix
	\remark     矩阵的逆矩阵，如果矩阵不可逆，则返回单位矩阵，invertible（如果不为0）返回矩阵是否可逆
	*/
	WMatrix inverted(bool* invertible = 0) const;

	/**
	\brief      fuzzyCompare
	\Access    public 
	\param  const WMatrix & other
	\retval     bool
	\remark     矩阵是否相等
	*/
	bool fuzzyCompare(const WMatrix& other) const;

	//以下是矩阵的一些算符重载
	bool operator==(const WMatrix& rhs) const;
	bool operator!=(const WMatrix& rhs) const;

	WMatrix& operator*=(const WMatrix& rhs);
	WMatrix operator*(const WMatrix& rhs) const;

	WMatrix& operator=(const WMatrix& rhs);

private:
	/*
	|m11, m12, m13|
	|m21, m22, m23|
	|dx,    dy,    m33|
	*/
	double _m11, _m12;
	double _m21, _m22;
	double _dx, _dy;
};

// mathematical semantics
WWorldPoint operator*(const WWorldPoint& p, const WMatrix& m);
WWorldPointF operator*(const WWorldPointF& p, const WMatrix& m);
WWorldLineF operator*(const WWorldLineF& l, const WMatrix& m);
WWorldLine operator*(const WWorldLine& l, const WMatrix& m);
WWorldPolygon operator*(const WWorldPolygon& a, const WMatrix& m);
WWorldPolygonF operator*(const WWorldPolygonF& a, const WMatrix& m);

#endif
