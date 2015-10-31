#ifndef __C_Label_Manager_H__
#define __C_Label_Manager_H__

#include "wlabelformat.h"



class WAircraftGlyph;
/** 
 \brief		标牌管理器
 \details   负责具体航迹标牌管理，支持动态改变设置
 \author    @zcw
 \date      2013/06/14
*/
class CLabelManager
{
public:
	//! 标牌逻辑标志，由于SDD的标牌格式与显示颜色是多种状态才能决定的，以下标志描述状态
	//! 以下类型，并未全部有联系，仅标志用（即有些组合在业务上是肯定不会出现的）
	enum LogicFlags
	{
		none = 0x0,
		no_coupling = 0x1, //非相关
		coupling = 0x2, // 相关性
		holding = 0x4,  // 等待
		no_jurisdiciton = 0x8, //非管制
		post_jurisdiction = 0x10,//预管制
		jurisdiction = 0x20, //管制
		handover_in = 0x40,  // 移交入
		handover_out = 0x80, // 移交出
		announced = 0x100, // ??
		detailed = 0x200,  // 详细
		extended = 0x400,  // 扩展性
		rad_tag = 0x800,   // 简标牌
		vehicle = 0x1000,   // 车辆标牌
		flash = 0x2000,    //正在闪烁标牌
		show_ssr = 0x4000, //显示二次码标牌
	};
	WLabelFields* GetFields(WAircraftGlyph* label);
	WLabelFormatter* GetFormatter(WAircraftGlyph* label);

	//!给指定航迹添加标牌格式
	bool AddLabel(WAircraftGlyph* label, const WLabelFormat& format = WLabelFormat());
	//!删除某个航迹的标牌格式
	bool RemoveLabel(WAircraftGlyph* label);
	//!清空所有标牌格式关联
	void Reset();

	//!设置所有AircraftGlyph的标牌格式
	void SetFormat(const WLabelFormat& format);
	//!设置某个AircraftGlyph的标牌格式
	bool SetFormat(WAircraftGlyph* label, const WLabelFormat& format);

	//!更新所有标牌内容
	void UpdateLabel(bool bForce = false);
	//!更新具体AircraftGlyph标牌内容
	bool UpdateLabel(WAircraftGlyph* label, bool bForce = false);

	//!逻辑处理AircraftGlyph的格式(在UpdateLabel之前调用，调用改函数会影响之前设置的Format
	//Format会根据LogicFlags来逻辑处理
	void LogicProcFormat();
	void LogicProcFormat(WAircraftGlyph* label);
	//!在原来基础上添加标志
	bool AddLogicFlag(WAircraftGlyph* label, CLabelManager::LogicFlags flag);
	//!删除某个标志
	bool DelLogicFlag(WAircraftGlyph* label, CLabelManager::LogicFlags flag);
	//!重置所有标志
	bool SetLogicFlags(WAircraftGlyph* label, int flags);

	//! 给当前管理的飞机标牌都增加一个标志
	bool AddLogicFlag(CLabelManager::LogicFlags flag);
	//！给当前管理的飞机标牌都删除某个标志
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
 \brief		标牌格式工厂
 \details   负责各种标牌格式的创建
 \author    
 \date      2013/06/14
*/
class WLabelFormatFactory
{
public:
	enum label_type
	{
		//带_radar后缀的为雷达及ADS航迹，带_plan后缀的为计划航迹
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
		vehicle, //车辆标牌
		end,
	};

	WLabelFormatFactory();

	const WLabelFormat* GetFormat(label_type lt) const;

	static WLabelFormatFactory& Instance();

private:
	WLabelFormat m_formats[end];
};

#endif // __C_Label_Manager_H__
