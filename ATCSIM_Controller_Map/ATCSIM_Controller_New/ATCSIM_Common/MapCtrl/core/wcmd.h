/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wcmd.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  主要定义了WCmd接口
  【其  它】:   
******************************************************************************/
#ifndef _WCMD_H_
#define _WCMD_H_

#include "../wdllimport.h"

/** 
 \brief                 此类是一个具体操作的抽象
\details   比如将某个窗口先移动，然后放大，最后滚动等，将这一系列操作记为一个操作A，
			 A就是一个WCmd的实例，可以将它保存，在任意需要的时间点执行操作A，也就等价于
			 进行了上面的一系列操作
			 自从有了WCmdFactory，通常你不需要自己实现WCmd子类，充分利用WCmdFactory你就可以
			 完成大部分的WCmd命令创建的过程
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WCmd
{
public:
	virtual ~WCmd() {}

	/**
	\brief      exec
	\Access    virtual public 
	\retval     void
	\remark    执行此操作 
	*/
	virtual void exec() = 0;
};

#endif