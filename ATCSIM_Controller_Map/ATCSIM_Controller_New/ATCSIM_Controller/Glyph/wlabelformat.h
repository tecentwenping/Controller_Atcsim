#ifndef _WLABEL_FORMAT_H_
#define _WLABEL_FORMAT_H_

#include <list>
#include <string>
#include <vector>
#include <hash_map>
#include <boost/shared_ptr.hpp>
#include "wpen.h"
#include "wfont.h"
#include "wbrush.h"
#include "wworldrect.h"

class WBlockData;
class WAircraftGlyph;
class WAircraftItemData;

/** 
 \brief		标牌中的具体块
 \details   
 \author    
 \date      2013/06/26
*/
class WLabelField
{
public:
	enum change_type
	{
		none = 0x0,
		size_changed = 0x1,
		show_bounding_changed = 0x2,
		text_changed = 0x4,
		font_changed = 0x8,
		pen_changed = 0x10,
		bounding_pen_changed = 0x20,
		brush_changed = 0x40,
		all_changed = size_changed | show_bounding_changed | text_changed 
		| font_changed | pen_changed | bounding_pen_changed | brush_changed,
	};

	WLabelField();

	void ResetChangeFlags() const;
	int GetChangeFlags() const;
	bool HasChange() const;

	int GetCharN() const;
	WSizeF GetSize() const;
	bool GetShowBoundingFlag() const;
	std::wstring GetText() const;
	WFont GetFont() const;
	WPen GetTextPen() const;
	WPen GetBoundingPen() const;
	WBrush GetBrush() const;

	//! 用于显示固定长度内容，不管该字符是否为空
	void SetCharN(int n);
	//! 现在不用SetSize接口，内容会自动根据字符的内容进行长度的调整
	void SetSize(const WSizeF& size);
	void SetShowBoundingFlag(bool show);
	void SetText(const std::wstring& text);
	void SetFont(const WFont& font);
	void SetTextPen(const WPen& pen);
	void SetBoundingPen(const WPen& pen);
	void SetBrush(const WBrush& brush);

private:
	WSizeF m_size; //block's size (size 根据当前使用的字体以及内容的长度自己控制，不进行外部设置)
	int m_iCharN; // 字符个数
	bool m_bShowBounding; //whether to draw bounding rect
	std::wstring m_text; //block text
	WFont m_font; //font to draw text
	WPen m_penText; //pen to draw text
	WPen m_penBounding; //pen to draw bounding rect
	WBrush m_brush; //brush to draw bounding rect

	mutable int m_changeFlags;
};

class WLabelFields
{
public:
	/*以下字段请参考：DPS08程序管制模拟机受训管制员(SDD)席位 用户手册 P12-13*/
	enum field_type
	{
		beg = 0,
		
		confirm = 0, 
		//紧急告警
		hij, //非法劫持
		rad, //无线电失效
		emg, //紧急情况
		//告警
		stca, //短期冲突告警
		daiw, //侵入危险区
		msaw, //最低安全高度告警
		clam, //高度偏差告警
		ram, //航路偏差告警
		dupe, //二次代码重复
		 
		acid, //飞机标识，8个字符
		moda, //SSR代码，4个字符
		w, //尾流，1个字符，H=high M=medium L=light
		mcl, //C模式高度，公制时10米为单位，显示4字符，英制时100英尺为单位，显示3字符，不足前补0
		indicator, //高度指示，向上的箭头∧2227表示爬升，向下的箭头∨2228表示下降，水平箭头>表示平飞，旁路模式不显示
		hdg,  //飞机朝向
		cfl, //许可飞行高度，公制时10米为单位，显示4字符，英制时100英尺为单位，显示3字符，不足前补0
		rvsm, //X表示未获准RVSM飞行，空格表示获准RVSM飞行
		v, //飞行规则，一个字符：I(IFR) V(VFR) Y(IFR-VFR) Z(VFR-IFR)
		gs, //地速，公制时10km/h为单位，显示3位数字，英制时，以10knm/h为单位，显示2位数字
		prl, //飞行员报告高度，公制时10米为单位4字符显示，英制时100英尺为单位显示3字符，不足前补0
		ades, //降落机场，最多4字符
		typ, //机型，最多4字符（本来此字段为type，考虑到可能与C++未来关键字重名，后面e略）
		aidc, //航班的aidc信息，没有则不显示
		label_data, //用户输入的自由文本，10字符
		space, //文字间的间隙(1个字符宽）
		end,
	};

	field_type GetSize() const;
	int GetChangeFlags() const;
	bool HasChange() const;
	void ResetChangeFlags() const;
	
	WLabelField& operator[](field_type id);
	const WLabelField& operator[](field_type id) const;

private:
	WLabelField m_fields[end];
};

class WLabelFormat
{
public:
	typedef WLabelFields::field_type field_type;

	void Reset();
	void SetRowCount(size_t count);
	void AddField(size_t row, field_type field, bool bAutoHide = true);
	void ReplaceField(const field_type& ePreType, const field_type& eCurType, bool bAutoHide = true);

	//删除标牌中某个字段
	void DelField(const field_type& field);

	size_t GetFieldCount() const;
	size_t GetFieldCount(size_t row) const;

	const std::vector<std::vector<field_type> >& GetFormat();
	const std::vector<std::vector<bool> >& GetFormatFlag();
private:
	std::vector<std::vector<field_type> > m_format;
	std::vector<std::vector<bool> > m_formatflag; // 标注该字段是否在没有数据的时候自动隐藏
};

/** 
 \brief		
 \details   
 \author    @chl & @zcw
 \date      2013/06/26
 \mark	Format时候是根据外部设置的具体WLabelField的大小来调整整个Label Rect大小的，
	WLabelField中字体并不会影响Format
*/

class WLabelFormatter
{
	typedef WLabelFields::field_type field_type;

public:
	WLabelFormatter(const WLabelFields* fields, WAircraftGlyph* label, 
		const WLabelFormat& format = WLabelFormat());

	WLabelFormat GetFormat() const;
	void SetFormat(const WLabelFormat& format);

	void Format(bool bForce = false);

	//! 更新使用字体大小
	static void UpdateCharSize();
private:
	void FormatAllChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);

	//! 大小改变，进行更新（ 现在没用了，由内部自己控制大小的改变）
	void FormatSizeChanged(const std::vector<std::vector<field_type> >& format, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);
	//! 内容更新（现在回更新所有标牌，由于内容更新，可能导致相邻的区域更新，所有现在内容更新，标牌大小会重新计算）
	void FormatTextChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag,
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);
	void Format(const std::vector<std::vector<field_type> >& format, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);

private:
	bool m_formatChanged;
	const WLabelFields* m_fields;
	WAircraftGlyph* m_label;
	WLabelFormat m_format;

	//! 单个字符的宽与高度，用于动态处理标牌格式中数据的变化
	static double m_dCharWidth;
	static double m_dCharHeight;
};



#endif