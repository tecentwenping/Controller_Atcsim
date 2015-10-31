#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <boost/shared_ptr.hpp>
//该类主要管理地图图元的相关功能
class CSimMap;
class Coordinate;
class CGlyphCreator;
class CGlyphUpdater;
class CGlyphManager;

typedef boost::shared_ptr<CGlyphManager> GlyphManagerPtr;
typedef boost::shared_ptr<CSimMap> SimMapPtr;
typedef boost::shared_ptr<Coordinate> CoordinatePtr;
typedef boost::shared_ptr<CGlyphUpdater> GlyphUpdaterPtr;
typedef boost::shared_ptr<CGlyphCreator> GlyphCreatorPtr;

class CMapManager
{


public:
	CMapManager();
	~CMapManager();
public:
	void InitMapScene();
	void InitGlyphs();
public:
	SimMapPtr		GetSimMapPtr()const;
	CoordinatePtr	GetMapCoordinatePtr()const;
	GlyphManagerPtr GetGlyphManagerPtr()const;
	GlyphUpdaterPtr GetGlyphUpdaterPtr()const;
	GlyphCreatorPtr GetGlyphCreatorPtr()const;
private:
	GlyphUpdaterPtr	m_pGlyphUpdater;
	GlyphCreatorPtr m_pGlyphCreator;
	GlyphManagerPtr m_pGlyphManager;
	CoordinatePtr   m_pCoordinate;
	SimMapPtr		m_pSimMap;



};

#endif // MAPMANAGER_H
