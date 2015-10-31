#include "MemcacheService.h"
#include <iostream>

static void memcached_free_temporary_value(memcached_st*, void* mem)
{
	free(mem);
}

MemcacheService::MemcacheService(void) :
	m_memc(NULL),
	m_server(NULL),
	m_expiration(0),
	m_flags(0),
	m_ip(NULL),
	m_port(0),
	m_bConnected(false)
{
}

MemcacheService::~MemcacheService(void)
{
}

bool MemcacheService::Connect(const char *ip, unsigned int port)
{
	bool bret = false;
	m_ip = ip;
	m_port = port;
	m_memc = memcached_create(NULL);
	m_memc->call_free = memcached_free_temporary_value;
	//m_server = memcached_server_list_append(NULL,"localhost",11211,&m_rc);
	m_server = memcached_server_list_append(NULL,m_ip,m_port,&m_rc);
	m_rc = memcached_server_push(m_memc,m_server);
	memcached_server_list_free(m_server);
	m_rc = memcached_behavior_set(m_memc, MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT, 0);	//连接超时
	m_rc = memcached_behavior_set(m_memc, MEMCACHED_BEHAVIOR_RCV_TIMEOUT, 0);		//读超时
	m_rc = memcached_behavior_set(m_memc, MEMCACHED_BEHAVIOR_SND_TIMEOUT, 0);		//写超时

	//测试连接是否成功
	m_rc = memcached_set(m_memc, "__test_server__", sizeof("__test_server__")-1, 
		"test", sizeof("test")-1, 2, 0);
	if (m_rc != MEMCACHED_SUCCESS)
	{
		memcached_free(m_memc);
		m_bConnected = false;//连接失败
		bret = false;
	}
	else
	{
		m_bConnected = true;//连接成功
		bret = true;
	}

	return bret;
}

bool MemcacheService::SetData(string key, const char *value, size_t value_length)
{
	if (m_memc == NULL || !m_bConnected)
	{
		return false;
	}

	m_rc = memcached_set(m_memc,key.c_str(),key.length(),value,value_length,m_expiration,m_flags);
	return m_rc==MEMCACHED_SUCCESS ? true : false;
}

char *MemcacheService::GetData(string key)
{
	if (m_memc == NULL || !m_bConnected)
	{
		return NULL;
	}

	size_t value_length;
	char* result = memcached_get(m_memc,key.c_str(),key.length(),&value_length,&m_flags,&m_rc);
	return m_rc == MEMCACHED_SUCCESS ? result : NULL;
}

bool MemcacheService::DelData(string key)
{
	if (m_memc == NULL || !m_bConnected)
	{
		return false;
	}

	m_rc = memcached_delete(m_memc,key.c_str(),key.length(),m_expiration);
	return m_rc == MEMCACHED_SUCCESS ? true : false;
}

bool MemcacheService::Flush()
{
	if (m_memc == NULL || !m_bConnected)
	{
		return false;
	}

	m_rc = memcached_flush(m_memc,m_expiration);
	return m_rc == MEMCACHED_SUCCESS ? true : false;
}

void MemcacheService::Free(void* mem)
{
	if (m_memc && m_memc->call_free)
	{
		(m_memc->call_free)(m_memc, mem);
	}
}