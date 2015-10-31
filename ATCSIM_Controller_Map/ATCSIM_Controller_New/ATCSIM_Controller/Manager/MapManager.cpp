#include "MapManager.h"
#include "totalbasedata.h"
#include "airport_data_objs.h"
#include "coordinate.h"
#include "wrunwayglyph.h"
#include "wglyphidentity.h"
#include "getdatafromdb.h"
#include "CMapView.h"
#include "wunclosedlineglyph.h"
#include "wnavpointglyph.h"
#include "wgateglyph.h"
#include "wpainter.h"
#include "wqtpainter.h"
#include "WndsManager.h"
#include "CSimMap.h"
#include "CMapView.h"
#include "MapManager.h"
#include "CGlyphCreator.h"
#include "CGlyphUpdater.h"
#include "CGlyphManager.h"
CMapManager::CMapManager()
{
}
CMapManager::~CMapManager()
{

}
SimMapPtr CMapManager::GetSimMapPtr() const
{
   return m_pSimMap;
}

CoordinatePtr CMapManager::GetMapCoordinatePtr() const
{
   return m_pCoordinate;
}
GlyphManagerPtr CMapManager::GetGlyphManagerPtr() const
{
  return m_pGlyphManager;
}

GlyphUpdaterPtr CMapManager::GetGlyphUpdaterPtr() const
{

return m_pGlyphUpdater;
}

GlyphCreatorPtr CMapManager::GetGlyphCreatorPtr() const
{
	return m_pGlyphCreator;
}

void CMapManager::InitGlyphs()
{
   //初始化图元管理
	if(!m_pGlyphManager)
	{
		m_pGlyphManager = boost::make_shared<CGlyphManager>();
	}
	//初始化图元创建者
	if(!m_pGlyphCreator)
	{
		m_pGlyphCreator = boost::make_shared<CGlyphCreator>(m_pGlyphManager,m_pCoordinate,m_pSimMap);
	}
	m_pGlyphCreator->InitMapGlyph();
	//初始化图元更新者
	if(!m_pGlyphUpdater)
	{
		m_pGlyphUpdater = boost::make_shared<CGlyphUpdater>();
	}
}

void CMapManager::InitMapScene()
{
	if(!m_pSimMap)
	{
		m_pSimMap = boost::make_shared<CSimMap>();
		m_pSimMap->InitMapScene();
	}
	//初始化坐标系统
	if(!m_pCoordinate)
	{
		m_pCoordinate = boost::make_shared<Coordinate>(0,0);
	}

}
