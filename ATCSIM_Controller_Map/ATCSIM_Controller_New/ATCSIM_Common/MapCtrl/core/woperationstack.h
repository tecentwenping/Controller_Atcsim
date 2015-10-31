/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: woperationstack.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/22
  【描  述】:  此文件主要实现WOperationStack类
  【其  它】:   
******************************************************************************/
#ifndef _WOPERATION_STACK_H_
#define _WOPERATION_STACK_H_

#include <stack>
#include "../wdllimport.h"

class WCmd;

/** 
 \brief       此类实现了一个操作堆栈，主要用于进行一些操作后然后需要对这些操作进行撤消和重做操作
			 进行一系列操作后， 每一个操作以一个命令的形式进入堆栈中，撤消操作的时候，
			 这些操作的逆操作，以反向的顺序出栈，并执行。而重做操作和撤消操作正好相反，
			 和最开始进栈的顺序一致。
\details   
 \author    陈龙
\date      2013/05/22
*/
class MAPAPI WOperationStack //场景操作堆栈
{
public:
	~WOperationStack();

	/**
	\brief      push
	\Access    public 
	\param  WCmd * cmdDo
	\param  WCmd * cmdUndo
	\retval     void
	\remark    将一个命令和其逆命令进栈（命令通常由WCmdFactory创建） 
	*/
	void push(WCmd* cmdDo, WCmd* cmdUndo); //增加一个操作

	/**
	\brief      undo
	\Access    public 
	\retval     void
	\remark    撤消最近的操作 
	*/
	void undo(); //撤消

	/**
	\brief      redo
	\Access    public 
	\retval     void
	\remark    重做最近的操作 
	*/
	void redo(); //重做

	/**
	\brief      canUndo
	\Access    public 
	\retval     bool
	\remark    是否可以撤消 
	*/
	bool canUndo() const; //是否可以撤消

	/**
	\brief      canRedo
	\Access    public 
	\retval     bool
	\remark     是否可以重做
	*/
	bool canRedo() const; //是否可以重做

	/**
	\brief      clear
	\Access    public 
	\retval     void
	\remark     清空操作堆栈
	*/
	void clear(); //清空操作堆栈

private:
	std::stack<WCmd*> _stk_do;
	std::stack<WCmd*> _stk_undo;
	std::stack<WCmd*> _stk_redo;
	std::stack<WCmd*> _stk_unredo;
};

#endif