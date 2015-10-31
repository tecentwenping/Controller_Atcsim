#include "Mutex.h"

CQMutex::CQMutex()

{
	qLockMutex=new QMutex;
	

}

CQMutex::~CQMutex()
{
	qLockMutex->unlock();
	delete qLockMutex;

}

void CQMutex::MyLock()
{
    qLockMutex->lock();
}

void CQMutex::MyUnlock()
{
   qLockMutex->unlock();
}
