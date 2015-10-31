/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wserialize.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ���˶����л����Ĺ��ܵİ�װ��ʹ֮ʹ�ø�����
					��Ҫʵ��������archive�࣬������<<��>>��&��������
					ʹ���ǲ�����std::coutһ������
  ����  ����:   
******************************************************************************/
#ifndef _WSERIALIZE_H_
#define _WSERIALIZE_H_

#include "wserializeprivate.h"

/** 
 \brief                 ������һ��ģ�������ֵģ�ͣ���ʵ���˶�һ������ļ򵥰�װ
\details   
 \author    ����
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
	\remark    ������ģ�͵ĳ�ֵ 
	*/
	explicit WSingleValueModel(value_type v = value_type()) : _value(v) {}

	/**
	\brief      value
	\Access    public 
	\retval     value_type
	\remark    ��ȡģ�͵�ֵ 
	*/
	inline value_type value() const { return _value; }

	/**
	\brief      setValue
	\Access    public 
	\param  const value_type & v
	\retval     void
	\remark    ����ģ�͵���ֵ 
	*/
	inline void setValue(const value_type& v) { _value = v; }

private:
	value_type _value;
};

/** 
 \brief                 ���������л�archive����
\details   
 \author    ����
\date      2013/05/23
*/
typedef WSingleValueModel<char*> WSerializer;

/** 
 \brief                 �����˷����л�archive����
\details   
 \author    ����
\date      2013/05/23
*/
typedef WSingleValueModel<const char*> WUnserializer;

/** 
 \brief                 �����˻�ȡ�����С��archive����
\details   
 \author    ����
\date      2013/05/23
*/
typedef WSingleValueModel<size_t> WSizeHelper;

/**
\brief      operator<<
\Access    public 
\param  WSerializer & serializer
\param  const T & t
\retval     WSerializer&
\remark    ΪWSerializer����operator<< 
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
\remark    ΪWUnserializer����operator>> 
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
\remark    ΪWSizeHelper����operator<< 
*/
template<class T>
inline WSizeHelper& operator<<(WSizeHelper& sizeHelper, const T& t)
{
	sizeHelper.setValue(sizeHelper.value() + serialize_size(t));
	return sizeHelper;
}

/** 
 \brief                 ������һ������ģ����WArchiveHelper
\details		������ڵ����ɣ�WSerializer��WUnserializer��WSizeHelper�����߶���Ĳ��������ֱ�Ϊ
				<<��>>��<<����ʽ�ϲ�һ�£���WArchiveHelper�������߽��м򵥵İ�װ����Ϊ���ߵĴ����࣬
				ʹ������������ʽ�Ͼ��е��ýӿڵ�һ����
				��������������ͷֱ�����ػ�
 \author    ����
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
\remark    �˽ӿ������л����ܵ��ܵ���� 
*/
template<class Archive, typename T>
inline Archive& operator&(Archive& ar, T& t)
{
	return WArchiveHelper<Archive>()(ar, t);
}

#endif