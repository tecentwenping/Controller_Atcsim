#ifndef _WLOG_APPENDER_H_
#define _WLOG_APPENDER_H_

#include <sstream>
#include "wunaryfunctor.h"

class WLogAppender //日志格式化器
{
public:
	typedef WLogAppender _Myt; //定义自身类型
	typedef const std::string& text_type;
	typedef WUnaryFunctorBase<text_type> WLogDispatcher;

	WLogAppender();
	template<class F>
	WLogAppender(F f);
	template<class T>
	WLogAppender(T* obj, void (T::*mfn)(text_type));

	~WLogAppender();

	//重置日志容器
	void ResetDispatcher();

	//设置日志容器
	template<class F>
	void SetDispatcher(F f);
	template<class T>
	void SetDispatcher(T* obj, void (T::*mfn)(text_type));

	void Flush(); //将流中的数据刷新，通常不用显式调用，调用算符形式的*this << std::flush或std::endl即可

	_Myt& operator<<(_Myt& (*pfn)(_Myt&)); //实现算符，如std::endl std::ends

	template<typename T>
	_Myt& operator<<(const T& t); //实现输出任意类型对象

	std::ostream& GetStream(); //获取流对象

private:
	std::ostringstream m_oss;
	WLogDispatcher* m_dispatcher; //日志容器
};

template<class F>
WLogAppender::WLogAppender(F f) : m_dispatcher(new WUnaryFunctor<text_type, F>(f))
{
}

template<class T>
WLogAppender::WLogAppender(T* obj, void (T::*mfn)(text_type))
	: m_dispatcher(new WUnaryMemfun<text_type, T>(obj, mfn))
{
}

template<class F>
void WLogAppender::SetDispatcher(F f)
{
	delete m_dispatcher;
	m_dispatcher = new WUnaryFunctor<text_type, F>(f);
}

template<class T>
void WLogAppender::SetDispatcher(T* obj, void (T::*mfn)(text_type))
{
	delete m_dispatcher;
	m_dispatcher = new WUnaryMemfun<text_type, T>(obj, mfn);
}

template<typename T>
WLogAppender::_Myt& WLogAppender::operator<<(const T& t)
{
#ifdef _USE_LOG
	m_oss << t;
#else
	t; //wipe out compile warning : unreferenced parameter
#endif
	return *this;
}

namespace std
{
	WLogAppender& flush(WLogAppender& appender); //刷新算符
	WLogAppender& ends(WLogAppender& appender); //结束算符
	WLogAppender& endl(WLogAppender& appender); //换行+刷新算符
	WLogAppender& time(WLogAppender& appender); //时间算符[hh:mm:ss]
	WLogAppender& timeplus(WLogAppender& appender); //时间算符[hh:mm:ss.ms]
}

#endif