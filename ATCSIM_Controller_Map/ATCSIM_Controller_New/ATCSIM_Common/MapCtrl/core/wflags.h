/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wflags.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现WFlags模板类
  【其  它】:   
******************************************************************************/
#ifndef _WFLAGS_H_
#define _WFLAGS_H_

/** 
 \brief                 此类主要实现对给定类型的枚举Enum可以轻松的进行位操作
\details  此类的相关运用请参见wenums.h头文件 
 \author    陈龙
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
	\remark    赋值 
	*/
	inline WFlags &operator=(const WFlags &f) { i = f.i; return *this; }

	/**
	\brief      operator&=
	\Access    public 
	\param  int mask
	\retval     WFlags &
	\remark    与操作 
	*/
	inline WFlags &operator&=(int mask) { i &= mask; return *this; }
	inline WFlags &operator&=(unsigned int mask) { i &= mask; return *this; }

	/**
	\brief      operator|=
	\Access    public 
	\param  WFlags f
	\retval     WFlags &
	\remark    或操作 
	*/
	inline WFlags &operator|=(WFlags f) { i |= f.i; return *this; }
	inline WFlags &operator|=(Enum f) { i |= f; return *this; }

	/**
	\brief      operator^=
	\Access    public 
	\param  WFlags f
	\retval     WFlags &
	\remark    异或操作 
	*/
	inline WFlags &operator^=(WFlags f) { i ^= f.i; return *this; }
	inline WFlags &operator^=(Enum f) { i ^= f; return *this; }

	/**
	\brief      operator int
	\Access    public 
	\retval     
	\remark    转换成整数 
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
	\remark    结果是否为0 
	*/
	inline bool operator!() const { return !i; }

	/**
	\brief      testFlag
	\Access    public 
	\param  Enum f
	\retval     bool
	\remark    测试某个位有没有被设置 
	*/
	inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }

private:
	int i; //代表枚举的位操作结果
};

#define W_DECLARE_FLAGS(Flags, Enum) typedef WFlags<Enum> Flags;

#endif