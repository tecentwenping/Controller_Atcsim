#ifndef _Poly_Data_Obj_H_
#define _Poly_Data_Obj_H_

#include "data_obj.h"

class Base
{
public:
	Base(){}
	Base(int i) : m_iId(i)
	{
	}
	int m_iId;
};

class DerivedA : public Base
{
public:
	DerivedA(){}
	DerivedA(int i, const user_define& ud) : Base(i), m_ud(ud)
	{
	}

	user_define m_ud;
};

#endif