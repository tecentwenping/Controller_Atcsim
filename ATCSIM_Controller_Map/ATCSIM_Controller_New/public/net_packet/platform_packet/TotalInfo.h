/******************************************************************************
��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
���ļ�����:   TotalInfo.h
����  �ߡ�:   @lijin
����  ����:   1.0
��������ڡ�: 2013-8-12
����  ����:   �������ȫ����Ϣ(�������˽ṹ��Ϣ)

����  ����:   
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
	site_info m_site_info;					//!<ϯλ��Ϣ
	std::string m_strIP;					//!<��ϯλip
	int m_nPort;							//!<��ϯλ����port
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, DataServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort;
}

//////////////////////////////////////////////////////////////////////////
struct MemcacheServerInfo
{
	site_info m_site_info;					//!<ϯλ��Ϣ
	std::string m_strIP;					//!<memcached�������ip
	int m_nPort;							//!<memcached����������port
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, MemcacheServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort;
}

//////////////////////////////////////////////////////////////////////////
struct CenterInfo
{
	site_info m_site_info;					//!<ϯλ��Ϣ
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, CenterInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info;
}

//////////////////////////////////////////////////////////////////////////
//���ķ�����Ϣ��Ŀǰ����ATG��
struct ServiceInfo
{
	site_info m_site_info;					//!<ϯλ��Ϣ
	bool m_bUsed;							//!<�Ƿ��ѱ�ʹ�ã����Ƿ��Ѽ�����飩
	int m_nExServerID;						//!<����ʹ�ã������������ExServerID
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, ServiceInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_bUsed & ud.m_nExServerID;
}

//////////////////////////////////////////////////////////////////////////
struct ClientSiteInfo
{
	site_info m_site_info;					//!<ϯλ��Ϣ
	bool m_bUsed;							//!<�Ƿ��ѱ�ʹ�ã����Ƿ��Ѽ�����飩
	int m_nExServerID;						//!<����ʹ�ã������������ExServerID
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, ClientSiteInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_bUsed & ud.m_nExServerID;
}

//////////////////////////////////////////////////////////////////////////
struct ExServerInfo
{
	site_info m_site_info;					//!<ϯλ��Ϣ
	std::string m_strIP;					//!<��ϯλip
	short m_nPort;							//!<��ϯλ����port
	bool m_bUsed;							//!<�Ƿ��ѱ�ʹ�ã����Ƿ��Ѽ�����飩
	std::vector<ServiceInfo> m_vServiceInfo;//!<������ķ���Ⱥ
	std::vector<ClientSiteInfo> m_vClientSiteInfo;//!<����ͻ���ϯλȺ
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, ExServerInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_site_info & ud.m_strIP & ud.m_nPort & ud.m_bUsed & ud.m_vServiceInfo & ud.m_vClientSiteInfo;
}

//////////////////////////////////////////////////////////////////////////
//�������˽ṹ��Ϣ����SwitchServer����
struct TotalInfo
{
	int m_nGroupCount;								//!<��������
	DataServerInfo m_DataServerInfo;				//!<DataServer��Ϣ
	MemcacheServerInfo m_MemcacheServerInfo;		//!<MemcacheServer��Ϣ
	CenterInfo m_CenterInfo;						//!<Center��Ϣ
	std::vector<ServiceInfo> m_vServiceInfo;		//!<vector<���ķ�����Ϣ>
	std::vector<ClientSiteInfo> m_vClientSiteInfo;	//!<vector<�ͻ���ϯλ��Ϣ>��Controller��Pilot��Coach
	std::vector<ExServerInfo> m_vExServerInfo;		//!<vector<������Ϣ>
};

//�ṹ������л�����Ƕ��ʽ��
template<class Archive>
Archive& serialize(Archive& ar, TotalInfo& ud, const unsigned int /*version*/)
{
	return	ar & ud.m_nGroupCount & ud.m_DataServerInfo & ud.m_MemcacheServerInfo & ud.m_CenterInfo \
		& ud.m_vServiceInfo & ud.m_vClientSiteInfo & ud.m_vExServerInfo;
}

//////////////////////////////////////////////////////////////////////////
/** 
 \brief �������˽ṹ��Ϣ�� 
 \details   ��Center���ӽ���ʱ��Switch���͸�Center
\author		@lijin
\date      2013-08-12
*/
class TotalInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(TotalInfoPacket);

public:
	TotalInfo m_totalInfo;					//!<Switch�������˽ṹ
private:
	SERIALIZE_PACKET(m_totalInfo);
};

//////////////////////////////////////////////////////////////////////////
/** 
 \brief ExServer������Ϣ�� 
 \details   ��ExServer����Switch���״����ӻ���Switch�Ͽ����������������ӣ������ͱ�����Ϣ��Switch
\author		@lijin
\date      2013-09-29
*/
class GroupInfoPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(GroupInfoPacket);

public:
	ExServerInfo m_ExServerInfo;			//!<������Ϣ
private:
	SERIALIZE_PACKET(m_ExServerInfo);
};
