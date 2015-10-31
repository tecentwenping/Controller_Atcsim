#ifndef _SIMMAP_H
#define _SIMMAP_H

#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>

#include "wworldpoint.h"
class CMapView;
class WGraphicsItem;
class WGraphicsScene;
//该类负责地图的相关逻辑组织及其处理
typedef boost::shared_ptr<CMapView> MapViewPtr;
class CSimMap
{
public:
	enum LAYER
	{
		LAYER_BACKGROUD,
		LAYER_ACFT,
		LAYER_BEACON,
	};
public:
	CSimMap();
	~CSimMap();
public:
	//初始化地图场景
	void InitMapScene();
	void AddItemToMapScene(WGraphicsItem* pGlyphItem, int nLayerID = -1);
	void RemoveItemFromMapScene(WGraphicsItem* pGlyphItem, int nLayerID = -1);

	//清空场景图层
	void ClearAllLayers();
	void UpdateMap();


public:
	CMapView* GetMainMapView();
	boost::shared_ptr<WGraphicsScene>& GetMapScene() { return m_pMapScene; }
private:
	CMapView*    m_pMainMapView;  //主地图窗口
	boost::shared_ptr<WGraphicsScene> m_pMapScene; 
};
#endif