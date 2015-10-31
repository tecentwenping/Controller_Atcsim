/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsproxymanager.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WGraphicsProxyManager模板类，
					并在此基础上定义了新类型WGraphicsItemProxyManager
					WGraphicsLayerProxyManager，WGraphicsItemFilterManager类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_PROXY_MANAGER_H_
#define _WGRAPHICS_PROXY_MANAGER_H_

#include <map>
#include "../wdllimport.h"
#include "wgraphicsitemproxy.h"
#include "wgraphicslayerproxy.h"


/** 
 \brief                 此类主要用来支持给一个对象增加代理的功能
\details   当然还有删除代理，查找代理，获取代理的功能
 \author    陈龙
\date      2013/05/29
*/
template<class proxyee_type, class proxy_type>
class WGraphicsProxyManager
{
public:
	virtual ~WGraphicsProxyManager();

	bool addProxy(proxyee_type* proxyee, const proxy_type& proxy);
	bool removeProxy(proxyee_type* proxyee);
	bool hasProxy(proxyee_type* proxyee) const;
	const proxy_type proxy(proxyee_type* proxyee) const;

private:
	std::map<proxyee_type*, proxy_type> _proxies;
};

template<class proxyee_type, class proxy_type>
WGraphicsProxyManager<proxyee_type, proxy_type>::~WGraphicsProxyManager()
{
}

template<class proxyee_type, class proxy_type>
bool WGraphicsProxyManager<proxyee_type, proxy_type>::addProxy(proxyee_type* proxyee, const proxy_type& proxy)
{
	return _proxies.insert(std::make_pair(proxyee, proxy)).second;
}

template<class proxyee_type, class proxy_type>
bool WGraphicsProxyManager<proxyee_type, proxy_type>::removeProxy(proxyee_type* proxyee)
{
	return _proxies.erase(proxyee) > 0;
}

template<class proxyee_type, class proxy_type>
bool WGraphicsProxyManager<proxyee_type, proxy_type>::hasProxy(proxyee_type* proxyee) const
{
	return _proxies.find(proxyee) != _proxies.end();
}

template<class proxyee_type, class proxy_type>
const proxy_type WGraphicsProxyManager<proxyee_type, proxy_type>::proxy(proxyee_type* proxyee) const
{
	std::map<proxyee_type*, proxy_type>::const_iterator i = _proxies.find(proxyee);
	return (i != _proxies.end()) ? i->second : proxy_type();
}

/** 
 \brief                 此类实现图元的代理的管理功能
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsItemProxyManager
	: public WGraphicsProxyManager<WGraphicsItem, WGraphicsItemProxy>
{
};

/** 
 \brief                 此类实现图层代理的管理功能
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsLayerProxyManager
	: public WGraphicsProxyManager<WGraphicsLayer, WGraphicsLayerProxy>
{
};


#endif