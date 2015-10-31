/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wcmdfactory.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫ���WCmdFactory��
  ����  ����:   
******************************************************************************/
#ifndef _WCMD_FACTORY_H_
#define _WCMD_FACTORY_H_

#include <boost/bind.hpp>
#include "../wdllimport.h"
#include "wcmd.h"

/** 
 \brief                 ����Ϊһ�������࣬��Ҫ���ڴ������WCmd������ʵ����
\details   
 \author    ����
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
	\remark     �ȼ��ڵ���f()
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
	\remark    �ȼ��ڵ���(a1->*f)() 
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
	\remark     �ȼ��ڵ���(a1->*f)(a2)
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
	\remark       �ȼ��ڵ���(a1->*f)(a2, a3)
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
	\remark       �ȼ��ڵ���(a1->*f)(a2, a3, a4)
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
	\remark       �ȼ��ڵ���(a1->*f)(a2, a3, a4, a5)
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
	\remark       �ȼ��ڵ���(a1->*f)(a2, a3, a4, a5, a6)
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
	\remark    ɾ������������ 
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
	\remark    ����������ڲ�ʵ�� 
	*/
	template<class F>
	static WCmd* createPrivate(F f)
	{
/** 
 \brief                 �����ڲ���
\details   
 \author    ����
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