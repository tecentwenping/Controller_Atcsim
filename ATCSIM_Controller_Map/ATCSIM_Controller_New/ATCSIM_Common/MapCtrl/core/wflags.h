/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wflags.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ��WFlagsģ����
  ����  ����:   
******************************************************************************/
#ifndef _WFLAGS_H_
#define _WFLAGS_H_

/** 
 \brief                 ������Ҫʵ�ֶԸ������͵�ö��Enum�������ɵĽ���λ����
\details  ��������������μ�wenums.hͷ�ļ� 
 \author    ����
\date      2013/05/23
*/
template<typename Enum>
class WFlags
{
public:
	typedef Enum enum_type;
	inline WFlags() : i(0) {}
	inline WFlags(int a) : i(a) {}
	inline WFlags(const WFlags &f) : i(f.i) {}
	inline WFlags(Enum f) : i(f) {}

	/**
	\brief      operator=
	\Access    public 
	\param  const WFlags & f
	\retval     WFlags &
	\remark    ��ֵ 
	*/
	inline WFlags &operator=(const WFlags &f) { i = f.i; return *this; }

	/**
	\brief      operator&=
	\Access    public 
	\param  int mask
	\retval     WFlags &
	\remark    ����� 
	*/
	inline WFlags &operator&=(int mask) { i &= mask; return *this; }
	inline WFlags &operator&=(unsigned int mask) { i &= mask; return *this; }

	/**
	\brief      operator|=
	\Access    public 
	\param  WFlags f
	\retval     WFlags &
	\remark    ����� 
	*/
	inline WFlags &operator|=(WFlags f) { i |= f.i; return *this; }
	inline WFlags &operator|=(Enum f) { i |= f; return *this; }

	/**
	\brief      operator^=
	\Access    public 
	\param  WFlags f
	\retval     WFlags &
	\remark    ������ 
	*/
	inline WFlags &operator^=(WFlags f) { i ^= f.i; return *this; }
	inline WFlags &operator^=(Enum f) { i ^= f; return *this; }

	/**
	\brief      operator int
	\Access    public 
	\retval     
	\remark    ת�������� 
	*/
	inline operator int() const { return i; }

	inline WFlags operator|(WFlags f) const { WFlags g; g.i = i | f.i; return g; }
	inline WFlags operator|(Enum f) const { WFlags g; g.i = i | f; return g; }
	inline WFlags operator^(WFlags f) const { WFlags g; g.i = i ^ f.i; return g; }
	inline WFlags operator^(Enum f) const { WFlags g; g.i = i ^ f; return g; }
	inline WFlags operator&(int mask) const { WFlags g; g.i = i & mask; return g; }
	inline WFlags operator&(unsigned int mask) const { WFlags g; g.i = i & mask; return g; }
	inline WFlags operator&(Enum f) const { WFlags g; g.i = i & f; return g; }
	inline WFlags operator~() const { WFlags g; g.i = ~i; return g; }

	/**
	\brief      operator!
	\Access    public 
	\retval     bool
	\remark    ����Ƿ�Ϊ0 
	*/
	inline bool operator!() const { return !i; }

	/**
	\brief      testFlag
	\Access    public 
	\param  Enum f
	\retval     bool
	\remark    ����ĳ��λ��û�б����� 
	*/
	inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }

private:
	int i; //����ö�ٵ�λ�������
};

#define W_DECLARE_FLAGS(Flags, Enum) typedef WFlags<Enum> Flags;

#endif