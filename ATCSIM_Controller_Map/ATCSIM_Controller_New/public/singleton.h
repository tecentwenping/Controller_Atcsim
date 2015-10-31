#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "uncopyable.h"

#define DECLARE_SINGLETON(T) friend T& WSingleton<T>::Ref(); private:T() {}
#define DECLARE_SINGLETON_EX(T) friend T& WSingleton<T>::Ref(); private:T();

template<class T>
class WSingleton : private WUncopyable
{
public:
	inline static T& Ref() { static T t; return t; }
	inline static T* Ptr() { return &Ref(); }
};

#ifdef _SINGLETON_DEMO_
//the following code demonstrates how to use class singleton

/***************************demo1*********************************************/
class sgt_demo1 : public WSingleton<sgt_demo1>
{
	DECLARE_SINGLETON(sgt_demo1)

	int foo(bool b) { return 0; }
};

sgt_demo1& rd = sgt_demo1::Ref(); //get reference (recommended usage)
sgt_demo1* pd = sgt_demo1::Ptr(); //get pointer
int i = sgt_demo1::Ref().foo(false); //call member function
/************************************************************************/

/*******************************demo2**********************************/
class sgt_demo2 : public WSingleton<sgt_demo2>
{
	DECLARE_SINGLETON_EX(sgt_demo2)

private:
	int* p;
	bool b;
};

//if you want to do something in constructor, you have the chance
//do it in you cpps
sgt_demo2::sgt_demo2() : p(0), b(false)
{
}
/************************************************************************/
#endif

#endif