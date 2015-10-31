/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wfontmetrics.cpp
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫ������WAbstractFontMetricsEngine�ӿڣ�
					Ȼ����ڴ˽ӿ�ʵ����һ��WQtFontMetricsEngine��
  ����  ����:   
******************************************************************************/
#include <QFontMetrics>
#include "../wdllexport.h"
#include "wfontmetrics.h"
#include "../gui/guitransform.h"

/** 
 \brief                 ������Ҫ��WFontMetricsʹ�ã�ΪWFontMetrics�ļ�������
\details   ��������нӿں����WFontMetrics����һ��
 \author    ����
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
 \brief                 ���������WAbstractFontMetricsEngine�ӿڽ�����ʵ��
\details   
 \author    ����
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