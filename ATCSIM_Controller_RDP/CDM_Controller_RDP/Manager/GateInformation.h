#ifndef GATEINFORMATION_H
#define GATEINFORMATION_H
#include "Manager/ReadFile.h"
class CGateInformation:public CFile
{
public:
	CGateInformation();
	~CGateInformation();
	void ReadGateInformation();
	//void ReadInformationFromFile();
};
#endif // GATEINFORMATION_H
