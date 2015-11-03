#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QDebug>
#include <QTime>
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
	qDebug()<<"info in main()	Info:start the application	Time:"+QTime::currentTime().toString();
 	if(!theApp::instance().InitAppInstance())
 	{
		qDebug()<<"error in main()  Info:init application failed  Time:"+QTime::currentTime().toString();
 		return -1;
 	}
	qDebug()<<"info in main()	Info:init application successed	Time:"+QTime::currentTime().toString();
	return a.exec();
}
