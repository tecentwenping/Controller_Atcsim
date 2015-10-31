#pragma once
#include "serial_base.h"
#include "public/site_info.h"
#include "Serialization/wserialize.h"
#include "trainplan_data_objs.h"
#include "public/baseTypeDefine/PublicTypeDefine.h"

class CreateDelCloudPacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CreateDelCloudPacket);
public:
	int m_iCloudID;		//!<��ID
	EM_CLOUD_TYPE m_eCloudType;	//!<������
	double m_dLower;//!<���ŵĵ׸�
	double m_dHeight;	//!<���ŵĸ߸�
	std::vector<stPoint> m_vCloudArea;
	bool m_bCreate;     //!<trueΪ������falseΪɾ��

private:
	SERIALIZE_PACKET(m_iCloudID  & m_eCloudType & m_dLower & m_dHeight 
		              & m_vCloudArea & m_bCreate);
};