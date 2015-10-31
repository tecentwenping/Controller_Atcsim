#include "data_stack.h"
#include "data_buffer.h"

#ifdef _WIN32
#include "memory.h"
#include "string.h"
#endif

data_stack::data_stack(int min_size,int max_free_size,int min_free_size)
{
	m_size = 0 ;
	m_buffer=0;
	Init(min_size,max_free_size,min_free_size); 
}

data_stack::~data_stack()
{
	if ((m_buffer != 0) && (m_size > 0))
		delete[] m_buffer;
	m_buffer = 0 ;
	m_current = m_buffer ;
}

int data_stack::Append(const char *data, int len)
{
	if ((len <= 0) || (data == 0))
		return -1;

	if ((m_size - m_length) < len )
	{
		int size = m_length + len + m_max_free_size ; 
		if (size < m_min_size + m_min_free_size)
			size = m_min_size + m_min_free_size ;
		char* newbuf = new char[size] ;
		if (0 == newbuf)
		{
			return -1 ;
		}
		memset(newbuf,0,size);
		//not any space allocated
		if (m_size == 0)
		{
			memcpy(newbuf,data,len) ;	
		}
		else
		{
			//backup old data
			memcpy(newbuf,m_current,m_length) ;
			//copy new data
			memcpy(newbuf+m_length,data,len) ;
			delete[] m_buffer ;
		}

		m_buffer = newbuf ;
		m_current = m_buffer ;
		m_size = size ;

	}
	else
	{

		if (m_current != m_buffer)
		{
			int back = m_size - (m_current - m_buffer) - m_length ;
			//move data
			if (back < len)
			{
				memcpy(m_buffer,m_current,m_length);
				memset(m_current,0,m_length);
				m_current = m_buffer ;
			}

		}
		memcpy(m_current+m_length,data,len) ;
	}

	m_length += len ;
	return len ;
}



int data_stack::Length()
{
	return m_length;
}


int data_stack::Copy(char ** pdata, int len)
{
	memset(*pdata,0,len);
	if (len < m_length)
	{
		delete[] *pdata;
		*pdata = new char[m_length];
		memset(*pdata,0,m_length);
	}
	memcpy(*pdata,m_buffer,m_length);
	int iLen = m_length ;
	return iLen ;
}

void data_stack::Reset(int min_size,int max_free_size,int min_free_size)
{
	Init(min_size,max_free_size,min_free_size); 
}
int data_stack::get_first_char()
{
	char tmp[]=EOP;
	int size = sizeof(EOP);
	if(size >0)
		return tmp[0];

	return 0; 
}
int data_stack::EndofPacket()
{

	int ch = get_first_char();
	int m_endlen = sizeof(EOP) ;

	int Result = -1;

	char* pos = m_current + m_searchpos;
	while(pos && (m_length - (pos - m_current) >= m_endlen))
	{

		//find the packet end
		if( memcmp( pos , EOP , m_endlen) ==0 )
		{
			Result = (int) (pos -  m_current + 1);
			m_searchpos = 0;
			break ;
		}
		//next search start pos
		pos =(char *)  memchr( pos + 1, ch , m_length - (pos - m_current + 1 ) ) ;
		//pos =(char *)  memchr( pos, ch , m_length - (pos - m_current)) ;
		//
		if (pos)
		{
			m_searchpos = pos - m_current ;
		}
		else
		{
			m_searchpos = m_length ;
		}
	}
	return Result ;
}
bool data_stack::GetPacket(data_buffer &Buffer)
{


	bool Result ;
	int m_endlen = sizeof(EOP) ;
	int pos = EndofPacket() ;
	if (pos == -1 )
	{
		if (((m_size - m_length) > m_max_free_size) && (m_size > (m_min_size + m_min_free_size)))
		{
			int cur_size = m_length + m_max_free_size ;
			if (cur_size < m_min_size + m_min_free_size)
				cur_size = m_min_size + m_min_free_size ;	
			char* newbuf = new char[cur_size] ;
			if (newbuf)
			{
				memset(newbuf,0,cur_size);
				memcpy(newbuf,m_current,m_length);
				if (m_buffer)
					delete[] m_buffer ;
				m_buffer = newbuf ;
				m_current = m_buffer ;
				m_size = cur_size ;
			}
		}
		else
		{
			if (m_buffer != m_current)
			{
				memmove(m_buffer,m_current,m_length);
				memset(m_buffer+m_length,0,m_current - m_buffer);
				m_current = m_buffer ;
			}

		}

		Result = false ;
	}
	else
	{
		int len = pos + m_endlen - 1 ;
		Buffer.set_buffer(m_current,len);
		memset(m_current,0,len);
		m_length -= len ;
		if (m_length == 0)
			m_current = m_buffer ;
		else
			m_current += len ;	
		Result = true ;
	}
	return Result ;
}

bool data_stack::Init(int min_size, int max_free_size,int min_free_size)
{
	m_length = 0;
	m_searchpos = 0 ;
	if (max_free_size > 0)
		m_max_free_size = max_free_size ;
	else
		m_max_free_size = MAX_FREE_SIZE ;
	if (min_free_size > 0)
		m_min_free_size = min_free_size ;
	else
		m_min_free_size = MIN_FREE_SIZE ;


	if (min_size > 0)
	{
		m_min_size = min_size ;
		if (m_size < min_size)
		{
			if (m_buffer)
				delete[] m_buffer ;
			m_buffer = new char[min_size] ;
			if (m_buffer)
			{
				memset(m_buffer,0,min_size) ;
				m_size = min_size ;   
			}
		}

	}
	else
	{

		if (m_buffer)
			delete[] m_buffer ;
		m_buffer = 0 ;		
		m_size = 0 ;
		m_min_size = 0 ;
	}
	m_current = m_buffer ;
	return true ;

}
