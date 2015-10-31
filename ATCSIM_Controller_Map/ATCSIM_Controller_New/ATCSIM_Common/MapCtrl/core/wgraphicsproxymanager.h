/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsproxymanager.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WGraphicsProxyManagerģ���࣬
					���ڴ˻����϶�����������WGraphicsItemProxyManager
					WGraphicsLayerProxyManager��WGraphicsItemFilterManager��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_PROXY_MANAGER_H_
#define _WGRAPHICS_PROXY_MANAGER_H_

#include <map>
#include "../wdllimport.h"
#include "wgraphicsitemproxy.h"
#include "wgraphicslayerproxy.h"


/** 
 \brief                 ������Ҫ����֧�ָ�һ���������Ӵ���Ĺ���
\details   ��Ȼ����ɾ���������Ҵ�����ȡ����Ĺ���
 \author    ����
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
 \brief                 ����ʵ��ͼԪ�Ĵ���Ĺ�����
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsItemProxyManager
	: public WGraphicsProxyManager<WGraphicsItem, WGraphicsItemProxy>
{
};

/** 
 \brief                 ����ʵ��ͼ�����Ĺ�����
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsLayerProxyManager
	: public WGraphicsProxyManager<WGraphicsLayer, WGraphicsLayerProxy>
{
};


#endif