#include <gtest/gtest.h>
#include "data_serialization.h"
#include "wserialize.h"
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#define BUFF_SIZE 1024

template<typename Iter1, typename Iter2>
void compair2container(Iter1 beg1, Iter1 end1, Iter2 beg2, Iter2 end2);
template<typename Iter1, typename Iter2>
void compair2container2(Iter1 beg1, Iter1 end1, Iter2 beg2, Iter2 end2);


class DataObjTest : public testing::Test
{
protected:
	void SetUp(){}
	void TearDown(){}

protected:
	char buff[BUFF_SIZE];
};


// 基本POD类型的串行化
TEST_F(DataObjTest, test_base_pod_obj)
{
	memset(buff, 0, BUFF_SIZE);

	// data in
	int i = -100;
	unsigned int ui = 100;
	char c = 'G';
	unsigned char uc = -33;
	short s = -34;
	unsigned short us = 34;
	long l = -25555;
	unsigned ul = 25555;
	double d = 2.50;
	float f = 3.33f;
	std::string str = "This is pod serialization test!";
	bool b = false;

	WSerializer(buff) & i & ui & c & uc & s & us & l & ul & d & f & str & b;
	
	// data out 
	int i_;
	unsigned int ui_;
	char c_;
	unsigned char uc_;
	short s_;
	unsigned short us_;
	long l_;
	unsigned long ul_;
	double d_;
	float f_;
	std::string str_;
	bool b_;

	WUnserializer(buff) & i_ & ui_ & c_ & uc_ & s_ & us_ & l_ & ul_ & d_ & f_ & str_ & b_;

	EXPECT_EQ(i, i_);
	EXPECT_EQ(ui, ui_);
	EXPECT_EQ(c, c_);
	EXPECT_EQ(uc, uc_);
	EXPECT_EQ(s, s_);
	EXPECT_EQ(us, us_);
	EXPECT_EQ(l, l_);
	EXPECT_EQ(ul, ul_);
	EXPECT_EQ(d, d_);
	EXPECT_EQ(f, f_);
	EXPECT_EQ(str, str_);
	EXPECT_EQ(b, b_);
}



TEST_F(DataObjTest, test_standard_container)
{
	memset(buff, 0, BUFF_SIZE);
	
	std::vector<int> v, v_;// int, out
	std::list<std::string> l, l_;
	std::deque<int> deq, deq_;
	std::map<int, std::string> mp, mp_;
	std::multimap<int, std::string> mmp, mmp_;
	std::set<int> st, st_;
	std::multiset<std::string> mst, mst_;
	std::pair<std::string, std::string> pss, pss_;

	// 初始化数据
	v.push_back(20);
	v.push_back(30000);
	v.push_back(-1);

	l.push_back("this");
	l.push_back("is");
	l.push_back("test");

	deq.push_back(5);
	deq.push_back(6);
	deq.push_back(7);

	mp.insert(std::make_pair(1, "hello"));
	mp.insert(std::make_pair(2, "world"));

	mmp.insert(std::make_pair(3, "multimap"));
	mmp.insert(std::make_pair(3, "test"));
	mmp.insert(std::make_pair(1, "gggg"));

	pss = std::make_pair("Hello", "World");

	st.insert(-1);
	st.insert(100);

	mst.insert("Hello");
	mst.insert("World");
	mst.insert("Hello");
	mst.insert("gtest");

	//TEST BY hxl 13.8.2
// 	for (std::map<int, std::string>::iterator iter = mp.begin(); iter != mp.end(); ++iter)
// 	{
// 		mp_.insert(std::make_pair(iter->first, "hxl"));
// 	}
// 
// 	for (std::multimap<int, std::string>::iterator iter = mmp.begin(); iter != mmp.end(); ++iter)
// 	{
// 		mmp_.insert(std::make_pair(iter->first, "hxl"));
// 	}
// 
// 	for (std::set<int>::iterator iter = st.begin(); iter != st.end(); ++iter)
// 	{
// 		st_.insert(0);
// 	}
// 
// 	for (std::multiset<std::string>::iterator iter = mst.begin(); iter != mst.end(); ++iter)
// 	{
// 		mst_.insert("hxl");
// 	}

	WSerializer(buff) & v & l & deq & mp & mmp & st & mst & pss;

	// out 
	WUnserializer(buff) & v_ & l_ & deq_ & mp_ & mmp_ & st_ & mst_ & pss_;

	EXPECT_EQ(v.size(), v_.size());
	compair2container(v.begin(), v.end(), v_.begin(), v_.end());

	EXPECT_EQ(l.size(), l_.size());
	compair2container(l.begin(), l.end(), l_.begin(), l_.end());

	EXPECT_EQ(deq.size(), deq_.size());
	compair2container(deq.begin(), deq.end(), deq_.begin(), deq_.end());

	EXPECT_EQ(mp.size(), mp_.size());
	compair2container2(mp.begin(), mp.end(), mp_.begin(), mp_.end());

	EXPECT_EQ(mmp.size(), mmp_.size());
	compair2container2(mmp.begin(), mmp.end(), mmp_.begin(), mmp_.end());

	EXPECT_EQ(st.size(), st_.size());
	compair2container(st.begin(), st.end(), st_.begin(), st_.end());

	EXPECT_EQ(mst.size(), mst_.size());
	compair2container(mst.begin(), mst.end(), mst_.begin(), mst_.end());

	EXPECT_EQ(pss.first, pss_.first);
	EXPECT_EQ(pss.second, pss_.second);
}

TEST_F(DataObjTest, test_pointer)
{
	memset(buff, 0, BUFF_SIZE);

	int* pInt = new int(220);
	std::string* pStr = new std::string("This is pointer test!");
	char *pChar = new char;
	*pChar = 'X';

	WSerializer(buff) & pInt & pStr & pChar;

	int* pInt_ = new int();
	std::string* pStr_ = new std::string();
	char* pChar_ = new char();

	WUnserializer(buff) & pInt_ & pStr_ & pChar_;

	EXPECT_EQ(*pInt, *pInt_);
	EXPECT_EQ(*pStr, *pStr_);
	EXPECT_EQ(*pChar, *pChar_);
}



TEST_F(DataObjTest, test_shared_ptr)
{
	memset(buff, 0, BUFF_SIZE);

	boost::shared_ptr<int> pInt(new int(200));
	boost::shared_ptr<std::string> pString(new std::string("this is a test"));
	boost::scoped_ptr<int> psInt(new int(-33333));
	boost::scoped_ptr<std::string> psString(new std::string("this is a scoped ptr test!\n"));

	WSerializer(buff) & pInt & pString & psInt & psString;

	boost::shared_ptr<int> pInt_(new int);
	boost::shared_ptr<std::string> pString_(new std::string());
	boost::scoped_ptr<int> psInt_(new int);
	boost::scoped_ptr<std::string> psString_(new std::string());

	WUnserializer(buff) & pInt_ & pString_ & psInt_ & psString_;

	EXPECT_EQ(*pInt, *pInt_);
	EXPECT_EQ(*pString, *pString_);
	EXPECT_EQ(*psInt, *psInt_);
	EXPECT_EQ(*psString, *psString_);
}
TEST_F(DataObjTest, test_array)
{
	memset(buff, 0, BUFF_SIZE);
	int i[] = { 1, 3, 4, 5};
	int i_[4];
	char c[] = {'a', 'b', 'c'};
	std::string str[] = { "hello", "world", "test" };
	std::string str_[3];
	char c_[3];

	WSerializer(buff) & i & str & c;

	WUnserializer(buff) & i_ & str_ & c_;

	compair2container(i, i + 4, i_, i_ + 4);
	compair2container(str, str + 3, str_, str_ + 3);
	compair2container(c, c + 3, c_, c_ + 3);
	std::cout << "array compair: " << memcmp(i, i_, 4 * sizeof(int)) << std::endl;
}

TEST_F(DataObjTest, test_user_define)
{
	memset(buff, 0, BUFF_SIZE);

	user_define u1(5, 'x', "this is user define test", time(0));
	user_define u2(7, 'y', "this is another user define test!", time(0));
	
	complex_user_define cu;
	cu.m_vUserDefine.push_back(u1);
	cu.m_vUserDefine.push_back(u2);

	more_complex_user_define mcu;
	*(mcu.m_pComplexUserDefine) = cu;

	more_complex_user_define mcu2(mcu);


	more_complex_user_define mcus[2];
	mcus[0] = mcu;
	mcus[1] = mcu2;

	WSerializer(buff) & u1 & u2 & cu & mcu & mcus;
	
	size_t in_size = (WSizeHelper() & u1 & u2 & cu & mcu & mcus).value();

	user_define u1_;
	user_define u2_;
	complex_user_define cu_;
	more_complex_user_define mcu_;
	more_complex_user_define mcus_[2];

	WUnserializer(buff) & u1_ & u2_ & cu_ & mcu_ & mcus_;

	size_t out_size = (WSizeHelper() & u1_ & u2_ & cu_ & mcu_ & mcus_).value();

	EXPECT_EQ(u1, u1_);
	EXPECT_EQ(u2, u2_);
	EXPECT_EQ(cu, cu_);
	EXPECT_EQ(mcu, mcu_);
	compair2container(mcus, mcus + 2, mcus_, mcus_ + 2);
	EXPECT_EQ(in_size, out_size);

	std::cout << "test user define serialization buffer size is " << out_size << std::endl;
}

TEST_F(DataObjTest, test_base_derived)
{
	memset(buff, 0, BUFF_SIZE);

	user_define ud(5, 'G', "this is poly test", time(0));
	DerivedA d(5, ud);

	WSerializer(buff) & d;

	DerivedA d_;

	WUnserializer(buff) & d_;

	EXPECT_EQ(d.m_iId, d_.m_iId);
	EXPECT_EQ(d.m_ud, d_.m_ud);
}

TEST_F(DataObjTest, test_alert_info)
{
	/*memset(buff, 0, BUFF_SIZE);

	AlarmInfo alarmInfo;
	alarmInfo.SPI = 1;
	alarmInfo.HJ = 2;
	alarmInfo.CF = 3;
	alarmInfo.EM = 4;
	alarmInfo.STCA = 5;
	alarmInfo.MSAW = 6;
	alarmInfo.DAIW = 7;
	alarmInfo.CLAM = 8;
	alarmInfo.RAM = 9;
	alarmInfo.rvsmAlarm = 10;

	WSerializer(buff) & alarmInfo;

	AlarmInfo alarmInfo_;

	WUnserializer(buff) & alarmInfo_;

	EXPECT_EQ(alarmInfo_.SPI, alarmInfo.SPI);
	EXPECT_EQ(boost::is_pod<AlarmInfo>::value, true);
	EXPECT_EQ(boost::is_class<AlarmInfo>::value, true);*/
	//EXPECT_FALSE(boost::is_class<AlarmInfo>::value);
}


// 针对顺序容器的比较
template<typename Iter1, typename Iter2>
void compair2container(Iter1 beg1, Iter1 end1, Iter2 beg2, Iter2 end2)
{
	while(beg1 != end1 && beg2 != end2)
	{
		//std::cout << "[" << *beg1 << "] == [" << *beg2 << "]" << std::endl;
		EXPECT_EQ(*beg1, *beg2);
		++beg1;
		++beg2;
	}
}


// 针对关联容器的比较
template<typename Iter1, typename Iter2>
void compair2container2(Iter1 beg1, Iter1 end1, Iter2 beg2, Iter2 end2)
{
	while (beg1 != end1)
	{
		std::cout << "key[" << beg1->first << "] == key[" << beg2->first << "]" << std::endl;
		std::cout << "value[" << beg1->second << "] == value[" << beg2->second << "]" << std::endl;

		EXPECT_EQ(beg1->first, beg2->first);
		EXPECT_EQ(beg1->second, beg2->second);

		++beg1;
		++beg2;
	}
}

