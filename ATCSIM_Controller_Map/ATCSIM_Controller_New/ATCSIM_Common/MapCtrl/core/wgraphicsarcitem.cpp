#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include "../wdllexport.h"
#include "wevent.h"
#include "wcursor.h"
#include "wglobal.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"
#include "wworldpolygon.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "wgraphicsarcitem.h"

//ѡ�б�ʶ
//select flag--->SF
//left--->L
//right--->R
//top--->T
//bottom--->B
static const int SF_NONE = 0; //û�б�ѡ��
static const int SF_TL = 0x1; //���߶�Ӧ�ľ��ε����Ͻǿ��Ƶ㱻ѡ��
static const int SF_TR = 0x2; //���߶�Ӧ�ľ��ε����Ͻǿ��Ƶ㱻ѡ��
static const int SF_BR = 0x4; //���߶�Ӧ�ľ��ε����½ǿ��Ƶ㱻ѡ��
static const int SF_BL = 0x8; //���߶�Ӧ�ľ��ε����Ͻǿ��Ƶ㱻ѡ��
static const int SF_START = 0x10; //���ߵ���㱻ѡ��
static const int SF_END = 0x20; //���ߵ��յ㱻ѡ��
static const int SF_CONTENT = 0x40; //���߶�Ӧ�ľ�������ѡ��

//�������ߣ�ƫ�ƣ����Եı�
static const int ADJUST_TABLE[8][4] = 
{
	{0, 0, 0, 0},
	{1, 0, 0, 1},
	{0, 0, 1, 1},
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 1},
};

/**
\brief      getCursorShape
\Access    public static 
\param  int flag
\retval     Ws::CursorShape
\remark     ����ͼԪ��ѡ��״̬��ȡ��Ӧ�Ĺ��
*/
static Ws::CursorShape getCursorShape(int flag)
{
	switch(flag)
	{
	case SF_NONE : return Ws::ArrowCursor;
	case SF_TL : return Ws::SizeFDiagCursor;
	case SF_TR : return Ws::SizeBDiagCursor;
	case SF_BR : return Ws::SizeFDiagCursor;
	case SF_BL : return Ws::SizeBDiagCursor;
	case SF_START : return Ws::CrossCursor;
	case SF_END : return Ws::CrossCursor;
	case SF_CONTENT : return Ws::SizeAllCursor;
	default: return Ws::ArrowCursor;
	}
}

/************************************************************************/
/* returns intersect point of an ellipse and a directional line
	the ellipse is specified by @para rect
	the line is starting from the center of the above ellipse, with direction @para angle) */
/************************************************************************/
//static WWorldPointF point_on_ellipse(const WWorldRectF& rect, double angle)
//{
//	//ellipse parameter equation : x = a*cos��, y = a*sin��
//	//�� = atan2(a / b * sin(��), cos(��)), �� is input(radian of @para angle)
//
//	double a = rect.width() / 2;
//	double b = rect.height() / 2;
//
//	double �� = angle * M_PI / 180.0;
//	double �� = atan2(a * sin(��), b * cos(��)); //return value range [-��, ��]
//	//note!!!  �� and �� are in the same quadrant, so do not use the following formula,
//	//which may result in lose quadrant info
//	//double �� = atan(a / b * tan(��)); //return value range [-��/2, ��/2]
//	
//	WWorldPointF c(rect.center());
//	return WWorldPointF(c.x()+a*cos(��), c.y()+b*sin(��));
//}

/**
\brief      point_on_ellipse
\Access    public static 
\param  const WWorldRectF & rect
\param  double angle
\retval     WWorldPointF
\remark     ������Բ�ϵ�һ���㣬���������Բ���ĵ������������x�������angle���Ƕ��ƣ��Ƕ�
*/
static WWorldPointF point_on_ellipse(const WWorldRectF& rect, double angle)
{
	double a = rect.width() / 2;
	double b = rect.height() / 2;
	double �� = angle * M_PI / 180.0;

	return rect.center() + WWorldPointF(a*cos(��), b*sin(��));
}

//��̬ʶ���
RTTI_IMPL(WGraphicsArcItem)

char* WArcItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << rect << startAngle << endAngle << pen).value();
}

const char* WArcItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> rect >> startAngle >> endAngle >> pen).value();
}

size_t WArcItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << rect << startAngle << endAngle << pen).value();
}

WGraphicsArcItem::WGraphicsArcItem(const WWorldRectF& rect, double startAngle, double endAngle, const WPen& pen)
	: WGraphicsItem(new data_type(Type, rect, normalized_angle(startAngle), normalized_angle(endAngle), pen)),
	_select_flag(SF_NONE)
{
	_dragging = false;
	updateCp();
}

WGraphicsArcItem::WGraphicsArcItem(data_type* d) : WGraphicsItem(d ? d : new data_type), _select_flag(SF_NONE)
{
	_dragging = false;
	updateCp();
}

WWorldRectF WGraphicsArcItem::rect() const
{
	return data()->rect;
}

double WGraphicsArcItem::startAngle() const
{
	return data()->startAngle;
}

double WGraphicsArcItem::endAngle() const
{
	return data()->endAngle;
}

WPen WGraphicsArcItem::pen() const
{
	return data()->pen;
}

void WGraphicsArcItem::setRect(const WWorldRectF& rect, bool update, bool opStack)
{
	if (rect == data()->rect)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsArcItem::setRect, this, rect, true, false),
			WCmdFactory::create(&WGraphicsArcItem::setRect, this, data()->rect, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->rect = rect;
		updateCp();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->rect = rect;
		updateCp();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsArcItem::setAngle(double startAngle, double endAngle, bool update, bool opStack)
{
	startAngle = normalized_angle(startAngle);
	endAngle = normalized_angle(endAngle);

	if (wFuzzyCompare(startAngle, data()->startAngle) && wFuzzyCompare(endAngle, data()->endAngle))
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsArcItem::setAngle, this, startAngle, endAngle, true, false),
			WCmdFactory::create(&WGraphicsArcItem::setAngle, this, data()->startAngle, data()->endAngle, true, false));
	}

	data()->startAngle = startAngle;
	data()->endAngle = endAngle;
	updateCp();

	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsArcItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (pen == data()->pen)
	{
		return;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsArcItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WGraphicsArcItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;

	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsArcItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);

	if (isSelected()) //���ͼԪ��ѡ�оͻ�һ���߽����
	{
		painter->setBrush(WBrush());
		painter->setPen(WPen(Ws::DashLine, WColor(0, 0, 255), 1.0));
		painter->drawRect(data()->rect);
	}

	painter->setPen(data()->pen);
	double delta = data()->endAngle - data()->startAngle;
	painter->drawArc(data()->rect, data()->startAngle*16, (delta < 0 ? delta + 360 : delta)*16);

	if (isSelected()) //���ͼԪ��ѡ�оͻ������еĿ��Ƶ�
	{
		painter->setPen(CP_PEN);
		painter->setBrush(CP_BRUSH);
		for (unsigned i=0; i<array_size(_cp); ++i)
		{
			painter->drawEllipse(WWorldRectF(_cp[i].x() - CP_RADIUS, _cp[i].y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
		}
	}

	if (_dragging) //���ͼԪ���϶�
	{
		WPen dragPen = data()->pen;
		dragPen.setColor(dragPen.color().lighter(2.0));
		painter->setPen(dragPen);

		const WWorldRectF& r = data()->rect;
		WWorldPointF pos = scene()->mousePos();

		if (_select_flag == SF_START) //drag start point���϶����ߵ����
		{
			double startAngle = WWorldLineF(r.center(), pos).angle();
			double delta = data()->endAngle - startAngle;
			painter->drawArc(r, startAngle * 16, (delta < 0 ? delta + 360 : delta)*16);
		}
		else if (_select_flag == SF_END) //drag end point���϶����ߵ��յ�
		{
			double endAngle = WWorldLineF(r.center(), pos).angle();
			double delta = endAngle - data()->startAngle;
			painter->drawArc(r, data()->startAngle * 16, (delta < 0 ? delta + 360 : delta)*16);
		}
		else //�϶��������ߣ���һ�����߱�ʾ�϶��Ĺ���
		{
			WWorldPointF offset = pos - scene()->dragStartPos();
			const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];
			WWorldRectF rect = data()->rect.adjusted(offset.x() * f[0], offset.y() * f[1], offset.x() * f[2], offset.y() * f[3]);
			painter->drawArc(rect, data()->startAngle * 16, (delta < 0 ? delta + 360 : delta)*16);
		}
	}
}

/**
\brief      contains
\Access    virtual public 
\param  const WWorldPointF & point
\retval     bool
\remark     ͼԪ�Ƿ񱻰���ĳһ��
*/
bool WGraphicsArcItem::contains(const WWorldPointF& point) const
{
	if (isSelected()) //���ͼԪ��ѡ��
	{
		return data()->rect.adjusted(-CP_RADIUS, -CP_RADIUS, CP_RADIUS, CP_RADIUS).contains(point);
	}

	//ͼԪû�б�ѡ��

	WWorldPointF offset = point - data()->rect.center(); //�㵽���߶�Ӧ��Բ�����ĵ�ƫ������
	double theta = atan2(offset.y(), offset.x()) * 180.0 / M_PI; //�����ĽǶ�
	theta = normalized_angle(theta);

	bool b1 = data()->startAngle < data()->endAngle;
	bool b2 = in_range(data()->startAngle, data()->endAngle, theta);
	if ((b1 && b2) || (!b1 && !b2)) //�Ƕ��ڻ��ߵĽǶȷ�Χ��
	{
		double rate_x = 2.0 * offset.x() / data()->rect.width();
		double rate_y = 2.0 * offset.y() / data()->rect.height();
		double rate = rate_x * rate_x + rate_y * rate_y;
		static const double EPSILON = 0.05;
		if (fabs(rate - 1.0) < EPSILON) //�˵���뻡�ߺܽ�
		{
			return true;
		}
	}

	return false;
}

WWorldRectF WGraphicsArcItem::boundingRect() const
{
	return expanded(data()->rect);
}

void WGraphicsArcItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	bool contain = contains(event->scenePos());
	if (isSelectable() && !isSelected() && contain)//status transfer, not selected ---> selected
	{
		_select_flag = SF_CONTENT;
		setSelected();
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

		scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));
	}
	else if (isSelected() && !contain)//status transfer, selected ---> not selected
	{
		_select_flag = SF_NONE;
		setSelected(false);
		scene()->update(boundingRect());
		event->widget()->setCursor(WCursor(getCursorShape(_select_flag)));

		scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));
	}
}

void WGraphicsArcItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging)
	{
		_dragging = false;

		const WWorldRectF& r = data()->rect;
		WWorldPointF pos = event->scenePos();

		if (_select_flag == SF_START) //drag start point
		{
			setAngle(WWorldLineF(r.center(), pos).angle(), data()->endAngle, false, true);
		}
		else if (_select_flag == SF_END) //drag end point
		{
			setAngle(data()->startAngle, WWorldLineF(r.center(), pos).angle(), false, true);
		}
		else //�϶����߶�Ӧ�ľ��ο��Ƶ����������
		{
			WWorldPointF offset = pos - scene()->dragStartPos();
			const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];
			WWorldRectF rect = data()->rect.adjusted(offset.x() * f[0], offset.y() * f[1], offset.x() * f[2], offset.y() * f[3]);
			setRect(rect, false, true);
		}

		scene()->update();
	}
}

void WGraphicsArcItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = event->scenePos();

	if (isSelected()) //����ѡ��
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;

			WWorldRectF r = data()->rect;
			if ((_select_flag != SF_START) && (_select_flag != SF_END)) //���ѡ�е��Ǿ��εĿ��Ƶ����������
			{	
				const int (&f)[4] = ADJUST_TABLE[bit(_select_flag)];

				WWorldPointF offsetFrom = event->lastScenePos() - scene()->dragStartPos(); //ԭ�����϶�ƫ��
				WWorldPointF offsetTo = pos - scene()->dragStartPos(); //���ڵ��϶�ƫ��
				WWorldRectF rectFrom = data()->rect.adjusted(offsetFrom.x() * f[0], offsetFrom.y() * f[1], offsetFrom.x() * f[2], offsetFrom.y() * f[3]);
				WWorldRectF rectTo = data()->rect.adjusted(offsetTo.x() * f[0], offsetTo.y() * f[1], offsetTo.x() * f[2], offsetTo.y() * f[3]);
				r |= (rectFrom | rectTo);
			}

			scene()->update(expanded(r));
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
				unsigned i = 0;
				unsigned size = array_size(_cp);
				for (; i<size; ++i)
				{
					if (distance(pos, _cp[i]) < CP_RADIUS) //detect wheter control point is selected
					{
						_select_flag = (1 << i); //control point _cp[i] is presently selected
						break;
					}
				}

				if (i == size) //no control point is selected, that is, content is selected
				{
					_select_flag = SF_CONTENT;
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

int WGraphicsArcItem::type() const
{
	return Type;
}

void WGraphicsArcItem::updateCp()
{
	_cp[0] = data()->rect.topLeft();
	_cp[1] = data()->rect.topRight();
	_cp[2] = data()->rect.bottomRight();
	_cp[3] = data()->rect.bottomLeft();
	_cp[4] = point_on_ellipse(data()->rect, data()->startAngle);
	_cp[5] = point_on_ellipse(data()->rect, data()->endAngle);
}

WGraphicsArcItem::data_type* WGraphicsArcItem::data()
{
	return W_D();
}

const WGraphicsArcItem::data_type* WGraphicsArcItem::data() const
{
	return W_CD();
}

WGraphicsArcItem* WGraphicsArcItem::copy() const
{
	return new WGraphicsArcItem(new data_type(*data()));
}

void WGraphicsArcItem::translate(const WWorldPointF& offset)
{
	setRect(data()->rect.translated(offset));
}