/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wabstractcreator.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要包含WAbstractCreator类
  【其  它】:   
******************************************************************************/
#ifndef _WABSTRACT_CREATOR_H_
#define _WABSTRACT_CREATOR_H_

#include <QObject>
#include "../wdllimport.h"

class QString;
class WKeyEvent;
class WGraphicsItem;
class WGraphicsSceneMouseEvent;

/** 
 \brief                 此类主要定义了地图中随机作图过程的一个接口标准
\details   
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WAbstractCreator : public QObject
{
//	Q_OBJECT

public:
	virtual ~WAbstractCreator() {}

	/**
	\brief      start
	\Access    virtual public 
	\retval     void
	\remark     启动随机作图过程，在启动之前所需做的初始化工作可以在此函数中进行
	*/
	virtual void start() = 0;

	/**
	\brief      start
	\Access    virtual public 
	\retval     void
	\remark     用于取消某个随机作图
	*/
	virtual void stop() {}

	/**
	\brief      mouseMoveEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void 
	\remark     鼠标移动事件
	*/
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mousePressEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     鼠标按下事件
	*/
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mouseReleaseEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     鼠标释放事件
	*/
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mouseDoubleClickEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     鼠标双击事件
	*/
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      keyPressEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark     键盘按键按下事件
	*/
	virtual void keyPressEvent(WKeyEvent* event) = 0;

	/**
	\brief      keyReleaseEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark     键盘按键释放事件
	*/
	virtual void keyReleaseEvent(WKeyEvent* event) = 0;

signals:
	/**
	\brief      finished
	\Access    public 
	\param  WGraphicsItem * item
	\retval     void
	\remark     当随机作图过程完成（或取消）时请发送此信号
				参数是作图完成的图元，或是0如果作图被取消
	*/
	void finished(WGraphicsItem* item);

	///**
	//\brief      tip
	//\Access    public 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!废弃
	//*/
	void tip(const QString&);

	///**
	//\brief      geometry
	//\Access    public 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!废弃
	//*/
	void geometry(const QString&);
};

#endif