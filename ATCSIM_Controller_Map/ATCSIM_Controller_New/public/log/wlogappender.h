#ifndef _WLOG_APPENDER_H_
#define _WLOG_APPENDER_H_

#include <sstream>
#include "wunaryfunctor.h"

class WLogAppender //��־��ʽ����
{
public:
	typedef WLogAppender _Myt; //������������
	typedef const std::string& text_type;
	typedef WUnaryFunctorBase<text_type> WLogDispatcher;

	WLogAppender();
	template<class F>
	WLogAppender(F f);
	template<class T>
	WLogAppender(T* obj, void (T::*mfn)(text_type));

	~WLogAppender();

	//������־����
	void ResetDispatcher();

	//������־����
	template<class F>
	void SetDispatcher(F f);
	template<class T>
	void SetDispatcher(T* obj, void (T::*mfn)(text_type));

	void Flush(); //�����е�����ˢ�£�ͨ��������ʽ���ã����������ʽ��*this << std::flush��std::endl����

	_Myt& operator<<(_Myt& (*pfn)(_Myt&)); //ʵ���������std::endl std::ends

	template<typename T>
	_Myt& operator<<(const T& t); //ʵ������������Ͷ���

	std::ostream& GetStream(); //��ȡ������

private:
	std::ostringstream m_oss;
	WLogDispatcher* m_dispatcher; //��־����
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
	WLogAppender& flush(WLogAppender& appender); //ˢ�����
	WLogAppender& ends(WLogAppender& appender); //�������
	WLogAppender& endl(WLogAppender& appender); //����+ˢ�����
	WLogAppender& time(WLogAppender& appender); //ʱ�����[hh:mm:ss]
	WLogAppender& timeplus(WLogAppender& appender); //ʱ�����[hh:mm:ss.ms]
}

#endif