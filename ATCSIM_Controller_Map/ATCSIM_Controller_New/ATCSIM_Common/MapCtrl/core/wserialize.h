#ifndef _WSERIALIZE_H_
#define _WSERIALIZE_H_

#include "wserializeprivate.h"

template<class T>
class WSingleValueModel
{
public:
	typedef T value_type;

	explicit WSingleValueModel(value_type v = value_type()) : _value(v) {}

	inline value_type value() const { return _value; }
	inline void setValue(const value_type& v) { _value = v; }

private:
	value_type _value;
};

typedef WSingleValueModel<char*> WSerializer;
typedef WSingleValueModel<const char*> WUnserializer;
typedef WSingleValueModel<size_t> WSizeHelper;

template<class T>
WSerializer& operator<<(WSerializer& serializer, const T& t)
{
	serializer.setValue(serialize(serializer.value(), t));
	return serializer;
}

template<class T>
WUnserializer& operator>>(WUnserializer& unserializer, T& t)
{
	unserializer.setValue(unserialize(unserializer.value(), t));
	return unserializer;
}

template<class T>
WSizeHelper& operator<<(WSizeHelper& sizeHelper, const T& t)
{
	sizeHelper.setValue(sizeHelper.value() + serialize_size(t));
	return sizeHelper;
}

#endif