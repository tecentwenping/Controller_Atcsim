/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wabstractscenereader.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要定义了WAbstractSceneReader接口
  【其  它】:   
******************************************************************************/
#ifndef _WABSTRACT_SCENE_READER_H_
#define _WABSTRACT_SCENE_READER_H_

#include "../wdllimport.h"

class WGraphicsItem;
class WGraphicsScene;

/** 
 \brief                 定义了读取场景中标准接口
\details   
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WAbstractSceneReader
{
public:
	WAbstractSceneReader();
	virtual ~WAbstractSceneReader();
	
	/**
	\brief      read
	\Access    public 
	\param  WGraphicsScene * scene
	\retval     void
	\remark     读取场景总接口
	*/
	void read(WGraphicsScene* scene);

protected:
	/**
	\brief      readBegin
	\Access    protected 
	\retval     void
	\remark     读取之前执行
	*/
	void readBegin();

	/**
	\brief      readEnd
	\Access    protected 
	\retval     void
	\remark     读取完成后执行
	*/
	void readEnd();

	/**
	\brief      itemAvailable
	\Access    protected 
	\param  WGraphicsItem * item
	\retval     void
	\remark     当有图元可用时调用此函数
	*/
	void itemAvailable(WGraphicsItem* item);

	/**
	\brief      readImpl
	\Access    virtual protected 
	\retval     void
	\remark     读取场景的具体实现（由子类完成）
	*/
	virtual void readImpl() = 0;

private:
	WGraphicsScene* _scene;
};

#endif