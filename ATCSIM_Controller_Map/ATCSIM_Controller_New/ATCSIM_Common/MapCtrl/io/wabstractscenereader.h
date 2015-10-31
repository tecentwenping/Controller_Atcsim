/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wabstractscenereader.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ������WAbstractSceneReader�ӿ�
  ����  ����:   
******************************************************************************/
#ifndef _WABSTRACT_SCENE_READER_H_
#define _WABSTRACT_SCENE_READER_H_

#include "../wdllimport.h"

class WGraphicsItem;
class WGraphicsScene;

/** 
 \brief                 �����˶�ȡ�����б�׼�ӿ�
\details   
 \author    ����
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
	\remark     ��ȡ�����ܽӿ�
	*/
	void read(WGraphicsScene* scene);

protected:
	/**
	\brief      readBegin
	\Access    protected 
	\retval     void
	\remark     ��ȡ֮ǰִ��
	*/
	void readBegin();

	/**
	\brief      readEnd
	\Access    protected 
	\retval     void
	\remark     ��ȡ��ɺ�ִ��
	*/
	void readEnd();

	/**
	\brief      itemAvailable
	\Access    protected 
	\param  WGraphicsItem * item
	\retval     void
	\remark     ����ͼԪ����ʱ���ô˺���
	*/
	void itemAvailable(WGraphicsItem* item);

	/**
	\brief      readImpl
	\Access    virtual protected 
	\retval     void
	\remark     ��ȡ�����ľ���ʵ�֣���������ɣ�
	*/
	virtual void readImpl() = 0;

private:
	WGraphicsScene* _scene;
};

#endif