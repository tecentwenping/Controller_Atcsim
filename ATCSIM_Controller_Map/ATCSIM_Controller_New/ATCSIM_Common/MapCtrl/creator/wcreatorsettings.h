/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wcreatorsettings.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ����WCreatorSettings��
  ����  ����:   
******************************************************************************/
#ifndef _WCREATOR_SETTINGS_H_
#define _WCREATOR_SETTINGS_H_

#include "../wdllimport.h"
#include "../core/wpen.h"
#include "../core/wfont.h"
#include "../core/wbrush.h"

/** 
\brief                 ������Ҫ��������/��ȡ�����ͼ�����еĻ��ʣ���ˢ��ͼ�㣬������Ϣ
\details   
 \author    ����
\date      2013/05/31
*/
class MAPAPI WCreatorSettings
{
public:
	void setLayer(int layer);
	void setBrush(const WBrush& brush);
	void setPen(const WPen& pen);
	void setFont(const WFont& font);
	void setPointType(int pointType);
	void set(int layer, const WBrush& brush, const WPen& pen, const WFont& font);
	void reset();

	int layer() const;
	WBrush brush() const;
	WPen pen() const;
	WFont font() const;
	int pointType() const;

	static WCreatorSettings& instance();

private:
	int layer_; //ͼ��
	WBrush brush_; //��ˢ
	WPen pen_; //����
	WFont font_; //����
	int pointType_; //�������
};

#endif