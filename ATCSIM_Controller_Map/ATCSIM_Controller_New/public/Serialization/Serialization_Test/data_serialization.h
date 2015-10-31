#ifndef _Data_Serialization_H_
#define _Data_Serialization_H_

#include "data_obj.h"
#include "poly_data_obj.h"

#define SERIALIZE(DataObj, value)\
	template<typename Archive>\
	Archive& serialize(Archive& ar, DataObj& d, const unsigned int)\
{\
	return ar & value;\
}

//// ���л�user_define
SERIALIZE(user_define, d.m_int & d.m_char & d.m_str & d.m_t)
//
// ���л�complex_user_define
SERIALIZE(complex_user_define, d.m_vUserDefine)

// ���л�more_complex_user_define
SERIALIZE(more_complex_user_define, d.m_pComplexUserDefine);


//************************************************************
// ���л�Base
SERIALIZE(Base, d.m_iId)

// ������ʽ��д��
template<typename Archive>
Archive& serialize(Archive& ar, DerivedA& d, const unsigned int version)
{
	serialize(ar, static_cast<Base&>(d), version);

	return ar & d.m_ud;
}


#endif
