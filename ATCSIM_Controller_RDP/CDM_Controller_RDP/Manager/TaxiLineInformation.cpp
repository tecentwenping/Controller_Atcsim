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
	//存放进场路径点和离场路径点的映射表，key为起点-终点，value为起点到终点的路径点
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
	每一条路径数据总是标准的，其格式为：
	ra1-101p,ra1,ra6,a6x1,a6x2,a6b9,ab10,bb10,p8565,p8569,h5h6,p8567,101c,101p;
	起点-终点：起点到终点要经过的各个点
	*/
	//读取所有的路径
	QStringList qStringList=qStr.split(";",QString::SkipEmptyParts);
	//分割路径
	//“,”分割
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
