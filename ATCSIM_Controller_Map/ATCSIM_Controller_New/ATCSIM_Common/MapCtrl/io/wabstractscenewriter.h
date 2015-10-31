/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wabstractscenewriter.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要包含WAbstractSceneWriter类
  【其  它】:   
******************************************************************************/
#ifndef _WABSTRACT_SCENE_WRITER_H_
#define _WABSTRACT_SCENE_WRITER_H_

#include "../wdllimport.h"

class WGraphicsItem;
class WGraphicsScene;

/** 
 \brief                 定义了一个将场景保存的标准接口
\details   
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WAbstractSceneWriter
{
public:
	virtual ~WAbstractSceneWriter();
	
	/**
	\brief      write
	\Access    public 
	\param  const WGraphicsScene * scene
	\retval     void
	\remark     将场景保存
	*/
	void write(const WGraphicsScene* scene);

protected:
	/**
	\brief      writeBegin
	\Access    virtual protected 
	\retval     void
	\remark     在保存之前执行的虚函数
	*/
	virtual void writeBegin();

	/**
	\brief      writeEnd
	\Access    virtual protected 
	\retval     void
	\remark     保存之后虚函数
	*/
	virtual void writeEnd();

	/**
	\brief      writeImpl
	\Access    virtual protected 
	\param  const WGraphicsItem * item
	\retval     void
	\remark     由子类实现具体的图元保存工作
	*/
	virtual void writeImpl(const WGraphicsItem* item) = 0;
};

#endif