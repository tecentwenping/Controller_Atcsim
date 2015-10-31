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
#include "wgraphicsrectitem.h"

//select flag--->SF
//left--->L
//right--->R
//top--->T
//bottom--->B
//center--->C
static const int SF_NONE = 0x0;
static const int SF_TL = 0x1;
static const int SF_TC = 0x2;
static const int SF_TR = 0x4;
static const int SF_RC = 0x8;
static const int SF_BR = 0x10;
static const int SF_BC = 0x20;
static const int SF_BL = 0x40;
static const int SF_LC = 0x80;
static const int SF_CONTENT = 0x100; //整个矩形被选中
static const int SF_ROTATE = 0x200; //旋转点被选中

//偏移设置表
static const int ADJUST_TABLE[10][4] = 
{
	{0, 0, 0, 0},
	{1, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 0, 1, 1},
	{0, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 1, 1},
};

RTTI_IMPL(WGraphicsRectItem)

char* WRectItemData::serialize(char* buf) const
{
	return (WSerializer(WAbstractShapeItemData::serialize(buf)) << rect << angle).value();
}

const char* WRectItemData::unserialize(const char* buf)
{
	return (WUnserializer(WAbstractShapeItemData::unserialize(buf)) >> rect >> angle).value();
}

size_t WRectItemData::serialize_size() const
{
	return (WSizeHelper(WAbstractShapeItemData::serialize_size()) << rect << angle).value();
}

WGraphicsRectItem::WGraphicsRectItem(const WWorldRectF& r, const WBrush& b, const WPen& p, double ag) :
	WAbstractGraphicsShapeItem(new data_type(Type, r, b, p, ag)), _select_flag(SF_NONE)
{
	updateCp();
}

WGraphicsRectItem::WGraphicsRectItem(data_type* d) : 
	WAbstractGraphicsShapeItem(d ? d : new data_type), _select_flag(SF_NONE)
{
	updateCp();
}

WWorldRectF WGraphicsRectItem::rect() const
{
	return data()->rect;
}

double WGraphicsRectItem::angle() const
{
	return data()->angle;
}

void WGraphicsRectItem::setRect(const WWorldRectF& rect, bool update, bool opStack)
{
	if (rect == data()->rect)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsRectItem::setRect, this, rect, true, false),
			WCmdFactory::create(&WGraphicsRectItem::setRect, this, data()->rect, true, false));
	}

	WWorldRectF r = boundingRect();
	data()->rect = rect;
	updateCp();

	if (update)
	{
		scene()->update(r | boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsRectItem::setAngle(double ag, bool update, bool opStack)
{
	if (wFuzzyCompare(ag, data()->angle))
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsRectItem::setAngle, this, ag, true, false),
			WCmdFactory::create(&WGraphicsRectItem::setAngle, this, data()->angle, true, false));
	}

	WWorldRectF r = boundingRect();
	data()->angle = ag;

	if (update)
	{
		scene()->update(r | boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsRectItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setRenderHint(Ws::Antialiasing, false);
	painter->setRenderHint(Ws::TextAntialiasing, false);
	painter->setWorldTransform(getRotateMatrix(), true); //设置旋转矩阵

	painter->setBrush(brush());
	painter->setPen(pen());
	painter->drawRect(data()->rect); //绘制矩形
	
	if (isSelected()) //矩形被选中，绘制所有的控制点
	{
		painter->drawLine(WWorldLineF(_rotate_pt, WWorldPointF(_rotate_pt.x(), data()->rect.top())));

		painter->setPen(CP_PEN);
		painter->setBrush(CP_BRUSH);
		for (unsigned i=0; i<array_size(_cp); ++i)
		{
			if (i & 1)
			{
				painter->drawRect(WWorldRectF(_cp[i].x() - CP_RADIUS, _cp[i].y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
			}
			else
			{
				painter->drawEllipse(WWorldRectF(_cp[i].x() - CP_RADIUS, _cp[i].y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
			}
		}
		
		painter->setBrush(ROTATE_BRUSH);
		painter->drawEllipse(WWorldRectF(_rotate_pt.x() - CP_RADIUS, _rotate_pt.y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
	}

	if (_dragging) //矩形在拖动，绘制正在拖动的矩形
	{
		WWorldPointF pos = scene()->attachedPoint(scene()->mousePos());
		WPen dragPen = data()->pen;
		WBrush dragBrush = data()->brush;
		dragPen.setColor(dragPen.color().lighter(2.0));
		dragBrush.setColor(dragBrush.color().lighter(2.0));
		painter->setPen(dragPen);
		painter->setBrush(dragBrush);

		if (_select_flag != SF_ROTATE)
		{
			if (_select_flag != SF_CONTENT || isMovable())
			{
				WWorldPointF offset = pos - scene()->dragStartPos();
				const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];
				painter->drawRect(data()->rect.adjusted(offset.x() * f[0], offset.y() * f[1], offset.x() * f[2], offset.y() * f[3]));
			}
		}
		else
		{
			painter->setWorldTransform(getRotateMatrix_1(), true);

			WWorldPointF c = data()->rect.center();
			double ag = WWorldLineF(c, pos).angle() - 90;
			painter->setWorldTransform(WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(ag + data()->angle) * WMatrix().translate(c.x(), c.y()));
			painter->drawRect(data()->rect);
		}
	}
}

bool WGraphicsRectItem::contains(const WWorldPointF& point) const
{
	bool b = data()->rect.adjusted(-CP_RADIUS, -CP_RADIUS, CP_RADIUS, CP_RADIUS).contains(point);
	return isSelected() ? (b || distance(point, _rotate_pt) < CP_RADIUS) : b;
}

WWorldRectF WGraphicsRectItem::boundingRect() const
{
	return getRotateMatrix().mapRect(data()->rect.adjusted(-2*CP_RADIUS, -2*CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS+CP_ROTATE_HEADER));
}

int WGraphicsRectItem::type() const
{
	return Type;
}

void WGraphicsRectItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WMatrix matrix = getRotateMatrix_1();
	WWorldPointF pos = matrix.map(event->scenePos());
	
	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;

			WWorldPointF lastPos = matrix.map(event->lastScenePos());
			WWorldPointF dragPos = matrix.map(scene()->dragStartPos());

			WWorldRectF r = boundingRect();
			if (_select_flag != SF_ROTATE) //矩形不是在旋转
			{
				if (_select_flag != SF_CONTENT || isMovable()) //矩形不是整个被选中
				{
					const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];

					WWorldPointF offsetFrom = lastPos - dragPos;
					WWorldPointF offsetTo = pos - dragPos;
					WWorldRectF rectFrom = data()->rect.adjusted(offsetFrom.x() * f[0], offsetFrom.y() * f[1], offsetFrom.x() * f[2], offsetFrom.y() * f[3]);
					WWorldRectF rectTo = data()->rect.adjusted(offsetTo.x() * f[0], offsetTo.y() * f[1], offsetTo.x() * f[2], offsetTo.y() * f[3]);
					scene()->update(expanded(rectFrom | rectTo | boundingRect()));
				}
			}
			else //矩形在旋转
			{
				double radius = std::max(data()->rect.width() / 2, data()->rect.height() / 2);
				WWorldPointF c = data()->rect.center();
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
				unsigned i=0;
				unsigned size = array_size(_cp);
				for (; i<size; ++i)
				{
					if (distance(pos, _cp[i]) < CP_RADIUS) //detect wheter control point is selected
					{
						_select_flag = (1 << i); //control point _cp[i] is presently selected
						break;
					}
				}

				if (i == size)
				{
					_select_flag = (distance(_rotate_pt, pos) < CP_RADIUS) ? SF_ROTATE : SF_CONTENT;
				}
			}

			if (_select_flag != old_flag) //select status changed
			{
				scene()->update(boundingRect());
				event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));
			}
		}
	}
}

void WGraphicsRectItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	bool contain = contains(getRotateMatrix_1().map(event->scenePos()));
	if (isSelectable() && !isSelected() && contain) //status transfer, not selected ---> selected
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

void WGraphicsRectItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		WWorldPointF pos = event->scenePos();
		WMatrix matrix = getRotateMatrix_1(); //获取逆向矩阵

		if (_select_flag != SF_ROTATE) //矩形不是在旋转
		{
			if (_select_flag != SF_CONTENT || isMovable())
			{
				const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];

				WWorldPointF offset = pos - scene()->dragStartPos();
				WWorldRectF rect = data()->rect.adjusted(offset.x() * f[0], offset.y() * f[1], offset.x() * f[2], offset.y() * f[3]);
				setRect(rect, false, true);
			}
		}
		else //矩形在旋转
		{
			WWorldPointF c = data()->rect.center();
			double ag = WWorldLineF(c, pos).angle() - 90;
			setAngle(data()->angle + ag, false, true);
		}

		scene()->update();
	}
}

/**
\brief      updateCp
\Access    public 
\retval     void
\remark     更新控制点
*/
void WGraphicsRectItem::updateCp()
{
	double t = data()->rect.top();
	double b = data()->rect.bottom();
	double l = data()->rect.left();
	double r = data()->rect.right();

	_cp[0].setXY(l, t);
	_cp[1].setXY((l+r)/2, t);
	_cp[2].setXY(r, t);
	_cp[3].setXY(r, (t+b)/2);
	_cp[4].setXY(r, b);
	_cp[5].setXY((l+r)/2, b);
	_cp[6].setXY(l, b);
	_cp[7].setXY(l, (t+b)/2);
	_rotate_pt.setXY((l+r)/2, t+CP_ROTATE_HEADER);
}

WGraphicsRectItem::data_type* WGraphicsRectItem::data()
{
	return W_D();
}

const WGraphicsRectItem::data_type* WGraphicsRectItem::data() const
{
	return W_CD();
}

WGraphicsRectItem* WGraphicsRectItem::copy() const
{
	return new WGraphicsRectItem(new data_type(*data()));
}

void WGraphicsRectItem::keyPressEvent(WKeyEvent* event)
{
	if (isSelected()) //矩形被选中
	{
		if ((event->modifiers() & Ws::ShiftModifier)) //旋转矩形
		{
			double delta = 0.0;
			switch(event->key()) //确定旋转的方向
			{
			case Ws::Key_Up : delta = 1.0; break;
			case Ws::Key_Down : delta = -1.0; break;
			default : break;
			}

			if (!wFuzzyCompare(delta, 0.0)) //旋转角度不为0
			{
				setAngle(data()->angle + delta, true, true);
			}
		}
	}
}

WMatrix WGraphicsRectItem::getRotateMatrix() const
{
	WWorldPointF c = data()->rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(data()->angle) * WMatrix().translate(c.x(), c.y());
}

WMatrix WGraphicsRectItem::getRotateMatrix_1() const
{
	WWorldPointF c = data()->rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(-data()->angle) * WMatrix().translate(c.x(), c.y());
}

bool WGraphicsRectItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	WWorldPointF p = getRotateMatrix_1().map(pos);

	const WWorldRectF& r = data()->rect;
	double x1 = r.left();
	double x2 = r.right();
	double y1 = r.bottom();
	double y2 = r.top();
	double x = p.x();
	double y = p.y();
	double* px = 0;
	double* py = 0;
	
	if (x1 - ATTACH_DISTANCE < x && x < x2 + ATTACH_DISTANCE)
	{
		px = &x;
		if (y1 - ATTACH_DISTANCE < y && y < y1 + ATTACH_DISTANCE)
		{
			py = &y1;
		}
		else if (y2 - ATTACH_DISTANCE < y && y < y2 + ATTACH_DISTANCE)
		{
			py = &y2;
		}
	}
	
	if (!(px && py) && y1 - ATTACH_DISTANCE < y && y < y2 + ATTACH_DISTANCE)
	{
		py = &y;
		if (x1 - ATTACH_DISTANCE < x && x < x1 + ATTACH_DISTANCE)
		{
			px = &x1;
		}
		else if (x2 - ATTACH_DISTANCE < x && x < x2 + ATTACH_DISTANCE)
		{
			px = &x2;
		}
	}

	if (px && py && attachedPos)
	{
		*attachedPos = getRotateMatrix().map(WWorldPointF(*px, *py));
	}

	return px && py;
}

Ws::CursorShape WGraphicsRectItem::getCursorShape(int flag)
{
	switch(flag)
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_TL : return Ws::SizeFDiagCursor;
	case SF_TC : return Ws::SizeVerCursor;
	case SF_TR : return Ws::SizeBDiagCursor;
	case SF_RC : return Ws::SizeHorCursor;
	case SF_BR : return Ws::SizeFDiagCursor;
	case SF_BC : return Ws::SizeVerCursor;
	case SF_BL : return Ws::SizeBDiagCursor;
	case SF_LC : return Ws::SizeHorCursor;
	case SF_CONTENT : return isMovable() ? Ws::SizeAllCursor : Ws::ForbiddenCursor;
	case SF_ROTATE : return Ws::BusyCursor;
	default: return Ws::ArrowCursor;
	}
}

void WGraphicsRectItem::translate(const WWorldPointF& offset)
{
	setRect(data()->rect.translated(offset));
}