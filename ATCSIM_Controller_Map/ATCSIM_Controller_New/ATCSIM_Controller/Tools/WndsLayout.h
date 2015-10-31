#ifndef _WNDSLAYOUT_H
#define _WNDSLAYOUT_H

//该类主要管理窗口布局
class WndsLayout
{
public:
	WndsLayout(){};
	virtual ~WndsLayout(){};
public:
	virtual void Layout(){}; 
};


#endif