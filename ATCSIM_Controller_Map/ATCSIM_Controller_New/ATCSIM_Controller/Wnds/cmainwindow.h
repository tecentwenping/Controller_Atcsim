#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <boost/shared_ptr.hpp>
#include <QWidget>
#include <QMainWindow>
class CMainCallBackLogic;
class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent=0);
	CMainWindow(boost::shared_ptr<CMainCallBackLogic> pCallback,QWidget* parent=0);
	~CMainWindow();
protected:
	virtual void keyPressEvent(QKeyEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
private:
	boost::shared_ptr<CMainCallBackLogic> m_pCallback;
	
};

#endif // CMAINWINDOW_H
