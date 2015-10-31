#include "DataObj.h"

DataObj::DataObj(void)
{
}

DataObj::~DataObj(void)
{
}

int DataObj::GetId()
{
	return -1;
}

int DataObj::GetOwnerId()
{
	return -1;
}

string DataObj::GetDisplayLabel()
{
	return "";
}

string DataObj::GetObjectName()
{
	return "DataObj";
}

bool DataObj::IsEqual(DataObj *dataobj)
{
	return false;
}
void DataObj::Copy(DataObj *dataobj)
{

}

void DataObj::ReadFromBuffer(const char* pBuffer, int &iOffSize)
{

}

void DataObj::WriteToBuffer(char* pBuffer, int &iOffSize)
{
	
}

int DataObj::GetBufferSize()
{
	return 0;
}