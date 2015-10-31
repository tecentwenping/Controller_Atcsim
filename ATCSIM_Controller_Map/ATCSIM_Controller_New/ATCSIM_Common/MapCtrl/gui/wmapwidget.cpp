#include <QMenu>
#include <QToolTip>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QSignalMapper>
#include <boost/foreach.hpp>
#include <iostream>
#include "../wdllexport.h"
#include "wqtpainter.h"
#include "guitransform.h"
#include "wmapwidget.h"
#include "../core/wevent.h"
#include "../core/wgraphicsscene.h"
#include "../creator/wabstractcreator.h"

WMapWidget::WMapWidget(WGraphicsScene* scene) : WGraphicsView(scene), _creator(0)
{
	qRegisterMetaType<WWorldRectF>();

	//�����˵����������
	_contextMenu = new QMenu(this);
	
	actions[0] = _contextMenu->addAction("NormalSize");
	actions[1] = _contextMenu->addAction("ZoomIn");
	actions[2] = _contextMenu->addAction("ZoomOut");
	_contextMenu->addSeparator();
	actions[3] = _contextMenu->addAction("Copy");
	actions[4] = _contextMenu->addAction("Paste");
	_contextMenu->addSeparator();
	actions[5] = _contextMenu->addAction("AddVertex");
	actions[6] = _contextMenu->addAction("DeleteVertex");

	QSignalMapper* signalMapper = new QSignalMapper(this);
	for (size_t i=0; i<array_size(actions); ++i)
	{
		connect(actions[i], SIGNAL(triggered()), signalMapper, SLOT(map()));
		signalMapper->setMapping(actions[i], i);
	}
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onContextMenu(int)));

	setMouseTracking(true); //��������ǿ��Ը��ٵģ�������ӦmouseMove�¼�

	setEnableDrag(true);
	setEnableWheelScale(true);
}

void WMapWidget::updateScene(const WWorldRectF& rect)
{
	//QMetaObject::invokeMethod(this, "updateSceneSlot", Qt::AutoConnection, Q_ARG(WWorldRectF, rect));
	updateSceneSlot(rect);
}

void WMapWidget::updateSceneSlot(const WWorldRectF& rect)
{
	WWorldRectF r = worldTransform().mapRect(rect);
	if (r.isEmpty())
	{
		update();
	}
	else
	{
		update(transform(r).toRect());
	}
}

WCursor WMapWidget::cursor() const
{
	return transform(QWidget::cursor());
}

/**
\brief      paintEvent
\Access    virtual protected 
\param  QPaintEvent * event
\retval     void
\remark     �Ȼ���һ��ͼƬ��Ȼ��ͼƬ����������������
				��ͼƬ���Ȼ��Ʊ������ٻ��Ƴ����е�����
*/
void WMapWidget::paintEvent(QPaintEvent* event)
{
	QPalette p = palette();
	const QColor BK_COLOR = p.color(QPalette::Background);
	const QBrush BK_BRUSH(BK_COLOR);
	const QPen BK_PEN(BK_COLOR);

	QSize sz = dynamic_cast<QWidget*>(this)->size();

	if (_bufferPixmap.size() != sz)
	{
		_bufferPixmap.~QPixmap();
		new (&_bufferPixmap) QPixmap(sz);
	}
    //���ؾ���������
	WMatrix matrix_1 = worldTransform().inverted();

	QRectF r = event->rect();

	QPainter painter(&_bufferPixmap);
	painter.setBrush(BK_BRUSH);
	painter.setPen(BK_PEN);
	painter.drawRect(r); //fill background
	//These hints are used to initialize QPainter before each visible item is drawn
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	WQtPainter qp(this, &painter);
	qp.setWorldTransform(worldTransform());
	WGraphicsView::render(&qp, matrix_1.mapRect(transform(r)));

	QPainter painterWidget(this);
	painterWidget.drawPixmap(0, 0, _bufferPixmap);
}

void WMapWidget::setCursor(const WCursor& cursor)
{
	QWidget::setCursor(transform(cursor));
}

void WMapWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (!scene())
	{
		return;
	}

	WMatrix matrix = worldTransform().inverted();

	WGraphicsSceneMouseEvent e;
	e.setWidget(this);
	e.setButton(static_cast<Ws::MouseButton>(event->button()));
	e.setButtons(static_cast<Ws::MouseButtons>(event->buttons()));
	e.setModifiers(static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setScenePos(matrix.map(transform(event->posF())));
	e.setLastScenePos(matrix.map(transform(_lastPos)));

	if (_creator) //��ͼ�������ڽ���
	{
		_creator->mouseDoubleClickEvent(&e);
	}
	else
	{
		scene()->mouseDoubleClickEvent(&e);
	}

	_lastPos = event->posF();
}

void WMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (!scene())
	{
		return;
	}

	WMatrix matrix = worldTransform().inverted();


	WGraphicsSceneMouseEvent e;
	e.setWidget(this);
	e.setButtons(static_cast<Ws::MouseButtons>(event->buttons()));
	e.setModifiers(static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setScenePos(matrix.map(transform(event->posF())));
	e.setLastScenePos(matrix.map(transform(_lastPos)));
	e.setScreenPos(transform(event->pos()));
	e.setLastScreenPos(transform(QPoint(_lastPos.x(), _lastPos.y())));

	if (_creator) //���Ƚ��¼����ݸ�creator
	{
		_creator->mouseMoveEvent(&e);

		/*static bool b = true;
		b = !b;

		if (!_tip.isEmpty())
		{
			QToolTip::showText(QCursor::pos(), b ? _tip : _tip+QString(" "), this);
		}*/
	}
	else
	{
		emit mouseMoved(e.scenePos());

		if (editable() | !(e.buttons() & Ws::LeftButton)) //��ͼ�ɱ༭ or �����������
		{
			scene()->mouseMoveEvent(&e); //���¼����ݸ�����
			if ((e.buttons() & Ws::LeftButton) && !scene()->hasSelectedItem()
				&& _bEnableDrag) //������� && ������û��ͼԪ��ѡ��
			{
				_offset = event->posF() - _lastPos;
				translate(transform(_offset)); //�ƶ���ͼ
				updateScene();
			}
		}
		else if (_bEnableDrag)//�ƶ���ͼ
		{
			_offset = event->posF() - _lastPos;
			translate(transform(_offset));
			updateScene();
		}
	}

	_lastPos = event->posF();
}

void WMapWidget::mousePressEvent(QMouseEvent* event)
{
	if (!scene())
	{
		return;
	}

	WMatrix matrix = worldTransform().inverted();

	WGraphicsSceneMouseEvent e;
	e.setWidget(this);
	e.setButton(static_cast<Ws::MouseButton>(event->button()));
	e.setButtons(static_cast<Ws::MouseButtons>(event->buttons()));
	e.setModifiers(static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setScenePos(matrix.map(transform(event->posF())));
	e.setLastScenePos(matrix.map(transform(_lastPos)));
	e.setScreenPos(transform(event->pos()));
	e.setLastScreenPos(transform(QPoint(_lastPos.x(), _lastPos.y())));

	if (_creator) //��ͼ�������ڽ���
	{
		_creator->mousePressEvent(&e);
	}
	else if (editable()) //��ͼ�ɱ༭
	{
		scene()->mousePressEvent(&e);
	}

	_lastPos = event->posF();
}

void WMapWidget::mouseReleaseEvent(QMouseEvent* event)
{

	if (!scene())
	{
		return;
	}

	const WMatrix& matrix = worldTransform().inverted();

	WGraphicsSceneMouseEvent e;
	e.setWidget(this);
	e.setButton(static_cast<Ws::MouseButton>(event->button()));
	e.setButtons(static_cast<Ws::MouseButtons>(event->buttons()));
	e.setModifiers(static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setScenePos(matrix.map(transform(event->posF())));
	e.setLastScenePos(matrix.map(transform(_lastPos)));
	e.setScreenPos(transform(event->pos()));
	e.setLastScreenPos(transform(QPoint(_lastPos.x(), _lastPos.y())));

	if (_creator) //��ͼ�������ڽ���
	{
		_creator->mouseReleaseEvent(&e);
	}
	else if (editable()) //��ͼ���Ա༭
	{
		scene()->mouseReleaseEvent(&e);
	}

	_lastPos = event->posF();
}

void WMapWidget::keyPressEvent(QKeyEvent* event)
{
	if (!scene())
	{
		return;
	}

	WKeyEvent e(WEvent::KeyPress, event->key(), static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setWidget(this);
	scene()->keyPressEvent(&e);
}

void WMapWidget::keyReleaseEvent(QKeyEvent* event)
{
	if (!scene())
	{
		return;
	}

	WKeyEvent e(WEvent::KeyRelease, event->key(), static_cast<Ws::KeyboardModifiers>(event->modifiers()));
	e.setWidget(this);
	scene()->keyReleaseEvent(&e);
}

/**
\brief      wheelEvent
\Access    virtual protected 
\param  QWheelEvent * event
\retval     void
\remark     �������¼�
*/
void WMapWidget::wheelEvent(QWheelEvent* event)
{
	if (!_bEnableWheelScale)
	{
		return;
	}

	static const double FACTOR = 1.04;
	static const double FACTOR_1 = 1.0 / FACTOR;

	const double& factor = event->delta() > 0 ? FACTOR : FACTOR_1;
	scale(factor, true);
}

void WMapWidget::onFinished()
{
	_creator->disconnect(this);
	_creator = 0;
	emit createFinished();
}

void WMapWidget::onTip(const QString& tip)
{
	_tip = tip;
	emit createTip(tip);
}

void WMapWidget::onDelete()
{
	if (!scene())
	{
		return;
	}

	scene()->removeSelectedItems(true, true);
	setCursor(WCursor(Ws::ArrowCursor));
}

void WMapWidget::onClear()
{
	if (!scene())
	{
		return;
	}

	scene()->removeAllLayers(true);
}

void WMapWidget::scale(double factor, bool combine)
{
	if (!scene())
	{
		return;
	}

	const WMatrix& matrix = worldTransform();
	bool changed = false;
	double factorOrg = fabs(matrix.m11());

	if (!combine)
	{
		if (!wFuzzyCompare(factor, factorOrg))
		{
			factor /= factorOrg;
			changed = true;
		}
	}
	else if (!wFuzzyCompare(factor, 1.0))
	{
		changed = true;
	}

	if (changed) //����������ӷ����ı�
	{
		WWorldPointF c = matrix.inverted().map(transform(QPointF(rect().center()))); // ��Ļ���ĵ�ӳ�䵽������
		WMatrix m = matrix;
		m.translate(c).scale(factor, factor).translate(-c);
		setWorldTransform(m);
		updateScene();
		emit scaled(fabs(m.m11()));
	}
}

bool WMapWidget::isCreating() const
{
	return _creator != 0;
}

void WMapWidget::onContextMenu(int id)
{
	WGraphicsView::onContextMenu(static_cast<Ws::ContextMenuFlag>(1 << id));
}

void WMapWidget::requestContextMenu(Ws::ContextMenuFlags flags)
{
	for (size_t i=0; i<array_size(actions); ++i)
	{
		actions[i]->setEnabled(flags & (1 << i));
	}
	//_contextMenu->exec(QCursor::pos());
}

const QPixmap& WMapWidget::backgroundPixmap() const
{
	return _bgPixmap;
}

void WMapWidget::setBackgroudPixmap(const QPixmap& pixmap)
{
	_bgPixmap = pixmap;
	update();
}

void WMapWidget::startCreator(WAbstractCreator* creator)
{
	if (!scene())
	{
		return;
	}

	_tip.clear();
	_creator = creator;
	connect(_creator, SIGNAL(finished(WGraphicsItem*)), this, SLOT(onFinished()));
	connect(_creator, SIGNAL(geometry(const QString&)), this, SIGNAL(createGeometry(const QString&)));
	connect(_creator, SIGNAL(tip(const QString&)), this, SLOT(onTip(const QString&)));
	_creator->start();
}

WWorldSizeF WMapWidget::size() const
{
	QSizeF sz(dynamic_cast<const QWidget*>(this)->size());
	return WWorldSizeF(sz.width(), sz.height());
}

/**
\brief      SetBackGroundColor
\Access    public 
\param  const QColor & color
\retval     void
\remark     
*/
void WMapWidget::setBackgroundColor( const QColor &color )
{
	QPalette pal = palette();
	pal.setColor(QPalette::Window, color);
	setPalette(pal);
}

/**
\brief      GetBackGroundColor
\Access    public 
\param  QColor & color
\retval     void
\remark     
*/
void WMapWidget::getBackgroundColor( QColor &color )
{
	QPalette pal = palette();
	color = pal.color(QPalette::Window);
}

/**
\brief      setEnableDrag
\Access    public 
\param  bool bEnable
\retval     void
\remark     
*/
void WMapWidget::setEnableDrag( bool bEnable )
{
	_bEnableDrag = bEnable;
}

/**
\brief      setEnableWheelScale
\Access    public 
\param  bool bEnable
\retval     void
\remark     
*/
void WMapWidget::setEnableWheelScale( bool bEnable )
{
	_bEnableWheelScale = bEnable;
}

void WMapWidget::mouseMoved( const WWorldPointF& pos )
{

}

void WMapWidget::scaled( double factor )
{

}

void WMapWidget::createGeometry( const QString& )
{

}

void WMapWidget::createTip( const QString& )
{

}

void WMapWidget::createFinished()
{

}

#include "moc_wmapwidget.cpp"