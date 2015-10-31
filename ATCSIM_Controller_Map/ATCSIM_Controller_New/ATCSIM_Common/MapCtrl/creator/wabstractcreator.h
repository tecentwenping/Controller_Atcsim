/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wabstractcreator.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ����WAbstractCreator��
  ����  ����:   
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
 \brief                 ������Ҫ�����˵�ͼ�������ͼ���̵�һ���ӿڱ�׼
\details   
 \author    ����
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
	\remark     ���������ͼ���̣�������֮ǰ�������ĳ�ʼ�����������ڴ˺����н���
	*/
	virtual void start() = 0;

	/**
	\brief      start
	\Access    virtual public 
	\retval     void
	\remark     ����ȡ��ĳ�������ͼ
	*/
	virtual void stop() {}

	/**
	\brief      mouseMoveEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void 
	\remark     ����ƶ��¼�
	*/
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mousePressEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     ��갴���¼�
	*/
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mouseReleaseEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     ����ͷ��¼�
	*/
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      mouseDoubleClickEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark     ���˫���¼�
	*/
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event) = 0;

	/**
	\brief      keyPressEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark     ���̰��������¼�
	*/
	virtual void keyPressEvent(WKeyEvent* event) = 0;

	/**
	\brief      keyReleaseEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark     ���̰����ͷ��¼�
	*/
	virtual void keyReleaseEvent(WKeyEvent* event) = 0;

signals:
	/**
	\brief      finished
	\Access    public 
	\param  WGraphicsItem * item
	\retval     void
	\remark     �������ͼ������ɣ���ȡ����ʱ�뷢�ʹ��ź�
				��������ͼ��ɵ�ͼԪ������0�����ͼ��ȡ��
	*/
	void finished(WGraphicsItem* item);

	///**
	//\brief      tip
	//\Access    public 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!!����
	//*/
	void tip(const QString&);

	///**
	//\brief      geometry
	//\Access    public 
	//\param  const QString &
	//\retval     void
	//\remark     !!!!!!!!����
	//*/
	void geometry(const QString&);
};

#endif