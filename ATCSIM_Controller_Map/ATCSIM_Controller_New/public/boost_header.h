#ifndef _BOOST_HEADER_H
#define _BOOST_HEADER_H

//���ļ���Ҫ�������ֳ��õ�boost��������Ҫ���õ�ͷ�ļ�

#pragma warning(disable:4068)
//singleton
#include <boost/pool/detail/singleton.hpp>
using boost::details::pool::singleton_default;

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/static_assert.hpp>
using namespace boost;


#include <boost/signals2.hpp>
#include <vector>
using namespace boost;
using namespace boost::signals2;

//����boost�з��صĿ�ָ��
#define NULL_PTR(T) (boost::shared_ptr<T>())

#endif