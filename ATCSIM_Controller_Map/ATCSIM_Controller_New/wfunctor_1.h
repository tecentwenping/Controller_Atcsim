#ifndef _WFUNCTOR_1_H_
#define _WFUNCTOR_1_H_

template<typename A1>
class WFunctorBase_1
{
public:
	virtual ~WFunctorBase_1() {}

	virtual void operator()(A1 a1) = 0;

	virtual bool equal(const WFunctorBase_1<A1>& other) const = 0;
	virtual bool sameObject(const WFunctorBase_1<A1>&) const { return false; }
};

template<typename A1, typename F>
class WFunctor_1 : public WFunctorBase_1<A1>
{
public:
	explicit WFunctor_1(F& f) : f_(f) {}

	virtual void operator()(A1 a1) { f_(a1); }

	virtual bool equal(const WFunctorBase_1<A1>& other) const
	{
		const WFunctor_1<A1, F>* p = dynamic_cast<const WFunctor_1<A1, F>*>(&other);
		return p && (&p->f_ == &f_);
	}

private:
	F& f_;
};

template<typename A1, typename Obj>
class WMemfunBase_1 : public WFunctorBase_1<A1>
{
public:
	explicit WMemfunBase_1(Obj& obj) : obj_(obj) {}

	Obj& getObject() const { return obj_; }

private:
	Obj& obj_;
};

template<typename A1, typename R, typename Obj>
class WMemfunFunctor_1 : public WMemfunBase_1<A1, Obj>
{
public:
	typedef R (Obj::*memfun)(A1);

	WMemfunFunctor_1(Obj& obj, memfun mf) : WMemfunBase_1(obj), mf_(mf) {}

	virtual void operator()(A1 a1) { (getObject().*mf_)(a1); }

	virtual bool equal(const WFunctorBase_1<A1>& other) const
	{
		const WMemfunFunctor_1<A1, R, Obj>* p  = 
			dynamic_cast<const WMemfunFunctor_1<A1, R, Obj>*>(&other);
		return p && (&getObject() == &p->getObject()) && (mf_ == p->mf_);
	}

	virtual bool sameObject(const WFunctorBase_1<A1>& other) const 
	{ 
		const WMemfunBase_1<A1, Obj>* p  = 
			dynamic_cast<const WMemfunBase_1<A1, Obj>*>(&other);
		return p && (&getObject() == &p->getObject());
	}

private:
	memfun mf_;
};

#endif