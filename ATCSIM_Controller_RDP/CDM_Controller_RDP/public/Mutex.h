#ifndef CDM_QMUTEX_H
#define CDM_QMUTEX_H

#include <QObject>
#include <QMutex>
class CQMutex : QObject
{
	Q_OBJECT

public:
	CQMutex();
	~CQMutex();
	void MyLock();
	void MyUnlock();
private:
	 QMutex *qLockMutex;//Ëø±äÁ¿

};

#endif // CDM_QMUTEX_H
