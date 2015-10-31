#include "../wdllexport.h"
#include "wrttimacro.h"

const WItemInfo* WItemInfo::begin = 0; //图元创建链表头指针初始为0

WItemRegHelper::WItemRegHelper(WItemInfo* info) //将此结点插入到图元创建链表的头部
{
	info->next = WItemInfo::begin;
	WItemInfo::begin = info;
}