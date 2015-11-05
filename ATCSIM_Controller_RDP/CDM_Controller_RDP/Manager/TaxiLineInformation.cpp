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
	std::multimap<QString,QStringList> inTaxLinePointMap,outTaxLinePointMap;
	_GetTaxLineInformation(qInPathFileName,inTaxLinePointMap,1);
	_GetTaxLineInformation(qOutPathFileName,outTaxLinePointMap,2);
	if(!inTaxLinePointMap.empty()){
		theData::instance().SetPathInformation(inTaxLinePointMap,1);
	}
	if(!outTaxLinePointMap.empty()){
		theData::instance().SetPathInformation(outTaxLinePointMap,2);
	}
}

void CTaxiLineInformation::_GetTaxLineInformation( const QString& qFileName,std::multimap<QString,QStringList>& vMap,int flag )
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
	while(Iter!=qStringList.end()-1){
		qMutex.MyLock();
		qTemp=(*Iter).split(",",QString::SkipEmptyParts);
			if(flag==2){
				vMap.insert(std::make_pair(qTemp[1],qTemp));
			}else
			{
				vMap.insert(std::make_pair(qTemp[0],qTemp));
			}
		qMutex.MyUnlock();
		++Iter;
	}
}
