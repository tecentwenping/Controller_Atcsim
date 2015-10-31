#include "../wdllexport.h"
#include "wpixmap.h"
#include "../gui/guitransform.h"


#define QPIXMAP(pixmap) (dynamic_cast<QPixmap&>(pixmap))
#define QPIXMAP_C(pixmap) (dynamic_cast<const QPixmap&>(pixmap))

WPixmap::WPixmap()
{
}

WPixmap::WPixmap(int width, int height) : QPixmap(width, height)
{
}

WPixmap::WPixmap(const std::string& filename, const char* format)
	: QPixmap(QString::fromStdString(filename), format)
{
}

WPixmap::WPixmap(const WPixmap& pixmap) : QPixmap(QPIXMAP_C(pixmap))
{
}

WPixmap::WPixmap(const QPixmap& pixmap) : QPixmap(pixmap)
{
}

WPixmap& WPixmap::operator=(const WPixmap& pixmap)
{
	if (this != &pixmap)
	{
		QPIXMAP(*this) = QPIXMAP_C(pixmap);
	}
	return *this;
}

WPixmap WPixmap::xcopy(int x, int y, int width, int height) const
{
	return WPixmap(copy(x, y, width, height));
}

/**
\brief      xtransformed
\Access    public 
\param  const WMatrix & matrix
\param  Ws::TransformationMode mode
\retval     WPixmap
\remark     
*/
WPixmap WPixmap::xtransformed( const WMatrix& matrix, Ws::TransformationMode mode /*= FastTransformation*/ ) const
{
	QMatrix m(matrix.m11(), matrix.m12(), matrix.m21(), matrix.m22(), matrix.dx(), matrix.dy());

	//return WPixmap(transformed(transform(matrix), mode));// 编译无法匹配到QTransform的接口
	return WPixmap(transformed(m, static_cast<Qt::TransformationMode>(mode)));
}

/**
\brief      xrotated
\Access    public 
\param  double angle
\retval     WPixmap
\remark     
*/
WPixmap WPixmap::xrotated( double angle, Ws::TransformationMode mode ) const
{
	QMatrix m;
	m.rotate(angle);
	return WPixmap(transformed(m, static_cast<Qt::TransformationMode>(mode)));
}


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
WPixmap WPixmap::xscaled( int width, int height, Ws::AspectRatioMode aspectRatioMode /*= Ws::IgnoreAspectRatio*/, Ws::TransformationMode transformationMode /*= Ws::FastTransformation*/ ) const
{
	QMatrix m;
	m.scale(width, height);
	return WPixmap(scaled(width, height, static_cast<Qt::AspectRatioMode>(aspectRatioMode), static_cast<Qt::TransformationMode>(transformationMode)));

}
