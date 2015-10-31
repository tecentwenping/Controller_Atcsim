#ifndef _Data_Obj_H_
#define _Data_Obj_H_
#include <string>
#include <vector>
#include <ctime>
#include <assert.h>

class user_basic_define_no_construct
{
public:
	int getInt() {return m_i;} // ���˷�����Ҳ���ԣ�virtual�Ͳ�Ϊpod���ͣ�
	int m_i;
	char m_c;
};

template<class Archive>
Archive& serialize(Archive& ar, user_basic_define_no_construct& ud, const unsigned int version)
{
	assert(false);
	return ar & ud.m_i & ud.m_c;
}

class user_define_has_construct
{
public:
	user_define_has_construct(){}

	int m_i;
	char m_c;
};


class user_define
{
public:
	user_define(){}
	user_define(int i, char c, std::string str, time_t t)
		: m_int(i), m_char(c), m_str(str), m_t(t)
	{

	}


	int m_int;
	char m_char;
	std::string m_str;
	time_t m_t;
};



class complex_user_define
{
public:
	std::vector<user_define> m_vUserDefine;
};



class more_complex_user_define
{
public:
	more_complex_user_define()
	{
		// must define memory for point use
		m_pComplexUserDefine = new complex_user_define;
	}

	~more_complex_user_define()
	{
		if (m_pComplexUserDefine)
		{
			delete m_pComplexUserDefine;
		}
	}
	
	// ��ֵ����
	more_complex_user_define(const more_complex_user_define& ud)
	{
		*this = ud;
	}
	// �������
	void operator=(const more_complex_user_define& ud)
	{
		if(&ud == this)
			return;

		this->m_pComplexUserDefine = new complex_user_define;
		*(this->m_pComplexUserDefine) = *(ud.m_pComplexUserDefine);
	}


	complex_user_define* m_pComplexUserDefine;
};

bool operator==(const user_define& u1, const user_define& u2)
{
	return u1.m_char == u2.m_char && u1.m_int == u2.m_int
		&& u1.m_str == u2.m_str && u1.m_t == u2.m_t;
}

bool operator==(const complex_user_define& u1, const complex_user_define& u2)
{
	size_t size = u1.m_vUserDefine.size();
	if ( size != u2.m_vUserDefine.size() )
	{
		return false;
	}

	for (size_t i = 0; i < size; ++i)
	{
		if (!(u1.m_vUserDefine[i] == u2.m_vUserDefine[i]))
		{
			return false;
		}
	}

	return true;
}

bool operator==(const more_complex_user_define& u1, const more_complex_user_define& u2)
{
	return *(u1.m_pComplexUserDefine) == *(u2.m_pComplexUserDefine);
}


enum ALERM
{
	AL_NONE = 0x0,
    AL_SPI =  0x1,		//�������λ�ø澯
	AL_HJ  =  0x2,		//7500 
	AL_CF  =  0x4,		//7600
	AL_EM  =  0x8,		//7700
	AL_STCA = 0x10,		//��ͻ�澯
	AL_MSAW = 0x20,		//�͸߸澯
	AL_DAIW = 0x40,		//�����澯 ������ ����
	AL_CLAM = 0x80,		//CFL�澯
	AL_RAM  = 0x100,	//ƫ��RAM�澯 jjp 2011-05-20 hb
	AL_RVSM = 0x200,	//δ��׼��δ֪RVSM����Ŀ�����RVSM����
};

// ����������ڴ��л��в���֧�� unsigned int    SPI:1
struct AlarmInfo 
{
	//unsigned int alarm;
	unsigned int    SPI:1;				//�������λ�ø澯
	unsigned int    HJ:1;				//7500 
	unsigned int    CF:1;				//7600
	unsigned int    EM:1;				//7700
	unsigned int    STCA:1;				//��ͻ�澯
	unsigned int    MSAW:1;				//�͸߸澯
	unsigned int    DAIW:1;				//�����澯 ������ ����
	unsigned int    CLAM:1;				//CFL�澯
	unsigned int    RAM:1;				//ƫ��RAM�澯 jjp 2011-05-20 hb
	unsigned int    rvsmAlarm:1;			//δ��׼��δ֪RVSM����Ŀ�����RVSM����


	int    STCAAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  30
	int    MSAWAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  60                        
	int    DAIWAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  0xffe
	int    RVSMAlertTime;		//0-�澯  ��0-Ԥ��ʱ��(��)  0xffe
};

//�ṹ������л�����Ƕ��ʽ��
//template<class Archive>
//Archive& serialize(Archive& ar, AlarmInfo& ud, const unsigned int version)
//{
//	return	ar & ud.SPI & ud.HJ & ud.CF & ud.EM & ud.STCA & ud.MSAW & ud.DAIW & ud.CLAM & ud.RAM
//		& ud.rvsmAlarm & ud.STCAAlertTime & ud.MSAWAlertTime & ud.DAIWAlertTime & ud.RVSMAlertTime;
//}
#endif