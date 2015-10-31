/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wmapwidget.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要包含WMapWidget类
  【其  它】:   
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
 \brief                 此类用Qt的窗口类实现了一个WGraphicsView定义的所有接口
\details   如果是实现WGraphicsView中的虚接口，关于接口的含义此处不再赘述
 \author    陈龙
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
	\remark     默认鼠标拖动地图实现（左键拖动地图），是否激活，默认激活
	*/
	void setEnableDrag(bool bEnable);

	/**
	\brief      setEnableWheelScale
	\Access    public 
	\param  bool bEnable
	\retval     void
	\remark     默认鼠标缩放地图实现（中键滚动），是否激活，默认激活
	*/
	void setEnableWheelScale(bool bEnable);
	/**
	\brief      isCreating
	\Access    public 
	\retval     bool
	\remark     返回是否在创建图元的标识
	*/
	bool isCreating() const;

	/**
	\brief      backgroundPixmap
	\Access    public 
	\retval     const QPixmap&
	\remark     返回背景图片
	*/
	const QPixmap& backgroundPixmap() const;

	/**
	\brief      setBackgroudPixmap
	\Access    public 
	\param  const QPixmap & pixmap
	\retval     void 设置背景图片
	\remark     
	*/
	void setBackgroudPixmap(const QPixmap& pixmap);

	
	/**
	\brief      setBackgroundColor
	\Access    public 
	\param  const QColor & color
	\retval     void
	\remark     设置背景颜色
	*/
	void setBackgroundColor(const QColor &color);


	/**
	\brief      getBackgroundColor
	\Access    public 
	\param  QColor & color
	\retval     void
	\remark     获取背景颜色
	*/
	
	void getBackgroundColor(QColor &color);


	/**
	\brief      startCreator
	\Access    public 
	\param  WAbstractCreator * creator
	\retval     void
	\remark     启动一个绘图过程
					绘图过程中场景的事件全部交由creator处理，直到绘图过程结束，
					此时this会发出createFinished信号，creator也会发出此信号
	*/
	void startCreator(WAbstractCreator* creator);
	
public slots:
	/**
	\brief      scale
	\Access    public 
	\param  double factor
	\param  bool combine
				 如果为true，则在原来的基础上进行放缩，也就是新的放缩比例为f = f * factor
				 如果为false，则将原来的放缩比例修改为factor，即是f = factor
	\retval     void
	\remark     对地图进行放缩操作
	*/
	void scale(double factor, bool combine = false);

	/**
	\brief      updateSceneSlot
	\Access    public 
	\param  const WWorldRectF & rect
	\retval     void
	\remark     更新场景（重绘）的槽
	*/
	void updateSceneSlot(const WWorldRectF& rect);

private slots:
	/**
	\brief      onClear
	\Access    private 
	\retval     void
	\remark     清除场景中所有的图层
	*/
	void onClear();

	/**
	\brief      onDelete
	\Access    private 
	\retval     void
	\remark     删除场景中所有选中的图元
	*/
	void onDelete();

	/**
	\brief      onFinished
	\Access    private 
	\retval     void
	\remark     由startCreator启动的creator绘图过程完成
	*/
	void onFinished();

	/**
	\brief      onTip
	\Access    private 
	\param  const QString &
	\retval     void
	\remark     !!!!!! 废弃
	*/
	void onTip(const QString&);

	/**
	\brief      onContextMenu
	\Access    private 
	\param  int id
	\retval     void
	\remark     响应右键菜单
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
	\remark     由startCreator启动的creator绘图过程完成的信号
	*/
	void createFinished();

	///**
	//\brief      createTip
	//\Access    protected 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!!废弃
	//*/
	void createTip(const QString&);

	///**
	//\brief      createGeometry
	//\Access    protected 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!废弃
	//*/
	void createGeometry(const QString&);

	/**
	\brief      scaled
	\Access    protected 
	\param  double factor 新的放缩因子
	\retval     void
	\remark     地图被放缩的信号
	*/
	void scaled(double factor);

	/**
	\brief      mouseMoved
	\Access    protected 
	\param  const WWorldPointF & pos 新的位置
	\retval     void
	\remark     鼠标被移动的信号
	*/
	void mouseMoved(const WWorldPointF& pos);
	
private:
	WAbstractCreator* _creator; //当前已经启动的绘图过程，如果没有则为0

	bool _bEnableDrag; // 是否开启鼠标拖动地图
	bool _bEnableWheelScale; // 是否开启鼠标中键滚动缩放地图
	QPointF _lastPos; //上一次鼠标在视图上的位置
	QString _tip; //!!!!!!!!!废弃
	QMenu* _contextMenu; //地图的右键菜单
	QAction* actions[7]; //地图的右键菜单命令
	QPixmap _bgPixmap; //地图的背景图片
	QPixmap _bufferPixmap; //主要用于地图在绘制paintEvent过程中缓存上次绘制的图片（视图的截图），
										//这样在地图反复移动的进程中可能会提高地图的绘制效率
	QPointF _offset; //地图移动的偏移量
};

#endif