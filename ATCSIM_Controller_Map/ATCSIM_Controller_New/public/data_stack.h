#pragma once
#include "sim_net_def.h"


class data_buffer;
class data_stack
{
private:

	int m_min_size ;
	int m_min_free_size ;
	int m_max_free_size ;
	//
	int m_size;		//可用数据长度
	//数据缓冲区
	char*	m_buffer;
	//
	char*   m_current;
	//当前数据长度---已有数据长度
	int		m_length;
	//当前包尾标记的搜索开始位置
	int      m_searchpos;
	
	enum
	{
		MIN_BUF_SIZE = 16384 ,
		MIN_FREE_SIZE = 0 ,
		MAX_FREE_SIZE = 16384 
	};
public:
	data_stack(int min_size = MIN_BUF_SIZE ,int max_free_size = MAX_FREE_SIZE,int min_free_size = MIN_FREE_SIZE);
	~data_stack();
public:
	bool GetPacket(data_buffer& Buffer);
	//复位操作 
	void Reset(int min_size = MIN_BUF_SIZE ,int max_free_size = MAX_FREE_SIZE,int min_free_size = MIN_FREE_SIZE);
	//判断当前有无完整的包，返回值为包尾的位置，若未找到，则返回-1 
	int EndofPacket();
	//取得当前数据的长度
	int Length ();
	//将开始数据取出，并将后面的数据前移 
	//在尾部追加数据
	int Append (const char* data, int len);
	//将所有数据复制
	int Copy(char ** pdata,int len);
private:
	bool Init(int size,int max_free_size,int min_free_size);
	int  get_first_char();
};