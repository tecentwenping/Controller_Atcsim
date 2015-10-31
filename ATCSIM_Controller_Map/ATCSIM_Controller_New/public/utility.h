#pragma once

class data_buffer;
class CSerial_Base;
struct site_info;

namespace utility
{
	void wait_time(unsigned int mill);
	bool encode_buffer(site_info& target,CSerial_Base& Packet,data_buffer& Buffer);
	CSerial_Base* decode_buffer(site_info& target,data_buffer& Buffer);
	CSerial_Base* decode_buffer(site_info& target,char* pbuf,int buf_len);
	site_info get_buffer_siteinfo(data_buffer &Buffer);
}


