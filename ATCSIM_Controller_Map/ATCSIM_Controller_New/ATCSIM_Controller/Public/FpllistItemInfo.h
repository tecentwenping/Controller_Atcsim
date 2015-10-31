#ifndef _FPLLIST_ITEMINFO_H
#define _FPLLIST_ITEMINFO_H

enum HMI_STAT
{
	HMI_NONE = 0,
	HMI_UNCONCERN,
	HMI_PREA,
	HMI_HND_IN,
	HMI_ANNOUNCE,
	HMI_HND_OUT,
	HMI_JURI,
};


class FplListItemInfo
{
public:
	int m_nAcftID;
	std::string m_strMid;        //Ψһ��ʶ��
	int         m_nRowID;        //���������Ϣ��ʾ���к�

	std::string m_strType;
	std::string m_strACID;       //����
	std::string m_strSSR;        //������
	std::string m_strPSource;    //�ƻ���Դ
	std::string m_strPState;     //�ƻ�״̬
	std::string m_strHMIState;   //�˻�����״̬
	std::string m_strCouple;
	std::string m_strRadarID;
	std::string m_strTrackID;
	std::string m_strFplType;
	std::string m_strADDep;
	std::string m_strEtd;
	std::string m_strAtd;
	std::string m_strAddArr;
	std::string m_strETA;
	std::string m_strATA;
	std::string m_strCtrlSec;
	std::string m_strCurSec;
	std::string m_strAcpSec;
	std::string m_strNextSec;
	std::string m_strBPN;
	std::string m_strETN;
	std::string m_strBPX;
	std::string m_strETX;
};



#endif 