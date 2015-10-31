#ifndef _WSYSINFO_GLYPH_H
#define _WSYSINFO_GLYPH_H

#include "wgraphicsitem.h"

class WSysInfoItemData: public WItemData
{
public:
	WSysInfoItemData();

	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;
public:
	std::string m_strLongitude;
	std::string m_strLatitude;
};


//show some system info, like mouse coordinate
class WSysInfoGlyph: public WGraphicsItem
{
	RTTI_DECL(WSysInfoGlyph)
public:
	typedef WSysInfoItemData data_type;
public:
	explicit WSysInfoGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};



#endif