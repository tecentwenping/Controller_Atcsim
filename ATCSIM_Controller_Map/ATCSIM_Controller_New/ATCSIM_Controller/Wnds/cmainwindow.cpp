#include "cmainwindow.h"
#include "CMainCallbackLogic.h"
CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
{

}

CMainWindow::CMainWindow( boost::shared_ptr<CMainCallBackLogic> pCallback,QWidget* parent/*=0*/ )
:m_pCallback(pCallback),QMainWindow(parent)
{


}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::keyPressEvent( QKeyEvent * event)
{
	if(m_pCallback)
	{
		m_pCallback->ProcessKeyEvent(event);
	}

}

void CMainWindow::mouseMoveEvent( QMouseEvent * event)
{
	if(m_pCallback)
	{
		m_pCallback->ProcessMouseMoveEvent(event);
	}
  
}
