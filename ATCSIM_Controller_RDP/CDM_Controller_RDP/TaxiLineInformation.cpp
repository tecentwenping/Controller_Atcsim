#include "TaxiLineInformation.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include "Mutex.h"
#include "Manager/DataManager.h"
CTaxiLineInformation::CTaxiLineInformation() {}
CTaxiLineInformation::~CTaxiLineInformation(){}

void CTaxiLineInformation::GetTaxiLineInformation()
{
	QString qInPathFileName("./offline_in_taxline.txt");
	QString qOutPathFileName("./offline_out_taxline.txt");
	//��Ž���·������볡·�����ӳ���keyΪ���-�յ㣬valueΪ��㵽�յ��·����
	std::map<QString,QStringList> inTaxLinePointMap,outTaxLinePointMap;
	_GetTaxLineInformation(qInPathFileName,inTaxLinePointMap);
	_GetTaxLineInformation(qOutPathFileName,outTaxLinePointMap);
	if(!inTaxLinePointMap.empty()){
		theData::instance().SetPathInformation(inTaxLinePointMap,1);
	}
	if(!outTaxLinePointMap.empty()){
		theData::instance().SetPathInformation(outTaxLinePointMap,2);
	}
}

void CTaxiLineInformation::_GetTaxLineInformation( const QString& qFileName,std::map<QString,QStringList>& vMap )
{
    QFile qFileObj(qFileName);
	assert(qFileObj.open(QIODevice::ReadOnly|QIODevice::Text));
	QTextStream qTextStream(&qFileObj);
	QString qStr=qTextStream.readAll();
	/*
	ÿһ��·���������Ǳ�׼�ģ����ʽΪ��
	ra1-101p,ra1,ra6,a6x1,a6x2,a6b9,ab10,bb10,p8565,p8569,h5h6,p8567,101c,101p;
	���-�յ㣺��㵽�յ�Ҫ�����ĸ�����
	*/
	//��ȡ���е�·��
	QStringList qStringList=qStr.split(";",QString::SkipEmptyParts);
	//�ָ�·��
	//��,���ָ�
	QStringList qTemp;
	CQMutex qMutex;
	QStringList::iterator Iter=qStringList.begin();
	while(Iter!=qStringList.end()){
		qMutex.MyLock();
		qTemp=(*Iter).split(",",QString::SkipEmptyParts);
		vMap.insert(std::make_pair(qTemp[0],qTemp));
		qMutex.MyUnlock();
		++Iter;
	}
}
