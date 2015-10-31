#ifndef __Test_Type_Traits_H__
#define __Test_Type_Traits_H__

#include <bitset>
#include <gtest/gtest.h>
#include <boost/type_traits.hpp>
#include "wserialize.h"
#include "data_obj.h"




class TypeTraitsTest : public testing::Test
{
protected:
	void SetUp(){}
	void TearDown(){}
};


TEST_F(TypeTraitsTest, test_pod_type)
{
	//EXPECT_EQ(boost::is_pod<unsigned int:1>::value, true);
	EXPECT_EQ(boost::is_pod<user_basic_define_no_construct>::value, true);
	EXPECT_EQ(boost::is_pod<user_define_has_construct>::value, false);
}

TEST_F(TypeTraitsTest, test_serialize_)
{
	char buff[1000];
	user_basic_define_no_construct ud;
	ud.m_i = 1;
	ud.m_c = 5;

	WSerializer(buff) & ud;

	user_basic_define_no_construct _ud;
	WUnserializer(buff) & _ud;

	EXPECT_EQ(_ud.m_i, 1);
	EXPECT_EQ(_ud.m_c, 5);
}

#endif