/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wcreatorsettings.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要包含WCreatorSettings类
  【其  它】:   
******************************************************************************/
#ifndef _WCREATOR_SETTINGS_H_
#define _WCREATOR_SETTINGS_H_

#include "../wdllimport.h"
#include "../core/wpen.h"
#include "../core/wfont.h"
#include "../core/wbrush.h"

/** 
\brief                 此类主要用于设置/获取随机作图过程中的画笔，画刷，图层，字体信息
\details   
 \author    陈龙
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
	int layer_; //图层
	WBrush brush_; //画刷
	WPen pen_; //画笔
	WFont font_; //字体
	int pointType_; //点的类型
};

#endif