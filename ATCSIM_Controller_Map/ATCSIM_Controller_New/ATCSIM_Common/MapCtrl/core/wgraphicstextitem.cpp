#include "../wdllexport.h"
#include "wevent.h"
#include "wcursor.h"
#include "wmatrix.h"
#include "wpainter.h"
#include "wserialize.h"
#include "wcmdfactory.h"
#include "wfontmetrics.h"
#include "wpainterproxy.h"
#include "wgraphicsview.h"
#include "wgraphicsscene.h"
#include "woperationstack.h"
#include "wgraphicschange.h"
#include "wgraphicstextitem.h"

static const int SF_NONE = 0x0;
static const int SF_CONTENT = 0x1;
static const int SF_ROTATE = 0x2;

/**
\brief      getCursorShape
\Access    public static 
\param  int flag
\retval     Ws::CursorShape
\remark     根据选中状态获取相应的光标形状
*/
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

/**
\brief      text_lines
\Access    public static 
\param  const std::string & text
\retval     unsigned
\remark     !!!!!!!!!此函数废弃不用了
*/
static unsigned text_lines(const std::string& text)
{
	unsigned cnt = 0;
	std::string::size_type pos = 0;
	
	if (!text.empty())
	{
		while (pos != std::string::npos)
		{
			++cnt;
			pos = text.find('\n', pos + 1);
		}
	}

	return cnt;
}

/**
\brief      line_max_chars
\Access    public static 
\param  const std::string & text
\retval     unsigned
\remark     !!!!!!!!!!!!!!此函数废弃不用了
*/
static unsigned line_max_chars(const std::string& text)
{
	unsigned max_chars = 0;
	unsigned curr_max_chars = 0;
	std::string::size_type pos = 0;

	while (pos != std::string::npos)
	{
		std::string::size_type p = text.find('\n', pos);
		curr_max_chars = (p == std::string::npos ? text.size() : p) - pos;
		max_chars = wMax(max_chars, curr_max_chars);
		pos = (p == std::string::npos) ? p : p + 1;
	}

	return max_chars;
}

RTTI_IMPL(WGraphicsTextItem)

char* WTextItemData::serialize(char* buf) const
{
	return (WSerializer(WItemData::serialize(buf)) << pos << text << font << pen << angle).value();
}

const char* WTextItemData::unserialize(const char* buf)
{
	return (WUnserializer(WItemData::unserialize(buf)) >> pos >> text >> font >> pen >> angle).value();
}

size_t WTextItemData::serialize_size() const
{
	return (WSizeHelper(WItemData::serialize_size()) << pos << text << font << pen << angle).value();
}

WGraphicsTextItem::WGraphicsTextItem(const WWorldPointF& pos, const std::string& text, const WFont& font, const WPen& pen, double angle) : 
WGraphicsItem(new data_type(Type, pos, text, font, pen, angle)), _select_flag(SF_NONE), _fx(1.0), _fy(1.0)
{
	updateBoundRect();
}

WGraphicsTextItem::WGraphicsTextItem(WTextItemData* d) :
	WGraphicsItem(d ? d : new data_type), _select_flag(SF_NONE), _fx(1.0), _fy(1.0)
{
	updateBoundRect();
}

WWorldPointF WGraphicsTextItem::pos() const
{
	return data()->pos;
}

std::string WGraphicsTextItem::text() const
{
	return data()->text;
}

WFont WGraphicsTextItem::font() const
{
	return data()->font;
}

WPen WGraphicsTextItem::pen() const
{
	return data()->pen;
}

double WGraphicsTextItem::angle() const
{
	return data()->angle;
}

void WGraphicsTextItem::setPos(const WWorldPointF& p, bool update, bool opStack)
{
	if (p == data()->pos)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsTextItem::setPos, this, p, true, false),
			WCmdFactory::create(&WGraphicsTextItem::setPos, this, data()->pos, true, false));
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

void WGraphicsTextItem::setText(const std::string& t, bool update, bool opStack)
{
	if (t == data()->text)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsTextItem::setText, this, t, true, false),
			WCmdFactory::create(&WGraphicsTextItem::setText, this, data()->text, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->text = t;
		updateBoundRect();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->text = t;
		updateBoundRect();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsTextItem::setFont(const WFont& f, bool update, bool opStack)
{
	if (f == data()->font)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsTextItem::setFont, this, f, true, false),
			WCmdFactory::create(&WGraphicsTextItem::setFont, this, data()->font, true, false));
	}

	if (update)
	{
		WWorldRectF r = boundingRect();
		data()->font = f;
		updateBoundRect();
		scene()->update(r | boundingRect());
	}
	else
	{
		data()->font = f;
		updateBoundRect();
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsTextItem::setPen(const WPen& pen, bool update, bool opStack)
{
	if (pen == data()->pen)
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsTextItem::setPen, this, pen, true, false),
			WCmdFactory::create(&WGraphicsTextItem::setPen, this, data()->pen, true, false));
	}

	data()->pen = pen;
	if (update)
	{
		scene()->update(boundingRect());
	}

	scene()->itemChange(WGraphicsChange(WGraphicsChange::GenericChange, this));
}

void WGraphicsTextItem::setAngle(double angle, bool update, bool opStack)
{
	if (wFuzzyCompare(angle, data()->angle))
	{
		return ;
	}

	if (opStack)
	{
		scene()->operationStack()->push(WCmdFactory::create(&WGraphicsTextItem::setAngle, this, angle, true, false),
			WCmdFactory::create(&WGraphicsTextItem::setAngle, this, data()->angle, true, false));
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

int WGraphicsTextItem::type() const
{
	return Type;
}

WGraphicsTextItem::data_type* WGraphicsTextItem::data()
{
	return W_D();
}

const WGraphicsTextItem::data_type* WGraphicsTextItem::data() const
{
	return W_CD();
}

WGraphicsTextItem* WGraphicsTextItem::copy() const
{
	return new WGraphicsTextItem(new data_type(*data()));
}

WMatrix WGraphicsTextItem::getRotateMatrix() const
{
	WWorldPointF c = _bound_rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * (isScalable() ? WMatrix() : WMatrix().scale(fabs(1/_fx), fabs(1/_fy))) * WMatrix().rotate(data()->angle) * WMatrix().translate(c.x(), c.y());
}

WMatrix WGraphicsTextItem::getRotateMatrix_1() const
{
	WWorldPointF c = _bound_rect.center();
	return WMatrix().translate(-c.x(), -c.y()) * (isScalable() ? WMatrix() : WMatrix().scale(fabs(_fx), fabs(_fy))) * WMatrix().rotate(-data()->angle) * WMatrix().translate(c.x(), c.y());
}

//void WGraphicsTextItem::updateBoundRect()
//{
//	unsigned pointSize = data()->font.pointSize();
//	unsigned w = line_max_chars(data()->text) * pointSize * 4 / 5;
//	unsigned h = pointSize * 2 * text_lines(data()->text);
//	_bound_rect = WWorldRectF(data()->pos, WWorldSizeF(w, h));
//	_rotate_pt.setXY((_bound_rect.left()+_bound_rect.right())/2, _bound_rect.top() + CP_ROTATE_HEADER);
//}

void WGraphicsTextItem::updateBoundRect()
{
	WFontMetrics metrics(data()->font);
	_bound_rect = WWorldRectF(data()->pos, WWorldSizeF(metrics.width(data()->text), metrics.height()));
	_rotate_pt.setXY((_bound_rect.left()+_bound_rect.right())/2, _bound_rect.top() + CP_ROTATE_HEADER);
}

WWorldRectF WGraphicsTextItem::boundingRect() const
{
	return getRotateMatrix().mapRect(_bound_rect.adjusted(-2*CP_RADIUS, -2*CP_RADIUS, 2*CP_RADIUS, 2*CP_RADIUS+CP_ROTATE_HEADER));
}

bool WGraphicsTextItem::contains(const WWorldPointF& point) const
{
	bool b = _bound_rect.adjusted(-CP_RADIUS, -CP_RADIUS, CP_RADIUS, CP_RADIUS).contains(point);
	return isSelected() ? (b || distance(point, _rotate_pt) < CP_RADIUS) : b;
}

void WGraphicsTextItem::paint(WPainter* painter)
{
	if (!isScalable()) //如果文本不支持放缩
	{
		WMatrix m = painter->worldTransform();
		_fx = fabs(m.m11());
		_fy = fabs(m.m22());
	}

	{
		WPainterProxy proxy(painter);

		painter->setWorldTransform(getRotateMatrix(), true); //设置旋转矩阵( 设置按矩形中心旋转，如果不设置将按场景原点旋转）



		if (isSelected()) //文本被选中
		{
			painter->setPen(HOVER_PEN);
			painter->setBrush(WBrush());
			painter->drawRect(_bound_rect); //绘制文本边框
			painter->drawLine(WWorldLineF(_rotate_pt, WWorldPointF(_rotate_pt.x(), _bound_rect.top())));

			painter->setPen(CP_PEN);
			painter->setBrush(ROTATE_BRUSH);
			//绘制文本旋转控制点
			painter->drawEllipse(WWorldRectF(_rotate_pt.x() - CP_RADIUS, _rotate_pt.y() - CP_RADIUS, CP_RADIUS * 2, CP_RADIUS * 2));
		}

		painter->setPen(data()->pen);
		painter->setFont(data()->font);
		const WPointF& p = _bound_rect.center();
		painter->setWorldTransform(WMatrix().translate(p.x(), p.y()).scale(1, -1).translate(-p.x(), -p.y()), true);
		painter->drawText(_bound_rect, 0/*Ws::AlignCenter*/, data()->text);
	}

	if (_dragging) //文本在拖动
	{
		WPainterProxy proxy(painter);
		if (_select_flag & SF_CONTENT) //文本在平移，绘制平移后的文本
		{
			WWorldPointF offset = scene()->mousePos() - scene()->dragStartPos();
			WWorldRectF br = _bound_rect.translated(offset);
			WWorldPointF c = br.center();

			WMatrix matrix =  WMatrix().translate(-c.x(), -c.y()) * (isScalable() ? WMatrix() : WMatrix().scale(fabs(1/_fx), fabs(1/_fy))) * WMatrix().rotate(data()->angle) * WMatrix().translate(c.x(), c.y());
			painter->setWorldTransform(matrix, true);

			WPen dragPen = data()->pen;
			dragPen.setColor(dragPen.color().lighter(2.0));
			painter->setPen(dragPen);
			painter->setFont(data()->font);
			painter->drawText(br, 0/*Ws::AlignCenter*/, data()->text);
		}
		else if (_select_flag & SF_ROTATE) //文本在旋转，绘制旋转后的文本
		{
			WWorldPointF pos = scene()->mousePos();
			WWorldPointF c = _bound_rect.center();
			double ag = normalized_angle(WWorldLineF(c, pos).angle() - 90);
			WMatrix m = WMatrix().translate(-c.x(), -c.y()) * (isScalable() ? WMatrix() : WMatrix().scale(fabs(1/_fx), fabs(1/_fy))) * WMatrix().rotate(ag) * WMatrix().translate(c.x(), c.y());
			painter->setWorldTransform(m, true);
			painter->setBrush(WBrush());
			painter->setPen(DRAG_PEN);
			painter->drawRect(_bound_rect);
		}
	}
}

void WGraphicsTextItem::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	WWorldPointF pos = getRotateMatrix_1().map(event->scenePos());

	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			_dragging = true;

			if (_select_flag & SF_CONTENT)
			{
				WWorldRectF r = boundingRect();
				WWorldRectF rectFrom = r.translated(event->lastScenePos() - scene()->dragStartPos());
				WWorldRectF rectTo = r.translated(event->scenePos() - scene()->dragStartPos());
				scene()->update(r | rectFrom | rectTo);
			}
			else if (_select_flag & SF_ROTATE)
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

void WGraphicsTextItem::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	bool contain = contains(getRotateMatrix_1().map(event->scenePos()));
	if (!isSelected() && contain) //status transfer, not selected ---> selected
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

void WGraphicsTextItem::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected() && (event->button() == Ws::LeftButton) && _dragging) //左键释放，并且在拖动
	{
		_dragging = false;

		if (_select_flag & SF_CONTENT) //文本在平移
		{
			setPos(data()->pos + event->scenePos() - scene()->dragStartPos(), false, true);
		}
		else if (_select_flag & SF_ROTATE) //文本在旋转
		{
			setAngle(normalized_angle(WWorldLineF(_bound_rect.center(), event->scenePos()).angle() - 90.0), false, true);
		}

		scene()->update();
	}
}

void WGraphicsTextItem::translate(const WWorldPointF& offset)
{
	setPos(data()->pos + offset);
}