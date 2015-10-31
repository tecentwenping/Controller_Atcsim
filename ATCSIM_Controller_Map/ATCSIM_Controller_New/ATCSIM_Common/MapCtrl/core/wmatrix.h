/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wmatrix.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WMatrix��
  ����  ����:   
******************************************************************************/
#ifndef _WMATRIX_H_
#define _WMATRIX_H_

#include "../wdllimport.h"
#include "wglobal.h"
#include "wworldline.h"
#include "wworldrect.h"
#include "wworldpolygon.h"

/** 
 \brief                 ����任��
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WMatrix // 2D transform matrix
{
public:
	/**
	\brief      WMatrix
	\Access    public 
	\retval     
	\remark     Ĭ���ǵ�λ����
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
	\remark     ���þ���ĳ�ֵ
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
	\remark     �������þ���ĳ�ֵ
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
	\remark     ����(x, y)ӳ�䵽��(*tx, *ty)
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
	\remark     ͬ��
	*/
	void map(double x, double y, double* tx, double* ty) const;

	/**
	\brief      mapRect
	\Access    public 
	\param  const WWorldRect & rect
	\retval     WWorldRect
	\remark    ӳ����� 
	*/
	WWorldRect mapRect(const WWorldRect& rect) const;

	/**
	\brief      mapRect
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     WWorldRectF
	\remark     ͬ��
	*/
	WWorldRectF mapRect(const WWorldRectF& rect) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPoint & p
	\retval     WWorldPoint
	\remark     ӳ���
	*/
	WWorldPoint map(const WWorldPoint& p) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     ͬ��
	*/
	WWorldPointF map(const WWorldPointF& p) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldLine & l
	\retval     WWorldLine
	\remark     ӳ��ֱ��
	*/
	WWorldLine map(const WWorldLine& l) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldLineF & l
	\retval     WWorldLineF
	\remark     ͬ��
	*/
	WWorldLineF map(const WWorldLineF& l) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPolygonF & a
	\retval     WWorldPolygonF
	\remark     ӳ������
	*/
	WWorldPolygonF map(const WWorldPolygonF& a) const;

	/**
	\brief      map
	\Access    public 
	\param  const WWorldPolygon & a
	\retval     WWorldPolygon
	\remark     ͬ��
	*/
	WWorldPolygon map(const WWorldPolygon& a) const;

	/**
	\brief      mapToPolygon
	\Access    public 
	\param  const WWorldRect & r
	\retval     WWorldPolygon
	\remark     ������ӳ��ɶ����
	*/
	WWorldPolygon mapToPolygon(const WWorldRect& r) const;

	/**
	\brief      reset
	\Access    public 
	\retval     void
	\remark     ����������
	*/
	void reset();

	/**
	\brief      isIdentity
	\Access    public 
	\retval     bool
	\remark     �Ƿ��ǵ�λ����
	*/
	bool isIdentity() const;

	/**
	\brief      translate
	\Access    public 
	\param  double dx
	\param  double dy
	\retval     WMatrix&
	\remark     ����ƫ�Ʋ���
	*/
	WMatrix& translate(double dx, double dy);

	/**
	\brief      translate
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WMatrix&
	\remark     ͬ��
	*/
	WMatrix& translate(const WWorldPointF& p);

	/**
	\brief      scale
	\Access    public 
	\param  double sx
	\param  double sy
	\retval     WMatrix&
	\remark     �����������
	*/
	WMatrix& scale(double sx, double sy);

	/**
	\brief      shear
	\Access    public 
	\param  double sh
	\param  double sv
	\retval     WMatrix&
	\remark     ����б�в���
	*/
	WMatrix& shear(double sh, double sv);

	/**
	\brief      rotate
	\Access    public 
	\param  double a
	\retval     WMatrix&
	\remark     ������ת
	*/
	WMatrix& rotate(double a);

	/**
	\brief      isInvertible
	\Access    public 
	\retval     bool
	\remark     �����Ƿ����
	*/
	bool isInvertible() const;

	/**
	\brief      determinant
	\Access    public 
	\retval     double
	\remark     �����Ӧ������ʽ��ֵ
	*/
	double determinant() const;

	/**
	\brief      inverted
	\Access    public 
	\param  bool * invertible
	\retval     WMatrix
	\remark     ����������������󲻿��棬�򷵻ص�λ����invertible�������Ϊ0�����ؾ����Ƿ����
	*/
	WMatrix inverted(bool* invertible = 0) const;

	/**
	\brief      fuzzyCompare
	\Access    public 
	\param  const WMatrix & other
	\retval     bool
	\remark     �����Ƿ����
	*/
	bool fuzzyCompare(const WMatrix& other) const;

	//�����Ǿ����һЩ�������
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
