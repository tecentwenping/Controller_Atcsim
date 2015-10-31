#ifndef CONTROLLERWNDSCREATOR_H
#define CONTROLLERWNDSCREATOR_H

#include "wndscreator.h"
#include <boost/shared_ptr.hpp>
#include <QWidget>
#include <QMainWindow>
class TotalBaseData;
class Coordinate;
class RunwayData;
class CSimMap;
class GetDataFromDB;
class CMapView;
class CWndsManager;
class CMapManager;

//typedef boost::shared_ptr<CMapManager> MapManagerPtr;
typedef boost::shared_ptr<CMapView> MapViewPtr;
typedef boost::shared_ptr<CSimMap>  SimMapPtr;
class ControllerWndsCreator : public WndsCreator
{
public:
	ControllerWndsCreator(QMainWindow *pMainWindow);
	ControllerWndsCreator(boost::shared_ptr<CWndsManager> pWndsManager,QMainWindow* pMainWindow);
	~ControllerWndsCreator();
public:
	virtual void InitAppWnds();
private:
	QMainWindow		*m_pMainWindow;
	/*CSimMap			*m_pSimMap;
	CMapView		*m_pMapView;
	CMapManager 	*m_pMapManager;*/

};

#endif // CONTROLLERWNDSCREATOR_H
