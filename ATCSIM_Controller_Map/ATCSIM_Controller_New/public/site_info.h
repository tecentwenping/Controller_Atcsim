#pragma once

#define INVALID_SITE_TYPE -1
#define INVALID_SITE_ID   -1
#define INVALID_TOPIC_PUB 0
#define INVALID_TOPIC_SUB 0

struct site_info
{
	int site_type;
	int site_id;
	int topic_pub;//发布的服务
	int topic_sub;//订阅的服务
	//site_info()
	//{
	//	site_type = INVALID_SITE_TYPE;
	//	site_id =   INVALID_SITE_ID;
	//	topic_pub = INVALID_TOPIC_PUB;
	//	topic_sub = INVALID_TOPIC_SUB;
	//}

	site_info(int type = INVALID_SITE_TYPE, int id = INVALID_SITE_ID, int pub = INVALID_TOPIC_PUB, int sub = INVALID_TOPIC_SUB)
	{
		site_type = type;
		site_id =   id;
		topic_pub = pub;
		topic_sub = sub;
	}

	bool operator == (const site_info& siteID)
	{
		return(site_type == siteID.site_type && site_id == siteID.site_id);
	}

	bool operator != (const site_info &siteID)
	{
		return !(site_type == siteID.site_type && site_id == siteID.site_id);
	}
};

//结构体的序列化（非嵌入式）
template<class Archive>
Archive& serialize(Archive& ar, site_info& ud, const unsigned int version)
{
	return	ar & ud.site_type & ud.site_id & ud.topic_pub & ud.topic_sub;
}
