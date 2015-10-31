#include "data_buffer.h"

#ifdef _WIN32
#include <memory.h>
#endif
void data_buffer::buffer_alloc(size_t size)
{
	m_pbuffer = new char[size];
	m_buffer_size = size;
	m_len=size;
}
data_buffer::data_buffer()
{
	buffer_alloc();
}
data_buffer::data_buffer(size_t size)
{
	buffer_alloc(size);
}
data_buffer::data_buffer(const data_buffer & other_buffer)
{
	buffer_alloc();
	set_buffer(other_buffer.m_pbuffer,other_buffer.m_len);
}

data_buffer& data_buffer::operator=(const data_buffer& other_buffer)
{
	set_buffer(other_buffer.m_pbuffer,other_buffer.m_len);
	return *this;
}
data_buffer::~data_buffer()
{
	delete[] m_pbuffer;
}
size_t data_buffer::get_buffer_len()
{
	return m_len;
}

char* data_buffer::get_buffer_pt()
{
	return m_pbuffer;
}

void data_buffer::set_buffer(char * pbuf,size_t len)
{
	if (pbuf == 0 || len <= 0)
	{	
		return;
	}
	if (len > m_buffer_size)
	{

		if (m_pbuffer && m_buffer_size > 0)
			delete[] m_pbuffer ;
		m_buffer_size = 0;
		m_len = 0;
		m_pbuffer = new char[len];
		if (m_pbuffer)
			m_buffer_size = len;
	}
	if (m_pbuffer)
	{
		memcpy(m_pbuffer, pbuf, len);
		m_len = len;
	}
}
void data_buffer::cat_buffer(char * pbuf,size_t len)
{
	if (0 == pbuf)
		return;

	if (m_buffer_size < m_len + len)
	{
		char *tmp_buf = new char[m_len];

		memcpy(tmp_buf, m_pbuffer, m_len);
		m_buffer_size = m_len + len;
		delete []m_pbuffer;
		m_pbuffer = new char[m_buffer_size];
		memcpy(m_pbuffer, tmp_buf, m_len);
		delete[] tmp_buf ;

	}


	memcpy(m_pbuffer + m_len, pbuf, len);
	m_len = m_len + len;
}
