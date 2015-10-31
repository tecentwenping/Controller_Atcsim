#include "wevent.h"
#include "wworldrect.h"
#include "wgraphicsscene.h"
#include "wgraphicsview.h"
#include "wtelemeterglyph.h"
#include "wtelemetercreator.h"
#include "wglyphidentity.h"

WTelemeterCreator::WTelemeterCreator(WGraphicsScene* scene) : WDefaultCreator(scene), _step(0), _item(0)
{
}

void WTelemeterCreator::clear()
{
	_step = 0;
	_item = 0;
}

void WTelemeterCreator::start()
{
	clear();
}

void WTelemeterCreator::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{

	// 	if (event->buttons() & Ws::RightButton)
// 	{
// 		if (_item)
// 		{
// 			scene()->currentLayer()->removeItem(_item, true);
// 		}
// 		emit finished(0);
// 		clear();
// 	}

	if (event->buttons() & Ws::MidButton)
	{
		if (_step == 0)
		{
			WPointF pos = event->widget()->mapToScene(_savePoint);// 使用上一次保存的点
			scene()->attachPoint(pos, &pos);

			_item = new WTelemeterGlyph;
			WTelemeterItemData& d = *_item->data();
			d.m_penLine.setColor(WColor(255, 0, 0));
			d.m_penLine.setStyle(Ws::DashLine);
			d.m_penText.setColor(WColor(0, 255, 255));
			d.m_line.setLine(pos.x(), pos.y(), pos.x() + 1.0, pos.y() - 1.0);

			WGraphicsLayer* l = scene()->addLayer(GLYPH_TELEMETER);
			l->setEditable(true);
			l->addItem(_item, true);
			emit start(_item);

			emit stepOver(_item, _step, pos);
			++_step;
		}
		else if (_step == 1)
		{
			WRectF r = _item->boundingRect();
			WPointF pos = event->scenePos();

			scene()->attachPoint(pos, &pos);
			_item->data()->m_line.setP2(pos);
			scene()->update(_item->boundingRect() | r);
		}
	}
}

void WTelemeterCreator::mousePressEvent(WGraphicsSceneMouseEvent* event)
{

}

/**
\brief      mouseReleaseEvent
\Access    virtual public 
\param  WGraphicsSceneMouseEvent * event
\retval     void
\remark     
*/
void WTelemeterCreator::mouseReleaseEvent( WGraphicsSceneMouseEvent* event )
{
	if (_step == 1)
	{	
		if (_item->data()->m_line.length() < 1)//0m的测距线不显示
		{
			scene()->layer(GLYPH_TELEMETER)->removeItem(_item, true);
			delete _item;
			_item = NULL;
		}
	
		else
		{
			_item->data()->m_penLine.setStyle(Ws::SolidLine);
			emit stepOver(_item, _step, event->scenePos()); // 外部可能会修改， 所有update在后
			scene()->update(_item->boundingRect());
		}
		
		emit finished(_item);
		clear();
	}
}

/**
\brief      setSavePoint
\Access    public 
\param  const WPointF & p
\retval     void
\remark     
*/
void WTelemeterCreator::setSavePoint( const WPointF& p )
{
	_savePoint = p;
}


