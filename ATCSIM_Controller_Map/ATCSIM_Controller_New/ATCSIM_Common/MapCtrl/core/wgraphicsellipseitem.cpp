#include "../wdllexport.h"
#include "wpainter.h"
#include "wpainterproxy.h"
#include "wgraphicsscene.h"
#include "wgraphicsellipseitem.h"

//ѡ�б�ʶ
//select flag--->SF
//left--->L
//right--->R
//top--->T
//bottom--->B
//center--->C
static const int SF_NONE = 0x0; //û�б�ѡ��
static const int SF_TL = 0x1; //��Բ��Ӧ�ľ��ε�top left��ѡ��
static const int SF_TC = 0x2; //~top center~
static const int SF_TR = 0x4; //~top right~
static const int SF_RC = 0x8; //~right center~
static const int SF_BR = 0x10; //~bottom right~
static const int SF_BC = 0x20; //~bottom center~
static const int SF_BL = 0x40; //~bottom left~
static const int SF_LC = 0x80; //~left center~
static const int SF_CONTENT = 0x100; //��Բ��Ӧ���������α�ѡ��
static const int SF_ROTATE = 0x200; //��Բ����ת�㱻ѡ��

//��Բ��Ӧ�ľ���ƫ�Ƶ���
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

/**
\brief      point_in_ellipse
\Access    public static 
\param  const WWorldRectF & r
\param  const WWorldPointF & p
\retval     bool
\remark     �ж�ĳһ���Ƿ�����Բ��
		(x - x0)^2 / a^2 + (y - y0)^2 / b^2 = 1
		�ж�ĳһ���Ƿ�����Բ��ֻ���������̵���ߵ�ֵС��1����
*/
static bool point_in_ellipse(const WWorldRectF& r, const WWorldPointF& p)
{
	WWorldPointF offset = p - r.center();
	double rx = offset.x() / r.width() * 2;
	double ry = offset.y() / r.height() * 2;
	return rx * rx + ry * ry <= 1;
}

RTTI_IMPL(WGraphicsEllipseItem)

WGraphicsEllipseItem::WGraphicsEllipseItem(const WWorldRectF& r, const WBrush& b, const WPen& p, double ag)
: WGraphicsRectItem(r, b, p, ag)
{
}

WGraphicsEllipseItem::WGraphicsEllipseItem(data_type* d) : WGraphicsRectItem(d ? d : new data_type)
{
}

void WGraphicsEllipseItem::paint(WPainter* painter)
{
	WPainterProxy proxy(painter);
	painter->setWorldTransform(getRotateMatrix(), true); //������ת����

	if (isSelected()) //ѡ�к���Ʊ߽����
	{
		painter->setBrush(WBrush());
		painter->setPen(HOVER_PEN);
		painter->drawRect(data()->rect);
	}

	painter->setBrush(brush());
	painter->setPen(pen());
	painter->drawEllipse(data()->rect); //������Բ

	if (isSelected()) //ѡ�к���ƿ��Ƶ�
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

	if (_dragging) //��������϶��ͻ�����һ����Բ
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
				painter->drawEllipse(data()->rect.adjusted(offset.x() * f[0], offset.y() * f[1], offset.x() * f[2], offset.y() * f[3]));
			}
		}
		else
		{
			painter->setWorldTransform(getRotateMatrix_1(), true);

			WWorldPointF c = data()->rect.center();
			double ag = WWorldLineF(c, pos).angle() - 90;
			painter->setWorldTransform(WMatrix().translate(-c.x(), -c.y()) * WMatrix().rotate(ag + data()->angle) * WMatrix().translate(c.x(), c.y()));
			painter->drawEllipse(data()->rect);
		}
	}
}

bool WGraphicsEllipseItem::contains(const WWorldPointF& point) const
{
	bool b = data()->rect.adjusted(-CP_RADIUS, -CP_RADIUS, CP_RADIUS, CP_RADIUS).contains(point);
	return isSelected() ? (b || distance(point, _rotate_pt) < CP_RADIUS) : point_in_ellipse(data()->rect, point);
}
	

int WGraphicsEllipseItem::type() const
{
	return Type;
}

WGraphicsEllipseItem* WGraphicsEllipseItem::copy() const
{
	return new WGraphicsEllipseItem(new data_type(*data()));
}

/**
\brief      attachPoint
\Access    virtual public 
\param  const WWorldPointF & pos
\param  WWorldPointF * attachedPos
\retval     bool
\remark     ����������
*/
bool WGraphicsEllipseItem::attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const
{
	static const double EPSILON = 0.1;

	const WWorldRectF& r = data()->rect;
	double a = r.width() / 2;
	double b = r.height() / 2;
	WWorldPointF c = r.center();
	WWorldPointF offset = pos - c;
	double rate_x = offset.x() / a;
	double rate_y = offset.y() / b;
	double rate = rate_x * rate_x + rate_y * rate_y;
	
	if (fabs(rate - 1.0) < EPSILON) //������Բ�ϣ����������ĵ�
	{
		if (attachedPos)
		{
			double �� = atan2(offset.y(), offset.x());
			�� = atan2(a * sin(��), b * cos(��));
			attachedPos->setXY(c.x() + a * cos(��), c.y() + b * sin(��));
		}
		return true;
	}
	return false;
}