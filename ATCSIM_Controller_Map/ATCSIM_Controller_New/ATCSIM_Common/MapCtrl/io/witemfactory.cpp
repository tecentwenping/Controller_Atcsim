#include "../wdllexport.h"
#include "witemfactory.h"
#include "../core/wserialize.h"
#include "../core/wgraphicsitem.h"

char* WItemFactory::serialize(char* buf, const WGraphicsItem& item)
{
	return (WSerializer(buf) << std::string(item.classinfo()->name) << *item.data()).value();
}

size_t WItemFactory::serialize_size(const WGraphicsItem& item)
{
	return (WSizeHelper() << std::string(item.classinfo()->name) << *item.data()).value();
}

const char* WItemFactory::create(const char* buf, WGraphicsItem** item)
{
	std::string classname;
	buf = (WUnserializer(buf) >> classname).value();
	const WItemInfo* info = WItemInfo::begin;
	while (info) //查找创建图元的函数指针
	{
		if (classname == info->name)
		{
			*item = (info->create)();
			buf = (*item)->data()->unserialize(buf);
			break;
		}
		info = info->next;
	}

	return buf;
}