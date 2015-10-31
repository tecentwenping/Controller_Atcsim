#ifndef _WPACKET_HANDLER_H_
#define _WPACKET_HANDLER_H_

#include "..\uncopyable.h"
#include "..\wunaryfunctor.h"

class WPacketHandlerBase
{
public:
	virtual ~WPacketHandlerBase() {}
};

template<class Packet>
class WPacketHandler : public WPacketHandlerBase, private WUncopyable
{
public:
	template<class F>
	WPacketHandler(F f) : m_f(new WUnaryFunctor<const Packet&, F>(f)) {}

	template<class Target>
	WPacketHandler(Target* target, void (Target::*h)(const Packet&)) 
		: m_f(new WUnaryMemfun<const Packet&, Target>(target, h)) {}

	virtual ~WPacketHandler() { delete m_f; }

	virtual void dispatch(const Packet& packet) const { (*m_f)(packet);}

private:
	WUnaryFunctorBase<const Packet&>* m_f;
};

#endif