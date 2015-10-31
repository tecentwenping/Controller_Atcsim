/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wserialize.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现了对序列化核心功能的包装，使之使用更方便
					主要实现了三种archive类，并重载<<，>>，&操作符，
					使它们操作像std::cout一样流畅
  【其  它】:   
******************************************************************************/
#ifndef _WSERIALIZE_H_
#define _WSERIALIZE_H_

#include "wserializeprivate.h"

/** 
 \brief                 定义了一个模板类代表单值模型，它实现了对一个对象的简单包装
\details   
 \author    陈龙
\date      2013/05/23
*/
template<class T>
class WSingleValueModel
{
public:
	typedef T value_type;

	/**
	\brief      WSingleValueModel
	\Access    public 
	\param  value_type v
	\retval     
	\remark    定义了模型的初值 
	*/
	explicit WSingleValueModel(value_type v = value_type()) : _value(v) {}

	/**
	\brief      value
	\Access    public 
	\retval     value_type
	\remark    获取模型的值 
	*/
	inline value_type value() const { return _value; }

	/**
	\brief      setValue
	\Access    public 
	\param  const value_type & v
	\retval     void
	\remark    设置模型的新值 
	*/
	inline void setValue(const value_type& v) { _value = v; }

private:
	value_type _value;
};

/** 
 \brief                 定义了序列化archive类型
\details   
 \author    陈龙
\date      2013/05/23
*/
typedef WSingleValueModel<char*> WSerializer;

/** 
 \brief                 定义了反序列化archive类型
\details   
 \author    陈龙
\date      2013/05/23
*/
typedef WSingleValueModel<const char*> WUnserializer;

/** 
 \brief                 定义了获取对象大小的archive类型
\details   
 \author    陈龙
\date      2013/05/23
*/
typedef WSingleValueModel<size_t> WSizeHelper;

/**
\brief      operator<<
\Access    public 
\param  WSerializer & serializer
\param  const T & t
\retval     WSerializer&
\remark    为WSerializer定义operator<< 
*/
template<class T>
inline WSerializer& operator<<(WSerializer& serializer, const T& t)
{
	serializer.setValue(serialize(serializer.value(), t));
	return serializer;
}

/**
\brief      operator>>
\Access    public 
\param  WUnserializer & unserializer
\param  T & t
\retval     WUnserializer&
\remark    为WUnserializer定义operator>> 
*/
template<class T>
inline WUnserializer& operator>>(WUnserializer& unserializer, T& t)
{
	unserializer.setValue(unserialize(unserializer.value(), t));
	return unserializer;
}

/**
\brief      operator<<
\Access    public 
\param  WSizeHelper & sizeHelper
\param  const T & t
\retval     WSizeHelper&
\remark    为WSizeHelper定义operator<< 
*/
template<class T>
inline WSizeHelper& operator<<(WSizeHelper& sizeHelper, const T& t)
{
	sizeHelper.setValue(sizeHelper.value() + serialize_size(t));
	return sizeHelper;
}

/** 
 \brief                 定义了一个帮助模板类WArchiveHelper
\details		此类存在的理由：WSerializer，WUnserializer，WSizeHelper这三者定义的操作符（分别为
				<<，>>，<<）形式上不一致，而WArchiveHelper对这三者进行简单的包装，成为三者的代理类，
				使它们三者在形式上具有调用接口的一致性
				下面针对三种类型分别进行特化
 \author    陈龙
\date      2013/05/23
*/
template<class Archive>
struct WArchiveHelper
{
	template<typename T>
	inline Archive& operator()(Archive& ar, T&)
	{
		return ar;
	}
};

template<>
struct WArchiveHelper<WSerializer>
{
	template<typename T>
	inline WSerializer& operator()(WSerializer& ar, T& t)
	{
		return ar << t;
	}
};

template<>
struct WArchiveHelper<WUnserializer>
{
	template<typename T>
	inline WUnserializer& operator()(WUnserializer& ar, T& t)
	{
		return ar >> t;
	}
};

template<>
struct WArchiveHelper<WSizeHelper>
{
	template<typename T>
	inline WSizeHelper& operator()(WSizeHelper& ar, T& t)
	{
		return ar << t;
	}
};

/**
\brief      operator&
\Access    public 
\param  Archive & ar
\param  T & t
\retval     Archive&
\remark    此接口是序列化功能的总的入口 
*/
template<class Archive, typename T>
inline Archive& operator&(Archive& ar, T& t)
{
	return WArchiveHelper<Archive>()(ar, t);
}

#endif