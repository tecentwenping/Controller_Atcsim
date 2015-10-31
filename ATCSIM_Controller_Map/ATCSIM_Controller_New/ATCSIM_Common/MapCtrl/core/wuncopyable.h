/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wuncopyable.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要完成WUncopyable类
  【其  它】:   
******************************************************************************/
#ifndef _WUNCOPYABLE_H_
#define _WUNCOPYABLE_H_

#include "../wdllimport.h"

/** 
 \brief          此主要完成类对象的不可以拷贝的语意，此类是一个基类，
					所有不支持对象拷贝的类从这个类继承即可
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WUncopable
{
public:
	WUncopable() {}

private:
	/**
	\brief      WUncopable
	\Access    private 
	\param  const WUncopable &
	\retval     
	\remark    禁止拷贝操作 
	*/
	WUncopable(const WUncopable&);

	/**
	\brief      operator=
	\Access    private 
	\param  const WUncopable &
	\retval     WUncopable&
	\remark    禁止赋值操作 
	*/
	WUncopable& operator=(const WUncopable&);
};

#endif