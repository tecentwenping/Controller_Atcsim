/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wdefaultcreator.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ����WDefaultCreator��
  ����  ����:   
******************************************************************************/
#ifndef _WDEFAULT_CREATOR_H_
#define _WDEFAULT_CREATOR_H_

#include "../wdllimport.h"
#include "wabstractcreator.h"

class WGraphicsScene;

/** 
 \brief                 ����WAbstractCreator�ӿڵĻ������ṩ��һ��Ĭ�ϵ�ʵ�֣�ʲô�¼�Ҳ���ɣ�
\details   WAbstractCreatorֻ�Ƕ�����һ����׼�ӿڣ���������̫��Ĵ��麯�������ʺ�ֱ�Ӽ̳�ʹ��
			 �����ṩ�˴��࣬�Ա��������ඨ��ܶ�û�õ�ʵ��
 \author    ����
\date      2013/05/31
*/
class MAPAPI WDefaultCreator : public WAbstractCreator
{
public:
	explicit WDefaultCreator(WGraphicsScene* scene);

	virtual void start();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);
	virtual void keyPressEvent(WKeyEvent* event);
	virtual void keyReleaseEvent(WKeyEvent* event);
	
	WGraphicsScene* scene() const;

private:
	WGraphicsScene* _scene;
};

#endif