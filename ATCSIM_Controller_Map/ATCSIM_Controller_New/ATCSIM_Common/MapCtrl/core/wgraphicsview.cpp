#include "../wdllexport.h"
#include "wpainter.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"

WGraphicsView::WGraphicsView(WGraphicsScene* scene) : _scene(scene), _editable(false)
{
	_matrix.scale(1, -1); //将坐标系切换到世界坐标系
	if (_scene)
	{
		_scene->addView(this); //将视图加到场景中
	}
}

WGraphicsView::~WGraphicsView()
{
	_scene = 0;
}

WGraphicsScene* WGraphicsView::scene() const
{
	return _scene;
}

void WGraphicsView::setScene(WGraphicsScene* scene)
{
	if (_scene)
	{
		_scene->removeView(this);
	}
	_scene = scene;
	if (_scene)
	{
		_scene->addView(this); 
	}
}

void WGraphicsView::render(WPainter* painter, const WWorldRectF& rect)
{
	if (_scene)
	{
		_scene->render(painter, rect, this);
	}
}


WMatrix WGraphicsView::worldTransform() const
{
	return _matrix;
}

void WGraphicsView::setWorldTransform(const WMatrix& matrix, bool combine)
{
	if (combine)
	{
		_matrix *= matrix;
	}
	else
	{
		_matrix = matrix;
	}
}

void WGraphicsView::setCenter(const WWorldPointF& c)
{
	WWorldPointF offset = mapToView(_center) - c;
	_center = mapToScene(c);
	_matrix.translate(offset.x()/_matrix.m11(), offset.y()/_matrix.m22());
}

WWorldPointF WGraphicsView::center() const
{
	return _center;
}

void WGraphicsView::requestContextMenu(Ws::ContextMenuFlags)
{
}

void WGraphicsView::onContextMenu(Ws::ContextMenuFlag flag)
{
	_scene->onContextMenu(flag);
}

bool WGraphicsView::editable() const
{
	return _editable;
}

void WGraphicsView::setEditable(bool enabled)
{
	_editable = enabled;
}

void WGraphicsView::translate(double dx, double dy)
{
	_center -= WWorldPointF(dx/_matrix.m11(), dy/_matrix.m22());
	_matrix *= WMatrix().translate(dx, dy);
}

void WGraphicsView::translate(const WWorldPointF& p)
{
	translate(p.x(), p.y());
}

void WGraphicsView::translateView(double dx, double dy)
{
	translate(dx / _matrix.m11(), dy / _matrix.m22());
}

void WGraphicsView::translateView(const WWorldPointF& p)
{
	translateView(p.x(), p.y());
}

WGraphicsItemProxyManager& WGraphicsView::itemProxyManager()
{
	return _item_proxy_manager;
}

const WGraphicsItemProxyManager& WGraphicsView::itemProxyManager() const
{
	return _item_proxy_manager;
}

WGraphicsLayerProxyManager& WGraphicsView::layerProxyManager()
{
	return _layer_proxy_manager;
}

const WGraphicsLayerProxyManager& WGraphicsView::layerProxyManager() const
{
	return _layer_proxy_manager;
}


void WGraphicsView::rotate(double angle, const WWorldPointF& p)
{
	_matrix *= WMatrix().translate(-p) * WMatrix().rotate(angle) * WMatrix().translate(p);
	//_matrix.translate(-p).rotate(angle).translate(p);
	updateScene();
}

void WGraphicsView::rotate(double angle)
{
	_matrix.rotate(angle);
	updateScene();
}

void WGraphicsView::rotateView(double angle)
{
	WWorldSizeF sz = size();
	rotate(angle, mapToScene(WWorldPointF(sz.width() / 2.0, sz.height() / 2.0)));
}

WWorldPointF WGraphicsView::mapToScene(const WWorldPointF& p)
{
	return _matrix.inverted().map(p);
}

WWorldPointF WGraphicsView::mapToView(const WWorldPointF& p)
{
	return _matrix.map(p);
}

void WGraphicsView::reset(double factor)
{
	WWorldSizeF c = size() / 2;
	_matrix.reset();
	_matrix.translate(c.width(), c.height());
	_matrix.scale(factor, -factor);

	_center.setXY(0, 0);

	updateScene();
}