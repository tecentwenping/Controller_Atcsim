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
 \brief		�����еľ����
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

	//! ������ʾ�̶��������ݣ����ܸ��ַ��Ƿ�Ϊ��
	void SetCharN(int n);
	//! ���ڲ���SetSize�ӿڣ����ݻ��Զ������ַ������ݽ��г��ȵĵ���
	void SetSize(const WSizeF& size);
	void SetShowBoundingFlag(bool show);
	void SetText(const std::wstring& text);
	void SetFont(const WFont& font);
	void SetTextPen(const WPen& pen);
	void SetBoundingPen(const WPen& pen);
	void SetBrush(const WBrush& brush);

private:
	WSizeF m_size; //block's size (size ���ݵ�ǰʹ�õ������Լ����ݵĳ����Լ����ƣ��������ⲿ����)
	int m_iCharN; // �ַ�����
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
	/*�����ֶ���ο���DPS08�������ģ�����ѵ����Ա(SDD)ϯλ �û��ֲ� P12-13*/
	enum field_type
	{
		beg = 0,
		
		confirm = 0, 
		//�����澯
		hij, //�Ƿ��ٳ�
		rad, //���ߵ�ʧЧ
		emg, //�������
		//�澯
		stca, //���ڳ�ͻ�澯
		daiw, //����Σ����
		msaw, //��Ͱ�ȫ�߶ȸ澯
		clam, //�߶�ƫ��澯
		ram, //��·ƫ��澯
		dupe, //���δ����ظ�
		 
		acid, //�ɻ���ʶ��8���ַ�
		moda, //SSR���룬4���ַ�
		w, //β����1���ַ���H=high M=medium L=light
		mcl, //Cģʽ�߶ȣ�����ʱ10��Ϊ��λ����ʾ4�ַ���Ӣ��ʱ100Ӣ��Ϊ��λ����ʾ3�ַ�������ǰ��0
		indicator, //�߶�ָʾ�����ϵļ�ͷ��2227��ʾ���������µļ�ͷ��2228��ʾ�½���ˮƽ��ͷ>��ʾƽ�ɣ���·ģʽ����ʾ
		hdg,  //�ɻ�����
		cfl, //��ɷ��и߶ȣ�����ʱ10��Ϊ��λ����ʾ4�ַ���Ӣ��ʱ100Ӣ��Ϊ��λ����ʾ3�ַ�������ǰ��0
		rvsm, //X��ʾδ��׼RVSM���У��ո��ʾ��׼RVSM����
		v, //���й���һ���ַ���I(IFR) V(VFR) Y(IFR-VFR) Z(VFR-IFR)
		gs, //���٣�����ʱ10km/hΪ��λ����ʾ3λ���֣�Ӣ��ʱ����10knm/hΪ��λ����ʾ2λ����
		prl, //����Ա����߶ȣ�����ʱ10��Ϊ��λ4�ַ���ʾ��Ӣ��ʱ100Ӣ��Ϊ��λ��ʾ3�ַ�������ǰ��0
		ades, //������������4�ַ�
		typ, //���ͣ����4�ַ����������ֶ�Ϊtype�����ǵ�������C++δ���ؼ�������������e�ԣ�
		aidc, //�����aidc��Ϣ��û������ʾ
		label_data, //�û�����������ı���10�ַ�
		space, //���ּ�ļ�϶(1���ַ���
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

	//ɾ��������ĳ���ֶ�
	void DelField(const field_type& field);

	size_t GetFieldCount() const;
	size_t GetFieldCount(size_t row) const;

	const std::vector<std::vector<field_type> >& GetFormat();
	const std::vector<std::vector<bool> >& GetFormatFlag();
private:
	std::vector<std::vector<field_type> > m_format;
	std::vector<std::vector<bool> > m_formatflag; // ��ע���ֶ��Ƿ���û�����ݵ�ʱ���Զ�����
};

/** 
 \brief		
 \details   
 \author    @chl & @zcw
 \date      2013/06/26
 \mark	Formatʱ���Ǹ����ⲿ���õľ���WLabelField�Ĵ�С����������Label Rect��С�ģ�
	WLabelField�����岢����Ӱ��Format
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

	//! ����ʹ�������С
	static void UpdateCharSize();
private:
	void FormatAllChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);

	//! ��С�ı䣬���и��£� ����û���ˣ����ڲ��Լ����ƴ�С�ĸı䣩
	void FormatSizeChanged(const std::vector<std::vector<field_type> >& format, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);
	//! ���ݸ��£����ڻظ������б��ƣ��������ݸ��£����ܵ������ڵ�������£������������ݸ��£����ƴ�С�����¼��㣩
	void FormatTextChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag,
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);
	void Format(const std::vector<std::vector<field_type> >& format, 
		WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter);

private:
	bool m_formatChanged;
	const WLabelFields* m_fields;
	WAircraftGlyph* m_label;
	WLabelFormat m_format;

	//! �����ַ��Ŀ���߶ȣ����ڶ�̬������Ƹ�ʽ�����ݵı仯
	static double m_dCharWidth;
	static double m_dCharHeight;
};



#endif