/******************************************************************************
版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
【文件名】:   TotalInfo.h
【作  者】:   @lijin
【版  本】:   1.0
【完成日期】: 2013-8-12
【描  述】:   接入服务全部信息(分组拓扑结构信息)

【其  它】:   
******************************************************************************/

#pragma once
#include "..\serial_base.h"
#include "site_info.h"
#include <string>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////
struct DataServerInfo
{
	site_info m_site_info;					//!<席位信息
	std::string m_strIP;					//!<本席位ip
	int m_nPort;							//!<本席位监听port
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, DataServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort;
}

//////////////////////////////////////////////////////////////////////////
struct MemcacheServerInfo
{
	site_info m_site_info;					//!<席位信息
	std::string m_strIP;					//!<memcached缓存服务ip
	int m_nPort;							//!<memcached缓存服务监听port
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, MemcacheServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort;
}

//////////////////////////////////////////////////////////////////////////
struct CenterInfo
{
	site_info m_site_info;					//!<席位信息
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, CenterInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info;
}

//////////////////////////////////////////////////////////////////////////
//核心服务信息（目前仅有ATG）
struct ServiceInfo
{
	site_info m_site_info;					//!<席位信息
	bool m_bUsed;							//!<是否已被使用（即是否已加入分组）
	int m_nExServerID;						//!<若被使用，其所属分组的ExServerID
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, ServiceInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_bUsed & ud.m_nExServerID;
}

//////////////////////////////////////////////////////////////////////////
struct ClientSiteInfo
{
	site_info m_site_info;					//!<席位信息
	bool m_bUsed;							//!<是否已被使用（即是否已加入分组）
	int m_nExServerID;						//!<若被使用，其所属分组的ExServerID
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, ClientSiteInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_bUsed & ud.m_nExServerID;
}

//////////////////////////////////////////////////////////////////////////
struct ExServerInfo
{
	site_info m_site_info;					//!<席位信息
	std::string m_strIP;					//!<本席位ip
	short m_nPort;							//!<本席位监听port
	bool m_bUsed;							//!<是否已被使用（即是否已加入分组）
	std::vector<ServiceInfo> m_vServiceInfo;//!<本组核心服务群
	std::vector<ClientSiteInfo> m_vClientSiteInfo;//!<本组客户端席位群
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, ExServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort & ud.m_bUsed & ud.m_vServiceInfo & ud.m_vClientSiteInfo;
}

//////////////////////////////////////////////////////////////////////////
//分组拓扑结构信息，由SwitchServer缓存
struct TotalInfo
{
	int m_nGroupCount;								//!<分组数量
	DataServerInfo m_DataServerInfo;				//!<DataServer信息
	MemcacheServerInfo m_MemcacheServerInfo;		//!<MemcacheServer信息
	CenterInfo m_CenterInfo;						//!<Center信息
	std::vector<ServiceInfo> m_vServiceInfo;		//!<vector<核心服务信息>
	std::vector<ClientSiteInfo> m_vClientSiteInfo;	//!<vector<客户端席位信息>：Controller、Pilot、Coach
	std::vector<ExServerInfo> m_vExServerInfo;		//!<vector<分组信息>
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, TotalInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_nGroupCount & ud.m_DataServerInfo & ud.m_MemcacheServerInfo & ud.m_CenterInfo \
		& ud.m_vServiceInfo & ud.m_vClientSiteInfo & ud.m_vExServerInfo;
}

//////////////////////////////////////////////////////////////////////////
/** 
 \brief 分组拓扑结构信息包 
 \details   当Center连接进入时，Switch发送给Center
\author		@lijin
\date      2013-08-12
*/
class TotalInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TotalInfoPacket);

public:
	TotalInfo m_totalInfo;					//!<Switch分组拓扑结构
private:
	SERIALIZE_PACKET(m_totalInfo);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief ExServer分组信息包 
 \details   当ExServer连接Switch（首次连接或者Switch断开后重启发生的连接），发送本组信息给Switch
\author		@lijin
\date      2013-09-29
*/
class GroupInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(GroupInfoPacket);

public:
	ExServerInfo m_ExServerInfo;			//!<分组信息
private:
	SERIALIZE_PACKET(m_ExServerInfo);
};
