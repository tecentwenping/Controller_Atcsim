#pragma once
#include "public/data_queue.hpp"
#include <string>
class Messager
{
public:
	static Messager *GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new Messager;
		}
		return m_pInstance;
	}
public:
	void ReadMessage(std::string & msg);
	void AddMessage(const std::string msg);

private:
	Messager();
	~Messager(void);

private:
	boost::shared_ptr<data_queue<std::string>> m_pMSGQueue;
	static Messager *m_pInstance;
};
