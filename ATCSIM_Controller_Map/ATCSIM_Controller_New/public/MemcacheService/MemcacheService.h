/*
* Copyright (c) 2013,�Ĵ�������ʤ����ɷ����޹�˾����ģ�ⲿ
* All rights reserved.
*
* �ļ����ƣ�MemcacheService.h
* ���ܽ��ܣ�memcached�����װ�࣬ʵ�����ӡ����桢��ȡ��ɾ�����ݹ���
* ��ǰ�汾��1.0
* ���ߣ�lijin
* ������ڣ�2013��1��8��
*/

/*******************************use demo*********************************
1.������ҳ�����ͷ�ļ�·������../../public/MemcacheService���͡�../../public/MemcacheService/include��
2.��ӿ��ļ�·����../../public/MemcacheService/lib
  ��ע�⡿1��2��ǰ��ġ�../����·����ȶ�����
3.��ӿ��ļ���libmemcached.lib
4.����Ҫ����ͷ�ļ���������boostͷ�ļ�֮ǰ�����������������ͷ�ļ�֮ǰ�������������������ͳ�ͻ
5.��libmemcached.dll������Debug��Release�ļ���
6.���롢����
************************************************************************/

#ifndef _MEMECACHE_SERVICE_H_
#define _MEMECACHE_SERVICE_H_

#include <string>
#include <libmemcached/memcached.h>

using namespace std;

class MemcacheService
{
public:
	static MemcacheService& Ref()
	{
		static MemcacheService instance;
		return instance;
	}

	static MemcacheService * Ptr()
	{
		return &Ref();
	}

	/*
	* �������ܣ�����memcached������
	* ���������const char *ip		memcached������ip��ַ
	*			unsigned int port	memcached�����������˿ں�
	* �����������
	* �� �� ֵ��true				���ӳɹ�
	*			false				����ʧ��//1�������Ƿ�����//2�������Ƿ�װ
	*/
	bool Connect(const char *ip, unsigned int port);

	/*
	* �������ܣ���������
	* ���������string key			����ֵ
	*			const char *value	����ֵ
	*			size_t value_length	���ݳ���
	* �����������
	* �� �� ֵ��true				����ɹ�
	*			false				����ʧ��
	*/
	bool SetData(string key, const char *value, size_t value_length);

	/*
	* �������ܣ���ȡ����
	* ���������string key			����ֵ
	* �����������
	* �� �� ֵ����NULL				��ȡ�ɹ��������ػ�ȡ������
	*			NULL				��ȡʧ��
	*/
	char *GetData(string key);

	/*
	* �������ܣ�ɾ������
	* ���������string key			����ֵ
	* �����������
	* �� �� ֵ��true				ɾ���ɹ�
	*			false				ɾ��ʧ��
	*/
	bool DelData(string key);

	/*
	* �������ܣ�ʹ����item��Ч
	* �����������
	* �����������
	* �� �� ֵ��true				ִ�гɹ�
	*			false				ִ��ʧ��
	*/
	bool Flush();

	void Free(void* mem);

private:
	MemcacheService(void);
	~MemcacheService(void);
	MemcacheService(const MemcacheService&);//uncopyalbe
	MemcacheService& operator=(const MemcacheService&);//uncopyalbe

private:
	memcached_st *m_memc;
	memcached_return m_rc;
	memcached_server_st *m_server;
	time_t m_expiration;
	unsigned __int32  m_flags;
	const char *m_ip;
	unsigned int m_port;
	bool m_bConnected;//���ӳɹ���־
};

#endif /*_MEMECACHE_SERVICE_H_*/