#include "serial_base.h"
#include "wpacketdispatcher.h"

WPacketDispatcher::WPacketDispatcher()
{
}

WPacketDispatcher::~WPacketDispatcher()
{
	while (!_mp.empty())
	{
		this_map::iterator it = _mp.begin();
		delete it->second;
		_mp.erase(it);
	}
}

void WPacketDispatcher::dispatch(const CSerial_Base& pkt)
{
	std::string name = pkt.GetPacketClassInfo()->m_lpszPacketName;
	this_map::const_iterator cit = _mp.find(pkt.GetPacketClassInfo()->m_lpszPacketName);
	if (cit != _mp.end())
	{
		pkt.callback(cit->second, pkt);
	}
}