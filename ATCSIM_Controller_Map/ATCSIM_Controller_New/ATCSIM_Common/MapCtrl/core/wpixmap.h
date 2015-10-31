/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wpixmap.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WPixmap类
  【其  它】:   
******************************************************************************/
#ifndef _WPIXMAP_H_
#define _WPIXMAP_H_

#include <QtGui/QPixmap>
#include "../wdllimport.h"
#include "wenums.h"
#include "wmatrix.h"
/** 
 \brief                 此类主要完成图片的概念抽象
\details   
 \author    陈龙 & @zcw
\date      2013/05/22
*/
class MAPAPI WPixmap : public QPixmap
{
public:
	WPixmap();
	WPixmap(int width, int height);
	WPixmap(const std::string& filename, const char* format = 0);
	WPixmap(const QPixmap& pixmap);
	WPixmap(const WPixmap& pixmap);

	WPixmap& operator=(const WPixmap& pixmap);

	/**
	\brief      xcopy
	\Access    public 
	\param  int x
	\param  int y 
	\param  int width 
	\param  int height
	\retval     WPixmap
	\remark    主要完成图片的复制操作，从原图片的(x, y)点开始复制，复制width，height大小 
	*/
	WPixmap xcopy(int x, int y, int width, int height) const;


	/**
	\brief      xtransformed
	\Access    public 
	\param  const WMatrix & matrix
	\param  Ws::TransformationMode mode
	\retval     WPixmap
	\remark    包装QPixmap方法 
	*/
	WPixmap xtransformed(const WMatrix& matrix, Ws::TransformationMode mode = Ws::FastTransformation) const;

	/**
	\brief      xrotated
	\Access    public 
	\param  double angle
	\retval     WPixmap
	\remark     对图片进行旋转
	*/
	WPixmap xrotated(double angle, Ws::TransformationMode mode = Ws::FastTransformation) const;


	/**
	\brief      xscaled
	\Access    public 
	\param  int width
	\param  int height
	\param  Ws::AspectRatioMode aspectRatioMode
	\param  Ws::TransformationMode transformationMode
	\retval     WPixmap
	\remark     
	*/
	WPixmap xscaled(int width, int height, Ws::AspectRatioMode aspectRatioMode = Ws::IgnoreAspectRatio, Ws::TransformationMode transformationMode = Ws::FastTransformation) const;
};

#endif