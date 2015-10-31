#ifndef CGLYPHMANAGER_H
#define CGLYPHMANAGER_H
#include "wglyphidentity.h"
#include "EnumVarible.h"
#include<map>
#include <vector>
#include "wgraphicsitem.h"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include <boost/make_shared.hpp>

using namespace boost;
using namespace boost::signals2;
class WColor;
class WAircraftGlyph;
typedef WGlyphIdentity GlyphIdentity;
typedef boost::shared_ptr<GlyphIdentity> GlyphIdentityPtr;
typedef WGraphicsItem MapGlyph;

class CGlyphManager
{
public:
	typedef signal<void()> sigtype_updateMap;
	typedef signal<void(WGraphicsItem*,int)> sigtype_updateGlyph;
	typedef std::map<GlyphIdentityPtr,MapGlyph*> mpGlyph;
	typedef std::map<GlyphType,mpGlyph> mpGlyphs;

public:
	CGlyphManager();
	~CGlyphManager();
public:
	void AddGlyph(GlyphType type,GlyphIdentity glyphIdentity,MapGlyph* pGlyph);
	void AddGlyph(GlyphType type,MapGlyph* pGlyph);
	template<typename T>
	void RemoveGlyph(GlyphType type,T* pGlyph);
	template<typename T>
	void GetGlyph(GlyphType type, std::vector<T*>& vMapGlyph);

	template<typename T>
	void GetGlyph(int nLayerID, std::vector<T*>& vMapGlyph);

	//返回图元相关的属性数据
	template<typename T>
	void GetGlyph(GlyphType type, std::map<GlyphIdentityPtr, T*>& vMapGlyph);

	template<typename T>
	void GetGlyph(GlyphType type, const std::string& szName, T** pMapGlyph);

	//因为可能同时存在呼号相同的几个航空器或车辆，通过类型和ID来找航空器或车辆图元
	void GetGlyph(const GlyphType& type, const int& nTraceID, WAircraftGlyph** pMapGlyph);
public:
	sigtype_updateMap m_sig_updateMap;
	sigtype_updateGlyph m_sig_clearGlyph;
private:
	mpGlyphs	m_mpGlyph;
	
};
template<typename T>
void CGlyphManager::RemoveGlyph(GlyphType type,T* pGLyph)
{
	std::map<GlyphIdentityPtr,MapGlyph*>::iterator iter = m_mpGlyph[type].begin();
	for(; iter != m_mpGlyph[type].end(); ++iter)
	{
		if(pGLyph == iter->second)
		{
			m_mpGlyph[type].erase(iter);
			break;
		}
	}
}
//根据图元类型以及图元名称查找图元
template<typename T>
void CGlyphManager::GetGlyph(GlyphType type, const std::string& szName, T** pMapGlyph)
{
	std::map<GlyphIdentityPtr, MapGlyph *>::iterator iter = m_mpGlyph[type].begin();
	for (; iter != m_mpGlyph[type].end(); ++iter)
	{
		if (0 == strcmp(szName.c_str(), iter->first->strName.c_str()))
		{
			//转换为指定类型的图元类型
			*pMapGlyph = dynamic_cast<T* >(iter->second);
			return;
		}
	}
}


//根据图层查找图元组
template<typename T>
void CGlyphManager::GetGlyph(int nLayerID, std::vector<T*>& vMapGlyph)
{

}


template<typename T>
void CGlyphManager::GetGlyph(GlyphType type, std::map<GlyphIdentityPtr, T*>& vMapGlyph)
{
	mpGlyph glyphs = m_mpGlyph[type];
	mpGlyph::iterator iter = glyphs.begin();
	for (; iter != glyphs.end(); ++iter)
	{
		vMapGlyph.insert(std::make_pair(iter->first, dynamic_cast<T*>(iter->second)));
	}
}


//根据图元类型查找图元组
template<typename T>
void CGlyphManager::GetGlyph(GlyphType type, std::vector<T*>& vMapGlyph)
{
	vMapGlyph.clear();
	if (!m_mpGlyph[type].empty())
	{
		std::map<GlyphIdentityPtr, MapGlyph *>::iterator iter = m_mpGlyph[type].begin();
		for (; iter != m_mpGlyph[type].end(); ++iter)
		{
			vMapGlyph.push_back(dynamic_cast<T*>(iter->second));
		}
	}
}


#endif // CGLYPHMANAGER_H
