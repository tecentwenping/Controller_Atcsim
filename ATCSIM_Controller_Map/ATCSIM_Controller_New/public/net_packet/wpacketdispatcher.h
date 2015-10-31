#ifndef _WPACKET_DISPATCHER_H_
#define _WPACKET_DISPATCHER_H_

#include <map>
#include "wpackethandler.h"

class CSerial_Base;

class WPacketDispatcher
{
public:
	WPacketDispatcher();
	~WPacketDispatcher();

	void dispatch(const CSerial_Base& pkt);

	template<class Packet, class F>
	bool registerPacketProc(F f);
	template<class Packet, class Target>
	bool registerPacketProc(Target* target, void (Target::*f)(const Packet&));
	template<class Packet>
	bool unregisterPacketProc();

private:
	typedef const char* text_type;
	typedef std::map<text_type, WPacketHandlerBase*> this_map;

	std::map<text_type, WPacketHandlerBase*> _mp;
};

template<class Packet, class F>
bool WPacketDispatcher::registerPacketProc(F f)
{
	if (_mp.find(Packet::GetPacketName()) == _mp.end())
	{
		_mp.insert(std::make_pair(Packet::GetPacketName(), new WPacketHandler<Packet>(f)));
		return true;
	}
	return false;
}

template<class Packet, class Target>
bool WPacketDispatcher::registerPacketProc(Target* target, void (Target::*f)(const Packet&))
{
	if (_mp.find(Packet::GetPacketName()) == _mp.end())
	{
		_mp.insert(std::make_pair(Packet::GetPacketName(), new WPacketHandler<Packet>(target, f)));
		return true;
	}
	return false;
}

template<class Packet>
bool WPacketDispatcher::unregisterPacketProc()
{
	this_map::iterator it = _mp.find(Packet::GetPacketName());
	if (it != _mp.end())
	{
		delete it->second;
		_mp.erase(it);
		return true;
	}
	return false;
}

#endif