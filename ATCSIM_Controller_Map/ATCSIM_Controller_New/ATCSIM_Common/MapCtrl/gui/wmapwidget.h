/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wmapwidget.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫ����WMapWidget��
  ����  ����:   
******************************************************************************/
#ifndef _WMAP_WIDGET_H_
#define _WMAP_WIDGET_H_

#include <vector>
#include <QWidget>
#include <QPixmap>
#include <QMetaType>
#include "../wdllimport.h"
#include "../core/wgraphicsview.h"

class QMenu;
class WAbstractCreator;

Q_DECLARE_METATYPE(WWorldRectF);

/** 
 \brief                 ������Qt�Ĵ�����ʵ����һ��WGraphicsView��������нӿ�
\details   �����ʵ��WGraphicsView�е���ӿڣ����ڽӿڵĺ���˴�����׸��
 \author    ����
\date      2013/05/29
*/
class MAPAPI WMapWidget : public QWidget, public WGraphicsView
{
	//Q_OBJECT

public:
	explicit WMapWidget(WGraphicsScene* scene);

	virtual void updateScene(const WWorldRectF& rect = WWorldRectF());

	virtual WCursor cursor() const;
	virtual void setCursor(const WCursor& cursor);

	virtual WWorldSizeF size() const;

	virtual void requestContextMenu(Ws::ContextMenuFlags flags);

	WAbstractCreator* GetCurCreatorPtr() {return _creator;}

	
	/**
	\brief      setEnableDrag
	\Access    public 
	\param  bool bEnable
	\retval     void
	\remark     Ĭ������϶���ͼʵ�֣�����϶���ͼ�����Ƿ񼤻Ĭ�ϼ���
	*/
	void setEnableDrag(bool bEnable);

	/**
	\brief      setEnableWheelScale
	\Access    public 
	\param  bool bEnable
	\retval     void
	\remark     Ĭ��������ŵ�ͼʵ�֣��м����������Ƿ񼤻Ĭ�ϼ���
	*/
	void setEnableWheelScale(bool bEnable);
	/**
	\brief      isCreating
	\Access    public 
	\retval     bool
	\remark     �����Ƿ��ڴ���ͼԪ�ı�ʶ
	*/
	bool isCreating() const;

	/**
	\brief      backgroundPixmap
	\Access    public 
	\retval     const QPixmap&
	\remark     ���ر���ͼƬ
	*/
	const QPixmap& backgroundPixmap() const;

	/**
	\brief      setBackgroudPixmap
	\Access    public 
	\param  const QPixmap & pixmap
	\retval     void ���ñ���ͼƬ
	\remark     
	*/
	void setBackgroudPixmap(const QPixmap& pixmap);

	
	/**
	\brief      setBackgroundColor
	\Access    public 
	\param  const QColor & color
	\retval     void
	\remark     ���ñ�����ɫ
	*/
	void setBackgroundColor(const QColor &color);


	/**
	\brief      getBackgroundColor
	\Access    public 
	\param  QColor & color
	\retval     void
	\remark     ��ȡ������ɫ
	*/
	
	void getBackgroundColor(QColor &color);


	/**
	\brief      startCreator
	\Access    public 
	\param  WAbstractCreator * creator
	\retval     void
	\remark     ����һ����ͼ����
					��ͼ�����г������¼�ȫ������creator����ֱ����ͼ���̽�����
					��ʱthis�ᷢ��createFinished�źţ�creatorҲ�ᷢ�����ź�
	*/
	void startCreator(WAbstractCreator* creator);
	
public slots:
	/**
	\brief      scale
	\Access    public 
	\param  double factor
	\param  bool combine
				 ���Ϊtrue������ԭ���Ļ����Ͻ��з�����Ҳ�����µķ�������Ϊf = f * factor
				 ���Ϊfalse����ԭ���ķ��������޸�Ϊfactor������f = factor
	\retval     void
	\remark     �Ե�ͼ���з�������
	*/
	void scale(double factor, bool combine = false);

	/**
	\brief      updateSceneSlot
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     ���³������ػ棩�Ĳ�
	*/
	void updateSceneSlot(const WWorldRectF& rect);

private slots:
	/**
	\brief      onClear
	\Access    private 
	\retval     void
	\remark     ������������е�ͼ��
	*/
	void onClear();

	/**
	\brief      onDelete
	\Access    private 
	\retval     void
	\remark     ɾ������������ѡ�е�ͼԪ
	*/
	void onDelete();

	/**
	\brief      onFinished
	\Access    private 
	\retval     void
	\remark     ��startCreator������creator��ͼ�������
	*/
	void onFinished();

	/**
	\brief      onTip
	\Access    private 
	\param  const QString &
	\retval     void
	\remark     !!!!!! ����
	*/
	void onTip(const QString&);

	/**
	\brief      onContextMenu
	\Access    private 
	\param  int id
	\retval     void
	\remark     ��Ӧ�Ҽ��˵�
	*/
	void onContextMenu(int id);
	
protected:
	virtual void paintEvent(QPaintEvent*);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void wheelEvent(QWheelEvent* event);

signals:
	/**
	\brief      createFinished
	\Access    protected 
	\retval     void
	\remark     ��startCreator������creator��ͼ������ɵ��ź�
	*/
	void createFinished();

	///**
	//\brief      createTip
	//\Access    protected 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!!����
	//*/
	void createTip(const QString&);

	///**
	//\brief      createGeometry
	//\Access    protected 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!����
	//*/
	void createGeometry(const QString&);

	/**
	\brief      scaled
	\Access    protected 
	\param  double factor �µķ�������
	\retval     void
	\remark     ��ͼ���������ź�
	*/
	void scaled(double factor);

	/**
	\brief      mouseMoved
	\Access    protected 
	\param  const WWorldPointF & pos �µ�λ��
	\retval     void
	\remark     ��걻�ƶ����ź�
	*/
	void mouseMoved(const WWorldPointF& pos);
	
private:
	WAbstractCreator* _creator; //��ǰ�Ѿ������Ļ�ͼ���̣����û����Ϊ0

	bool _bEnableDrag; // �Ƿ�������϶���ͼ
	bool _bEnableWheelScale; // �Ƿ�������м��������ŵ�ͼ
	QPointF _lastPos; //��һ���������ͼ�ϵ�λ��
	QString _tip; //!!!!!!!!!����
	QMenu* _contextMenu; //��ͼ���Ҽ��˵�
	QAction* actions[7]; //��ͼ���Ҽ��˵�����
	QPixmap _bgPixmap; //��ͼ�ı���ͼƬ
	QPixmap _bufferPixmap; //��Ҫ���ڵ�ͼ�ڻ���paintEvent�����л����ϴλ��Ƶ�ͼƬ����ͼ�Ľ�ͼ����
										//�����ڵ�ͼ�����ƶ��Ľ����п��ܻ���ߵ�ͼ�Ļ���Ч��
	QPointF _offset; //��ͼ�ƶ���ƫ����
};

#endif