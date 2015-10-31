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
	int m_iCloudID;		//!<云ID
	EM_CLOUD_TYPE m_eCloudType;	//!<云类型
	double m_dLower;//!<云团的底高
	double m_dHeight;	//!<云团的高高
	std::vector<stPoint> m_vCloudArea;
	bool m_bCreate;     //!<true为创建，false为删除

private:
	SERIALIZE_PACKET(m_iCloudID  & m_eCloudType & m_dLower & m_dHeight 
		              & m_vCloudArea & m_bCreate);
};