#ifndef _WFUNCTOR_MANAGER_1_H_
#define _WFUNCTOR_MANAGER_1_H_

#include <map>
#include <boost/foreach.hpp>
#include "wfunctor_1.h"

template<typename A1, typename I = int>
class WFunctorManager_1
{
	typedef std::multimap<I, WFunctorBase_1<A1>*> functors_type;
	typedef typename functors_type::iterator iterator_type;
	typedef typename functors_type::value_type value_type;

public:
	~WFunctorManager_1()
	{
		BOOST_FOREACH(value_type& v, functors_)
		{
			delete v.second;
		}
	}

	template<typename F>
	bool registerFunctor(const I& id, F f)
	{
		return registerPrivate(id, new WFunctor_1<A1, F>(f));
	}

	template<typename Obj, typename R>
	bool registerFunctor(const I& id, Obj& obj, R (Obj::*mf)(A1))
	{
		return registerPrivate(id, new WMemfunFunctor_1<A1, R, Obj>(obj, mf));
	}

	template<typename F>
	size_t unregisterFunctor(F f)
	{
		return unregisterPrivate(functors_.begin(), functors_.end(), new WFunctor_1<A1, F>(f));
	}

	template<typename F>
	size_t unregisterFunctor(const I& id, F f)
	{
		return unregisterPrivate(id, new WFunctor_1<A1, F>(f));
	}

	template<typename Obj>
	size_t unregisterObject(Obj& obj)
	{
		return unregisterObjectPrivate(functors_.begin(), functors_.end(), obj);
	}

	template<typename Obj>
	size_t unregisterObject(const I& id, Obj& obj)
	{
		std::pair<iterator_type, iterator_type> p = functors_.equal_range(id);
		return unregisterObjectPrivate(p.first, p.second, obj);
	}

	template<typename Obj, typename R>
	size_t unregisterFunctor(Obj& obj, R (Obj::*mf)(A1))
	{
		return unregisterPrivate(functors_.begin(), functors_.end(), new WMemfunFunctor_1<A1, R, Obj>(obj, mf));
	}

	template<typename Obj, typename R>
	size_t unregisterFunctor(const I& id, Obj& obj, R (Obj::*mf)(A1))
	{
		return unregisterPrivate(id, new WMemfunFunctor_1<A1, R, Obj>(obj, mf));
	}

	void call(const I& i, A1 a1)
	{
		std::pair<iterator_type, iterator_type> p = functors_.equal_range(i);
		for (; p.first != p.second; ++p.first)
		{
			(*p.first->second)(a1);
		}
	}

private:
	bool registerPrivate(const I& id, WFunctorBase_1<A1>* functor)
	{
		std::pair<iterator_type, iterator_type> p = functors_.equal_range(id);
		for (; p.first != p.second; ++p.first)
		{
			if (functor->equal(*p.first->second))
			{
				delete functor;
				return false;
			}
		}

		functors_.insert(value_type(id, functor));
		return true;
	}

	size_t unregisterPrivate(iterator_type beg, iterator_type end, WFunctorBase_1<A1>* functor)
	{
		size_t count = 0;
		while (beg != end)
		{
			iterator_type i = beg++;
			if (functor->equal(*i->second))
			{
				delete i->second;
				functors_.erase(i);
				++count;
			}
		}

		delete functor;
		return count;
	}

	template<typename Obj>
	size_t unregisterObjectPrivate(iterator_type beg, iterator_type end, Obj& obj)
	{
		size_t count = 0;
		WFunctorBase_1<A1>* functor =	new WMemfunFunctor_1<A1, void, Obj>
			(obj, static_cast<void (Obj::*)(A1)>(0));

		while (beg != end)
		{
			iterator_type i = beg++;
			if (functor->sameObject(*i->second))
			{
				delete i->second;
				functors_.erase(i);
				++count;
			}
		}

		delete functor;
		return count;
	}

	size_t unregisterPrivate(const I& id, WFunctorBase_1<A1>* functor)
	{
		std::pair<iterator_type, iterator_type> p = functors_.equal_range(id);
		return unregisterPrivate(p.first, p.second, functor);
	}

private:
	functors_type functors_;
};

#endif