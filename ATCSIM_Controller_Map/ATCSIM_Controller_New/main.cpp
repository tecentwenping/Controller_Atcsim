#include <QtGui/QApplication>
#include "controllerwndscreator.h"
#include <QWidget>
#include "wgraphicsscene.h"
#include "MainApp.h"
#include "controllerwndscreator.h"
#include "CtrollerCallbackLogic.h"
#include "cmainwindow.h"
#include "CtrollerWndsManager.h"
#include<boost/make_shared.hpp>
#include "Net/RecvAircraftTrace.h"
#include <QThread>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFile styleSheet("./eurocat_style.qss");
	if(!styleSheet.open(QIODevice::ReadOnly)){
		qWarning("Unable to open :/eurocat_style.qss");
	}
	qApp->setStyleSheet(styleSheet.readAll());
	//qApp->setStyleSheet("background-color: rgb(109, 109, 0);");
	//回调逻辑类，用处不是特别大
	boost::shared_ptr<CMainCallBackLogic> pCallback = boost::make_shared<CtrollerCallbackLogic>();
	//窗口管理类的初始化
	boost::shared_ptr<CWndsManager> pWndsManager = boost::make_shared<CtrollerWndsManager>();
	//初始化主窗口
	CMainWindow *pMainWindow = new CMainWindow(pCallback);
	//初始化窗口创建类
	boost::shared_ptr<WndsCreator> pWndsCreator = boost::make_shared<ControllerWndsCreator>(pWndsManager,pMainWindow);
	theApp::instance().SetMainCallbackPtr(pCallback);//设置主回调逻辑
	theApp::instance().SetMainWindowPtr(pMainWindow);//设置主窗体
	theApp::instance().SetWndsMangerPtr(pWndsManager);//设置窗体管理类
	theApp::instance().SetWndsCreatorPtr(pWndsCreator);//设置窗体创建类
	if(!theApp::instance().InitAppInstance())//初始化地图
	{
		return -1;
		
	}
	return a.exec();
}
