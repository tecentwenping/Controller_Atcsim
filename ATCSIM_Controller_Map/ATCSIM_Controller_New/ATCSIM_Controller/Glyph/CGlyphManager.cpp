#include "CGlyphManager.h"
#include "waircraftglyph.h"

CGlyphManager::CGlyphManager()

{

}

CGlyphManager::~CGlyphManager()
{

}

void CGlyphManager::AddGlyph( GlyphType type,GlyphIdentity glyphIdentity,MapGlyph* pGlyph )
{
	GlyphIdentityPtr pIdentity = boost::make_shared<GlyphIdentity>(glyphIdentity);
	m_mpGlyph[type].insert(std::make_pair(pIdentity,pGlyph));
}

void CGlyphManager::AddGlyph( GlyphType type,MapGlyph* pGlyph )
{
	GlyphIdentityPtr pIdentity = boost::make_shared<GlyphIdentity>();
	m_mpGlyph[type].insert(std::make_pair(pIdentity,pGlyph));

}
void CGlyphManager::GetGlyph(const GlyphType& type, const int& nTraceID, WAircraftGlyph** pMapGlyph)
{
	std::map<GlyphIdentityPtr, MapGlyph *>::iterator iter = m_mpGlyph[type].begin();
	for (; iter != m_mpGlyph[type].end(); ++iter)
	{
		if (nTraceID == iter->first->m_nTraceID)
		{
			//转换为指定类型的图元类型
			*pMapGlyph = dynamic_cast<WAircraftGlyph* >(iter->second);
			return;
		}
	}
}
