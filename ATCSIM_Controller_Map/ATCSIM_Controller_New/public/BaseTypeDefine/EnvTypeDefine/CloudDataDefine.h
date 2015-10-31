#ifndef _CLOUD_DATA_DEFINE_H_
#define _CLOUD_DATA_DEFINE_H_
#include "public/BaseTypeDefine/PublicTypeDefine.h"
struct ST_CloudData
{
	int   m_iCloudID;    //!<云ID
	EM_CLOUD_TYPE    m_eCloudType;   //!<云类型
	double    m_dLower;    //!<云图低高
	double m_dHeight;    //!<云图高高
	bool m_bIsCreateDeletet;//!创建还是删除 创建true,删除false;
	std::vector<stPoint> m_vCloudArea;   // 云的坐标
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCloudID & m_eCloudType & m_dLower & m_dHeight & m_bIsCreateDeletet & m_vCloudArea; 
	}
};
#endif