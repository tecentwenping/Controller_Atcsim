/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wfontmetrics.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现了WFontMetrics类
  【其  它】:   
******************************************************************************/
#ifndef _WFONT_METRICS_H_
#define _WFONT_METRICS_H_

#include <string>
#include "../wdllimport.h"
#include "wworldsize.h"
#include "wworldrect.h"

class WFont;
class WAbstractFontMetricsEngine;

/** 
 \brief                 此类用于实现计算WFont的一些性质
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WFontMetrics
{
public:
	WFontMetrics(const WFont& font);
	~WFontMetrics();

	/**
	\brief      ascent
	\Access    public 
	\retval     double
	\remark    返回字体的基线baseline到最高字符位置（高度）的距离 
	*/
	double ascent() const;

	/**
	\brief      descent
	\Access    public 
	\retval     double
	\remark    返回字体的基线baseline到最低字符位置（高度）的距离 
	*/
	double descent() const;

	/**
	\brief      height
	\Access    public 
	\retval     double
	\remark    返回字体的高度，它等于ascent() + descent() +１（1为基线高度） 
	*/
	double height() const;

	double leading() const;

	/**
	\brief      averageCharWidth
	\Access    public 
	\retval     double
	\remark    返回平均字符宽度 
	*/
	double averageCharWidth() const;

	/**
	\brief      maxWidth
	\Access    public 
	\retval     double
	\remark    返回最宽字符宽度 
	*/
	double maxWidth() const;

	/**
	\brief      width
	\Access    public 
	\param  const std::string & text
	\retval     double
	\remark    返回字符串的宽度 
	*/
	double width(const std::string& text) const;

	/**
	\brief      width
	\Access    public 
	\param  const std::wstring & text
	\retval     double
	\remark    返回宽字符串的宽度 
	*/
	double width(const std::wstring& text) const;

	/**
	\brief      size
	\Access    public 
	\param  int flags 此标识可以是Ws::TextAlignment和Ws::TextFlag的任意组合
	\param  const std::string & text
	\retval     WWorldSizeF
	\remark    返回字符串占矩形区域的大小 
	*/
	WWorldSizeF size(int flags, const std::string& text) const;

	/**
	\brief      size
	\Access    public 
	\param  int flags 此标识可以是Ws::TextAlignment和Ws::TextFlag的任意组合
	\param  const std::wstring & text
	\retval     WWorldSizeF
	\remark    返回宽字符串占矩形区域的大小 
	*/
	WWorldSizeF size(int flags, const std::wstring& text) const;

	/**
	\brief      boundingRect
	\Access    public 
	\param  const std::string & text
	\retval     WWorldRectF
	\remark    返回字符串所占矩形区域 
	*/
	WWorldRectF boundingRect(const std::string& text) const;

	/**
	\brief      boundingRect
	\Access    public 
	\param  const std::wstring & text
	\retval     WWorldRectF
	\remark    返回宽字符串所占矩形区域 
	*/
	WWorldRectF boundingRect(const std::wstring& text) const;

private:
	WAbstractFontMetricsEngine* engine_; //字体各种特性的计算引擎
};

#endif