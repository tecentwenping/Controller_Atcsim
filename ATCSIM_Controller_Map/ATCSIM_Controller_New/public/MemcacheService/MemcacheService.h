/*
* Copyright (c) 2013,四川川大智胜软件股份有限公司仿真模拟部
* All rights reserved.
*
* 文件名称：MemcacheService.h
* 功能介绍：memcached服务封装类，实现连接、保存、获取、删除数据功能
* 当前版本：1.0
* 作者：lijin
* 完成日期：2013年1月8日
*/

/*******************************use demo*********************************
1.在属性页中添加头文件路径：“../../public/MemcacheService”和“../../public/MemcacheService/include”
2.添加库文件路径：../../public/MemcacheService/lib
  【注意】1、2项前面的“../”视路径深度而定。
3.添加库文件：libmemcached.lib
4.【重要】本头文件需在所有boost头文件之前被包含（最好在所有头文件之前包含），否则会出现类型冲突
5.将libmemcached.dll拷贝到Debug和Release文件夹
6.编译、运行
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
	* 函数介绍：连接memcached服务器
	* 输入参数：const char *ip		memcached服务器ip地址
	*			unsigned int port	memcached服务器监听端口号
	* 输出参数：无
	* 返 回 值：true				连接成功
	*			false				连接失败//1检查服务是否启动//2检查服务是否安装
	*/
	bool Connect(const char *ip, unsigned int port);

	/*
	* 函数介绍：保存数据
	* 输入参数：string key			主键值
	*			const char *value	数据值
	*			size_t value_length	数据长度
	* 输出参数：无
	* 返 回 值：true				保存成功
	*			false				保存失败
	*/
	bool SetData(string key, const char *value, size_t value_length);

	/*
	* 函数介绍：获取数据
	* 输入参数：string key			主键值
	* 输出参数：无
	* 返 回 值：非NULL				获取成功，即返回获取的数据
	*			NULL				获取失败
	*/
	char *GetData(string key);

	/*
	* 函数介绍：删除数据
	* 输入参数：string key			主键值
	* 输出参数：无
	* 返 回 值：true				删除成功
	*			false				删除失败
	*/
	bool DelData(string key);

	/*
	* 函数介绍：使所有item无效
	* 输入参数：无
	* 输出参数：无
	* 返 回 值：true				执行成功
	*			false				执行失败
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
	bool m_bConnected;//连接成功标志
};

#endif /*_MEMECACHE_SERVICE_H_*/