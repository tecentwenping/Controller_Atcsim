#ifndef _SIMMAP_H
#define _SIMMAP_H

#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>

#include "wworldpoint.h"
class CMapView;
class WGraphicsItem;
class WGraphicsScene;
//���ฺ���ͼ������߼���֯���䴦��
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
	//��ʼ����ͼ����
	void InitMapScene();
	void AddItemToMapScene(WGraphicsItem* pGlyphItem, int nLayerID = -1);
	void RemoveItemFromMapScene(WGraphicsItem* pGlyphItem, int nLayerID = -1);

	//��ճ���ͼ��
	void ClearAllLayers();
	void UpdateMap();


public:
	CMapView* GetMainMapView();
	boost::shared_ptr<WGraphicsScene>& GetMapScene() { return m_pMapScene; }
private:
	CMapView*    m_pMainMapView;  //����ͼ����
	boost::shared_ptr<WGraphicsScene> m_pMapScene; 
};
#endif