#include "../wdllexport.h"
#include "wgraphicsitemproxy.h"

WGraphicsItemProxy::WGraphicsItemProxy() : m_proxyObj(0)
{
}

/**
\brief      WGraphicsItemProxy
\Access    public 
\param  const ItemProxyObj & obj
\retval     
\remark     
*/
WGraphicsItemProxy::WGraphicsItemProxy( const ItemProxyObj& obj )
: m_proxyObj(obj)
{

}

/**
\brief      proxy
\Access    public 
\param  WGraphicsItem * item
\param  WPainter * painter
\param  const WWorldRectF & rct
\param  WGraphicsView * view
\retval    bool 
\remark     
*/
bool WGraphicsItemProxy::proxy( WGraphicsItem* item, WPainter* painter, const WWorldRectF& rct, WGraphicsView* view )
{
	if (m_proxyObj)
	{
		return m_proxyObj(item, painter, rct, view);
	}

	return false;
}

