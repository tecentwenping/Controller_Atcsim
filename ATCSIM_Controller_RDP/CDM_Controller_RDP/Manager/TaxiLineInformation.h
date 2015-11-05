#ifndef TAXILINEINFORMATION_H
#define TAXILINEINFORMATION_H

#include <QObject>
#include "Manager/ReadFile.h"
class CTaxiLineInformation : public CFile
{
	

public:
	CTaxiLineInformation();
	~CTaxiLineInformation();
	/**************************************************************************
	*��������GetTaxiLineInformation
	*�������ܣ���ȡ�����Ѿ����úõĻ��е��������ra1��ra8��ÿһ��ͣ��λ�Ļ���
	·�����Ѿ�ͨ���������ú��ˣ�����������ͬ���ļ����棬ֻ��Ҫ��ȡ�ļ����ݣ���
	���ڴ��У�����Ҫ��ʱ���ü���.
	*��������
	**************************************************************************/
	void GetTaxiLineInformation();

private:
	void _GetTaxLineInformation(const QString& qFileName,std::multimap<QString,QStringList>& vMap,int flag);
	
};

#endif // TAXILINEINFORMATION_H
