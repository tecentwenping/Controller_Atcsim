#ifndef CMAINCALLBACKLOGIC_H
#define CMAINCALLBACKLOGIC_H


//���������ص��߼������࣬��Ϊ��ͬ�Ľ�������漰
//����ͬ�Ĳ��������Խ��������Ϊ����

#include <QtGui>
#include "wglyphidentity.h"
class CMapManager;

class CMainCallBackLogic
{
	

public:
	CMainCallBackLogic();
	virtual ~CMainCallBackLogic();
public:
	//�����ݼ�����
	virtual void ProcessKeyEvent(QKeyEvent *event);
	virtual void ProcessMouseMoveEvent(QMouseEvent *event);
	virtual void ProcessMousePressEvent(QMouseEvent *event);
	virtual void ProcessSetCurAircraft(const int nID){};
	
};

#endif // CMAINCALLBACKLOGIC_H
