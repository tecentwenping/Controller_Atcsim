#include "../wdllexport.h"
#include "wgraphicslayerproxy.h"



/**
\brief      WGraphicsLayerProxy
\Access    public 
\retval     
\remark     
*/
WGraphicsLayerProxy::WGraphicsLayerProxy() : m_proxyObj(0)
{

}

WGraphicsLayerProxy::WGraphicsLayerProxy(const LayerProxyObj& obj) : m_proxyObj(obj)
{
}

bool WGraphicsLayerProxy::proxy(WGraphicsLayer* layer, WPainter* painter, const WWorldRectF& rect, WGraphicsView* view)
{
	if (m_proxyObj)
	{
		return m_proxyObj(layer, painter, rect, view);
	}

	return false;
}


