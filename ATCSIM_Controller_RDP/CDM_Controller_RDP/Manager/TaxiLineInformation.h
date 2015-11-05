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
	*函数名：GetTaxiLineInformation
	*函数功能：读取离线已经配置好的滑行道，降落点ra1，ra8到每一个停机位的滑行
	路径都已经通过离线配置好了，放在两个不同的文件里面，只需要读取文件内容，放
	在内存中，等需要的时候用即可.
	*变量：空
	**************************************************************************/
	void GetTaxiLineInformation();

private:
	void _GetTaxLineInformation(const QString& qFileName,std::multimap<QString,QStringList>& vMap,int flag);
	
};

#endif // TAXILINEINFORMATION_H
