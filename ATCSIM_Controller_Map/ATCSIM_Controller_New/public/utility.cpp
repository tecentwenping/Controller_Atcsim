#include <boost/thread/thread.hpp>
#include "utility.h"
#include "sim_net_def.h"
#include "data_buffer.h"
#include "net_packet/serial_base.h"
#include "site_info.h"


namespace utility
{
	void wait_time(unsigned int mill)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(mill));
	}

	site_info get_buffer_siteinfo(data_buffer &Buffer)
	{
		site_info site;
		const char* buf =Buffer.get_buffer_pt();
		memcpy(&site,buf+sizeof(int),sizeof(site_info));
		return site;
	}
	bool encode_buffer(site_info & target,CSerial_Base& Packet,data_buffer &Buffer)
	{
		int size = Packet.GetSize();
		int len =  sizeof(int) + sizeof(site_info) + size +  sizeof(EOP);
		char* buf = new char[len];
		if (buf != 0)
		{	
			//包格式：
			//|长度|SITETYPE|SITEID|数据|结尾|
			memset(buf,0,len);
			memcpy(buf,&len,sizeof(int));
			memcpy(buf+sizeof(int),&target,sizeof(site_info));
			Packet.Serialize(buf+sizeof(int)+sizeof(site_info));
			memcpy(buf+sizeof(int)+sizeof(site_info)+size,EOP,sizeof(EOP));
			Buffer.set_buffer(buf,len);
			delete []buf; 
			return true ;
		}
		return false ;
	}
	
	CSerial_Base* decode_buffer(site_info& target,char* pbuf,int buf_len)
	{

		const char* buf = pbuf;
		int len = buf_len;

		int dataLen ;
		
		//读长度
		memcpy(&dataLen,buf,sizeof(int));
		//校验数据正确
		if (len == dataLen)
		{
			//读SITEID
			memcpy(&target,buf+sizeof(int),sizeof(site_info));
			CSerial_Base* pkt = CPacketFactory::CreatePacketFromBuffer(buf+sizeof(int)+sizeof(site_info));
			return pkt ;
		}
		return 0;
	}

	CSerial_Base* decode_buffer(site_info& target,data_buffer& Buffer)
	{
		return decode_buffer(target,Buffer.get_buffer_pt(),Buffer.get_buffer_len());	
	}
}