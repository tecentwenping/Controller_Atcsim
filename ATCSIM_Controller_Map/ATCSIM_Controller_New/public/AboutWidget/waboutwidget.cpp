#include "waboutwidget.h"
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

WAboutWidget::WAboutWidget(QWidget* parent) : QDialog(parent)
{
	setWindowFlags(Qt::WindowStaysOnTopHint);//´°¿ÚÖÃ¶¥
	//ok button
	QPushButton* btn_ok = new QPushButton("OK", this);
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(hide()));
	QHBoxLayout* horizontalLayout = new QHBoxLayout();
	horizontalLayout->addItem(new QSpacerItem(0, 0));
	horizontalLayout->addWidget(btn_ok);
	horizontalLayout->addItem(new QSpacerItem(0, 0));
	horizontalLayout->setStretch(0, 5);
	horizontalLayout->setStretch(1, 2);
	horizontalLayout->setStretch(2, 5);

	//wisesoft symbol
	QLabel* label_image = new QLabel(this);
	label_image->setPixmap(QPixmap(QString(":/wisesoft.png")));

	//version
	label_version = new QLabel(this);
	
	QVBoxLayout* verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(0);
	verticalLayout->addWidget(label_image);
	verticalLayout->addWidget(label_version);
	QFile copyright_html(":/copyright.html");
	copyright_html.open(QIODevice::ReadOnly);
	verticalLayout->addWidget(new QLabel(QString(copyright_html.readAll()), this));
	verticalLayout->addLayout(horizontalLayout);

	verticalLayout->setStretch(0, 3);
	verticalLayout->setStretch(1, 1);
	verticalLayout->setStretch(2, 3);
	verticalLayout->setStretch(3, 1);

	resize(382, 301);
}

void WAboutWidget::SetVersionInfo(const QString& version)
{
	static const char* VERSION_PREFIX = "<p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">";
	static const char* VERSION_POSTFIX = "</span></p>";

	label_version->setText(VERSION_PREFIX + version + VERSION_POSTFIX);
}