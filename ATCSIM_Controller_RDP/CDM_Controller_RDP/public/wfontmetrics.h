/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wfontmetrics.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ����WFontMetrics��
  ����  ����:   
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
 \brief                 ��������ʵ�ּ���WFont��һЩ����
\details   
 \author    ����
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
	\remark    ��������Ļ���baseline������ַ�λ�ã��߶ȣ��ľ��� 
	*/
	double ascent() const;

	/**
	\brief      descent
	\Access    public 
	\retval     double
	\remark    ��������Ļ���baseline������ַ�λ�ã��߶ȣ��ľ��� 
	*/
	double descent() const;

	/**
	\brief      height
	\Access    public 
	\retval     double
	\remark    ��������ĸ߶ȣ�������ascent() + descent() +����1Ϊ���߸߶ȣ� 
	*/
	double height() const;

	double leading() const;

	/**
	\brief      averageCharWidth
	\Access    public 
	\retval     double
	\remark    ����ƽ���ַ���� 
	*/
	double averageCharWidth() const;

	/**
	\brief      maxWidth
	\Access    public 
	\retval     double
	\remark    ��������ַ���� 
	*/
	double maxWidth() const;

	/**
	\brief      width
	\Access    public 
	\param  const std::string & text
	\retval     double
	\remark    �����ַ����Ŀ�� 
	*/
	double width(const std::string& text) const;

	/**
	\brief      width
	\Access    public 
	\param  const std::wstring & text
	\retval     double
	\remark    ���ؿ��ַ����Ŀ�� 
	*/
	double width(const std::wstring& text) const;

	/**
	\brief      size
	\Access    public 
	\param  int flags �˱�ʶ������Ws::TextAlignment��Ws::TextFlag���������
	\param  const std::string & text
	\retval     WWorldSizeF
	\remark    �����ַ���ռ��������Ĵ�С 
	*/
	WWorldSizeF size(int flags, const std::string& text) const;

	/**
	\brief      size
	\Access    public 
	\param  int flags �˱�ʶ������Ws::TextAlignment��Ws::TextFlag���������
	\param  const std::wstring & text
	\retval     WWorldSizeF
	\remark    ���ؿ��ַ���ռ��������Ĵ�С 
	*/
	WWorldSizeF size(int flags, const std::wstring& text) const;

	/**
	\brief      boundingRect
	\Access    public 
	\param  const std::string & text
	\retval     WWorldRectF
	\remark    �����ַ�����ռ�������� 
	*/
	WWorldRectF boundingRect(const std::string& text) const;

	/**
	\brief      boundingRect
	\Access    public 
	\param  const std::wstring & text
	\retval     WWorldRectF
	\remark    ���ؿ��ַ�����ռ�������� 
	*/
	WWorldRectF boundingRect(const std::wstring& text) const;

private:
	WAbstractFontMetricsEngine* engine_; //����������Եļ�������
};

#endif