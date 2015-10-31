/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wabstractscenewriter.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ����WAbstractSceneWriter��
  ����  ����:   
******************************************************************************/
#ifndef _WABSTRACT_SCENE_WRITER_H_
#define _WABSTRACT_SCENE_WRITER_H_

#include "../wdllimport.h"

class WGraphicsItem;
class WGraphicsScene;

/** 
 \brief                 ������һ������������ı�׼�ӿ�
\details   
 \author    ����
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
	\remark     ����������
	*/
	void write(const WGraphicsScene* scene);

protected:
	/**
	\brief      writeBegin
	\Access    virtual protected 
	\retval     void
	\remark     �ڱ���֮ǰִ�е��麯��
	*/
	virtual void writeBegin();

	/**
	\brief      writeEnd
	\Access    virtual protected 
	\retval     void
	\remark     ����֮���麯��
	*/
	virtual void writeEnd();

	/**
	\brief      writeImpl
	\Access    virtual protected 
	\param  const WGraphicsItem * item
	\retval     void
	\remark     ������ʵ�־����ͼԪ���湤��
	*/
	virtual void writeImpl(const WGraphicsItem* item) = 0;
};

#endif