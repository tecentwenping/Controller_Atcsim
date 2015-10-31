#include "CLabelManager.h"
#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>


//#include "CDataManager.h"
//#include "CConfigManager.h"

#include "waircraftglyph.h"

CLabelManager::info* CLabelManager::GetInfo(WAircraftGlyph* label)
{
	BOOST_AUTO(i, m_labelInfo.find(label));
	return (i != m_labelInfo.end()) ? &i->second : 0;
}

bool CLabelManager::AddLabel(WAircraftGlyph* label, const WLabelFormat& format)
{
	bool found = (GetInfo(label) != 0);

	if (!found)
	{
		info i;
		i.m_fields = boost::shared_ptr<WLabelFields>(new WLabelFields);
		i.m_formatter = boost::shared_ptr<WLabelFormatter>(new WLabelFormatter(i.m_fields.get(), label, format));
		i.m_flags = none;
		i.m_bFlagsChanged = true;
		m_labelInfo.insert(std::make_pair(label, i));
	}

	return !found;
}

void CLabelManager::SetFormat(const WLabelFormat& format)
{
	BOOST_FOREACH(value_type& v, m_labelInfo)
	{
		SetFormat(v.first, format);
	}
}

bool CLabelManager::SetFormat(WAircraftGlyph* label, const WLabelFormat& format)
{
	info* i = GetInfo(label);
	if (i && i->m_bFlagsChanged)
	{
		i->m_formatter = boost::shared_ptr<WLabelFormatter>(new WLabelFormatter(i->m_fields.get(), label, format));

		i->m_bFlagsChanged = false;
	}

	return i != 0;
}

void CLabelManager::Reset()
{
	m_labelInfo.clear();
}

WLabelFields* CLabelManager::GetFields(WAircraftGlyph* label)
{
	info* i = GetInfo(label);
	return i ? i->m_fields.get() : 0;
}

WLabelFormatter* CLabelManager::GetFormatter(WAircraftGlyph* label)
{
	info* i = GetInfo(label);
	return i ? i->m_formatter.get() : 0;
}

void CLabelManager::UpdateLabel(bool bForce)
{
	BOOST_FOREACH(value_type& v, m_labelInfo)
	{
		v.second.m_formatter->Format(bForce);
	}
}

bool CLabelManager::UpdateLabel(WAircraftGlyph* label, bool bForce)
{
	info* i = GetInfo(label);
	bool found = (i != 0);

	if (found)
	{
		i->m_formatter->Format(bForce);
	}

	return found;
}


CLabelManager& CLabelManager::Instance()
{
	static CLabelManager instance;
	return instance;
}

/**
\brief      LogicProcFormat
\Access    virtual public 
\retval     void
\remark     
*/
void CLabelManager::LogicProcFormat()
{
	BOOST_FOREACH(value_type& v, m_labelInfo)
	{
		LogicProcFormat(v.first);
	}
}

/**
\brief      LogicProcFormat
\Access    public 
\param  WAircraftGlyph * label
\retval     void
\remark     
*/
void CLabelManager::LogicProcFormat( WAircraftGlyph* label )
{
	//info* i = GetInfo(label);
	//if (!i)
	//{
	//	return;
	//}

	//if (!i->m_bFlagsChanged)
	//{
	//	return;
	//}

	//WLabelFormatFactory::label_type lt;
	//int flags = i->m_flags;
	//if (flags & coupling) // 
	//{
	//	if (flags & holding)
	//	{ // holding
	//		lt = WLabelFormatFactory::holding_radar;
	//	}
	//	else if (flags & rad_tag)
	//	{ // rad tag format
	//		lt = WLabelFormatFactory::rad_tag_radar;
	//	}
	//	else
	//	{
	//		if ((flags & jurisdiction
	//			|| flags & no_jurisdiciton
	//			|| flags & post_jurisdiction
	//			|| flags & handover_in
	//			|| flags & handover_out
	//			|| flags & announced
	//			|| flags & detailed)
	//			&& flags & extended)
	//		{ // Fix Extended
	//			lt = WLabelFormatFactory::fixed_extended_radar;
	//		}
	//		else
	//		{ // normal
	//			lt = WLabelFormatFactory::normal_radar;
	//		}
	//	}
	//}
	//else //未相关标牌
	//{ // limit format
	//	lt = WLabelFormatFactory::limited_radar;
	//}

	//if (flags & vehicle)
	//{
	//	lt = WLabelFormatFactory::normal_radar; // TODO Mark@zcw  添加车辆标牌格式
	//}
	//const WLabelFormat& format = *WLabelFormatFactory::Instance().GetFormat(lt);

	////process color TODO Modify color from config file
	////CConfig& config = theData::instance().GetConfigManager()->GetConfig();
	////WColor Announced_Track_Label_Color = config.GetAnnouncedTrackLabelColor();
	////WColor HAND_IN_TRACK_LABEL_COLOR   = config.GetHandInTracklabelColor();
	////WColor CTL_TRACK_LABEL_COLOR       = config.GetCtlTracklabelcolor();
	////WColor UNCTL_TRACK_LABEL_COLOR     = config.GetUnCtlTrackLabelColor(); 
	////WColor HAND_OUT_TRACK_LABEL_COLOR  = config.GetHandOutTrackLabelColor();
	////WColor FLASH_LABEL_COLOR           = config.GetFlashLabelColor();


	//WLabelFields& lf = *(i->m_fields.get());
	//int beg = WLabelFields::acid;
	//int end = WLabelFields::end;
	//WLabelField* fd;
	//if (flags & handover_in)
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(HAND_IN_TRACK_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = HAND_IN_TRACK_LABEL_COLOR;
	//}
	//else if (flags & handover_out)
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(HAND_OUT_TRACK_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = HAND_OUT_TRACK_LABEL_COLOR;
	//}
	//else if (flags & jurisdiction)
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(CTL_TRACK_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = CTL_TRACK_LABEL_COLOR;
	//}
	//else if (flags & no_jurisdiciton
	//	|| flags & post_jurisdiction
	//	|| flags & no_coupling) // 未相关与非管制，黑色显示
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(UNCTL_TRACK_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = UNCTL_TRACK_LABEL_COLOR;
	//}
	//else if (flags & announced)
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(Announced_Track_Label_Color));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = Announced_Track_Label_Color;
	//}
	//else if (flags & vehicle)
	//{

	//	//TODO Mark@zcw 后面优化车辆颜色
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(CTL_TRACK_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = CTL_TRACK_LABEL_COLOR;
	//}
	//else if (flags & flash)
	//{
	//	while (beg != end)
	//	{
	//		fd = &lf[WLabelFields::field_type(beg)];
	//		fd->SetTextPen(WPen(FLASH_LABEL_COLOR));
	//		++beg;
	//	}

	//	label->data()->m_SymbolColor = FLASH_LABEL_COLOR;
	//}
	//if (flags & show_ssr)
	//{
	//	//将呼号字段替换为二次码字段
	//	WLabelFormat tmpFormat = format;
	//	tmpFormat.ReplaceField(WLabelFields::acid, WLabelFields::moda);
	//	SetFormat(label, tmpFormat);
	//	return;
	//}

	//SetFormat(label, format);
}

/**
\brief      AddLogicFlag
\Access    public 
\param  WAircraftGlyph * label
\param  LogicFlags flag
\retval     bool
\remark     
*/
bool CLabelManager::AddLogicFlag( WAircraftGlyph* label, LogicFlags flag )
{
	/*info* i = GetInfo(label);
	if (i)
	{
		int save = i->m_flags;
		i->m_flags |= flag;
		i->m_bFlagsChanged = (save == i->m_flags) ? false : true;
	}
	*/
    int i=1;
	return i != 0;
}

/**
\brief      AddLogicFlag
\Access    public 
\param  LogicFlags flag
\retval     bool
\remark     
*/
bool CLabelManager::AddLogicFlag( LogicFlags flag )
{
	/*BOOST_FOREACH(value_type& v, m_labelInfo)
	{
		AddLogicFlag(v.first, flag);
	}*/
	return true;
}

/**
\brief      DelLogicFlag
\Access    public 
\param  WAircraftGlyph * label
\param  LogicFlags flag
\retval     bool
\remark     
*/
bool CLabelManager::DelLogicFlag( WAircraftGlyph* label, LogicFlags flag )
{
	/*info* i = GetInfo(label);
	if (i && i->m_flags & flag)
	{
		int save = i->m_flags;
		i->m_flags &= ~flag;
		i->m_bFlagsChanged = (save == i->m_flags) ? false : true;
	}
     */
	int i=1;
	return i != 0;
}

/**
\brief      SetLogicFlags
\Access    public 
\param  WAircraftGlyph * label
\param  int flags
\retval     bool
\remark     
*/
bool CLabelManager::SetLogicFlags( WAircraftGlyph* label, int flags )
{
	//info* i = GetInfo(label);
	//if (i)
	//{
	//	int save = i->m_flags;
	//	i->m_flags = flags;
	//	i->m_bFlagsChanged = (save == i->m_flags) ? false : true;
	//}
    // */
	int i =1;
	return i != 0;
}

/**
\brief      DelLogicaFlag
\Access    public 
\param  LogicFlags flags
\retval     bool
\remark     
*/
bool CLabelManager::DelLogicFlag( LogicFlags flags )
{
	/*BOOST_FOREACH(value_type& v, m_labelInfo)
	{
		DelLogicFlag(v.first, flags);
	}
	*/
	return true;
}

WLabelFormatFactory::WLabelFormatFactory()
{
	WLabelFormat* format = 0;

	format = m_formats + normal_radar;  // Normal 雷达航迹
	format->SetRowCount(5);
	format->AddField(0, WLabelFields::confirm,false);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::indicator);
	format->AddField(2, WLabelFields::cfl);
	// 由于cfl添加一个空白，很多地方需要获取cfl值，进行处理，带来问题，索性使用空白来解决问题
	// 不建议添加space来处理空格，建议在外部拼接" "字符串来达到效果，提高绘制性能
	format->AddField(2, WLabelFields::space); 
	format->AddField(2, WLabelFields::v);
	format->AddField(2, WLabelFields::rvsm);
	format->AddField(2, WLabelFields::gs);
	format->AddField(3, WLabelFields::aidc);
	format->AddField(4, WLabelFields::label_data, false);

	//////////////////////////////////////////////////////////////////////////
	format = m_formats + normal_plan;  // Normal 计划航迹
	format->SetRowCount(5);
	format->AddField(0, WLabelFields::confirm,false);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::moda);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::indicator);
	format->AddField(2, WLabelFields::cfl);
	format->AddField(3, WLabelFields::gs);
	format->AddField(3, WLabelFields::hdg);
	format->AddField(3, WLabelFields::rvsm);
	format->AddField(4, WLabelFields::label_data, false);

	format = m_formats + fixed_extended_radar; // 雷达航迹，扩展标牌格式
	format->SetRowCount(6);
	format->AddField(0, WLabelFields::confirm, false);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::indicator);
	format->AddField(2, WLabelFields::cfl);
	format->AddField(2, WLabelFields::space);
	format->AddField(2, WLabelFields::v);
	format->AddField(2, WLabelFields::rvsm);
	format->AddField(2, WLabelFields::gs);
	format->AddField(3, WLabelFields::ades);
	format->AddField(3, WLabelFields::typ);
	format->AddField(4, WLabelFields::aidc);
	format->AddField(5, WLabelFields::label_data, false);

	format = m_formats + fixed_extended_plan;  // 计划航迹，扩展标牌格式
	format->SetRowCount(6);
	format->AddField(0, WLabelFields::confirm, false);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::prl);
	format->AddField(2, WLabelFields::cfl);
	format->AddField(2, WLabelFields::space);
	format->AddField(2, WLabelFields::v);
	format->AddField(2, WLabelFields::gs);
	format->AddField(3, WLabelFields::ades);
	format->AddField(3, WLabelFields::typ);
	format->AddField(4, WLabelFields::aidc);
	format->AddField(5, WLabelFields::label_data, false);

	format = m_formats + holding_radar;
	format->SetRowCount(3);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::indicator);
	format->AddField(2, WLabelFields::cfl);

	format = m_formats + holding_plan;
	format->SetRowCount(3);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::prl);
	format->AddField(2, WLabelFields::cfl);

	format = m_formats + limited_radar;
	format->SetRowCount(3);
	format->AddField(1, WLabelFields::moda);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::space);
	format->AddField(2, WLabelFields::gs);

	format = m_formats + limited_plan;
	format->SetRowCount(2);
	format->AddField(0, WLabelFields::moda);
	format->AddField(1, WLabelFields::mcl);
	format->AddField(1, WLabelFields::space);
	format->AddField(1, WLabelFields::gs);

	format = m_formats + rad_tag_radar;
	format->SetRowCount(4);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::w);
	format->AddField(2, WLabelFields::mcl);
	format->AddField(2, WLabelFields::indicator);
	format->AddField(2, WLabelFields::cfl);
	format->AddField(2, WLabelFields::space);
	format->AddField(2, WLabelFields::rvsm);
	format->AddField(2, WLabelFields::gs);
	format->AddField(3, WLabelFields::label_data, false);

	format = m_formats + rad_tag_plan;
	format->SetRowCount(4);
	format->AddField(1, WLabelFields::acid);
	format->AddField(1, WLabelFields::moda);
	format->AddField(2, WLabelFields::cfl);
	format->AddField(3, WLabelFields::label_data, false);

	//车辆标牌格式
	format = m_formats + vehicle;
	format->SetRowCount(2);
	format->AddField(0, WLabelFields::acid);
	format->AddField(1, WLabelFields::gs);
	format->AddField(1, WLabelFields::hdg);

	BOOST_FOREACH(WLabelFormat& v, m_formats)
	{
		//limited label no warn
		if ((&v == GetFormat(limited_plan)) || (&v == GetFormat(vehicle)))
		{
			continue;
		}
		v.AddField(0, WLabelFields::hij);
		v.AddField(0, WLabelFields::rad);
		v.AddField(0, WLabelFields::emg);
		v.AddField(0, WLabelFields::stca);
		v.AddField(0, WLabelFields::daiw);
		v.AddField(0, WLabelFields::msaw);
		v.AddField(0, WLabelFields::clam);
		v.AddField(0, WLabelFields::ram);
		v.AddField(0, WLabelFields::dupe);
	}
}

const WLabelFormat* WLabelFormatFactory::GetFormat(label_type lt) const
{
	return &m_formats[lt];
}

WLabelFormatFactory& WLabelFormatFactory::Instance()
{
	static WLabelFormatFactory instance;
	return instance;
}