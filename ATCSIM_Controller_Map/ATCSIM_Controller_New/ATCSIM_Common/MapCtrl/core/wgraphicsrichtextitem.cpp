#include <QtGui/QStaticText>
#include "../wdllexport.h"
#include "wevent.h"
#include "wcursor.h"
#include "wmatrix.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "wgraphicsrichtextitem.h"

static const int SF_NONE = 0x0;
static const int SF_CONTENT = 0x1;
static const int SF_ROTATE = 0x2;

static Ws::CursorShape getCursorShape(int flag)
{
	switch(flag)
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_CONTENT : return Ws::SizeAllCursor;
	case SF_ROTATE : return Ws::BusyCursor;
	default: return Ws::ArrowCursor;
	}
}

RTTI_IMPL(WGraphicsRichTextItem)

char* WRichTextItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << pos << text << angle).value();
}

const char* WRichTextItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> pos >> text >> angle).value();
}

size_t WRichTextItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << pos << text << angle).value();
}

WGraphicsRichTextItem::WGraphicsRichTextItem(const WWorldPointF& p, const std::string& t, double ag) : 
	WGraphicsItem(new data_type(Type, p, t, ag)), _select_flag(SF_NONE)
{
	if (!t.empty())
	{
		updateBoundSize();
	}
	updateBoundRect();
}

WGraphicsRichTextItem::WGraphicsRichTextItem(data_type* d) :
	WGraphicsItem(d ? d : new data_type), _select_flag(SF_NONE)
{
	if (!data()->text.empty())
	{
		updateBoundSize();
	}
	updateBoundRect();
}

WWorldPointF WGraphicsRichTextItem::pos() const
{
	return data()->pos;
}

std::string WGraphicsRichTextItem::text() const
{
	return data()->text;
}

double WGraphicsRichTextItem::angle() const
{
	return data()->angle;
}

void WGraphicsRichTextItem::setPos(const WWorldPointF& p, bool update, bool opStack)
{
	if (p == data()->pos)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsRichTextItem::setPos, this, p, true, false),
			WCmdFactory::create(&WGraphicsRichTextItem::setPos, this, data()->pos, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->pos = p;
		updateBoundRect();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->pos = p;
		updateBoundRect();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsRichTextItem::setText(const std::string& t, bool update, bool opStack)
{
	if (data()->text == t)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsRichTextItem::setText, this, t, true, false),
			WCmdFactory::create(&WGraphicsRichTextItem::setText, this, data()->text, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->text = t;
		updateBoundSize();
		updateBoundRect();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->text = t;
		updateBoundSize();
		updateBoundRect();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsRichTextItem::setAngle(double angle, bool update, bool opStack)
{
	if (wFuzzyCompare(data()->angle, angle))
	{
		return ;
	}
	
	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsRichTextItem::setAngle, this, angle, true, false),
			WCmdFactory::create(&WGraphicsRichTextItem::setAngle, this, data()->angle, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->angle = angle;
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->angle = angle;
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

int WGraphicsRichTextItem::type() const
{
	return Type;
}

WGraphicsRichTextItem::data_type* WGraphicsRichTextItem::data()
{
	return W_D();
}

const WGraphicsRichTextItem::data_type* WGraphicsRichTextItem::data() const
{
	return W_CD();
}

WGraphicsRichTextItem* WGraphicsRichTextItem::copy() const
{
	return new WGraphicsRichTextItem(new data_type(*data()));
}

WMatrix WGraphicsRichTextItem::getRotateMatrix() const
{
	WWorldPointF c = _bound_rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(data()->angle) * WMatrix().translate(c.x(), c.y());
}

WMatrix WGraphicsRichTextItem::getRotateMatrix_1() const
{
	WWorldPointF c = _bound_rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(-data()->angle) * WMatrix().translate(c.x(), c.y());
}

void WGraphicsRichTextItem::updateBoundSize()
{
	QStaticText st(QString::fromStdString(data()->text));
	QSizeF sz = st.size();
	_bound_size.setWidth(sz.width() * 1.2);
	_bound_size.setHeight(sz.height() * 1.2);
}

void WGraphicsRichTextItem::updateBoundRect()
{
	_bound_rect = WWorldRectF(data()->pos, _bound_size);
	_rotate_pt.setXY((_bound_rect.left()+_bound_rect.right())/2, _bound_rect.top() + CP_ROTATE_HEADER);
}

WWorldRectF WGraphicsRichTextItem::boundingRect() const
{
	return getRotateMatrix().mapRect(_bound_rect.adjusted(-2*CP_RADIUS, -2*CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS+CP_ROTATE_HEADER));
}

bool WGraphicsRichTextItem::contains(const WWorldPointF& point) const
{
	bool b = _bound_rect.adjusted(-CP_RADIUS, -CP_RADIUS, CP_RADIUS, CP_RADIUS).contains(point);
	return isSelected() ? (b || distance(point, _rotate_pt) < CP_RADIUS) : b;
}

void WGraphicsRichTextItem::paint(WPainter* painter)
{
	{
		WPainterProxy proxy(painter);
		painter->setWorldTransform(getRotateMatrix(), true);

		if (isSelected())
		{
			painter->setPen(HOVER_PEN);
			painter->setBrush(WBrush());
			painter->drawRect(_bound_rect);
			painter->drawLine(WWorldLineF(_rotate_pt, WWorldPointF(_rotate_pt.x(), _bound_rect.top())));

			painter->setPen(CP_PEN);
			painter->setBrush(ROTATE_BRUSH);
			painter->drawEllipse(WWorldRectF(_rotate_pt.x() - CP_RADIUS, _rotate_pt.y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
		}

		painter->setPen(WPen());
		painter->setBrush(WBrush());
		WWorldPointF c = _bound_rect.topLeft();
		WMatrix matrix = WMatrix().translate(-c.x(), -c.y()) * WMatrix().scale(1, -1) * WMatrix().translate(c.x(), c.y());
		painter->setWorldTransform(matrix, true);
		painter->drawStaticText(matrix.map(c), data()->text);
	}
	
	if (_dragging)
	{
		WPainterProxy proxy(painter);
		if (_select_flag & SF_CONTENT)
		{
			WWorldPointF offset = scene()->mousePos() - scene()->dragStartPos();
			WWorldPointF pos = _bound_rect.topLeft() + offset;
			WWorldRectF br = _bound_rect.translated(offset);
			WWorldPointF c = br.center();

			WMatrix matrix =  WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(data()->angle) * WMatrix().translate(c.x(), c.y());
			painter->setWorldTransform(matrix, true);

			WMatrix m = WMatrix().translate(-pos.x(), -pos.y()) * WMatrix().scale(1, -1) * WMatrix().translate(pos.x(), pos.y());
			painter->setWorldTransform(m, true);

			painter->drawStaticText(m.map(pos), data()->text);
		}
		else if (_select_flag & SF_ROTATE)
		{
			WWorldPointF pos = scene()->mousePos();
			WWorldPointF c = _bound_rect.center();
			double ag = normalized_angle(WWorldLineF(c, pos).angle() - 90);
			WMatrix m = WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(ag) * WMatrix().translate(c.x(), c.y());
			painter->setWorldTransform(m, true);
			painter->setBrush(WBrush());
			painter->setPen(DRAG_PEN);
			painter->drawRect(_bound_rect);
		}
	}
}

void WGraphicsRichTextItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = getRotateMatrix_1().map(event->scenePos());

	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;
			
			if (_select_flag == SF_CONTENT)
			{
				WWorldRectF r = boundingRect();
				WWorldRectF rectFrom = r.translated(event->lastScenePos() - scene()->dragStartPos());
				WWorldRectF rectTo = r.translated(event->scenePos() - scene()->dragStartPos());
				scene()->update(r | rectFrom | rectTo);
			}
			else if (_select_flag == SF_ROTATE)
			{
				WWorldPointF c = _bound_rect.center();
				double radius = WWorldLineF(_bound_rect.topLeft(), _bound_rect.bottomRight()).length() / 2;
				scene()->update(WWorldRectF(c.x(), c.y(), 0.0, 0.0).adjusted(-radius, -radius, radius, radius));
			}
		}
		else //update select flag (status transfer) 
		{
			int old_flag = _select_flag;
			if (!contains(pos)) //other status ---> none selected
			{
				_select_flag = SF_NONE;
			}
			else
			{
				_select_flag = (distance(_rotate_pt, pos) < CP_RADIUS) ? SF_ROTATE : SF_CONTENT;
			}

			if (_select_flag != old_flag) //select status changed
			{
				scene()->update(boundingRect());
				event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
			}
		}
	}
}

void WGraphicsRichTextItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	bool contain = contains(getRotateMatrix_1().map(event->scenePos()));
	if (isSelectable() && isSelectable() && !isSelected() && contain) //status transfer, not selected ---> selected
	{
		_select_flag = SF_CONTENT;
		setSelected();
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

		scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
	}
	else if (isSelected() && !contain) //status transfer, selected ---> not selected
	{
		_select_flag = SF_NONE;
		setSelected(false);
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

		scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
	}
}

void WGraphicsRichTextItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		if (_select_flag & SF_CONTENT)
		{
			setPos(data()->pos + event->scenePos() - scene()->dragStartPos(), false, true);
		}
		else if (_select_flag & SF_ROTATE)
		{
			setAngle(normalized_angle(WWorldLineF(_bound_rect.center(), event->scenePos()).angle() - 90.0), false, true);
		}

		scene()->update();
	}
}

void WGraphicsRichTextItem::translate(const WWorldPointF& offset)
{
	setPos(data()->pos + offset);
}