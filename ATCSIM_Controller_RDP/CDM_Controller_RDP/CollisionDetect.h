#ifndef COLLISIONDETECT_H
#define COLLISIONDETECT_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CollisionDetect
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2015/10/29
  ����  ����: ����ʵ�ֵ�����ײ��⹦�� 
  ����  ����:   
**************************************************************************/
#include "public/PublicStruct.h"
#include <deque>
#include "wworldpoint.h"
class CollisionDetect
{
	

public:
	CollisionDetect();
	~CollisionDetect();

private:
	/**************************************************************************
	*��������_SetSafeDistance
	*�������ܣ�����һ���������������澯��ͻ�����ĺͣ���������Ҫ����β����ȷ��
	*������
	**************************************************************************/
	void _SetSafeDistance(PublicDataStruct::Aircraft& aircraft);

	void _CollisonDetect();
private:
	std::deque<WPointF> m_deqAircraft;
	
	
};

#endif // COLLISIONDETECT_H
