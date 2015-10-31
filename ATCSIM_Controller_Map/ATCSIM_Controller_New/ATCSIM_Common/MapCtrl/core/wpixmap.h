/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wpixmap.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WPixmap��
  ����  ����:   
******************************************************************************/
#ifndef _WPIXMAP_H_
#define _WPIXMAP_H_

#include <QtGui/QPixmap>
#include "../wdllimport.h"
#include "wenums.h"
#include "wmatrix.h"
/** 
 \brief                 ������Ҫ���ͼƬ�ĸ������
\details   
 \author    ���� & @zcw
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
	\remark    ��Ҫ���ͼƬ�ĸ��Ʋ�������ԭͼƬ��(x, y)�㿪ʼ���ƣ�����width��height��С 
	*/
	WPixmap xcopy(int x, int y, int width, int height) const;


	/**
	\brief      xtransformed
	\Access    public 
	\param  const WMatrix & matrix
	\param  Ws::TransformationMode mode
	\retval     WPixmap
	\remark    ��װQPixmap���� 
	*/
	WPixmap xtransformed(const WMatrix& matrix, Ws::TransformationMode mode = Ws::FastTransformation) const;

	/**
	\brief      xrotated
	\Access    public 
	\param  double angle
	\retval     WPixmap
	\remark     ��ͼƬ������ת
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