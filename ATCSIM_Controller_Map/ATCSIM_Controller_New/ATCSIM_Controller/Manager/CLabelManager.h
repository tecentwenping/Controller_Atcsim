#ifndef __C_Label_Manager_H__
#define __C_Label_Manager_H__

#include "wlabelformat.h"



class WAircraftGlyph;
/** 
 \brief		���ƹ�����
 \details   ������庽�����ƹ���֧�ֶ�̬�ı�����
 \author    @zcw
 \date      2013/06/14
*/
class CLabelManager
{
public:
	//! �����߼���־������SDD�ı��Ƹ�ʽ����ʾ��ɫ�Ƕ���״̬���ܾ����ģ����±�־����״̬
	//! �������ͣ���δȫ������ϵ������־�ã�����Щ�����ҵ�����ǿ϶�������ֵģ�
	enum LogicFlags
	{
		none = 0x0,
		no_coupling = 0x1, //�����
		coupling = 0x2, // �����
		holding = 0x4,  // �ȴ�
		no_jurisdiciton = 0x8, //�ǹ���
		post_jurisdiction = 0x10,//Ԥ����
		jurisdiction = 0x20, //����
		handover_in = 0x40,  // �ƽ���
		handover_out = 0x80, // �ƽ���
		announced = 0x100, // ??
		detailed = 0x200,  // ��ϸ
		extended = 0x400,  // ��չ��
		rad_tag = 0x800,   // �����
		vehicle = 0x1000,   // ��������
		flash = 0x2000,    //������˸����
		show_ssr = 0x4000, //��ʾ���������
	};
	WLabelFields* GetFields(WAircraftGlyph* label);
	WLabelFormatter* GetFormatter(WAircraftGlyph* label);

	//!��ָ��������ӱ��Ƹ�ʽ
	bool AddLabel(WAircraftGlyph* label, const WLabelFormat& format = WLabelFormat());
	//!ɾ��ĳ�������ı��Ƹ�ʽ
	bool RemoveLabel(WAircraftGlyph* label);
	//!������б��Ƹ�ʽ����
	void Reset();

	//!��������AircraftGlyph�ı��Ƹ�ʽ
	void SetFormat(const WLabelFormat& format);
	//!����ĳ��AircraftGlyph�ı��Ƹ�ʽ
	bool SetFormat(WAircraftGlyph* label, const WLabelFormat& format);

	//!�������б�������
	void UpdateLabel(bool bForce = false);
	//!���¾���AircraftGlyph��������
	bool UpdateLabel(WAircraftGlyph* label, bool bForce = false);

	//!�߼�����AircraftGlyph�ĸ�ʽ(��UpdateLabel֮ǰ���ã����øĺ�����Ӱ��֮ǰ���õ�Format
	//Format�����LogicFlags���߼�����
	void LogicProcFormat();
	void LogicProcFormat(WAircraftGlyph* label);
	//!��ԭ����������ӱ�־
	bool AddLogicFlag(WAircraftGlyph* label, CLabelManager::LogicFlags flag);
	//!ɾ��ĳ����־
	bool DelLogicFlag(WAircraftGlyph* label, CLabelManager::LogicFlags flag);
	//!�������б�־
	bool SetLogicFlags(WAircraftGlyph* label, int flags);

	//! ����ǰ����ķɻ����ƶ�����һ����־
	bool AddLogicFlag(CLabelManager::LogicFlags flag);
	//������ǰ����ķɻ����ƶ�ɾ��ĳ����־
	bool DelLogicFlag(CLabelManager::LogicFlags flags);
	static CLabelManager& Instance();

private:
	struct info
	{
		boost::shared_ptr<WLabelFields> m_fields;
		boost::shared_ptr<WLabelFormatter> m_formatter;
		mutable int m_flags;
		bool m_bFlagsChanged;
	};

private:
	info* GetInfo(WAircraftGlyph* label);

private:
	typedef stdext::hash_map<WAircraftGlyph*, info> label_info_type;
	typedef label_info_type::value_type value_type;

	label_info_type m_labelInfo;
};

/** 
 \brief		���Ƹ�ʽ����
 \details   ������ֱ��Ƹ�ʽ�Ĵ���
 \author    
 \date      2013/06/14
*/
class WLabelFormatFactory
{
public:
	enum label_type
	{
		//��_radar��׺��Ϊ�״ＰADS��������_plan��׺��Ϊ�ƻ�����
		beg = 0,
		normal_radar = 0,
		normal_plan,
		fixed_extended_radar,
		fixed_extended_plan,
		holding_radar,
		holding_plan,
		limited_radar,
		limited_plan,
		rad_tag_radar,
		rad_tag_plan,
		vehicle, //��������
		end,
	};

	WLabelFormatFactory();

	const WLabelFormat* GetFormat(label_type lt) const;

	static WLabelFormatFactory& Instance();

private:
	WLabelFormat m_formats[end];
};

#endif // __C_Label_Manager_H__
