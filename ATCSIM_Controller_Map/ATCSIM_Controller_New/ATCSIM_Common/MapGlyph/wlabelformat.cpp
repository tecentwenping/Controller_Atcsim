#include <boost/foreach.hpp>
#include <boost/typeof/typeof.hpp>
#include "wlabelformat.h"
#include "wfontmetrics.h"
#include "waircraftglyph.h"



static const double SPACING_LEFT = 1.0;
static const double SPACING_COLUMN = 0.0;
static const double SPACING_RIGHT = 1.0;
static const double SPACING_TOP = 1.0;
static const double SPACING_ROW = 0.0;
static const double SPACING_BOTTOM = 1.0;


int CountWString(const std::wstring& s)
{
	//宽字符中单字符个数，主要目的，处理中文问题
	//中文中为宽字符，编码为16位，而英文则为8位，英文在宽字符中高8位为00000000
	int count = 0;
	for (unsigned i = 0; i < s.length(); ++i)
	{
		if (s[i]>>8 != 0) // 判断高8位是否为0
		{
			count++;
		}
		count++;
	}

	return count;
}


WLabelField::WLabelField() : m_changeFlags(0), m_bShowBounding(false), 
m_size(0.0, 0.0), m_penText(WColor(0, 255, 255)) , m_iCharN(0)
{
	ResetChangeFlags();
	m_changeFlags |= (show_bounding_changed | size_changed);
}

void WLabelField::ResetChangeFlags() const
{
	m_changeFlags = none;
}

int WLabelField::GetChangeFlags() const
{
	return m_changeFlags;
}

bool WLabelField::HasChange() const
{
	return m_changeFlags != none;
}

int WLabelField::GetCharN() const
{
	return m_iCharN;
}

WSizeF WLabelField::GetSize() const
{
	return m_size;
}

bool WLabelField::GetShowBoundingFlag() const
{
	return m_bShowBounding;
}

std::wstring WLabelField::GetText() const
{
	return m_text;
}

WFont WLabelField::GetFont() const
{
	return m_font;
}

WPen WLabelField::GetTextPen() const
{
	return m_penText;
}

WPen WLabelField::GetBoundingPen() const
{
	return m_penBounding;
}

WBrush WLabelField::GetBrush() const
{
	return m_brush;
}

void WLabelField::SetCharN(int n)
{
	if (m_iCharN != n)
	{
		m_iCharN = n;
		m_changeFlags |= text_changed;
	}
}

void WLabelField::SetSize(const WSizeF& size)
{
	if (m_size != size)
	{
		m_size = size;
		//m_changeFlags |= size_changed;
	}
}

void WLabelField::SetShowBoundingFlag(bool show)
{
	if (m_bShowBounding != show)
	{
		m_bShowBounding = show;
		m_changeFlags |= show_bounding_changed;
	}
}

void WLabelField::SetText(const std::wstring& text)
{
	if (m_text != text)
	{
		m_text = text;
		m_changeFlags |= text_changed;
	}
}

void WLabelField::SetFont(const WFont& font)
{
	if (m_font != font)
	{
		m_font = font;
		m_changeFlags |= font_changed;
	}
}

void WLabelField::SetTextPen(const WPen& pen)
{
	if (m_penText != pen)
	{
		m_penText = pen;
		m_changeFlags |= pen_changed;
	}
}

void WLabelField::SetBoundingPen(const WPen& pen)
{
	if (m_penBounding != pen)
	{
		m_penBounding = pen;
		m_changeFlags |= bounding_pen_changed;
	}
}

void WLabelField::SetBrush(const WBrush& brush)
{
	if (m_brush != brush)
	{
		m_brush = brush;
		m_changeFlags |= brush_changed;
	}
}


WLabelField& WLabelFields::operator[](field_type id)
{
	return m_fields[id];
}

const WLabelField& WLabelFields::operator[](field_type id) const
{
	return m_fields[id];
}

WLabelFields::field_type WLabelFields::GetSize() const
{
	return end;
}

int WLabelFields::GetChangeFlags() const
{
	int flags = 0;
	BOOST_FOREACH(const WLabelField& field, m_fields)
	{
		flags |= field.GetChangeFlags();
	}

	return flags;
}

bool WLabelFields::HasChange() const
{
	return GetChangeFlags() != static_cast<int>(WLabelField::none);
}

void WLabelFields::ResetChangeFlags() const
{
	BOOST_FOREACH(const WLabelField& field, m_fields)
	{
		field.ResetChangeFlags();
	}
}


void WLabelFormat::Reset()
{
	m_format.clear();
	m_formatflag.clear();
}

void WLabelFormat::SetRowCount(size_t count)
{
	Reset();
	m_format.resize(count);
	m_formatflag.resize(count);
}

void WLabelFormat::AddField(size_t row, field_type field, bool bAutoHide)
{
	m_format[row].push_back(field);
	m_formatflag[row].push_back(bAutoHide);
}

size_t WLabelFormat::GetFieldCount() const
{
	size_t count = 0;
	BOOST_FOREACH(const std::vector<field_type>& v, m_format)
	{
		count += v.size();
	}

	return count;
}


size_t WLabelFormat::GetFieldCount(size_t row) const
{
	return m_format[row].size();
}

const std::vector<std::vector<WLabelFormat::field_type> >& WLabelFormat::GetFormat()
{
	return m_format;
}

const std::vector<std::vector<bool> >& WLabelFormat::GetFormatFlag()
{
	return m_formatflag;
}

/**
\brief      ReplaceField
\Access     public 
\param      const field_type & ePreType
\param      const field_type & eCurType
\retval     void
\remark     
*/
void WLabelFormat::ReplaceField(const field_type& ePreType, const field_type& eCurType, bool bAutoHide)
{
	std::vector<std::vector<field_type> >::iterator iter = m_format.begin();
	for (; iter != m_format.end(); ++iter)
	{
		std::vector<field_type>::iterator iterField = (*iter).begin();
		for (; iterField != (*iter).end(); ++iterField)
		{
			if ((*iterField) == ePreType)
			{
				std::vector<field_type>::iterator iterCur = (*iter).insert(iterField, eCurType);
				if (iterCur != (*iter).end())
				{
					++iterCur;
					(*iter).erase(iterCur);
				}
				return;
			}
		}
	}

	// bAutoHide 没有用到，暂时没写
}

/**
\brief      DelField
\Access    public 
\param  const field_type & field
\retval     void
\remark     
*/
void WLabelFormat::DelField( const field_type& field )
{
	std::vector<std::vector<field_type> >::iterator iterFormat = m_format.begin();
	std::vector<std::vector<bool> >::iterator iterFlags = m_formatflag.begin();
	for (; iterFormat != m_format.end(); ++iterFormat, ++iterFlags)
	{
		std::vector<field_type>::iterator iterField = (*iterFormat).begin();
		std::vector<bool>::iterator iterFlag = (*iterFlags).begin();
		for (; iterField != (*iterFormat).end(); ++iterField, ++iterFlag)
		{
			if ((*iterField) == field)
			{
				(*iterFormat).erase(iterField);
				(*iterFlags).erase(iterFlag);
				return;
			}
		}
	}

}


double WLabelFormatter::m_dCharWidth = 11.; // default value
double WLabelFormatter::m_dCharHeight = 19.;  // default value


WLabelFormatter::WLabelFormatter(const WLabelFields* fields, WAircraftGlyph* label, const WLabelFormat& format) :
	m_fields(fields), m_label(label), m_format(format), m_formatChanged(true)
{
}

WLabelFormat WLabelFormatter::GetFormat() const
{
	return m_format;
}

void WLabelFormatter::SetFormat(const WLabelFormat& format)
{
	m_format = format;
	m_formatChanged = true;
}

void WLabelFormatter::Format(bool bForce)
{
	WAircraftItemData& d = *m_label->data();
	std::list<WBlockData>& blocks = d.m_blocks;
	std::list<WBlockData>::iterator block_iter = blocks.begin();
	const std::vector<std::vector<field_type> >& format = m_format.GetFormat();
	const std::vector<std::vector<bool> >& formatflag = m_format.GetFormatFlag();

	if (bForce || m_formatChanged)
	{
		FormatAllChanged(format, formatflag, d, blocks, block_iter);
		m_formatChanged = false;
	}
	else
	{
		int flags = m_fields->GetChangeFlags();

		if (flags & WLabelField::size_changed)
		{
			FormatSizeChanged(format, d, blocks, block_iter);
			flags &= ~WLabelField::size_changed;
		}

		if (flags & WLabelField::text_changed)
		{
			FormatTextChanged(format, formatflag, d, blocks, block_iter);
			flags &= ~WLabelField::text_changed;
		}

		if (flags)
		{
			Format(format, d, blocks, block_iter);
		}
	}

	m_fields->ResetChangeFlags();
	m_label->updateCache();
}

void WLabelFormatter::FormatAllChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag,
					  WAircraftItemData& d, std::list<WBlockData>& blocks, std::list<WBlockData>::iterator block_iter)
{
	blocks.clear();
	blocks.resize(m_format.GetFieldCount());
	block_iter = blocks.begin();

	double maxWidth = 0.0;
	double currHeight = SPACING_BOTTOM;
	
	BOOST_AUTO(flag_iter_h, formatflag.begin());
	
	BOOST_FOREACH(const std::vector<field_type>& fts, format)
	{
		double currWidth = SPACING_LEFT;
		double maxHeight = 0.0;
		BOOST_AUTO(flag_iter, flag_iter_h->begin());

		BOOST_FOREACH(field_type ft, fts)
		{
			const WLabelField& field = (*m_fields)[ft];
			WBlockData& block = *block_iter;

			/*WSizeF size = field.GetSize();
			double width = size.width();
			double height = size.height();*/
			block.m_iId = static_cast<int>(ft);
			block.m_bShowBounding = field.GetShowBoundingFlag();
			block.m_text = field.GetText();
			block.m_font = field.GetFont();
			block.m_penText = field.GetTextPen();
			block.m_penBounding = field.GetBoundingPen();
			block.m_brush = field.GetBrush();

			double width = .0;
			double height = .0;
			if (!block.m_text.empty())
			{
				width = m_dCharWidth * CountWString(block.m_text);
				height = m_dCharHeight;
			}
			else if (*flag_iter == false) // false
			{
				width = m_dCharWidth * field.GetCharN();
				height = m_dCharHeight;
			}

			block.m_boundingRect.setRect(currWidth, currHeight, width, height);
			currWidth += width + SPACING_COLUMN;
			if (height > maxHeight)
			{
				maxHeight = height;
			}

			++block_iter;
			++flag_iter;
		}

		if (currWidth > maxWidth)
		{
			maxWidth = currWidth;
		}
		currHeight += maxHeight + SPACING_ROW;

		++flag_iter_h;
	}

	d.m_boundingRect.setRect(d.m_boundingRect.x(), d.m_boundingRect.y(), maxWidth, currHeight);
	d.m_showRect = d.m_boundingRect;

	// check first line and last line
	// 由于非自动隐藏的field_type，在内容为empty的时候，根据CharN来
	// 确定占用大小，对于标牌来说，如果该行，所有自动隐藏的区域内容为空，非自动隐藏区域，内容为空，标牌上的边框将不包含这
	// 一行
	// 算法只考虑了（第一行与最后一行）(正常算法，应该第一行情况满足上述条件，需进行第二行检查，
	// 由于实际应用主要只涉及到confim & label_data, 一般在第一行，最后一行, 所有不进行复杂算法)
	if (!format.empty())
	{
		//first
		BOOST_AUTO(vf_begin, format.begin());
		BOOST_AUTO(vfg_begin, formatflag.begin());
		
		bool bCheckHide = false;
		int i = 0;
		BOOST_FOREACH(field_type ft, *vf_begin)
		{
			const WLabelField& field = (*m_fields)[ft];
			if (!field.GetText().empty())//not empty
			{
				bCheckHide = false;
				break;
			}
			else if (!vfg_begin->at(i))
			{
				bCheckHide = true; // has no-auto hide field
			}
			++i;
		}

		if (bCheckHide)  
		{
			d.m_showRect.setRect(d.m_showRect.x(), d.m_showRect.y() + m_dCharHeight, d.m_showRect.width(), d.m_showRect.height() - m_dCharHeight);
		}

		// last
		if (format.size() == 1)
		{
			return;
		}
		
		BOOST_AUTO(vf_end, format.rbegin());
		BOOST_AUTO(vfg_end, formatflag.rbegin());
		bCheckHide = false;
		i = 0;
		BOOST_FOREACH(field_type ft, *vf_end)
		{
			const WLabelField& field = (*m_fields)[ft];
			if (!field.GetText().empty())//not empty
			{
				bCheckHide = false;
				break;
			}
			else if (!vfg_end->at(i))
			{
				bCheckHide = true; // has no-auto hide field
			}
			++i;
		}

		if (bCheckHide)  
		{
			d.m_showRect.setRect(d.m_showRect.x(), d.m_showRect.y(), d.m_showRect.width(),  d.m_showRect.height() - m_dCharHeight);
		}

	}


}

void WLabelFormatter::FormatSizeChanged(const std::vector<std::vector<field_type> >& format, 
					   WAircraftItemData& d, std::list<WBlockData>&, std::list<WBlockData>::iterator block_iter)
{
	return;
}

void WLabelFormatter::FormatTextChanged(const std::vector<std::vector<field_type> >& format, const std::vector<std::vector<bool> >& formatflag,
					   WAircraftItemData& d, std::list<WBlockData>&, std::list<WBlockData>::iterator block_iter)
{

	double maxWidth = 0.0;
	double currHeight = SPACING_BOTTOM;
	BOOST_AUTO(flag_iter_h, formatflag.begin());

	BOOST_FOREACH(const std::vector<field_type>& fts, format)
	{
		double currWidth = SPACING_LEFT;
		double maxHeight = 0.0;

		BOOST_AUTO(flag_iter, flag_iter_h->begin());
		BOOST_FOREACH(field_type ft, fts)
		{
			const WLabelField& field = (*m_fields)[ft];
			WBlockData& block = *block_iter;

			if (field.GetChangeFlags() & WLabelField::text_changed)
			{
				block_iter->m_text = field.GetText();
			}

			double width = .0;
			double height = .0;
			if (!block.m_text.empty())
			{
				width = m_dCharWidth * CountWString(block.m_text);
				height = m_dCharHeight;
			}
			else if (!(*flag_iter)) // false
			{
				width = m_dCharWidth * field.GetCharN();
				height = m_dCharHeight;
			}
		
			block.m_boundingRect.setRect(currWidth, currHeight, width, height);
			currWidth += width + SPACING_COLUMN;
			if (height > maxHeight)
			{
				maxHeight = height;
			}

			++block_iter;
			++flag_iter;
		}

		if (currWidth > maxWidth)
		{
			maxWidth = currWidth;
		}
		currHeight += maxHeight + SPACING_ROW;

		++flag_iter_h;
	}

	d.m_boundingRect.setRect(d.m_boundingRect.x(), d.m_boundingRect.y(), maxWidth, currHeight);

	d.m_showRect = d.m_boundingRect;

	// check first line and last line
	// 由于非自动隐藏的field_type，在内容为empty的时候，根据CharN来
	// 确定占用大小，对于标牌来说，如果该行，所有自动隐藏的区域内容为空，非自动隐藏区域，内容为空，标牌上的边框将不包含这
	// 一行
	// 算法只考虑了（第一行与最后一行）(正常算法，应该第一行情况满足上述条件，需进行第二行检查，
	// 由于实际应用主要只涉及到confim & label_data, 一般在第一行，最后一行, 所有不进行复杂算法)
	if (!format.empty())
	{
		//first
		BOOST_AUTO(vf_begin, format.begin());
		BOOST_AUTO(vfg_begin, formatflag.begin());

		bool bCheckHide = false;
		int i = 0;
		BOOST_FOREACH(field_type ft, *vf_begin)
		{
			const WLabelField& field = (*m_fields)[ft];
			if (!field.GetText().empty())//not empty
			{
				bCheckHide = false;
				break;
			}
			else if (!vfg_begin->at(i))
			{
				bCheckHide = true; // has no-auto hide field
			}

			++i;
		}
		
		if (bCheckHide)
		{
			d.m_showRect.setRect(d.m_showRect.x(), d.m_showRect.y() + m_dCharHeight, d.m_showRect.width(), d.m_showRect.height() - m_dCharHeight);
		}


		// last
		if (format.size() == 1)
		{
			return;
		}

		BOOST_AUTO(vf_end, format.rbegin());
		BOOST_AUTO(vfg_end, formatflag.rbegin());
		bCheckHide = false;
		i = 0;
		BOOST_FOREACH(field_type ft, *vf_end)
		{
			const WLabelField& field = (*m_fields)[ft];
			if (!field.GetText().empty())//not empty
			{
				bCheckHide = false;
				break;
			}
			else if (!vfg_end->at(i))
			{
				bCheckHide = true; // has no-auto hide field
			}
			++i;
		}

		if (bCheckHide)  
		{
			d.m_showRect.setRect(d.m_showRect.x(), d.m_showRect.y(), d.m_showRect.width(), d.m_showRect.height() - m_dCharHeight);
		}

	}

}

void WLabelFormatter::Format(const std::vector<std::vector<field_type> >& format, 
			WAircraftItemData& d, std::list<WBlockData>&, std::list<WBlockData>::iterator block_iter)
{
	BOOST_FOREACH(const std::vector<field_type>& fts, format)
	{
		BOOST_FOREACH(field_type ft, fts)
		{
			const WLabelField& field = (*m_fields)[ft];
			WBlockData& block = *block_iter;
			
			int flags = field.GetChangeFlags();

			if (flags & WLabelField::show_bounding_changed)
			{
				block.m_bShowBounding = field.GetShowBoundingFlag();
				d.m_bShowBounding = block.m_bShowBounding;
			}

			if (flags & WLabelField::font_changed)
			{
				block.m_font = field.GetFont();
			}

			if (flags & WLabelField::pen_changed)
			{
				block.m_penText = field.GetTextPen();
			}

			if (flags & WLabelField::bounding_pen_changed)
			{
				block.m_penBounding = field.GetBoundingPen();
			}

			if (flags & WLabelField::brush_changed)
			{
				block.m_brush = field.GetBrush();
			}
			
			++block_iter;
		}
	}
}

/**
\brief      UpdateCharSize
\Access    public 
\retval     void
\remark     
*/
void WLabelFormatter::UpdateCharSize()
{
	const WFontMetrics metrics(WAircraftGlyph::getLabelFont());
	m_dCharWidth = metrics.averageCharWidth();
	m_dCharHeight = metrics.height();
}

