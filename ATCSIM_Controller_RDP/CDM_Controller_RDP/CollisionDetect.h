#ifndef COLLISIONDETECT_H
#define COLLISIONDETECT_H
/**************************************************************************
   版权所有 (C), 2013 - 2014, 四川大学空管实验室
  【类  名】: CollisionDetect
  【作  者】: 陈文平
  【版  本】:1.0
  【完成日期】:2015/10/29
  【描  述】: 该类实现的是碰撞检测功能 
  【其  它】:   
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
	*函数名：_SetSafeDistance
	*函数功能：传入一个航空器，算出其告警层和基础层的和，保护层需要根据尾流来确定
	*变量：
	**************************************************************************/
	void _SetSafeDistance(PublicDataStruct::Aircraft& aircraft);

	void _CollisonDetect();
private:
	std::deque<WPointF> m_deqAircraft;
	
	
};

#endif // COLLISIONDETECT_H
