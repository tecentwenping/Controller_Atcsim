#include "GateInformation.h"
#include "Manager/DataManager.h"
CGateInformation::CGateInformation()
{

}
CGateInformation::~CGateInformation()
{

}
//void CGateInformation::ReadInformationFromFile( )
//{
//	////��ȡͣ��λ��Ϣ
//	//QString strFileName1 = "./T1.txt";
//	//QString strFileName2 = "./T2.txt";
//	////�ֱ��ȡT1��վ¥��T2��վ¥�Ļ�λ��Ϣ
//	//typedef std::vector<QStringList> vecGateInformation;
//	//vecGateInformation vecGateInformation_T1,vecGateInformation_T2;
//	//GetInfoFromFile(strFileName1,vecGateInformation_T1);
//	//GetInfoFromFile(strFileName2,vecGateInformation_T2);
//	//if(!vecGateInformation_T1.empty())
//	//{
//	//	theData::instance().SetGateInformation(vecGateInformation_T1,1);
//	//}
//	//if(! vecGateInformation_T2.empty())
//	//{
//	//	theData::instance().SetGateInformation(vecGateInformation_T2,2);
//	//}
//}

void CGateInformation::ReadGateInformation()
{
    QString gateInfomationFile="./gate.txt";
	typedef std::vector<QStringList> vGateInformation;
	vGateInformation vecGate;
	GetInfoFromFile(gateInfomationFile,vecGate);
	if(!vecGate.empty()){
		theData::instance().GetPublicDataPtr()->SetGateInformation_New(vecGate);
	}
}

