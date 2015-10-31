#ifndef CMAINCALLBACKLOGIC_H
#define CMAINCALLBACKLOGIC_H


//该类是主回调逻辑处理类，因为不同的界面可能涉及
//到不同的操作，所以将该类设计为基类

#include <QtGui>
#include "wglyphidentity.h"
class CMapManager;

class CMainCallBackLogic
{
	

public:
	CMainCallBackLogic();
	virtual ~CMainCallBackLogic();
public:
	//处理快捷键操作
	virtual void ProcessKeyEvent(QKeyEvent *event);
	virtual void ProcessMouseMoveEvent(QMouseEvent *event);
	virtual void ProcessMousePressEvent(QMouseEvent *event);
	virtual void ProcessSetCurAircraft(const int nID){};
	
};

#endif // CMAINCALLBACKLOGIC_H
