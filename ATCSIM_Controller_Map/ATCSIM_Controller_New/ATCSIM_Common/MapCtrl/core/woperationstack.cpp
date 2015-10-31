#include "../wdllexport.h"
#include "wcmdfactory.h"
#include "woperationstack.h"

static void clear_operation_stack(std::stack<WCmd*>& stk)
{
	while (!stk.empty())
	{
		WCmdFactory::destroy(stk.top());
		stk.pop();
	}
}

WOperationStack::~WOperationStack()
{
	clear();
}

void WOperationStack::clear()
{
	clear_operation_stack(_stk_do);
	clear_operation_stack(_stk_undo);
	clear_operation_stack(_stk_redo);
	clear_operation_stack(_stk_unredo);
}

void WOperationStack::push(WCmd* cmdDo, WCmd* cmdUndo)
{
	_stk_do.push(cmdDo);
	_stk_undo.push(cmdUndo);

	clear_operation_stack(_stk_redo);
	clear_operation_stack(_stk_unredo);
}

bool WOperationStack::canUndo() const
{
	return !_stk_undo.empty();
}

bool WOperationStack::canRedo() const
{
	return !_stk_redo.empty();
}

void WOperationStack::undo()
{
	if (canUndo())
	{
		_stk_undo.top()->exec();
		_stk_unredo.push(_stk_undo.top());
		_stk_undo.pop();

		_stk_redo.push(_stk_do.top());
		_stk_do.pop();
	}
}

void WOperationStack::redo()
{
	if (canRedo())
	{
		_stk_redo.top()->exec();
		_stk_do.push(_stk_redo.top());
		_stk_redo.pop();

		_stk_undo.push(_stk_unredo.top());
		_stk_unredo.pop();
	}
}