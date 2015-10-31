#ifndef _WABOUT_WIDGET_H_
#define _WABOUT_WIDGET_H_

#include <QDialog>

class QLabel;

class WAboutWidget : public QDialog
{
public:
	explicit WAboutWidget(QWidget* parent = 0);

	void SetVersionInfo(const QString& version);

private:
	QLabel* label_version;
};

#endif