//#include <boost/foreach.hpp>
//#include <boost/thread/detail/singleton.hpp>
//#include "wevent.h"
//#include "wpainter.h"
//#include "wlabelglyph.h"
//#include "wpainterproxy.h"
//#include "wgraphicsscene.h"
//#include "wgraphicschange.h"
//
//WLabelGlyph::WLabelGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
//{
//}
//
//WLabelGlyph::data_type* WLabelGlyph::data()
//{
//	return W_D();
//}
//
//const WLabelGlyph::data_type* WLabelGlyph::data() const
//{
//	return W_CD();
//}
//
//WLabelGlyph::WLabelCallbackManager& WLabelGlyph::getCallbackManager()
//{
//	return boost::detail::thread::singleton<WLabelCallbackManager>::instance();
//}
//
//void WLabelGlyph::updateCache()
//{
//	const data_type& d = *data();
//	m_cd.labelBottomLeft = d.m_boundingRect.bottomLeft();
//	m_cd.labelMatrix = WMatrix().translate(-m_cd.labelBottomLeft) * WMatrix().scale(1.0 / m_cd.fx, 1.0 / m_cd.fy) * WMatrix().translate(m_cd.labelBottomLeft);
//	m_cd.labelMatrix_1 = WMatrix().translate(-m_cd.labelBottomLeft) * WMatrix().scale(m_cd.fx, m_cd.fy) * WMatrix().translate(m_cd.labelBottomLeft);
//	m_cd.labelCenter = m_cd.labelMatrix.mapRect(d.m_boundingRect).center();
//
//	m_cd.blockRects.clear();
//	m_cd.blockMappedRects.clear();
//	m_cd.blockMatries.clear();
//
//	const std::list<WBlockData>& blocks = d.m_blocks;
//	BOOST_FOREACH(const WBlockData& block, blocks)
//	{
//		WPointF pos = block.m_boundingRect.bottomLeft() + m_cd.labelBottomLeft;
//		WRectF blockRect = block.m_boundingRect.translated(m_cd.labelBottomLeft);
//		m_cd.blockRects.push_back(blockRect);
//
//		WMatrix matrixText = WMatrix().translate(-pos) * WMatrix().scale(1.0, -1.0) * WMatrix().translate(pos);
//		m_cd.blockMatries.push_back(matrixText);
//		m_cd.blockMappedRects.push_back(matrixText.mapRect(blockRect));
//	}
//
//	double R = wMax(d.m_penBounding.width(), d.m_penBoundingSel.width(), 2.0);
//	WRectF rectLabelLine(m_cd.labelCenter, d.m_posTarget);
//	m_cd.boundingRect =  m_cd.labelMatrix.mapRect(d.m_boundingRect).adjusted(-R, -R, R, R) | rectLabelLine.normalized();
//}
//
//void WLabelGlyph::paint(WPainter* painter)
//{
//	WPainterProxy proxy(painter);
//
//	const data_type& d = *data();
//
//	painter->setPen(d.m_penLine);
//	painter->drawLine(WLineF(m_cd.labelCenter, d.m_posTarget));
//
//	WMatrix matrixOrg = painter->worldTransform();
//	double fx = fabs(matrixOrg.m11());
//	double fy = fabs(matrixOrg.m22());
//
//	if (!(wFuzzyCompare(fx, m_cd.fx) && wFuzzyCompare(fy, m_cd.fy)))
//	{
//		m_cd.fx = fx;
//		m_cd.fy = fy;
//		updateCache();
//	}
//
//	painter->setWorldTransform(m_cd.labelMatrix, true);
//
//	size_t i = 0;
//	const std::list<WBlockData>& blocks = d.m_blocks;
//	BOOST_FOREACH(const WBlockData& block, blocks)
//	{
//		WMatrix m = painter->worldTransform();
//
//		if (block.m_bShowBounding)
//		{
//			painter->setBrush(block.m_brush);
//			painter->setPen(block.m_penBounding);
//			painter->drawRect(m_cd.blockRects[i]);
//		}
//
//		painter->setWorldTransform(m_cd.blockMatries[i], true);
//		painter->setPen(block.m_penText);
//		painter->setFont(block.m_font);
//		painter->drawText(m_cd.blockMappedRects[i], Ws::AlignCenter, block.m_text);
//
//		++i;
//		painter->setWorldTransform(m);
//	}
//
//	if (d.m_bShowBounding)
//	{
//		painter->setPen(isSelected() ? d.m_penBoundingSel : d.m_penBounding);
//		painter->setBrush(isSelected() ? d.m_brushSel : d.m_brush);
//		painter->drawRect(d.m_boundingRect);
//	}
//}
//
//bool WLabelGlyph::contains(const WWorldPointF& point) const
//{
//	return data()->m_boundingRect.contains(point);
//}
//
//WWorldRectF WLabelGlyph::boundingRect() const
//{
//	return m_cd.boundingRect;
//}
//
//WMatrix WLabelGlyph::getMatrix() const
//{
//	return m_cd.labelMatrix;
//}
//
//WMatrix WLabelGlyph::getMatrix_1() const
//{
//	return m_cd.labelMatrix_1;
//}
//
//WBlockData* WLabelGlyph::getActivatedBlock(const WPointF& pos)
//{
//	WPointF p = pos - data()->m_boundingRect.bottomLeft();
//	std::list<WBlockData>& blocks = data()->m_blocks;
//
//	BOOST_FOREACH(WBlockData& block, blocks)
//	{
//		if (block.m_boundingRect.contains(p))
//		{
//			return &block;
//		}
//	}
//
//	return 0;
//}
//
//static void fill_label_event_feedback(WLabelEventFeedback& feedback, WLabelGlyph* item, 
//									  WGraphicsSceneMouseEvent* event)
//{
//	feedback.m_item = item;
//	feedback.m_itemData = item->data();
//	feedback.m_buttons = event->buttons();
//	feedback.m_modifiers = event->modifiers();
//	feedback.m_event = event;
//}
//
//void WLabelGlyph::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
//{
//	if (isSelected())
//	{
//		if (event->buttons() & Ws::LeftButton) //drag move
//		{
//			WRectF r = boundingRect();
//			data()->m_boundingRect.translate(event->scenePos() - event->lastScenePos());
//			updateCache();
//			scene()->update(r | boundingRect());
//		}
//	}
//}
//
//void WLabelGlyph::mousePressEvent(WGraphicsSceneMouseEvent* event)
//{
//	WPointF pos = getMatrix_1().map(event->scenePos());
//	bool contain = contains(pos);
//
//	if (isSelected())
//	{
//		if (contain)
//		{
//			WLabelEventFeedback feedback;
//			fill_label_event_feedback(feedback, this, event);
//			feedback.m_eType = WLabelEventFeedback::mouse_press;
//			feedback.m_blockData = getActivatedBlock(pos);
//			getCallbackManager().call(this, feedback);
//		}
//		else //status transfer, selected ---> not selected
//		{
//			setSelected(false);
//			scene()->update(boundingRect());
//			scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
//		}
//	}
//	else if (contain) //status transfer, not selected ---> selected
//	{
//		setSelected();
//		scene()->update(boundingRect());
//		scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
//	}
//}
//
//void WLabelGlyph::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
//{
//	if (isSelected())
//	{
//		WLabelEventFeedback feedback;
//		fill_label_event_feedback(feedback, this, event);
//		feedback.m_eType = WLabelEventFeedback::mouse_release;
//		feedback.m_blockData = getActivatedBlock(getMatrix_1().map(event->scenePos()));
//		getCallbackManager().call(this, feedback);
//	}
//}
//
//void WLabelGlyph::mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event)
//{
//	if (isSelected())
//	{
//		WLabelEventFeedback feedback;
//		fill_label_event_feedback(feedback, this, event);
//		feedback.m_eType = WLabelEventFeedback::mouse_double_click;
//		feedback.m_blockData = getActivatedBlock(getMatrix_1().map(event->scenePos()));
//		getCallbackManager().call(this, feedback);
//	}
//}
//
