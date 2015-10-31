/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: weventoption.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现了WEventOption类
  【其  它】:   
******************************************************************************/
#ifndef _WEVENT_OPTION_H_
#define _WEVENT_OPTION_H_

#include "../wdllimport.h"


#define OPTION_ITEM(memName, getMethod, setMethod)\
public:\
bool getMethod() const\
{\
	return memName;\
}\
\
void setMethod(bool accept = true)\
{\
	memName = accept;\
}\
\
private:\
bool memName;\
\

/** 
 \brief                 此类主要用于过滤场景中的事件，主要配合WEventListener类一起使用
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WEventOption
{
	OPTION_ITEM(_lbuttonDown, lbuttonDown, acceptLButtonDown)
	OPTION_ITEM(_lbuttonUp, lbuttonUp, acceptLButtonUp)
	OPTION_ITEM(_rbuttonDown, rbuttonDown, acceptRButtonDown)
	OPTION_ITEM(_rbuttonUp, rbuttonUp, acceptRButtonUp)
};

//class WEventOption
//{
//public:
//	bool lbuttonDown() const;
//	bool lbuttonUp() const;
//	bool rbuttonDown() const;
//	bool rbuttonUp() const;
//
//	void acceptLButtonDown(bool accept = true);
//	void acceptLButtonUp(bool accept = true);
//	void acceptRButtonDown(bool accept = true);
//	void acceptRButtonUp(bool accept = true);
//
//private:
//	bool _lbuttonDown;
//	bool _lbuttonUp;
//	bool _rbuttonDown;
//	bool _rbuttonUp;
//};

#endif