/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wabstractgraphicsshapeitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/22
  ����  ����:  ��Ҫʵ��WAbstractShapeItem��WAbstractShapeItemData��
  ����  ����:   
******************************************************************************/
#ifndef _WABSTRACT_GRAPHICS_SHAPE_ITEM_H_
#define _WABSTRACT_GRAPHICS_SHAPE_ITEM_H_

#include "../wdllimport.h"
#include "wpen.h"
#include "wbrush.h"
#include "wgraphicsitem.h"

/** 
 \brief                 WAbstractShapeItem�������࣬��Ҫ��������WPen�ͻ�ˢWBrush��������
\details   
 \author    ����
\date      2013/05/22
*/
class MAPAPI WAbstractShapeItemData : public WItemData
{
public:
	explicit WAbstractShapeItemData(int typ = 0, const WBrush& b = WBrush(), const WPen& p = WPen()) : WItemData(typ), brush(b), pen(p) {}
	
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	virtual WAbstractShapeItemData* copy() const { return new WAbstractShapeItemData(*this); }

	WBrush brush; //�����������Ļ�ˢ
	WPen pen; //�����������Ļ���
};

/** 
 \brief                 ������һ�����࣬��Ϊ��������״��ͼԪ�ṩ�˳���
\details   
 \author    ����
\date      2013/05/22
*/
class MAPAPI WAbstractGraphicsShapeItem : public WGraphicsItem
{
	RTTI_DECL(WAbstractGraphicsShapeItem)

public:
	typedef WAbstractShapeItemData data_type;

public:
	explicit WAbstractGraphicsShapeItem(const WBrush& brush, const WPen& pen = WPen());
	explicit WAbstractGraphicsShapeItem(data_type* d = 0);

	WBrush brush() const;
	WPen pen() const;

	/**
	\brief      setBrush
	\Access    public 
	\param  const WBrush & brush
	\param  bool update �Ƿ���������һ��ˢ��
	\param  bool opStack �Ƿ񽫲�����ջ
	\retval     void
	\remark     ���û�ˢ
	*/
	void setBrush(const WBrush& brush, bool update = false, bool opStack = false);

	/**
	\brief      setPen
	\Access    public 
	\param  const WPen & pen
	\param  bool update
	\param  bool opStack
	\retval     void
	\remark    ���û��ʣ�update��opStack����������ĺ���һ�� 
	*/
	void setPen(const WPen& pen, bool update = false, bool opStack = false);

	data_type* data();
	const data_type* data() const;

	enum { Type = TYPE_SHAPE_ITEM };
	virtual int type() const;
};

#endif