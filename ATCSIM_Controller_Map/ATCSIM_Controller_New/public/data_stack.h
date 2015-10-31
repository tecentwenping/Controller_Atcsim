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
	int m_size;		//�������ݳ���
	//���ݻ�����
	char*	m_buffer;
	//
	char*   m_current;
	//��ǰ���ݳ���---�������ݳ���
	int		m_length;
	//��ǰ��β��ǵ�������ʼλ��
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
	//��λ���� 
	void Reset(int min_size = MIN_BUF_SIZE ,int max_free_size = MAX_FREE_SIZE,int min_free_size = MIN_FREE_SIZE);
	//�жϵ�ǰ���������İ�������ֵΪ��β��λ�ã���δ�ҵ����򷵻�-1 
	int EndofPacket();
	//ȡ�õ�ǰ���ݵĳ���
	int Length ();
	//����ʼ����ȡ�����������������ǰ�� 
	//��β��׷������
	int Append (const char* data, int len);
	//���������ݸ���
	int Copy(char ** pdata,int len);
private:
	bool Init(int size,int max_free_size,int min_free_size);
	int  get_first_char();
};