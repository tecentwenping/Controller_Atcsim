/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicschange.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ����WGraphicsChange��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_CHANGE_H_
#define _WGRAPHICS_CHANGE_H_

#include "../wdllimport.h"

class WGraphicsItem;

/** 
 \brief                 ������ҪΪWEventListener������������˳����з����ı��¼��ĸ������
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsChange
{
public:
	//�����иı��¼�����
	enum Type
	{
		Null, //û���¼�
		Create, //��������ͼԪ������
		Delete, //��������ͼԪ��ɾ��
		Selected, //�����е�ͼԪ��ѡ��
		Unselected, //�����б�ѡ�е�ͼԪʧȥ�˽���
		GenericChange, //������ͼԪͨ�øı����ͣ�������ɫ����С��λ�õȸı䣬
								//��Ȼ������չ��ö�٣��øı����͸���ȷ�У����ڴ��������·ǳ�����
		ClipboardChange, //�����еļ��а巢���ı䣨����ͼԪ�����Ƶ�ʱ��
	};

public:
	explicit WGraphicsChange(Type typ = Null, WGraphicsItem* item = 0);

	Type type() const;
	WGraphicsItem* item() const;

	void setType(Type typ);
	void setItem(WGraphicsItem* item);

private:
	Type _type; //�����ı������
	WGraphicsItem* _item; //�����ı��ͼԪ������ǳ��������ı������ͼԪɾ����������ֶ�Ϊ0��
										//����ǳ����е�ͼԪ�������ĸı�����ֶ�ָ���ͼԪ
};

#endif