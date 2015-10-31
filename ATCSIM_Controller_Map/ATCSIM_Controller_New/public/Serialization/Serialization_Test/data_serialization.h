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

//// 串行化user_define
SERIALIZE(user_define, d.m_int & d.m_char & d.m_str & d.m_t)
//
// 串行化complex_user_define
SERIALIZE(complex_user_define, d.m_vUserDefine)

// 串行化more_complex_user_define
SERIALIZE(more_complex_user_define, d.m_pComplexUserDefine);


//************************************************************
// 串行化Base
SERIALIZE(Base, d.m_iId)

// 非侵入式类写法
template<typename Archive>
Archive& serialize(Archive& ar, DerivedA& d, const unsigned int version)
{
	serialize(ar, static_cast<Base&>(d), version);

	return ar & d.m_ud;
}


#endif
