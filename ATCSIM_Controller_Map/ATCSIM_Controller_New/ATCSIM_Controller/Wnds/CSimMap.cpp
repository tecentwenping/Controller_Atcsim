#include "CSimMap.h"
#include "wgraphicsscene.h"
#include "wgraphicsarcitem.h"
#include "wpolygoncreator.h"
#include "wrunwayglyph.h"
#include "wnavpointglyph.h"
#include <boost/thread/shared_mutex.hpp>
#include <boost/make_shared.hpp>
#include <QtGui/QGridLayout>
#include "CMapView.h"
#include "wgraphicsarcitem.h"
#include "wgraphicsscene.h"
#include "wglyphidentity.h "

extern boost::shared_mutex g_sm;

CSimMap::CSimMap()
{
	if(!m_pMapScene)
	{
  	  m_pMapScene = boost::make_shared<WGraphicsScene>();
	}
	m_pMainMapView = new CMapView(m_pMapScene.get());
	m_pMainMapView->showFullScreen();
 	m_pMainMapView->reset();
 	m_pMainMapView->setEditable(true);

 	m_pMapScene->defaultLayer()->setEditable(true);
 	m_pMapScene->addLayer(GLYPH_AIRCRAFT)->setEditable(true);
}

CSimMap::~CSimMap()
{  
  if(NULL != m_pMainMapView)
  {
	  delete m_pMainMapView;
	  m_pMainMapView = NULL;
  }

}


CMapView* CSimMap::GetMainMapView()
{
	return m_pMainMapView;
}




//将图元添加至指定的图层
void CSimMap::AddItemToMapScene(WGraphicsItem *pGlyphItem, int nLayerID /* = -1 */)
{
	nLayerID = (nLayerID == -1 ? m_pMapScene->defaultLayer()->layer() : nLayerID);
	m_pMapScene->addLayer(nLayerID)->setEditable(true);
	m_pMapScene->addLayer(nLayerID)->addItem(pGlyphItem);
}

void CSimMap::RemoveItemFromMapScene(WGraphicsItem* pGlyphItem, int nLayerID /* = -1 */)
{
	//g_sm.lock();
	if (-1 == nLayerID)
	{
		WGraphicsLayer* layer = m_pMapScene->defaultLayer();
		layer->removeItem(pGlyphItem);
	}
	else
	{
		WGraphicsLayer* layer = m_pMapScene->layer(nLayerID);
		if (layer)
		{
			layer->removeItem(pGlyphItem);
		}
	}
	//g_sm.unlock();
}


void CSimMap::InitMapScene()
{
	m_pMapScene->setAttachEnabled(true);
}


void CSimMap::ClearAllLayers()
{
	//g_sm.lock();
	if (m_pMapScene)
	{
		m_pMapScene->removeAllLayers();
	}
	//g_sm.unlock();
}

void CSimMap::UpdateMap()
{
	if (m_pMapScene)
	{
		m_pMapScene->update();
	}
}




