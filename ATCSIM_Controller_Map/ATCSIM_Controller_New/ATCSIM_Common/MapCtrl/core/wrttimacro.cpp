#include "../wdllexport.h"
#include "wrttimacro.h"

const WItemInfo* WItemInfo::begin = 0; //ͼԪ��������ͷָ���ʼΪ0

WItemRegHelper::WItemRegHelper(WItemInfo* info) //���˽����뵽ͼԪ���������ͷ��
{
	info->next = WItemInfo::begin;
	WItemInfo::begin = info;
}