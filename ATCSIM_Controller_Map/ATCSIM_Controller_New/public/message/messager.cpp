#include "messager.h"
Messager * Messager::m_pInstance = NULL;
Messager::Messager():m_pMSGQueue(new data_queue<std::string>(40))
{
}

Messager::~Messager(void)
{
}

void Messager::ReadMessage(std::string & msg)
{
	m_pMSGQueue->read(&msg);
}
void Messager::AddMessage(const std::string msg)
{
 	std::string msgTemp = msg;
 	m_pMSGQueue->write(msgTemp);
}