/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: woperationstack.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ���ļ���Ҫʵ��WOperationStack��
  ����  ����:   
******************************************************************************/
#ifndef _WOPERATION_STACK_H_
#define _WOPERATION_STACK_H_

#include <stack>
#include "../wdllimport.h"

class WCmd;

/** 
 \brief       ����ʵ����һ��������ջ����Ҫ���ڽ���һЩ������Ȼ����Ҫ����Щ�������г�������������
			 ����һϵ�в����� ÿһ��������һ���������ʽ�����ջ�У�����������ʱ��
			 ��Щ��������������Է����˳���ջ����ִ�С������������ͳ������������෴��
			 ���ʼ��ջ��˳��һ�¡�
\details   
 \author    ����
\date      2013/05/22
*/
class MAPAPI WOperationStack //����������ջ
{
public:
	~WOperationStack();

	/**
	\brief      push
	\Access    public 
	\param  WCmd * cmdDo
	\param  WCmd * cmdUndo
	\retval     void
	\remark    ��һ����������������ջ������ͨ����WCmdFactory������ 
	*/
	void push(WCmd* cmdDo, WCmd* cmdUndo); //����һ������

	/**
	\brief      undo
	\Access    public 
	\retval     void
	\remark    ��������Ĳ��� 
	*/
	void undo(); //����

	/**
	\brief      redo
	\Access    public 
	\retval     void
	\remark    ��������Ĳ��� 
	*/
	void redo(); //����

	/**
	\brief      canUndo
	\Access    public 
	\retval     bool
	\remark    �Ƿ���Գ��� 
	*/
	bool canUndo() const; //�Ƿ���Գ���

	/**
	\brief      canRedo
	\Access    public 
	\retval     bool
	\remark     �Ƿ��������
	*/
	bool canRedo() const; //�Ƿ��������

	/**
	\brief      clear
	\Access    public 
	\retval     void
	\remark     ��ղ�����ջ
	*/
	void clear(); //��ղ�����ջ

private:
	std::stack<WCmd*> _stk_do;
	std::stack<WCmd*> _stk_undo;
	std::stack<WCmd*> _stk_redo;
	std::stack<WCmd*> _stk_unredo;
};

#endif