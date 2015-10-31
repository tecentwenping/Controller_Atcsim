/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: weventoption.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ����WEventOption��
  ����  ����:   
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
 \brief                 ������Ҫ���ڹ��˳����е��¼�����Ҫ���WEventListener��һ��ʹ��
\details   
 \author    ����
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