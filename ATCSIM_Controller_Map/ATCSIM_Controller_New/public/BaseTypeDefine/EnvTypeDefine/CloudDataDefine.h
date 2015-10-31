#ifndef _CLOUD_DATA_DEFINE_H_
#define _CLOUD_DATA_DEFINE_H_
#include "public/BaseTypeDefine/PublicTypeDefine.h"
struct ST_CloudData
{
	int   m_iCloudID;    //!<��ID
	EM_CLOUD_TYPE    m_eCloudType;   //!<������
	double    m_dLower;    //!<��ͼ�͸�
	double m_dHeight;    //!<��ͼ�߸�
	bool m_bIsCreateDeletet;//!��������ɾ�� ����true,ɾ��false;
	std::vector<stPoint> m_vCloudArea;   // �Ƶ�����
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCloudID & m_eCloudType & m_dLower & m_dHeight & m_bIsCreateDeletet & m_vCloudArea; 
	}
};
#endif