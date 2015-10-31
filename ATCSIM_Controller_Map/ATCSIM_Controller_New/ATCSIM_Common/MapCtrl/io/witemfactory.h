/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: witemfactory.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要定义了WItemFactory类
  【其  它】:   
******************************************************************************/
#ifndef _WITEM_FACTORY_H_
#define _WITEM_FACTORY_H_

#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief       此类主要实现了将图元串行化到二进制流中，并在二进制流中动态创建图元对象
\details   
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WItemFactory
{
public:
	/**
	\brief      serialize
	\Access    public static 
	\param  char * buf
	\param  const WGraphicsItem & item
	\retval     char*
	\remark     将图元串行化到二进制流中
	*/
	static char* serialize(char* buf, const WGraphicsItem& item);
	
	/**
	\brief      serialize_size
	\Access    public static 
	\param  const WGraphicsItem & item
	\retval     size_t
	\remark     计算图元串行化到二进制流中所需缓冲区大小
	*/
	static size_t serialize_size(const WGraphicsItem& item);

	/**
	\brief      create
	\Access    public static 
	\param  const char * buf
	\param  WGraphicsItem * * item
	\retval     const char* 图元创建后缓冲区的当前指针位置
	\remark     从输入缓冲区buf中创建图元（由*item返回，如果创建失败item不变）
	*/
	static const char* create(const char* buf, WGraphicsItem** item);
};

#endif