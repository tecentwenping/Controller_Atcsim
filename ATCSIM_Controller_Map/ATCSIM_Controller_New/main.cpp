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
	//�ص��߼��࣬�ô������ر��
	boost::shared_ptr<CMainCallBackLogic> pCallback = boost::make_shared<CtrollerCallbackLogic>();
	//���ڹ�����ĳ�ʼ��
	boost::shared_ptr<CWndsManager> pWndsManager = boost::make_shared<CtrollerWndsManager>();
	//��ʼ��������
	CMainWindow *pMainWindow = new CMainWindow(pCallback);
	//��ʼ�����ڴ�����
	boost::shared_ptr<WndsCreator> pWndsCreator = boost::make_shared<ControllerWndsCreator>(pWndsManager,pMainWindow);
	theApp::instance().SetMainCallbackPtr(pCallback);//�������ص��߼�
	theApp::instance().SetMainWindowPtr(pMainWindow);//����������
	theApp::instance().SetWndsMangerPtr(pWndsManager);//���ô��������
	theApp::instance().SetWndsCreatorPtr(pWndsCreator);//���ô��崴����
	if(!theApp::instance().InitAppInstance())//��ʼ����ͼ
	{
		return -1;
		
	}
	return a.exec();
}
