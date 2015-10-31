#ifndef CHILDMAPWINDOW_H
#define CHILDMAPWINDOW_H

#include <QWidget>
#include <QKeyEvent>
class ChildMapView;
class WGraphicsScene;
#include "SimWnd.h"

class ChildMapWindow:public SimWnd
{


public:
	ChildMapWindow(WGraphicsScene* s,QWidget *parent);
	~ChildMapWindow();
	ChildMapView* GetChildMapView();
protected:
	virtual void keyPressEvent(QKeyEvent *event);

private:
	ChildMapView *m_pChildMapView;
	WGraphicsScene *m_pScene;
	
};

#endif // CHILDMAPWINDOW_H
