#ifndef _WUNARY_FUNCTOR_H_
#define _WUNARY_FUNCTOR_H_

template<class Arg>
class WUnaryFunctorBase
{
public:
	virtual ~WUnaryFunctorBase() {}

	virtual void operator()(Arg arg) const = 0;
};

template<class Arg, class F>
class WUnaryFunctor : public WUnaryFunctorBase<Arg>
{
public:
	WUnaryFunctor(F f) : m_f(f) {}

	virtual void operator()(Arg arg) const { m_f(arg); }

private:
	F m_f;
};

template<class Arg, class Target>
class WUnaryMemfun : public WUnaryFunctorBase<Arg>
{
	typedef void (Target::*handler)(Arg);

public:
	WUnaryMemfun(Target* target, handler h) : m_target(target), m_handler(h) {}

	virtual void operator()(Arg arg) const { (m_target->*m_handler)(arg); }

private:
	Target* m_target;
	handler m_handler;
};

template<class Arg, class Target>
WUnaryMemfun<Arg, Target> unary_memfun(Target* target, void (Target::*h)(Arg))
{
	return WUnaryMemfun<Arg, Target>(target, h);
}

template<class Arg, class Target>
WUnaryMemfun<Arg, Target>* unary_memfun_ptr(Target* target, void (Target::*h)(Arg))
{
	return new WUnaryMemfun<Arg, Target>(target, h);
}

#endif