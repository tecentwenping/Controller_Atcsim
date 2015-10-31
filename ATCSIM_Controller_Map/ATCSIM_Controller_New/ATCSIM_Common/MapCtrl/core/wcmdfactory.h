/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wcmdfactory.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WCmdFactory类
  【其  它】:   
******************************************************************************/
#ifndef _WCMD_FACTORY_H_
#define _WCMD_FACTORY_H_

#include <boost/bind.hpp>
#include "../wdllimport.h"
#include "wcmd.h"

/** 
 \brief                 此类为一个工厂类，主要用于创建命令（WCmd的子类实例）
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WCmdFactory
{
public:
	/**
	\brief      create
	\Access    public static 
	\param  F f
	\retval     WCmd*
	\remark     等价于调用f()
	*/
	template<class F>
	static WCmd* create(F f)
	{
		return createPrivate(f);
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\retval     WCmd*
	\remark    等价于调用(a1->*f)() 
	*/
	template<class F, class A1>
	static WCmd* create(F f, A1 a1)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1));
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\param  A2 a2
	\retval     WCmd*
	\remark     等价于调用(a1->*f)(a2)
	*/
	template<class F, class A1, class A2>
	static WCmd* create(F f, A1 a1, A2 a2)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1, a2));
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\param  A2 a2
	\param  A3 a3
	\retval     WCmd*
	\remark       等价于调用(a1->*f)(a2, a3)
	*/
	template<class F, class A1, class A2, class A3>
	static WCmd* create(F f, A1 a1, A2 a2, A3 a3)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1, a2, a3));
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\param  A2 a2
	\param  A3 a3
	\param  A4 a4
	\retval     WCmd*
	\remark       等价于调用(a1->*f)(a2, a3, a4)
	*/
	template<class F, class A1, class A2, class A3, class A4>
	static WCmd* create(F f, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1, a2, a3, a4));
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\param  A2 a2
	\param  A3 a3
	\param  A4 a4
	\param  A5 a5
	\retval     WCmd*
	\remark       等价于调用(a1->*f)(a2, a3, a4, a5)
	*/
	template<class F, class A1, class A2, class A3, class A4, class A5>
	static WCmd* create(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1, a2, a3, a4, a5));
	}

	/**
	\brief      create
	\Access    public static 
	\param  F f
	\param  A1 a1
	\param  A2 a2
	\param  A3 a3
	\param  A4 a4
	\param  A5 a5
	\param  A6 a6
	\retval     WCmd*
	\remark       等价于调用(a1->*f)(a2, a3, a4, a5, a6)
	*/
	template<class F, class A1, class A2, class A3, class A4, class A5, class A6>
	static WCmd* create(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		return createPrivate(boost::bind(boost::type<void>(), f, a1, a2, a3, a4, a5, a6));
	}

	/**
	\brief      destroy
	\Access    public static 
	\param  WCmd * cmd
	\retval     void
	\remark    删除创建的命令 
	*/
	static void destroy(WCmd* cmd) 
	{
		delete cmd;
	}

private:
	/**
	\brief      createPrivate
	\Access    private static 
	\param  F f
	\retval     WCmd*
	\remark    创建命令的内部实现 
	*/
	template<class F>
	static WCmd* createPrivate(F f)
	{
/** 
 \brief                 函数内部类
\details   
 \author    陈龙
\date      2013/05/22
*/
		class WCmdPrivate : public WCmd
		{
		public:
			explicit WCmdPrivate(F f) : _f(f) {}

			virtual void exec() { _f(); }

		private:
			F _f;
		};

		return new WCmdPrivate(f);
	}
};

#endif