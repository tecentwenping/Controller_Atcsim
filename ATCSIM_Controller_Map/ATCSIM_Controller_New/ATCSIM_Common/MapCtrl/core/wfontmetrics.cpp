/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wfontmetrics.cpp
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要定义了WAbstractFontMetricsEngine接口，
					然后基于此接口实现了一个WQtFontMetricsEngine类
  【其  它】:   
******************************************************************************/
#include <QFontMetrics>
#include "../wdllexport.h"
#include "wfontmetrics.h"
#include "../gui/guitransform.h"

/** 
 \brief                 此类主要被WFontMetrics使用，为WFontMetrics的计算引擎
\details   此类的所有接口含义和WFontMetrics保持一致
 \author    陈龙
\date      2013/05/23
*/
class WAbstractFontMetricsEngine
{
public:
	WAbstractFontMetricsEngine(const WFont&) {}
	virtual ~WAbstractFontMetricsEngine() {}

	virtual double ascent() = 0;
	virtual double descent() = 0;
	virtual double height() = 0;
	virtual double leading() = 0;

	virtual double averageCharWidth() = 0;
	virtual double maxWidth() = 0;

	virtual double width(const std::string& text) = 0;
	virtual double width(const std::wstring& text) = 0;
	virtual WWorldSizeF size(int flags, const std::string& text) = 0;
	virtual WWorldSizeF size(int flags, const std::wstring& text) = 0;
	virtual WWorldRectF boundingRect(const std::string& text) = 0;
	virtual WWorldRectF boundingRect(const std::wstring& text) = 0;
};

/** 
 \brief                 基于上面的WAbstractFontMetricsEngine接口进行了实现
\details   
 \author    陈龙
\date      2013/05/23
*/
class WQtFontMetricsEngine : public WAbstractFontMetricsEngine
{
public:
	WQtFontMetricsEngine(const WFont& font) 
		: WAbstractFontMetricsEngine(font), metrics_(transform(font)) {}

	virtual double ascent() { return metrics_.ascent(); }
	virtual double descent() { return metrics_.descent(); }
	virtual double height() { return metrics_.height(); }
	virtual double leading() { return metrics_.leading(); }

	virtual double averageCharWidth() { return metrics_.averageCharWidth(); }
	virtual double maxWidth() { return metrics_.maxWidth(); }

	virtual double width(const std::string& text) 
	{ 
		return metrics_.width(QString::fromStdString(text)); 
	}

	virtual double width(const std::wstring& text) 
	{ 
		return metrics_.width(QString::fromStdWString(text)); 
	}

	virtual WWorldSizeF size(int flags, const std::string& text) 
	{ 
		return transform(metrics_.size(flags, QString::fromStdString(text))); 
	}

	virtual WWorldSizeF size(int flags, const std::wstring& text) 
	{ 
		return transform(metrics_.size(flags, QString::fromStdWString(text))); 
	}

	virtual WWorldRectF boundingRect(const std::string& text) 
	{ 
		return WWorldRectF(0, 0, width(text), height()); 
	}

	virtual WWorldRectF boundingRect(const std::wstring& text) 
	{
		return WWorldRectF(0, 0, width(text), height());
	}

private:
	mutable QFontMetricsF metrics_;
};

WFontMetrics::WFontMetrics(const WFont& font)
{
	engine_ = new WQtFontMetricsEngine(font);
}

WFontMetrics::~WFontMetrics()
{
	delete engine_;
}

double WFontMetrics::ascent() const
{
	return engine_->ascent();
}

double WFontMetrics::descent() const
{
	return engine_->descent();
}

double WFontMetrics::height() const
{
	return engine_->height();
}

double WFontMetrics::leading() const
{
	return engine_->leading();
}

double WFontMetrics::averageCharWidth() const
{
	return engine_->averageCharWidth();
}

double WFontMetrics::maxWidth() const
{
	return engine_->maxWidth();
}

double WFontMetrics::width(const std::string& text) const
{
	return engine_->width(text);
}

double WFontMetrics::width(const std::wstring& text) const
{
	return engine_->width(text);
}

WWorldSizeF WFontMetrics::size(int flags, const std::string& text) const
{
	return engine_->size(flags, text);
}

WWorldSizeF WFontMetrics::size(int flags, const std::wstring& text) const
{
	return engine_->size(flags, text);
}

WWorldRectF WFontMetrics::boundingRect(const std::string& text) const
{
	return engine_->boundingRect(text);
}

WWorldRectF WFontMetrics::boundingRect(const std::wstring& text) const
{
	return engine_->boundingRect(text);
}