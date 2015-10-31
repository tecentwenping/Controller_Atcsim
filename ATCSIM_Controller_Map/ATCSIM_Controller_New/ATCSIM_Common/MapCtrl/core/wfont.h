/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wfont.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要实现了WFont类
  【其  它】:   
******************************************************************************/
#ifndef _WFONT_H_
#define _WFONT_H_

#include "../wdllimport.h"
#include <string>

/** 
 \brief                 此类主要实现了GDI中的字体
\details   
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WFont
{
	//字体的粗细
	enum Weight 
	{
		Light = 25,
		Normal = 50,
		DemiBold = 63,
		Bold = 75,
		Black = 87,
	};

public:
	explicit WFont(const std::string& family = std::string(), int pointSize = -1, int weight = -1, bool italic = false);

	std::string family() const;
	int pointSize() const;
	int weight() const;
	bool italic() const;
	bool underline() const;
	bool strikeOut() const;
	bool kerning() const;
	bool bold() const;

	void setFamily(const std::string& family);
	void setPointSize(int pointSize);
	void setWeight(int weight);
	void setItalic(bool enable = true);
	void setUnderline(bool enable = true);
	void setStrikeOut(bool enable = true);
	void setKerning(bool enable = true);
	void setBold(bool enable = true);

	bool equal(const WFont& other) const;

private:
	std::string _family; //字体类型
	int _point_size; //字体字号
	int _weight; //字体粗细
	bool _italic; //字体是否倾斜
	bool _underline; //字体是否有下滑线
	bool _strike_out; //字体是否有删除线
	bool _kerning;
};

inline bool operator==(const WFont& lhs, const WFont& rhs)
{
	return lhs.equal(rhs);
}

inline bool operator!=(const WFont& lhs, const WFont& rhs)
{
	return !(lhs == rhs);
}

#endif