#include "WFrameCreator.h"
#include "wgraphicsrectitem.h"
#include "wevent.h"
#include "wgraphicsscene.h"
#include "cellformat.h"
#include "wglyphidentity.h"

WFrameCreator::WFrameCreator(WGraphicsScene* scene) : WDefaultCreator(scene), 
													  _item(NULL), 
													  _step(0)
{

}

/**
\brief      start
\Access    virtual public 
\retval     void
\remark     
*/
void WFrameCreator::start()
{
	clear();
	m_layer = scene()->addLayer(GLYPH_FRAME);
	m_layer->setEditable(true);
	scene()->setCurrentLayer(m_layer);
}

/**
\brief      mouseMoveEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WFrameCreator::mouseMoveEvent( WGraphicsSceneMouseEvent* event )
{
	if (event->buttons() & Ws::RightButton)
	{
		if (_step == 0)
		{
			WWorldPointF pos = event->scenePos();
			scene()->attachPoint(pos, &pos);
			WWorldRectF rect(pos.x(), pos.y(), 0, 0);
			WPen pen(Ws::SolidLine, WColor(255,255,0), 0);
			WBrush brush(Ws::NoBrush);
			_item = m_layer->addRect(rect, 0.0, pen, brush, true);
			emit filterOtherViews((WGraphicsItem*)_item);
			++_step;	
		}

		else if (_step == 1)
		{
			WWorldRectF rect = _item->rect();
			WWorldPointF pos = event->scenePos();
			scene()->attachPoint(pos, &pos);
			WWorldPointF offset = pos - rect.bottomRight();
			_item->setRect(rect.adjusted(0, offset.y(), offset.x(), 0), true);
		}
	}
}

/**
\brief      mousePressEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WFrameCreator::mousePressEvent( WGraphicsSceneMouseEvent* event )
{

}

/**
\brief      mouseReleaseEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WFrameCreator::mouseReleaseEvent( WGraphicsSceneMouseEvent* event )
{
	if (1 == _step)
	{
		emit finished(_item);
		m_layer->removeItem(_item, true);
		clear();	
	}	
}

/**
\brief      clear
\Access    private 
\retval     void
\remark     
*/
void WFrameCreator::clear()
{
	_item = NULL;
	_step = 0;
}