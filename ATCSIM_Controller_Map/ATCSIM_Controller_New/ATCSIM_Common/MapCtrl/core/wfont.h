/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wfont.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫʵ����WFont��
  ����  ����:   
******************************************************************************/
#ifndef _WFONT_H_
#define _WFONT_H_

#include "../wdllimport.h"
#include <string>

/** 
 \brief                 ������Ҫʵ����GDI�е�����
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WFont
{
	//����Ĵ�ϸ
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
	std::string _family; //��������
	int _point_size; //�����ֺ�
	int _weight; //�����ϸ
	bool _italic; //�����Ƿ���б
	bool _underline; //�����Ƿ����»���
	bool _strike_out; //�����Ƿ���ɾ����
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