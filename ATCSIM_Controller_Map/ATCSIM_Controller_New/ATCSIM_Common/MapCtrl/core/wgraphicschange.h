/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicschange.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现了WGraphicsChange类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_CHANGE_H_
#define _WGRAPHICS_CHANGE_H_

#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief                 此类主要为WEventListener类服务，它定义了场景中发生改变事件的各种情况
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WGraphicsChange
{
public:
	//场景中改变事件种类
	enum Type
	{
		Null, //没有事件
		Create, //场景中有图元被创建
		Delete, //场景中有图元被删除
		Selected, //场景中的图元被选中
		Unselected, //场景中被选中的图元失去了焦点
		GenericChange, //场景中图元通用改变类型，比如颜色，大小，位置等改变，
								//当然可以扩展此枚举，让改变类型更加确切，这在大多数情况下非常有用
		ClipboardChange, //场景中的剪切板发生改变（当有图元被复制的时候）
	};

public:
	explicit WGraphicsChange(Type typ = Null, WGraphicsItem* item = 0);

	Type type() const;
	WGraphicsItem* item() const;

	void setType(Type typ);
	void setItem(WGraphicsItem* item);

private:
	Type _type; //发生改变的类型
	WGraphicsItem* _item; //发生改变的图元，如果是场景发生改变或者是图元删除操作则此字段为0，
										//如果是场景中的图元本身发生的改变则此字段指向此图元
};

#endif