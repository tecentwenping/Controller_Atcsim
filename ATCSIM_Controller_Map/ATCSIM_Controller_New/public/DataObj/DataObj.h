#ifndef _DATA_OBJ_H_
#define _DATA_OBJ_H_

#include <vector>
#include <string>
using namespace std;
#include "Serialization/wserialize.h"

class DataObj
{
public:
	DataObj(void);
	virtual ~DataObj(void);

	//ͨ�÷���
	virtual int GetId();
	virtual int GetOwnerId();
	virtual string GetDisplayLabel();
	virtual string GetObjectName();

	virtual bool IsEqual(DataObj *dataobj);
	virtual void Copy(DataObj *dataobj);

	//���л�����
	virtual void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	virtual void WriteToBuffer(char* pBuffer, int &iOffSize);
	virtual int GetBufferSize();

};


#endif
