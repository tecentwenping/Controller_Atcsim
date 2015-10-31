#pragma once

class data_buffer
{
private:
	char* m_pbuffer;
	size_t m_len;//ʵ�ʳ���	
	size_t m_buffer_size;//���������� 
	const static size_t max_buffer_size = 20;
private:
	void buffer_alloc(size_t size = max_buffer_size);
public:
	data_buffer();
	data_buffer(size_t size);
	data_buffer(const data_buffer & other_buffer);
	~data_buffer();
	
	data_buffer& operator=(const data_buffer& other_buffer);
	
	size_t get_buffer_len();
	char*  get_buffer_pt();
	
	void set_buffer(char * pbuf,size_t len);
	void cat_buffer(char * pbuf,size_t len);
};