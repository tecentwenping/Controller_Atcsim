#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QDebug>
#include "Interface/theApp.h"
#include <boost/new_progress_timer.hpp>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator oTranslator;
	oTranslator.load(":/qt_zh_CN");
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//支持中文
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	a.installTranslator(&oTranslator);
 	if(!theApp::instance().InitAppInstance())
 	{
         qDebug()<<"Init Application failed.....";
 		return -1;
 	}
 	qDebug()<<"Init Application successed....";
	return a.exec();
}
